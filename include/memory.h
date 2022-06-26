#ifndef XEN_MEM_H
#define XEN_MEM_H

#include <iostream>

struct AllocationMetrics {
  uint32_t TotalAllocated = 0;
  uint32_t TotalFreed = 0;
  uint32_t CurrentUsage() { return TotalAllocated - TotalFreed; }
};

static AllocationMetrics s_AllocationMetrics;

void *operator new(size_t size) {
  s_AllocationMetrics.TotalAllocated += size;
  std::cout << "[MEMORY]: Allocating " << size << " bytes\n";
  return malloc(size);
}

void operator delete(void *memory, size_t size) {
  s_AllocationMetrics.TotalFreed += size;
  std::cout << "[MEMORY]: Free " << size << " bytes\n";
  free(memory);
}

static void PrintMemoryUsage() {
  std::cout << "[LOG]: Memory usage = " << s_AllocationMetrics.CurrentUsage()
            << " bytes\n";
}

#endif
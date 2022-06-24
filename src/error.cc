#include <iostream>

class IXenException : public std::exception {};

// error if the file is not .xen file
class FileExtensionError : public IXenException {};

SRC_DIR := ../src
OBJ_DIR := .../obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cc)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cc,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS := ...
CPPFLAGS := ...
CXXFLAGS := ...

main.exe: $(OBJ_FILES)
   g++ $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
   g++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

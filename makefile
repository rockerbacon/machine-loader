CXX=g++ --std=c++14

SRC_DIR=./src/objs
HEADERS_DIR=./headers
TESTS_DIR=./tests

TEST_BUILD_DIR=./test_build
OBJS_BUILD_DIR=./objs

RELEASE_BUILD_DIR=./release

RELEASE_SRC_DIR=./src

OBJS=$(patsubst $(SRC_DIR)/%.cpp, $(OBJS_BUILD_DIR)/%.o, $(wildcard $(SRC_DIR)/*.cpp))
TESTS=$(patsubst $(TESTS_DIR)/%.cpp, $(TEST_BUILD_DIR)/%, $(wildcard $(TESTS_DIR)/*.cpp))
RELEASES=$(patsubst $(RELEASE_SRC_DIR)/%.cpp, $(RELEASE_BUILD_DIR)/%, $(wildcard $(RELEASE_SRC_DIR)/*.cpp))

CXXFLAGS=-I$(HEADERS_DIR)

.SECONDARY: $(OBJS)

.PHONY: clean tests build_obj_build_path

nothing: $(RELEASES)

clean:
	rm -f $(OBJS_BUILD_DIR)/*
	rm -f $(TEST_BUILD_DIR)/*
	rm -f $(RELEASE_BUILD_DIR)/*


$(OBJS_BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADER_DEPS) | $(OBJS_BUILD_DIR)
	$(CXX) -c $< -o $(OBJS_BUILD_DIR)/$*.o $(CXXFLAGS)

$(TEST_BUILD_DIR)/%: $(TESTS_DIR)/%.cpp $(OBJS) | $(TEST_BUILD_DIR)
	$(CXX) $^ -o $(TEST_BUILD_DIR)/$* $(CXXFLAGS)

tests: $(TESTS)

$(RELEASE_BUILD_DIR)/%: $(RELEASE_SRC_DIR)/%.cpp $(OBJS) | $(RELEASE_BUILD_DIR)
	$(CXX) -static $^ -o $(RELEASE_BUILD_DIR)/$* $(CXXFLAGS)

$(TEST_BUILD_DIR):
	mkdir -p $@

$(OBJS_BUILD_DIR):
	mkdir -p $@

$(RELEASE_BUILD_DIR):
	mkdir -p $@

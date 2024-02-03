#TUPOY 21 MAKEFILE

#TYPYE PEREMENNYE
BUILD_DIR=build/
MKDIR_EXISTING=mkdir -p
CXX=g++
CXX_FLAGS= -O3 -lrt -lm -g -std=c++20
GTEST_FLAGS=-lgtest -lpthread
CONTAINERS_DIR=./lib/containers
UNIT_TESTS_DIR=unit_tests
TESTING_INCLUDE_PATH=$(CONTAINERS_DIR)/testing_include
CPPFLAGS = -isystem ./include
MOVE=mv

#TYPYA OTCHISTKA
clean :
	rm -rf $(BUILD_DIR)/*

#TYPOE SOZDANIE BUILD PAPKI
___build_dir___ :
	$(MKDIR_EXISTING) $(BUILD_DIR)

#TYPOY OBJNYY CONTEYNER
LIST=list
MAP=map
QUEUE=queue
SET=set
STACK=stack
VECTOR=vector
test_base : clean ___build_test_list___ ___build_test_map___ ___build_test_queue___ ___build_test_set___ ___build_test_stack___ ___build_test_vector___
	./$(BUILD_DIR)$(LIST)
	./$(BUILD_DIR)$(MAP)
	./$(BUILD_DIR)$(QUEUE)
	./$(BUILD_DIR)$(SET)
	./$(BUILD_DIR)$(STACK)
	./$(BUILD_DIR)$(VECTOR)



___build_test_list___ : ___build_dir___
	$(CXX) $(CXX_FLAGS) -I$(TESTING_INCLUDE_PATH) -I$(CONTAINERS_DIR)/$(LIST)/ $(CPPFLAGS) \
	$(CONTAINERS_DIR)/$(LIST)/$(UNIT_TESTS_DIR)/*.cpp \
	$(GTEST_FLAGS) -o $(LIST)
	$(MOVE) $(LIST) $(BUILD_DIR)

___build_test_map___ : ___build_dir___
	$(CXX) $(CXX_FLAGS) -I$(TESTING_INCLUDE_PATH) -I$(CONTAINERS_DIR)/$(MAP)/ $(CPPFLAGS) \
	$(CONTAINERS_DIR)/$(MAP)/$(UNIT_TESTS_DIR)/*.cpp \
	$(GTEST_FLAGS) -o $(MAP)
	$(MOVE) $(MAP) $(BUILD_DIR)

___build_test_queue___ : ___build_dir___
	$(CXX) $(CXX_FLAGS) -I$(TESTING_INCLUDE_PATH) -I$(CONTAINERS_DIR)/$(QUEUE)/ $(CPPFLAGS) \
	$(CONTAINERS_DIR)/$(QUEUE)/$(UNIT_TESTS_DIR)/*.cpp \
	$(GTEST_FLAGS) -o $(QUEUE)
	$(MOVE) $(QUEUE) $(BUILD_DIR)

___build_test_set___ : ___build_dir___
	$(CXX) $(CXX_FLAGS) -I$(TESTING_INCLUDE_PATH) -I$(CONTAINERS_DIR)/$(SET)/ $(CPPFLAGS) \
	$(CONTAINERS_DIR)/$(SET)/$(UNIT_TESTS_DIR)/*.cpp \
	$(GTEST_FLAGS) -o $(SET)
	$(MOVE) $(SET) $(BUILD_DIR)

___build_test_stack___ : ___build_dir___
	$(CXX) $(CXX_FLAGS) -I$(TESTING_INCLUDE_PATH) -I$(CONTAINERS_DIR)/$(STACK)/ $(CPPFLAGS) \
	$(CONTAINERS_DIR)/$(STACK)/$(UNIT_TESTS_DIR)/*.cpp \
	$(GTEST_FLAGS) -o $(STACK)
	$(MOVE) $(STACK) $(BUILD_DIR)

___build_test_vector___ : ___build_dir___
	$(CXX) $(CXX_FLAGS) -I$(TESTING_INCLUDE_PATH) -I$(CONTAINERS_DIR)/$(VECTOR)/ $(CPPFLAGS) \
	$(CONTAINERS_DIR)/$(VECTOR)/$(UNIT_TESTS_DIR)/*.cpp \
	$(GTEST_FLAGS) -o $(VECTOR)
	$(MOVE) $(VECTOR) $(BUILD_DIR)


#TYPOY PLYS CONTEYNER
ARRAY=array
MULTISET=multiset
test : clean test_base ___build_test_array___ ___build_test_multiset___
	./$(BUILD_DIR)$(ARRAY)
	./$(BUILD_DIR)$(MULTISET)


___build_test_array___ : ___build_dir___
	$(CXX) $(CXX_FLAGS) -I$(TESTING_INCLUDE_PATH) -I$(CONTAINERS_DIR)/$(ARRAY)/ $(CPPFLAGS) \
	$(CONTAINERS_DIR)/$(ARRAY)/$(UNIT_TESTS_DIR)/*.cpp \
	$(GTEST_FLAGS) -o $(ARRAY)
	$(MOVE) $(ARRAY) $(BUILD_DIR)

___build_test_multiset___ : ___build_dir___
	$(CXX) $(CXX_FLAGS) -I$(TESTING_INCLUDE_PATH) -I$(CONTAINERS_DIR)/$(MULTISET)/ $(CPPFLAGS) \
	$(CONTAINERS_DIR)/$(MULTISET)/$(UNIT_TESTS_DIR)/*.cpp \
	$(GTEST_FLAGS) -o $(MULTISET)
	$(MOVE) $(MULTISET) $(BUILD_DIR)



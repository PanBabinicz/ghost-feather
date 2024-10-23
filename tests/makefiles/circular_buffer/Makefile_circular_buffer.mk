COMPONENT_NAME=circular_buffer

SRC_FILES = \
  $(PROJECT_SRC_DIR)/shared/data_structure/circular_buffer.c

TEST_SRC_FILES = \
  $(UNITTEST_SRC_DIR)/test_circular_buffer/test_circular_buffer_push.cpp

include $(CPPUTEST_MAKFILE_INFRA)

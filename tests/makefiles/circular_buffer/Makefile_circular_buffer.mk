COMPONENT_NAME=circular_buffer

SRC_FILES = \
  $(PROJECT_SRC_DIR)/shared/data_structure/circular_buffer.c

TEST_SRC_FILES = \
  $(UNITTEST_SRC_DIR)/test_circular_buffer/test_circular_buffer_single_push_pop.cpp \
  $(UNITTEST_SRC_DIR)/test_circular_buffer/test_circular_buffer_clear_single.cpp \
  $(UNITTEST_SRC_DIR)/test_circular_buffer/test_circular_buffer_clear_all.cpp \
  $(UNITTEST_SRC_DIR)/test_circular_buffer/test_circular_buffer_pass_null_element.cpp \
  $(UNITTEST_SRC_DIR)/test_circular_buffer/test_circular_buffer_push_pop_overflow.cpp \

include $(CPPUTEST_MAKFILE_INFRA)

# where the CppUTest includes and *.a are located

# Uncomment the following values depending on which system
# This is obviously better done using `ifeq` and checking the system type

# Linux Values
# CPPUTEST_HOME ?= /usr
# TARGET_PLATFORM ?= x86_64-linux-gnu

# MacOS + Brew Values
CPPUTEST_HOME ?= /opt/homebrew/Cellar/cpputest/4.0
TARGET_PLATFORM ?= 

LD_LIBRARIES = -L$(CPPUTEST_HOME)/$(TARGET_PLATFORM)lib -lCppUTest -lCppUTestExt

TEST_SRC_FILES += \
  $(UNITTEST_SRC_DIR)/AllTests.cpp

UNITTEST_EXTRA_INC_PATHS += \
  -I$(CPPUTEST_HOME)/include \
  -I$(UNITTEST_ROOT)/ \
  -I$(PROJECT_ROOT_DIR)

# Define `INSIDE_UNITTEST` so that our code can do things like `#if INSIDE_UNITTEST`
CPPUTEST_CPPFLAGS += $(UNITTEST_EXTRA_INC_PATHS) \
  -DINSIDE_UNITTEST=1

export SILENCE ?= @

export CPPUTEST_USE_EXTENSIONS=Y
export CPPUTEST_USE_MEM_LEAK_DETECTION=Y
export CPPUTEST_USE_GCOV=Y
# Enable branch coverage reporting
export GCOV_ARGS=-b -c

# These clang warnings aren't particularly helpful
CPPUTEST_WARNINGFLAGS = \
  -Wno-missing-braces \
  -Wno-missing-field-initializers \
  -Wno-packed \
  -Wno-switch-enum \
  -Wno-unused-parameter \
  -Wno-vla

CC_VERSION_OUTPUT ="$(shell $(CXX) -v 2>&1)"
CLANG_STR = clang
ifeq ($(findstring $(CLANG_STR),$(CC_VERSION_OUTPUT)),$(CLANG_STR))
COMPILER_SPECIFIC_WARNINGS += \
  -Wno-c++11-extensions \
  -Wno-c11-extensions \
  -Wno-c99-extensions \
  -Wno-covered-switch-default \
  -Wno-documentation \
  -Wno-documentation-unknown-command \
  -Wno-flexible-array-extensions \
  -Wno-gnu-variable-sized-type-not-at-end \
  -Wno-keyword-macro \
  -Wno-reserved-id-macro \
  -Wno-shorten-64-to-32 \
  -Wno-vla-extension \
  -Wno-suggest-override \
  -Wno-poison-system-directories \
  -Wno-suggest-destructor-override
endif

CPPUTEST_WARNINGFLAGS += $(COMPILER_SPECIFIC_WARNINGS)
export CPPUTEST_WARNINGFLAGS

UNITTEST_RESULT_DIR = $(UNITTEST_BUILD_DIR)/$(COMPONENT_NAME)

export TEST_TARGET = $(UNITTEST_RESULT_DIR)/$(COMPONENT_NAME)_tests
export CPPUTEST_OBJS_DIR = $(UNITTEST_RESULT_DIR)/objs
export CPPUTEST_LIB_DIR = $(UNITTEST_RESULT_DIR)/lib

# Enable color!
export CPPUTEST_EXE_FLAGS = "-c"

# run MakefileWorker.mk with the variables defined here
include MakefileWorker.mk

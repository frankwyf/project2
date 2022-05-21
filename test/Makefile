#We try to detect the OS we are running on, and adjust commands as needed
ifeq ($(OS),Windows_NT)
  ifeq ($(shell uname -s),) # not in a bash-like shell
	CLEANUP = del /F /Q
	MKDIR = mkdir
  else # in a bash-like shell, like msys
	CLEANUP = rm -f
	MKDIR = mkdir -p
  endif
	TARGET_EXTENSION=.exe
else
	CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=.out
endif

C_COMPILER=gcc
ifeq ($(shell uname -s), Darwin)
C_COMPILER=clang
endif

UNITY_ROOT=../unity
SRCs=../

CFLAGS = -Wall -O

#CFLAGS += -Wno-misleading-indentation

TARGET_BASE1=datastructure
TARGET_BASE2=check
TARGET1 = $(TARGET_BASE1)$(TARGET_EXTENSION)
TARGET2 = $(TARGET_BASE2)$(TARGET_EXTENSION)
SRC_FILES1=$(UNITY_ROOT)/src/unity.c ../src/Check.c ../src/GameOfLife.c ../src/Show.c  TestDataStructure.c  test_runners/TestDataStructure_Runner.c
SRC_FILES2=$(UNITY_ROOT)/src/unity.c ../src/Check.c ../src/GameOfLife.c ../src/Show.c TestCheck.c test_runners/TestCheck_Runner.c
INC_DIRS=-I$(SRCs)src -I$(UNITY_ROOT)/src 
LIBS =   -lSDL2 -lSDL2_ttf 

SDLDIR = D:\SDL2

all: clean default

default: $(SRC_FILES1) $(SRC_FILES2)
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES1) -o $(TARGET1) $(LIBS)
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES2) -o $(TARGET2) $(LIBS)
	- ./$(TARGET1)
	- ./$(TARGET2)


test_runners/TestDataStructure_Runner.c: TestDataStructure.c
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb TestDataStructure.c  test_runners/TestDataStructure_Runner.c
test_runners/TestCheck_Runner.c: TestCheck.c
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb TestCheck.c test_runners/TestCheck_Runner.c


clean:
	$(CLEANUP) $(TARGET1) $(TARGET2)


ci: default

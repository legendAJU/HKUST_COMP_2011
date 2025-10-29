CXX := g++
CXXFLAGS := -g -std=c++11 -Wall -Werror=pedantic -pedantic-errors
LDFLAGS :=
TARGET := lab6
SRCS := helper.cpp octopus.cpp main.cpp test.cpp
OBJS := $(SRCS:.cpp=.o)
DEPS := $(SRCS:.cpp=.d)

ifneq ($(OS), Windows_NT)
RM = -rm -f
ifeq ($(shell uname), Linux)
# Enable AddressSanitizer and UndefinedBehaviorSanitizer on Linux
CXXFLAGS += -fsanitize=address,undefined
LDFLAGS += -fsanitize=address,undefined
endif
else
RM = -del /s
endif

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

test: $(TARGET)
	./$(TARGET) 0

-include $(DEPS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

clean:
	$(RM) $(OBJS) $(DEPS) $(TARGET) $(TARGET).exe

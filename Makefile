CXX=g++
CXXFLAGS=-Wall -std=c++11
LIBS=-lcurl

SRCS=downloadhtml.cpp
OBJS=$(SRCS:.cpp=.o)
TARGET=downloadhtml

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

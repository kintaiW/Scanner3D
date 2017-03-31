TARGET = test

#
OBJS = Director.o ProcessImage.o
CXX ?= g++

CXXFLAGS += -c -Wall -std=c++11 -DTEST_PC=1 $(shell pkg-config --cflags opencv) -I/usr/include/opencv2/ -Iinclude/
LDFLAGS += -lpthread $(shell pkg-config --libs --static opencv)

all: $(TARGET)

$(TARGET):$(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $< -o $@ $(CXXFLAGS)


clean: ; rm -f $(TARGET)  $(OBJS) *~ ./include/*~ *.ply *.jpg



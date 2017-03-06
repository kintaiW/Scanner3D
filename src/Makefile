TARGET = test

#
OBJS = main.o Image.o Scanner.o Request.o Scheduler.o PointProcessor.o
CXX ?= g++

CXXFLAGS += -c -Wall -std=c++11 $(shell pkg-config --cflags opencv) -I/usr/include/opencv2/ -Iinclude/
LDFLAGS += -lpthread $(shell pkg-config --libs --static opencv)

all: $(TARGET)

$(TARGET):$(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $< -o $@ $(CXXFLAGS)


clean: ; rm -f $(TARGET)  $(OBJS) *~ ./include/*~ *.ply *.jpg



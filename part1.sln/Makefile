clean:
	-rm ./part1

all:
	-g++ -o ./part1 main1.cpp `pkg-config --cflags opencv4` `pkg-config --libs opencv4` `wx-config --cxxflags` `wx-config --libs` -std=c++0x

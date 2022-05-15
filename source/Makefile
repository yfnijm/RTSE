CXX := g++
CXXFLAGS := -O3 -Wall -shared -std=c++17 -fPIC 
TARGET = _RTSE.*.so

all: $(TARGET)

$(TARGET): _RTSE.cpp Rtree_non_overlapping.hpp
	$(CXX) $(CXXFLAGS) `python3 -m pybind11 --includes` $< -o _RTSE`python3-config --extension-suffix` `python3-config --includes`

test: 
	python3 -m pytest test.py

clean: 
	rm -rf *.o *.so __pycache__ .pytest_cache *.txt *.csv 

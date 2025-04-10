HOME_TREE     := ../../
MODULE_NAME   := $(notdir $(CURDIR))

# Python + Pybind11 headers
PYTHON_INCLUDE       := /home/bo/miniconda3/envs/vln/include/python3.8
PYBIND11_INCLUDE     := /usr/include/pybind11

# Define your code’s source here
CXXSRC = src/main.cpp

CXXFLAGS += -std=c++11 -fPIC -I$(PYTHON_INCLUDE) -I$(PYBIND11_INCLUDE)

# Remove -static (we need a shared library)
LDFLAGS  = -shared

# We can also add any other flags needed from your environment
# e.g., -O3 or -Wall, etc.
CXXFLAGS += -O3

LD_LIBS  = -Xlinker "-(" \
           -lstdc++ -ldl -lz -lrt -lm -lpthread \
           -l$(RPOS_SLAMWARE_NAME) -l$(RPOS_CORE_NAME) \
           -lboost_atomic \
           -lboost_chrono \
           -lboost_date_time \
           -lboost_regex \
           -lboost_system \
           -lboost_thread \
           -lboost_filesystem \
           -lboost_random \
           -lbase64 \
           -ljsoncpp \
           -lrlelib \
           -lcrypto \
           -lcurl \
           -lssl \
           -lcares \
           -Xlinker "-)"

# extension suffix to match python
EXT_SUFFIX := $(shell python3-config --extension-suffix)
TARGET     := slamware_controller$(EXT_SUFFIX)

# This includes your platform’s default definitions & rules
include $(HOME_TREE)/mak_def.inc
include $(HOME_TREE)/mak_common.inc

all: $(TARGET)

$(TARGET): $(CXXSRC)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) $(LD_LIBS) -o $@

clean: clean_app
	rm -f $(TARGET)

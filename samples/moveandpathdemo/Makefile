#/*
# * Copyright (C) 2014  SlamTec
# *
# * This program is free software: you can redistribute it and/or modify
# * it under the terms of the GNU General Public License as published by
# * the Free Software Foundation, either version 3 of the License, or
# * (at your option) any later version.
# *
# * This program is distributed in the hope that it will be useful,
# * but WITHOUT ANY WARRANTY; without even the implied warranty of
# * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# * GNU General Public License for more details.
# *
# * You should have received a copy of the GNU General Public License
# * along with this program.  If not, see <http://www.gnu.org/licenses/>.
# *
# */
#
HOME_TREE := ../../

MODULE_NAME := $(notdir $(CURDIR))

CXXSRC 	   := src/main.cpp
CXXFLAGS   := -std=c++11 -D_GNU_SOURCE -D_DEFAULT_SOURCE -D_XOPEN_SOURCE=700 -DPTHREAD_STACK_MIN=16384
LDFLAGS    := -static

LD_LIBS    =  -Xlinker "-(" \
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
              -Xlinker "-)" \

all: build_app

clean: clean_app

#includes the common definitions...
#do not remove them unless you know what you are doing
include $(HOME_TREE)/mak_def.inc
include $(HOME_TREE)/mak_common.inc


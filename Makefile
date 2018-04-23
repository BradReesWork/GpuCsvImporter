# Copyright (c) 2018, NVIDIA CORPORATION. All rights reserved.
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.


CC=gcc
CPP=g++ -std=c++14
LD=g++

BOOST_LIB=/usr/local/boost_1_67_0/stage/lib

CUDACC=$(CUDA_HOME)/bin/nvcc -std=c++11
CUDA_ARCH=-arch=sm_60
CUDACFLAGS=-m64 -c -O3 --ptxas-options=-v -I./include

INC=-I./include


#CFLAGS=-W -Wall -Wno-unused-function -Wno-unused-parameter -c -O3 -I$(CUDA_HOME)/include ${INC}
CFLAGS=-W -c -O3 -I$(CUDA_HOME)/include ${INC}

LDFLAGS =  -L$(CUDA_HOME)/lib64 -lcudart -L$(BOOST_LIB) -lboost_iostreams


OBJ = \
	src/Main.o \


all: ${OBJ}  Makefile
	${LD} -o bin/csvImport ${OBJ} ${LDFLAGS}

%.o: %.c Makefile
	$(CC) $(CFLAGS) $< -o $@

%.o: %.cpp Makefile
	$(CPP) $(CFLAGS) $< -o $@

%.o: %.cu Makefile
	$(CUDACC) $(CUDACFLAGS) $(CUDA_ARCH) $< -o $@

clean:
	rm -rf src/*.o csvImport

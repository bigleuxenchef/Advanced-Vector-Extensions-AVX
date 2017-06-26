//============================================================================
// Name        : AVX Test.cpp
// Author      : rumi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style, I always like testing technology with Hello worl appraoch, it becomes rapidely more than just hellow world
// anyway this has allowed me pushing my C++ rusty knowledge in action, I know  I could have avoided playing with template but  I love it.
// furthermore the Intel routine for vectorization are not necessarily package the way I like.
// there is one optimization in the code I may do later is to merge the 128 and 256 routines in the same template :-)
//
//============================================================================

#include <iostream>
#include <emmintrin.h> // for _m128
#include <immintrin.h> // for _m256
#include <math.h>
#include <chrono>
#include <typeinfo>
#include "avxtest.h"

using namespace std::chrono;
using namespace std;

int main(int argc, char** argv) {
	if (argc != 2)
		return 1;
	int N = atoi(argv[1]);

	//GlobalTest<float>(N);
	//GlobalTest<double>(N);
	float *a;
	posix_memalign((void**) &a, 64, N * sizeof(float));
	for (int j = 0; j < 100; j++) {
		__init(a, N, 3141592.65358)
		_mm_Test(normal,, add,);
		_mm_print_Test_runtime(normal,, add);
		_mm_print_clock_time(normal,, add);
	}
}


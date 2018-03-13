//============================================================================
// Name        : AVX Test.cpp
// Author      : rumi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style, I always like testing technology with Hello world approach, it becomes rapidly more than just hello world
// anyway this has allowed me pushing my C++ rusty knowledge in action, I know  I could have avoided playing with template but  I love it.
// furthermore the Intel routine for vectorization are not necessarily package the way I like.
// there is one optimization in the code I may do later is to merge the 128 and 256 routines in the same template :-)
//
//============================================================================
// debug options -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize
// compile flag : -mxsave -mavx

#include <iostream>
#include <emmintrin.h> // for _m128
#include <immintrin.h> // for _m256
#include <math.h>
#include <chrono>
#include <typeinfo>
#include "avxtest.h"

using namespace std::chrono;
using namespace std;

template<typename T>
void GlobalTest(int N) {
	T* a;
	cout << "\n\n!!!Hello World OF Advanced Vector Extensions for : "
			<< typeid(T).name() << " sizeof  : " << sizeof(T) << endl << "iteration : " << N << endl;

	auto alloc_start = chrono::high_resolution_clock::now();

	posix_memalign((void**) &a, 64, N * sizeof(T));
	auto alloc_end = chrono::high_resolution_clock::now();

	auto init_start = chrono::high_resolution_clock::now();
	__init(a, N, 3141592.65358)
	auto init_end = chrono::high_resolution_clock::now();
	_mm_Test(normal,, sqrt,)
	__init(a, N, 3141592.65358)
	_mm_Test(sse, 128, sqrt,)
	__init(a, N, 3141592.65358)
	_mm_Test(sse, 256, sqrt,)
	__init(a, N, 3141592.65358)
	_mm_Test(normal,, add,);
	__init(a, N, 3141592.65358)
	_mm_Test(sse, 128, add,);
	__init(a, N, 3141592.65358)
	_mm_Test(sse, 256, add,);
	__init(a, N, 3141592.65358)
	_mm_Test(normal,, sub,);
	__init(a, N, 3141592.65358)
	_mm_Test(sse, 128, sub,);
	__init(a, N, 3141592.65358)
	_mm_Test(sse, 256, sub,);

	__init(a, N, 3141592.65358)
	_mm_Test(normal,, div,);
	__init(a, N, 3141592.65358)

	_mm_Test(sse, 128, div,);
	__init(a, N, 3141592.65358)
	_mm_Test(sse, 256, div,);

	printf("Effective Threads Runtime\n");
	printf("********* SQRT TEST ************\n");
	_mm_print_Test_runtime(normal,, sqrt)
	_mm_print_Test_runtime(sse, 128, sqrt)
	_mm_print_Test_runtime(sse, 256, sqrt)
	printf("********* ADD  TEST ************\n");
	_mm_print_Test_runtime(normal,, add)
	_mm_print_Test_runtime(sse, 128, add)
	_mm_print_Test_runtime(sse, 256, add)

	printf("********* SUB  TEST ************\n");
	_mm_print_Test_runtime(normal,, sub)
	_mm_print_Test_runtime(sse, 128, sub)
	_mm_print_Test_runtime(sse, 256, sub)

	printf("********* DIV  TEST ************\n");
	_mm_print_Test_runtime(normal,, div)
	_mm_print_Test_runtime(sse, 128, div)
	_mm_print_Test_runtime(sse, 256, div)

	printf("\nEffective clock Runtime\n\n");

	printf("Memory %lld.%7lld s\n",
			chrono::duration_cast<chrono::seconds>(alloc_end - alloc_start).count(),
			chrono::duration_cast<chrono::microseconds>(alloc_end - alloc_start).count());
	printf("Init   %lld.%7lld s\n",
			chrono::duration_cast<chrono::seconds>(init_end - init_start).count(),
			chrono::duration_cast<chrono::microseconds>(init_end - init_start).count());
	printf("********* SQRT TEST ************\n");
	_mm_print_clock_time(normal,, sqrt)
	_mm_print_clock_time(sse, 128, sqrt)
	_mm_print_clock_time(sse, 256, sqrt)
	printf("********* ADD  TEST ************\n");
	_mm_print_clock_time(normal,, add)
	_mm_print_clock_time(sse, 128, add)
	_mm_print_clock_time(sse, 256, add)

	printf("********* SUB  TEST ************\n");
	_mm_print_clock_time(normal,, sub)
	_mm_print_clock_time(sse, 128, sub)
	_mm_print_clock_time(sse, 256, sub)

	printf("********* DIV  TEST ************\n");
	_mm_print_clock_time(normal,, div)
	_mm_print_clock_time(sse, 128, div)
	_mm_print_clock_time(sse, 256, div)

}
int main(int argc, char** argv) {
	if (argc != 2)
		return 1;
	int N = atoi(argv[1]);

	GlobalTest<float>(N);
	GlobalTest<double>(N);

}


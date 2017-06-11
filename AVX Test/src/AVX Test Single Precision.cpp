//============================================================================
// Name        : AVX.cpp
// Author      : rumi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <emmintrin.h> // for _m128
#include <immintrin.h> // for _m256
#include <math.h>
#include <chrono>

using namespace std::chrono;
using namespace std;

#define _mm_Test(NAME,INDEX,FUNCTION)\
	auto NAME ## INDEX ## _ ## FUNCTION ## _start = chrono::high_resolution_clock::now();\
	clock_t c_ ## NAME ## INDEX ## _ ## FUNCTION ## _start = clock();\
	{\
		NAME ## INDEX ## _ ## FUNCTION (a, N);\
	}\
	auto NAME ## INDEX ## _ ## FUNCTION ## _end = chrono::high_resolution_clock::now();\
	clock_t c_ ## NAME ## INDEX ## _ ## FUNCTION ## _end = clock();

#define _mm_print_clock_time(NAME,INDEX,FUNCTION)\
printf(# NAME # INDEX " %lld.%7lld s\n",\
			chrono::duration_cast<chrono::seconds>(NAME ## INDEX ## _ ## FUNCTION ##  _end - NAME ## INDEX ## _ ## FUNCTION ##  _start).count(),\
			chrono::duration_cast<chrono::microseconds>(\
					NAME ## INDEX ## _ ## FUNCTION ## _end - NAME ## INDEX ## _ ## FUNCTION ##  _start).count());

#define _mm_print_Test_runtime(NAME,INDEX,FUNCTION)\
printf(# NAME # INDEX "_" # FUNCTION "\t%8.5f s\n",\
				(double) (c_ ## NAME ## INDEX ## _ ## FUNCTION ## _end - c_ ## NAME ## INDEX ## _ ## FUNCTION ## _start) / CLOCKS_PER_SEC);


#define __init(a,N)\
for (int i = 0; i < N; ++i)\
		a[i] = 3141592.65358;

// compile making sure you have support for AVX2 : compiler option -mavx2

void normal_sqrt(float* a, int N) {
/*#pragma nounroll
#pragma clang loop interleave(disable)
#pragma clang loop vectorize(disable)*/
	for (int i = 0; i < N; ++i)
		a[i] = sqrt(a[i]);
}


void normal_add(float* a, int N) {
#pragma nounroll
#pragma clang loop interleave(disable)
#pragma clang loop vectorize(disable)
	for (int i = 0; i < N/2; ++i)
		a[i] = a[i] + a[N/2+i];
}

void sse128_sqrt(float* a, int N) {
	// We assume N % 4 == 0.
	int nb_iters = N / 4;
	__m128* ptr = (__m128*)a;

	for (int i = 0; i < nb_iters; ++i, ++ptr, a += 4)
		_mm_store_ps(a, _mm_sqrt_ps(*ptr));
}

void sse128_add(float* a, int N) {
	// We assume N % 4 == 0.
	int nb_iters = N / 4 / 2;
	__m128* ptr = (__m128*)a;
	__m128* ptr2 = (__m128*) &(a[N/2]);

	for (int i = 0; i < nb_iters; ++i, ++ptr, ++ptr2, a += 8)
		_mm_store_ps(a, _mm_add_ps(*ptr, *ptr2));
}


void sse256_sqrt(float* a, int N) {
	// We assume N % 4 == 0.
	int nb_iters = N / 8;
	__m256* ptr = (__m256*)a;

	for (int i = 0; i < nb_iters; ++i, ++ptr, a += 8)
		_mm256_store_ps(a, _mm256_sqrt_ps(*ptr));
}

void sse256_add(float* a, int N) {
	// We assume N % 4 == 0.
	int nb_iters = N / 8 / 2;
	__m256* ptr = (__m256*)a;
	__m256* ptr2 = (__m256*) &(a[N/2]);

	for (int i = 0; i < nb_iters; ++i, ++ptr,++ptr2, a += 8)
		_mm256_store_ps(a, _mm256_add_ps(*ptr, *ptr2));
}
int main(int argc, char** argv) {
	if (argc != 2)
		return 1;
	int N = atoi(argv[1]);
	cout
			<< "!!!Hello World OF Advanced Vector Extensions : Single Precision Test!!!"
			<< endl;
	float* a;

	auto alloc_start = chrono::high_resolution_clock::now();

	posix_memalign((void**) &a, 64, N * sizeof(float));
	auto alloc_end = chrono::high_resolution_clock::now();


	auto init_start = chrono::high_resolution_clock::now();
	__init(a,N)
	auto init_end = chrono::high_resolution_clock::now();

	_mm_Test(normal,, sqrt)
	__init(a,N)
	_mm_Test(sse, 128, sqrt)
	__init(a,N)
	_mm_Test(sse, 256, sqrt)
	__init(a,N)
	_mm_Test(normal, , add);
	__init(a,N)
	_mm_Test(sse, 128, add);
	__init(a,N)
	_mm_Test(sse, 256, add);

	printf("Effective Threads Runtime\n");
	printf("********* SQRT TEST ************\n");
	_mm_print_Test_runtime(normal,, sqrt)
	_mm_print_Test_runtime(sse, 128, sqrt)
	_mm_print_Test_runtime(sse, 256, sqrt)
	printf("********* ADD  TEST ************\n");
	_mm_print_Test_runtime(normal,, add)
	_mm_print_Test_runtime(sse, 128, add)
	_mm_print_Test_runtime(sse, 256, add)

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

}


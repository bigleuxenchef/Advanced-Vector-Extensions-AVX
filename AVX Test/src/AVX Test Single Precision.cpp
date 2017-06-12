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

using namespace std::chrono;
using namespace std;

#define _mm_Test(NAME,INDEX,FUNCTION,CAST)\
	auto NAME ## INDEX ## _ ## FUNCTION ## _start = chrono::high_resolution_clock::now();\
	clock_t c_ ## NAME ## INDEX ## _ ## FUNCTION ## _start = clock();\
	{\
		NAME ## INDEX ## _ ## FUNCTION ## CAST(a, N);\
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

#define __init(a,N,VALUE)\
for (int i = 0; i < N; ++i)\
		a[i] = VALUE+ i / 10000;

template<typename T, typename U> void mm_store(T t, U u);

template<typename U>
void mm_store(float* f, U u) {
	_mm_store_ps(f, u);
}

template<typename U>
void mm_store(double* d, U u) {
	_mm_store_pd(d, u);
}

template<typename T, typename U> void mm256_store(T t, U u);

template<typename U>
void mm256_store(float* f, U u) {
	_mm256_store_ps(f, u);
}

template<typename U>
void mm256_store(double* d, U u) {
	_mm256_store_pd(d, u);
}

// compile making sure you have support for AVX2 : compiler option -mavx2

template<typename T>
void normal_sqrt(T* a, int N) {
	for (int i = 0; i < N; ++i)
		a[i] = sqrt(a[i]);
}

template<typename T>
void normal_add(T* a, int N) {
	for (int i = 0; i < N / 2; ++i)
		a[i] = a[i] + a[N / 2 + i];
}

template<typename T>
void normal_sub(T* a, int N) {
	for (int i = 0; i < N / 2; ++i)
		a[i] = a[i] - a[N / 2 + i];
}

template<typename T>
void normal_div(T* a, int N) {
	for (int i = 0; i < N / 2; ++i)
		a[i] = a[i] / a[N / 2 + i];
}

template<typename T>
void sse128_sqrt(T* a, int N) {
	// We assume N % 4 == 0.
	int nb_iters = N * sizeof(T) / 16;
	__m128* ptr = (__m128*)a;

	for (int i = 0; i < nb_iters; ++i, ++ptr, a += 16 / sizeof(T))
		mm_store(a,
				std::is_same<float, T>::value ?
						_mm_sqrt_ps(*ptr) : _mm_sqrt_pd(*ptr));
}
template<typename T>
void sse128_add(T* a, int N) {
	// We assume N % 4 == 0.
	int nb_iters = N * sizeof(T) / 16 / 2;
	__m128* ptr = (__m128*)a;
	__m128* ptr2 = (__m128*) &(a[N/2]);

	for (int i = 0; i < nb_iters; ++i, ++ptr, ++ptr2, a += 16 / sizeof(T))
		mm_store(a,
				std::is_same<float, T>::value ?
						_mm_add_ps(*ptr, *ptr2) : _mm_add_pd(*ptr, *ptr2));
}

template<typename T>
void sse128_sub(T* a, int N) {
	// We assume N % 4 == 0.
	int nb_iters = N * sizeof(T) / 16 / 2;
	__m128* ptr = (__m128*)a;
	__m128* ptr2 = (__m128*) &(a[N/2]);

	for (int i = 0; i < nb_iters; ++i, ++ptr, ++ptr2, a += 16 / sizeof(T))
		mm_store(a,
				std::is_same<float, T>::value ?
						_mm_sub_ps(*ptr, *ptr2) : _mm_sub_pd(*ptr, *ptr2));
}

template<typename T>
void sse128_div(T* a, int N) {
	// We assume N % 4 == 0.
	int nb_iters = N * sizeof(T) / 16 / 2;
	__m128* ptr = (__m128*)a;
	__m128* ptr2 = (__m128*) &(a[N/2]);

	for (int i = 0; i < nb_iters; ++i, ++ptr, ++ptr2, a += 16 / sizeof(T))
		mm_store(a,
				std::is_same<float, T>::value ?
						_mm_div_ps(*ptr, *ptr2) : _mm_div_pd(*ptr, *ptr2));
}
template<typename T>
void sse256_sqrt(T* a, int N) {
	// We assume N % 4 == 0.
	int nb_iters = N * sizeof(T) / 32;
	__m256* ptr = (__m256*)a;

	for (int i = 0; i < nb_iters; ++i, ++ptr, a += 32 / sizeof(T))
		mm256_store(a,
				std::is_same<float, T>::value ?
						_mm256_sqrt_ps(*ptr) : _mm256_sqrt_pd(*ptr));
}

template<typename T>
void sse256_add(T* a, int N) {
	// We assume N % 4 == 0.
	int nb_iters = N * sizeof(T) / 32 / 2;
	__m256* ptr = (__m256*)a;
	__m256* ptr2 = (__m256*) &(a[N/2]);

	for (int i = 0; i < nb_iters; ++i, ++ptr, ++ptr2, a += 32 / sizeof(T))
		mm256_store(a,
				std::is_same<float, T>::value ?
						_mm256_add_ps(*ptr, *ptr2) :
						_mm256_add_pd(*ptr, *ptr2));
}

template<typename T>
void sse256_sub(T* a, int N) {
	// We assume N % 4 == 0.
	int nb_iters = N * sizeof(T) / 32 / 2;
	__m256* ptr = (__m256*)a;
	__m256* ptr2 = (__m256*) &(a[N/2]);

	for (int i = 0; i < nb_iters; ++i, ++ptr, ++ptr2, a += 32 / sizeof(T))
		mm256_store(a,
				std::is_same<float, T>::value ?
						_mm256_sub_ps(*ptr, *ptr2) :
						_mm256_sub_pd(*ptr, *ptr2));
}

template<typename T>
void sse256_div(T* a, int N) {
	// We assume N % 4 == 0.
	int nb_iters = N * sizeof(T) / 32 / 2;
	__m256* ptr = (__m256*)a;
	__m256* ptr2 = (__m256*) &(a[N/2]);

	for (int i = 0; i < nb_iters; ++i, ++ptr, ++ptr2, a += 32 / sizeof(T))
		mm256_store(a,
				std::is_same<float, T>::value ?
						_mm256_div_ps(*ptr, *ptr2) :
						_mm256_div_pd(*ptr, *ptr2));
}

template<typename T>
void GlobalTest(int N) {
	T* a;
	cout << "\n\n!!!Hello World OF Advanced Vector Extensions for : "
			<< typeid(T).name() << " sizeof  : " << sizeof(T) << endl;
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


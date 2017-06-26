/*
 * avxtest.h
 *
 *  Created on: Jun 16, 2017
 *      Author: rumi
 */

#ifndef AVXTEST_H_
#define AVXTEST_H_


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
	_mm_store_pd(d, (__m128d ) u);

}

template<typename T, typename U> void mm256_store(T t, U u);

template<typename U>
void mm256_store(float* f, U u) {
	_mm256_store_ps(f, u);
}

template<typename U>
void mm256_store(double* d, U u) {
	_mm256_store_pd(d, (__m256d ) u);
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
#if float == T
				_mm_sqrt_ps((__m128 )*ptr)
#else
				_mm_sqrt_pd((__m128d ) *ptr)
#endif
						);
}
template<typename T>
void sse128_add(T* a, int N) {
	// We assume N % 4 == 0.
	int nb_iters = N * sizeof(T) / 16 / 2;
	__m128* ptr = (__m128*)a;
	__m128* ptr2 = (__m128*) &(a[N/2]);

	for (int i = 0; i < nb_iters; ++i, ++ptr, ++ptr2, a += 16 / sizeof(T))
		mm_store(a,
#if float == T
				_mm_add_ps((__m128 )*ptr, (__m128 )*ptr2)
#else
				_mm_add_pd((__m128d ) *ptr, (__m128d ) *ptr2)
#endif
						);
}

template<typename T>
void sse128_sub(T* a, int N) {
	// We assume N % 4 == 0.
	int nb_iters = N * sizeof(T) / 16 / 2;
	__m128* ptr = (__m128*)a;
	__m128* ptr2 = (__m128*) &(a[N/2]);

	for (int i = 0; i < nb_iters; ++i, ++ptr, ++ptr2, a += 16 / sizeof(T))
		mm_store(a,
#if float == T
				_mm_sub_ps(*ptr, *ptr2)
#else
				_mm_sub_pd((__m128d ) *ptr, (__m128d ) *ptr2)
#endif
						);

}

template<typename T>
void sse128_div(T* a, int N) {
	// We assume N % 4 == 0.
	int nb_iters = N * sizeof(T) / 16 / 2;
	__m128* ptr = (__m128*)a;
	__m128* ptr2 = (__m128*) &(a[N/2]);

	for (int i = 0; i < nb_iters; ++i, ++ptr, ++ptr2, a += 16 / sizeof(T))
		mm_store(a,
#if float == T
				_mm_div_ps(*ptr, *ptr2)
#else
				_mm_div_pd((__m128d ) *ptr, (__m128d ) *ptr2)
#endif
						);
}
template<typename T>
void sse256_sqrt(T* a, int N) {
	// We assume N % 4 == 0.
	int nb_iters = N * sizeof(T) / 32;
	__m256* ptr = (__m256*)a;

	for (int i = 0; i < nb_iters; ++i, ++ptr, a += 32 / sizeof(T))
		mm256_store(a,
#if float == T
				_mm256_sqrt_ps((__m256 )*ptr)
#else
				_mm256_sqrt_pd((__m256d )*ptr)
#endif
				);

}

	template<typename T>
	void sse256_add(T* a, int N) {
		// We assume N % 4 == 0.
		int nb_iters = N * sizeof(T) / 32 / 2;
		__m256* ptr = (__m256*)a;
		__m256* ptr2 = (__m256*) &(a[N/2]);

	for (int i = 0; i < nb_iters; ++i, ++ptr, ++ptr2, a += 32 / sizeof(T))
	mm256_store(a,
#if float == T
			_mm256_add_ps((__m256 )*ptr, (__m256 )*ptr2)
#else
			_mm256_add_pd((__m256d )*ptr, (__m256d )*ptr2)

#endif
	);
}

template<typename T>
void sse256_sub(T* a, int N) {
	// We assume N % 4 == 0.
	int nb_iters = N * sizeof(T) / 32 / 2;
	__m256* ptr = (__m256*)a;
	__m256* ptr2 = (__m256*) &(a[N/2]);

	for (int i = 0; i < nb_iters; ++i, ++ptr, ++ptr2, a += 32 / sizeof(T))
		mm256_store(a,
#if float == T
				_mm256_sub_ps(*ptr, *ptr2)
#else
				_mm256_sub_pd((__m256d ) *ptr, (__m256d ) *ptr2)
#endif
						);
}

template<typename T>
void sse256_div(T* a, int N) {
	// We assume N % 4 == 0.
	int nb_iters = N * sizeof(T) / 32 / 2;
	__m256* ptr = (__m256*)a;
	__m256* ptr2 = (__m256*) &(a[N/2]);

	for (int i = 0; i < nb_iters; ++i, ++ptr, ++ptr2, a += 32 / sizeof(T))
		mm256_store(a,
#if float == T
				_mm256_div_ps(*ptr, *ptr2)
#else
				_mm256_div_pd((__m256d ) *ptr, (__m256d ) *ptr2)
#endif
						);
}




#endif /* AVXTEST_H_ */

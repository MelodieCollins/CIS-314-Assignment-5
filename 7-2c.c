#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct ColorPoint {
	long a;
	long r;
	long g;
	long b;
};

long f(struct ColorPoint **points, int n) {
	long sum = 0;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			sum+= points[j][i].a;
			sum+= points[j][i].r;
			sum+= points[j][i].g;
			sum+= points[j][i].b;

		}
	}
	return sum;
}

long g(struct ColorPoint **points, int n) {
	long sum = 0;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			sum+= points[i][j].a;
			sum+= points[i][j].r;
			sum+= points[i][j].g;
			sum+= points[i][j].b;
		}
	}
	return sum;
}

struct ColorPoint** create2DArray(int n) {
	//array to hold a pointer to the beginning of each row
	struct ColorPoint **points = 
		(struct ColorPoint **)malloc(n * sizeof(struct ColorPoint *));
	for(int i = 0; i < n; i++) {
		//array to hold each row
		points[i] =
			(struct ColorPoint *)malloc(n * sizeof(struct ColorPoint));
		for(int j = 0; j < n; j++) {
			//init the ColorPoint struct
			points[i][j].a = rand();
			points[i][j].r = rand();
			points[i][j].g = rand();
			points[i][j].b = rand();
		}
	}
	return points;
}

void free2DArray(struct ColorPoint** points, int n) {
	for(int i = 0; i < n; i++) {
		free(points[i]);
	}
	free(points);
}

int main() {
	//allocate a 2048 x 2048 array of ColorPoint structs and then measure the time taken to call the f and g functions. Which is faster? Explain.
	int n = 2048;
	struct ColorPoint** array = create2DArray(n);
	clock_t start, end;
	double cpu_time_f, cpu_time_g;
	start = clock();
	printf("result f(): %d\n", f(array, n));
	end = clock();
	cpu_time_f = ((double)(end-start)) / CLOCKS_PER_SEC;
	start = clock();
	printf("result g(): %d\n", g(array, n));
	end = clock();
	cpu_time_g = ((double)(end-start)) / CLOCKS_PER_SEC;

	printf("time f(): %d\n", cpu_time_f); 
	printf("time g(): %d\n", cpu_time_g);

	free2DArray(array, n);
}
/*g() is faster than f() because its cache miss rate is smaller, therefore it finishes faster.*/

//f()
/*[0][0].a cold miss because cache is empty
loads [0][0].r [0][0].g [0][0].b
loads [0][1].a [0][1].r [0][1].g [0][1].b
[0][0].r [0][0].g [0][0].b all hit
since [0][1] loaded and you're trying to access [1][0], [1][0].a is conflict miss
[1][0] now loaded
[1][0].r [1][0].g [1][0].b all hit
6 hits 2 misses
2/(6+2) = 25% miss rate*/

//g()
/*function g can only load 2 at a time, therefore when loading the thir
 * it misses
 * miss rate = misses / (hits + misses) = 4/(28+4)
 * when running g, the cache has a 12.5% miss rate.*/

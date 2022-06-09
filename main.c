/**
* @brief Program for speedtests of parallel version of Gaus solver for systems of linear
equaions.
* This file is of HPC course.
* by @triod315
*
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <omp.h>
#include <iostream>

using namespace std;

/**
* @brief Gaus solver
*
* @param a array with equatios params (including right part of equations).
* @param x allocated array for solution.
* @param n cout of equations in system (count of unknown variables).
* @param core_count count of cores for openmp.
*/
void run_gaus_solver(float ** a, float * x, int n, int core_count)
{
int i, j, k;
float ratio;
omp_set_num_threads(core_count);
double start_time = omp_get_wtime();
// Applying Gauss Elimination
for (i = 0; i < n - 1; i++) {
if (a[i][i] == 0.0) {
printf("Mathematical Error!");
exit(0);
}
#pragma omp parallel for schedule(dynamic) shared (a, x) private (ratio,j,k)
for (j = i + 1; j < n; j++) {
ratio = a[j][i] / a[i][i];
for (k = 0; k < n + 1; k++) {
a[j][k] = a[j][k] - ratio * a[i][k];
}
}
}
// Obtaining Solution by Back Subsitution
x[n-1] = a[n-1][n] / a[n-1][n-1];
for (i = n - 2; i >= 0; i--) {
x[i] = a[i][n];
for (j = i + 1; j < n; j++) {
x[i] = x[i] - a[i][j] * x[j];
}
x[i] = x[i] / a[i][i];
}
double ent_time = omp_get_wtime();
cout << "Elapsed_time: " << ent_time - start_time << " " << core_count << endl;
}
/**
* @brief Reads matrix, which represents system of linear equations.
*
* @param file_name Name of text file.
* @param n cunt of equations.
* @return float** initalized two-dimensional array.
*/
float ** read_matrix_from_file(string file_name, int n)
{
// Declare memory block of size N*(N+1)
float** a = new float*[n];
for (int i = 0; i < n; i++) {
a[i] = new float[n+1];
}
ifstream matrix_file_stream;
matrix_file_stream.open(file_name);

for (int i = 0; i < n; i++) {
for (int j = 0; j < n + 1; j++) {
matrix_file_stream >> a[i][j];
}
}

matrix_file_stream.close();

return a;
}

void print_solution(float * x, int n)
{
for (size_t i = 0; i < n; i++)
{
cout << "x[" << i << "] = " << x[i] << endl;
}
}

int main(int argc, char ** argv)
{
float ratio;
int i, j, k, n;

n = atoi(argv[1]);

string file_name = argv[2];

int core_count = atoi(argv[3]);
int max_core_count = core_count;
if (argc == 5)
max_core_count = atoi(argv[4]);

for (size_t current_core_count = core_count; current_core_count <= max_core_count;
current_core_count++)
{
float * x = new float[n];
float ** a = read_matrix_from_file(file_name, n);
run_gaus_solver(a, x, n, current_core_count);
//print_solution(x, n);
for(int f=0;f<n;f++)
delete[] a[f];
delete [] a;
delete [] x;
}
return(0);
}
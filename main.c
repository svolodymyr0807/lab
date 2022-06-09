#include <mpi.h>
#include <stdio.h>
#define LEN(arr) ((int)(sizeof(arr) / sizeof(arr)[0]))

int main(int argc, char **argv)
{
	int i, j;
	int array[3][3] = {{2, 4, 0}, {-2, 1, 3}, {-1, 0, 1}};
	int n = LEN(array);
	int m = LEN(array[0]);
	int vector[3] = {1, 2, -1};
	int k = LEN(vector);
	int z = 3;
	MPI_Init(NULL, NULL);

	// Get the number of processes
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	// Get the rank of the process
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	if (world_rank == 0)
	{
		//Array
		printf("Кількість процесів: %d \n", world_size);
		printf("Кількість стовпчиків матриці: %d \n", m);
		printf("Кількість рядків матриці: %d \n", n);
		printf("Матриця: \n");
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < m; j++)
			{
				printf("%d ", array[i][j]);
			}
			printf("\n");
		}

		printf("Вектор: \n");
		for (int i = 0; i < k; i++)
		{
			printf("%d ", vector[i]);
		}
		printf("\n");
		printf("Рядків містить 1 процес: %d \n", z);
	}

	int totalresult[k];
	MPI_Bcast(vector, k, MPI_INT, 0, MPI_COMM_WORLD);
	int r = z * m;
	int rbuf[r];
	MPI_Scatter(array, r, MPI_INT, rbuf, r, MPI_INT, 0, MPI_COMM_WORLD);
	int result[z];
	i = 0;
	int e;
	for (e = 0; e < z; e++)
	{
		int b = 0;
		for (int j = 0; j < k; j++)
		{
			b += vector[j] * rbuf[i];
			i += 1;
		}
		result[e] = b;
	}

	MPI_Gather(result, z, MPI_INT, totalresult, z, MPI_INT, 0, MPI_COMM_WORLD);

	if (world_rank == 0)
	{
		printf("Відповідь: \n");
		for (int i = 0; i < k; i++)
		{
			printf("%d \n", totalresult[i]);
		}
	}

	MPI_Finalize();
	return 0;
}
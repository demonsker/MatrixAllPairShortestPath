#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define PATH "C:\\Users\\Eucliwood\\Desktop\\stat(SaveMode)\\Sequential\\"
#define INF 999999
#define SIZE 2048

void distance_generate(int[][SIZE]);
void distance_useexample(int[][SIZE]);
void find_AllPairShortestPath(int[][SIZE], int[][SIZE]);
void array_print(int[][SIZE]);
void array_transpose(int[][SIZE], int[][SIZE]);
void log_save(float);

int main()
{
	clock_t start, end;
	start = clock();

	int i, j;

	//declare distance and path
	int (*distance)[SIZE], (*path)[SIZE];
	distance = (int(*)[SIZE]) malloc(SIZE * sizeof(int[SIZE]));
	path = (int(*)[SIZE]) malloc(SIZE * sizeof(int[SIZE]));

	//Initial Path
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			path[i][j] = j;
		}
	}

	//generate data
	distance_generate(distance);
	//distance_useexample(distance);

	//Find Shortest Path
	find_AllPairShortestPath(distance, path);

	end = clock();

	//Print ShortestDistance
	//printf("Shortest Distance\n");
	//array_print(distance);

	//Print ShortestPath
	//printf("Shortest Path\n");
	//array_print(path);

	//Print Path
	//find_path(path, 1, 7);

	float diff = ((float)(end - start) / 1000000.0F) * 1000;
	printf("%.4f\n", diff);

	log_save(diff);

	getchar();
	return 0;
}

void find_AllPairShortestPath(int distance[][SIZE], int path[][SIZE])
{
	int round = (int)(log10(SIZE) / log10(2));
	int(*temp_distance)[SIZE];
	temp_distance = (int(*)[SIZE]) malloc(SIZE * sizeof(int[SIZE]));
	
	for (int r = 0; r < round; r++)
	{
		//Use inverse copy for row major
		array_transpose(distance, temp_distance);
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				for (int k = 0; k < SIZE; k++)
				{
					//Use inverse (j,k) for row major
					if (distance[i][k] + temp_distance[j][k] < distance[i][j])
					{
						distance[i][j] = distance[i][k] + temp_distance[j][k];
						path[i][j] = path[i][k];
					}
				}
			}
		}
	}
}

void distance_generate(int data[][SIZE])
{
	int i, j, r;

	for (i = 0; i < SIZE; i++)
	{
		data[i][i] = 0;
		for (j = i + 1; j < SIZE; j++)
		{
			r = (rand() % 20) + 1;
			if (r == 19)
				data[i][j] = INF;
			else
				data[i][j] = r;
			data[j][i] = data[i][j];
		}
	}
}

void array_transpose(int sour[][SIZE], int dest[][SIZE])
{
	int i, j;

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			dest[i][j] = sour[j][i];
		}
	}
}

void array_print(int distance[][SIZE])
{
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			if (distance[i][j] == INF)
				printf("%7s", "INF");
			else
				printf("%7d", distance[i][j]);
		}
		printf("\n");
	}
}

void distance_useexample(int data[][SIZE])
{
	int example[8][8] = {
		{ 0,1,9,3,INF,INF,INF,INF },
		{ 1,0,INF,1,INF,3,INF,INF },
		{ 9,INF,0,INF,INF,3,10,INF },
		{ 3,1,INF,0,5,INF,INF,8 },
		{ INF,INF,INF,5,0,2,2,1 },
		{ INF,3,3,INF,2,0,INF,INF },
		{ INF,INF,10,INF,2,INF,0,4 },
		{ INF,INF,INF,8,1,INF,4,0 }
	};

	int i, j;

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			data[i][j] = example[i][j];
		}
	}
}

void find_path(int shortestpath[][SIZE], int u, int v)
{
	if (shortestpath[u][v] == NULL)
		printf("[]");

	printf("[%d]", u);
	while (u != v) {
		u = shortestpath[u][v];
		printf("[%d]", u);
	}
}

void log_save(float diff)
{
	FILE * fp;
	char filePath[70] = PATH;
	char fileName[10];
	sprintf(fileName, "%d.txt", SIZE);
	strcat(filePath, fileName);
	fp = fopen(filePath, "a");
	fprintf(fp, "%.4f\n", diff);
	fclose(fp);
}

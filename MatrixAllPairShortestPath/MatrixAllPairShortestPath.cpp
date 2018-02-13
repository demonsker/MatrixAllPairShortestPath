#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define SIZE 8
#define INF 99999

void findAllPairShortestPath(int **, int **);
void findPath(int **, int, int);
void generate(int **);
void initialize(int **, int **);
void print(int **);
void useExampleData(int **);

int main()
{
	clock_t start1, end1, start2, end2;
	start1 = clock();

	int i, j;

	//distance for gen
	int **distanceGen;
	distanceGen = (int**)malloc(SIZE * sizeof(int*));
	for (i = 0; i < SIZE; i++)
	{
		distanceGen[i] = (int*)malloc(SIZE * sizeof(int));
	}

	end1 = clock();

	//generate data
	//generate(distanceGen);
	useExampleData(distanceGen);

	//Print datagen
	//printf("Generate Distance\n");
	//print(distanceGen);

	start2 = clock();

	//Distance for receiving from distanceGen
	//Path for collect path
	int **distance, **path;
	distance = (int**)malloc(SIZE * sizeof(int*));
	path = (int**)malloc(SIZE * sizeof(int*));
	for (i = 0; i < SIZE; i++)
	{
		distance[i] = (int*)malloc(SIZE * sizeof(int));
		path[i] = (int*)malloc(SIZE * sizeof(int));
	}

	//Initial Path
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			path[i][j] = j;
		}
	}

	//copy datagen to data
	initialize(distanceGen, distance);

	//Find Shortest Path
	findAllPairShortestPath(distance, path);

	end2 = clock();

	//Print ShortestDistance
	//printf("Shortest Distance\n");
	//print(distance);

	//Print ShortestPath
	//printf("Shortest Path\n");
	//print(path);

	//Print Path
	//findPath(path, 1, 7);


	float diff = ((float)(end1 - start1 + end2 - start2) / 1000000.0F) * 1000;
	printf("%.4f\n", diff);

	FILE * fp;
	char filePath[70] = "C:\\Users\\EucliwoodX\\Desktop\\STATS\\Matrix\\stat(SaveMode)\\Sequential\\";
	char fileName[10];
	sprintf(fileName, "%d.txt", SIZE);
	strcat(filePath, fileName);
	fp = fopen(filePath, "a");
	fprintf(fp, "%.4f\n", diff);
	fclose(fp);

	//getchar();
	return 0;
}

void findAllPairShortestPath(int **graph, int **path)
{
	int **tempGraph;
	tempGraph = (int**)malloc(SIZE * sizeof(int*));
	for (int i = 0; i < SIZE; i++)
	{
		tempGraph[i] = (int*)malloc(SIZE * sizeof(int));
	}
	
	for (int r = 0; r < log2(SIZE); r++)
	{
		initialize(graph, tempGraph);
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				for (int k = 0; k < SIZE; k++)
				{
					if (graph[i][k] + tempGraph[k][j] < graph[i][j])
					{
						graph[i][j] = graph[i][k] + tempGraph[k][j];
						path[i][j] = path[i][k];
					}
				}
			}
		}
	}
}

void generate(int **data)
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

void initialize(int **sour, int **dest)
{
	int i, j;

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			dest[j][i] = sour[i][j];
		}
	}
}

void print(int **distance)
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

void useExampleData(int **data)
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

void findPath(int** shortestpath, int u, int v)
{
	if (shortestpath[u][v] == NULL)
		printf("[]");

	printf("[%d]", u);
	while (u != v) {
		u = shortestpath[u][v];
		printf("[%d]", u);
	}
}
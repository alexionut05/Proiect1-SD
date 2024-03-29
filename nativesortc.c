#include <stdio.h>
#include <stdlib.h>

int cmpfnc(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int main(int argv, char **argc)
{
	int n;
	FILE *fin = fopen(argc[1], "r");
	fscanf(fin, "%d", &n);
	int *arr = (int *)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
		fscanf(fin, "%d", &arr[i]);
	fclose(fin);

	qsort(arr, n, sizeof(int), cmpfnc);

	FILE *fout = fopen(argc[2], "w");
	fprintf(fout, "%d\n", n);
	for (int i = 0; i < n; i++)
		fprintf(fout, "%d ", arr[i]);
	fclose(fout);

	free(arr);
	return 0;
}
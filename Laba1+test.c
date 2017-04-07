#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <stdlib.h> 
#include <locale.h>

int k;//отвечает за тип данных
int q;//отвечает за тип операции

struct matrix{
	int n, m, size;
	void* z;
}first, second, result;
struct complex{
	int x, y;
};
void* init(int* n, int* m){
	int i, j;
	void* matrix = malloc(*n**m*first.size);
	for (i = 0; i < *n; i++)
		for (j = 0; j < *m; j++){
			if (k == 1){
				if (n == &first.n) printf("a[%d][%d] = ", i, j);
				else printf("b[%d][%d] = ", i, j);
				scanf("%d", ((int*)matrix + i**m + j));
			}
			else if (k == 2){
				if (n == &first.n) printf("a[%d][%d] = ", i, j);
				else printf("b[%d][%d] = ", i, j);
				scanf("%f", ((float*)matrix + i**m + j));
			}
			else if (k == 3){
				if (n == &first.n){
					printf("a[%d][%d].re = ", i, j);
					scanf("%d", &(((struct complex*)matrix + i**m + j)->x));
					printf("a[%d][%d].im = ", i, j);
					scanf("%d", &(((struct complex*)matrix + i**m + j)->y));
				}
				else {
					printf("b[%d][%d].re = ", i, j);
					scanf("%d", &(((struct complex*)matrix + i**m + j)->x));
					printf("b[%d][%d].im = ", i, j);
					scanf("%d", &(((struct complex*)matrix + i**m + j)->y));
				}
			}
		}
	return matrix;
}
void sumInt(void* a, void* b, int i, int j){
	*((int*)result.z + i*first.m + j) = *((int*)a) + *((int*)b);
}
void sumFloat(void* a, void* b, int i, int j){
	*((float*)result.z + i*first.m + j) = *((float*)a) + *((float*)b);
}
void sumComplex(void* a, void* b, int i, int j){
	((struct complex*)result.z + i*first.m + j)->x = ((struct complex*)a)->x + ((struct complex*)b)->x;
	((struct complex*)result.z + i*first.m + j)->y = ((struct complex*)a)->y + ((struct complex*)b)->y;
}
void universalSum(void* a, void* b, void(*func)(void* a, void* b, int i, int j)){
	int i, j;
	result.z = malloc(first.n*first.m*first.size);
	for (i = 0; i < first.n; i++)
		for (j = 0; j < first.m; j++){
			func((char*)a + (i*first.m + j)*first.size, (char*)b + (i*first.m + j)*first.size, i, j);
		}
}
void multiplyInt(void* a, void* b, int i, int j){
	*((int*)result.z + i*second.m + j) += *((int*)a) * *((int*)b);
}
void multiplyFloat(void* a, void* b, int i, int j){
	*((float*)result.z + i*second.m + j) += *((float*)a) * *((float*)b);
}
void multiplyComplex(void* a, void* b, int i, int j){
	((struct complex*)result.z + i*second.m + j)->x += ((struct complex*)a)->x*((struct complex*)b)->x - ((struct complex*)a)->y*((struct complex*)b)->y;
	((struct complex*)result.z + i*second.m + j)->y += ((struct complex*)a)->x*((struct complex*)b)->y + ((struct complex*)a)->y*((struct complex*)b)->x;
}
void universalMultiply(void* a, void* b, void(*func)(void *a, void *b, int i, int j)){
	int i, j, h;
	result.z = calloc(first.n*second.m, first.size);
	for (i = 0; i < first.n; i++)
		for (j = 0; j < second.m; j++)
			for (h = 0; h < first.m; h++){
				func((char*)a + (i*second.n + h)*first.size, (char*)b + (i*second.n + h)*first.size, i, j);
			}
}
void output(void* a){
	int i, j;
	if (q == 1){
		for (i = 0; i < first.n; i++){
			for (j = 0; j < first.m; j++){
				if (k == 1) printf("%d  ", *((int*)result.z + i*first.m + j));
				else if (k == 2) printf("%f  ", *((float*)result.z + i*first.m + j));
				else if (k == 3) printf("(%d + %d*i)  ", ((struct complex*)result.z + i*first.m + j)->x, ((struct complex*)result.z + i*first.m + j)->y);
			}
			printf("\n");
		}
	}
	if (q == 2){
		for (i = 0; i < first.n; i++){
			for (j = 0; j < second.m; j++){
				if (k == 1) printf("%d  ", *((int*)result.z + i*second.m + j));
				else if (k == 2) printf("%f  ", *((float*)result.z + i*second.m + j));
				else if (k == 3) printf("(%d + %d*i)  ", ((struct complex*)result.z + i*second.m + j)->x, ((struct complex*)result.z + i*second.m + j)->y);
			}
			printf("\n");
		}
	}
}
void test(){
	int i, j;
	first.z = malloc(2 * 3 * first.size);
	second.z = malloc(2 * 3 * first.size);
	first.n = 2;
	first.m = 3;
	if (q == 1){
		if (k == 1){
			for (i = 0; i < first.n; i++)
				for (j = 0; j < first.m; j++){
					*((int*)first.z + i*first.m + j) = i + j;
					*((int*)second.z + i*first.m + j) = 2 * (i + j);
				}
			universalSum(first.z, second.z, sumInt);
			for (i = 0; i < first.n; i++)
				for (j = 0; j < first.m; j++)
					if (*((int*)result.z + i*first.m + j) != 3 * (i + j)) printf("Error \n");
		}
		else if (k == 2){
			for (i = 0; i < first.n; i++)
				for (j = 0; j < first.m; j++){
					*((float*)first.z + i*first.m + j) = i + j;
					*((float*)second.z + i*first.m + j) = 2 * (i + j);
				}
			universalSum(first.z, second.z, sumFloat);
			for (i = 0; i < first.n; i++)
				for (j = 0; j < first.m; j++)
					if (*((float*)result.z + i*first.m + j) != 3 * (i + j)) printf("Error \n");
		}
		else if (k == 3){
			for (i = 0; i < first.n; i++)
				for (j = 0; j < first.m; j++){
					((struct complex*)first.z + i*first.m + j)->x = ((struct complex*)first.z + i*first.m + j)->y = i + j;
					((struct complex*)second.z + i*first.m + j)->x = ((struct complex*)second.z + i*first.m + j)->y = 2 * (i + j);
				}
			universalSum(first.z, second.z, sumComplex);
			for (i = 0; i < first.n; i++)
				for (j = 0; j < first.m; j++){
					if (((struct complex*)result.z + i*first.m + j)->x != 3 * (i + j)) printf("Error\n");
					if (((struct complex*)result.z + i*first.m + j)->y != 3 * (i + j)) printf("Error\n");
				}
		}
	}
	if (q == 2){
		second.n = 3;
		second.m = 2;
		if (k == 1){
			for (i = 0; i < first.n; i++)
				for (j = 0; j < first.m; j++)
					*((int*)first.z + i*first.m + j) = 8;
			for (i = 0; i < second.n; i++)
				for (j = 0; j < second.m; j++)
					*((int*)second.z + i*second.m + j) = 2;
			universalMultiply(first.z, second.z, multiplyInt);
			for (i = 0; i < first.n; i++)
				for (j = 0; j < second.m; j++)
					if (*((int*)result.z + i*second.m + j) != 48) printf("Error \n");
		}
		else if (k == 2){
			for (i = 0; i < first.n; i++)
				for (j = 0; j < first.m; j++)
					*((float*)first.z + i*first.m + j) = 8;
			for (i = 0; i < second.n; i++)
				for (j = 0; j < second.m; j++)
					*((float*)second.z + i*second.m + j) = 2;
			universalMultiply(first.z, second.z, multiplyFloat);
			for (i = 0; i < first.n; i++)
				for (j = 0; j < second.m; j++)
					if (*((float*)result.z + i*second.m + j) != 48) printf("Error\n");
		}
		else if (k == 3){
			for (i = 0; i < first.n; i++)
				for (j = 0; j < first.m; j++)
					((struct complex*)first.z + i*first.m + j)->x = ((struct complex*)first.z + i*first.m + j)->y = 2;
			for (i = 0; i < second.n; i++)
				for (j = 0; j < second.m; j++)
					((struct complex*)second.z + i*second.m + j)->x = ((struct complex*)second.z + i*second.m + j)->y = 2;
			universalMultiply(first.z, second.z, multiplyComplex);
			for (i = 0; i < first.n; i++)
				for (j = 0; j < second.m; j++){
					if (((struct complex*)result.z + i*second.m + j)->x != 0) printf("Error\n");
					if (((struct complex*)result.z + i*second.m + j)->y != 24) printf("Error\n");
				}
		}
	}

}
int main(){
	setlocale(LC_ALL, "Rus");
	int p;
	printf("Введите 1 для целых, 2 для вещественных, 3 для комплексных\n");
	scanf("%d", &k);
	if (k == 1) first.size = sizeof(int);
	else if (k == 2) first.size = sizeof(float);
	else if (k == 3) first.size = sizeof(struct complex);
	printf("Введите 1 для сложения, 2 для умножения\n");
	scanf("%d", &q);
	printf("Хотите выполнить тест? (Yes-1 or No-2)\n");
	scanf("%d", &p);
	if (p == 1){
		test();
	}
	else if (p == 2){
		printf("Введите кол-во строк и столбцов первой матрицы\n");
		scanf("%d %d", &first.n, &first.m);
		printf("Введите кол-во строк и столбцов второй матрицы\n");
		scanf("%d %d", &second.n, &second.m);
		if (q == 1){
			if (first.n == second.n && first.m == second.m){
				first.z = init(&first.n, &first.m);
				second.z = init(&second.n, &second.m);
				if (k == 1) universalSum(first.z, second.z, sumInt);
				else if (k == 2) universalSum(first.z, second.z, sumFloat);
				else if (k == 3) universalSum(first.z, second.z, sumComplex);
				output(result.z);
			}
			else printf("Матрицы невозможно сложить\n");
		}
		else if (q == 2){
			if (first.m == second.n){
				first.z = init(&first.n, &first.m);
				second.z = init(&second.n, &second.m);
				if (k == 1) universalMultiply(first.z, second.z, multiplyInt);
				else if (k == 2) universalMultiply(first.z, second.z, multiplyFloat);
				else if (k == 3) universalMultiply(first.z, second.z, multiplyComplex);
				output(result.z);
			}
			else printf("Матрицы невозможно умножить\n");
		}
	}
	free(first.z);
	free(second.z);
	free(result.z);
	system("PAUSE");
}
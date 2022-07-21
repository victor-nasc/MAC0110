/* 
Victor Nascimento Ribeiro
nUSP: 12513949
*/

#include <stdio.h>
#define MAX 100

int main(){
	int a[MAX], b[MAX];
	int m, n;
	int i, j;

	printf("Digite m e n: ");
	scanf("%d %d", &m, &n);

	printf("Digite a primeira sequencia: ");
	for(i = 0; i < m; i++)
		scanf("%d", &a[i]);

	printf("Digite a segunda sequencia: ");
	for(i = 0; i < n; i++)
		scanf("%d", &b[i]);

	printf("Sequencia ordenada com numeros de ambas, sem repeticao: \n");
	i = j = 0;
	while(i < m && j < n){
		if(a[i] < b[j]){
			printf("%d ", a[i]);
			i++;
		}
		else if(a[i] > b[j]){
			printf("%d ", b[j]);
			j++;
		}
		else{
			printf("%d ", a[i]);
			i++;
			j++;
		}
	}

	/* um dos vetores terminou mas o outro nao */
	while(i < m){
		printf("%d ", a[i]);
		i++;
	}
	while(j < n){
		printf("%d ", b[j]);
		j++;
	}

	printf("\n");
	return 0;
}
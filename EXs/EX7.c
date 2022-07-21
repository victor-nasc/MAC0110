/* 
Victor Nascimento Ribeiro
nUSP: 12513949
*/

#include <stdio.h>
#define MAX 100

int main(){
	int A[MAX][MAX];
	int n,
		i, j,
		total,
		sum1, sum2,
		magico = 1;
	
	printf("Digite n: ");
	scanf("%d", &n);

	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			scanf("%d", &A[i][j]);

	/* diagonal principal */
	total = 0;
	for(i = 0; i < n; i++)
		total += A[i][i];
	
	/* diagonal secundaria */
	sum1 = 0;
	for(i = 0; i < n; i++)
		sum1 += A[i][n-1 - i];

	if(total != sum1) magico = 0;

	/* linhas(sum1) e colunas(sum2) */
	for(i = 0; i < n && magico; i++){
		sum1 = 0;
		sum2 = 0;
		for(j = 0; j < n; j++){
			sum1 += A[i][j];
			sum2 += A[j][i];
		}
		if(total != sum1 || total != sum2) 
			magico = 0;
	}

	if(magico) printf("Eh um quadrado magico\n");
	else printf("NAO eh um quadrado magico\n");

	return 0;
}
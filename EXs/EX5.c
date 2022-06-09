/* 
Victor Nascimento Ribeiro
nUSP: 12513949
*/

#include <stdio.h>

int main(){
	double x, eps;
	double fat = 1;
	double termo = 1;
	double soma = 1;

	printf("Digite x: ");
	scanf("%lf", &x);
	printf("Digite eps: ");
	scanf("%lf", &eps);

	while(termo >= eps || termo <= -eps){
		termo = termo * (x / fat);
		soma = soma + termo;
		fat++;
	}

	printf("Aproximacao: %lf\n", soma);

	return 0;
}
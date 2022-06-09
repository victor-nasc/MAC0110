/* 
Victor Nascimento Ribeiro
nUSP: 12513949
*/

#include <stdio.h>

int contadigitos(int, int);

int main(){
	int a, b;
	int permutacao = 1;

	printf("Digite a: ");
	scanf("%d", &a);
	printf("Digite b: ");
	scanf("%d", &b);

	for(int i = 1; i <= 9 && permutacao; i++)
		if(contadigitos(a, i) != contadigitos(b, i))
			permutacao = 0;
	
	if(permutacao)
		printf("%d eh permutacao de %d\n", a, b);
	else
		printf("%d NAO eh permutacao de %d\n", a, b);
	
	return 0;
}

int contadigitos(int n, int d){
	int qt = 0;

	for(int i = n; i > 0; i /= 10)
		if(i % 10 == d)
			qt++;

	return qt;
}
/*
EX2 - MAC110
Victor Nascimento Ribeiro
nUSP: 12513849
*/

#include <stdio.h>

int main(){
	int n, num;
	int max = 0;

	scanf("%d", &n);

	if(n > 0)
		scanf("%d", &max);

	n--;
	
	while(n > 0){
		scanf("%d", &num);
		if(num > max)
			max = num;
		n--;
	}

	printf("O maior numero da sequencia e %d \n", max);

	return 0;
}
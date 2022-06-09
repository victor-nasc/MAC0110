/*
 Victor Nascimento Ribeiro
 nUSP: 12513849
*/

#include <stdio.h>

int main(){
	int n, qt, i;
	
	scanf("%d", &n);
	
	for(i = 2; n > 0; i++){
		qt = 0;
		while(n % i == 0){
			n = n / i;
			qt++;
		}
		if(qt > 0)
			printf("fator %d multiplicidade %d \n", i, qt);
		}
		
	return 0;
}
		

/*
 Victor Nascimento Ribeiro
 nUSP: 12513849
*/

#include <stdio.h>

int main(){
    int n, aux, inv = 0;

    printf("Digite n: ");
    scanf("%d", &n);

    for(aux = n; aux > 0; aux /= 10)
        inv = inv * 10 + aux % 10;

    if(inv == n) 
        printf("%d eh palindromo\n", n);
    else
        printf("%d nao eh palindromo\n", n);

    return 0;
}
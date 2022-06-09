/* 
EP1 - MAC110
Victor Nascimento Ribeiro
nUSP: 12513849
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
	int num,					 /* numero sorteado */
		dig,					 /* digito da tentativa */
		d1, d2, d3,				 /* digitos de num separados */
		certo1, certo2, certo3,  /* armazena se o digito foi acertado */
		opc = 0,				 /* opcao */
		qt = 0,					 /* quantidade de jogos jogados */	
		wins = 0,				 /* quantidade de vitorias */
		dep = 0,				 /* modo depuracao */
		tentativas,				 /* quantidade de tentativas */
		vitoria;				 /* armazena se ganhou ou perdeu a rodada */
	
    printf("  Bem-vindo ao JOGO da FORCA !!\n");
    printf("  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    while(opc != 3){
		printf("\n");
		if(dep == 0)
			printf("[ depuracao = DESLIGADO / jogos jogados = %d ]\n", qt);
		else 
			printf("[ depuracao = LIGADO    / jogos jogados = %d ]\n", qt);
		printf("  1. Continuar a jogar\n");
		printf("  2. Alternar modo depuracao e continuar a jogar\n");
		printf("  3. Parar\n");
		
		printf("Escolha uma opcao: ");
		scanf("%d", &opc);
		printf("\n");

		if(opc != 3){
			num = rand() % 1000;
			/* separa os digitos de num */
			d3 = num % 10;
			num = num / 10;
			d2 = num % 10;
			d1 = num / 10;
			vitoria	= 0;
			certo1 = certo2 = certo3 = 0;

			/* muda o modo de depuracao */
			if(opc == 2) dep = (dep + 1) % 2;

			if(dep == 1)
				printf("Numero a ser adivinhado: %d %d %d\n", d1, d2, d3);
			
			for(tentativas = 6; !vitoria && tentativas > 0; tentativas--){
				if(tentativas > 1)
					printf("Restam %d tentativas\n", tentativas);
				else
					printf("Resta uma tentativa!\n");

				printf("Sua proxima tentativa (digito de 0 a 9): ");
				scanf("%d", &dig);

				if(dig == d1) certo1 = 1;
				if(dig == d2) certo2 = 1;
				if(dig == d3) certo3 = 1;

				printf("Voce ja acertou os seguintes digitos: ");

				if(certo1) printf("%d ", d1);
				else printf("_ ");
				if(certo2) printf("%d ", d2);
				else printf("_ ");
				if(certo3) printf("%d \n", d3);
				else printf("_ \n");
				printf("\n");

				if(certo1 && certo2 && certo3){
					vitoria = 1;
					wins++;
				}
			}
			if(vitoria) printf("Voce VENCEU!\n");
			else printf("Voce PERDEU!\n");
			qt++;
		}
	}
    
    printf("Voce jogou %d jogos e venceu %d vezes!\n", qt, wins);
    
    return 0;
}
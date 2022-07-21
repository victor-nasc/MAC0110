/* 
EP3 - MAC110
Victor Nascimento Ribeiro
nUSP: 12513849
*/

#include <stdio.h>
#include <stdlib.h>

int *load_image_from_file(char *, int *, int *);
void save_image_to_file(char *, int *, int, int);
int *invert_image(int *, int, int);
int *binarize(int *, int, int, int);
int *filter_image(int *, int, int, int, int);
int *aumenta_matriz(int *, int, int, int);
int *vetor_vizinhos(int *, int *, int, int, int, int);
void ordena(int *, int);
int *contorno(int *, int, int);
int *label_components(int *, int, int, int *);
void dfs(int *, int *, int, int, int, int);


int main(){
    char filename[100];     /* nome do arquivo                                      */
    char opc;               /* opcao                                                */
    int *I = NULL;          /* matriz imagem                                        */
    int *R = NULL;          /* matriz resultado                                     */
    int w, h;               /* largura e altura                                     */
    int t;                  /* limiar                                               */
    int tipo_f, tam_f;      /* tipo e tamanho filtro                                */
    int ncc;                /* numero de componentes conexos                        */
    int modificou;          /* variavel booleana que representa se modificou ou nao */
    int i;

    do{

        printf("----------------------------------------------\n");
        printf("Escolha uma opção\n");
        printf("  Q. Quit\n");
        printf("  L. Ler um arquivo\n");
        printf("  S. Salvar imagem em arquivo\n");
        printf("  M. Manter entrada anterior\n");
        printf("\n");
        printf("  B. Binarizar a imagem\n");
        printf("  C. Contorno da imagem\n");
        printf("  I. Inverter a imagem\n");
        printf("  F. Filtrar a imagem\n");
        printf("  R. Rotular os componentes conexos\n");
        printf(" ==> ");
    
        scanf(" %c", &opc); 
        printf("\n");

        
        if(opc == 'l' || opc == 'L'){
            
            printf(" ==> Digite o nome do arquivo de entrada: ");
            scanf("%s", filename);

            free(R); R = NULL;
            free(I); I = NULL;

            I = load_image_from_file(filename, &w, &h);

            if(I == NULL){
                printf(" ** Nao consegui abrir o arquivo %s\n", filename);
                return 0;
            }

            printf(" ** Tamanho da imagem: %d x %d\n", w, h);           

            modificou = 0;
        }


        else if(opc == 's' || opc == 'S'){
            
            printf(" ==> Digite o nome do arquivo de saída: ");
            scanf("%s", filename);

            if(modificou) save_image_to_file(filename, R, w, h);
            else save_image_to_file(filename, I, w, h);

            printf(" ** Imagem gravada no arquivo %s\n", filename);

        }
    

        else if(opc == 'm' || opc == 'M'){

            free(R); R = NULL;

            modificou = 0;
        }
        

        /* se a opcao nao for S, L ou M copia R para I */
        if(modificou){
            free(I);
            I = R;
            R = NULL;

            modificou = 0;
        }
        

        if(opc == 'b' || opc == 'B'){

            printf(" ==> Digite o limiar: ");
            scanf("%d", &t);

            R = binarize(I, w, h, t);

            printf(" ** Imagem foi binarizada\n");

            modificou = 1;
        }


        else if(opc == 'c' || opc == 'C'){

            R = contorno(I, w, h);
            
            printf(" ** Contorno foi calculado\n");
            
            modificou = 1;
        }


        else if(opc == 'i' || opc == 'I'){

            R = invert_image(I, w, h);

            printf(" ** Imagem foi invertida\n");
            
            modificou = 1;
        }
            

        else if(opc == 'f' || opc == 'F'){

            printf(" ==> Digite o tipo do filtro: ");
            scanf("%d", &tipo_f);
            printf(" ==> Digite o tamanho do filtro: ");
            scanf("%d", &tam_f);

            R = filter_image(I, w, h, tam_f, tipo_f);

            printf(" ** Imagem foi filtrada\n");
            
            modificou = 1;
        }


        else if(opc == 'r' || opc == 'R'){
            
            R = label_components(I, w, h, &ncc);

            printf(" ** Imagem foi rotulada\n");
            printf(" ** Número de componentes conexos: %d\n", ncc);
            
            if(ncc <= 127)
                for(i = 0; i < w*h; i++)
                    R[i] = R[i] * 255/ncc;

            modificou = 1;
        }

        printf("\n");

    } while(opc != 'q');


    free(I); I = NULL;
    free(R); R = NULL;
    
    return 0;
}



int *load_image_from_file(char *filename, int *w, int *h){
    FILE *arq;
    char line[100];
    int i;
    int *I;
    int tam;

    arq = fopen(filename, "r");

    /* erro na abertura do arquivo */
    if(arq == NULL) return NULL;            
    
    fscanf(arq, "%[^\n]\n", line);
    fscanf(arq, "%d %d\n", w, h);
    fscanf(arq, " %[^\n]\n", line);

    tam = (*w) * (*h);
    I = malloc(tam * sizeof(int));

    for(i = 0; i < tam; i++)
        fscanf(arq, "%d", &I[i]);

    fclose(arq);
    return I;
}


void save_image_to_file(char *filename, int *I, int w, int h){
    FILE *arq;
    int i, j;

    arq = fopen(filename, "w");

    fprintf(arq, "P2\n");
    fprintf(arq, "%d %d\n", w, h);
    fprintf(arq, "255\n");

    for(i = 0; i < h; i++){
        for(j = 0; j < w; j++)
            fprintf(arq, "%d ", I[i*w + j]);
        fprintf(arq, "\n");
    }

    fclose(arq);
}


int *invert_image(int *I, int w, int h){
    int i;
    int *R = malloc(w * h * sizeof(int));

    for(i = 0; i < w*h; i++)
        R[i] = 255 - I[i];

    return R;
}


int *binarize(int *I, int w, int h, int t){
    int i;
    int *R = malloc(w * h * sizeof(int));

    for(i = 0; i < w*h; i++){
        if(I[i] >= t) R[i] = 255;
        else R[i] = 0;
    }
        
    return R;
}


int *contorno(int *I, int w, int h){
    int i;
    int *R = filter_image(I, w, h, 3, 1);

    for(i = 0; i < w*h; i++)
        R[i] = I[i] - R[i];   

    return R;
}


int *filter_image(int *I, int w, int h, int d, int tipo){
    int i, j;
    int *aux;                                    /* matriz aumentada (auxiliar)  */
    int tam_v = d * d;                           /* quantidade de vizinhos       */
    int *v = malloc(tam_v * sizeof(int));        /* vetor que guarda os vizinhos */
    int *R = malloc(w * h * sizeof(int)); 


    d /= 2; /* tamanho da margem em cada um dos lados */
    aux = aumenta_matriz(I, w, h, d);

    for(i = 0; i < h; i++)
        for(j = 0; j < w; j++){
            v = vetor_vizinhos(v, aux, d, i+d, j+d, w + 2*d);
            ordena(v, tam_v);

            if(tipo == 1)
                R[i*w + j] = v[0];
            else if(tipo == 2)
                R[i*w + j] = v[tam_v / 2]; 
            else 
                R[i*w + j] = v[tam_v - 1];

        }

    free(aux); aux = NULL;
    free(v); v = NULL;
    return R;
}


int *aumenta_matriz(int *I, int w, int h, int d){
    int i, j;
    /* proporcoes da matriz aumentada */
    int h_aux = h + 2*d;
    int w_aux = w + 2*d;
    int *aux = malloc(w_aux * h_aux * sizeof(int));


    /* copia os elementos de I na parte central de aux */
    for(i = 0; i < h; i++)
        for(j = 0; j < w; j++)
            aux[(i+d)*w_aux + j + d] = I[i*w + j];
    
    for(i = 0; i < d; i++){
        /* copia as bordas de I nas bordas de aux */
        for(j = 0; j < d; j++){
            aux[i*w_aux + j] = I[0];                        /* esquerda cima   */
            aux[i*w_aux + j + w + d] = I[w - 1];            /* direita cima    */
            aux[(i+h+d)*w_aux + j] = I[w*h - w];            /* esquerda baixo  */
            aux[(i+h+d)*w_aux + j + w + d] = I[w*h - 1];    /* direita baixo   */
        }

        /* copia a primeira e ultima linhas de I em aux */
        for(j = 0; j < w; j++){
            aux[i*w_aux + j + d] = I[j];                    /* linha cima      */
            aux[(i+h+d)*w_aux + j + d] = I[w*h - w + j];    /* linha baixo     */
        } 

        /* copia a primeira e ultima coluda de I em aux */
        for(j = 0; j < h; j++){
            aux[(j+d)*w_aux + i] = I[j*w];                  /* coluna esquerda */
            aux[(j+d)*w_aux + i + w + d] = I[j*w + w - 1];  /* coluna direita  */
        }
    }

    return aux;
}


/* devolve um vetor contendo os vizinhos de uma matriz a partir da posicao (lin,col) */
int *vetor_vizinhos(int *v, int *aux, int d, int lin, int col, int w_aux){
    int i, j;
    int k = 0;

    for(i = lin-d; i <= lin+d; i++)
        for(j = col-d; j <= col+d; j++){
            v[k] = aux[i*w_aux + j];
            k++;
        }

    return v;
}


/* ordena um vetor usando Insertion Sort */
void ordena(int *v, int n){
    int i, j, x;
    
    for(i = 1; i < n; i++){
        x = v[i]; 
        for (j = i - 1; j >= 0 && v[j] > x; j--)
            v[j+1] = v[j];
        v[j+1] = x;
    }
}


int *label_components(int *I, int w, int h, int *ncc){
    int i, j;
    int ind = 1;
    int *R = malloc(w * h * sizeof(int));

    for(i = 0; i < w*h; i++)
        R[i] = 0;

    /* para cada posicao da matriz */
    for(i = 0; i < h; i++)
        for(j = 0; j < w; j++)
            /* se a posicao nao eh um fundo e ainda nao foi rotulado(visitado) */
            if(I[i*w + j] == 255 && R[i*w + j] == 0){
                dfs(I, R, i*w + j, ind, w, h);
                ind++;
            }

    *ncc = ind-1;
    return R;
}

/* faz uma busca em profundidade a partir da posicao (lin,col)
   e rotula todos os componentes conexos */
void dfs(int *I, int *R, int atu, int ind, int w, int h){
    int i, j; 
    int lin, col;
    int tam = 1;                               /* tamanho da pilha  */
    int *stack = malloc(w * h * sizeof(int));  /* pilha de posicoes */
    
    stack[0] = atu;

    /* enquanto a pilha nao estiver vazia */
    while(tam > 0){
        /* desempilha e pega o topo da pilha */
        tam--;
        lin = stack[tam] / w; /* (i*w + j) / w = i */
        col = stack[tam] % w; /* (i*w + j) % w = j */
        
        /* olha os vizinhos da posicao (lin,col) */
        for(i = lin-1; i <= lin+1; i++)
            for(j = col-1; j <= col+1; j++)
                /* se eh uma posicao valida, nao eh um fundo e nao foi rotulado(visitado) */
                if(i >= 0 && j >= 0 && i < h && j < w && I[i*w + j] == 255 && R[i*w+j] == 0){
                    R[i*w + j] = ind;
                    /* empilha */
                    stack[tam] = i*w + j;
                    tam++;
                }
    }
    
    free(stack); 
    stack = NULL;
}
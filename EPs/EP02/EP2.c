/* 
EP2 - MAC110
Victor Nascimento Ribeiro
nUSP: 12513849
*/

#include <stdio.h>
#define PI 3.14159
#define RAIO_AP 200
#define RAIO_ZA 2000 
#define DELTA_ALARME 60
#define EPS_COS 0.000001 
#define EPS 0.01 

int localiza(double, double, double, double, double, double, double, double, double, double *, double *);
int intercepta(double, double, double, double, double *, double *);
int iguais(double, double);
double velocidade(double, double, double, double, double);
double cosseno(double, double);
double raiz(double, double);

/* troca 3 numeros */
void troca(double *, double *, double *, double *, double *, double *);


int main(){
    /* leitura do arquivo */
    FILE *arq_entrada;
    char filename[256];
    
    int n;                        /* numero de casos a serem analisados */
    int veic;                     /* numero do veiculo */
    int id1, id2, id3;            /* id da posicao */
    int localizou;                /* se foi possivel e quais torres localizou */
    
    /* coordenadas (x,y), H, angulo theta e distancia das antenas ate o veiculo */
    double xi, yi, hi, thi, div;
    double xj, yj, hj, thj, djv;
    double xk, yk, hk, thk, dkv;

    double xv0, yv0, xv1, yv1;    /* coordenadas (x,y) do veiculo */
    double x, y;                  /* coordenadas do ponto de interseccao */
    double deltaT;                /* intervalo de tempo */
    double VM;                    /* velocidade media */
    double dist;                  /* distancia */


    printf("Programa-demo para o Sistema de Monitoramento\n");
    printf("\n\n\n");

    printf("Digite o nome do arquivo com os dados a serem processados ");
    scanf("%s", filename);
    
    arq_entrada = fopen(filename, "r");
    
    if (arq_entrada == NULL) {
        printf("Nao consegui abrir o arquivo %s.\n", filename);
        return 0;
    }
    
    fscanf(arq_entrada, "%d", &n);
    printf("Numero de casos a serem analisados: %d\n", n);
    
    while(n > 0){
        printf("\n\n\n");
        fscanf(arq_entrada, "%d", &veic);
        printf("IDENTIFICACAO: veiculo %d\n", veic);
        printf("\n");

        /* posicao previa das antenas */
        fscanf(arq_entrada, "%d %lf %lf %lf %lf", &id1, &xi, &yi, &hi, &thi);
        fscanf(arq_entrada, "%d %lf %lf %lf %lf", &id2, &xj, &yj, &hj, &thj);
        fscanf(arq_entrada, "%d %lf %lf %lf %lf", &id3, &xk, &yk, &hk, &thk);
        
        /* distancia da antena ate veiculo */
        div = hi * cosseno(thi, EPS_COS);
        djv = hj * cosseno(thj, EPS_COS);
        dkv = hk * cosseno(thk, EPS_COS);
        
        printf("Antenas na posicao previa\n");
        printf(" id | posicao | H (m) | theta (graus) | distancia (m)\n");
        printf("%3d | (%8.2f,%8.2f) | %8.2f | %8.2f | %8.2f\n", id1, xi, yi, hi, thi, div);
        printf("%3d | (%8.2f,%8.2f) | %8.2f | %8.2f | %8.2f\n", id2, xj, yj, hj, thj, djv);
        printf("%3d | (%8.2f,%8.2f) | %8.2f | %8.2f | %8.2f\n", id3, xk, yk, hk, thk, dkv);
        printf("\n");
        
        fscanf(arq_entrada, "%lf", &deltaT);
        localizou = 0;
        
        if(localiza(xi, yi, div, xj, yj, djv, xk, yk, dkv, &xv0, &yv0)){
            printf("Localizacao previa: (%8.2f,%8.2f)\n", xv0, yv0);
            printf("\n");
            printf("Intervalo de tempo: %4.2f segundos\n", deltaT);
            printf("\n");
            localizou = 1;
        }
        
        /* posicao atual das antenas */
        fscanf(arq_entrada, "%d %lf %lf %lf %lf", &id1, &xi, &yi, &hi, &thi);
        fscanf(arq_entrada, "%d %lf %lf %lf %lf", &id2, &xj, &yj, &hj, &thj);
        fscanf(arq_entrada, "%d %lf %lf %lf %lf", &id3, &xk, &yk, &hk, &thk);
        
        /* distancia da antena ate veiculo */
        div = hi * cosseno(thi, EPS_COS);
        djv = hj * cosseno(thj, EPS_COS);
        dkv = hk * cosseno(thk, EPS_COS);
        
        if(localizou == 1){
            printf("Antenas na posicao atual\n");
            printf(" id | posicao | H (m) | theta (graus) | distancia (m)\n");
            printf("%3d | (%8.2f,%8.2f) | %8.2f | %8.2f | %8.2f\n", id1, xi, yi, hi, thi, div);
            printf("%3d | (%8.2f,%8.2f) | %8.2f | %8.2f | %8.2f\n", id2, xj, yj, hj, thj, djv);
            printf("%3d | (%8.2f,%8.2f) | %8.2f | %8.2f | %8.2f\n", id3, xk, yk, hk, thk, dkv);
            printf("\n");
            
            if(localiza(xi, yi, div, xj, yj, djv, xk, yk, dkv, &xv1, &yv1)){
                VM = velocidade(xv0, yv0, xv1, yv1, deltaT);
                dist = raiz((xv1 - xv0)*(xv1 - xv0) + (yv1 - yv0)*(yv1 - yv0), EPS);
                printf("Localizacao atual: (%8.2f,%8.2f)\n", xv1, yv1);
                printf("\n");
                printf("Distancia percorrida: %.2f m\n", dist);
                printf("Velocidade: %.2f m/s\n", VM);
                printf("\n");
                localizou = 2;
            } 
            else{
                printf("Nao foi possivel calcular a localizacao atual do veiculo %d.\n", veic);
                printf("\n");
                printf("Nao foi possivel determinar a situacao do veiculo %d\n", veic);
            }
        }
        else{
            printf("Nao foi possivel calcular a localizacao inicial do veiculo %d.\n", veic);
            printf("\n");
            printf("Nao foi possivel determinar a situacao do veiculo %d\n", veic);
        }
        
        if(localizou == 2){
            dist = raiz(xv1*xv1 + yv1*yv1, EPS);
            printf("Distancia da origem: %.2f\n", dist);
            
            if(iguais(VM, 0.0)) printf("Veiculo estacionado ");
            else printf("Veiculo em movimento ");
            
            if(dist > RAIO_ZA) printf("FORA da zona de alerta\n");
                
            else if(dist <= RAIO_AP){
                printf("na AP\n");
                printf("\n");
                printf("*************************************\n");
                printf("  ALARME, ALARME, ALARME, ALARME !!  \n");
                printf("       Veiculo esta na AP !          \n");
                printf("*************************************\n");
            }
            
            else{ /* ameaca */
                printf("na ZONA DE ALERTA\n");
                printf("\n");

                if(intercepta(xv0, yv0, xv1, yv1, &x, &y)){
                    dist = raiz((xv1-x)*(xv1-x) + (yv1-y)*(yv1-y), EPS);
                    printf("Trajetoria INTERCEPTARA AP\n");
                    printf("Distancia atual a AP e' de %.2f metros\n", dist);
                    printf("Interseccao ocorrera em %.2f segundos,\n", dist / VM);
                    printf("na coordenada (%8.2f,%8.2f)\n", x, y);
                    
                    if(dist / VM <= DELTA_ALARME){
                        printf("\n");
                        printf("*************************************\n");
                        printf("  ALARME, ALARME, ALARME, ALARME !!  \n");
                        printf("      Invasao iminente !             \n");
                        printf("*************************************\n");
                    }
                }
                else if(!iguais(VM, 0.0))
                    printf("Trajetoria NAO INTERCEPTARA AP\n");
            }
        }
        printf("\n");
        n--;
    }

    fclose(arq_entrada);
    return 0;
}


int localiza(double xi, double yi, double div, double xj, double yj, double djv, double xk, double yk, double dkv, double *xv, double *yv){
    double pik, pij, qij, qik;

    /* evitar divisao por zero */
    if(iguais(xi,xj)) 
        troca(&xi, &yi, &div, &xk, &yk, &dkv); /* i <--> k */
    else if(iguais(xi,xk))
        troca(&xi, &yi, &div, &xj, &yj, &djv); /* i <--> j */
    
    /* torres colineares */
    if(iguais(xi,xj)) return 0;

    /* calcula xv e yv */
    pik = (xi*xi - xj*xj + yi*yi - yj*yj - div*div + djv*djv) / (2 * (xi-xj));
    pij = (xi*xi - xk*xk + yi*yi - yk*yk - div*div + dkv*dkv) / (2 * (xi-xk));
    qij = (yj - yi) / (xi - xj);
    qik = (yk - yi) / (xi - xk);
    *yv = -1 * (pik - pij) / (qij-qik);
    *xv = 0.5 * (pij + pik + (qij + qik) * (*yv));

    return 1;
}

int intercepta(double x0, double y0, double x1, double y1, double *x, double *y){
    double delta;         
    double a, b, c;          /* coeficientes da eq da reta */
    double xa, xb, ya, yb;   /* pontos de interseccao */

    /* d(atual,origem) < d(anterior,origem) => se aproximando de AP */
    if(raiz(x1*x1 + y1*y1, EPS) < raiz(x0*x0 + y0*y0, EPS)){
        a = y0 - y1;
        b = x1 - x0;
        c = x0*y1 - x1*y0;
        
        if(!iguais(x1, x0)){
            /* equacao do 2*grau */
            delta = (2*a*c)/(b*b) * (2*a*c)/(b*b) - 4*((a*a)/(b*b)+1) * ((c*c)/(b*b) - RAIO_AP*RAIO_AP);
            if(delta >= 0){
                xa = (-1*(2*a*c)/(b*b) + raiz(delta, EPS)) / (2 * ((a*a)/(b*b)+1));
                xb = (-1*(2*a*c)/(b*b) - raiz(delta, EPS)) / (2 * ((a*a)/(b*b)+1));
                ya = raiz(RAIO_AP*RAIO_AP - xa*xa, EPS);
                yb = raiz(RAIO_AP*RAIO_AP - xb*xb, EPS);
            }
            else return 0;  /* reta externa a circunferencia */ 
        }
        else{
            if(x1 > RAIO_AP || x1 < -RAIO_AP) return 0; /* reta externa a circunferencia */
            xa = xb = -c/a;
            ya = raiz(RAIO_AP * RAIO_AP - (c/a * c/a), EPS);
            yb = -ya;
        }

        /* seleciona a interseccao mais perto do carro */
        /* delta == 0 tem xa == xb e ya == yb, entao selecionar a ou b nao tem diferenca */
        if(raiz((xa-x1)*(xa-x1) + (ya-y1)*(ya-y1), EPS) < raiz((xb-x1)*(xb-x1) + (yb-y1)*(yb-y1), EPS)){
            *x = xa;
            *y = ya;
        }
        else{
            *x = xb;
            *y = yb;
        }

        return 1;
    }

    return 0;
}

int iguais(double x, double y){
    if(x-y < EPS && y-x < EPS) 
        return 1;
    else 
        return 0;
}

double velocidade(double x0, double y0, double x1, double y1, double deltaT){
    double deltaX, deltaY, deltaS;

    deltaX = x1 - x0;
    deltaY = y1 - y0;
    deltaS = raiz(deltaX*deltaX + deltaY*deltaY, EPS);

    return deltaS/deltaT;
}

double cosseno(double theta, double epsilon){
    double termo = 1;
    double res = 1;
    double x = theta * PI / 180.0; /* graus -> radiano */
    int i;
    
    for(i = 1; termo >= epsilon || termo <= -epsilon; i++){
        termo *= -1 * x * x / (2 * i * (2 * i-1));
        res += termo;
    }

    return res;
}

double raiz(double x, double epsilon){
    double ant;
    double raiz = x;
    
    if(iguais(x, 0.0)) return 0.0;

    do{
        ant = raiz;
        raiz = 0.5 * (ant + (x / ant));
    } while(ant - raiz >= epsilon);

    return raiz;
}

void troca(double *x1, double *y1, double *d1, double *x2, double *y2, double *d2){
    double aux;
    /* troca x */
    aux = *x1;
    *x1 = *x2;
    *x2 = aux;
    /* troca y */
    aux = *y1;
    *y1 = *y2;
    *y2 = aux;
    /* troca d */
    aux = *d1;
    *d1 = *d2;
    *d2 = aux;
}
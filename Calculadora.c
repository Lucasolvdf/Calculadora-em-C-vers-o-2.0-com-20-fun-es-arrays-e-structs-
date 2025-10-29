#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_HIST 50

typedef struct {
    char tipo[20];
    double a, b;
    double resultado;
    int id;
} Operacao;

Operacao historico[MAX_HIST];
int contadorOperacoes = 0;

// FUNÇÕES BÁSICAS
double soma(double a, double b) { return a + b; }
double subtracao(double a, double b) { return a - b; }
double multiplicacao(double a, double b) { return a * b; }
double divisao(double a, double b, int *erro) {
    if (b == 0) { *erro = 1; return 0; }
    *erro = 0; return a / b;
}

// FUNÇÕES AVANÇADAS
double potencia(double base, double expoente) { return pow(base, expoente); }
double raizQuadrada(double n, int *erro) {
    if (n < 0) { *erro = 1; return 0; }
    *erro = 0; return sqrt(n);
}
double fatorial(int n, int *erro) {
    if (n < 0 || n > 20) { *erro = 1; return 0; }
    *erro = 0;
    double r = 1; for (int i = 1; i <= n; i++) r *= i;
    return r;
}
double logaritmo(double n, int *erro) {
    if (n <= 0) { *erro = 1; return 0; }
    *erro = 0; return log10(n);
}
double seno(double ang) { return sin(ang); }
double cosseno(double ang) { return cos(ang); }
double tangente(double ang) { return tan(ang); }

// FUNÇÕES ESTATÍSTICAS
double media(double arr[], int n) {
    double soma = 0; for (int i = 0; i < n; i++) soma += arr[i];
    return soma / n;
}
double mediana(double arr[], int n) {
    double temp[n]; memcpy(temp, arr, n * sizeof(double));
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (temp[j] > temp[j + 1]) {
                double t = temp[j]; temp[j] = temp[j + 1]; temp[j + 1] = t;
            }
    return (n % 2 == 0) ? (temp[n/2 - 1] + temp[n/2]) / 2 : temp[n/2];
}
double desvioPadrao(double arr[], int n) {
    double m = media(arr, n), soma = 0;
    for (int i = 0; i < n; i++) soma += pow(arr[i] - m, 2);
    return sqrt(soma / n);
}
double maximo(double arr[], int n) {
    double max = arr[0]; for (int i = 1; i < n; i++) if (arr[i] > max) max = arr[i];
    return max;
}
double minimo(double arr[], int n) {
    double min = arr[0]; for (int i = 1; i < n; i++) if (arr[i] < min) min = arr[i];
    return min;
}
int mdc(int a, int b) { while (b != 0) { int t = b; b = a % b; a = t; } return a; }
int mmc(int a, int b) { return abs(a * b) / mdc(a, b); }

// FUNÇÕES DE MATRIZES
void lerMatriz(double M[3][3], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            printf("[%d][%d]: ", i, j);
            scanf("%lf", &M[i][j]);
        }
}
void imprimirMatriz(double M[3][3], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%8.2lf ", M[i][j]);
        printf("\n");
    }
}
void somaMatrizes(double A[3][3], double B[3][3], double R[3][3], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            R[i][j] = A[i][j] + B[i][j];
}
void multiplicaMatrizes(double A[3][3], double B[3][3], double R[3][3], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            R[i][j] = 0;
            for (int k = 0; k < n; k++)
                R[i][j] += A[i][k] * B[k][j];
        }
}

// HISTÓRICO
void adicionarOperacao(char tipo[], double a, double b, double resultado) {
    if (contadorOperacoes >= MAX_HIST) return;
    historico[contadorOperacoes].id = contadorOperacoes + 1;
    strcpy(historico[contadorOperacoes].tipo, tipo);
    historico[contadorOperacoes].a = a;
    historico[contadorOperacoes].b = b;
    historico[contadorOperacoes].resultado = resultado;
    contadorOperacoes++;
}
void exibirHistorico() {
    printf("\n=== HISTÓRICO DE OPERAÇÕES ===\n");
    if (contadorOperacoes == 0) { printf("Nenhuma operação registrada.\n"); return; }
    for (int i = 0; i < contadorOperacoes; i++)
        printf("[%d] %s (%.2lf, %.2lf) = %.2lf\n",
               historico[i].id, historico[i].tipo,
               historico[i].a, historico[i].b,
               historico[i].resultado);
}
void salvarHistoricoEmArquivo() {
    FILE *f = fopen("historico.csv", "w");
    if (!f) { printf("Erro ao criar arquivo.\n"); return; }
    fprintf(f, "ID,Tipo,A,B,Resultado\n");
    for (int i = 0; i < contadorOperacoes; i++)
        fprintf(f, "%d,%s,%.2lf,%.2lf,%.2lf\n",
                historico[i].id,
                historico[i].tipo,
                historico[i].a,
                historico[i].b,
                historico[i].resultado);
    fclose(f);
    printf("Histórico salvo em 'historico.csv'\n");
}

// LIMPAR HISTÓRICO
void limparHistorico() {
    contadorOperacoes = 0;
    printf("Histórico limpo com sucesso!\n");
}

// ENTRADA
double lerDouble() { double n; printf("Digite um número: "); scanf("%lf", &n); return n; }
int lerInteiroPositivo() { int n; do { printf("Digite um inteiro positivo: "); scanf("%d", &n); } while (n <= 0); return n; }

// MENU
int main() {
    int opcao, erro;
    double a, b, resultado;

    do {
        printf("\n==== CALCULADORA MODULAR ====\n");
        printf(" 1. Soma\n 2. Subtração\n 3. Multiplicação\n 4. Divisão\n");
        printf(" 5. Potência\n 6. Raiz Quadrada\n 7. Fatorial\n 8. Logaritmo\n");
        printf(" 9. Seno\n10. Cosseno\n11. Tangente\n12. Média\n13. Mediana\n14. Desvio Padrão\n");
        printf("15. Máximo\n16. Mínimo\n17. MDC\n18. MMC\n19. Matrizes (2x2 ou 3x3)\n");
        printf("20. Histórico\n21. Salvar Histórico\n22. Limpar Histórico\n 0. Sair\nEscolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: a=lerDouble(); b=lerDouble(); resultado=soma(a,b); adicionarOperacao("Soma",a,b,resultado); printf("Resultado=%.2lf\n",resultado); break;
            case 2: a=lerDouble(); b=lerDouble(); resultado=subtracao(a,b); adicionarOperacao("Subtração",a,b,resultado); printf("Resultado=%.2lf\n",resultado); break;
            case 3: a=lerDouble(); b=lerDouble(); resultado=multiplicacao(a,b); adicionarOperacao("Multiplicação",a,b,resultado); printf("Resultado=%.2lf\n",resultado); break;
            case 4: a=lerDouble(); b=lerDouble(); resultado=divisao(a,b,&erro); if(erro) printf("Erro: divisão por zero!\n"); else { adicionarOperacao("Divisão",a,b,resultado); printf("Resultado=%.2lf\n",resultado); } break;
            case 5: a=lerDouble(); b=lerDouble(); resultado=potencia(a,b); adicionarOperacao("Potência",a,b,resultado); printf("Resultado=%.2lf\n",resultado); break;
            case 6: a=lerDouble(); resultado=raizQuadrada(a,&erro); if(erro) printf("Erro: raiz de número negativo!\n"); else { adicionarOperacao("Raiz",a,0,resultado); printf("Resultado=%.2lf\n",resultado); } break;
            case 7: { int n=lerInteiroPositivo(); resultado=fatorial(n,&erro); if(erro) printf("Erro: inválido!\n"); else { adicionarOperacao("Fatorial",n,0,resultado); printf("Resultado=%.0lf\n",resultado); } break; }
            case 8: a=lerDouble(); resultado=logaritmo(a,&erro); if(erro) printf("Erro: log<=0!\n"); else { adicionarOperacao("Log",a,0,resultado); printf("Resultado=%.2lf\n",resultado); } break;
            case 9: a=lerDouble(); resultado=seno(a); adicionarOperacao("Seno",a,0,resultado); printf("Resultado=%.4lf\n",resultado); break;
            case 10: a=lerDouble(); resultado=cosseno(a); adicionarOperacao("Cosseno",a,0,resultado); printf("Resultado=%.4lf\n",resultado); break;
            case 11: a=lerDouble(); resultado=tangente(a); adicionarOperacao("Tangente",a,0,resultado); printf("Resultado=%.4lf\n",resultado); break;
            case 12: {
                int n; printf("Quantos números? "); scanf("%d",&n);
                double arr[n];
                for(int i=0;i<n;i++){ printf("Valor %d: ",i+1); scanf("%lf",&arr[i]); }
                resultado=media(arr,n);
                adicionarOperacao("Média",n,0,resultado);
                printf("Resultado=%.2lf\n",resultado);
                break;
            }
            case 13: {
                int n; printf("Quantos números? "); scanf("%d",&n);
                double arr[n];
                for(int i=0;i<n;i++){ printf("Valor %d: ",i+1); scanf("%lf",&arr[i]); }
                resultado=mediana(arr,n);
                adicionarOperacao("Mediana",n,0,resultado);
                printf("Resultado=%.2lf\n",resultado);
                break;
            }
            case 14: {
                int n; printf("Quantos números? "); scanf("%d",&n);
                double arr[n];
                for(int i=0;i<n;i++){ printf("Valor %d: ",i+1); scanf("%lf",&arr[i]); }
                resultado=desvioPadrao(arr,n);
                adicionarOperacao("Desvio",n,0,resultado);
                printf("Resultado=%.2lf\n",resultado);
                break;
            }
            case 15: {
                int n; printf("Quantos números? "); scanf("%d",&n);
                double arr[n];
                for(int i=0;i<n;i++){ printf("Valor %d: ",i+1); scanf("%lf",&arr[i]); }
                resultado=maximo(arr,n);
                adicionarOperacao("Máximo",n,0,resultado);
                printf("Resultado=%.2lf\n",resultado);
                break;
            }
            case 16: {
                int n; printf("Quantos números? "); scanf("%d",&n);
                double arr[n];
                for(int i=0;i<n;i++){ printf("Valor %d: ",i+1); scanf("%lf",&arr[i]); }
                resultado=minimo(arr,n);
                adicionarOperacao("Mínimo",n,0,resultado);
                printf("Resultado=%.2lf\n",resultado);
                break;
            }
            case 17: a=lerDouble(); b=lerDouble(); resultado=mdc((int)a,(int)b); adicionarOperacao("MDC",a,b,resultado); printf("Resultado=%.0lf\n",resultado); break;
            case 18: a=lerDouble(); b=lerDouble(); resultado=mmc((int)a,(int)b); adicionarOperacao("MMC",a,b,resultado); printf("Resultado=%.0lf\n",resultado); break;
            case 19: {
                int n; do { printf("Qual o tamanho da matriz (2 ou 3)? "); scanf("%d",&n); } while(n<2 || n>3);
                double A[3][3], B[3][3], R[3][3];
                printf("Matriz A:\n"); lerMatriz(A,n);
                printf("Matriz B:\n"); lerMatriz(B,n);
                somaMatrizes(A,B,R,n);
                printf("Soma das matrizes:\n"); imprimirMatriz(R,n);
                multiplicaMatrizes(A,B,R,n);
                printf("Multiplicação das matrizes:\n"); imprimirMatriz(R,n);
                break;
            }
            case 20: exibirHistorico(); break;
            case 21: salvarHistoricoEmArquivo(); break;
            case 22: limparHistorico(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n"); break;
        }

    } while(opcao != 0);

    return 0;
}

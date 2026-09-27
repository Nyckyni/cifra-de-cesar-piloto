# cifra-de-cesar-piloto
codificação de cifra de ceasar 
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Verifica se a palavra possui somente letras
int palavraValida(char palavra[]) {

    for (int i = 0; i < strlen(palavra); i++) {

        if (palavra[i] < 'a' || palavra[i] > 'z') {
            return 0;
        }
    }

    return 1;
}


// Verifica se um número é primo
int ehPrimo(int numero) {

    if (numero < 2) {
        return 0;
    }

    for (int i = 2; i * i <= numero; i++) {

        if (numero % i == 0) {
            return 0;
        }
    }

    return 1;
}


// Retorna o termo da sequência escolhida
long long calcularSequencia(int tipo, int posicao, int inicio, int razao) {

    // PA
    if (tipo == 1) {

        return inicio + (posicao * razao);
    }

    // PG
    else if (tipo == 2) {

        long long resultado = inicio;

        for (int i = 0; i < posicao; i++) {
            resultado *= razao;
        }

        return resultado;
    }

    // Fibonacci
    else if (tipo == 3) {

        if (posicao == 0 || posicao == 1) {
            return 1;
        }

        long long a = 1;
        long long b = 1;
        long long c;

        for (int i = 2; i <= posicao; i++) {

            c = a + b;
            a = b;
            b = c;
        }

        return b;
    }

    // Números primos
    else if (tipo == 4) {

        int contador = 0;
        int numero = 2;

        while (1) {

            if (ehPrimo(numero)) {

                if (contador == posicao) {
                    return numero;
                }

                contador++;
            }

            numero++;
        }
    }

    return 0;
}


int main() {

    char palavra[16];
    char criptografada[16];

    int shift;
    int tipo;

    int inicio = 1;
    int razao = 1;

    printf("=====================================\n");
    printf("       SISTEMA DE CRIPTOGRAFIA\n");
    printf("=====================================\n\n");

    // Entrada da palavra
    printf("Digite a palavra secreta: ");
    scanf("%15s", palavra);

    // Verificação da palavra
    if (strlen(palavra) > 15) {

        printf("\nErro: a palavra deve ter no maximo 15 letras.\n");

        return 1;
    }

    if (!palavraValida(palavra)) {

        printf("\nErro: use somente letras minusculas, sem acentos.\n");

        return 1;
    }


    // Entrada do SHIFT
    printf("Digite o valor do SHIFT: ");
    scanf("%d", &shift);


    // Escolha da sequência
    printf("\nEscolha a sequencia numerica:\n");

    printf("1 - Progressao Aritmetica (PA)\n");
    printf("2 - Progressao Geometrica (PG)\n");
    printf("3 - Fibonacci\n");
    printf("4 - Numeros Primos\n");

    printf("\nDigite sua escolha: ");
    scanf("%d", &tipo);


    // Verifica escolha
    if (tipo < 1 || tipo > 4) {

        printf("\nErro: opcao de sequencia invalida.\n");

        return 1;
    }


    // Configura PA
    if (tipo == 1) {

        printf("\nDigite o primeiro termo da PA: ");
        scanf("%d", &inicio);

        printf("Digite a razao da PA: ");
        scanf("%d", &razao);
    }


    // Configura PG
    if (tipo == 2) {

        printf("\nDigite o primeiro termo da PG: ");
        scanf("%d", &inicio);

        printf("Digite a razao da PG: ");
        scanf("%d", &razao);
    }


    // Criptografia
    for (int i = 0; i < strlen(palavra); i++) {

        // Calcula o valor da sequência
        long long valorSequencia =
            calcularSequencia(tipo, i, inicio, razao);

        // Primeira camada + segunda camada
        long long deslocamento =
            shift + valorSequencia;

        // Converte a letra para uma posição de 0 a 25
        int posicao = palavra[i] - 'a';

        // Aplica o deslocamento
        posicao = (posicao + deslocamento) % 26;

        // Converte novamente para letra
        criptografada[i] = posicao + 'a';
    }


    // Final da string
    criptografada[strlen(palavra)] = '\0';


    // Mostra resultado
    printf("\n=====================================\n");
    printf("          RESULTADO\n");
    printf("=====================================\n");

    printf("Palavra original: %s\n", palavra);
    printf("SHIFT: %d\n", shift);
    printf("Palavra criptografada: %s\n", criptografada);


    // Criação do arquivo
    FILE *arquivo;

    arquivo = fopen("resultado_criptografia.txt", "w");


    if (arquivo == NULL) {

        printf("\nErro ao criar o arquivo.\n");

        return 1;
    }


    // Grava informações no arquivo
    fprintf(arquivo, "=====================================\n");
    fprintf(arquivo, "      RESULTADO DA CRIPTOGRAFIA\n");
    fprintf(arquivo, "=====================================\n");

    fprintf(arquivo, "Palavra original: %s\n", palavra);
    fprintf(arquivo, "Palavra codificada: %s\n", criptografada);
    fprintf(arquivo, "SHIFT: %d\n", shift);
    fprintf(arquivo, "Tipo de sequencia: %d\n", tipo);
    fprintf(arquivo, "Quantidade de letras: %d\n",
            (int)strlen(palavra));

    fclose(arquivo);


    printf("\nArquivo 'resultado_criptografia.txt' criado com sucesso!\n");

    return 0;
}

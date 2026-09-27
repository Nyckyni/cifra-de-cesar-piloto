#include <stdio.h>
#include <string.h>

// Verifica se a palavra possui somente letras
int palavraValida(char palavra[]) {

    size_t tamanhoPalavra = strlen(palavra);

    for (size_t i = 0; i < tamanhoPalavra; i++) {

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
    char entrada[256];
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

    if (scanf("%255s", entrada) != 1) {
        return 1;
    }

    if (strlen(entrada) > 15) {

        printf("\nErro: a palavra deve ter no maximo 15 letras.\n");

        return 1;
    }

    strcpy(palavra, entrada);

    // Verificação da palavra
    if (!palavraValida(palavra)) {

        printf("\nErro: use somente letras minusculas, sem acentos.\n");

        return 1;
    }


    // Entrada do SHIFT
    printf("Digite o valor do SHIFT: ");

    if (scanf("%d", &shift) != 1) {

        printf("\nErro: entrada numerica invalida.\n");

        return 1;
    }


    // Escolha da sequência
    printf("\nEscolha a sequencia numerica:\n");

    printf("1 - Progressao Aritmetica (PA)\n");
    printf("2 - Progressao Geometrica (PG)\n");
    printf("3 - Fibonacci\n");
    printf("4 - Numeros Primos\n");

    printf("\nDigite sua escolha: ");

    if (scanf("%d", &tipo) != 1) {

        printf("\nErro: entrada numerica invalida.\n");

        return 1;
    }


    // Verifica escolha
    if (tipo < 1 || tipo > 4) {

        printf("\nErro: opcao de sequencia invalida.\n");

        return 1;
    }


    // Configura PA
    if (tipo == 1) {

        printf("\nDigite o primeiro termo da PA: ");
        if (scanf("%d", &inicio) != 1) {

            printf("\nErro: entrada numerica invalida.\n");

            return 1;
        }

        printf("Digite a razao da PA: ");
        if (scanf("%d", &razao) != 1) {

            printf("\nErro: entrada numerica invalida.\n");

            return 1;
        }
    }


    // Configura PG
    if (tipo == 2) {

        printf("\nDigite o primeiro termo da PG: ");
        if (scanf("%d", &inicio) != 1) {

            printf("\nErro: entrada numerica invalida.\n");

            return 1;
        }

        printf("Digite a razao da PG: ");
        if (scanf("%d", &razao) != 1) {

            printf("\nErro: entrada numerica invalida.\n");

            return 1;
        }
    }


    // Criptografia
    size_t tamanhoPalavra = strlen(palavra);

    for (size_t i = 0; i < tamanhoPalavra; i++) {

        // Calcula o valor da sequência
        long long valorSequencia =
            calcularSequencia(tipo, (int)i, inicio, razao);

        // Primeira camada + segunda camada
        long long deslocamento =
            shift + valorSequencia;

        // Converte a letra para uma posição de 0 a 25
        int posicao = palavra[i] - 'a';

        // Aplica o deslocamento
        posicao = (int)(((posicao + deslocamento) % 26 + 26) % 26);

        // Converte novamente para letra
        criptografada[i] = posicao + 'a';
    }


    // Final da string
    criptografada[tamanhoPalavra] = '\0';


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

        printf("\nAviso: nao foi possivel criar o arquivo de resultado.\n");

        return 0;
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

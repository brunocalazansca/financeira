#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dados{
    float salario;
    float despesa;
    float credito;
    char nome[50];
    char cpf[15];
    char identidade[10];
};

void logo(){
    printf("   ______            ____  ___   _____ ___ \n");
    printf("  / ____/           / __ \\/   | / ___//   |\n");
    printf(" / /      ______   / /_/ / /| | \\__ \\/ /| |\n");
    printf("/ /___   /_____/  / _, _/ ___ |___/ / ___ |\n");
    printf("\\____/           /_/ |_/_/  |_|____/_/  |_|\n");
}

void pause() {
    printf("Pressione Enter para continuar...");
    getchar();
}

void cabecalho(){
    printf("+--------------------------------------------------------+\n");
    printf("+                                                        +\n");
    printf("+        Bem-Vindo a sua analise de credito!             +\n");
    printf("+                                                        +\n");
    printf("+--------------------------------------------------------+\n");
}
void cabecalhoDados(){
    printf("+--------------------------------------------------------+\n");
    printf("+                                                        +\n");
    printf("+           Preencha o que se pede a seguir!             +\n");
    printf("+                                                        +\n");
    printf("+--------------------------------------------------------+\n");
}
void dadosPessoais(){
    printf("+--------------------------------------------------------+\n");
    printf("+                                                        +\n");
    printf("+             Insira os seus dados abaixo!               +\n");
    printf("+                                                        +\n");
    printf("+--------------------------------------------------------+\n");
}

void dadosFinanceiro() {
    printf("+--------------------------------------------------------+\n");
    printf("+                                                        +\n");
    printf("+              Insira o seu os seus dados                +\n");
    printf("+                 financeiros abaixo!                    +\n");
    printf("+                                                        +\n");
    printf("+--------------------------------------------------------+\n");
}

void analiseCredito() {
    printf("+--------------------------------------------------------+\n");
    printf("+                                                        +\n");
    printf("+                 Analise de Credito!                    +\n");
    printf("+                                                        +\n");
    printf("+--------------------------------------------------------+\n");
}

void imprimirPositivo(struct dados* pessoa, int tamanho){
    for (int i = 0; i < tamanho; i++){
        if (pessoa[i].credito >= 0) {
            printf("Nome: %s\n", pessoa[i].nome);
            printf("Valor do Credito: %.2f\n", pessoa[i].credito);
            printf("\n");
        }
    }
}

void imprimirNegativo(struct dados* pessoa, int tamanho){
    for (int i = 0; i < tamanho; i++){
        if (pessoa[i].credito < 0) {
            printf("Nome: %s\n", pessoa[i].nome);
            printf("Valor do Credito: %.2f\n", pessoa[i].credito);
            printf("\n");
        }
    }
}

void salvarCSV(struct dados pessoa[], int tamanho){
    FILE* arquivo = fopen("Dados.csv", "w");

    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    //Escrever os dados no arquivo
    fprintf(arquivo, "Nome, CPF, Identidade, Salario, Despesa, Credito\n");

    int i;
    for(i = 0; i < tamanho; i++){
        fprintf(arquivo, "%s, %s, %s, %.2f, %.2f, %2.f\n", pessoa[i].nome, pessoa[i].cpf, pessoa[i].identidade, pessoa[i].salario, pessoa[i].despesa, pessoa[i].credito);
    }

    //Fechar arquivo
    fclose(arquivo);

    printf("Arquivo CSV criado com sucsso.\n");
}

void lerCSV(struct dados pessoa[], int* tamanho){
    FILE *arquivo = fopen("Dados.csv", "r+");

    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo.\n");

        return;
    }

    char linha[200];
    *tamanho = 0;

    fgets(linha, 200, arquivo);

    while(fgets(linha, 200, arquivo) != NULL){
        char *token = strtok(linha, ",");

        if(token == NULL){
            continue;
        }

        strcpy(pessoa[*tamanho].nome, token);
        token = strtok(NULL, ",");

        if(token == NULL){
            continue;
        }

        strcpy(pessoa[*tamanho].cpf, token);

        token = strtok(NULL, ",");

        if(token == NULL){
            continue;
        }

        strcpy(pessoa[*tamanho].identidade, token);
        token = strtok(NULL, ",");

        if(token == NULL){
            continue;
        }

        pessoa[*tamanho].salario = atof(token);

        token = strtok(NULL, ",");

        if(token == NULL){
            continue;
        }

        pessoa[*tamanho].despesa = atof(token);

        token = strtok(NULL, ",");

        if(token == NULL){
            continue;
        }

        pessoa[*tamanho].credito = atof(token);

        (*tamanho)++;
    }
    fclose(arquivo);
}

int verificarArquivoVazio (const char *nomeArquivo){ //Verifica o arquivo vasio
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {

        return -1;
    }

    fseek(arquivo, 0, SEEK_END); // Move o cursor para o final do arquivo
    long tamanho = ftell(arquivo); // Obtém a posição atual do cursor
    fclose(arquivo);

    if (tamanho == 0) {
        return 1;  // Arquivo está vazio
    }

    return 0;  // Arquivo não está vazio
}

void imprimirDados(const struct dados pessoa[], int tamanho){
    for (int i = 0; i < tamanho; i++) {
        printf("Nome: %s\n", pessoa[i].nome);
        printf("CPF: %s\n", pessoa[i].cpf);
        printf("Identidade: %s\n", pessoa[i].identidade);
        printf("Salario: %.2f\n", pessoa[i].salario);
        printf("Despesas: %.2f\n", pessoa[i].despesa);
        printf("Credito: %.2f\n\n", pessoa[i].credito);
    }
}

float analisePronta(float salario, float despesa, float credito){
    credito = salario - despesa;

    if(credito <= 0){
        printf("Desculpe, mas sua analise nao foi aprovada.\n");
    } else if(credito > 0){
        despesa = despesa * 2;

        if(salario > despesa){
            printf("Parabens! Sua analise de credito foi aprovada.\n");
            printf("Voce consegue um credito no valor de ate %.2f.\n", credito);

        } else if(salario <= despesa){
            printf("Parabens! Sua analise de credito foi aprovada. \n");
            printf("Voce consegue um credito no valor de ate %.2f.\n", credito);
        }
    }
    return credito;
}

void alterarDados(struct dados* pessoa, int tamanho) {
    int i;
    int num1;
    int num2;
    char cpfPesquisado[15];

    printf("Insira o CPF do titular: ");
    fgets(cpfPesquisado, sizeof(cpfPesquisado), stdin);
    cpfPesquisado[strcspn(cpfPesquisado, "\n")] = '\0';

    for (i = 0; i < tamanho; i++) {
        num1 = atoi(cpfPesquisado);
        num2 = atoi(pessoa[i].cpf);

        if (num1 == num2) {
            printf("Corrigir Nome: ");
            fgets(pessoa[i].nome, sizeof(pessoa[i].nome), stdin);
            pessoa[i].nome[strcspn(pessoa[i].nome, "\n")] = '\0';

            const char *nomeArquivo = "Dados.csv";

            int num1, num2, repeat = 0;

            do{
                int vazio = verificarArquivoVazio(nomeArquivo);

                if (vazio == -1) {
                    printf("\nPor favor salve esses dados pelo menos 1 vez para funcionar corretamente.\n");
                    repeat = 1;
                    break;
                }

                for (int i = 0; i < tamanho; i++){
                    num1 = atoi (pessoa[tamanho].cpf);
                    num2 = atoi (pessoa[i].cpf);

                    if (vazio == -1) {
                        repeat = 0;
                        break;

                    } else if(num1 == num2){
                        printf("\nO CPF esta cadastrado.\n Insira um CPF valido.\n");
                        repeat = 0;
                        break;

                    } else {
                        repeat = 1;
                    }
                }

            } while(repeat == 0);

            printf("Corrigir CPF: ");
            fgets(pessoa[i].cpf, sizeof(pessoa[i].cpf), stdin);
            pessoa[i].cpf[strcspn(pessoa[i].cpf, "\n")] = '\0';

            printf("Corrigir Identidade: ");
            fgets(pessoa[i].identidade, sizeof(pessoa[i].identidade), stdin);
            pessoa[i].identidade[strcspn(pessoa[i].identidade, "\n")] = '\0';

            printf("Corrigir Salario: ");
            scanf("%f", &pessoa[i].salario);
            getchar(); // Limpar o buffer de entrada

            printf("Corrigir Despesas: ");
            scanf("%f", &pessoa[i].despesa);
            getchar(); // Limpar o buffer de entrada

            pessoa[i].credito = analisePronta(pessoa[i].salario, pessoa[i].despesa, pessoa[i].credito);

            printf("Dados alterados com sucesso!\n");
            return;
        }
    }
    printf("CPF nao encontrado.\n\n");
}

void efetuarAnalise (struct dados *pessoa, int tamanho) {
    const char *nomeArquivo = "Dados.csv";
    int cpfAtual;
    int cpfNovo;
    int repeat = 0;
    int analise;

    logo();
    dadosPessoais();

    printf("Insira o seu nome: ");
    fgets(pessoa[tamanho].nome, sizeof(pessoa[tamanho].nome), stdin);

    size_t newlinePos = strcspn(pessoa[tamanho].nome, "\n");

    if (pessoa[tamanho].nome[newlinePos] == '\n') {
        pessoa[tamanho].nome[newlinePos] = '\0';
    }

    do {
        printf("Insira o seu CPF: ");
        fgets(pessoa[tamanho].cpf, sizeof(pessoa[tamanho].cpf), stdin);

        int vazio = verificarArquivoVazio(nomeArquivo);

        if (vazio == -1) {
            printf("\nPor favor, salve esses dados ao menos 1 vez para funcionar corretamente.\n\n");
            repeat = 1;
            break;
        }

        cpfAtual = atoi(pessoa[tamanho].cpf);
        repeat = 1;

        for(int i = 0; i < tamanho; i++){
            cpfNovo = atoi (pessoa[i].cpf);

            if (cpfAtual == cpfNovo) {
                repeat = 0;
                break;

            } if (cpfNovo == cpfAtual){
                printf("\nO CPF inserido ja esta cadastrado.\n Insira um CPF valido.\n\n");
                repeat = 0;
                break;
            }
        }

    } while (repeat == 0);

    newlinePos = strcspn(pessoa[tamanho].cpf, "\n");

    if (pessoa[tamanho].cpf[newlinePos] == '\n') {
        pessoa[tamanho].cpf[newlinePos] = '\0';
    }

    newlinePos = strcspn(pessoa[tamanho].cpf, "\n");

    if (pessoa[tamanho].cpf[newlinePos] == '\n') {
        pessoa[tamanho].cpf[newlinePos] = '\0';
    }

    printf("Insira a sua identidade: ");

    fgets(pessoa[tamanho].identidade, sizeof(pessoa[tamanho].identidade), stdin);
    newlinePos = strcspn(pessoa[tamanho].identidade, "\n");

    if (pessoa[tamanho].identidade[newlinePos] == '\n') {
        pessoa[tamanho].identidade[newlinePos] = '\0';
    }

    pause();
    logo();
    analiseCredito();

    pause();

    logo();
    dadosFinanceiro();

    printf("Insira o seu salario:");
    scanf("%f", &pessoa[tamanho].salario);
    fflush(stdin);

    printf("Insira as suas despesas mensais: ");
    scanf("%f", &pessoa[tamanho].despesa);
    fflush(stdin);

    printf("Se tiver interesse em fazer uma analise de credito, selecione [0] para NAO e [1] para SIM: ");
    scanf("%d", &analise);
    fflush(stdin);

    while (analise != 1 && analise != 0) {
        switch (analise) {
            case 0:
                printf("Que bom!! Espero ter ajudado!");
                break;

            case 1:

                logo();
                analiseCredito();

                printf("Otimo, vamos para a ánalise\n");

                while (getchar() != '\n');

                logo();
                analiseCredito();

                pessoa[tamanho].credito = analisePronta(pessoa[tamanho].salario, pessoa[tamanho].despesa, pessoa[tamanho].credito);
                break;

            default:
                printf("Insira o valor valido. [0] NAO [1] SIM. \n");
                scanf("%d", &analise);
                break;
        }
    }

    if (analise == 1) {
        logo();
        pessoa[tamanho].credito = analisePronta(pessoa[tamanho].salario, pessoa[tamanho].despesa, pessoa[tamanho].credito);

        if (pessoa[tamanho].credito <= 0) {
            printf("O usuario %s esta com score negativo.\n", pessoa[tamanho].nome);
            tamanho++;

            pause();

        } else {
            printf("O usuario %s esta com score positivo.\n", pessoa[tamanho].nome);
            tamanho++;

            pause();
        }
    }

    if (analise == 0) {
        printf("Que bom!! Espero ter ajudado!\n");
        pessoa[tamanho].credito = 0;

        pause();
    }
}

void listarCadastro (struct dados* pessoa, int tamanho) {
    imprimirDados(pessoa, tamanho);

    printf("\n\n");

    pause();
}

void lerDados (struct dados* pessoa, int tamanho) {
    imprimirDados(pessoa,tamanho);
    pause();
}

void corrigirDados (struct dados* pessoa, int tamanho) {
    alterarDados(pessoa, tamanho);
    pause();

}

void imprimirCreditoPositivo (struct dados* pessoa, int tamanho) {
    imprimirPositivo(pessoa, tamanho);

    pause();
}

void imprimirCreditoNegativo (struct dados* pessoa, int tamanho) {
    imprimirNegativo(pessoa, tamanho);

    pause();
}

void sair (struct dados* pessoa, int tamanho) {
    salvarCSV(pessoa, tamanho);

    printf("\n\n");

    pause();
}

int main () {
    cabecalho();
    cabecalhoDados();

    struct dados pessoa[100];
    const char *nomeArquivo = "Dados.csv";

    pause();

    int op;
    int tamanho = 0;

    lerCSV(pessoa, &tamanho);

    do {
        printf("\n\n");

        logo();

        printf(""
           "\nEscolha:\n"
           "\n 1 - Efetuar Analise"
           "\n 2 - Listar Cadastros"
           "\n 3 - Ler os Dados"
           "\n 4 - Alterar Dados"
           "\n 5 - Imprimir creditos positivos"
           "\n 6 - Imprimir creditos negativos"
           "\n 7 - Sair e Salvar\n\n"
        );

        printf("Selecione a opcao que deseja: ");
        scanf("%d", &op);

        while (getchar() != '\n');

        switch (op) {
            case 1:

                efetuarAnalise(pessoa, tamanho);
                tamanho++;

                break;

            case 2:
                listarCadastro(pessoa, tamanho);
                tamanho++;

                break;

            case 3:
                lerDados(pessoa, tamanho);
                tamanho++;

                break;

            case 4:
                alterarDados(pessoa, tamanho);
                tamanho++;

                break;

            case 5:
                imprimirCreditoPositivo(pessoa, tamanho);
                tamanho++;

                break;

            case 6:
                imprimirCreditoNegativo(pessoa, tamanho);
                tamanho++;

                break;

            case 7:
                tamanho++;
                sair(pessoa, tamanho);
                break;
        }

    } while (op != 7);

    return 0;
}
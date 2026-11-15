#include <stdio.h>

void lerNome(char nome[]) {
    fgets(nome, 51, stdin);

    int i = 0;

    while (nome[i] != '\n' && nome[i] != '\0') {
        i++;
    }

    nome[i] = '\0';
}

int main() {
    int encontrouItem = 0;
    int encontrado = 0;
    int quantidadeArquivo;
    int i;
    int iguais;
    char nomeArquivo[51];
    char item[51];
    int quantidade;
    int opcao = 0;
    char continuar = 's';

FILE *arquivo;
FILE *temporario;

    while (continuar == 's') {

    printf("===== Controle de Estoque =====\n");
    printf("1 - Adicionar Item\n");
    printf("2 - Remover Item\n");
    printf("3 - Listar Estoque\n");
    printf("4 - Sair\n");

    printf("Escolha uma opção: ");

if (scanf("%d", &opcao) != 1) {
    printf("Entrada invalida!\n");
    while (getchar() != '\n');
    continue;
}

if (getchar() != '\n') {
    printf("Entrada invalida! Digite apenas um número inteiro.\n");
    while (getchar() != '\n');
    continue;
}
if (opcao < 1 || opcao > 4) {
    printf("Opção inválida! Escolha de 1 a 4.\n");
    continue;
}
switch (opcao) {

    
case 1:
    printf("Digite o nome do item: ");
    lerNome(item);

    printf("Digite a quantidade: ");

while (scanf("%d", &quantidade) != 1 || quantidade <= 0) {
    printf("Quantidade inválida! Digite um número inteiro positivo: ");
    while (getchar() != '\n');
}

while (getchar() != '\n');

    arquivo = fopen("inventory.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        break;
    }

    fprintf(arquivo, "%s\n%d\n", item, quantidade);

    fclose(arquivo);

    printf("Item adicionado com sucesso!\n");
    break;

    case 2:
    printf("Digite o nome do item: ");
    lerNome(item);

    printf("Digite a quantidade a ser removida: ");

while (scanf("%d", &quantidade) != 1 || quantidade <= 0) {
    printf("Quantidade inválida! Digite um número inteiro positivo: ");
    while (getchar() != '\n');
}

while (getchar() != '\n');

    arquivo = fopen("inventory.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        break;
    }
    temporario = fopen("temporario.txt", "w");
    if (temporario == NULL) {
    printf("Erro ao criar arquivo temporário!\n");
    fclose(arquivo);
    break;
}
    encontrado = 0;
    while (fgets(nomeArquivo, 51, arquivo) != NULL) {

         i = 0;

    while (nomeArquivo[i] != '\n' && nomeArquivo[i] != '\0') {
        i++;
    }

    nomeArquivo[i] = '\0';

    fscanf(arquivo, "%d", &quantidadeArquivo);
    fgetc(arquivo);
    iguais = 1;

i = 0;

while (item[i] != '\0' || nomeArquivo[i] != '\0') {

    if (item[i] != nomeArquivo[i]) {
        iguais = 0;
        break;
    }

    i++;
}

if (iguais == 1) {
    encontrado = 1;

    if (quantidade > quantidadeArquivo) {
        printf("Estoque insuficiente! Disponível: %d\n", quantidadeArquivo);
        fprintf(temporario, "%s\n%d\n", nomeArquivo, quantidadeArquivo);

    } else {
        quantidadeArquivo = quantidadeArquivo - quantidade;

        if (quantidadeArquivo > 0) {
            printf("Estoque atualizado com sucesso! Quantidade restante: %d\n", quantidadeArquivo);
            fprintf(temporario, "%s\n%d\n", nomeArquivo, quantidadeArquivo);

        } else {
            printf("Produto removido do estoque! O saldo chegou a zero.\n");
        }
    }

} else {
    fprintf(temporario, "%s\n%d\n", nomeArquivo, quantidadeArquivo);
}
}

if (encontrado == 0) {
    printf("Item não encontrado.\n");
}

fclose(arquivo);
fclose(temporario);

if (remove("inventory.txt") == 0) {
    if (rename("temporario.txt", "inventory.txt") != 0) {
        printf("Erro ao atualizar o estoque!\n");
    }
} else {
    printf("Erro ao substituir o arquivo antigo!\n");
}

break;

    case 3:
    arquivo = fopen("inventory.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        break;
    }

    printf("===== Estoque Atual =====\n");

encontrouItem = 0;

    while (fgets(nomeArquivo, 51, arquivo) != NULL) {

encontrouItem = 1;

        i = 0;

while (nomeArquivo[i] != '\n' && nomeArquivo[i] != '\0') {
    i++;
}

nomeArquivo[i] = '\0';

fscanf(arquivo, "%d", &quantidadeArquivo);
fgetc(arquivo);

printf("Nome: %s\n", nomeArquivo);
printf("Quantidade: %d\n\n", quantidadeArquivo);
    }
    if (encontrouItem == 0) {
    printf("O estoque está vazio!\n");
}

    fclose(arquivo);
    break;

    case 4:
        printf("Obrigado por usar o Controle de Estoques! Até a próxima.\n");
        return 0;
}
printf("Deseja realizar outra operação? (s/n): ");
        scanf(" %c", &continuar);

if (continuar == 'S') {
    continuar = 's';
} else if (continuar == 'N') {
    continuar = 'n';
}

while (continuar != 's' && continuar != 'n') {
    printf("Resposta inválida! Digite s ou n: ");
    scanf(" %c", &continuar);

    if (continuar == 'S') {
        continuar = 's';
    } else if (continuar == 'N') {
        continuar = 'n';
    }
}
if (continuar == 'n') {
        printf("Obrigado por usar o Controle de Estoques! Até a próxima.\n");
}

}

return 0;
}

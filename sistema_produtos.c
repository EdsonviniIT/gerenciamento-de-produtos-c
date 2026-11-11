#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100
#define TAM_NOME 50
#define TAM_CATEGORIA 50
#define TAM_FORNECEDOR 50
#define ARQUIVO_CSV "produtos.csv"

/*
    SISTEMA DE GERENCIAMENTO DE PRODUTOS

    O programa mantém os produtos em um vetor de estruturas na memória
    e utiliza um arquivo CSV para guardar os dados entre execuções.

    Observação: para manter este exemplo didático, os campos de texto
    não devem conter ponto e vírgula (;), pois esse caractere separa
    as colunas do CSV.
*/

struct Produto {
    int id;
    char nome[TAM_NOME];
    char categoria[TAM_CATEGORIA];
    float preco;
    int quantidade;
    char fornecedor[TAM_FORNECEDOR];
};

/* Remove o ENTER deixado pelo fgets. */
void removerQuebraLinha(char texto[]) {
    texto[strcspn(texto, "\n")] = '\0';
}

/* Lê uma linha de texto com segurança. */
void lerTexto(const char mensagem[], char destino[], int tamanho) {
    printf("%s", mensagem);

    if (fgets(destino, tamanho, stdin) != NULL) {
        removerQuebraLinha(destino);
    } else {
        destino[0] = '\0';
    }
}

/* Lê um número inteiro e repete até receber uma entrada válida. */
int lerInteiro(const char mensagem[]) {
    char linha[100];
    char *fim;
    long valor;

    while (1) {
        printf("%s", mensagem);

        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            continue;
        }

        valor = strtol(linha, &fim, 10);

        if (fim == linha) {
            printf("Entrada invalida. Digite um numero inteiro.\n");
            continue;
        }

        while (*fim == ' ' || *fim == '\t' || *fim == '\n') {
            fim++;
        }

        if (*fim != '\0') {
            printf("Entrada invalida. Digite somente o numero.\n");
            continue;
        }

        return (int)valor;
    }
}

/* Lê um número decimal. O usuário deve utilizar ponto, por exemplo 19.90. */
float lerFloat(const char mensagem[]) {
    char linha[100];
    char *fim;
    float valor;

    while (1) {
        printf("%s", mensagem);

        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            continue;
        }

        valor = strtof(linha, &fim);

        if (fim == linha) {
            printf("Entrada invalida. Digite um numero, por exemplo 19.90.\n");
            continue;
        }

        while (*fim == ' ' || *fim == '\t' || *fim == '\n') {
            fim++;
        }

        if (*fim != '\0') {
            printf("Entrada invalida. Digite somente o numero.\n");
            continue;
        }

        return valor;
    }
}

/* Procura um produto pelo ID e devolve sua posição no vetor.
   Se não encontrar, devolve -1. */
int buscarIndicePorID(struct Produto lista[], int quantidade, int id) {
    for (int i = 0; i < quantidade; i++) {
        if (lista[i].id == id) {
            return i;
        }
    }

    return -1;
}

/* Encontra o próximo ID disponível, usando o maior ID existente + 1. */
int gerarProximoID(struct Produto lista[], int quantidade) {
    int maiorID = 0;

    for (int i = 0; i < quantidade; i++) {
        if (lista[i].id > maiorID) {
            maiorID = lista[i].id;
        }
    }

    return maiorID + 1;
}

/* Mostra os dados de um único produto. */
void mostrarUmProduto(struct Produto p) {
    printf("\nID: %d\n", p.id);
    printf("Nome: %s\n", p.nome);
    printf("Categoria: %s\n", p.categoria);
    printf("Preco: R$ %.2f\n", p.preco);
    printf("Quantidade: %d\n", p.quantidade);
    printf("Fornecedor: %s\n", p.fornecedor);
}

/* Lista todos os produtos cadastrados. */
void listarProdutos(struct Produto lista[], int quantidade) {
    if (quantidade == 0) {
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    printf("\n========== LISTA DE PRODUTOS ==========\n");

    for (int i = 0; i < quantidade; i++) {
        printf("\n--- Produto %d de %d ---\n", i + 1, quantidade);
        mostrarUmProduto(lista[i]);
    }
}

/* Cadastra um produto novo no final do vetor. */
void cadastrarProduto(struct Produto lista[], int *quantidade) {
    struct Produto novo;

    if (*quantidade >= MAX_PRODUTOS) {
        printf("\nLimite de %d produtos atingido.\n", MAX_PRODUTOS);
        return;
    }

    novo.id = gerarProximoID(lista, *quantidade);

    printf("\n========== CADASTRO DE PRODUTO ==========\n");
    printf("ID gerado automaticamente: %d\n", novo.id);

    lerTexto("Nome: ", novo.nome, TAM_NOME);
    lerTexto("Categoria: ", novo.categoria, TAM_CATEGORIA);
    novo.preco = lerFloat("Preco (use ponto decimal, ex. 49.90): R$ ");
    novo.quantidade = lerInteiro("Quantidade em estoque: ");
    lerTexto("Fornecedor: ", novo.fornecedor, TAM_FORNECEDOR);

    if (novo.preco < 0 || novo.quantidade < 0) {
        printf("\nPreco e quantidade nao podem ser negativos. Cadastro cancelado.\n");
        return;
    }

    lista[*quantidade] = novo;
    (*quantidade)++;

    printf("\nProduto cadastrado com sucesso!\n");
}

/* Pesquisa produtos por ID, nome, categoria ou preço. */
void pesquisarProduto(struct Produto lista[], int quantidade) {
    int opcao;
    int encontrados = 0;
    char texto[TAM_NOME];
    int id;
    float preco;

    printf("\n========== PESQUISAR PRODUTO ==========\n");
    printf("1 - Pesquisar por ID\n");
    printf("2 - Pesquisar por nome\n");
    printf("3 - Pesquisar por categoria\n");
    printf("4 - Pesquisar por preco exato\n");
    opcao = lerInteiro("Escolha o tipo de pesquisa: ");

    switch (opcao) {
        case 1:
            id = lerInteiro("Digite o ID: ");
            {
                int indice = buscarIndicePorID(lista, quantidade, id);
                if (indice != -1) {
                    mostrarUmProduto(lista[indice]);
                    encontrados++;
                }
            }
            break;

        case 2:
            lerTexto("Digite o nome ou parte do nome: ", texto, TAM_NOME);
            for (int i = 0; i < quantidade; i++) {
                if (strstr(lista[i].nome, texto) != NULL) {
                    mostrarUmProduto(lista[i]);
                    encontrados++;
                }
            }
            break;

        case 3:
            lerTexto("Digite a categoria: ", texto, TAM_CATEGORIA);
            for (int i = 0; i < quantidade; i++) {
                if (strstr(lista[i].categoria, texto) != NULL) {
                    mostrarUmProduto(lista[i]);
                    encontrados++;
                }
            }
            break;

        case 4:
            preco = lerFloat("Digite o preco (use ponto decimal): R$ ");
            for (int i = 0; i < quantidade; i++) {
                /* A tolerância evita problemas comuns de comparação de float. */
                float diferenca = lista[i].preco - preco;
                if (diferenca >= -0.005f && diferenca <= 0.005f) {
                    mostrarUmProduto(lista[i]);
                    encontrados++;
                }
            }
            break;

        default:
            printf("Opcao de pesquisa invalida.\n");
            return;
    }

    if (encontrados == 0) {
        printf("\nNenhum produto encontrado com esse criterio.\n");
    } else {
        printf("\nTotal de produtos encontrados: %d\n", encontrados);
    }
}

/* Altera os dados de um produto encontrado pelo ID. */
void alterarProduto(struct Produto lista[], int quantidade) {
    int id = lerInteiro("\nDigite o ID do produto que deseja alterar: ");
    int indice = buscarIndicePorID(lista, quantidade, id);

    if (indice == -1) {
        printf("\nProduto com ID %d nao encontrado.\n", id);
        return;
    }

    struct Produto atualizado = lista[indice];

    printf("\nProduto localizado. Digite os novos dados.\n");
    mostrarUmProduto(lista[indice]);

    lerTexto("\nNovo nome: ", atualizado.nome, TAM_NOME);
    lerTexto("Nova categoria: ", atualizado.categoria, TAM_CATEGORIA);
    atualizado.preco = lerFloat("Novo preco (use ponto decimal): R$ ");
    atualizado.quantidade = lerInteiro("Nova quantidade: ");
    lerTexto("Novo fornecedor: ", atualizado.fornecedor, TAM_FORNECEDOR);

    if (atualizado.preco < 0 || atualizado.quantidade < 0) {
        printf("\nPreco e quantidade nao podem ser negativos. Alteracao cancelada.\n");
        return;
    }

    lista[indice] = atualizado;
    printf("\nProduto alterado com sucesso!\n");
}

/* Exclui um produto deslocando os elementos seguintes uma posição para trás. */
void excluirProduto(struct Produto lista[], int *quantidade) {
    int id = lerInteiro("\nDigite o ID do produto que deseja excluir: ");
    int indice = buscarIndicePorID(lista, *quantidade, id);

    if (indice == -1) {
        printf("\nProduto com ID %d nao encontrado.\n", id);
        return;
    }

    for (int i = indice; i < *quantidade - 1; i++) {
        lista[i] = lista[i + 1];
    }

    (*quantidade)--;

    printf("\nProduto excluido com sucesso!\n");
}

/* Salva todos os produtos no arquivo CSV.
   O modo "w" cria o arquivo ou substitui seu conteúdo anterior. */
int salvarCSV(struct Produto lista[], int quantidade) {
    FILE *arquivo = fopen(ARQUIVO_CSV, "w");

    if (arquivo == NULL) {
        printf("\nErro: nao foi possivel abrir o arquivo para salvar.\n");
        return 0;
    }

    fprintf(arquivo, "id;nome;categoria;preco;quantidade;fornecedor\n");

    for (int i = 0; i < quantidade; i++) {
        fprintf(arquivo, "%d;%s;%s;%.2f;%d;%s\n",
                lista[i].id,
                lista[i].nome,
                lista[i].categoria,
                lista[i].preco,
                lista[i].quantidade,
                lista[i].fornecedor);
    }

    fclose(arquivo);
    return 1;
}

/* Carrega os produtos do CSV para o vetor.
   Se o arquivo ainda não existir, o sistema começa vazio. */
int carregarCSV(struct Produto lista[], int *quantidade) {
    FILE *arquivo = fopen(ARQUIVO_CSV, "r");
    char linha[300];

    *quantidade = 0;

    if (arquivo == NULL) {
        return 1;
    }

    /* Lê e descarta a primeira linha, que contém os nomes das colunas. */
    if (fgets(linha, sizeof(linha), arquivo) == NULL) {
        fclose(arquivo);
        return 1;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL &&
           *quantidade < MAX_PRODUTOS) {

        struct Produto p;
        char *campo;

        removerQuebraLinha(linha);

        campo = strtok(linha, ";");
        if (campo == NULL) continue;
        p.id = atoi(campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        strncpy(p.nome, campo, TAM_NOME - 1);
        p.nome[TAM_NOME - 1] = '\0';

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        strncpy(p.categoria, campo, TAM_CATEGORIA - 1);
        p.categoria[TAM_CATEGORIA - 1] = '\0';

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        p.preco = (float)atof(campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        p.quantidade = atoi(campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        strncpy(p.fornecedor, campo, TAM_FORNECEDOR - 1);
        p.fornecedor[TAM_FORNECEDOR - 1] = '\0';

        lista[*quantidade] = p;
        (*quantidade)++;
    }

    fclose(arquivo);
    return 1;
}

/* Exibe as opções disponíveis para o usuário. */
void mostrarMenu(void) {
    printf("\n========== SISTEMA DA LOJA ==========\n");
    printf("1 - Cadastrar produto\n");
    printf("2 - Listar produtos\n");
    printf("3 - Pesquisar produto por ID\n");
    printf("4 - Alterar produto\n");
    printf("5 - Excluir produto\n");
    printf("6 - Salvar dados no CSV\n");
    printf("0 - Salvar e sair\n");
}

/* Função principal: organiza a execução do sistema. */
int main(void) {
    struct Produto lista[MAX_PRODUTOS];
    int quantidade = 0;
    int opcao;

    carregarCSV(lista, &quantidade);

    printf("Sistema iniciado. %d produto(s) carregado(s).\n", quantidade);

    do {
        mostrarMenu();
        opcao = lerInteiro("Escolha uma opcao: ");

        switch (opcao) {
            case 1:
                cadastrarProduto(lista, &quantidade);
                salvarCSV(lista, quantidade);
                break;

            case 2:
                listarProdutos(lista, quantidade);
                break;

            case 3:
                pesquisarProduto(lista, quantidade);
                break;

            case 4:
                alterarProduto(lista, quantidade);
                salvarCSV(lista, quantidade);
                break;

            case 5:
                excluirProduto(lista, &quantidade);
                salvarCSV(lista, quantidade);
                break;

            case 6:
                if (salvarCSV(lista, quantidade)) {
                    printf("\nDados salvos em %s.\n", ARQUIVO_CSV);
                }
                break;

            case 0:
                if (salvarCSV(lista, quantidade)) {
                    printf("\nDados salvos. Encerrando o sistema.\n");
                } else {
                    printf("\nSistema encerrado, mas houve falha ao salvar.\n");
                }
                break;

            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}

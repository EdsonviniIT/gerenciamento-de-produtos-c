# Sistema de Gerenciamento de Produtos em C

Projeto desenvolvido em linguagem C para praticar lógica de programação, organização de dados em estruturas e manipulação de arquivos.

O sistema mantém os produtos em um vetor de estruturas (`struct Produto`) e utiliza um arquivo CSV para preservar os registros entre execuções.

## Funcionalidades

- Cadastro de produtos com geração automática de ID;
- Listagem dos produtos cadastrados;
- Pesquisa por ID, nome, categoria ou preço;
- Alteração de informações;
- Exclusão de produtos;
- Salvamento e carregamento dos registros em CSV;
- Validação básica de entradas numéricas.

## Conceitos de C praticados

- `struct` e vetor de estruturas;
- Funções e passagem de parâmetros;
- Ponteiros e operador `&`;
- Manipulação de arquivos com `FILE`, `fopen`, `fgets`, `fprintf` e `fclose`;
- Manipulação de strings com `strstr`, `strtok`, `strncpy` e `strcspn`;
- Conversão de texto para números com `strtol`, `strtof`, `atoi` e `atof`;
- Estruturas de controle `if`, `switch`, `for`, `while` e `do-while`.

## Estrutura do projeto

```text
gerenciamento-de-produtos-c/
├── sistema_produtos.c       # Código-fonte principal
├── produtos.csv             # Dados de exemplo para iniciar o sistema
├── README.md                # Apresentação e instruções do projeto
├── .gitignore               # Arquivos que não precisam ir para o GitHub
└── docs/
    └── GUIA-DE-ESTUDO.md    # Explicação dos principais conceitos do código
```

## Como compilar e executar

É necessário ter um compilador C instalado, como o GCC.

### Windows (MinGW/GCC)

Abra o terminal na pasta do projeto e execute:

```bash
gcc sistema_produtos.c -o sistema_produtos.exe
./sistema_produtos.exe
```

Se o terminal do Windows não aceitar `./`, execute:

```powershell
.\sistema_produtos.exe
```

### Linux

```bash
gcc sistema_produtos.c -o sistema_produtos
./sistema_produtos
```

O arquivo `produtos.csv` deve permanecer na mesma pasta do executável durante a execução. Se ele não existir, o programa inicia sem produtos e cria o arquivo ao salvar.

## Formato dos dados

O CSV utiliza ponto e vírgula (`;`) como separador e contém as colunas:

`id;nome;categoria;preco;quantidade;fornecedor`

Digite os preços com ponto decimal, por exemplo `49.90`. Nesta versão, não utilize ponto e vírgula nos campos de texto, pois ele é usado para separar as colunas.

## Limitações conhecidas

- O vetor comporta até 100 produtos;
- Os campos de texto têm tamanho máximo definido no código;
- O CSV é uma implementação didática e não trata todos os recursos do formato CSV, como separadores dentro de campos entre aspas;
- A pesquisa por texto diferencia maiúsculas de minúsculas.

## Objetivo

Transformar conceitos estudados em uma aplicação de terminal funcional, praticando a criação de estruturas, o uso de ponteiros, a divisão do programa em funções e a persistência de dados em arquivos.

## Guia de estudo

Consulte [`docs/GUIA-DE-ESTUDO.md`](docs/GUIA-DE-ESTUDO.md) para ver explicações sobre a organização do código, ponteiros, funções, arquivos e fluxo de execução.

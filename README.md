# Trabalho Prático de Algoritmo e Estrutura de Dados III

Este é um trabalho prático desenvolvido para a disciplina de Algoritmos e Estruturas de Dados III. O projeto consiste em implementações de Árvore Binária, Árvore AVL e Pesquisa Sequencial, bem como um Gerador de Registros, com objetivo de analisar o algoritmo de busca de uma chave em cada estrutura de dados. Neste README está presente as instruções para executar cada código.

## Conteúdo

1. [Gerador de Registros](#gerador-de-registros)
2. [Árvore Binária](#árvore-binária)
3. [Árvore AVL](#árvore-avl)
4. [Pesquisa Sequencial](#pesquisa-sequencial)
5. [Observações Gerais](#observações-gerais)
6. [Autores](#autores)

## Gerador de Registros 

O Gerador de Registros cria os registros e os armazena em 2 arquivos .txt diferentes, um contendo os registros com as chaves de forma ordenada, e outro contendo os registros com as chaves de maneira desordenada.

### Arquivo: `GerarArquivos.py`

#### Estruturas de Dados

- **Registro**: Uma estrutura que representa um registro com três campos - chave (um número inteiro), dado1 (um número inteiro) e dado2 (um char de 1000 caracteres).

#### Funções 

- `def gerar_char()`: Gera um char de 1000 caracteres
- `def gerar_numero()`: Gera um número inteiro aleatório entre 1 e 100

### Como Usar

1. Compile o código.
2. Execute o programa.
3. Os arquivos de dados ordenados e desordenados são gerados com base no número de registros propostos.

## Árvore Binária

A Árvore Binária é uma estrutura de dados que armazena os registros de forma que sempre a subárvore a direita do nó vai conter chaves maiores do que a do nó atual e a subárvore a esquerda vai conter chaves menores do que a do nó atual.

### Arquivo: `arvore_binaria.cpp`

#### Estruturas de Dados

- **Tiporeg**: Uma estrutura que representa um registro com três campos - chave (um número inteiro), dado1 (um número inteiro) e dado2 (uma char de 1000 caracteres).
- **No**: Uma estrutura que representa um nó em uma árvore binária, com um registro, ponteiros para os nós à esquerda e à direita e uma variável para contar o número de interações durante as operações.

#### Funções

- `novoNo(Tiporeg pRegistro)`: Cria um novo nó com um registro específico e retorna o ponteiro para esse nó.

### Como Usar

1. Compile o código.
2. Execute o programa.
3. O programa vai pedir para você digitar o nome do arquivo desejado (Qualquer um dos presentes na pasta de Arquivos de Entrada) e vai pedir o número de registros presentes no arquivo (Quantidade de linhas).
4. Após inserir essas informações, ele vai realizar a inserção dos registros em uma árvore binária e realizar a pesquisa de 30 chaves, 15 presentes e 15 não presentes na estrutura.
5. Será gerado um arquivo de saída contendo o número de interações e o tempo gasto para cada chave pesquisada.

## Árvore AVL

A Árvore AVL é uma árvore binária balanceada que mantém seu fator de equilíbrio.

### Arquivo: `arvore_avl.cpp`

#### Estruturas de Dados

- **Tiporeg**: Uma estrutura que representa um registro com três campos - chave (um número inteiro), dado1 (um número inteiro) e dado2 (uma char de 1000 caracteres).
- **No**: Uma estrutura que representa um nó em uma árvore AVL, com um registro, ponteiros para os nós à esquerda e à direita, uma variável para contar o número de interações durante as operações e uma variável para manter a altura do nó.

#### Funções

- `rotacaoDireita(No* y)`: Realiza uma rotação à direita em um nó da árvore AVL para manter o equilíbrio.
- `rotacaoEsquerda(No* x)`: Realiza uma rotação à esquerda em um nó da árvore AVL para manter o equilíbrio.
- `fatorBalanceamento(No* no)`: Calcula o fator de balanceamento de um nó (diferença entre a altura da subárvore esquerda e da subárvore direita).

### Como Usar

1. Compile o código.
2. Execute o programa.
3. O programa vai pedir para você digitar o nome do arquivo desejado (Qualquer um dos presentes na pasta de Arquivos de Entrada) e vai pedir o número de registros presentes no arquivo (Quantidade de linhas).
4. Após inserir essas informações, ele vai realizar a inserção dos registros em uma AVL e realizar a pesquisa de 30 chaves, 15 presentes e 15 não presentes na estrutura.
5. Será gerado um arquivo de saída contendo o número de interações e o tempo gasto para cada chave pesquisada.

## Pesquisa Sequencial

O código de Pesquisa Sequencial armazena os registros em um vetor

### Arquivo: `pesquisa_sequencial.cpp`

#### Funcionalidades

- Gera chaves aleatórias e busca por elas nos registros.
- Registra o tempo de busca e o número de comparações realizadas.
- Armazena os resultados das buscas em arquivos de saída.

### Como Usar

1. Compile o código.
2. Execute o programa.
3. O programa vai pedir para você digitar o nome do arquivo desejado (Qualquer um dos presentes na pasta de Arquivos de Entrada) e vai pedir o número de registros presentes no arquivo (Quantidade de linhas).
4. Após inserir essas informações, ele vai realizar a inserção dos registros em um vetor e realizar a pesquisa de 30 chaves, 15 presentes e 15 não presentes na estrutura.
5. Será gerado um arquivo de saída contendo o número de interações e o tempo gasto para cada chave pesquisada.

## Observações Gerais

- O gerador gera os arquivos no próprio local onde for executado, após isso é necessário mover os arquivos para a pasta "Arquivos de Entrada"
- É importante que as pastas "Arquivos de Saida" e "Arquivos de entrada estejam no mesmo lugar onde o executável do programa for gerado
- Se as pastas não estiverem no mesmo lugar do executável gerado, o programa vai reportar "Erro ao abrir arquivo" ou "Erro ao abrir arquivo de saida" e encerrar.
- Quando compilar o programa, caso seja gerada uma pasta "output" com o executável, mova as pastas "Arquivos de Saida" e "Arquivos de Entrada" para dentro dessa pasta.
- A pasta "Arquivos de Saida" tem dentro 3 pastas distintas, "Pesquisa Sequencial", "avl" e "binaria", cada uma vai armazenar os arquivos de saída de suas respectivas estruturas de dados, é importante que essas pastas estejam lá e escritas dessa maneira, caso contrário o programa vai reportar "Erro ao abrir arquivo de saida" e encerrar.

## Autores

- Robson da Lomba Campos Junior - robson.campos@ufvjm.edu.br
- Samuel Couto Monteiro Assunção - monteiro.samuel@ufvjm.edu.br
- Marcela Cristina Santos Cruz - marcela.cruz@ufvjm.edu.br








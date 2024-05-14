#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstring>
#include <iomanip>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>
using namespace std;
using namespace chrono;

// Declaração do tipo de registro presente em cada nó
struct Tiporeg {
    int chave;
    int dado1;
    char dado2[1000];
};

// Declaração do tipo de nó 

struct No {
    Tiporeg registro;
    No* esquerda;
    No* direita;
    int altura; // propriedade que retorna a altura do no na arvore
};

//Função para retornar a altura da arvore

int altura(No* no) {
    // essa função retorna a altura do no e é utilizada para pegar o valor máximo do lado direito e esquerdo
    if (no == nullptr) return 0;
    return no->altura;
}

// função para retornar o valor máximo entre duas variáveis
int maximo(int a, int b) {
    return (a > b) ? a : b; 
}

// Função para retornar o ponteiro para um novo nó 
No* novoNo(Tiporeg pRegistro) {
    No* no = new No();
    no->registro = pRegistro;
    no->esquerda = nullptr;
    no->direita = nullptr;
    no->altura = 1;
    return no;
}

struct Arvore_avl {
    // Nó raiz
    No* raiz;

    // inteiro para contar o número de interações ao buscar uma chave 
    int numero_interacoes = 0;

    No* rotacaoDireita(No* y) {
        // 'x' é o nó à esquerda de 'y'
        No* x = y->esquerda;

        // 'T' é a subárvore à direita de 'x'
        No* T = x->direita;

        // Fazendo a rotação à direita
        x->direita = y;
        y->esquerda = T;

        // Atualizando as alturas dos nós após a rotação
        y->altura = maximo(altura(y->esquerda), altura(y->direita)) + 1;
        x->altura = maximo(altura(x->esquerda), altura(x->direita)) + 1;

        // Retorna o novo nó que se torna a raiz da subárvore após a rotação
        return x;
    }


    No* rotacaoEsquerda(No* x) {
        // 'y' é o nó à direita de 'x'
        No* y = x->direita;

        // 'T' é a subárvore à esquerda de 'y'
        No* T = y->esquerda;

        // Fazendo a rotação à esquerda
        y->esquerda = x;
        x->direita = T;

        // Atualizando as alturas dos nós após a rotação
        x->altura = maximo(altura(x->esquerda), altura(x->direita)) + 1;
        y->altura = maximo(altura(y->esquerda), altura(y->direita)) + 1;

        // Retorna o novo nó que se torna a raiz da subárvore após a rotação
        return y;
    }


    int fatorBalanceamento(No* no) {
        // Se o nó é nulo, retorna 0 (árvore vazia tem fator de balanceamento 0)
        if (no == nullptr) return 0;
        
        // Retorna a diferença entre a altura da subárvore esquerda e a altura da subárvore direita
        return altura(no->esquerda) - altura(no->direita);
    }


    No* inserir(No* no, Tiporeg registro) {
        // Se o nó é nulo, cria um novo nó com o registro fornecido
        if (no == nullptr) return novoNo(registro);

        // Caso a chave do registro seja menor que a chave do nó atual, insere na subárvore esquerda
        if (registro.chave < no->registro.chave)
            no->esquerda = inserir(no->esquerda, registro);
        // Caso a chave do registro seja maior que a chave do nó atual, insere na subárvore direita
        else if (registro.chave > no->registro.chave)
            no->direita = inserir(no->direita, registro);
        // Caso a chave do registro seja igual à chave do nó atual, retorna o nó sem fazer nada (evitando duplicatas)
        else
            return no;

        // Atualiza a altura do nó atual com base na altura das subárvores esquerda e direita
        no->altura = 1 + maximo(altura(no->esquerda), altura(no->direita));

        // Calcula o fator de balanceamento para verificar se a árvore está desbalanceada
        int balance = fatorBalanceamento(no);

        // Realiza rotações para reequilibrar a árvore, se necessário
        if (balance > 1 && registro.chave < no->esquerda->registro.chave)
            return rotacaoDireita(no);

        if (balance < -1 && registro.chave > no->direita->registro.chave)
            return rotacaoEsquerda(no);

        if (balance > 1 && registro.chave > no->esquerda->registro.chave) {
            no->esquerda = rotacaoEsquerda(no->esquerda);
            return rotacaoDireita(no);
        }

        if (balance < -1 && registro.chave < no->direita->registro.chave) {
            no->direita = rotacaoDireita(no->direita);
            return rotacaoEsquerda(no);
        }

        // Retorna o nó atual após a inserção e as rotações (se houverem)
        return no;
    }

    void Buscar(No* no, int chave) {
        // Se o nó é nulo, a chave não foi encontrada, retorna falso
        if (no == nullptr) {
            return;
        }
        // Se a chave é menor que a chave do nó atual, realiza busca na subárvore esquerda
        else if (chave < no->registro.chave){
            // Incrementa o número de interações (comparações) realizadas durante a busca
            numero_interacoes++;
            // Chama a função de busca recursivamente na subárvore esquerda
            Buscar(no->esquerda, chave);
        }
        // Se a chave é maior que a chave do nó atual, realiza busca na subárvore direita
        else if (chave > no->registro.chave){
            // Incrementa o número de interações (comparações) realizadas durante a busca
            numero_interacoes++;
            // Chama a função de busca recursivamente na subárvore direita
            Buscar(no->direita, chave);
        }
        // Se a chave é igual à chave do nó atual, a chave foi encontrada, retorna verdadeiro
        else
            return;
    }

};

Tiporeg retornaTipoReg(string s) {
    // Cria uma variável do tipo Tiporeg para armazenar os dados extraídos da string
    Tiporeg aux;

    // Copia a string original para uma variável auxiliar para manipulação
    string auxS = s;

    // Define o delimitador como " "
    string delimiter = " ";

    // Encontra a posição do primeiro delimitador na string
    int pos = s.find(delimiter);

    // Extrai a substring da posição 0 até a posição do primeiro delimitador e converte para inteiro, armazenando em aux.chave
    aux.chave = stoi(s.substr(0, pos));
    // Extrai a substring da posição após o primeiro delimitador até o final da string, converte para inteiro e armazena em aux.dado1
    aux.dado1 = stoi(auxS.substr(pos + 1, s.length()));

    // Encontra a próxima posição do delimitador na string
    pos = s.find(delimiter, pos + 1);

    // Extrai a substring da posição após o segundo delimitador até o final da string e a converte para um array de caracteres, copiando para aux.dado2
    auxS = s.substr(pos + 1, s.length());
    strcpy(aux.dado2, auxS.c_str());

    // Retorna a estrutura Tiporeg com os dados extraídos da string
    return aux;
};


int main() {

    // Cria uma instância da estrutura Arvore_avl
    Arvore_avl arv;
    
    // Variáveis para armazenar dados temporários
    string linha,nomeArquivo;
    int tamanhoArquivo;
    Tiporeg registro_temp;

    // Inicializa a raiz da árvore como nula
    arv.raiz = nullptr;

    cout << "Digite o nome do arquivo de entrada: ";
    cin >> nomeArquivo;
    cout << "Digite a quantidade de registros presentes no arquivo: ";
    cin >> tamanhoArquivo;

    vector<int> chavesPresentes(tamanhoArquivo); // Usando vector para armazenar as chaves presentes
    vector<int> chavesAusentes(tamanhoArquivo); // Usando vector para armazenar as chaves ausentes

    // Preenche o vetor com as chaves presentes 
    for (int i = 0; i < tamanhoArquivo; ++i) { 
        chavesPresentes[i] = i + 1;
    }

    // Preenche o vetor com as chaves ausentes
    for (int i = 0; i < tamanhoArquivo; ++i) { 
        chavesAusentes[i] = i + tamanhoArquivo+1; // Garante que nenhuma chave nesse vetor vai estar presente
    }
    
    random_device rd;
    mt19937 gerador(rd());
    shuffle(chavesPresentes.begin(), chavesPresentes.end(), gerador); // Embaralha as chaves presentes
    shuffle(chavesAusentes.begin(), chavesAusentes.end(), gerador); // Embaralha as chaves ausentes

    vector<int> chavesSorteadas(chavesPresentes.begin(), chavesPresentes.begin() + 15); // Cria um vetor com as 15 primeiras chaves presentes do vetor embaralhado
    chavesSorteadas.insert(chavesSorteadas.end(), chavesAusentes.begin(), chavesAusentes.begin() + 15); // Adiciona 15 chaves ausentes no vetor de chaves sorteadas

    ifstream arquivo("Arquivos de Entrada/"+nomeArquivo);

    // Verifica se o arquivo foi aberto corretamente
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return 1;
    }

    // Lê dados do arquivo e insere na árvore AVL
    while (getline(arquivo, linha)) {
        string s = linha;
        if (s != "") {
            // Converte a linha do arquivo para a estrutura Tiporeg e insere na árvore AVL
            registro_temp = retornaTipoReg(s);
            arv.raiz = arv.inserir(arv.raiz, registro_temp);
        }
    }

    // Fecha o arquivo após a leitura
    arquivo.close();

    

    // Abre o arquivo de saída "arquivo_saida.txt"
    ofstream arquivo_saida("Arquivos de Saida/avl/arquivo_saida_"+nomeArquivo);

    // Verifica se o arquivo de saída foi aberto corretamente
    if (!arquivo_saida.is_open()) {
        cerr << "Erro ao abrir o arquivo de saída." << endl;
        return 1;
    }

    for (int i = 0; i < 30; i++){
        int chaveAtual = chavesSorteadas[i];

        arv.numero_interacoes = 0; // Iniciar o contador de comparações 

        auto start = high_resolution_clock::now(); // Inicia timer antes de realizar a busca

        //Compara a chave atual com cada chave do arquivo
        arv.Buscar(arv.raiz, chavesSorteadas[i]);

        auto end = high_resolution_clock::now(); // Finaliza timer

        auto duration = duration_cast<nanoseconds>(end - start); // Calcula tempo de execução

        double durationInNanoSeconds = duration.count();

        arquivo_saida << setw(20) << left << "Chave sorteada: " << setw(15) << left << chaveAtual 
        << setw(25) << right << "Número de interações: " << setw(10) << left << arv.numero_interacoes 
        << setw(45) << right << "Tempo de execução (Nanossegundos): " << setw(10) << left << fixed << setprecision(2) << durationInNanoSeconds << "\n";
    }

    
    arquivo_saida.close();

    return 0;
}

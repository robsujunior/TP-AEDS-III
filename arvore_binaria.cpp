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

struct Tiporeg
{
    int chave;
    int dado1;
    char dado2[1000];
};

struct No
{
    Tiporeg registro;
    No* esquerda;
    No* direita;
};

No* novoNo(Tiporeg pRegistro) {
    // Cria um novo nó na memória
    No* no = new No();

    // Define o registro do novo nó com o registro passado como parâmetro
    no->registro = pRegistro;

    // Inicializa os ponteiros da esquerda e direita como nulos, indicando que o novo nó é uma folha
    no->esquerda = nullptr;
    no->direita = nullptr;

    // Retorna o ponteiro para o novo nó criado
    return no;
}


struct ArvoreBinaria {
    No* raiz;               // Ponteiro para o nó raiz da árvore
    int numero_interacoes;  // Variável para contar o número de interações durante as operações

    // Função para inserir um novo nó na árvore
    No* inserir(No* no, Tiporeg registro) {
        // Se o nó atual é nulo, cria um novo nó com o registro fornecido
        if (no == nullptr) return novoNo(registro);

        // Se a chave do registro é menor que a chave do nó atual, insere na subárvore esquerda
        if (registro.chave < no->registro.chave)
            no->esquerda = inserir(no->esquerda, registro);
        // Se a chave do registro é maior que a chave do nó atual, insere na subárvore direita
        else if (registro.chave > no->registro.chave)
            no->direita = inserir(no->direita, registro);

        // Retorna o nó atual após a inserção
        return no;
    }

    // Função para buscar uma chave na árvore binária
    void Buscar(No* no, int chave) {
        // Se o nó é nulo, a chave não foi encontrada na árvore
        if (no == nullptr) {
            return;
        }
        // Se a chave é menor que a chave do nó atual, busca na subárvore esquerda
        else if (chave < no->registro.chave){
            // Incrementa o número de interações (comparações) realizadas durante a busca
            numero_interacoes++;
            // Chama a função de busca recursivamente na subárvore esquerda
            Buscar(no->esquerda, chave);
        }
        // Se a chave é maior que a chave do nó atual, busca na subárvore direita
        else if (chave > no->registro.chave){
            // Incrementa o número de interações (comparações) realizadas durante a busca
            numero_interacoes++;
            // Chama a função de busca recursivamente na subárvore direita
            Buscar(no->direita, chave);
        }
        // Se a chave é igual à chave do nó atual, a chave foi encontrada na árvore
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
    aux.dado1 = stoi(s.substr(pos + 1, s.length()));

    // Encontra a próxima posição do delimitador na string
    pos = s.find(delimiter, pos + 1);

    // Extrai a substring da posição após o segundo delimitador até o final da string e a converte para um array de caracteres, copiando para aux.dado2
    auxS = s.substr(pos + 1, s.length());
    strcpy(aux.dado2, auxS.c_str());

    // Retorna a estrutura Tiporeg com os dados extraídos da string
    return aux;
};

int main() {

    // Cria uma instância da estrutura ArvoreBinaria
    ArvoreBinaria arv;

    // Variáveis para leitura do arquivo e controle
    string linha, nomeArquivo;
    int tamanhoArquivo;

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

    ifstream arquivo("Arquivos de Entrada/" + nomeArquivo);

    // Verifica se o arquivo foi aberto corretamente
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return 1;
    }

    // Lê dados do arquivo e insere na árvore binária de busca
    while (getline(arquivo, linha)) {
        string linhaAux = linha;
        if (linhaAux != "") {
            // Converte a linha do arquivo para a estrutura Tiporeg e insere na árvore
            Tiporeg auxiliar = retornaTipoReg(linhaAux);
            arv.raiz = arv.inserir(arv.raiz, auxiliar);
        }
    }

    // Fecha o arquivo após a leitura
    arquivo.close();

    

    // Abre o arquivo de saída "arquivo_saida.txt"
    ofstream arquivo_saida("Arquivos de Saida/binaria/arquivo_saida_" + nomeArquivo);

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

    // Fecha o arquivo de saída
    arquivo_saida.close();

    return 0;
}

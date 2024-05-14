#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <cstring>
#include <algorithm>
#include <random>
#include <vector>
using namespace std;
using namespace chrono;

struct Tiporeg
{
    int chave;
    int dado1;
    char dado2[1000];
};

Tiporeg retornaTipoReg(string s) {
    Tiporeg aux;
    string auxS = s;
    string delimiter = " ";
    int pos = s.find(delimiter);

    // Extrai a chave da string e a converte para um inteiro
    aux.chave = stoi(s.substr(0, pos));

    // Extrai o dado1 da string e o converte para um inteiro
    aux.dado1 = stoi(s.substr(pos + 1, s.length()));
    
    // Encontra a próxima posição do delimitador
    pos = s.find(delimiter, pos + 1);
    
    // Extrai o dado2 da string e copia-o para o campo 'dado2' da estrutura
    auxS = s.substr(pos + 1, s.length());
    strcpy(aux.dado2, auxS.c_str());
    
    return aux;
}

int main() {

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

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;  // Exibe uma mensagem de erro se a abertura falhar
        return 1;  // Encerra o programa com código de erro
    }

    Tiporeg *dados = new Tiporeg[tamanhoArquivo];  // Aloca dinamicamente memória para um array de estruturas
    int index = 0;

    while (getline(arquivo, linha)) {
        string linhaAux = linha;
        if (linhaAux != "") {
            dados[index] = retornaTipoReg(linha);  // Converte a linha em uma estrutura e armazena no array
            index++;
        }
    }

    arquivo.close();  // Fecha o arquivo de entrada

    ofstream arquivo_saida("Arquivos de Saida/Pesquisa Sequencial/arquivo_saida_" + nomeArquivo);  // Abre arquivo de saída

    if (!arquivo_saida.is_open()) {
        cerr << "Erro ao abrir o arquivo de saída." << endl;  // Exibe mensagem de erro se a abertura do arquivo de saída falhar
        return 1;  // Encerra o programa com código de erro
    }
    

    for (int i = 0; i < 30; i++){
        int chaveAtual = chavesSorteadas[i];

        int numeroComparacoes = 0; // Iniciar o contador de comparações 

        auto start = high_resolution_clock::now(); // Inicia timer antes de realizar a busca

        //Compara a chave atual com cada chave do arquivo
        for(int j = 0; j < tamanhoArquivo; j++){
            numeroComparacoes++;
            if(dados[j].chave == chavesSorteadas[i]){
                break;
            }
        }

        auto end = high_resolution_clock::now(); // Finaliza timer

        auto duration = duration_cast<nanoseconds>(end - start); // Calcula tempo de execução

        double durationInNanoSeconds = duration.count();

        arquivo_saida << setw(20) << left << "Chave sorteada: " << setw(15) << left << chaveAtual 
        << setw(25) << right << "Número de interações: " << setw(10) << left << numeroComparacoes
        << setw(45) << right << "Tempo de execução (Nanossegundos): " << setw(10) << left << fixed << setprecision(10) << durationInNanoSeconds << "\n";
    }
    

    arquivo_saida.close();  // Fecha o arquivo de saída

    delete[] dados;  // Libera a memória alocada dinamicamente

    return 0;  // Encerra o programa com sucesso
}

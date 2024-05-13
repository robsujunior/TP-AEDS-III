import random
import string 

def gerar_char(): #Gera um char com 1000 caracteres aleatórios
    caracteres = string.ascii_letters
    char = ''.join(random.choice(caracteres) for _ in range(1000))
    return char

def gerar_numero(): #Gera um inteiro aleatório entre 1 e 100
    numero_aleatorio = random.randint(1,100)
    return numero_aleatorio


tamanho = int(input("Qual tamanho de arquivo você deseja criar? (Já vai ser criado ordenado e não ordenado): "))

chaves = [x for x in range (1,tamanho+1)] #Cria um vetor com a quantidade de chaves necessária

with open("tamanho" + str(tamanho) + "ordenado.txt", "w") as arquivo: #Cria um txt para armazenar os dados

    for chave in chaves: #Preenche as linhas do arquivo

        dado1 = gerar_numero() #Para cada linha vai ser gerado um número aleatório
        dado2 = gerar_char() #Para cada linha vai ser gerado um char de tamanho 1000 aleatório

        arquivo.write(str(chave) + " ") #Escreve a chave no começo da linha
        arquivo.write(str(dado1) + " ") #Escreve o primeiro dado
        arquivo.write(dado2) #Escreve o segundo dado
        arquivo.write("\n")

with open("tamanho" + str(tamanho) + "desordenado.txt", "w") as arquivo:
    random.shuffle(chaves) #Embaralha o vetor de chaves

    for chave in chaves: #Preenche as linhas do arquivo

        dado1 = gerar_numero() #Para cada linha vai ser gerado um número aleatório
        dado2 = gerar_char() #Para cada linha vai ser gerado um char de tamanho 1000 aleatório
    
        arquivo.write(str(chave) + " ") #Escreve a chave no começo da linha
        arquivo.write(str(dado1) + " ") #Escreve o primeiro dado
        arquivo.write(dado2) #Escreve o segundo dado
        arquivo.write("\n")



        
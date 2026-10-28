#include <bits/stdc++.h>
// Biblioteca bits importa todas as bibliotecas padrão do C++ (Vector, Iostream, etc).

using namespace std;
// Atalho para utilizar o namespace padrão (std).

/*
    O problema pede para distribuirmos N alunos em uma grade de X linhas por Y colunas.
    A principal "pegadinha" é a orientação: a numeração das carteiras começa no canto superior direito 
    e cresce da direita para a esquerda. 
    Para resolver isso sem complicar os laços 'for', o código usa um truque: 
    ele preenche a matriz da esquerda para a direita normalmente (como se a mesa 1 fosse a [0][0]), 
    mas na hora de imprimir na tela, ele imprime as colunas de trás para frente
*/

int main() {

    int N, X, Y;
    
    
    cin >> N >> X >> Y;
        
    int P = (X * Y) / N;
    // P é o "pulo" entre um aluno e outro. 
    // Como X e Y e N são inteiros, a divisão trunca automaticamente para baixo.
    // Exemplo: 9 lugares para 4 alunos = 9 / 4 = 2. O pulo será de 2 em 2.
    
    vector<vector<char>> vetor(X, vector<char>(Y, '.'));
    // Criação de uma matriz 2D (vetor de vetores) com X linhas e Y colunas.
    // Já inicializamos todas as posições com o caractere '.', representando carteiras vazias.
    
    int prox = 1;  
    // Armazena o índice da próxima carteira que deve receber um aluno. O primeiro aluno sempre senta no índice 1.
    int cont = 1;
    // Contador que simula o índice da carteira atual que estamos olhando.
    int alunos = 0;
    // Variável de controle para saber quantos alunos já sentaram.
    
    // Laço para percorrer e preencher a matriz (simulando a ordem normal de contagem 1, 2, 3...)
    for(int i = 0; i < X; i++){
        for(int j = 0; j < Y; j++){
            
            // Se a carteira atual (cont) for a carteira onde o próximo aluno deve sentar (prox)
            if(cont == prox){
                vetor[i][j] = 'A';  // Colocamos o aluno 'A'.
                prox += P;          // Calculamos a carteira do próximo aluno somando o pulo P.
                alunos++;           // Registramos que mais um aluno sentou.
            } 
            cont++; // Independentemente de ter sentado aluno ou não, avançamos o índice da carteira.
            
            // Otimização: se já sentamos todos os N alunos, paramos a contagem para não perder tempo de processamento.
            if(alunos >= N) break;
        }
        if(alunos >= N) break;
    }
    
    // Laço de impressão (Truque da Direita para a Esquerda)
    for(int i = 0; i < X; i++){
        // Em vez de imprimir do j = 0 até Y-1, nós iteramos do final (Y-1) até o 0.
        // Isso inverte visualmente a matriz, fazendo com que o índice 1 
        // que colocamos na posição [0][0] apareça no canto superior direito.
        for(int j = Y - 1; j >= 0; j--){
            cout << vetor[i][j];
        }
        cout << "\n"; // Quebra de linha ao fim de cada fileira.
    }
    
    return 0;
    
    /*
    Testando o passo a passo com o caso de entrada: 4 3 3
    N = 4, X = 3, Y = 3
    P = (3 * 3) / 4 = 9 / 4 = 2. (Pulo é 2)
    
    Temos 9 posições e os alunos sentarão nos índices: 1, 3, 5 e 7.
    O código vai colocar 'A' em vetor[0][0] (índice 1), vetor[0][2] (índice 3), vetor[1][1] (índice 5), vetor[2][0] (índice 7).
    
    Nossa matriz na memória ficará assim:
    A . A  (linha 0: ind 1, ind 2, ind 3)
    . A .  (linha 1: ind 4, ind 5, ind 6)
    A . .  (linha 2: ind 7, ind 8, ind 9)
    
    Ao imprimir de trás para frente (da última coluna para a primeira), o console exibe:
    A . A
    . A .
    . . A
    
    // Complexidade:
    // O(X * Y) - Tempo linear em relação ao tamanho da matriz. O algoritmo visita cada célula no máximo duas vezes (uma para preencher e outra para imprimir)
	// o que é extremamente eficiente e passa com folga no Timelimit de 1 segundo.
    */
}

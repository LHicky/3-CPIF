#include <bits/stdc++.h>
// Biblioteca bits importa bibliotecas padrão como Vector, String, Math e muitas outras.

using namespace std;
// Atalho para utilizar o namespace padrão (std).

// O exercício pede para encontrarmos a fileira mais distante onde o aluno ainda consiga ouvir o professor, 
// sabendo que o volume da voz diminui de forma linear a cada fileira.
// Trata-se de um problema matemático que pode ser resolvido de forma otimizada usando uma simples divisão (O(1)), 
// em vez de utilizar um loop iterativo para subtrair o som fileira por fileira.

int main() {

    int V, P, A;
    cin >> V >> P >> A;
    // Lendo os valores de entrada na exata ordem especificada pelo problema:
    // V = volume inicial da voz do professor (na primeira fileira);
    // P = quantidade de decibéis que o som perde a cada fileira de distância;
    // A = volume mínimo em decibéis necessário para o aluno entender a aula.

    int Fileira = (V - A) / P;
    // Para descobrir quantas fileiras podemos recuar, subtraímos o volume mínimo (A) do volume inicial (V).
    // Isso nos dá a "sobra" de decibéis. Dividindo essa sobra pela perda por fileira (P), 
    // obtemos o número de fileiras que o aluno pode se afastar.
    // Como utilizamos 'int', a divisão em C++ arredonda automaticamente para baixo (trunca), 
    // garantindo a fileira exata sem ultrapassar o limite audível.

    if (Fileira < 1) {
        cout << "Na mesa do professor!\n";
    }
    // O exercício detalha que, se não for possível ouvir o professor (ou seja, a conta der 0 ou negativo), 
    // devemos imprimir "Na mesa do professor!". 
    // Se o volume V for muito baixo desde o início, (V - A) resultará em um número negativo, 
    // a divisão por P fará com que 'Fileira' seja menor que 1, e o programa ativará essa condição.
    else {
        cout << Fileira << "\n";
    }
    // Caso a fileira calculada seja 1 ou maior, significa que existe uma posição válida na sala de aula, 
    // portanto imprimimos o valor da fileira limite.

    return 0;
    
    /*
    Testando os casos de entrada passo a passo:
    
    Caso 1:
    V = 50, P = 5, A = 30
    Fileira = (50 - 30) / 5
    Fileira = 20 / 5 = 4
    Como 4 < 1 é falso, o programa entra no 'else' e imprime 4.
    
    Caso 2:
    V = 67, P = 6, A = 7
    Fileira = (67 - 7) / 6
    Fileira = 60 / 6 = 10
    Como 10 < 1 é falso, o programa entra no 'else' e imprime 10.
    
    Caso 3:
    V = 20, P = 5, A = 30
    Fileira = (20 - 30) / 5
    Fileira = -10 / 5 = -2
    Como -2 < 1 é verdadeiro, o programa entra no 'if' e imprime "Na mesa do professor!".
    
    // Complexidade:
    // O(1) - Tempo constante. O algoritmo resolve o problema com uma única operação matemática direta,
	// independentemente do tamanho ou proporção dos números na entrada.
    */
}

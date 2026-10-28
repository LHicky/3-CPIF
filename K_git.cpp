#include <bits/stdc++.h>

using namespace std;

int maior = 0; // Variável global para armazenar o tamanho do maior palíndromo encontrado.

/*
    Este é o "nível boss" da competição... O problema pede o tamanho da maior 
    substring palíndroma (um bloco contínuo que se lê igual de trás pra frente)
    Como a string pode ter até 2000 caracteres, testar todas as combinações do zero 
    (força bruta) daria "Time Limit Exceeded" com certeza. 
    A solução clássica e eficiente para isso é usar Programação Dinâmica (DP) direto das anotações.
    A grande sacada da DP é: se eu já sei que a parte do meio de uma palavra é um palíndromo, 
    só preciso verificar se as letras das pontas são iguais!
    
*/

// Ninguém tentou essa mas era o esperado mesmo, tem que ter alguma pra fazer perder tempo msm

void palindromo(string s) {
    int n = s.size();
    
    // Se a string tiver tamanho 0 ou 1, ela inteira já é um palíndromo por padrão.
    if (n <= 1) {
        maior = n;
        return;
    }
    
    // Criamos uma matriz (tabela) DP de tamanho N x N preenchida com 'false'.
    // dp[i][j] será 'true' se a parte da string que começa no índice 'i' e termina no 'j' for um palíndromo.
    vector<vector<bool>> dp(n, vector<bool>(n, false));
    
    // Caso Base 1: Toda letra sozinha (tamanho 1) é um palíndromo dela mesma.
    for (int i = 0; i < n; i++) {
        dp[i][i] = true;
    }
    
    maior = 1; // Já sabemos que existe pelo menos um palíndromo de tamanho 1.

    // O 'tam' é o tamanho da janela que estamos testando (começando de janelas de tamanho 2 até N).
    for (int tam = 2; tam <= n; tam++) {
        // O 'i' é onde a janela começa.
        for (int i = 0; i <= n - tam; i++) {
            // O 'j' é onde a janela termina.
            int j = i + tam - 1;
            
            // A mágica da Programação Dinâmica acontece aqui:
            // Para ser palíndromo, a letra da ponta esquerda (s[i]) DEVE ser igual à da ponta direita (s[j]).
            // ALÉM DISSO, o meio entre elas também precisa ser um palíndromo.
            // O meio é dp[i + 1][j - 1] (que nós já processamos nos loops anteriores de menor tamanho
			// ou seja vamos crescendo a DP aos poucos e verificando).
            // A exceção é se tam == 2, porque aí não tem miolo, basta as duas letras serem iguais.
            if (s[i] == s[j] && (tam == 2 || dp[i + 1][j - 1])) {
                dp[i][j] = true; // Marca na tabela que encontramos um palíndromo.
                
                // Se esse novo palíndromo for maior que o nosso recorde atual, atualizamos o 'maior'.
                if (tam > maior) {
                    maior = tam;
                } 
            }
        }
    }
}

int main() {

    string s;
    cin >> s;
    // Lê a string binária corrompida, composta exclusivamente por 0 e 1
    
    palindromo(s);
    
    // Imprime o tamanho máximo encontrado e quebra a linha
    cout << maior << "\n";
    
    return 0;
    
    /*
    Testando o passo a passo com o Caso de Exemplo 1
    String S = "10010101"
    Tamanho N = 8
    
    Tamanho 1: dp[0][0], dp[1][1]... todos recebem true. maior = 1.
    Tamanho 2: O loop testa vizinhos. Em "1001...", ele testa s[1]=='0' e s[2]=='0'.
               São iguais e tam==2, então dp[1][2] = true. maior = 2.
    Tamanho 3: Testa trincas. No final da string temos "010", s[4]=='0' e s[6]=='0'. O meio é s[5]=='1'.
               Como dp[5][5] é true e s[4]==s[6], dp[4][6] = true. maior = 3.
    ...
    Tamanho 5: Ele testa o bloco "10101" (índices 3 a 7).
               s[3] == '1' e s[7] == '1'.
               O miolo é "010" (índices 4 a 6). 
               Como nós já verificamos que dp[4][6] é true no passo de tam=3,
               imediatamente marcamos dp[3][7] = true sem testar tudo de novo. maior = 5.
               
    Ao final, nenhum palíndromo maior que 5 é encontrado na tabela.
    Saída = 5.
    
    // Complexidade:
    // O(N^2) - Tempo quadrático. Temos dois laços aninhados: um para o tamanho da janela 
    // e outro para deslizar a janela pela string. Como N é no máximo 2000
    // N^2 resulta em até 4.000.000 de operações.
    // Em C++, isso roda em poucos milissegundos, passando com muita folga no limite de tempo de 2.0s do problema
    */
}

#include <bits/stdc++.h>
// A biblioteca bits importa todas as ferramentas padrão do C++, como vector, string, map e sort.

using namespace std;

/*
    O problema exige que a distribuição dos LEDs seja feita na ordem alfabética dos alunos.
    As cores são distribuídas em sequência e, quando acabam, recomeçam da primeira cor (repetição circular).
    Para resolver isso de forma elegante, podemos ordenar a lista de nomes, usar um "mapa" (dicionário)
    para atrelar o nome do aluno à sua cor, e usar o operador de resto da divisão (%) para o ciclo de cores.
*/

int main() {

    string saida;
    int C, N, M;
    
    // Lendo a quantidade de cores disponíveis.
    cin >> C;

    vector<string> cores(C);
    for(int i = 0; i < C; i++) {
        cin >> cores[i];
        // Armazena a sequência fixa de cores da caixa.
    }

    // Lendo a quantidade total de alunos na sala.
    cin >> N;
    
    vector<string> nomes(N);
    for(int i = 0; i < N; i++) {
        cin >> nomes[i];
        // Lê os nomes dos alunos exatamente na ordem em que se matricularam (desordenada).
    }

    // A mágica da ordenação:
    sort(nomes.begin(), nomes.end());
    // A função sort() organiza o vetor 'nomes' em ordem alfabética crescente, 
    // cumprindo a regra rigorosa do professor Alexandre.

    map<string, string> mapa;
    // O 'map' funciona como um dicionário. Ele vai criar uma relação direta e rápida: mapa["Nome do Aluno"] = "Cor".
    
    for(int i = 0; i < N; i++) {
        mapa[nomes[i]] = cores[i % C];
        // Aqui está o grande truque do ciclo circular!
        // O operador '%' (módulo) retorna o resto da divisão. 
        // Se temos 3 cores (C = 3), o índice 'i % 3' vai gerar a sequência: 0, 1, 2, 0, 1, 2, 0...
        // Assim, nunca acessamos um índice fora do vetor 'cores' e a distribuição se repete perfeitamente.
    }

    // Lendo a quantidade de alunos que queimaram o LED na última aula.
    cin >> M;

    string nome;
    for(int i = 0; i < M; i++) {
        cin >> nome;
        // Lê o nome do aluno que foi expulso.

        // Concatena a string de saída no formato exato exigido pelo problema.
        // Usamos mapa[nome] para buscar instantaneamente qual foi a cor atrelada a esse aluno na distribuição.
        saida += "Vamos ver se dessa vez a gente acerta, ";
        saida += nome;
        saida += ", vamos evitar o LED ";
        saida += mapa[nome];
        saida += "\n";
    }

    // Imprime toda a saída de uma vez no final.
    cout << saida;
    
    return 0;
    
    /*
    Testando o passo a passo com o Caso de Exemplo 1:
    
    C = 3 Cores: {Vermelho, Azul, Verde}
    N = 4 Alunos: {Matheus, Vitor, Thierry, Henrique}
    
    1. O sort() organiza os alunos em ordem alfabética:
       {Henrique, Matheus, Thierry, Vitor}
       
    2. O laço de mapeamento usa (i % 3) para distribuir as cores:
       i = 0 -> Henrique recebe cores[0 % 3 = 0] -> Vermelho
       i = 1 -> Matheus recebe cores[1 % 3 = 1]  -> Azul
       i = 2 -> Thierry recebe cores[2 % 3 = 2]  -> Verde
       i = 3 -> Vitor recebe cores[3 % 3 = 0]    -> Vermelho
       
    3. Quando o professor chama os alunos M = 2 {Matheus, Thierry}:
       - Busca Matheus no map: retorna "Azul". Imprime a frase com Azul.
       - Busca Thierry no map: retorna "Verde". Imprime a frase com Verde.
    
    
    // Complexidade:
    // O(N log N) - A parte mais custosa do algoritmo é o sort() para ordenar os N nomes.
    // A inserção e busca no map também custam O(log N) por aluno. 
    // Como N tem no máximo 1000, o tempo total será minúsculo, muito abaixo do limite de 1 segundo.
    */
}

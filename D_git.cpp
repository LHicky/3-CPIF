#include <bits/stdc++.h>
// A biblioteca bits inclui tudo o que é padrão no C++.

using namespace std;

/*
    O problema descreve ciclos de tempo repetitivos. Um ciclo completo consiste em dar aula por N minutos 
    e descansar por X minutos. 
    A duração de um ciclo completo é (N + X) minutos.
    Para não fazer um loop que subtrai o tempo aos poucos (o que daria "Time Limit Exceeded" devido ao tamanho de A), 
    usamos matemática básica para descobrir quantos ciclos completos cabem no tempo total A, e depois olhamos para a sobra.
*/

int main() {
    
    // As restrições do PDF indicam que o tempo total A pode chegar até 10^18.
    // Um 'int' normal de 32 bits só suporta valores até ~1 * 10^8. 
    // Usar 'long long' (64 bits) é obrigatório para evitar o estouro de memória (Overflow).
    long long N, X, A;
    
    cin >> N >> X >> A;
    // Lendo os valores:
    // N = Tempo de aula antes de ficar exausto
    // X = Tempo de cochilo no carro
    // A = Duração total da aula
    
    // Passo 1: Quantos ciclos completos aconteceram?
    // A / (N + X) pega o tempo total e divide pelo tamanho de um ciclo. 
    // Como queremos saber o tempo de AULA nesses ciclos, multiplicamos esse número de ciclos por N.
    long long total = (A / (N + X)) * N;
    
    // Passo 2: Qual foi a "sobra" de tempo após todos esses ciclos completos?
    // O operador % (módulo) nos dá o resto da divisão. 
    A %= (N + X);
    
    // Passo 3: Avaliar a sobra.
    // O professor vai tentar dar aula durante toda essa sobra (A). 
    // Mas ele só aguenta dar aula por N minutos seguidos.
    // Portanto, o tempo que ele dará de aula na sobra será o menor valor entre N e a própria sobra A.
    // A função min(N, A) faz exatamente isso.
    total += min(N, A);
    
    // Imprime o resultado final e quebra a linha
    cout << total << "\n";
    
    return 0;
    
    /*
    Testando o passo a passo com o Caso de Exemplo 1:
    N = 45, X = 20, A = 120
    
    Tamanho de um ciclo: N + X = 45 + 20 = 65 minutos.
    
    Passo 1: 
    Quantos ciclos de 65 cabem em 120? 
    120 / 65 = 1 (truncado).
    Tempo de aula nesse 1 ciclo: 1 * 45 = 45 minutos.
    (total = 45)
    
    Passo 2:
    Qual a sobra de tempo na aula?
    A % 65 = 120 % 65 = 55 minutos restantes.
    
    Passo 3:
    O professor consegue dar aula por toda a sobra (55 mins)? 
    Não, o limite dele é N = 45 mins.
    Ele dá aula por min(45, 55) = 45 minutos. E depois vai dormir os 10 finais.
    Adicionamos 45 ao total: 45 + 45 = 90.
    
    Saída = 90.
    
    // Complexidade:
    // O(1) - Tempo constante. Graças ao uso da divisão e do módulo, não importa se A é 100 ou 10^18, 
    // o programa sempre fará apenas 3 operações matemáticas simples e imprimirá a resposta instantaneamente.
    */
}

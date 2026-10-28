#include <bits/stdc++.h>
// Importa todas as bibliotecas padrão, incluindo <iomanip> que usaremos para as casas decimais.

using namespace std;

/*
    A chave para resolver este problema é observar a figura e notar a "Semelhança de Triângulos".
    A linha pontilhada vermelha (o sinal de rádio) forma um triângulo retângulo gigante com a Torre e o chão.
    Dentro desse triângulo gigante, há um triângulo menor formado pelo topo do morro e o chão.
    
    Pela regra de proporção (semelhança):
    (Altura Maior) / (Base Maior) = (Altura Menor) / (Base Menor)
    Ht / (Dt + Dm) = Hm / Dm;
    
    Isolando o Ht (Altura da Torre), temos a nossa fórmula:
    Ht = Hm * (Dt + Dm) / Dm;
    
    
    Outra maneira (e melhor na minha opnião) de encontrar é pela hipotenusa
    catetoOposto / catetoAdjacente = tangente
    Como temos dois triângulos temos que pela figura
    Dm / Hm = tan(x);
    Como ambos os triangulos compartilham a reta, eles tem exatamente o mesmo ângulo.
    (Dt + Dm) / Ht = tan(x);
    Não precisamos saber a tan(x) como são igualdades podemos substituir
    Então temos que:
    Dm / Hm = (Dt + Dm) / Ht;
    Podemos isolar a altura:
    Ht = (Dt + Dm) * Hm / Dm
    
*/

int main() {
    
    // Como os valores podem ter casas decimais, precisamos usar 'double' (ponto flutuante de precisão dupla).
    double Dm, Hm, Dt;
    
    // Lendo os valores na ordem da entrada: Dm, Hm e Dt
    cin >> Dm >> Hm >> Dt;
    
    // Aplicando a fórmula de proporção deduzida acima
    double Ht = (Hm * (Dt + Dm)) / Dm;
    
    // O PDF exige que a saída tenha exatamente 2 casas decimais.
    // fixed e setprecision(2) garantem que qualquer 'cout' a partir de agora obedeça a essa regra de formatação.
    cout << fixed << setprecision(2);
    
    // Verificando a restrição de altura do professor Renato
    if (Ht < 1000.00) {
        // Se a antena tiver menos de 1000 metros, imprime o valor normal em metros.
        cout << Ht << "\n";
    } else {
        // Se for 1000 metros ou mais, precisamos converter para quilômetros (dividindo por 1000)
        // e imprimir junto com a frase de espanto
        cout << (Ht / 1000.0) << " km. Antena de quilometro ? E quem instala isso ai ?\n";
    }
    
    return 0;
    
    /*
    Testando o passo a passo com o Caso de Exemplo 2:
    Dm = 500.0, Hm = 2000.0, Dt = 3000.0
    
    Base Maior (distância total da torre ao cliente) = Dt + Dm = 3000.0 + 500.0 = 3500.0 metros.
    
    Aplicando a fórmula:
    Ht = 2000.0 * (3500.0) / 500.0
    Ht = 7000000.0 / 500.0
    Ht = 14000.0 metros
    
    Como 14000.0 é maior que 1000.00, o programa entra no 'else'.
    Converte para km: 14000.0 / 1000.0 = 14.00 km.
    
    Saída gerada: "14.00 km. Antena de quilometro ? E quem instala isso ai ?"
    
    // Complexidade:
    // O(1) - Tempo constante. Assim como o problema D, a matemática resolve tudo em uma única expressão, 
    // sem loops, executando de maneira instantânea.
    */
}

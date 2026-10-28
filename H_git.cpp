#include <bits/stdc++.h>
// Biblioteca padrão contendo todos os recursos básicos do C++.

using namespace std;

/*
    Este problema é uma clássica armadilha de maratona!
    Primeira pegadinha: O cálculo do "fator S" usando o prontuário.
    Como a fórmula da corrente é I = V / R, multiplicar ambos por S resulta em (V * S) / (R * S) = I,
    o que anula o S matematicamente. Ou seja, a string BI não serve para nada além de assustar e fazer perder tempo XD
    
    Segunda pegadinha: O arredondamento customizado do professor Shigueo
    Funções normais como setprecision() ou round() do C++ não funcionam aqui, porque as regras dele
    são muito específicas (limiar de > 3 na casa C+1 exata e truncamento do resto)
    Para evitar problemas de precisão e regras obscuras de ponto flutuante, a solução de Mestre 
    é simular a divisão na mão (como fazemos no papel), extraindo dígito por dígito como caracteres.
*/

/*
/*
    ERROS COMUNS QUE DERRUBARAM OS COMPETIDORES NESSE PROBLEMA:

    Muitos participantes caíram em armadilhas clássicas do C++ ao tentar resolver
    esse problema usando tipos de ponto flutuante (float/double) ou funções prontas.
    Aqui estão os principais motivos que geraram "Wrong Answer":

    1. A Ilusão do setprecision() e do arredondamento padrão:
       As funções nativas do C++ usam o arredondamento padrão da matemática 
       (arredonda para cima se o dígito for >= 5 e olha para a infinidade das casas). 
       A regra customizada exigia arredondar para cima APENAS se o dígito fosse > 3. 
       Além disso, a regra mandava olhar *estritamente* para a casa C+1 e ignorar o resto.
	   Funções prontas simplesmente não obedecem a essa regra que foi feita justamentate pra evitarem o setprecision.
       
    2. O Limite de Precisão do 'float':
       Declarar as variáveis de tensão e resistência como 'float' foi um erro fatal. 
       O 'float' no C++ tem uma precisão máxima de apenas ~7 casas decimais. 
       Como o problema pedia até C = 10,
	   o float começava a inventar números na memória nas últimas casas (ex: 3.1415927410...), estragando a verificação.

    3. Indexação Cega e Problemas com ASCII:
       Ao manipular a string do resultado, muitos tentaram pegar a casa decimal fixando 
       um índice manual (ex: 'numero[C + 1]'). Isso quebra porque o tamanho da parte 
       inteira varia (ex: "3.14" tem o ponto no índice 1; "355.14" tem o ponto no índice 3).
       
	4. Outro erro letal foi comparar o caractere da string diretamente com 
       um número inteiro (ex: 'numero[i] <= 3'). Isso compara o valor ASCII do caractere 
       (o caractere '4' vale 52) com o inteiro 3, o que sempre dá falso. O certo seria 
       comparar com o caractere (numero[i] <= '3').
    */
*/


int main() {

    string BI;
    long long V, R;
    int C;
    
    cin >> BI >> V >> R >> C;
        
    // Passo 1: Divisão da parte inteira.
    long long inteiro = V / R;   // Pega a porção inteira do resultado, antes da vírgula.
    long long resto = V % R;     // Pega o resto da divisão, que será a base para gerarmos as casas decimais.
    
    string decimais = "";
    
    // Passo 2: Gerar as casas decimais simulando a divisão manual (algoritmo da chave).
    // Vamos gerar exatamente C + 1 casas, pois o professor exige olhar "estritamente para o dígito na posição C+1"
    for (int i = 0; i <= C; i++) {
        resto *= 10;                         	// "Desce o zero" como fazemos no papel.
        decimais += to_string(resto / R);     	// Extrai apenas aquele dígito decimal e adiciona na string.
        resto %= R;                          	// Atualiza o resto para a próxima iteração.
    }
    
    bool um = false; // Flag (vai-um) que indicará se precisaremos somar +1 à casa anterior no arredondamento.
    
    // Passo 3: Aplicar o Método Shigueo de arredondamento
    // Verificamos a última posição gerada (índice C, que representa a casa C+1).
    if (decimais[C] > '3') {
        um = true; // Se o dígito for maior que 3, a regra manda somar +1 à casa decimal anterior e atualiza
    }
    
    // Após a verificação, apagamos o último caractere (a casa C+1), pois a saída final deve ter exatamente C casas
    decimais.pop_back();
    
    // Passo 4: Propagação do arredondamento (Efeito Cascata).
    if (um) {
        // Se precisamos somar +1, percorremos os decimais de trás para frente.
        for (int i = C - 1; i >= 0; i--) {
            if (decimais[i] == '9') {
                decimais[i] = '0'; // 9 + 1 = 10. A casa vira '0' e o 'vai-um' continua subindo.
                um = true;
            } else {
                decimais[i]++;     // Se não for '9', simplesmente soma 1 e finaliza o arredondamento.
                um = false;
                break;             // Encerra o loop, pois a cascata parou.
            }
        }
    }
    
    // Passo 5: Propagação para a parte inteira.
    // Se as casas decimais eram formadas inteiramente por noves (ex: 1.99) e sofreram arredondamento (1.99 + 0.01),
    // o 'um' sobrevive até o final. Nesse caso, a parte inteira precisa ser incrementada.
    if (um) {
        inteiro++;
    }
    
    // Imprime o valor da corrente I com exatamente C casas decimais, concatenando a parte inteira, o ponto e a string.
    cout << inteiro << "." << decimais << "\n";
    
    return 0;
    
    /*
    Testando o passo a passo com o Caso de Exemplo 1:
    BI = "BI7823419" (Ignorado no cálculo).
    V = 355 (Tensão base), R = 113 (Resistência base), C = 4 (Quantidade de casas decimais exigidas).
    
    Passo 1 (Inteiro):
    inteiro = 355 / 113 = 3.
    resto = 355 % 113 = 16.
    
    Passo 2 (Decimais):
    O loop roda C+1 vezes (5 vezes).
    1) resto = 16 * 10 = 160.  Dígito = 160 / 113 = 1. decimais = "1".    		Novo resto = 47.
    2) resto = 47 * 10 = 470.  Dígito = 470 / 113 = 4. decimais = "14".   		Novo resto = 18.
    3) resto = 18 * 10 = 180.  Dígito = 180 / 113 = 1. decimais = "141".  		Novo resto = 67.
    4) resto = 67 * 10 = 670.  Dígito = 670 / 113 = 5. decimais = "1415". 		Novo resto = 105.
    5) resto = 105 * 10 = 1050. Dígito = 1050 / 113 = 9. decimais = "14159". 	Novo resto = 33.
    Ao fim, decimais = "14159".
    
    Passo 3 (Regra Shigueo):
    A casa C+1 (índice 4) é '9'.
    Como '9' > '3', o arredondamento (um = true) é acionado.
    pop_back remove o '9'. decimais = "1415".
    
    Passo 4 (Propagação):
    A última casa da string agora é '5'.
    Como temos "um = true", somamos 1 ao '5', que vira '6'.
    Como '5' não era '9', o "vai-um" zera (um = false) e o loop é interrompido.
    decimais = "1416".
    
    Passo 5 (Parte Inteira):
    "um" é false, o inteiro permanece 3.
    
    Resultado Final impresso:
    3.1416
    
    // Complexidade:
    // O(C) - Tempo linear em relação ao número de casas decimais. Como C é no máximo 10,
    // o algoritmo fará no máximo 11 repetições no cálculo, sendo incrivelmente eficiente e superando 
    // qualquer problema de precisão (overflow de precisão) das bibliotecas nativas matemáticas.
    */
}

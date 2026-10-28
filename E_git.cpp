#include <bits/stdc++.h>
// A biblioteca bits inclui todas as ferramentas padrão, como set, string, e stringstream.

using namespace std;

/*
    Este problema pede que a gente atue como um analisador léxico básico (um "mini compilador") 
    para encontrar infrações às regras do professor Valtemir. 
    O desafio aqui não é a matemática, mas sim o processamento de texto (strings). 
    Como o código pode ter tabulações e vários espaços, a melhor forma de extrair as palavras 
    é lendo a linha inteira e quebrando ela palavra por palavra.
*/

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // Otimização padrão de leitura e escrita.

    int L;    
    string linha;
    
    // Um 'set' (conjunto) armazena valores únicos e permite buscas extremamente rápidas.
    // Vamos guardar as palavras que geram infrações diretas.
    // O PDF garante que "break" e "continue" sempre terminam colados com ponto e vírgula, 
    // e que "return" é seguido de espaço.
    set <string> proibido;
    proibido.insert("break;");
    proibido.insert("return");
    proibido.insert("continue;");

    cin >> L;
    cin.ignore();
    // cin.ignore() é crucial aqui! O 'cin >> L' lê o número, mas deixa o "Enter" (quebra de linha \n) solto no buffer.
    // Se não usarmos o ignore(), o primeiro 'getline' vai ler esse Enter vazio e pular a primeira linha real de código.
    
    int cont = 0;
    // Contador total de erros

    bool achouReturn = false;
    // Variável para controlar a Regra 4: o primeiro return é liberado, os próximos são erros
    
    // Lendo as L linhas de código do aluno
    for(int i = 0; i < L; i++){
        getline(cin, linha);
        // Lê a linha inteira, não importando quantos espaços existam no meio.
        
        stringstream ss(linha);
        // O stringstream transforma a linha (que é uma string única) em um "fluxo" de palavras.
        // Ele automaticamente ignora espaços extras e tabulações, entregando palavra por palavra.
        
        string palavra;
        string palavraAnterior = "";
        
        // Enquanto houver palavras válidas para extrair da linha atual...
        while(ss >> palavra){
            
            // Regra 3: Verifica se a palavra atual é "if" e a imediatamente anterior foi "else"
            if(palavra == "if" && palavraAnterior == "else"){
                cont++;
            }
            else{
                // Se não for um "else if", verificamos se a palavra está na nossa lista de proibidas.
                // proibido.count(palavra) retorna 1 se a palavra existir no set, e 0 se não existir.
                if(proibido.count(palavra)){
                    
                    if(palavra == "return"){
                        // Regra 4: Apenas um return é permitido
                        if(achouReturn)
                            cont++; // Se já achou um antes, este é um erro.
                        else
                            achouReturn = true; // Marca que o primeiro return (gratuito) foi usado.
                    }
                    else{
                        // Se caiu aqui, é "break;" ou "continue;" (Regras 1 e 2). É erro direto
                        cont++;
                    }
                }
            }
            
            // Atualiza a palavra anterior para a próxima iteração do loop.
            palavraAnterior = palavra;
        }
    }
    
    // Impressão do resultado seguindo estritamente as regras de saída[cite: 39].
    if(cont == 0){
        cout << "Valtemir sorri\n";
    }
    else{
        cout << "Bitolou! " << cont << " erro(s) encontrado(s)\n";
    }
    
    return 0;
    
    /*
    Testando o passo a passo com o Caso de Exemplo 1:
    Linha 1 a 4: "int baloes = 0;", etc... Nenhuma palavra proibida.
    Linha 5: "break;" -> Está no set proibido! Não é return. Adiciona 1 ao cont (cont = 1)
    Linha 6: "} else if (baloes == 1) {" -> Extrai "}", depois "else", depois "if". 
             Quando extrai o "if", verifica que palavraAnterior é "else". Adiciona 1 ao cont (cont = 2)
    Linha 7: "return 0;" -> Extrai "return". É proibido, mas é o primeiro (achouReturn era false).
             Muda achouReturn para true. Não soma erro.
    Linha 8 a 10: Processa chaves e acréscimos sem erros.
    Linha 11: "return 1;" -> Extrai "return". Está no set. Porém, achouReturn já é true! 
              Adiciona 1 ao cont (cont = 3).
              
    Fim do código. Cont = 3. 
    Imprime "Bitolou! 3 erro(s) encontrado(s)".
    
    // Complexidade:
    // O(L * W) - Onde L é o número de linhas e W é o máximo de palavras por linha. 
    // Como L vai só até 500 e as linhas até 200 caracteres, roda quase instantaneamente. 
    // O acesso ao set é O(log K), o que mantém tudo muito rápido e seguro para o Timelimit de 1 segundo.
    */
}

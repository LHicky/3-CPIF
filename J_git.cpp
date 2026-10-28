#include <bits/stdc++.h>

using namespace std;

// Array global para armazenar a quantidade de dias de cada mês em um ano normal
// Colocamos um '0' na posição 0 para que os índices batam exatamente com os meses 
// (ex: diasMes[1] = 31 para Janeiro, diasMes[2] = 28 para Fevereiro, etc.)
int diasMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// Função para verificar se um ano é bissexto seguindo as regras exatas do calendário Gregoriano
bool bissexto(int ano){
    if(ano % 4 == 0){
        // Se for divisível por 400, é bissexto com certeza
        if(ano % 400 == 0){
            return true;
        }
        // Se for divisível por 100 (mas não por 400), NÃO é bissexto
        if(ano % 100 == 0){
            return false;
        }
        // Divisível por 4, mas não por 100, é bissexto
        return true;
    }
    return false; // Não divisível por 4, não é bissexto.
}

// O '&' comercial significa "Passagem por Referência". 
// Isso quer dizer que qualquer alteração feita em 'dia', 'mes' e 'ano' dentro desta função 
// irá alterar diretamente as variáveis originais lá na função main().
void avancarDia(int &dia, int &mes, int &ano) {
    dia++; // Avança um dia.
    
    int maxDias = diasMes[mes]; // Descobre o limite de dias do mês atual.
    
    // Tratamento especial para Fevereiro em anos bissextos.
    if(mes == 2 && bissexto(ano)) {
        maxDias = 29;
    }
    
    // Se o dia ultrapassou o limite do mês, viramos o mês.
    if(dia > maxDias){
        dia = 1;
        mes++;
        // Se o mês ultrapassou 12 (Dezembro), viramos o ano. Bem simples, sem segredo.
        if(mes > 12){
            mes = 1;
            ano++;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string inicial, final, atual;
    
    // Lê as três datas. Como elas não têm espaços (formato DD/MM/AAAA), o cin lê perfeitamente
    cin >> inicial >> final >> atual;
    
    // Convertendo as strings para inteiros.
    // substr(posição_inicial, quantidade_de_caracteres) extrai pedaços da string.
    // stoi() converte esse pedaço de texto em um número inteiro (String TO Integer).
    int diaI = stoi(inicial.substr(0, 2));
    int mesI = stoi(inicial.substr(3, 2));
    int anoI = stoi(inicial.substr(6, 4));
    
    int diaF = stoi(final.substr(0, 2));
    int mesF = stoi(final.substr(3, 2));
    int anoF = stoi(final.substr(6, 4));
    
    int diaA = stoi(atual.substr(0, 2));
    int mesA = stoi(atual.substr(3, 2));
    int anoA = stoi(atual.substr(6, 4));
    
    int totalDias = 0;
    
    // Passo 1: Descobrir o prazo original.
    // Enquanto a data inicial não for exatamente igual à data final, avançamos dia após dia.
    while(diaI != diaF || mesI != mesF || anoI != anoF) {
        avancarDia(diaI, mesI, anoI); // Como passamos por referência, diaI, mesI e anoI são atualizados.
        totalDias++; // Contamos quantos dias se passaram.
    }
    
    // Passo 2: Aplicar o prazo à nova data de postagem.
    // Avançamos a data "atual" a mesma quantidade de dias calculada acima.
    while(totalDias > 0) {
        avancarDia(diaA, mesA, anoA);
        totalDias--;
    }
    
    // Passo 3: Formatação da saída.
    // setw(2) define que o número ocupará sempre 2 espaços.
    // setfill('0') preenche os espaços vazios com zero à esquerda (ex: dia 5 vira "05").
    // Isso garante o formato DD/MM/AAAA exigido pelo problema
    cout << setw(2) << setfill('0') << diaA << "/" 
         << setw(2) << setfill('0') << mesA << "/" 
         << setw(4) << setfill('0') << anoA << "\n";
         
    return 0;
    
    /*
    Testando o passo a passo com o Caso de Exemplo 2:
    Abertura original: 28/02/2023
    Fechamento original: 01/03/2023
    Data atual: 28/02/2024
    
    1. Loop de descobrimento de prazo:
       - Ano de 2023 NÃO é bissexto (2023 % 4 != 0)
       - O limite de fevereiro é 28 dias.
       - Chamamos avancarDia(28, 2, 2023). 
       - Como dia(28) + 1 = 29 > maxDias(28), o dia vira 1 e o mês vira 3.
       - As datas se igualam (01/03/2023 == 01/03/2023). 
       - totalDias = 1. O prazo da tarefa é de 1 dia!
       
    2. Loop de aplicação do prazo:
       - Vamos avançar 1 dia a partir da data atual (28/02/2024).
       - Ano de 2024 É bissexto (2024 % 4 == 0 e 2024 % 100 != 0)
       - O limite de fevereiro passa a ser 29 dias
       - Chamamos avancarDia(28, 2, 2024).
       - Como dia(28) + 1 = 29, que NÃO é maior que o limite (29), apenas o dia avança
       - A nova data calculada é 29/02/2024.
       
    O programa imprime 29/02/2024.
    Imprime bem na data bissexto
    
    // Complexidade:
    // O(D) - Onde D é a diferença em dias entre as duas datas originais. 
    // Como os anos variam de 1000 a 3000, a diferença máxima seria de cerca de 2000 anos, 
    // o que equivale a uns 730.000 dias. Um loop de 730 mil iterações executa quase instantaneamente em C++.
    */
}

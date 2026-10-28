#include <bits/stdc++.h>
// Biblioteca padrão contendo todos os recursos básicos do C++.

using namespace std;

/*
    Neste problema, precisamos organizar arquivos em um disquete de exatos 10.240 bytes
    O grande desafio é a ordenação com múltiplos critérios (a lógica rigorosa do professor Dú)
    1º Prioridade (do maior para o menor)
    2º Ordem de chegada (do menor índice para o maior, caso as prioridades empatem)
    
    Para não nos perdermos com vários vetores separados (um para tamanho, outro para prioridade, etc.), 
    criamos uma 'struct', que agrupa todas as informações de um único arquivo no mesmo lugar.
*/

struct arquivo{
    int ordem;
    int tamanho;
    int prioridade;
    
    // O pulo do gato: Sobrecarga do operador '<' (Menor que).
    // Quando pedirmos para a função sort() ordenar nosso vetor de arquivos, ela não sabe como fazer isso.
    // Com esse bloco, nós falamos para o sort(): Comparar dois arquivos (o atual e o 'outro').
    bool operator<(const arquivo& outro) const{
        
        // Regra 1: Se as prioridades forem diferentes, o maior vem primeiro
        if(prioridade != outro.prioridade)
            return prioridade > outro.prioridade ;
            
        // Regra 2: Se as prioridades empatarem, o que apareceu primeiro na lista original vem primeiro
        return ordem < outro.ordem;
    }
};

int main() {
    
    int N;
    cin >> N;
    // Lendo a quantidade total de arquivos na lista
    
    vector <arquivo> arquivos (N);
    // Criamos um vetor do nosso tipo customizado 'arquivo'.
    
    int total = 10240;
    // Capacidade máxima fixa do disquete (10kb)
    
    for(int i = 0; i < N; i++){
        cin >> arquivos[i].prioridade;
        cin >> arquivos[i].tamanho;
        // Os arquivos são numerados com índices de 1 até N, na ordem em que aparecem
        arquivos[i].ordem = i + 1; 
    }
    
    // A mágica da ordenação:
    sort(arquivos.begin(), arquivos.end());
    // Neste momento, o C++ vai olhar para a nossa 'struct' e usar as regras que definimos 
    // lá em cima para deixar os arquivos exatamente na ordem que o professor Dú tentará salvar.
    
    int cont = 0;
    string saida = "";
    bool first = true; // Variável de controle para não colocar um espaço antes do primeiro número impresso.
    
    // Regra 3: Tentar salvar os arquivos na ordem estabelecida
    for(int i = 0; i < arquivos.size(); i++){
        
        // Se o arquivo couber no espaço que sobrou, ele é salvo
        if(arquivos[i].tamanho <= total){
            total -= arquivos[i].tamanho; // Subtrai o espaço consumido.
            cont++; // Contabiliza que mais um arquivo foi salvo.
            
            // Formatando a string com os índices originais separados por espaço
            if(!first) saida += " ";
            saida += to_string(arquivos[i].ordem);
            first = false;
        }
        // Se não couber, o 'if' é ignorado e o laço simplesmente pula para o próximo arquivo
    }
    
    // Verificação da saída:
    if(cont == N){
        // Se o contador for igual a N, o professor conseguiu salvar todos os arquivos
        cout << "CE EH DOIDO MEU! Coube tudo!\n";
    }
    else{
        // Caso pelo menos um arquivo tenha ficado de fora
        cout << "P#TA MERDA! VAI A MERDA! Coube ";
        cout << cont;
        cout << " arquivos!\n";
        cout << saida << "\n"; // Imprime a lista dos índices salvos formatada
    }

    return 0;
    
    /*
    Testando o passo a passo com o Caso de Exemplo 2
    N = 5
    Arquivos originais e índices:
    1: P=10, S=6000
    2: P=20, S=8000
    3: P=5,  S=2000
    4: P=20, S=2000
    5: P=20, S=200
    
    Após o sort(), usando a nossa regra de prioridade e ordem, o vetor fica:
    (Empate de prioridade 20, decidimos pela ordem menor)
    1º -> Índice 2 (P=20, S=8000)
    2º -> Índice 4 (P=20, S=2000)
    3º -> Índice 5 (P=20, S=200)
    4º -> Índice 1 (P=10, S=6000)
    5º -> Índice 3 (P=5,  S=2000)
    
    Simulando a gravação (Espaço inicial = 10240):
    - Tenta salvar Arquivo 2 (S=8000). Cabe? Sim. Sobra 2240. (Salvos: 2)
    - Tenta salvar Arquivo 4 (S=2000). Cabe? Sim. Sobra 240.  (Salvos: 2, 4)
    - Tenta salvar Arquivo 5 (S=200).  Cabe? Sim. Sobra 40.   (Salvos: 2, 4, 5)
    - Tenta salvar Arquivo 1 (S=6000). Cabe? Não. Sobra 40.   (Ignora)
    - Tenta salvar Arquivo 3 (S=2000). Cabe? Não. Sobra 40.   (Ignora)
    
    Foram salvos 3 arquivos. Como 3 != 5, cai no 'else'.
    Saída: 
    P#TA MERDA! VAI A MERDA! Coube 3 arquivos!
    2 4 5
    
    // Complexidade:
    // O(N log N) - O tempo de execução é dominado pela função sort() que ordena os N arquivos.
    // O laço para salvar os arquivos percorre o vetor apenas uma vez: O(N).
    // Como N vai apenas até 1000, a ordenação é feita em milissegundos.
    */
}

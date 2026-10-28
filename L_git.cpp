#include <bits/stdc++.h>

using namespace std;

// Vetores de direção: uma técnica clássica de maratona para andar em matrizes
// Combinando dx[i] e dy[i], temos as 4 direções cardeais: 
// Cima (-1, 0), Baixo (1, 0), Esquerda (0, -1), Direita (0, 1).
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

// Estrutura para guardar o estado atual da nossa exploração no mapa.
struct Estado {
    int x, y;
    int custo;

    // Sobrecarga do operador '>'. Como vamos usar uma Fila de Prioridade (Priority Queue),
    // precisamos ensiná-la a ordenar os estados. Queremos sempre explorar o caminho MAIS BARATO primeiro,
    // por isso invertemos a lógica usando '>' para criar um Min-Heap (menor custo no topo).
    bool operator>(const Estado& outro) const {
        return custo > outro.custo;
    }
};

// Função simples para evitar que nosso encanador virtual saia dos limites da horta.
bool dentroDoMapa(int x, int y, int l, int c) {
    return x >= 0 && x < l && y >= 0 && y < c;
}

// Retorna o custo de cabo em metros para cada tipo de terreno
int obterCusto(char terreno) {
    if (terreno == '*') return 1; // Terreno limpo
    if (terreno == '@') return 3; // Entulho
    if (terreno == 'H') return 1; // Plugar na bomba
    return 1;
}

// O famoso Algoritmo de Dijkstra: encontra o caminho mais curto em grafos com pesos diferentes.
int dijkstra(int inicioX, int inicioY, int fimX, int fimY, int l, int c, const vector<string>& mapa) {
    
    // Fila de prioridade que sempre nos entrega o 'Estado' com o menor 'custo' acumulado.
    priority_queue<Estado, vector<Estado>, greater<Estado>> pq;
    
    // Matriz de distâncias (custos). Preenchemos tudo com um valor absurdamente alto (1e9 = 1 bilhão)
    // simulando o "infinito", pois no início não sabemos o custo para chegar em lugar nenhum.
    vector<vector<int>> dist(l, vector<int>(c, 1e9));

    // O custo para ir do início para o próprio início é sempre 0.
    dist[inicioX][inicioY] = 0;
    pq.push({inicioX, inicioY, 0});

    while (!pq.empty()) {
        Estado atual = pq.top(); // Pega a posição mais barata disponível.
        pq.pop(); // Remove da fila.

        // Se encontrarmos um custo na fila que é pior do que um que já achamos antes para essa mesma célula, ignoramos.
        if (atual.custo > dist[atual.x][atual.y]) continue;

        // Se chegamos na Bomba d'água (H), como o Dijkstra garante o menor caminho primeiro, 
        // já podemos retornar a resposta final e encerrar a busca!
        if (atual.x == fimX && atual.y == fimY) {
            return atual.custo;
        }

        // Tenta andar para as 4 direções possíveis.
        for (int i = 0; i < 4; i++) {
            int nx = atual.x + dx[i];
            int ny = atual.y + dy[i];

            if (!dentroDoMapa(nx, ny, l, c)) continue; // Bateu na cerca da horta.
            if (mapa[nx][ny] == 'S') continue; // Não faz sentido voltar para o quadro de energia.

            // Calcula qual seria o custo se fôssemos para essa nova célula vizinha.
            int novoCusto = atual.custo + obterCusto(mapa[nx][ny]);

            // Se esse novo caminho for MAIS BARATO do que o caminho que conhecíamos antes para essa célula:
            if (novoCusto < dist[nx][ny]) {
                dist[nx][ny] = novoCusto; // Atualiza o melhor custo.
                pq.push({nx, ny, novoCusto}); // Coloca na fila para explorar os vizinhos dela depois.
            }
        }
    }

    return -1; // Caso impossível de chegar (o problema garante que sempre tem caminho, mas é boa prática).
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int l, c;
    cin >> l >> c;
        
    vector<string> mapa(l, string(c, ' '));
    int inicioX = -1, inicioY = -1, fimX = -1, fimY = -1;

    // Lendo o mapa e já procurando onde está o Quadro (S) e a Bomba (H)
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            cin >> mapa[i][j]; 
            
            if (mapa[i][j] == 'S') {
                inicioX = i; 
                inicioY = j;
            } else if (mapa[i][j] == 'H') {
                fimX = i; 
                fimY = j;
            }
        }
    }

    // Chama o algoritmo para resolver o labirinto.
    int resultado = dijkstra(inicioX, inicioY, fimX, fimY, l, c, mapa);

    if (resultado != -1) {
        cout << "Bomba energizada com " << resultado << " metro(s) de fio\n";
    }
    
    return 0;
    
    /*
    Testando o passo a passo com o Caso de Exemplo 1
    4 linhas e 4 colunas
    S * @ H
    @ * @ *
    @ * * *
    @ @ @ @
    
    O Dijkstra sai do 'S' (0,0). Custo = 0.
    Ele olha para os vizinhos:
    - Direita (0,1): '*' -> Custo 0 + 1 = 1.
    - Baixo (1,0): '@' -> Custo 0 + 3 = 3.
    
    Ele escolhe ir para a direita (0,1), pois o custo 1 é menor.
    Do (0,1) ele olha os vizinhos:
    - Direita (0,2): '@' -> Custo 1 + 3 = 4.
    - Baixo (1,1): '*' -> Custo 1 + 1 = 2.
    
    Ele escolhe ir para baixo (1,1).
    Do (1,1) ele olha para baixo de novo (2,1) '*': Custo 2 + 1 = 3.
    Do (2,1) ele olha para a direita (2,2) '*': Custo 3 + 1 = 4.
    Do (2,2) ele olha para a direita (2,3) '*': Custo 4 + 1 = 5.
    Do (2,3) ele olha para cima (1,3) '*': Custo 5 + 1 = 6. Eita, caminho longo.
    
    Enquanto isso, daquele custo 4 no (0,2) '@', ele olha para a direita e acha o 'H' (0,3).
    Custo 4 + 1 = 5.
    
    Como ele achou o 'H' com custo 5 e as outras rotas na fila também estão custando 5 ou mais, 
    ele encerra e garante que 5 é o menor custo possível.
    
    Saída: Bomba energizada com 5 metro(s) de fio
    
    // Complexidade:
    // O(V + E * log V) - Onde V é o número de vértices (L * C) e E o número de arestas (4 direções).
    // Como a matriz tem no máximo 500x500 (250.000 células), o Dijkstra com fila de prioridade (Min-Heap) 
    // vai rodar de forma extremamente eficiente, bem abaixo dos 2 segundos de Timelimit.
    */
}

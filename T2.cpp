//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////                                                                                                          ////////
////////                                                                                                          ////////
////////                          TRABALHO 2 DE ALGORITMOS AVANÇADOS E APLICAÇÕES                                 ////////
////////					NOME: JOAO VICTOR GARCIA COELHO           NUSP: 10349540                              ////////   
////////					NOME: EDUARDO ALVES BARATELA			  NUSP: 10295270                              ////////
////////                                                                                                          ////////
////////                                                                                                          ////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <set>
#include <unordered_map>
#include <cmath>
using namespace std;

typedef long long ll;

typedef struct _Peca{
	int linha;
	int coluna;
	int tipo;

}Peca;

Peca result; //Variavel auxiliar para guardar a posicao da peca final do tabuleiro
int **tab; // tabuleiro
int nPecas = 0; //Variavel que conta o numero de pecas restantes no tabuleiro
ll nCaminhos = 0; //nCaminhos encontrados ate o momento
int vis[25];



// Estou sobrecarregando o operador () para usar a classe como um functor
// para que o set saiba como deve ser ordenado o conjunto


class ComparaPeca{
public:	
	bool operator()( Peca const&x, Peca const& y){ // Se y for maior que x, return true, senão, return false
	 	//Ordenando por linha, depois por coluna e por fim, por tipo de peça
	 	if(x.linha < y.linha)
	 		return true;
	 	else if(x.linha == y.linha){
	 		if(x.coluna < y.coluna)
	 			return true;
	 		else if(x.coluna == y.coluna){
	 			if(x.tipo < y.tipo)
	 				return true;
	 		}
	 	}
		return false;
	}
};

// Criando um conjunto de 
set <Peca, ComparaPeca> resultados; // Cria o set passando a struct e a classe de comparacao
set<Peca>::iterator it; // iterador de set


ll Base_4(int R, int C){
	long long x = 0;
	int cont = 0;
	for (int i = R-1; i >= 0; i--){
		for (int j = C-1; j >= 0; j--){
			x += tab[i][j] * pow(4, cont);
			cont++;
		}
	}
	return x;
}

void visit(int** tab, int i, int j, int R, int C, int* cont){

	(*cont)++;
	int pos = i*C + j;
	
	vis[pos] = 1;	

	if(i > 0){ // Se eu puder ir para o norte
		if(tab[i-1][j] != 0){
			pos = (i-1)*C + j;
			if(vis[pos] == 0){
				visit(tab, i-1, j, R, C,cont);
			}
		}	
	}
	if(j < (C-1)){ // Se eu puder ir para o direita
		if(tab[i][j+1] != 0){
			pos = i*C + (j+1);
			if(vis[pos] == 0){
				visit(tab, i, j+1, R, C, cont);
			}
		}	
	}
	if(i < (R-1)){ // Se eu puder ir para o sul
		if(tab[i+1][j] != 0){
			pos = (i+1)*C + j;
			if(vis[pos] == 0){
				visit(tab,i+1, j, R, C, cont);
			}
		}	
	}
	if(j > 0){ // Se eu puder ir para o esquerda
		if(tab[i][j-1] != 0){
			pos = i*C + j-1;
			if(vis[pos] == 0){
				visit(tab,i, j-1, R, C, cont);
			}
		}	
	}
				
	vis[pos] = 2;


}

// Se o numero de peças encontradas na dfs != num de peças restantes no tabuleiro, então existem ilhas

bool DFS(int** tab, int i, int j, int R, int C){

	for(int k = 0; k < R*C; k++){
		vis[k] = 0;

	}
	int cont = 0;
	visit(tab, i, j, R, C, &cont);

	if(cont == nPecas)
		return true;

	return false;
}

unordered_map <ll, ll> umap;

void Jan_Ken_Puzzle(int R, int C, ll chave, ll chaveANT){

	// Se o numero de pecas restantes no tabuleiro for 1
	if(nPecas == 1){ //Caso de parada
		resultados.insert(result); // insere a posicao final no set(se o final ja existir no set, ele insere)
		umap[chave] = 1;
		nCaminhos++; // mais um caminho encontrado
		return ;
	}
	int peca;
	if(umap.find(chave) != umap.end()){ // o tabuleiro já está na hash
		nCaminhos += umap[chave];
		return ;
	}

	umap.insert({chave, 0}); // insere uma nova chave no map

	for(int i = 0; i < R; i++){
		for (int j = 0; j < C; j++){ 
			if(tab[i][j] != 0){ // Se a posição n for vazia
				if(i > 0){ // Se eu puder ir para o norte
					if( (tab[i-1][j] == (tab[i][j]+1)) || ((tab[i-1][j] == 1) && (tab[i][j] == 3)) ){
						peca = tab[i-1][j];// guarda a peça que vai ser comida
						// verifica se há ilhas no tabuleiros
						if(DFS(tab, i,j, R, C) == false){
							return;
						}

						chaveANT = chave; // salva a chave atual
						// modifica a chave para o próximo tabuleiro

						chave += tab[i][j] * pow(4,(R*C) - (C*(i-1) + j +1));
						chave -= tab[i][j] * pow(4,(R*C) - (C*i + j +1));
						chave -= tab[i-1][j] * pow(4,(R*C) - (C*(i-1) + j +1));
						
						// come a peça
						tab[i-1][j] = tab[i][j];
						tab[i][j] = 0;
						nPecas--;
						
						// atualiza a variavel result, ja que ao comer essa peca, pode restar agora apenas 1 peca no jogo
						result.linha = i-1;
						result.coluna = j;
						result.tipo = tab[i-1][j];
						
						Jan_Ken_Puzzle(R, C, chave, chaveANT); // chama a função recursivamente
					
						// atualiza o valor de chave ant com o valor da chave encontrada
						umap[chaveANT] += umap[chave];

						// restaura o tabuleiro como ele tava
						tab[i][j] = tab[i-1][j];
						tab[i-1][j] = peca;


						chave = chaveANT;

						nPecas++;
					}
				}
				if(j < (C -1)){ // Se eu puder ir para a direita
					if( (tab[i][j+1] == (tab[i][j]+1)) || ((tab[i][j+1] == 1) && (tab[i][j] == 3)) ){
						peca = tab[i][j+1];// guarda a peça que vai ser comida
					
						// verifica se há ilhas no tabuleiros
						if(DFS(tab, i,j, R, C) == false){
							return;
						}

						chaveANT = chave;// salva a chave atual
						// modifica a chave para o próximo tabuleiro

						chave += tab[i][j] * pow(4,(R*C) - (C*i + (j+1) +1));
						chave -= tab[i][j] * pow(4,(R*C) - (C*i + j +1));
						chave -= tab[i][j+1] * pow(4,(R*C) - (C*i + (j+1) +1));	

						// come a peça
						tab[i][j+1] = tab[i][j];
						tab[i][j] = 0;
						nPecas--;
						// atualiza a variavel result, ja que ao comer essa peca, pode restar agora apenas 1 peca no jogo
						result.linha = i;
						result.coluna = j+1;
						result.tipo = tab[i][j+1];
						
						Jan_Ken_Puzzle(R, C, chave, chaveANT); // chama a função recursivamente
						// atualiza o valor de chave ant com o valor da chave encontrada
						umap[chaveANT] += umap[chave];

						// restaura o tabuleiro como ele tava
						tab[i][j] = tab[i][j+1];
						tab[i][j+1] = peca;

						chave = chaveANT;

						nPecas++;

					}
				}
				if(i < (R-1)){ // Se eu puder ir para o sul
					if( (tab[i+1][j] == (tab[i][j]+1)) || ((tab[i+1][j] == 1) && (tab[i][j] == 3)) ){
						peca = tab[i+1][j];// guarda a peça que vai ser comida
						
						// verifica se há ilhas no tabuleiros
						if(DFS(tab, i, j, R, C) == false){
							return;
						}

						chaveANT = chave;// salva a chave atual
						// modifica a chave para o próximo tabuleiro

						chave += tab[i][j] * pow(4,(R*C) - (C*(i+1) + j +1));
						chave -= tab[i][j] * pow(4,(R*C) - (C*i + j +1));
						chave -= tab[i+1][j] * pow(4,(R*C) - (C*(i+1) + j +1));

						// come a peça
						tab[i+1][j] = tab[i][j];
						tab[i][j] = 0;
						nPecas--;
						
						// atualiza a variavel result, ja que ao comer essa peca, pode restar agora apenas 1 peca no jogo
						result.linha = i+1;
						result.coluna = j;
						result.tipo = tab[i+1][j];
						
						Jan_Ken_Puzzle(R, C, chave, chaveANT); // chama a função recursivamente
						// atualiza o valor de chave ant com o valor da chave encontrada
						umap[chaveANT] += umap[chave];	

						// restaura o tabuleiro como ele tava
						tab[i][j] = tab[i+1][j];
						tab[i+1][j] = peca;

						chave = chaveANT;

						nPecas++;

					}
				}
				if(j > 0){ // Se eu puder ir para a esquerda
					if( (tab[i][j-1] == (tab[i][j]+1)) || ((tab[i][j-1] == 1) && (tab[i][j] == 3)) ){
						peca = tab[i][j-1]; // guarda a peça que vai ser comida
						
						// verifica se há ilhas no tabuleiros
						if(DFS(tab, i,j, R, C) == false){
							return;
						}

						chaveANT = chave;// salva a chave atual
						// modifica a chave para o próximo tabuleiro

						chave += tab[i][j] * pow(4,(R*C) - (C*i + (j-1) +1));
						chave -= tab[i][j] * pow(4,(R*C) - (C*i + j +1));
						chave -= tab[i][j-1] * pow(4,(R*C) - (C*i + (j-1) +1));	

						// come a peça
						tab[i][j-1] = tab[i][j];
						tab[i][j] = 0;
						nPecas--;
						// atualiza a variavel result, ja que ao comer essa peca, pode restar agora apenas 1 peca no jogo
						result.linha = i;
						result.coluna = j-1;
						result.tipo = tab[i][j-1];
						
						Jan_Ken_Puzzle(R, C, chave, chaveANT); // chama a função recursivamente
						// atualiza o valor de chave ant com o valor da chave encontrada
						umap[chaveANT] += umap[chave];

						// restaura o tabuleiro como ele tava
						tab[i][j] = tab[i][j-1];
						tab[i][j-1] = peca;

						chave = chaveANT;

						nPecas++;
					}
				}
			}

		}
	}
}


int main(){
	int R, C;
	// Lendo o numero de Linhas e Colunas
	cin >> R >> C;
	if((R == 0) || (C == 0))
		return 0; 

	// Alocando o tabuleiro
	tab = (int**) malloc(sizeof(int*) *R);
	for(int i = 0; i < R; i++)
		tab[i] = (int*) malloc(sizeof(int)*C);

	for(int i = 0; i < R; i++){
		for (int j = 0; j < C; j++){
			cin >> tab[i][j];

			if(tab[i][j] != 0) // Contando o numero de pecas no tabuleiro
				nPecas++;
			}
	}

	ll chave = Base_4(R,C);

	Jan_Ken_Puzzle(R, C, chave, chave);
	// numero de caminhos distintos encontrados
	cout << nCaminhos << endl;
	// numero de posicoes finais distintas encontradas e quais elas são
	cout << resultados.size() << endl;
	// Imprimindo todos os resultados finais distindos
	for (it = resultados.begin(); it != resultados.end(); it++){
		cout << (it->linha)+1 << " " << (it->coluna)+1 << " " <<it->tipo << endl;
	}

	return 0;
}
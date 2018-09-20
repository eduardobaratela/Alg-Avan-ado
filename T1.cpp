#include <iostream>
#include <set>

using namespace std;


typedef struct _Peca{
	int linha;
	int coluna;
	int tipo;

}Peca;

Peca result;
int **tab;
int nPecas = 0;
int nCaminhos = 0;


// Estou sobrecarregando o operador () para usar a classe como um functor 


class ComparePeca{
public:	
	bool operator()( Peca const&x, Peca const& y){
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

set <Peca, ComparePeca> resultados; // Cria o set passando a struct e a classe de comparacao
set<Peca>::iterator it; // iterador de set



void Jan_Ken_Puzzle(int R, int C){

	if(nPecas == 1){ //Caso de parada
		resultados.insert(result); // insere a posicao final no set
		nCaminhos++;
		return ;
	}
	int peca;

	for(int i = 0; i < R; i++){
		for (int j = 0; j < C; j++){ 
			if(tab[i][j] != 0){ // Se a posição n for vazia
				if(i > 0){ // Se eu puder ir para o norte
					if( (tab[i-1][j] == (tab[i][j]+1)) || ((tab[i-1][j] == 1) && (tab[i][j] == 3)) ){
						peca = tab[i-1][j];// guarda a peça que vai ser comida
						// come a peça
						tab[i-1][j] = tab[i][j];
						tab[i][j] = 0;
						nPecas--;
						
						result.linha = i-1;
						result.coluna = j;
						result.tipo = tab[i-1][j];
						
						Jan_Ken_Puzzle(R, C); // chama a função recursivamente
					
						// restaura o tabuleiro como ele tava
						tab[i][j] = tab[i-1][j];
						tab[i-1][j] = peca;
						nPecas++;
					}
				}
				if(j < (C -1)){ // Se eu puder ir para a direita
					if( (tab[i][j+1] == (tab[i][j]+1)) || ((tab[i][j+1] == 1) && (tab[i][j] == 3)) ){
						peca = tab[i][j+1];// guarda a peça que vai ser comida
						// come a peça
						tab[i][j+1] = tab[i][j];
						tab[i][j] = 0;
						nPecas--;
						
						result.linha = i;
						result.coluna = j+1;
						result.tipo = tab[i][j+1];
						
						Jan_Ken_Puzzle(R, C); // chama a função recursivamente
						// restaura o tabuleiro como ele tava
						tab[i][j] = tab[i][j+1];
						tab[i][j+1] = peca;
						nPecas++;

					}
				}
				if(i < (R-1)){ // Se eu puder ir para o sul
					if( (tab[i+1][j] == (tab[i][j]+1)) || ((tab[i+1][j] == 1) && (tab[i][j] == 3)) ){
						peca = tab[i+1][j];// guarda a peça que vai ser comida
						// come a peça
						tab[i+1][j] = tab[i][j];
						tab[i][j] = 0;
						nPecas--;
						
						result.linha = i+1;
						result.coluna = j;
						result.tipo = tab[i+1][j];
						
						Jan_Ken_Puzzle(R, C); // chama a função recursivamente
						// restaura o tabuleiro como ele tava
						tab[i][j] = tab[i+1][j];
						tab[i+1][j] = peca;
						nPecas++;

					}
				}
				if(j > 0){ // Se eu puder ir para a esquerda
					if( (tab[i][j-1] == (tab[i][j]+1)) || ((tab[i][j-1] == 1) && (tab[i][j] == 3)) ){
						peca = tab[i][j-1]; // guarda a peça que vai ser comida
						// come a peça
						tab[i][j-1] = tab[i][j];
						tab[i][j] = 0;
						nPecas--;
				
						result.linha = i;
						result.coluna = j-1;
						result.tipo = tab[i][j-1];
						
						Jan_Ken_Puzzle(R, C); // chama a função recursivamente
						// restaura o tabuleiro como ele tava
						tab[i][j] = tab[i][j-1];
						tab[i][j-1] = peca;
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

	Jan_Ken_Puzzle(R, C);
	// numero de caminhos distintos encontrados
	cout << nCaminhos << endl;
	// numero de posicoes finais distintas encontradas e quais elas são
	cout << resultados.size() << endl;
	for (it = resultados.begin(); it != resultados.end(); it++){
		cout << (it->linha)+1 << " " << (it->coluna)+1 << " " <<it->tipo << endl;
	}

	return 0;
}
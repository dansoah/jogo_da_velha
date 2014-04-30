#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <math.h>

/*
 *       DEFINES
**/

//Colunas
char COL = '|';
//Linhas
char LN = '-';
//Icones de jocador
char P1 = 'O';
char P2 = 'X';

/*
 *       PROTOTYPE
**/

void drawTabuleiro();
void point(char caractere,int x,int y);
void gotoxy(int x, int y);
void configura();
bool isPoint(int x, int y);
void color(int color);
void modeSelect();
int homemVsMaquina();
int homemVsHomem();
void maquinaJoga();
int testaVitoria(char * mapa);
int fat(int num);
void setPoint(char ponto, int x, int y);
void point(char caractere,int x,int y);

/*
 * Estrutura utilizada para armazenar as jogadas
 *
 */
typedef struct mapa{
    int x, y,key;
    char val;      
};

typedef struct estrategia{
    int x[3],y[3];        
};

//Nossa variável de controle
mapa mapa[3][3];


/*
 * Modo de jogo
 * 1 = Player Vs. PC
 * 2 = Human Vs. Human
 *
 */
 
int modoJogo = 1;

/*
 * Numero do jogador
 *
 * Modo 1:
 * 1 = Homem
 * 2 = PC
 *
 * Modo 2:
 * 1 = P1
 * 2 = P2
 */
 
 int jogador = 0;
 
/*
 *       MAIN PROCEDURE
**/
int main(){
    
    
    
    color(15);
    printf("::::: JOGO DA VELHA :::::::::");
    
    
    modeSelect();
    color(15);
    system("CLS");
    
    if(modoJogo == 1){
        homemVsMaquina();                   
    }else{
         homemVsHomem();      
    }
    
    gotoxy(1,25);
    system("PAUSE");
    
    
}

/*
 * Função que cria colunas.
 * @var x posição horizontal qual a coluna irá se posicionar
 * @var yBegin Posição vertical qual a coluna irá iniciar
 * @var yEnd Posição vertical qual a coluna irá acabar
**/
void coluna(int x, int yBegin, int yEnd){
     
      if(yBegin < yEnd){
          for(int y = yBegin;y<=yEnd;y++){              
              gotoxy(x,y);
              printf("%c",COL);      
          }
          return;
      }
      
      printf("Problemas ao montar o tabuleiro!");
      system("pause");
      exit(1);
}

/*
 * Função que cria linhas.
 * @var y posição vertical qual a linha irá se posicionar
 * @var xBegin Posição vertical qual a linha irá iniciar
 * @var xEnd Posição vertical qual a linha irá acabar
**/
void linha(int y,int xBegin,int xEnd){
     if(xBegin < xEnd){
          for(int x = xBegin;x<=xEnd;x++){              
              gotoxy(x,y);
              printf("%c",LN);      
          }
          return;
      }
      
      printf("Problemas ao montar o tabuleiro!");
      system("pause");
      exit(1);
}

/*
 * Função que desenha o tabuleiro
 *
**/
void drawTabuleiro(){
    coluna(15,3,15);
    coluna(25,3,15);
    
    linha(6,7,33);
    linha(11,7,33);
}

/*
 * Função que marca um ponto X ou O no nosso tabuleiro
 * @var caractere Caractere que será marcado
 * @var x Coordenada X no plano do tabuleiro
 */
void point(char caractere,int x,int y){
     if(!isPoint(x,y))
         return;
     gotoxy(x,y);
     printf("%c",caractere);
}

/*
 * Função que procura um ponto que possa ser preenchido baseado no que lhe for 
 * enviado.
 * @var x Coordenada X no plano do tabuleiro
 * @var y Coordenada Y no plano do tabuleiro
 */

bool isPoint(int x, int y){
    for(int i = 0; i<=2 ; i++){
        
        for(int j=0 ; j<=2 ; j++){
            int mpX = mapa[i][j].x;
            int mpY = mapa[i][j].y;
            if(mpX == x && mpY == y){
                return true;         
            }
                    
        }
                
    }   
    
    return false;  
}

void setPoint(char ponto, int x, int y){
     if(!isPoint(x,y))
        return;
        
      for(int i = 0; i<=2 ; i++){
        
          for(int j=0 ; j<=2 ; j++){
              int mpX = mapa[i][j].x;
              int mpY = mapa[i][j].y;
              if(mpX == x && mpY == y){
                  mapa[i][j].val = ponto;
              }
                    
          }
                
      }
}
/*
 * Função que obtem os pontos de uma tecla
*/

int * getKeyPoint(int tecla){
     bool encontrado = 0;
     int * xy = (int *) malloc(2 * sizeof (int));
     
     for(int i = 0;i<=2;i++)
         for(int j = 0; j <= 2 ; j++){
             if(mapa[i][j].key == tecla){
                  xy[0] = mapa[i][j].x;
                  xy[1] = mapa[i][j].y;
                  return xy;
             }
         }  
     xy[0] = -1;
     xy[1] = -1;
     return xy;
}

void gotoxy(int x, int y){
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

/*
 * Função que configura nosso mapa do jogo
 *
**/
void configura(){
/*
     *  10,4    |  20,4   | 30,4
     * ===========================
     *  10,8    |  20,8   | 30,8
     * ===========================
     *  10,14   |  20,14  | 30,14
     *
     */
    mapa[0][0].x = 10;
    mapa[0][0].y = 4;
    mapa[0][0].key = 55;
    
    mapa[0][1].x = 20;
    mapa[0][1].y = 4;
    mapa[0][1].key = 56;
    
    mapa[0][2].x = 30;
    mapa[0][2].y = 4;
    mapa[0][2].key = 57;    
    
    mapa[1][0].x = 10;
    mapa[1][0].y = 8;
    mapa[1][0].key = 52;
    
    mapa[1][1].x = 20;
    mapa[1][1].y = 8;
    mapa[1][1].key = 53;
    
    mapa[1][2].x = 30;
    mapa[1][2].y = 8;
    mapa[1][2].key = 54;    
    
    mapa[2][0].x = 10;
    mapa[2][0].y = 14;
    mapa[2][0].key = 49;
    
    mapa[2][1].x = 20;
    mapa[2][1].y = 14;
    mapa[2][1].key = 50;
    
    mapa[2][2].x = 30;
    mapa[2][2].y = 14;
    mapa[2][2].key = 51;
}

void color(int color){
     HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);   
}

void modeSelect(){
    bool ok = false;
    do{
        gotoxy(10,10);
        color(15);
        printf("SELECIONE O MODO DE JOGO\n");
        gotoxy(10,11);
        if(modoJogo == 1){
            color(127);        
        }else{
            color(15);
        }
        printf("Homem Vs. Maquina\n");
        gotoxy(10,12);
        if(modoJogo == 2){
            color(127);        
        }else{
            color(15);
        }
        printf("Homem Vs. Homem");
        int key = getch();
        //804 = para baixo
        //724 = para cima
        
        if(key == 72){
            if(modoJogo == 2)
                modoJogo = 1;
        }
        
        if(key == 80){
            if(modoJogo == 1)
                modoJogo = 2;
        }
        
        if(key == 13){
            ok = true;       
        }
        
    }while(ok == false);    
}

void showPlayer(){
     gotoxy(1,1);
     if(modoJogo = 1){
         if(jogador == 1)
            printf("Humano 1");
         else
             printf("Maquina");            
     }else{
          if(jogador == 1)
            printf("Humano 1");
         else
             printf("Humano 2");     
     }     
}

/******************************* ENGINES *******************************/
/**** AUXILIARES **/
void jogaMoeda(){
     if(rand() % 2 == 0){
         jogador = 1;
     }else{
         jogador = 2;      
     }
     
}

void trocaJogador(){
    if(jogador == 1)
        jogador = 2;
    else
        jogador = 1;     
}

/** Referentes a estratégia **/

bool alguemGanhou(){
        return false;       
}

bool deuVelha(){
     
}
/**** PRINCIPAIS ****/
int homemVsMaquina(){
    //Quem joga primeiro?
    jogaMoeda();
    showPlayer();
    
    //Monta tabuleiro e configura o sistema
    drawTabuleiro();
    configura();
    
    bool won = false;
    int x = 0;
    int y = 0;
    
    do{
        
        if(jogador == 1){
                gotoxy(1,20);
         
                bool xyOk = false;
                do{
                   int tecla = getch();
             
                   switch(tecla){
                       case 57:
                     case 56:
                     case 55:
                     case 54:
                     case 53:
                     case 52:
                     case 51:
                     case 50:
                     case 49:
                         int * xy = getKeyPoint(tecla);
                          x = xy[0];
                          y = xy[1];
                          xyOk = true;
                          break;  
                 }
             }while(!xyOk);
         
             //Marca o ponto
             point(P1,x,y);
             setPoint(P1,x,y);
         }else{
               
             maquinaJoga();
         }
         
         //testaVitoria();
         trocaJogador();
         
    }while(alguemGanhou() == false && deuVelha() == false);
}

int homemVsHomem(){
    
}

/*************************************************************************/

void maquinaJoga(){
     
    char tabuleiro[3][3];
    char testaJogada[3][3];
    
    int vazios = 0;
    //Montando o tabuleiro atual
    for(int i =0;i<=2;i++)
        for(int j=0;j<=2;j++){
            //Verificamos se essa posição foi preenchida
            if(mapa[i][j].val == P1 || mapa[i][j].val == P2)
                tabuleiro[i][j] = mapa[i][j].val;
            else{
                tabuleiro[i][j] = '\0';
                vazios++;
            }
        }
    //montando jogada
    
    
    
    
    
    
}

int testaVitoria(char mapa){
    
     //colunas
     for(int x =0;x<=2;x++){
         int cnt = 0; 
         char anterior;
         for(int y=0;y<=2;y++){
             if(y==0){
                 anterior = mapa[x][y];
                 continue;
             } 
             if(mapa[x][y] == anterior){
                 cnt++;              
             }
         } 
         
         if(cnt == 3)
             if(anterior == P1)
                 return 1;
             if(anterior == P2);
                 return 2;      
            
     }
     
     
     
     
     return 0;
     
     
}

int fat(int num){
    
    if(num == 1)
        return 1;
    
    if(num < 1)
        return 0;
    
    int fat = 1;
    for(int i= num;i>=1;i--){
        fat *= i;
    }
        
    return fat;
}

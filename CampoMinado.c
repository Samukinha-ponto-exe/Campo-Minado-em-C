#include <stdio.h> // biblioteca base da linguagem C
#include <time.h> // biblioteca utilizada para randomizar as bombas
#include <stdlib.h> // biblioteca utilizada para randomizar as bombas
#include <locale.h> // biblioteca utilizada para permitir acentua��o
#include <string.h> // biblioteca utilizada para obter o nome do usu�rio

//Vari�veis globais

int tam = 10, quant_bombas=10;
int qtd_reserva;
char nome[64];
int hora1, hora2, hora3;
int pontos = 0;
int cbase[75][75], volta[75][75];
char exibir1[75][75];
int bomb_final = 0;

void name() // fun��o para obter o nome do usu�rio, e tamb�m receber o inicializar o contador de tempo do jogo
{
    printf("\n Insira o seu nome: ");
    gets(nome);
    hora1 = time(NULL);
    printf("\n\n");
}

void distribuir_bombas() //fun��o para distribuir as bombas aleatoriamente
{
  int i, j, l_a, c_a;
  srand(time(NULL)); // fazer a randomiza��o realmente ser aleat�ria, se baseando no tempo atual do computador
  i = quant_bombas;
  do // gerar bombas enquanto ainda houver bombas dispon�veis
  {
    l_a = rand()%tam; // randomizar linha da bomba
    c_a = rand()%tam; // randomizar coluna da bomba

    if(cbase[l_a][c_a] == 0) // verificar se o local est� dispon�vel
    {
      cbase[l_a][c_a] = -1; // colocar a bomba no lugar
      i--; // diminuir uma bomba do contador
    }

  }while(i>0);
}

void abrir_campo() // fun��o para calcular as dicas de proximidade de bombas
{
    int i, j;

    for(i=0; i<tam; i++)
   {
       for(j=0; j<tam; j++)
       {
           if(cbase[i][j]==-1){ //verifica se a posi��o � de uma bomba
           if(cbase[i-1][j-1]!=-1){volta[i-1][j-1]+=1;} //somam 1 nas casas adjacentes da matriz de dicas, se n�o for uma bomba
           if(cbase[i-1][j]!=-1){volta[i-1][j]+=1;}
           if(cbase[i-1][j+1]!=-1){volta[i-1][j+1]+=1;}
           if(cbase[i][j-1]!=-1){volta[i][j-1]+=1;}
           if(cbase[i][j+1]!=-1){volta[i][j+1]+=1;}
           if(cbase[i+1][j-1]!=-1){volta[i+1][j-1]+=1;}
           if(cbase[i+1][j]!=-1){volta[i+1][j]+=1;}
           if(cbase[i+1][j+1]!=-1){volta[i+1][j+1]+=1;}
       }
     }
   }
}

void menu() //exibir menu com as op��es para o usu�rio
{
   int opcao, escolha;

   system("cls||clear"); // limpa a tela

   printf("\n\n");
   printf("\t|----------------------------|\n");
   printf("\t|   Campo Minado 2020 em C   |\n");
   printf("\t|----------------------------|\n");
   printf("\t|         1 - Jogar          |\n");
   printf("\t|         2 - Op��es         |\n");
   printf("\t|         3 - Sobre          |\n");
   printf("\t|         4 - Sair           |\n");
   printf("\t|----------------------------|\n");
   printf("\n\n Digite a op��o desejada: ");
   scanf("%d", &opcao); //recebe a op��o desejada pelo usu�rio

  fflush(stdin); // limpa o buffer do teclado

   switch(opcao)
   {
     case 1:    // continua para o jogo padr�o
        break;

     case 2: // exibe as op��es de dificuldade para o jogador escolher
        printf("\n\n Voc� tem 3 opc�es de jogo\n\n");
        printf(" (1) F�cil -  Tabuleiro [10][10] e 10 bombas\n\n");

        printf(" (2) Intermedi�rio - Tabuleiro[15][15] e 40 bombas");

        printf("\n\n (3) Dif�cil - Tabuleiro[20][20] e 99 bombas\n\n");

        printf(" Qual voc� deseja escolher? ");
        scanf("%d",&escolha); // recebe a escolha do usu�rio

        fflush(stdin);

        if(escolha == 1) //configura��o padr�o do jogo e exibe o menu novamente
        {
            tam = 10;
            quant_bombas = 10;
            menu();
        }
        else if(escolha == 2) // define a dificuldade para m�dia
        {
            tam = 15;
            quant_bombas = 40;
            menu();
        }
        else if(escolha == 3) // define a dificuldade para dif�cil
        {
            tam = 20;
            quant_bombas = 99;
            menu();
        }

        fflush(stdin);
        break;

        case 3:
            sobre(); // exibir a fun��o sobre
        break;

        case 4:
            exit(0); // sai do programa
        break;

        default:
            printf("Comando Inv�lido !!!"); //para caso o jogador digite algo errado
            getchar();
            menu();
        break;
   }
 }

void campo_base() //gera os campos base para todas as matrizes
{
  int i, j;

    for(i = 0; i <tam ; i++)
    {
        for(j=0; j <tam ; j++)
        {
            cbase[i][j]=0; // campo base para a matriz de bombas
        }
    }

    for(i=0; i<tam; i++)
    {
       for(j=0; j<tam; j++)
       {
           exibir1[i][j] = '-'; // campo base para a matriz de exibi��o
       }
   }

   for(i=0; i<tam; i++)
   {
       for(j=0; j<tam; j++)
       {
           volta[i][j] = 0; // campo base para a matriz de dicas de proximidade
       }
   }
}

void imprimir_campo() //reimprime o campo a cada vez
{
    int i, j;

    system("cls||clear"); // limpa a tela
    printf("\n\n\tNome: %s\t\tPontua��o: %d\t\tBombas Restantes: %d\n\n\n", nome, pontos, quant_bombas); // exibe o nome, pontua��o e quantidade de bombas restante

    if(tam ==10) // exibe a coluna para cada dificuldade
        printf("        0    1    2    3    4    5    6    7    8    9\n\n");
    if(tam ==15)
        printf("        0    1    2    3    4    5    6    7    8    9    10   11   12   13   14\n\n");
    if(tam ==20)
        printf("        0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   19\n\n");

    for(i = 0; i < tam; i++)
    {
        if(i<10){ // exibe as linhas
            printf(" 0%d ", i);
        }
        else{
            printf(" %d ", i);
        }

        for(j=0; j < tam; j++)
        {
            printf("%5c", exibir1[i][j]); // exibe a casa da matriz de exibi��o
        }
        printf("\n\n");
    }
}

int conf_tab() //confere o jogo, para saber se a pessoa ganhou o jogo
{
    int i, j, teste=1, cont=0, qtd;           //inicializa uma vari�vel para ganhar como 1, e um contador para verificar as bandeiras em rela��o as bombas

    for(i = 0; i <tam ; i++)
    {
        for(j=0; j <tam ; j++)
        {
            if(cbase[i][j]==0)
                teste = 0;            // caso alguma casa n�o aberta (fora as bombas) seja encontrada, o jogador continua a jogar
        }
    }

    if(quant_bombas == 0){ // conferir as posi��es das bandeiras caso o jogador tenha gasto todas
        for(i = 0; i <tam ; i++)
        {
            for(j=0; j <tam ; j++)
            {
                if(exibir1[i][j] == 'B' && cbase[i][j] == -1){
                    cont++; // contador de bandeiras corretas
                }
            }
        }

    if(cont == qtd_reserva){ // ganhar o jogo caso todas as bandeiras estejam corretas
        teste = 1;
    }else if(quant_bombas==0 && cont<qtd_reserva){ // perder o jogo caso alguma bandeira esteja errada

        qtd = qtd_reserva - cont;

        printf("\nVoc� gastou todas as suas bandeiras e errou a localiza��o de %d bombas\n", qtd);
        getchar();
        perde();
    }

  }
    return teste; // retorna o valor do teste
}

void perde() //fun��o para caso o jogador perca
{
    int i, j;

    bomb_final=1;

    if(bomb_final=1){                     // exibir na matriz de exibi��o a localiza��o de todas as bombas
      for(i=0; i<tam; i++){
        for(j=0; j<tam; j++){
            if(cbase[i][j] == -1)
                exibir1[i][j] = 169;
        }
      }
    }

    imprimir_campo(); // imprimir campo com a posi��o das bombas

    printf("\n\n\n\tVoc� perdeu\n\n"); //exibir para o jogador que ele perdeu

    hora2= time(NULL); // calcular tempo gasto no jogo
    hora3 = hora2-hora1;
    printf("\n\tNome do jogador: %s", nome);              //exibir as informa��es
    printf("\n\tSeu jogo durou %d segundos.\n\n", hora3);
    printf("\n\tPontua��o: %d", pontos);

    getchar();
    main();
}

void sobre() // fun��o para exibir dados sobre o grupo
{
    printf("\n\n|------------------------------------------------|\n");
    printf("|                                                |\n");
    printf("|           Lista de Desenvolvedores             |\n");
    printf("|                                                |\n");
    printf("|           Igor Richard Dias Silva              |\n");
    printf("|        Samuel Henrique da Cunha Machado        |\n");
    printf("|        Gustavo Xavier da Silva Bonif�cio       |\n");
    printf("|         Iago Rafael Sant'Anna Rodrigues        |\n");
    printf("|         Icaro Cau� da Silveira Oliveira        |\n");
    printf("|                                                |\n");
    printf("|------------------------------------------------|\n");
    printf("|  CEFET-MG Unidade Contagem | Professora Beth   |\n");
    printf("|------------------------------------------------|\n\n");

    getchar(); //espera a pessoa pressionar um enter
    menu(); //volta para o menu
}

void ganha() // fun��o para o jogador ganhar o jogo
{
    printf("\n\n\n NOSSOS PARAB�NS !!! VOC� VENCEU !! Esperamos que tenha gostado\n"); // informa ao jogador que ele ganhou

    hora2 = time(NULL);    //calcula o tempo gasto no jogo
    hora3 = hora2 - hora1;
    printf("\n\tNome do jogador: %s", nome);             // exibe as informa��es
    printf("\n\tSeu jogo durou %d segundos.\n\n", hora3);
    printf("\n\tPontua��o: %d", pontos);

    getchar();
    main();
}
void jogar() // fun��o do jogo normal
{
    int linha, coluna, cont, op;

    printf("\nDigite a linha desejada: ");    // pedir ao usu�rio a linha, coluna e opera��o desejada
    scanf("%d", &linha);
    fflush(stdin);
    printf("\nDigite a coluna desejada: ");
    scanf("%d", &coluna);
    fflush(stdin);
    printf("\nO que voc� deseja fazer?\n\n1-Explodir\n\n2-Bandeira\n\n3-Duvida\n\n\nOpera��o Desejada: ");
    scanf("%d", &op);
    fflush(stdin);

    if(coluna >=tam || linha>=tam){
        printf("\nMovimento inv�lido"); // informar um movimento inv�lido
        getchar();
    }
    else if(cbase[linha][coluna]==9){
        printf("\nMovimento inv�lido"); // movimento em casa onde j� ocorreu alguma a��o
        getchar();
    }else
    {
        if(op == 2){ // caso em que a pessoa escolhe a bandeira
            if(exibir1[linha][coluna] != 'B'){ // se no local n�o houver uma bandeira, insere uma e reduz na quantidade de bombas dispon�veis
                exibir1[linha][coluna] = 'B';
                quant_bombas--;
            }
        }
        else if(op == 3){ // caso a pessoa escolha a d�vida
            if(exibir1[linha][coluna]=='B') // se no local houver uma bandeira, ela � retirada e a contagem de bombas dispon�veis aumenta o valor correspondente
                quant_bombas++;
            exibir1[linha][coluna] = '?';
        }
        else{ // caso de explodir o local

        if(cbase[linha][coluna] == -1) // se o local for uma bomba, a pessoa ir� perder
        {
            perde();
        }

        if(exibir1[linha][coluna]=='B') // se o local tiver uma bandeira, ela � removida
                quant_bombas++;

        if(cbase[linha-1][coluna-1] != -1 && cbase[linha-1][coluna] != -1 && cbase[linha-1][coluna+1] != -1 && cbase[linha][coluna-1] != -1 && cbase[linha][coluna+1] != -1 && cbase[linha+1][coluna-1] != -1 && cbase[linha+1][coluna] != -1 && cbase[linha+1][coluna+1] != -1 )
        { // se n�o houverem bombas adjacentes ao local, libera as casas laterais, e exibe as dicas (se houver)

            exibir1[linha][coluna] = '+';                                   // cada fun��o a partir daqui exibe um + se n�o houverem dicas no local
            cbase[linha][coluna] = 9;                                       // ou o valor da dica, caso houver

            //pontos++;                                                       //sistema para somar a pontua�� corretamente

            if(exibir1[linha-1][coluna-1] == '-'){pontos++;}
            if(exibir1[linha-1][coluna] == '-'){pontos++;}
            if(exibir1[linha-1][coluna+1] == '-'){pontos++;}
            if(exibir1[linha][coluna-1] == '-'){pontos++;}
            if(exibir1[linha][coluna+1] == '-'){pontos++;}
            if(exibir1[linha+1][coluna-1] == '-'){pontos++;}
            if(exibir1[linha+1][coluna] == '-'){pontos++;}
            if(exibir1[linha+1][coluna+1] == '-'){pontos++;}
            if(exibir1[linha][coluna] == '-'){pontos++;}

            if(volta[linha-1][coluna-1] != 0){
                exibir1[linha-1][coluna-1] = volta[linha-1][coluna-1] + '0';
            }else{exibir1[linha-1][coluna-1] ='+';}

            if(volta[linha-1][coluna] != 0){
                exibir1[linha-1][coluna]   = volta[linha-1][coluna] + '0';
            }else{exibir1[linha-1][coluna] ='+';}

            if(volta[linha-1][coluna+1] != 0){
                exibir1[linha-1][coluna+1] = volta[linha-1][coluna+1] + '0';
            }else{exibir1[linha-1][coluna+1] ='+';}

            if(volta[linha][coluna-1] != 0){
                exibir1[linha][coluna-1]   = volta[linha][coluna-1] + '0';
            }else{exibir1[linha][coluna-1] ='+';}

            if(volta[linha][coluna+1] != 0){
                 exibir1[linha][coluna+1]   = volta[linha][coluna+1] + '0';
            }else{exibir1[linha][coluna+1] ='+';}

            if(volta[linha+1][coluna-1] != 0){
                 exibir1[linha+1][coluna-1] = volta[linha+1][coluna-1] + '0';
            }else{exibir1[linha+1][coluna-1] ='+';}

            if(volta[linha+1][coluna] != 0){
                exibir1[linha+1][coluna]   = volta[linha+1][coluna] + '0';
            }else{exibir1[linha+1][coluna] ='+';}

            if(volta[linha+1][coluna+1] != 0){
                exibir1[linha+1][coluna+1] = volta[linha+1][coluna+1] + '0';
            }else{exibir1[linha+1][coluna+1] ='+';}

            cbase[linha-1][coluna-1] = 9; //define as localiza��es como abertas
            cbase[linha-1][coluna]   = 9;
            cbase[linha-1][coluna+1] = 9;
            cbase[linha][coluna-1]   = 9;
            cbase[linha][coluna+1]   = 9;
            cbase[linha+1][coluna-1] = 9;
            cbase[linha+1][coluna]   = 9;
            cbase[linha+1][coluna+1] = 9;
        }
        else
        {
            pontos++; // soma 1 na pontua��o

                cbase[linha][coluna]= 9; // define o local como aberto
                exibir1[linha][coluna] = volta[linha][coluna] + '0'; //exibe a dica do local
        }
      }
   }
}

int main(void) { //fun��o principal

    setlocale(LC_ALL, "PORTUGUESE"); //define a l�ngua padr�o como portugu�s

   int i, j, teste, continuar;

   time_t currentTime;  //Fun��es para definir o sistema de marca��o do tempo
   time(&currentTime);
   typedef long time_t;

    do{ // Repeti��o para o jogador conseguir jogar quantas vezes quiser

    for(i=0; i<tam; i++) // inicializa��o pr�via da matriz (foi adicionada para evitar um bug que estava ocorrendo)
    {
       for(j=0; j<tam; j++)
       {
           exibir1[i][j] = '-';
       }
       printf("\n\n");
    }

    tam = 10;
    quant_bombas = 10;
    pontos=0;

    menu(); // chama o menu
    name(); // pede o nome do usu�rio

    qtd_reserva = quant_bombas; //define a vari�vel qtd_reserva, utilizada para ganhar ou perder usando o sistema de bandeiras

    campo_base(); // inicializa as matrizes bases
    distribuir_bombas(); // distribui as bombas
    abrir_campo(); // define as dicas

    do{ // repeti��o para o jogo rodar normalmente
        imprimir_campo(); // imprime a matriz de exibi��o
        jogar(); // pede os dados ao jogador
        teste = conf_tab(); // confere se o jogador ganhou o jogo
    }while(teste==0);
    imprimir_campo(); // imprime o campo uma �ltima vez caso o jogador ganhe
    ganha(); // fun��o que faz o jogador ganhar

    printf("\n\nDeseja continuar a jogar?\n0 - N�o\n1 - Sim\n\n"); //pergunta ao jogador se ele deseja jogar novamente
    scanf("%d", &continuar);
    fflush(stdin);
    }while(continuar=1);

    return 0; // finaliza o programa
}

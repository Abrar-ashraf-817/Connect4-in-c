//sourceCode by ABRAR ASHRAF

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>


#define PLAYER1 1
#define PLAYER2 2


//input handler: Makes sure only 0-9,tab,y,n are entered and any random inputs are ignored
char inputchar(void);//returns single character


//main game function
int connect4(void);


//display and update
void drawBoard(int BackBoard[][7]);//displays the game board
int updateboard(int n,int BackBoard[][7],int player);//updates the backboard
int howToGuide(void);//shows how to guide
void winboardtofile(int BackBoard[][7]);//prints winning board to file

//game logic
int win_Checker(int BackBoard[][7]);
int vertcheck(int col,int BackBoar[][7],int player);//checks all columns for win condition
int horicheck(int row,int BackBoard[][7],int player);//checks all rows for win condition
int majdcheck(int majd,int BackBoard[][7],int player);//checks  major diagonals that can hold 4 tokens for win condition also checks for draw condition
int mindcheck(int mind,int BackBoard[][7],int player);//checks  minor diagonals that can hold 4 tokens for win condition


//main function
int main(int n){

printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t1.START\n\t\t\t\t\t\t\t2.How to play\n\t\t\t\t\t\t\t3.Exit\n\n");
printf("\n\n\n\n\n\n\n\n\n\n\n\n\nPress 1, 2 or 3 to navigate: ");

int in;
if(n==0){in=1;}else{in = (inputchar()-'0');}
switch(in){

case 1:
    system("cls");
    if(connect4()== 1){main(0);}else{return 0;}
    break;
case 2:
    system("cls");
    if(howToGuide()== 1){main(1);}else{return 0;}
    break;
case 3:
    return 0;
    break;
default:
    system("cls");
    main(1);
    break;
}

return 0;
}


char inputchar(void){
    char in[100]; //input buffer
    while(1)//restriction to input
    {
    fgets(in,sizeof(in),stdin);
        if((isdigit(in[0])||in[0]=='\t'||in[0]=='y'||in[0]=='n')&&strlen(in)<3){
            break;
        }
        printf("only digits or tab(exit),y(yes),n(no) are accepted as input\n");
    }
    return in[0];
}

int connect4(void){

//board initialization
int row,col, BackBoard[6][7]= {{0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0},
                                              };

int win,itr=1;// win/draw conditional variable, turn switching variable

char in;

//main game loop
do{


drawBoard(BackBoard);
win=win_Checker(BackBoard);


if(win == PLAYER1){break;}
if(win == PLAYER2){break;}
if(win == -1){break;}


if(itr%2!=0){
        printf("Player 1's Turn --> @\n");
    }else{
        printf("Player 2's Turn --> $\n");
}

//player input
in=inputchar();
if(in=='\t'){break;}
int n = in-'0';// converting from character to integer e.g. ascii '1'=41,'0'=40 so 41-40=integer 1

//player turn switching
if(itr%2!=0){

switch(n){

case 1:
    if(updateboard(n,BackBoard,PLAYER1)==1){itr--;}
    break;
case 2:
    if(updateboard(n,BackBoard,PLAYER1)==1){itr--;}
    break;
case 3:
    if(updateboard(n,BackBoard,PLAYER1)==1){itr--;}
    break;
case 4:
    if(updateboard(n,BackBoard,PLAYER1)==1){itr--;}
    break;
case 5:
    if(updateboard(n,BackBoard,PLAYER1)==1){itr--;}
    break;
case 6:
    if(updateboard(n,BackBoard,PLAYER1)==1){itr--;}
    break;
case 7:
    if(updateboard(n,BackBoard,PLAYER1)==1){itr--;}
    break;
default://invalid input handler i.e. 9,y,0,8 etc.
    printf("not an input \n");
    itr--;
    break;

}
}else{

switch(n){

case 1:
    if(updateboard(n,BackBoard,PLAYER2)==1){itr--;}
    break;
case 2:
    if(updateboard(n,BackBoard,PLAYER2)==1){itr--;}
    break;
case 3:
    if(updateboard(n,BackBoard,PLAYER2)==1){itr--;}
    break;
case 4:
    if(updateboard(n,BackBoard,PLAYER2)==1){itr--;}
    break;
case 5:
    if(updateboard(n,BackBoard,PLAYER2)==1){itr--;}
    break;
case 6:
    if(updateboard(n,BackBoard,PLAYER2)==1){itr--;}
    break;
case 7:
    if(updateboard(n,BackBoard,PLAYER2)==1){itr--;}
    break;
default://invalid input handler i.e. 9,y,0,8 etc.
    printf("not an input \n");
    itr--;
    break;

}
}
itr++;
system("cls");
}while(in != '\t');

system("cls");
drawBoard(BackBoard);

if(win == PLAYER1){printf("\n\n\t\t\t\t\t\t        Player 1 wins!");winboardtofile(BackBoard);FILE *fp = fopen("snapshot.txt","a");fprintf(fp,"\n\n\t\t\t\t\t\t        Player 1 wins!\n\n");fclose(fp);}
if(win == PLAYER2){ printf("\n\n\t\t\t\t\t\t        Player 2 wins!");winboardtofile(BackBoard);FILE *fp = fopen("snapshot.txt","a");fprintf(fp,"\n\n\t\t\t\t\t\t        Player 2 wins!\n\n");fclose(fp);}
if(win == -1){ printf("\n\n\t\t\t\t\t\t           Draw");winboardtofile(BackBoard);FILE *fp = fopen("snapshot.txt","a");fprintf(fp,"\n\n\t\t\t\t\t\t        Draw\n\n");fclose(fp);}

printf("\n\n\n\t\t\t\t\t  Do you want to play again?(y/n):{yes|no}\n\n\t\t\t\t\t  ");

//exit handler
do{
in=inputchar();
    if(in=='y'){system("cls");return 1;}
    if(in=='n'){return 0;}
    if(in=='\t'){return 0;}
    if((in!='\t')||(in!='n')||(in!='y')){printf("please enter y or n or tab. ");}
}while((in!='\t')||(in!='n')||(in!='y'));

}


void drawBoard(int BackBoard[][7]){

int row,col;


printf("\t\t\t\t\t\t           CONNECT 4!       \n");
printf("\n\n\n");
printf("\t\t\t\t\t\t   1   2   3   4   5   6   7\n");
printf("\t\t\t\t\t\t   |   |   |   |   |   |   |\n");
printf("\t\t\t\t\t\t   V   V   V   V   V   V   V\n");
printf("\t\t\t\t\t\t ----------------------------\n");


for(row=0;row<13;row++){
    printf("\t\t\t\t\t\t||");//side panel
    if(row%2!=0){
        for(col=0;col<7;col++){
            if(BackBoard[row/2][col]==0){printf("   |");}//empty box and divider
            if(BackBoard[row/2][col]==PLAYER1){printf(" @ |");}//player 1 token and divider
            if(BackBoard[row/2][col]==PLAYER2){printf(" $ |");}//player 2 token and divider

        }
    }else{
        for(col=0;col<7;col++){
           if(col<6){
                printf("----");//top and bottom divider
            }else{
                printf("---|");//top and bottom divider and side panel
            }
        }
    }

    if(row<11){printf("\n");}else{printf("\n");};
}
printf("\t\t\t\t\t\t  ```````````````````````````\n");//bottom panel
}


int updateboard(int n,int BackBoard[][7],int player){
    int row,i = n - 1;

    if(BackBoard[0][i] != 0){
       printf("this col is filled ");
       return 1;
    }
    for(row=0;row<6;row++){
        if(BackBoard[row][i] != 0){
        break;
        }
    }
    BackBoard[row - 1][i] = player;
     if(BackBoard[5][i] == 0){
        BackBoard[5][i] = player;
    }
return 0;
}

int howToGuide(void){

printf("\n\n\n\n\n\n\n\n\n\t\t\t\t  Connect 4 is a very easy game, to win you need to\n");
printf("\t\t\t\t  have four of your chosen tokens be in a row\n");
printf("\t\t\t\t  vertically,horizontally or diagonally.\n\n");
printf("\t\t\t\t  This program only takes digits 0-9,tab,y and n as\n\t\t\t\t  inputs.\n\n\t\t\t\t  Tab is used to exit the game and program.");
printf("\n\n\n\n\n\n\n\n\n\n\nGo to Menu?(y) or exit(n)?:{yes|no}\n\n");

char in;

//exit handler
do{
in=inputchar();
    if(in=='y'){system("cls");return 1;}
    if(in=='n'){return 0;}
    if(in=='\t'){return 0;}
    if((in!='\t')||(in!='n')||(in!='y')){printf("please enter y or n or tab. ");}
}while((in!='\t')||(in!='n')||(in!='y'));
}


void winboardtofile(int BackBoard[][7]){
    FILE *fp = fopen("snapshot.txt","a");
    int row,col;


fprintf(fp,"\t\t\t\t\t\t           CONNECT 4!       \n");
fprintf(fp,"\n\n\n");
fprintf(fp,"\t\t\t\t\t\t   1   2   3   4   5   6   7\n");
fprintf(fp,"\t\t\t\t\t\t   |   |   |   |   |   |   |\n");
fprintf(fp,"\t\t\t\t\t\t   V   V   V   V   V   V   V\n");
fprintf(fp,"\t\t\t\t\t\t ----------------------------\n");


for(row=0;row<13;row++){
    fprintf(fp,"\t\t\t\t\t\t||");//side panel
    if(row%2!=0){
        for(col=0;col<7;col++){
            if(BackBoard[row/2][col]==0){fprintf(fp,"   |");}//empty box and divider
            if(BackBoard[row/2][col]==PLAYER1){fprintf(fp," @ |");}//player 1 token and divider
            if(BackBoard[row/2][col]==PLAYER2){fprintf(fp," $ |");}//player 2 token and divider

        }
    }else{
        for(col=0;col<7;col++){
           if(col<6){
                fprintf(fp,"----");//top and bottom divider
            }else{
                fprintf(fp,"---|");//top and bottom divider and side panel
            }
        }
    }

    if(row<11){fprintf(fp,"\n");}else{fprintf(fp,"\n");};
}
fprintf(fp,"\t\t\t\t\t\t  ```````````````````````````\n");

 fclose(fp);

}


int win_Checker(int BackBoard[][7]){
    int col,row,majd,t,mind;//majd is major diagonal constant i.e.in(x,y)_(x-y)=majd|mind is minor diagonal constant i.e.in(x,y)_(x+y)=mind
    for(col=0;col<7;col++){
        if(vertcheck(col,BackBoard,PLAYER1) >= 4){
            return 1;
            break;
        }
        if(vertcheck(col,BackBoard,PLAYER2) >= 4){
            return 2;
            break;
        }

    }
    for(row=0;row<6;row++){
        if(horicheck(row,BackBoard,PLAYER1) >= 4){
            return 1;
            break;
        }
        if(horicheck(row,BackBoard,PLAYER2) >= 4){
            return 2;
            break;
        }

    }
    for(majd=-3;majd<3;majd++){
        if(majdcheck(majd,BackBoard,PLAYER1) >= 4){
            return 1;
            break;
        }
        if(majdcheck(majd,BackBoard,PLAYER2) >= 4){
            return 2;
            break;
        }
        if(majdcheck(majd,BackBoard,PLAYER2) == -1){
            return -1;
            break;
        }
    }
    for(mind=3;mind<9;mind++){

        if(mindcheck(mind,BackBoard,PLAYER1) >= 4){
            return 1;
            break;
        }
        if(mindcheck(mind,BackBoard,PLAYER2) >= 4){
            return 2;
            break;
        }
    }

return 0;
}


int vertcheck(int col,int BackBoard[][7],int player){
    int row,vertcount=0;

    for(row=0;row<6;row++){
        if(BackBoard[row][col] == player){
            vertcount++;
            if(vertcount >= 4){
            return vertcount;
            break;
            }
        }
        else{
            vertcount = 0;
        }

    }
    return vertcount;
}


int horicheck(int row,int BackBoard[][7],int player){
    int col,horicount=0;

    for(col=0;col<7;col++){
        if(BackBoard[row][col] == player){
            horicount++;
            if(horicount >= 4){
            return horicount;
            break;
            }
        }
        else{
            horicount = 0;
        }

    }
    return horicount;
}


int majdcheck(int majd,int BackBoard[][7],int player){
    int row,col,majdcount=0,zerocnt=0;

    for(row=0;row<6;row++){
        for(col=0;col<7;col++){
                if(BackBoard[row][col]==0){zerocnt++;}
            if((row-col) == majd){
              if(BackBoard[row][col] != player){
                    majdcount=0;
                }else{
                    majdcount++;
                    if(majdcount >= 4){
                    return majdcount;
                    break;
                    }
                 }
            }
        }
    }

    if(zerocnt==0){return -1;}

    return majdcount;
}


int mindcheck(int mind,int BackBoard[][7],int player){
    int row,col,mindcount=0;

    for(row=0;row<6;row++){
        for(col=0;col<7;col++){
            if(((row+col) == mind)){
              if(BackBoard[row][col] != player){
                    mindcount=0;
                }else{
                    mindcount=mindcount+1;
                    if(mindcount >= 4){
                    return mindcount;
                    break;
                    }
               }
            }
        }
    }
    return mindcount;
}

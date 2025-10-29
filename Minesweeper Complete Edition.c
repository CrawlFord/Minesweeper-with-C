/*  Program Title: Minesweeper Game

    Author: Torobong Andrew-Udoh

    Department: Automatic Controls and Systems Engineering

    Description: The code is a C program that implements a simple Minesweeper game with login capabilities.
                 The program allows users to check their performance, read the rules, play the game at various difficulty settings,
                 log in, and make new user profiles. There are two methods to play the game: either label mines with flags or explore
                 boxes to avoid them. This text-based user interface has a number of features for both user interaction and game progression.
                 The code contains functions for administering user login, game logic, difficulty selection, menu selection, score administration,
                 and other responsibilities.


    Date Written: 08/05/2024*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dos.h>
#include <windows.h>

#define flush fflush(stdin)

// Function to set the cursor position on the console
void gotoxy(int x, int y)
{
     HANDLE hConsoleOutput;
     COORD Cursor_Pos={x,y};

    hConsoleOutput=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_Pos);
}

// Function that hides the cursor on the console
void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

// Structure to store user details
struct USER_DETAILS
{
	char USERNAME[30];
	char PASSWORD[30];
} user;

// Function for the start-up page
int menuoptions()
{
	int a, check;
	check=1;

	while(check)
    {
        system("cls");
        decor_line1();
        system("color 70");
        gotoxy(58,9);
        printf(">>>>>>>>>LOG-IN OPTIONS<<<<<<<<<");
        gotoxy(58,11);
        printf("1)SIGN-IN");
        gotoxy(58,13);
        printf("2)SIGN-UP");
        gotoxy(58,15);
        printf("3)EXIT");
        gotoxy(58,17);
        printf("Select an option...:");
        scanf("%d", &a);
        flush;

        if(a>=1 && a<=3)
        {
            check=0;
        }
        else
        {
            system("cls");
            system("color 47");
            gotoxy(71,14);
            printf("INVALID INPUT");
            Sleep(500);
        }
    }

	return a;
}

// Login Function
int login(char x[])
{
	system("color 70");

	int e=menuoptions(),flag=0;
	char USERNAME1[40],PASSWORD1[40];
	char ch='n';
    FILE *fp;

    // Code that allows the user to exit from start-up page
	if(e==3)
    {
        system("cls");
        decor_line1();
        gotoxy(71,14);
        printf("Exiting program.....");
        flag=0;
        Sleep(1000);
        exit(1);
    }

    // Code that allows the user to sign-in with existing details
	if(e==1)
	{
	    do
	    {
            ch='n';
            int answ=1;

            fp=fopen("USER_DETAILS.txt","a+");

            system("cls");
            decor_line1();
            gotoxy(72, 10);
            printf("USERNAME: ");
            gets(USERNAME1);
            flush;
            gotoxy(72,12);
            printf("PASSWORD: ");
            gets(PASSWORD1);
            flush;


            strcpy(x,USERNAME1);


			while(fread(&user,sizeof(struct USER_DETAILS),1,fp))
			{

				if(strcmp(user.USERNAME,USERNAME1)==0)
				{
					if(strcmp(user.PASSWORD,PASSWORD1)==0)
					{
						flag=1;
					}

				}
			}

			if(flag==0)
			{
			    while(answ)
                {
                    system("color 47");
                    gotoxy(67,17);
                    printf("Access denied");
                    Sleep(400);
                    gotoxy(67,18);
                    system("color 70");
                    printf("Do you want to retry(y/n)???");
                    ch=getch();
                    flush;
                    Sleep(400);

                    if( (ch == 'y') || (ch == 'n') )
                    {
                        answ=0;
                    }
                    else
                    {
                        answ=1;
                    }
                }
			}



        } while(ch=='y');

        fclose(fp);
    }



	// Code that allows the user to sign-up with new details
	if(e==2)
	{
		system("cls");

    	FILE *fp1;
	    fp1=fopen("USER_DETAILS.txt","a+");

        decor_line1();
        gotoxy(72,10);
		flush;
		printf("USERNAME: ");
		gets(user.USERNAME);
		gotoxy(72,12);
		flush;
		printf("Password: ");
		gets(user.PASSWORD);

		fwrite(&user,sizeof(struct USER_DETAILS),1,fp1);

		gotoxy(65,17);
		printf("congratulations your ID has been created");
		Sleep(500);
		flag=1;
		fclose(fp1);
		strcpy(x,user.USERNAME);
	}

    if(flag==1)
    {
        return 10;
    }
}

// Function to generate a random value within a range for the mines
int val_gen(int y, int g, int f)
{
    y=0;


    y=rand()%g;
    if(y<f)
    {
        y+=f;
    }

    return(y);
}

// Function to select the difficulty level to be played
void difficulty_selection(char x[])
{
    int n;
    int g=0;
    system("cls");
    system("color 70");
    decor_line1();
    gotoxy(43,6);
    printf("Player:%s", x);

    while( (g != 1) && (g != 2) && (g != 3) )
    {
        gotoxy(50, 9);
        printf("===========================================================");
        gotoxy(50,10);
        printf("Please choose which difficulty level do you want to play..:");
        gotoxy(50,11);
        printf("===========================================================");
        gotoxy(63,14);
        printf("EASY Level - Press 1");
        gotoxy(63,15);
        printf("INTERMEDIATE LEVEL - Press 2");
        gotoxy(63,16);
        printf("HARD LEVEL - Press 3");
        gotoxy(63,20);
        printf("Enter the number now - ");

        scanf("%d", &g);
        flush;

        //CODE TO SHOW WHEN AN INVALID INPUT HAS BEEN ENTERED

        if(g<=1 && g>=3)
        {
            system("cls");
            system("color 47");
            gotoxy(71,14);
            printf("INVALID INPUT");
            Sleep(500);
        }
    }

	system("cls");

	if(g==1)
	   {
	       g=0;
	       n=5;
	   }
	if(g==2)
	   {
	       n=9;
	   }
	if(g==3)
	   {
	       n=12;
	   }

    print_board(n, x); // Passing variables n and x to print_board
}

// Function to print the Minesweeper game board
void print_board(int n, char x[])
{
    //CODE TO PRINT THE BOARD ACCORDING TO THE SIZE DETERMINED BY N

    char board[n][n], i, j;
    int board1[n][n], board2[n][n];                //DECLARING AN EXTRA BOARD TO STORE THE POSITIONS OF MINE


    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            board[i][j]='*';                //ASSIGNING ALL THE POSITIONS OF THE ORIGINAL BOARD VALUE * TO PRINT THE BOARD
            board1[i][j]=0;                 //ASSIGNING ALL THE POSITIONS OF THE EXTRA BOARD THE VALUE 0
            board2[i][j]=0;
        }
    }


    // CODE FOR PRINTING THE ORIGINAL BOARD

    decor_line2();
    gotoxy(10,4);
    printf("\t\t\t");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            printf(" %c ", board[i][j]);
        }
        printf(" ");
        printf("\n\t\t\t\t");
    }

    gotoxy(12,2);
    printf("Player:%s", x);

    gotoxy(10, 3);
    printf("\t\t\t");
    for(i=0;i<n;i++)
    {
        printf(" %d ", i);
    }

    int u=4;

    for(i=0;i<n;i++)
    {
        gotoxy(9, u);
        printf("\t\t\t");
        printf(" %d ", i);
        u++;
    }

    mine_generator(n, u, x, board1, board2, board); // Passing variables n,u,x,board1,baord2 and board to mine_generator
}

void mine_generator(int n, int u, char b[], int board1[][n], int board2[][n], char board[][n])
{
    // Declare variables i and j locally in the function
    int i, j;

    //CODE TO DECIDE THE NUMBER OF MINES TO BE KEPT FOR A GIVEN N LEVEL

    int mine;

    if(n==5)
    {
        mine=7;
    }
    if(n==9)
    {
        mine=21;
    }
    if(n==12)
    {
        mine=60;
    }



    //CODE TO GENERATE A RANDOM PLACE FOR MINES TO KEEP

    int k, upper=n-1, lower=0, minechecker=0;
    while(minechecker<mine)
        {
            int x, y;
            int l1_flag=1;

            while(l1_flag)
                {
                    x=val_gen(i, upper, lower);
                    y=val_gen(j, upper, lower);

                    if(x==0&&y==0)
                    {
                        l1_flag=1;
                    }
                    if(board1[x][y]!=1)
                    {
                        board1[x][y]=1;
                        minechecker++;
                        l1_flag=0;
                    }
                }

        }

    play_game(n, b, mine, u, board1, board2, board); // Passing variables n,b,x,board1,baord2 and board to play_game
}

void play_game(int n, char x[], int mine, int u, int board1[][n], int board2[][n], char board[][n])
{
    //CODE TO MAKE USER ENTER BOX NAME AND CHECK FOR MINES AT THAT BOX

    int p, q, r, number, flagcount=0, correctmines=0, score=0, scoredelete=0, flag=mine, b_menu=3, i, j;
    FILE *fptr;
    fptr=fopen("USER_SCORE.txt","a+");
    int continue_game=1;

    while(continue_game)
        {
            system("cls");
            decor_line2();
            gotoxy(88, 2);
            printf("SCORE::%d", score);
            gotoxy(88, 3);
            printf("FLAGS::%d", flag);
            gotoxy(84, 4);
            printf("TOTAL MINES::%d", mine);
            gotoxy(10,4);
            printf("\t\t\t");

            for(i=0;i<n;i++)
                {
                    for(j=0;j<n;j++)
                        {
                            if(board[i][j]=='-')
                            {
                                printf(" %d ", board2[i][j]);
                            }

                            else
                            {
                                printf(" %c ", board[i][j]);
                            }

                        }
                    printf(" ");
                    printf("\n\t\t\t\t");

                }

            gotoxy(12,2);
            printf("Player:%s", x);
            gotoxy(10, 3);
            printf("\t\t\t");

            for(i=0;i<n;i++)
                {
                    printf(" %d ", i);
                }

            u=4;

            for(i=0;i<n;i++)
                {
                    gotoxy(7, u);
                    printf("\t\t\t     ");
                    printf(" %d ", i);
                    u++;
                }


            gotoxy(32, 18);
            printf("DO YOU WANT TO EXPLORE A BOX?.....Press 1:");
            gotoxy(32, 20);
            printf("DO YOU WANT TO FLAG A MINE?.....Press 2:");
            gotoxy(32, 22);
            printf("ENTER THE CO-ORDINATES HERE..:");
            scanf("%d %d %d", &p, &q, &r);

            //CODE TO CHECK FOR MINE AND DETERMINE NEW SCORE

            if(r==1)
            {
                if(board1[p][q]==1)
                {
                    do
                    {
                        system("cls");
                        decor_line1();
                        gotoxy(74,10);
                        printf("SCORE : %d", score);
                        gotoxy(45,15);
                        printf("OOPS...");
                        gotoxy(45,16);
                        printf("GAME-OVER");
                        gotoxy(45,17);
                        printf("YOU STEPPED ON A MINE....");
                        Sleep(1000);
                        continue_game = main_menu(b_menu);
                    }while(continue_game==1);

                    fprintf(fptr,"PLAYERNAME: %s ", x);
                    fprintf(fptr,"PLAYERSORE: %d \n", score);
                    fclose(fptr);
                }

                else
                {
                    number=0;

                    if(p>0&&board1[p-1][q]==1)
                    {
                        number++;
                    }
                    if(p>0&&q>0&&board1[p-1][q-1]==1)
                    {
                        number++;
                    }
                    if(q>0&&board1[p][q-1]==1)
                    {
                        number++;
                    }
                    if(p<(n-1)&&q>0&&board1[p+1][q-1]==1)
                    {
                        number++;
                    }
                    if(p<(n-1)&&board1[p+1][q]==1)
                    {
                        number++;
                    }
                    if(p<(n-1)&&q<(n-1)&&board1[p+1][q+1]==1)
                    {
                        number++;
                    }
                    if(q<(n-1)&&board1[p][q+1]==1)
                    {
                        number++;
                    }
                    if(p>0&&q<(n-1)&&board1[p-1][q+1]==1)
                    {
                        number++;
                    }

                    board2[p][q]=number;
                    board[p][q]='-';
                    score=score+5;
                    system("cls");
                }

            }

            else if(r==2)
            {
                flag=flag-1;
                if(board1[p][q]==1)
                {
                    correctmines++;
                }
                else
                {
                    scoredelete++;
                }
                board[p][q]='M';
                flagcount++;
                score=score+5;

            }

            if(flagcount==mine)
            {
                if(correctmines==mine)
                {
                    do
                    {
                        system("cls");
                        decor_line1();
                        gotoxy(65,12);
                        printf("SCORE : %d", score);
                        gotoxy(45, 16);
                        printf("YOU WIN!!!!");
                        gotoxy(45,17);
                        printf("YOU HAVE LOCATED ALL THE MINES");
                        Sleep(1000);
                        continue_game = main_menu(b_menu);
                    }while(continue_game==1);
                }
                else if(correctmines!=mine)
                {
                    do
                    {
                        system("cls");
                        decor_line1();
                        gotoxy(65,12);
                        printf("SCORE : %d", score-(5*scoredelete));
                        gotoxy(45, 16);
                        printf("OOOH..... YOU LOSE :(");
                        gotoxy(45,18);
                        printf("YOU DID NOT LOCATE ALL MINES AND HAVE EXHAUSTED ALL FLAGS.");
                        Sleep(1000);
                        continue_game = main_menu(b_menu);
                    }while(continue_game==1);
                }
            }
        }
}

// Function for after the user has played a round
int main_menu(int c_game)
{
    //CODE TO PROMPT USER TO EITHER EXIT THE PROGRAM FROM THE PLAY OR GO BACK TO MAIN MENU

    int m_menu;

    while( (c_game != 1) && (c_game != 0) )
    {
        gotoxy(56,20);
        printf("PRESS 1 TO GO TO MAIN MENU OR 0 TO EXIT PROGRAM....");
        scanf("%d",&c_game);
        flush;
    }


    if(c_game==1)
    {
        m_menu=0;
    }
    else
    {
        system("cls");
        decor_line1();
        gotoxy(71,14);
        printf("Exiting program.....");
        Sleep(1000);
        exit(1);
    }

    return m_menu;
}

void decor_line1()
{
    //CODE FOR GENERATING AND DISPLAYING DESIGN ONE ON SCREEN

	int i;
    gotoxy(39, 4);
    for( i=0;i<=80;i++)
    {
        printf("%c", 178);
    }

    gotoxy(43, 5);
    for(i=0;i<=72;i++)
    {
        printf("%c", 177);
    }

    int y=5;
    for(i=0;i<=17;i++)
    {
    	gotoxy(39, y);
    	printf("%c", 178);
    	y++;
	}

	y=5;
	for(i=0;i<=17;i++)
	{
		gotoxy(40, y);
		printf("%c", 178);
		y++;
	}

	y=5;
	for(i=0;i<=17;i++)
	{
		gotoxy(41, y);
		printf("%c", 177);
		y++;
	}

	y=5;
	for(i=0;i<=17;i++)
	{
		gotoxy(42, y);
		printf("%c", 177);
		y++;
	}

    gotoxy(39, 23);
    for( i=0;i<=80;i++)
    {
        printf("%c", 178);
    }

   gotoxy(43, 22);
    for(i=0;i<=72;i++)
    {
        printf("%c", 177);
    }

    y=5;
	for(i=0;i<=17;i++)
	{
		gotoxy(116, y);
		printf("%c", 177);
		y++;
	}

	y=5;
	for(i=0;i<=17;i++)
	{
		gotoxy(117, y);
		printf("%c", 177);
		y++;
	}

	y=5;
	for(i=0;i<=17;i++)
	{
		gotoxy(118, y);
		printf("%c", 178);
		y++;
	}

	y=5;
	for(i=0;i<=17;i++)
	{
		gotoxy(119, y);
		printf("%c", 178);
		y++;
	}
}


void decor_line2()
{
    //CODE FOR GENERATING DISPLAYING DESIGN TWO WHEN DURING PLAY

    int i;

    gotoxy(10,1);
    for(i=0;i<=90;i++)
    {
    	printf("%c", 178);
	}

	int y=2;
	for(i=0;i<=23;i++)
	{
		gotoxy(10,y);
		printf("%c", 178);
		y++;
	}

	y=2;
	for(i=0;i<=23;i++)
	{
		gotoxy(11,y);
		printf("%c", 178);
		y++;
	}



	gotoxy(10,26);
	for(i=0;i<=90;i++)
	{
		printf("%c", 178);
	}

	y=2;
	for(i=0;i<=23;i++)
	{
		gotoxy(100,y);
		printf("%c", 178);
		y++;
	}

	y=2;
	for(i=0;i<=23;i++)
	{
		gotoxy(99,y);
		printf("%c", 178);
		y++;
	}


}



int main()
{

    srand(time(NULL));    //SEEDING WITH CURRENT TIME

    int o, n;
    char USERNAME[30];
    int g=1;
    int OK=1;

	while( OK )
        {
            o=login(USERNAME);
            printf("%s", USERNAME);

            if(o!=10)
            {
                system("cls");
                printf("\n\n\n\t\t\t\tYOU HAVE NOT LOGGED-IN SUCCESSFULLY...\n\t\t\t\tYOU CAN'T PLAY");
                exit (1);
            }

            int input=1;
            while(input)
                {
                    int b=0;
                    int a=0;

                    do
                    {
                        system("cls");
                        decor_line1();
                        hidecursor();
                        gotoxy(43,6);
                        printf("Player:%s", USERNAME);
                        gotoxy (72,8);
                        system("color 10");
                        printf("MINESWEEPER");
                        Sleep(300);
                        gotoxy(65, 10);
                        printf("1) PLAY");
                        Sleep(300);
                        gotoxy(65, 11);
                        printf("2) LEVEL");
                        Sleep(300);
                        gotoxy(65,12);
                        printf("3) HOW TO PLAY?");
                        Sleep(300);
                        gotoxy(65,13);
                        printf("4) SCORE RECORD");
                        Sleep(300);
                        gotoxy(65,14);
                        printf("5) NEW USER");
                        Sleep(300);
                        gotoxy(65,15);
                        printf("6) QUIT GAME");
                        Sleep(350);
                        gotoxy(60,16);
                        printf("------------------------------------------\n");
                        gotoxy(60,17);
                        printf("------------------------------------------\n");
                        gotoxy(62,18);
                        printf("Select any option from above..:");
                        gotoxy(60,19);
                        printf("------------------------------------------\n");
                        gotoxy(60,20);
                        printf("------------------------------------------\n");
                        gotoxy(94,18);
                        Sleep(300);
                        system("color 70");
                        scanf("%d", &a);
                        flush;

                        //CODE TO SHOW WHEN AN INVALID INPUT HAS BEEN ENTERED

                        if((a!=1) && (a!=2) && (a!=3) && (a!=4) && (a!=5) && (a!=6))
                        {
                            system("cls");
                            system("color 47");
                            gotoxy(71,14);
                            printf("INVALID INPUT");
                            Sleep(350);
                        }
                    }while( (a!=1) && (a!=2) && (a!=3) && (a!=4) && (a!=5) && (a!=6) );

                    int c=0;

                    if(a==1)
                    {
                        while( (c != 1) && (c != 2) )
                        {
                            system("cls");
                            decor_line1();
                            gotoxy(43,6);
                            printf("Player:%s", USERNAME);
                            gotoxy(60, 11);
                            printf("Do you want to start playing in EASY level...");
                            gotoxy(60,12);
                            printf("1)YES\t\t\t2)NO");
                            gotoxy(60,15);
                            printf("Please select an option (1 or 2)..");
                            scanf("%d", &c);
                            flush;
                            system("cls");
                        }

                        if(c==1)
                        {
                            decor_line1();
                            system("cls");
                            g=0;
                            n=5;
                            print_board(n, USERNAME);
                            input=1;
                        }
                        else
                        {
                            decor_line1();
                            system("cls");
                            difficulty_selection(USERNAME);
                            input=1;
                        }

                    }


                    if(a==2)
                    {
                        system("cls");
                        difficulty_selection(USERNAME);
                        input=1;
                    }

                    if(a==3)
                    {
                        while( b != 1)
                        {
                            system("cls");
                            FILE *fp;
                            fp=fopen("rules.txt", "r");                              //USE OF FILE HANDLING......(FILE PRINTING)
                            char s=0;
                            do
                            {
                                s=getc(fp);
                                printf("%c", s);
                            }while(s!=EOF);

                            printf("\n\n\t\t\t\tPress 1 to go back to home page...:");

                            scanf("%d", &b);
                            flush;
                            system("cls");

                            input=1;
                        }
                    }

                    if(a==4)
                    {
                        while( b != 1)
                        {
                            system("cls");                                                     //USE OF FILE HANDLING(fILE PRINTING)
                            FILE *fp2;
                            fp2=fopen("USER_SCORE.txt", "r");
                            char s=0;
                            do
                            {
                                s=getc(fp2);
                                printf("%c", s);
                            }while(s!=EOF);

                            printf("\n\n\t\t\t\tPress 1 to go back to home page...:");

                            scanf("%d", &b);
                            flush;
                            system("cls");

                            input=1;
                        }
                    }

                    if(a==5)
                    {
                        system("cls");
                        system("color 20");
                        decor_line1();
                        Sleep(400);
                        input=0;
                    }
                    if(a==6)
                    {
                        system("cls");
                        decor_line1();
                        gotoxy(71,14);
                        printf("Exiting program.....");
                        Sleep(1000);
                        exit(1);
                    }

                }

        }
return 0;

}

/*
    mane.sagar6529
	Flow should be like:
		i will get the current status of game affter opponents turn
		now i will try all 324 moves for me to get best move
		best move will be mygain greater than oppgain
		for this, i will find oppgain depending on my move (324 times)
			this will be calculated for all 324 moves
				this will be found by making change in xoboard to temp1board and then calculate
					how to do this?
						make my move on board temp1board
						store it
						make 8 boxes around me as temporary mine boxex
						store them
						find opponents temporary boxes and change them to permanent
						store them
						now count sum of opponents gain
						keep this in 3 variables
							now again go inside one level
								consider all 324 possibilities of opponents move
								this will again run for 324 different moves
									make changes to temp1board and create temp2board
									store those changes
									make 8 boxes around that as opponents boxes
									store them
									find my temporary boxes and change them to permanent
									store them
									now count sum of my gain
									keep this in structure
									retrieve all stored data and start next iteration i.e. find temp1 from temp2
										now find minimum of all those 324 moves in structure
										now subtract previously found oppgain from this min my gain
											store this difference in structure with my move
						now retrieve all stored data i.e. xoboard from temp1
						start next iteration
*/



/*

	changes to be made:
	1) Detection of my and opp
	2) dont show o/p if game over
	3) increase that 4 4 limit
	4) make that to possible 4 anywhere not only in specific region



*/

#include<stdio.h>
//#include<conio.h>
#include<iostream>
#include<stdlib.h>
using namespace std;

typedef struct storeRetrieve
{
	int sx,sy;
	char changedFrom;
}storeRetrieve;

typedef struct move
{
	int movex,movey,diff;
}move;

typedef struct excase
{
	int ex,ey,sum;
}excase;

//FILE *fp;
char xoboard[19][19],t1board[19][19],t2board[19][19];
int wboard[19][19];
char my,opp,tmy,topp;
storeRetrieve XOT1[20];
storeRetrieve T2T1[20];
int XOT1n=0,T2T1n=0;

/*void print_t2()
{
	//clrscr();
	for(int i=0;i<18;i++)
	{
		for(int j=0;j<18;j++)
		{
//			cout<<t2board[i][j]<<" ";
		}
  //		cout<<endl;
	}
    //	getch();
}

void print_t1()
{
//	clrscr();
	for(int i=0;i<18;i++)
	{
		for(int j=0;j<18;j++)
		{
	  //		cout<<t1board[i][j]<<" ";
		}
	//	cout<<endl;
	}
      //	getch();
}*/

int take_input()
{
	//*******  IF 'x' IS PLAYING FIRST, COUNT 'x' ELSE COUNT 'o'
	int counto=0,countx=0;
	//fp=fopen("grid.txt","r");

		//getc(fp);


	for(int i=0;i<18;i++)
	{
		for(int j=0;j<18;j++)
		{
			//fscanf(fp,"%d",&wboard[i][j]);
			//wboard[i][j]=getc(fp)-48;
			cin>>wboard[i][j];
			//getc(fp);
		}
		//getc(fp);
	}

	for(int i=0;i<18;i++)
	{
		for(int j=0;j<18;j++)
		{
			//xoboard[i][j]=getc(fp);
			cin>>xoboard[i][j];
			t2board[i][j]=t1board[i][j]=xoboard[i][j];
			if(xoboard[i][j]=='x')
				countx++;
			else if(xoboard[i][j]=='o')
				counto++;
			//getc(fp);
		}
		//fclose(fp);
	}
	//Condition will change according to player who plays first
	if(counto==0)
	{
		my='O';
		tmy='o';
		opp='X';
		topp='x';
	}
	else
	{
		my='X';
		tmy='x';
		opp='O';
		topp='o';
	}

	if(countx==0 && counto==0)
		return 0;

	return 1;
}

void show_output()
{
    for(int i=0;i<18;i++)
	{
		for(int j=0;j<18;j++)
		{
//			cout<<xoboard[i][j]<<" ";
		}
//		cout<<endl;
	}
  //	getch();
  int sum=0;
	for(int i=0;i<18;i++)
	{
		for(int j=0;j<18;j++)
		{
			sum+=wboard[i][j];
    //cout<<wboard[i][j]<<" ";
		}
      //		cout<<endl;
	}
	//clrscr();
	//cout<<sum;
	//getch();
}

int changeXOtoT1(int i,int j)
{
	XOT1n=0;
	//look in XO put in T1

	//checking of valid move is remaining

	if((xoboard[i][j]==opp || xoboard[i][j]==my))

		return 0;

	if(!(xoboard[i][j]==opp || xoboard[i][j]==my))
	{
		XOT1[XOT1n].changedFrom=t1board[i][j];
		XOT1[XOT1n].sx=i;
		XOT1[XOT1n++].sy=j;
		t2board[i][j]=t1board[i][j]=my;
	}

	if(i+1<18 && j+1<18 && !(xoboard[i+1][j+1]==opp || xoboard[i+1][j+1]==my))
	{
		XOT1[XOT1n].changedFrom=t1board[i+1][j+1];
		XOT1[XOT1n].sx=i+1;
		XOT1[XOT1n++].sy=j+1;
		t2board[i+1][j+1]=t1board[i+1][j+1]=tmy;
	}
	if(i+1<18 && !(xoboard[i+1][j]==opp || xoboard[i+1][j]==my))
	{
		XOT1[XOT1n].changedFrom=t1board[i+1][j];
		XOT1[XOT1n].sx=i+1;
		XOT1[XOT1n++].sy=j;
		t2board[i+1][j]=t1board[i+1][j]=tmy;
	}
	if(i+1<18 && j-1>=0 && !(xoboard[i+1][j-1]==opp || xoboard[i+1][j-1]==my))
	{
		XOT1[XOT1n].changedFrom=t1board[i+1][j-1];
		XOT1[XOT1n].sx=i+1;
		XOT1[XOT1n++].sy=j-1;
		t2board[i+1][j-1]=t1board[i+1][j-1]=tmy;
	}
	if(j+1<18 && !(xoboard[i][j+1]==opp || xoboard[i][j+1]==my))
	{
		XOT1[XOT1n].changedFrom=t1board[i][j+1];
		XOT1[XOT1n].sx=i;
		XOT1[XOT1n++].sy=j+1;
		t2board[i][j+1]=t1board[i][j+1]=tmy;
	}
	if(j-1>=0 && !(xoboard[i][j-1]==opp || xoboard[i][j-1]==my))
	{
		XOT1[XOT1n].changedFrom=t1board[i][j-1];
		XOT1[XOT1n].sx=i;
		XOT1[XOT1n++].sy=j-1;
		t2board[i][j-1]=t1board[i][j-1]=tmy;
	}
	if(i-1>=0 && j+1<18 && !(xoboard[i-1][j+1]==opp || xoboard[i-1][j+1]==my))
	{
		XOT1[XOT1n].changedFrom=t1board[i-1][j+1];
		XOT1[XOT1n].sx=i-1;
		XOT1[XOT1n++].sy=j+1;
		t2board[i-1][j+1]=t1board[i-1][j+1]=tmy;
	}
	if(i-1>=0 && !(xoboard[i-1][j]==opp || xoboard[i-1][j]==my))
	{
		XOT1[XOT1n].changedFrom=t1board[i-1][j];
		XOT1[XOT1n].sx=i-1;
		XOT1[XOT1n++].sy=j;
		t2board[i-1][j]=t1board[i-1][j]=tmy;
	}
	if(i-1>=0 && j-1>=0 && !(xoboard[i-1][j-1]==opp || xoboard[i-1][j-1]==my))
	{
		XOT1[XOT1n].changedFrom=t1board[i-1][j-1];
		XOT1[XOT1n].sx=i-1;
		XOT1[XOT1n++].sy=j-1;
		t2board[i-1][j-1]=t1board[i-1][j-1]=tmy;
	}
	for(int aa=0;aa<18;aa++)
	{
		for(int bb=0;bb<18;bb++)
		{
			if(t1board[aa][bb]==topp)
			{
				XOT1[XOT1n].changedFrom=topp;
				XOT1[XOT1n].sx=aa;
				XOT1[XOT1n++].sy=bb;
				t2board[aa][bb]=t1board[aa][bb]=opp;
			}
		}
	}

	return 1;
}

int calculateOppGain()
{
	int gain=0;
	//from t1board and wboard
	for(int i=0;i<18;i++)
		for(int j=0;j<18;j++)
			if(t1board[i][j]==opp)
				gain += wboard[i][j];
	return gain;
}
int changeT1toT2(int i,int j)
{

	T2T1n=0;
	//look in T1 put in T2

	//checking of valid move is remaining
	//

	if(t1board[i][j]==opp || t1board[i][j]==my)
		return 0;

	if( !(t1board[i][j]==opp || t1board[i][j]==my))
	{
		T2T1[T2T1n].changedFrom=t2board[i][j];
		T2T1[T2T1n].sx=i;
		T2T1[T2T1n++].sy=j;
		t2board[i][j]=opp;
	}

	if(i+1<18 && j+1<18 && !(t1board[i+1][j+1]==opp || t1board[i+1][j+1]==my))
	{
		T2T1[T2T1n].changedFrom=t2board[i+1][j+1];
		T2T1[T2T1n].sx=i+1;
		T2T1[T2T1n++].sy=j+1;
		t2board[i+1][j+1]=topp;
	}
	if(i+1<18 && !(t1board[i+1][j]==opp || t1board[i+1][j]==my))
	{
		T2T1[T2T1n].changedFrom=t2board[i+1][j];
		T2T1[T2T1n].sx=i+1;
		T2T1[T2T1n++].sy=j;
		t2board[i+1][j]=topp;
	}
	if(i+1<18 && j-1>=0 && !(t1board[i+1][j-1]==opp || t1board[i+1][j-1]==my))
	{
		T2T1[T2T1n].changedFrom=t2board[i+1][j-1];
		T2T1[T2T1n].sx=i+1;
		T2T1[T2T1n++].sy=j-1;
		t2board[i+1][j-1]=topp;
	}
	if(j+1<18 && !(t1board[i][j+1]==opp || t1board[i][j+1]==my))
	{
		T2T1[T2T1n].changedFrom=t2board[i][j+1];
		T2T1[T2T1n].sx=i;
		T2T1[T2T1n++].sy=j+1;
		t2board[i][j+1]=topp;
	}
	if(j-1>=0 && !(t1board[i][j-1]==opp || t1board[i][j-1]==my))
	{
		T2T1[T2T1n].changedFrom=t2board[i][j-1];
		T2T1[T2T1n].sx=i;
		T2T1[T2T1n++].sy=j-1;
		t2board[i][j-1]=topp;
	}

	if(i-1>=0 && j+1<18 && !(t1board[i-1][j+1]==opp || t1board[i-1][j+1]==my))
	{
		T2T1[T2T1n].changedFrom=t2board[i-1][j+1];
		T2T1[T2T1n].sx=i-1;
		T2T1[T2T1n++].sy=j+1;
		t2board[i-1][j+1]=topp;
	}
	if(i-1>=0 && !(t1board[i-1][j]==opp || t1board[i-1][j]==my))
	{
		T2T1[T2T1n].changedFrom=t2board[i-1][j];
		T2T1[T2T1n].sx=i-1;
		T2T1[T2T1n++].sy=j;
		t2board[i-1][j]=topp;
	}
	if(i-1>=0 && j-1>=0 && !(t1board[i-1][j-1]==opp || t1board[i-1][j-1]==my))
	{
		T2T1[T2T1n].changedFrom=t2board[i-1][j-1];
		T2T1[T2T1n].sx=i-1;
		T2T1[T2T1n++].sy=j-1;
		t2board[i-1][j-1]=topp;
	}

	for(int aa=0;aa<18;aa++)
	{
		for(int bb=0;bb<18;bb++)
		{
			if(t2board[aa][bb]==tmy)
			{
				T2T1[T2T1n].changedFrom=tmy;
				T2T1[T2T1n].sx=aa;
				T2T1[T2T1n++].sy=bb;
				t2board[aa][bb]=my;
			}
		}
	}
	return 1;
}


int calculateMyGain()
{
	int gain=0;
	//from t2board and wboard
	for(int i=0;i<18;i++)
		for(int j=0;j<18;j++)
			if(t2board[i][j]==my)
				gain+=wboard[i][j];
	return gain;
}

void changeT2toT1()
{
	for(int i=0;i<T2T1n;i++)
	{
		t2board[T2T1[i].sx][T2T1[i].sy]=T2T1[i].changedFrom;
	}
}

int findMinMyGain(int a[],int n)
{
	int min=9999;
	for(int i=0;i<n;i++)
		if(a[i]<min)
			min=a[i];
	return min;
}


void changeT1toXO()
{
	for(int i=0;i<XOT1n;i++)
	{
		t1board[XOT1[i].sx][XOT1[i].sy]=XOT1[i].changedFrom;
	}
	for(int i=0;i<18;i++)
		for(int j=0;j<18;j++)
			t2board[i][j]=t1board[i][j];
}


int oppTurn(int row,int column)
{
	//this function will have 8 possibilities in form of a structure
	//containing move coordinates and difference
	//this function will find maximum difference
	//and it will then put those move coordinates and difference in
	//"option" structure array
	//struct move allPossible[325];
	//int countSend=0,countReceived,x,y,d;
	int arrayMyGain[325],count=0,psbl;
	for(int i=row-4; i<=row+4;i++)
		for(int j=column-4;j<column+4;j++)
		{
			//change t1board to t2board
			if(i<18&&i>=0&&j<18&&j>=0)
			{
				//clrscr();
				//getch();
				//print_t2();
				//getch();
				psbl=changeT1toT2(i,j);
				//clrscr();
				//print_t2();
				//getch();


				if(psbl)
				{
					arrayMyGain[count]=calculateMyGain();	//on t2board, find my gain
					//again change t2 board to t1 board
					changeT2toT1();
					//clrscr();
					//print_t2();
					//getch();
				}
				else
					//cout<<"\n\nIgnore\n";
					arrayMyGain[count]=9999;//getch();
				count++;
			}
			/*countReceived=test(allPossible,i,j);
			if(countReceived!=0)
			{
				findMaxDiff(allPossible,countReceived,&x,&y,&d);
				option[countSend].movex=x;
				option[countSend].movey=y;
				option[countSend++].diff=d;
			}*/
		}
	return findMinMyGain(arrayMyGain,count);
}

void storeInStructure(move a[],int n,int x, int y, int ans)
{
	a[n].movex=x;
	a[n].movey=y;
	a[n].diff=ans;
}


void findMaxDiff( move a[], int n, int *x, int *y)
{
	//this function ACTUALLY finds the maximum difference from given array
	//of structure variable
	//and gives move in return
	int max= -9999;
	for(int i=0;i<n;i++)
	{
		if(a[i].diff>max)
		{
			max=a[i].diff;
			*x=a[i].movex;
			*y=a[i].movey;
		}
	}
}

void myTurn(int *playx, int *playy)
{
	//this function will have 324 moves in form of a structure
	//containing move coordinates and difference
	//this function will find maximum difference
	//and finally it will give move coordinates in playx,playy
	//int n=checkMoves(option),notNeeded;				//n must get proper no.
	move option[325];
	int myMinGain,count=0,psbl,oppgain;
	for(int i=0;i<18;i++)
	{
		for(int j=0;j<18;j++)
		{
			//clrscr();
			//print_t1();
			//getch();
			psbl=changeXOtoT1(i,j);			//change xoboard to t1board
			//print_t1();
			//getch();
			if(psbl)
			{
				oppgain=calculateOppGain();  		//on t1board, find oppgain
				myMinGain=oppTurn(i,j);
				changeT1toXO();
				//print_t1();		//again change t1board to xoboard
				//getch();
				storeInStructure(option,count,i,j,myMinGain-oppgain);
				count++;
			}
		}
	}
	findMaxDiff(option,count,playx,playy);
}

void giveMeBest(excase a[],int n,int* px,int* py)
{
	int max= -9999;
	for(int i=0;i<n;i++)
	{
		if(a[i].sum>max)
		{
			max=a[i].sum;
			*px=a[i].ex;
			*py=a[i].ey;
		}
	}
}

int calculateSum(int i,int j)
{
	if(xoboard[i][j]==opp || xoboard[i][j]==my)
		return 0;

	int sum=0;
	if(!(xoboard[i][j]==opp || xoboard[i][j]==my))
		sum+=wboard[i][j];

	if(i+1<18 && j+1<18 && !(xoboard[i+1][j+1]==opp || xoboard[i+1][j+1]==my))
		sum+=wboard[i+1][j+1];

	if(i+1<18 && !(xoboard[i+1][j]==opp || xoboard[i+1][j]==my))
		sum+=wboard[i+1][j];

	if(i+1<18 && j-1>=0 && !(xoboard[i+1][j-1]==opp || xoboard[i+1][j-1]==my))
		sum+=wboard[i+1][j-1];

	if(j+1<18 && !(xoboard[i][j+1]==opp || xoboard[i][j+1]==my))
		sum+=wboard[i][j+1];

	if(j-1>=0 && !(xoboard[i][j-1]==opp || xoboard[i][j-1]==my))
		sum+=wboard[i][j-1];

	if(i-1>=0 && j+1<18 && !(xoboard[i-1][j+1]==opp || xoboard[i-1][j+1]==my))
		sum+=wboard[i-1][j+1];

	if(i-1>=0 && !(xoboard[i-1][j]==opp || xoboard[i-1][j]==my))
		sum+=wboard[i-1][j];

	if(i-1>=0 && j-1>=0 && !(xoboard[i-1][j-1]==opp || xoboard[i-1][j-1]==my))
		sum+=wboard[i-1][j-1];

	return sum;
}

void findBlockWithMaxSum(int *playx,int *playy)
{
	int count=0;
	excase array[325];
	for(int i=0;i<18;i++)
	{
		for(int j=0;j<18;j++)
		{
			array[count].ex=i;
			array[count].ey=j;
			//if(i==8 && j==8)
			  //	getch();
			array[count++].sum=calculateSum(i,j);
		}
	}
	giveMeBest(array,count,playx,playy);
}

void play_move(int *playx, int *playy)
{
	//this function will print the finally decided move on stdout
	cout<<(*playx)<<" "<<(*playy);
	//fp=fopen("c:\\tc\\source\\out.txt","w");
	//fprintf(fp,"%d %d",*playx,*playy);
	//fclose(fp);
}


int main()
{
	int playx,playy,psbl;
	psbl=take_input();
//	show_output();
	if(psbl)
		myTurn(&playx, &playy);
	else
		findBlockWithMaxSum(&playx,&playy);
	play_move(&playx, &playy);
	return 0;
}






/*
void checkMoves();
void swap(int *a, int *b);
*/

/*putInStructure(struct move *a,int *count, int i, int j, int *mdiff)
{
	//check for validity of move
	//if invalid then return
	//else find mingain and oppgain
	int mingain,oppgain=0,x,y,d,;
	findMinGainOppGain();
	*count = *count + 1;
}*/



/*int test(struct move a[],int i,int j)
{
	int count=0;	//if move is possible then only increament count
	int mdiff;
	for (int p=0;p<18;p++)
		for (int q=0;q<18;q++)
			putInStructure(a,&count,p,q,&mdiff);
	return count;
}*/

/*
void swap(struct move *a, struct move *b)
{
	struct move *temp;
	temp=a;
	a=b;
	b=temp;
}
*/

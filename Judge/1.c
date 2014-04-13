#include <stdio.h>
#include <stdlib.h>

char xboard [18][18];
int wboard [18][18];
int val2;
int val3 = 0 ;

void read()
{
		int i,j,val3=0;
	
		for(i=0;i<18;i++)
			for(j=0;j<18;j++)
				scanf("%d",&wboard[i][j]);
		getc(stdin);
		for(i=0;i<18;i++)
			for(j=0;j<18;j++)
				scanf("%c",&xboard[i][j]);
	
		for(i=0;i<18;i++)
			for(j=0;j<18;j++)
				if(xboard[i][j]=='x' || xboard[i][j]=='o')
					val3+=wboard[i][j];
}

int cal(int i, int j)
{
		int p,q,sum=0;
		val2=0;
		for(p=-1;p<=1;p++)
		{
				for(q=-1;q<=1;q++)
				{
						if(p==0 && q==0) continue;
						if(p+i>17 || p+i<0 || q+j>17 || q+j<0) continue;
						if(xboard[p+i][q+j]!='X' && xboard[p+i][q+j]!='O' )
						sum+=wboard[p+i][q+j];
						if(xboard[p+i][q+j]=='x' || xboard[p+i][q+j]=='o' )
						val2+=wboard[p+i][q+j];
				}
		}
		
		sum+=wboard[i][j];
		return sum;
}


void play()
{
		int i,j,a[18][18],max=-79,x,y,val1;
		
		for(i=0;i<18;i++)
		{
				
				for(j=0;j<18;j++)
				{
						val1=cal(i,j);
						a[i][j]=val1+val2-val3;
						
						if(xboard[i][j]=='X' || xboard[i][j]=='O')
						a[i][j]=-7799;
						
						if(a[i][j]>max)
						{
								max=a[i][j];
								x=i;y=j;
						}
				}
		}
		
		printf("%d %d",x,y);
}
int main()
{
	read();
	play();
	return 0;
}


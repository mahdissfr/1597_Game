#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
int   n ;
int fibu(int n)
{
    if(n == 1 || n == 2)
        return 1;
    else
        return fibu(n-1) + fibu(n-2);
}

int check_fibu(int x, int y)
    {
      int i;
      for(i = 2; fibu(i)<= x; i++)
       {
      if((x == fibu(i) && y == fibu(i-1)) || (x == fibu(i) && y ==fibu(i+1)))
           return 1;
      }
      return 0;
    }

void add_one(int a [][n])
{
    int m, h, w=1;
    while(w>=1)
    {
    m = rand() %n;
    h = rand() %n;
    if(a[m][h] != 0)
        w++;
    w--;
    }
    a[m][h] = 1;

}

void pushup(int a[][n])
{
    int i, j, k=1;
    while(k<=2)
    {
    for(i=n ; i>1; i--)
        {
     for(j=1; j<=n ; j++)
        {
        if(a[i-1][j]==0)
            {
                a[i-1][j]= a[i][j];
                a[i][j]=0;
            }

        else if(check_fibu(a[i-1][j], a[i][j]) == 1)
            {
                a[i-1][j] += a[i][j];
                a[i][j]=0;
            }

        }
        }
    k++;
}
}
void pushdown(int a[][n])
{
    int i, j, k=1;
    while(k<=2)
    {
    for(i=1 ; i<=n-1 ; i++)
    {
      for(j=1; j<=n ; j++)
        {
        if(a[i+1][j] == 0)
        {
        a[i+1][j]= a[i][j];
        a[i][j] = 0;
        }
        else if(check_fibu(a[i+1][j], a[i][j])== 1)
            {
            a[i+1][j] += a[i][j];
            a[i][j] = 0;
            }
       }
    }
  k++;
    }
}
void pushright(int a[][n])
{
    int i, j,k=1;
    while(k<=2)
    {
    for(i=1 ; i<=n ; i++)
    {
        for(j=1 ; j<=n-1 ; j++)
        {
         if(a[i][j+1] == 0)
            {
             a[i][j+1]= a[i][j];
             a[i][j] = 0;
            }
         else if(check_fibu(a[i][j+1] , a[i][j])== 1)
            {
               a[i][j+1] += a[i][j];
               a[i][j] = 0;
            }

        }
    }
    k++;
    }

}
void pushleft(int a[][n])
{
    int i, j, k=1;
    while(k<=2)
    {
    for(i=1 ; i<=n ; i++)
    {
        for(j=n ; j>1 ; j--)
        {
        if(a[i][j-1] == 0)
            {
             a[i][j-1]= a[i][j];
             a[i][j] = 0;
             }
        else if(check_fibu(a[i][j-1] , a[i][j])== 1)
            {
               a[i][j-1] += a[i][j];
               a[i][j] = 0;
            }
        }
    }
  k++;
    }
}
int finish(int a [][n])
{
    int i, j;
     for(i=1 ; i<=n ; i++)
        {
        for(j=1; j<=n ; j++)
                {
        if(a[i][j] == 1597)
            return 0;
                }
         }
            return 1;
}

int main()
{
    int i , j;
    char  c;
    scanf("%d", &n);
        int a[n][n];
        int b[n][n];    //matrix b is for undo
    if(n<=3 || n>=9)
    {
       printf("wrong input");
       return 0;
    }
        for(i=1 ; i<=n ; i++)
        {
         for(j=1; j<=n ; j++)
             a[i][j] = 0;
        }
     add_one(a);
     add_one(a);

      for(i=1 ; i<=n ; i++)
        {
        for(j=1 ; j<=n; j++)
            printf("  %4d | ", a[i][j]);
        printf("\n");
        }

    while(finish(a))
        {
       c=getch();
       system("cls");
      if(c =='i')               //arrow key up : if(c==72)
      {
      for(i=1 ; i<=n ; i++)
         {
         for(j=1 ; j<=n; j++)
              b[i][j] =a[i][j];
         }
         pushup(a);
      }

    else if(c == 'k')          //arrow key down : if(c==80)
    {
      for(i=1 ; i<=n ; i++)
         {
         for(j=1 ; j<=n; j++)
              b[i][j] =a[i][j];
         }
        pushdown(a);
    }
    else if(c == 'l')            //arrow key right : if(c==77)
    {
         for(i=1 ; i<=n ; i++)
         {
            for(j=1 ; j<=n; j++)
              b[i][j] =a[i][j];
         }
        pushright(a);
    }

    else if(c =='j')            //arrow key left : if(c==75)
    {
        for(i=1 ; i<=n ; i++)
         {
            for(j=1  ; j<=n; j++)
              b[i][j] =a[i][j];
         }
        pushleft(a);
    }

    else if(c == 'q')
    {
      printf("the game is finished");
            return 0;
    }

     if(c == 'u')
        {
     for(i=1 ; i<=n ; i++)
         {
        for(j=1 ; j<=n; j++)
             a[i][j]=b[i][j];
         }
        }
         else
            add_one(a);

        for(i=1 ; i<=n ; i++)
           {
         for(j=1 ; j<=n; j++)
            printf("  %4d | ", a[i][j]);

                printf("\n");
            }

        finish(a);

        }
        printf("you win");

    return 0;
}
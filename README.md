# typeracer
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
FILE *fpin;
FILE *fbts;
int file_counter ()
{
    char npart1[25] = "level-", npart2[11], npart3[5] = ".txt", npart4[11];
    int counter = 1, help = 24;
    FILE *fnof;
    for ( ; help%2 == 0; counter++)
    {
        sprintf (npart2, "%d", counter);
        strcat (npart2, npart3);
        strcat (npart1, npart2);
        fnof = fopen (npart1, "r");
        if (fnof == NULL)
            help--;
        fclose (fnof);
        strcpy (npart1, "level-");
        strcpy (npart2, npart4) ;
        counter ++;
    }

    return counter-3;

}
void inname (int level_)
{
    char part1[25] = "level-", part2[11], part3[5] = ".txt";
    sprintf (part2, "%d", level_);
    strcat (part2, part3);
    strcat (part1, part2);
    fpin = fopen(part1, "r") ;
}

int give_level (char name[15], FILE *finfo)
{
    int find = 0, flevel, levels[25];
    char checkname[15];
    fseek (finfo, 0, SEEK_SET);
    fscanf (finfo, "%s", checkname);
    for ( ; !feof (finfo); fscanf (finfo, "%s", checkname) )
    {
        if (strcmp(checkname, name) == 0)
        {
            fscanf (finfo, "%d", &levels[find]) ;
            find++;
        }
    }
    if (find > 0)
    {
        flevel = levels[find-1] + 1;
        return flevel;
    }
    else return -1;
}
float last_total_score (char name[15], FILE *finfo)
{
    int p = 0;
    char checkname[15];
    float scores[25], result = 0;
    fseek (finfo, 0, SEEK_SET);
    fscanf (finfo, "%s", checkname);
    for ( ;!feof (finfo); fscanf(finfo, "%s", checkname))
    {
        if (strcmp (checkname, name) == 0)
        {
            fscanf (finfo, "%f", &scores[p]);
            p++;
        }
    }
    if (p > 0)
        result = scores[p-1];
    return result;
}

void find_best_ten (FILE *finfo)
{
    int find = 0;
    float latest_score[50];
    char checkname[15];
    fseek (finfo, 0, SEEK_SET);
    fscanf (finfo, "%s", checkname);
    for ( ; !feof (finfo); fscanf (finfo, "%s", checkname), find++)
    {
        fscanf (finfo, "%f", &latest_score[find]);
    }
    char btname[10];
    int  i, j, k, d = 0, temp, btlevel[d];
    float btls;
    for (i = 0; i < find; ++i)
    {
        for (j = 0; j < find-1; ++j)
        {
            if (latest_score[i] < latest_score[i+1])
            {
                temp = latest_score[i];
                latest_score[i] = latest_score[i+1];
                latest_score[i+1] = temp;
            }
        }
    }
    fbts = fopen ("best_ten.txt", "w+");
    fseek (fbts, 0, SEEK_SET);
    fseek (finfo, 0, SEEK_SET);
    for ( ; !feof( finfo ); d++)
    {
        if (d< 10)
        {
            fscanf (finfo, "%s", btname);
            fscanf (finfo, "%d", &btlevel[d]);
            fscanf (finfo, "%f", &btls);
            if (btls == latest_score[d])
            {
                fprintf (fbts, "%s\n%d\n%f\n", btname, btlevel[d], latest_score[d]) ;
            }
            if (btls != latest_score[d])
            {
                d--;
            }
        }
    }
}
void print_bt (FILE *fbts)
{
    int u, btlevel;
    float latest_score;
    char btname[15];
    for (u =0; u < 10; u++)
    {
        printf ("%d ** ", u);
        fseek (fbts, 0, SEEK_SET);
        fscanf (fbts, "%s", btname);
        printf ("name : %s", btname);
        fscanf (fbts, "%d", &btlevel);
        printf ("last level : %d", btlevel);
        fscanf ( fbts, "%f", &latest_score);
        printf ("last score : %f\n", latest_score);
    }
}
int main()
{
    int n, e = 0, rnd, choice_, choice, choice2, choice3, level_, q, w, x=0, j, tedad, u = 0, wrong = 0;
    float score[1000], pls[35], seconds = 0, total_score = 0;
    char word[25][60], my_word, name[15], edame;

    HANDLE hstdout = GetStdHandle (STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute (hstdout, 15);
    FILE *finfo;
    finfo = fopen ("info.txt","a+");
    SetConsoleTextAttribute (hstdout, 55);
    printf ( "Player name : \n\n" );
    SetConsoleTextAttribute (hstdout, 15);
    scanf ("%s" , name);
    SetConsoleTextAttribute (hstdout, 55);
    printf ("\nHi %s :-) R U ready to play?!\n\n", name);
    printf ("[1] Play a new game \n\n[2] Resume an old game\n\n");
    SetConsoleTextAttribute (hstdout, 15);
    scanf ("%d", &choice_);
    int max_files = file_counter ();
    while ((choice_ != 1) && (choice_ != 2)){
               SetConsoleTextAttribute (hstdout, 55);
               printf ("\nENTER 1 OR 2?!\n\n");
               printf ("[1] Play a new game \n\n[2] Resume an old game\n\n");
               SetConsoleTextAttribute (hstdout, 15);
               scanf ("%d", &choice_);
    }
    if (choice_ == 2)
    {
        level_ = give_level (name, finfo);
        if(give_level (name, finfo) == -1)
        {
            SetConsoleTextAttribute (hstdout, 55);
            printf ("\n you have not already saved anything\n\n you should start a new game\n\n");
            printf (" Please Enter the Level (now, I have at most %d levels):\n\n" , max_files);
            SetConsoleTextAttribute (hstdout, 15);
            scanf ("%d" , &level_);
            while(level_ >  max_files)
            {
                SetConsoleTextAttribute (hstdout, 55);
                printf ("\n Error\n\n");
                printf ( " Please Enter the Level (now, I have at most %d levels):\n\n" , max_files);
                SetConsoleTextAttribute (hstdout, 15);
                scanf ("%d", &level_);
            }
        }
    }
    if(choice_ == 1)
    {
        SetConsoleTextAttribute (hstdout, 55);
        printf ("\n Okay\n\n Please Enter the Level (now, I have at most %d levels):\n\n" , max_files);
        SetConsoleTextAttribute (hstdout, 15);
        scanf ("%d", &level_);
        while ((level_ >  max_files) || (level_ < 1))
        {
            SetConsoleTextAttribute (hstdout, 55);
            printf ("\n Error\n\n");
            printf (" Please Enter the Level (now, I have at most %d levels):\n\n", max_files);
            SetConsoleTextAttribute (hstdout, 15);
            scanf ("%d", &level_);
        }
    }

    while (5)
    {
        SetConsoleTextAttribute (hstdout, 15);
        inname (level_);
        for (w=0, n=0; word[w][n] != EOF; w++)
        {
            word[w][n] = fgetc (fpin);
            if (word[w][n] == ' ')
            {
                w = -1 ;
                n++;
            }
        }
        fclose (fpin);
        for (tedad = 0; tedad<n; tedad++)
        {
            system ("cls");
            time_t t = time(NULL);
            srand (t);
            rnd = (rand() * n) / (RAND_MAX);
            while (isupper (word[0][rnd]))
            {
                rnd = (rand()*n) / (RAND_MAX);
            }
            for (j=0; word[j][rnd] != ' '; j++)
            {
                if (j == 0)
                {
                    SetConsoleTextAttribute (hstdout, 12);
                    printf ("%c", word[j][rnd]);
                    SetConsoleTextAttribute (hstdout, 15);
                }
                else
                {
                    SetConsoleTextAttribute (hstdout, 14);
                    printf ("%c", word[j][rnd]);
                    SetConsoleTextAttribute (hstdout, 15);
                }
            }
            printf ("\n");
            clock_t start = clock ();
            SetConsoleTextAttribute (hstdout, 15);
            scanf ("%c", &my_word );
            if(my_word == 'P')
            {
                clock_t end = clock ();
                seconds += (float) (end - start) / CLOCKS_PER_SEC ;
                printf ("%f\n",seconds);
                SetConsoleTextAttribute (hstdout, 55);
                printf ("\nEnter R to resume\n\n");
                SetConsoleTextAttribute (hstdout, 15);
                scanf ("%c", &edame );
                while ( edame != 'R' )
                {
                    system ("cls");
                    SetConsoleTextAttribute (hstdout, 55);
                    printf ("\nEnter R to resume\n\n");
                    SetConsoleTextAttribute (hstdout, 15);
                    scanf ("%c", &edame );
                }
                clock_t start = clock ();
                SetConsoleTextAttribute (hstdout, 15);
                scanf ("%c", &my_word );
            }
            SetConsoleTextAttribute (hstdout, 15);
            for (q=0; word[q][rnd] != ' '; q++, scanf("%c", &my_word))
            {
                if (my_word == 'Q')
                {
                    return 0;
                }
                if (my_word == 'P')
                {
                    clock_t end = clock();
                    seconds += (float) (end - start) / CLOCKS_PER_SEC;
                    printf ("%f\n", seconds);
                    SetConsoleTextAttribute (hstdout, 55);
                    printf ("\nEnter R to resume\n\n");
                    SetConsoleTextAttribute (hstdout, 15);
                    scanf ("%c", &edame);
                    while (edame != 'R')
                    {
                        system ("cls");
                        SetConsoleTextAttribute (hstdout, 55);
                        printf ("\nEnter R to resume\n\n");
                        SetConsoleTextAttribute (hstdout, 15);
                        scanf ("%c", &edame);
                    }
                    clock_t start = clock ();
                    SetConsoleTextAttribute (hstdout, 15);
                    scanf ("%c", &my_word);
                }
                if (word[q][rnd] == my_word)
                {
                    word[q][rnd] = toupper (word[q][rnd]) ;
                    x++;
                }
                else
                {
                    q = q-1;
                    wrong++;
                }
                system ("cls");
                for (j=0; word[j][rnd] != ' '; j++)
                {
                    if (j == q+1)
                    {
                        SetConsoleTextAttribute (hstdout, 12);
                        printf ("%c", word[j][rnd]);
                        SetConsoleTextAttribute (hstdout, 15);
                    }
                    else
                    {
                        SetConsoleTextAttribute (hstdout, 14);
                        printf ("%c", word[j][rnd]);
                        SetConsoleTextAttribute (hstdout, 15);
                    }
                }
                printf ("\n");
            }
            SetConsoleTextAttribute (hstdout, 15);
            clock_t end = clock();
            seconds += (float) (end - start) / CLOCKS_PER_SEC ;
            score[u] = (float) (x * 3 - wrong) / seconds;
            u++;
        }
        system ("cls");
        int y;
        float sum = 0;
        for (y = 0; y < u; y++)
            sum += score[y];
        pls[e]=sum/n;
        total_score += pls[e];
        SetConsoleTextAttribute (hstdout, 55);
        total_score += last_total_score ( name, finfo);
        printf ("\n your last total score : %f\n\n", total_score);
        printf (" save ?\n\n [1]yes\n\n [2]no\n\n");
        SetConsoleTextAttribute (hstdout, 15);
        scanf ("%d", &choice3);
        while ((choice3 != 1) && (choice3 != 2)){
            SetConsoleTextAttribute (hstdout, 55);
            printf ("\n Enter 1 or 2\n\n");
            printf (" save ?\n\n [1]yes\n\n [2]no\n\n");
            SetConsoleTextAttribute (hstdout, 15);
            scanf ("%d", &choice3);
        }
        if (choice3 == 1)
        {
            SetConsoleTextAttribute (hstdout, 55);
            fprintf (finfo, "\n%s\n\n%d\n\n%f\n\n", name, level_, total_score);
            SetConsoleTextAttribute (hstdout, 15);
        }
        level_++;
        e++;
        // find_best_ten(finfo) ;
        SetConsoleTextAttribute (hstdout, 55);
        printf ("\n what is your decision ? \n\n [1]Exit\n\n [2]next level \n\n");
        SetConsoleTextAttribute (hstdout, 15);
        scanf("%d", &choice2);
        while ((choice2 != 1) && (choice2 != 2)){
            SetConsoleTextAttribute (hstdout, 55);
            printf ("\n Enter 1 or 2 \n\n");
            printf ("[1]Exit\n\n [2]next level \n\n");
            SetConsoleTextAttribute (hstdout, 15);
            scanf ("%d", &choice2);
        }
        if (choice2 == 1)
        {
            system ("cls");
            SetConsoleTextAttribute (hstdout, 55);
            printf ("\n your last total score : %f\n\n", total_score);
            SetConsoleTextAttribute (hstdout, 15);
            /* printf( " top ten scores :\n");
             print_bt( fbts ) ;
             fclose( fbts ) ;*/
            return 0;
        }
        if (level_ > max_files +1)
        {
            system ("cls");
            SetConsoleTextAttribute (hstdout, 55);
            printf ("\n no more level :| \n\n");
            printf (" your last total score : %f\n\n", total_score);
            SetConsoleTextAttribute (hstdout, 15);
            fclose (finfo);
            /* printf( " top ten scores :\n");
             print_bt( fbts ) ;
             fclose( fbts ) ;*/
            return 0;
        }
    }
}


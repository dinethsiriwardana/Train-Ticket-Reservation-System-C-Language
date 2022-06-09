#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void bookedlist(char *username);
void deletebooking(int bookno, char *username);

void deletebooking(int bookno, char *username)
{

    FILE *file = fopen("savefile/userdata/dineths.txt", "r");

    FILE *filebkp = fopen("savefile/userdata/dinethsbkp.txt", "w");

    if (!file)
    {
        printf("\n Unable to open : ");
        return;
    }
    char line[500];
    char deletecon;
    int lineno = 1;
    while (fgets(line, sizeof(line), file))
    {

        if (lineno != bookno)
        {
            // printf("%d. %s",lineno ,line);
            fprintf(filebkp, "%s", line);
        }
        else
        {
            printf("Remove this line: %d. %s", lineno, line);
            printf("Are you Sure: [Y/N]:");
            scanf(" %c", &deletecon);
            if (deletecon == 'N' || deletecon == 'n')
            {
                fprintf(filebkp, "%s", line);
            }
        }
        lineno++;
    }
    fclose(file);
    if (deletecon == 'N' || deletecon == 'n')
    {
        if (remove("savefile/userdata/asd.txt") == 0)
        {
        rename("savefile/userdata/aa.txt", "savefile/userdata/asd.txt");
        }
    }

    printf("\n");
}

void bookedlist(char *username)
{
    
    // char fileurlfirst = "savefile/userdata/";
    // char fileurlend = ".txt";
    char filename;
    strcat(filename , "savefile/userdata/");

    FILE *file = fopen("savefile/userdata/dineths.txt", "r");

    if (!file)
    {
        printf("\n Unable to open : ");
        return;
    }
    char line[500];
    char data[10];
    int lineno = 1;

    while (fgets(line, sizeof(line), file))
    {
        printf("%d. %s", lineno, line);
        lineno++;
    }
    fclose(file);

    printf("\n");
}
int main()
{
    char filename = "s";
    strcat(filename , "savefile/userdata/");
    char *username = "dineths";
    int bookno;
    bookedlist(username);
    printf("\nPress the number for delete booking ");
    scanf("%d", &bookno);
    deletebooking(bookno, username);
    return 0;
}

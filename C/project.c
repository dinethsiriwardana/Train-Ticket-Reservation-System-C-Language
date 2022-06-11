#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void bookedlist(char username[]);
void deletebooking(int bookno, char username[]);

int main()
{

    char username[100] = "dineths";
    int bookno;
    bookedlist(username);
    printf("\nPress the number for delete booking : ");
    scanf("%d", &bookno);
    deletebooking(bookno, username);
    return 0;
}


void bookedlist(char username[])
{
    
    char fileurlfirst[100] = "savefile/userdata/";

    char filename[500] = "";
    strcat(filename , fileurlfirst);
    strcat(filename , username);
    strcat(filename , ".txt");

    FILE *file = fopen(filename, "r");

    if (!file)
    {
        printf("\n Unable to open : ");
        return;
    }
    char line[500];
    char data[10];
    int lineno = 1;
    printf("************* User Recording of  Username - %s *************** \n\n", username);
    while (fgets(line, sizeof(line), file))
    {
        printf("%d. %s", lineno, line);
        lineno++;
    }
    fclose(file);

    printf("\n");
}



void deletebooking(int bookno, char username[])
{

    char fileurlfirst[100] = "savefile/userdata/";
    char filename[500] = "";
    char filenamebkp[500] = "";
    strcat(filename , fileurlfirst);
    strcat(filename , username);
    strcat(filename , ".txt");

    strcat(filenamebkp , fileurlfirst);
    strcat(filenamebkp , username);
    strcat(filenamebkp , "bkp.txt");
    FILE *file = fopen(filename, "r");
    FILE *filebkp = fopen(filenamebkp, "w");

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
            fprintf(filebkp, "%s", line);
        }
        else
        {
            printf("\nSystem will remove this booking:  No: %d - %s", lineno, line);
            printf("Are you Sure: [Y/N]: ");
            scanf(" %c", &deletecon);
            if (deletecon == 'N' || deletecon == 'n')
            {
                fprintf(filebkp, "%s", line);
            }
        }
        lineno++;
    }
    fclose(file);
    if (deletecon != 'N' || deletecon != 'n')
    {
        printf("Deleting...");
        if (remove(filename) == 0)
        {
        if (rename(filenamebkp, filename) == 0) {
            printf("\nDeleting Complete");
        }
        }
    }

    printf("\n");
}

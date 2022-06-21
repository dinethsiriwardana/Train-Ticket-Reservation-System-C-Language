#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

void userRegister();
void userlogin();
void pricecal();
int trainlist();
int displaymeanu(int input);
int seeMore(int input);
int stop(int line);
void passengeroption();
void passengers();
void locationcal();
void payment();
void valid();
int datecvv();
void parcel();
int instructions();
float Weight(float);
void bookedlist();
void deletebooking(int bookno);

char userId[50];
char username[50];
char location_name[11][25] = {"Badulla [0]", "Bandarawela [1]", "Hatton [2]", "Peradeniya Junction [3]", "Polgahawela Junction [4]", "Gampha [5]", "Maradana [6]", "Colombo Fort [7]", "Panadura [8]", "Galle [9]", "Matara [10]"};
int from, to;
float classc_price;
float totalcost;
float classc_passnger_price, parcel_far;

FILE *booking;

int main()
{

	printf("\n\n\n\t*********************************************************** \n");
	printf("\t*                                                         * \n");
	printf("\t*        Welcome - Train Ticket Reservation System        * \n");
	printf("\t*                                                         * \n");
	printf("\t*********************************************************** \n\n\n");

	printf("\t**   Menu   ** \n\n");
	printf("\t [1] - Login \n");
	printf("\t [2] - Register \n\n");

	int navi;
	int subnavi;
	printf("\tPress the number for option : ");
	scanf("%d", &navi);
	fgetc(stdin);

	if (navi == 2)
	{
		userRegister();
		userlogin();
	}
	else if (navi == 1)
	{
		userlogin();
	}
	else
	{
		printf("\tError - Wrong Number\n");
		return 0;
	}
	do
	{
		printf("\n\n\n\t*********************************************************** \n");
		printf("\t*                                                         * \n");
		printf("\t*  Welcome - Train Ticket Reservation System - User area  * \n");
		printf("\t*                                                         * \n");
		printf("\t*********************************************************** \n\n\n");

		printf("\t**   Menu   ** \n\n");
		printf("\t [1] - Time Table \n");
		printf("\t [2] - Calculator \n");
		printf("\t [3] - Booking \n");
		printf("\t [4] - Remove \n");
		printf("\t [0] - Exit \n");
		printf("\tPress the number for option : ");
		scanf("%d", &subnavi);

		int subnavi2;
		if (subnavi == 1)
		{
			trainlist();
		}
		else if (subnavi == 2)
		{
				pricecal();	
		}
		else if (subnavi == 3)
		{
			int booktype; // booking type (parcel or passenger)
			do
			{
				printf("\n\n\t\t\t******* BOOK YOUR TICKET NOW *******\n\n");
				printf("\n\n\t\t\tPassengers [1]\n\t\t\tParcel [2]\n\t\t\tExit [3]\n\n\n");
				printf("\t\t\tEnter choice: ");
				scanf("%d", &booktype);

				switch (booktype)
				{
				case 1:
					passengeroption();
					break;
				case 2:
					parcel();
					break;
				case 3:
					printf("\n\n\t\t\tClosing ...");
					break;
				default:
					printf("\n\n\t\t\tInvalid choice!\n\n");
				}

			} while (booktype != 3);
		}
		else if (subnavi == 4)
		{
			int bookno;
			bookedlist();
			printf("\nPress the number for delete booking : ");
			scanf("%d", &bookno);
			deletebooking(bookno);
		}

		printf("\n\tPress [1] For Open Menu \n");
		printf("\tPress [0] For Exit \n");
		printf("\tPress the Number :- ");
		scanf("%d", &subnavi);
	} while (subnavi != 0);
}

void deletebooking(int bookno)
{

	char filenamebkp[500] = "";
	strcat(filenamebkp, userId);
	strcat(filenamebkp, "bkp.txt");
	FILE *file = fopen(userId, "r");
	FILE *filebkp = fopen(filenamebkp, "w");

	if (!file)
	{
		printf("\n Unable to open : %s",userId);
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
		if (remove(userId) == 0)
		{
			if (rename(filenamebkp, userId) == 0)
			{
				printf("\nDeleting Complete");
			}
		}
	}
	fclose(filebkp);
	printf("\n");
}

void bookedlist()
{

	FILE *file = fopen(userId, "r");

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

int trainlist()
{
	int displaymeanu(int input);
	int seeMore(int input);
	int stop(int line);

	int line;
	char more_details;

	printf("01.Main Line\n\n02. North Line \n\n03. Puttalama Line \n\n04. Kelni Valley Line\n\n");

	printf("Enter the Your Line Number  :");
	scanf("%d", &line);

	displaymeanu(line);

	printf("\nDo You Want to See more details Y/N : ");
	scanf(" %c", &more_details);

	if (more_details == 'y' || more_details == 'Y')
	{

		seeMore(line);
		stop(line);
	}
	else
	{
		printf("Thanks Using The System");
		return 0;
	}
}

int displaymeanu(int input)
{
	FILE *rptr;
	char name[20];
	char from[20];
	char departure[5];
	char to[20];
	char arrival[5];
	char type[20];
	char id[20];

	switch (input)
	{

	case 1:
		rptr = fopen("trainlist/main_line.txt", "r");
		if (rptr == NULL)
		{

			printf("Cannot Open the file !");
			return 0;
		}
		printf("************************Main line*************************\n");
		fscanf(rptr, "%s %s %s %s %s %s %s", id, name, from, departure, to, arrival, type);
		while (!feof(rptr))
		{
			printf("\n%s\t%s", id, name);
			fscanf(rptr, "%s %s %s %s %s %s %s", id, name, from, departure, to, arrival, type);
		}
		break;

	case 2:
		rptr = fopen("trainlist/trainlist/north_line.txt", "r");
		if (rptr == NULL)
		{

			printf("Cannot Open the file !");
			return 0;
		}
		printf("*************************North line*************************\n");
		fscanf(rptr, "%s %s %s %s %s %s %s", id, name, from, departure, to, arrival, type);
		while (!feof(rptr))
		{
			printf("\n%s\t%s", id, name);
			fscanf(rptr, "%s %s %s %s %s %s %s", id, name, from, departure, to, arrival, type);
		}
		break;

	case 3:
		rptr = fopen("trainlist/puththalama_line.txt", "r");
		if (rptr == NULL)
		{

			printf("Cannot Open the file !");
			return 0;
		}
		printf("*************************Puththalama Line*************************\n");
		fscanf(rptr, "%s %s %s %s %s %s %s", id, name, from, departure, to, arrival, type);
		while (!feof(rptr))
		{
			printf("\n%s\t%s", id, name);
			fscanf(rptr, "%s %s %s %s %s %s %s", id, name, from, departure, to, arrival, type);
		}
		break;

	case 4:
		rptr = fopen("trainlist/kalani_vali_line.txt", "r");
		if (rptr == NULL)
		{

			printf("Cannot Open the file !");
			return 0;
		}
		printf("*************************Kelni Valley Line*************************\n");
		fscanf(rptr, "%s %s %s %s %s %s %s", id, name, from, departure, to, arrival, type);
		while (!feof(rptr))
		{
			printf("\n%s\t%s", id, name);
			fscanf(rptr, "%s %s %s %s %s %s %s", id, name, from, departure, to, arrival, type);
		}
		break;
	}
}

int seeMore(int input)
{
	FILE *rptr;
	char name[20];
	char from[20];
	char departure[5];
	char to[20];
	char arrival[5];
	char type[20];
	char id[6];

	switch (input)
	{

	case 1:
		rptr = fopen("trainlist/main_line.txt", "r");
		if (rptr == NULL)
		{

			printf("Cannot Open the file !");
			return 0;
		}
		printf("*************************More Details*************************\n");
		fscanf(rptr, "%s %s %s %s %s %s %s ", id, name, from, departure, to, arrival, type);
		while (!feof(rptr))
		{
			printf("%s\t %s\t %s\t %s\t %s\t %s\t%s\n", id, name, from, departure, to, arrival, type);
			fscanf(rptr, "%s %s %s %s %s %s %s", id, name, from, departure, to, arrival, type);
		}

		break;

	case 2:
		rptr = fopen("trainlist/north_line.txt", "r");
		if (rptr == NULL)
		{

			printf("Cannot Open the file !");
			return 0;
		}
		printf("*************************More Details*************************\n");
		fscanf(rptr, "%s %s %s %s %s %s %s ", id, name, from, departure, to, arrival, type);
		while (!feof(rptr))
		{
			printf("%s\t %s\t %s\t %s\t %s\t %s\t%s\n", id, name, from, departure, to, arrival, type);
			fscanf(rptr, "%s %s %s %s %s %s %s", id, name, from, departure, to, arrival, type);
		}
		break;

	case 3:
		rptr = fopen("trainlist/puththalama_line.txt", "r");
		if (rptr == NULL)
		{

			printf("Cannot Open the file !");
			return 0;
		}
		printf("*************************More Details*************************\n");
		fscanf(rptr, "%s %s %s %s %s %s %s ", id, name, from, departure, to, arrival, type);
		while (!feof(rptr))
		{
			printf("%s\t %s\t %s\t %s\t %s\t %s\t%s\n", id, name, from, departure, to, arrival, type);
			fscanf(rptr, "%s %s %s %s %s %s %s", id, name, from, departure, to, arrival, type);
		}
		break;

	case 4:
		printf("*************************More Details*************************\n");
		rptr = fopen("trainlist/kalani_vali_line.txt", "r");
		if (rptr == NULL)
		{

			printf("Cannot Open the file !");
			return 0;
		}
		fscanf(rptr, "%s %s %s %s %s %s %s ", id, name, from, departure, to, arrival, type);
		while (!feof(rptr))
		{
			printf("%s\t %s\t %s\t %s\t %s\t %s\t%s\n", id, name, from, departure, to, arrival, type);
			fscanf(rptr, "%s %s %s %s %s %s %s", id, name, from, departure, to, arrival, type);
		}
		break;
	}
}

int stop(int line)
{

	char one[20];
	char two[20];
	char three[20];
	FILE *rptr;

	switch (line)
	{

	case 1:
		rptr = fopen("trainlist/main_stop.txt", "r");
		if (rptr == NULL)
		{

			printf("Cannot Open the file !");
			return 0;
		}
		fscanf(rptr, "%s %s %s", one, two, three);
		printf("\n\n **********All trains will stop at the following stations **********\n");
		while (!feof(rptr))
		{
			printf("%s\t %s\t %s\t\n", one, two, three);
			fscanf(rptr, "%s %s %s", one, two, three);
		}
		break;
	case 2:
		rptr = fopen("trainlist/north_stop.txt", "r");
		if (rptr == NULL)
		{

			printf("Cannot Open the file !");
			return 0;
		}
		fscanf(rptr, "%s %s %s", one, two, three);
		printf("\n\n **********All trains will stop at the following stations **********\n");
		while (!feof(rptr))
		{
			printf("%s\t %s\t %s\t\n", one, two, three);
			fscanf(rptr, "%s %s %s", one, two, three);
		}
		break;
	case 3:
		rptr = fopen("trainlist/puththalam_stop.txt", "r");
		if (rptr == NULL)
		{

			printf("Cannot Open the file !");
			return 0;
		}
		fscanf(rptr, "%s %s %s", one, two, three);
		printf("\n\n**********All trains will stop at the following stations **********\n");
		while (!feof(rptr))
		{
			printf("%s\t %s\t %s\t\n", one, two, three);
			fscanf(rptr, "%s %s %s", one, two, three);
		}
		break;
	}
}

void pricecal()
{

	printf("\n\n\n\t*********************************************************** \n");
	printf("\t*                                                         * \n");
	printf("\t* Welcome - Train Ticket Reservation System - Calculator  * \n");
	printf("\t*                                                         * \n");
	printf("\t*********************************************************** \n\n\n");

	int from;
	int to;
	int distance;
	double cost;
	double total_cost;
	int fstclass;
	int sndclass;
	int trdclass;

	printf("Select the Start and end points using numbers \n");

	printf("\nFrom \n");
	printf("0.Badulla\n1.Bandarawela\n2.Hatton\n3.Peradeniya Junction\n4.Polgahawela Junction\n5.Gampaha\n6.Maradana\n7.Colombo Fort\n8.Panadura\n9.Galle\n10.Matara\n");

	printf("\nEnter Start points using number:  \n");
	printf("From : ");
	scanf("%d", &from);

	printf("\nTo \n");
	printf("0.Badulla\n1.Bandarawela\n2.Hatton\n3.Peradeniya Junction\n4.Polgahawela Junction\n5.Gampaha\n6.Maradana\n7.Colombo Fort\n8.Panadura\n9.Galle\n10.Matara\n");

	printf("\nEnter End points using number:  \n");
	printf("To : ");
	scanf("%d", &to);
	printf("\n");

	distance = from - to;
	printf("\n");

	switch (distance)
	{
	case 1:
	case -1:
		cost = 300;
		break;
	case 2:
	case -2:
		cost = 350;
		break;
	case 3:
	case -3:
		cost = 400;
		break;
	case 4:
	case -4:
		cost = 450;
		break;
	case 5:
	case -5:
		cost = 500;
		break;
	case 6:
	case -6:
		cost = 550;
		break;
	case 7:
	case -7:
		cost = 600;
		break;
	case 8:
	case -8:
		cost = 650;
		break;
	case 9:
	case -9:
		cost = 700;
		break;
	case 10:
	case -10:
		cost = 750;
		break;
	default:
		printf("\nInvalid distance number\n\n");
	}

	printf("No Of tickets for First Class : ");
	scanf("%d", &fstclass);
	printf("No Of tickets for Second Class : ");
	scanf("%d", &sndclass);
	printf("No Of tickets for Third Class : ");
	scanf("%d", &trdclass);

	int costforclass1 = (fstclass * cost) + (fstclass * cost * 0.5);
	int costforclass2 = (sndclass * cost) + (sndclass * cost * 0.25);
	int costforclass3 = (trdclass * cost);
	total_cost = costforclass1 + costforclass2 + costforclass3;
	printf("\n\n");

	printf("Total Price = %.2f\n", total_cost);
}

void userlogin()
{
	FILE *rfp;

	char name[100], password[10], email[50], newline;
	char userEmail[50], userPassword[10];
	int Vemail, Vpass;
	int errLog;

	do
	{
		rfp = fopen("Data.txt", "r");

		if (rfp == NULL)
		{
			printf("ERROR connecting database\n");
			exit(1);
		}

		printf("\n---------------------------------User-LogIn------------------------------\n\n");

		errLog = 0;
		printf("Enter your email: ");
		scanf(" %s", userEmail);

		printf("\nEnter your password: ");
		scanf(" %s", userPassword);

		/*printf("Read username from user: %s ",userEmail);
		printf("Read userpassword from user: %s ",userPassword);*/

		do
		{
			fgets(name, 100, rfp);
			fscanf(rfp, "%s", password);
			fscanf(rfp, "%s", email);
			newline = fgetc(rfp);
			newline = fgetc(rfp);

			/*printf("\n\n\nRead name from file: %s ",name);
			printf("Read Email from file: %s ",email);
			printf("REad password from file: %s ",password);
			printf("Read newline from file: %c ",newline);*/

			Vemail = strcmp(userEmail, email);
			Vpass = strcmp(userPassword, password);

			if ((Vemail == 0) && (Vpass == 0))
			{
				/*printf("\nyou were get correct email and password from file \n");*/
				break;
			}

		} while (!feof(rfp));

		if ((Vemail == 0) && (Vpass == 0))
		{
			printf("\n\nYou have successfully logged In\n");
			printf("\nHi ,%s\n\n", name);
		}
		else
		{
			printf("\n\nYour Email or Password is Incorrect\n");
			errLog += 1;
		}

		fclose(rfp);

	} while (errLog == 1);

	int i;
	for (i = 0; i < strlen(email); i++)
	{

		if (email[i] == '@')
		{
			break;
		}
		else
		{
			userId[i] = email[i];
		}
	}
	strcat(username, userId);
	strcat(userId, ".txt");

	// printf("User Id data : %s\n",userId);
}

void userRegister()

{

	FILE *fp;
	char name[100], password[10], email[50];
	int i, tLetter, nameLength, fLetter;
	char ch;

	fp = fopen("Data.txt", "a");

	printf("\n\t\t\t---------------------------------\n");
	printf("\t\t\t|\tUser Registration\t|\n");
	printf("\t\t\t---------------------------------\n\n");

	if (fp == NULL)
	{
		printf("Can't connect to DataBase\n");
		exit(1);
	}

	do
	{
		tLetter = 0;
		fLetter = 0;

		printf("\t-----Enter your Name-------------------------------------------------------\n");
		printf("\tINSTRUCTIONS:- Name should be contain only Letters, Sapces, and Fullstops\n\n\t");
		fgets(name, 100, stdin);

		nameLength = strlen(name) - 1;

		for (i = 0; i < nameLength; i++)
		{
			ch = name[i];
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == ' ') || (ch == '.'))
			{
				tLetter += 1;
			}
			else
			{
				fLetter += 1;
			}
		}

		if (nameLength == tLetter)
		{
			fprintf(fp, "%s", name); // name printed into file
		}
		else
		{
			printf("\t\t!!!Your name contains invalid characters!!!\n");
			printf("\t\t\t\tTRY-AGAIN\n\n");
		}

	} while (nameLength != tLetter);

	// Enter password
	int passwordLength, special, numbers;
	char confPassword[10];
	int valiPass;

	do
	{
		tLetter = 0;
		fLetter = 0;
		special = 0;
		numbers = 0;

		printf("\n\t-----Enter your password---------------------------------------------------\n");
		printf("\tINSTRUCTIONS:-Accecept only 8 characters with at least one of these ");
		printf("%c %c %c %c %c\n\n\t", '@', '#', '$', '%', '*');
		scanf("%s", password);

		passwordLength = strlen(password);

		for (i = 0; i < passwordLength; i++)
		{
			ch = password[i];

			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
			{
				tLetter += 1;
			}
			else if ((ch >= '0' && ch <= '9'))
			{
				numbers += 1;
			}
			else if ((ch == '@') || (ch == '#') || (ch == '$') || (ch == '%') || (ch == '*'))
			{
				special += 1;
			}
			else
			{
				fLetter += 1;
			}
		}

		if (((tLetter + special + numbers) == 8) && (special > 0))
		{

			// re-enter password
			printf("\n\t-----Confirm Password:---------------------------------------------\n\n\t");
			do
			{

				valiPass = 1;

				scanf("%s", confPassword);
				fgetc(stdin);

				valiPass = strcmp(password, confPassword);

				if (valiPass == 0)
				{
					printf("\n\t\t\t***Password confirmed***\n");
				}

				else
				{
					printf("\n\t\t\t!!!Password not similer to previous one!!!\n");
					printf("\t\t\t\tTRY-AGAIN\n\n\t");
				}

			} while (!(valiPass == 0));

			fprintf(fp, "%s\n", password); // password written to the file
		}
		else
		{
			printf("\t\t!!!Your password is not acceptable!!!\n");
			printf("\t\t\t\tTRY-AGAIN\n\n");
		}

	} while (!(((tLetter + special + numbers) == 8) && (special > 0)));

	int emailLength, compL;
	int existEmail;

	do
	{
		tLetter = 0;
		compL = 0;
		fLetter = 0;

		printf("\n\t-----Enter your E-mail---------------------------------------------------\n");
		printf("\tINSTRUCTIONS:-E-mail should be contain Letters,%c , and Pulstops\n\n\t", '@');

		fgets(email, 50, stdin);

		emailLength = strlen(email) - 1;

		for (i = 0; i < emailLength; i++)
		{
			ch = email[i];
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'))
			{
				tLetter += 1;
			}
			else if ((ch == '@' || ch == '.'))
			{
				compL += 1;
			}

			else
			{
				fLetter += 1;
			}
		}

		// checking email exist or not
		char name[100], password[10], Emails[50], newline;

		FILE *erfp;
		erfp = fopen("Data.txt", "r");

		do
		{
			existEmail = 1;

			fgets(name, 100, erfp);
			fgets(password, 10, erfp);
			fgets(Emails, 50, erfp);
			newline = fgetc(erfp);

			existEmail = strcmp(email, Emails);

			if (existEmail == 0)
			{
				break;
				printf("Email is Used before\n");
			}

		} while (!feof(erfp));

		fclose(erfp);

		if ((emailLength == (tLetter + compL)) && (compL >= 2) && (existEmail != 0))
		{
			fprintf(fp, "%s", email);
			printf("\n\t***Your registration has been successfully completed***\n\n");
		}
		else if (existEmail == 0)
		{
			printf("\n\t!!!ERROR - Anyone has registered under this e-mail!!!\n\t\t\tUse another email address\n\n");
		}
		else
		{
			printf("\n\t!!!Your e-mail contains invalid characters or not contain compulsory characters!!!\n");
			printf("\t\t\t\tTRY-AGAIN\n\n");
		}

	} while (!((emailLength == (tLetter + compL)) && (compL >= 2) && (existEmail != 0)));
	//

	fputc('\n', fp);
	fclose(fp);
}

void passengeroption()
{
	char ch;
	int option;
	do
	{
		printf("\n\t\t\tBooking [1]\tView Booking [2]\tMain Menu [3]\tExit [4]");
		printf("\n\t\t\tEnter choice: ");
		scanf("%d", &option);
		switch (option)
		{
		case 1:
			passengers();
			break;
		case 2:
			booking = fopen(userId, "r");
			if (NULL == booking)
			{
				printf("\n\t\t\tFile can't be opened * NO PREVIOUS BOOKING *\n");
			}
			else
			{

				do
				{
					ch = fgetc(booking);
					printf("%c", ch);
				} while (ch != EOF);
				fclose(booking);
			}
			break;
		case 3:
			main();
			break;
		case 4:
			exit(0);
			break;
		}
	} while (option != 4);
}

void passengers()
{

	char bookagain; // to repeat do while
	int trainID, classa, classb, classc;
	float suma, sumb, sumc;
	char confirm;

	do
	{

		// Time
		time_t t;
		t = time(NULL);
		struct tm tm = *localtime(&t);

		printf("\n\t\t\tUser name : %s", userId);
		printf("\n\t\t\tCurrent Date: %d-%d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

		printf("\n\t\t\tEnter Train ID: ");
		scanf("%d", &trainID);

		locationcal();

		printf("\n\t\t\tNo Of tickets for First Class : ");
		scanf("%d", &classa);
		suma = (classc_price * 0.5 + classc_price) * classa;
		printf("\t\t\tNo Of tickets for Second Class : ");
		scanf("%d", &classb);
		sumb = (classc_price * 0.25 + classc_price) * classb;
		printf("\t\t\tNo Of tickets for Third Class : ");
		scanf("%d", &classc);
		sumc = (classc_price)*classc;
		totalcost = suma + sumb + sumc;
		printf("\n\t\t\tConfirm? [Y/N] : ");
		scanf(" %c", &confirm);

		if (confirm == 'y' || confirm == 'Y')
		{
			payment();
			booking = fopen(userId, "a");

			// Time
			time_t t;
			t = time(NULL);
			struct tm tm = *localtime(&t);

			fprintf(booking, "\t\t\t%d-%d-%d, %.2f, %s, %s, %d, %d, %d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, totalcost, location_name[from], location_name[to], classa, classb, classc);
			fclose(booking);
			printf("\n\t\t\tBOOKED SUCCESSFULLY!");
			printf("\n\n\t\t\t*** TOTAL COST FOR TICKETS FROM '%s' - TO '%s' ***\n\t\t\tClass A Tickets - %d\tClass B Tickets - %d\tClass C Tickets - %d\tTotal Cost: %.2f\n", location_name[from], location_name[to], classa, classb, classc, totalcost);
		}
		else
		{
			printf("\n\t\t\tCanceled!");
		}
		printf("\n\t\t\tDo you want to Book for another journey? [Y/N]: ");
		scanf(" %c", &bookagain);

	} while (bookagain == 'Y' || bookagain == 'y');
}

void locationcal()
{ // location and calculate cost

	int location[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int price[] = {300, 350, 400, 450, 500, 550, 600, 650, 700, 750};
	int far[] = {25, 40, 55, 70, 85, 100, 115, 130, 145, 160};
	int x, distance;

	printf("\n\t\t\t******* List of Location *******\n\n");
	for (x = 0; x <= 10; x++)
	{
		printf("\t\t\t\t%s\n", location_name[x]);
	}

	printf("\n\t\t\tFrom: ");
	scanf("%d", &from);
	printf("\n\t\t\tTo: ");
	scanf("%d", &to);
	if ((from <= 10 && from >= 0) && (to <= 10 && to >= 0))
	{
		distance = to - from;
		if (distance < 0)
		{
			distance *= -1;
		}

		classc_price = price[distance - 1];
		parcel_far = far[distance - 1];
	}
	else
	{
		printf("\n\t\t\tInvalid Inputs .. Please Enter again!\n\n");
		printf("\n\t\t\t-------------------------------------\n\n");
		locationcal();
	}
}

void payment()
{
	int num, number;

	num = datecvv();

	if (num == 1)
	{
		printf("\t\t\t*              VISA             * \n");
		valid();
	}
	else if (num == 2)
	{
		printf("\t\t\t*            MASTERCARD         * \n");
		valid();
	}
	else
	{
		printf("\t\t\t*   INVALID (Please try again)  * \n");
		payment();
	}
}

void valid()
{

	int month = 0, year = 0, cvv = 0;

	printf("\t\t\t********************************* \n");
	printf("\t\t\t*     Expiration date(MM/YY)    * \n");
	printf("\t\t\t*                               * \n");
	printf("\t\t\t               ");
	scanf("%d/%d", &month, &year);

	printf("\t\t\t*               CVV             * \n");
	printf("\t\t\t               ");
	scanf("%d", &cvv);

	if ((1000 > cvv && cvv > 99) && (13 > month && month > 0) && (year > 21))
	{

		printf("\t\t\tYour payment is successful\n");
	}
	else
	{
		printf("\t\t\tInvalid payment\n");
		instructions();
	}
}

int datecvv()
{
	long creditCardNumber;
	do
	{
		printf("\t\t\t*********************************      \n");
		printf("\t\t\t*     Please input CC number:   *       \n");
		printf("\t\t\t      ");
		scanf("%ld", &creditCardNumber);

	} while (creditCardNumber <= 0);

	long workingCC = creditCardNumber;
	int sum = 0;
	int count = 0;
	long divisor = 10;
	int number = 0;

	// 1st
	while (workingCC > 0)
	{
		int lastDigit = workingCC % 10;
		sum = sum + lastDigit;
		workingCC = workingCC / 100;
	}

	// 2nd
	workingCC = creditCardNumber / 10;
	while (workingCC > 0)
	{
		int lastDigit = workingCC % 10;
		int timesTwo = lastDigit * 2;
		sum = sum + (timesTwo % 10) + (timesTwo / 10);
		workingCC = workingCC / 100;
	}

	// length of the number / digit count
	workingCC = creditCardNumber;
	while (workingCC != 0)
	{
		workingCC = workingCC / 10;
		count++;
	}
	int i;
	// divisor
	for (i = 0; i < count - 2; i++)
	{
		divisor = divisor * 10;
	}

	int firstDigit = creditCardNumber / divisor;
	int firstTwoDigits = creditCardNumber / (divisor / 10);

	// final checks
	if (sum % 10 == 0)
	{
		if (firstDigit == 4 && (count == 13 || count == 16))
		{
			number = 1;
		}
		else if ((firstTwoDigits == 53 || firstTwoDigits == 37) && count == 16)
		{
			number = 2;
		}
		else if ((50 < firstTwoDigits && firstTwoDigits < 56) && count == 16)
		{
			number = 3;
		}
		else
		{
			number = 4;
		}
	}
	else
	{
		number = 4;
	}

	return number;
}

int instructions()
{

	int user_idea;

	printf("\t\t\t************************************************************************************* \n");
	printf("\t\t\t*   1.When You Enter the card number you have to enter 16 number in the your card   * \n\n");
	printf("\t\t\t*   2.When You Enter the valid date you have to firsh enter month and the enter /   * \n\n");
	printf("\t\t\t*    mark and enter the year ,using two number(EX-2023 you have to input - 23)      *  \n\n");
	printf("\t\t\t*   3.Then you have to enter your cvv pin                                           *  \n\n");
	printf("\t\t\t******************************************************************************************** \n");
	printf("\t\t\t*                                                                                          *\n");
	printf("\t\t\t* If you want to contune please enter 1 and If you do not want to contune please enter 0 : *\n");
	printf("\t\t\t*                                                                                          *\n");
	printf("\t\t\t******************************************************************************************** \n\t\t\t");
	scanf("%d", &user_idea);

	switch (user_idea)
	{

	case 0:
		printf("\t\t\t                *            Payment Canceled          *\n");
		exit(0);
		break;

	case 1:
		payment();
		break;
	default:
		break;
	}
}

void parcel()
{

	locationcal();
	float WEIGHT, Totalprice, nomalprice;
	int traintype;

	while (1)
	{
		printf("\n\n\t\t\tInput WEIGHT(ONLY from 0kg to 100Kg):");
		scanf("%f", &WEIGHT);
		if (WEIGHT <= 100)
		{
			break;
		}
		else
		{
			printf("\t\t\tOnly from 1kg to 100Kg Please enter again!!");
		}
	}

	printf("\n\t\t\tTrain Type:");
	printf("\n\t\t\t\t\t1.Normal Train");
	printf("\n\t\t\t\t\t2.Express Train\n\n");
	printf("\n\t\t\tSelect Train:");
	scanf("%d", &traintype);

	if (parcel_far >= 0 && parcel_far <= 25)
	{
		nomalprice = Weight(WEIGHT);
		Totalprice = nomalprice;
		printf("\n\t\t\tTotal pament for transpoting your parcel= RS.%.2f", Totalprice);
	}

	else if (parcel_far >= 26 && parcel_far <= 40)
	{

		nomalprice = Weight(WEIGHT);
		Totalprice = nomalprice + (3 * traintype);
		printf("\n\t\t\tTotal pament for transpoting your parcel= RS.%.2f", Totalprice);
	}
	else if (parcel_far >= 41 && parcel_far <= 55)
	{

		nomalprice = Weight(WEIGHT);
		Totalprice = nomalprice + (6 * traintype);
		printf("\n\t\t\tTotal pament for transpoting your parcel= RS.%.2f", Totalprice);
	}
	else if (parcel_far >= 56 && parcel_far <= 70)
	{

		nomalprice = Weight(WEIGHT);
		Totalprice = nomalprice + (9 * traintype);
		printf("\n\t\t\tTotal pament for transpoting your parcel= RS.%.2f", Totalprice);
	}
	else if (parcel_far >= 71 && parcel_far <= 85)
	{

		nomalprice = Weight(WEIGHT);
		Totalprice = nomalprice + (12 * traintype);
		printf("\n\t\t\tTotal pament for transpoting your parcel= RS.%.2f", Totalprice);
	}
	else if (parcel_far >= 86 && parcel_far <= 100)
	{

		nomalprice = Weight(WEIGHT);
		Totalprice = nomalprice + (15 * traintype);
		printf("\n\t\t\tTotal pament for transpoting your parcel= RS.%.2f", Totalprice);
	}
	else if (parcel_far >= 101 && parcel_far <= 115)
	{

		nomalprice = Weight(WEIGHT);
		Totalprice = nomalprice + (18 * traintype);
		printf("\n\t\t\tTotal pament for transpoting your parcel= RS.%.2f", Totalprice);
	}
	else if (parcel_far >= 116 && parcel_far <= 130)
	{

		nomalprice = Weight(WEIGHT);
		Totalprice = nomalprice + (21 * traintype);
		printf("\n\t\t\tTotal pament for transpoting your parcel= RS.%.2f", Totalprice);
	}
	else if (parcel_far >= 131 && parcel_far <= 145)
	{

		nomalprice = Weight(WEIGHT);
		Totalprice = nomalprice + (24 * traintype);
		printf("\n\t\t\tTotal pament for transpoting your parcel= RS.%.2f", Totalprice);
	}
	else if (parcel_far >= 146 && parcel_far <= 160)
	{

		nomalprice = Weight(WEIGHT);
		Totalprice = nomalprice + (27 * traintype);
		printf("\n\t\t\tTotal pament for transpoting your parcel= RS.%.2f", Totalprice);
	}
}

float Weight(float x)
{

	float Nomalprice = 50;

	if (x >= 1 && x <= 80)
	{
		Nomalprice = 50;
	}

	else
	{
		Nomalprice = Nomalprice + 30;
	}

	return Nomalprice;
}

// End
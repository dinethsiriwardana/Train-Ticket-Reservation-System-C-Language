#include <stdio.h>
#include<time.h>

//global variables
char userID[50] = "sasa.txt";
char location_name[11][25] = {"Badulla [0]","Bandarawela [1]","Hatton [2]","Peradeniya Junction [3]","Polgahawela Junction [4]","Gampha [5]","Maradana [6]","Colombo Fort [7]","Panadura [8]","Galle [9]","Matara [10]"}; 
int from, to;
float classc_price; 
FILE *booking;


//user defined functions
void passengers();
void locationcal();

int main(){
	
	int booktype; //booking type (parcel or passenger)
	
	do{
		printf("\n\n\t\t\t*** BOOK YOUR TICKET NOW ***\n\n");
		printf("\n\n\t\t\tPassengers [1]\n\t\t\tParcel [2]\n\t\t\tExit [3]\n\n\n");
		printf("\t\t\tEnter choice: ");
		scanf("%d",&booktype);
		
		switch(booktype){
			case 1:
				passengers(); 
				break;
			case 2:
			//	parcel(); 
				break;
			case 3:
				printf("\n\n\t\t\tClosing ...");
				break;
			default:
				printf("\n\n\t\t\tInvalid choice!\n\n");
		}
		
	}while(booktype != 3);
	
	
	return 0;
}


void passengers(){
	
	char bookagain; //to repeat do while 
	int trainID,classa,classb,classc;
	float totalcost,suma,sumb,sumc;
	char confirm;
	
	
	do{
		
		printf("\n\t\t\tUser name : %s",userID);
		
		time_t t;
    	t = time(NULL);
    	struct tm tm = *localtime(&t);
		printf("\n\t\t\tCurrent Date: %d-%d-%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
		
		printf("\n\t\t\tEnter Train ID: ");
		scanf("%d",&trainID);
		void locationcal();
		printf("\n\t\t\tNo Of tickets for First Class : ");
		scanf("%d",&classa);
		suma = (classc_price * 0.5 + classc_price) * classa;
		printf("\n\t\t\tNo Of tickets for Second Class : ");
		scanf("%d",&classb);
		sumb = (classc_price * 0.25 + classc_price) * classb;
		printf("\n\t\t\tNo Of tickets for Third Class : ");
		scanf("%d",&classc);
		sumc = (classc_price) * classc;
		totalcost = suma+sumb+sumc;
		printf("\n\t\t\tConfirm? [Y/N] : ");
		scanf(" %c",&confirm);
		if(confirm == 'y' || confirm == 'Y'){
			FILE *booking = fopen(userID,'a');
			//fprintf(booking,"%d-%d-%d,%.2f,%s,%s,%d,%d,%d",tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900,totalcost,from,to,classa,classb,classc);
			fprintf(booking,"%d,%d,%d\n",4,5,8);
			printf("\n\t\t\tBOOKED SUCCESSFULLY!");
		}else{
			printf("\n\t\t\tCanceled!");
		}
		printf("\n\t\t\tDo you want to Book for another journey? [Y/N]: ");
		scanf(" %c",&bookagain);
		
	}while(bookagain == 'Y' || bookagain == 'y');
	
}

void locationcal(){ //location and calculate cost
	
	int location[] = {0,1,2,3,4,5,6,7,8,9,10};
	int price[] = {300,350,400,450,500,550,600,650,700,750};
	int x, distance;
	
	printf("\n\t\t\t*** List of Location ***\n\n");
	for(x = 0; x<=10; x++){
		printf("\t\t\t\t%s\n",location_name[x]);
	}
	
	printf("\n\t\t\tFrom: "); scanf("%d",&from);
	printf("\n\t\t\tTo: "); scanf("%d",&to);
	
	distance = to - from;
	if(distance < 0){
		distance *= -1;
	}
	
	classc_price = price[distance-1];
	
}
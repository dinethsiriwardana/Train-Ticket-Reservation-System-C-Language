		
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
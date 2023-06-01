#define _CRT_SECURE_NO_WARNINGS
#include "library.h"




void op() {
	// File pointer
	FILE* file;
	//Declaración de variables
	char c;
	char ip[50];
	char route[100];
	char x[15];
	char name[100];

	//We save the path typed by keyboard in the path variable

	printf("Enter path to the file to be read: ");
	scanf("%s", &route);
	printf("\n");

	printf("The content of the file is: ");
	printf("\n\n");



	//open the file in read mode
	file = fopen(route, "r");


	if (file == NULL)
		exit(1);
	else { //We show the content of the file
		while ((c = fgetc(file)) != EOF)
			printf("%c", c);
		printf("\n\n");

	}
	rewind(file);

	while (!feof(file)) { //As long as the lines read do not reach the end of the file, EOF = End Of File continues to loop.

		fscanf(file, "%s", ip); //We mark the pointer inside the file
		do_ping(ip, x); //We use the function to launch the ping

	}
	fclose(file);
	adapters();
	//dns();
	compare();
	delete();


}

void do_ping(char address[], char b[]) {

	printf("\nPings, wait for it...\n");

	char average[25], m[15] = "ms";
	char failure[15] = "ERROR";
	char ping[50] = "ping";
	char route[50] = ">ips.txt";
	int ping1 = 0;

	FILE* f;
	FILE* f2;
	strcat(ping, " ");	//this works add quotes to ping
	strcat(ping, address);	//this function adds the ip address which we want to ping
	strcat(ping, route);		// this adds the address where the file we are going to save the ping to is stored
	system(ping);	//once modified the string ping that initially had only "ping now is "ping+ip+>ips.txt".

	f = fopen("ips.txt", "r"); //Open the file in read mode
	if (f == NULL)
		exit(1);
	else {

		fseek(f, -6, SEEK_END); //Access the end of the file by subtracting 6 spaces.
		fgets(average, 15, f);	//we dump the content of these spaces into the string average

	}
	if (strstr(average, m)) { 	// if media contains the letters ms it will be correct and then
		strcpy(b, average); //its contents are copied into the string b
		printf("\nPing %s responds correctly.\n", address);
		f2 = fopen("dns_ok.txt", "a"); //Open file to write down the good DNS
		fprintf(f2, address);
		fprintf(f2, "\n");

		fclose(f2);

	}
	else { //if the mean does not contain the letters ms then 
		printf("\nPing %s does NOT respond.\n", address);	//prints the error
		strcpy(b, failure);	// in string b, the contents of the failure string is copied 

	}
	fclose(f); //close the file	
}

void adapters() {

	FILE* file;	//assign to be able to open a file
	FILE* file2;
	FILE* file3;
	FILE* file4;

	char adap[100];
	char adap2[15] = "Adapter";
	char line[100];
	char op;
	char config[100];
	char ip[10] = "IPv4";
	char subnet[10] = "subnet";
	char Gateway[50] = "Gateway";
	char dns[20] = "Servers DNS";
	char Netbios[100] = "NetBIOS";
	system("ipconfig/all>configred.txt"); //command to execute and create the file to be analyzed
	system("netsh interface show interface>adapters.txt");
	int aux, aux2;
	aux = 0;
	aux2 = 0;
	file2 = fopen("adapters.txt", "r");
	file3 = fopen("dns_adapters.txt", "a");
	file4 = fopen("adapterAconf.txt", "a");

	do {
		printf("These are your network adapters:\n\n");
		while (aux != EOF) {	//this loop is used to make aux go through the entire file printing each character.
			aux = fgetc(file2);
			printf("%c", aux);
		}
		printf("Enter the network adapter you want to know the configuration for.\n");
		fflush(stdin);
		fgets(adap, 100, stdin); // here we will put the network adapter we want to analyze

		fputs(adap, file4);


		printf("\nThe adapter is: %s\n\n", adap);	// displays the network adapter to be analyzed on the screen

		file = fopen("confignet.txt", "r");	///open file
		rewind(file);
		while (!feof(file)) {	//loop will be executed until the end of the line.
			fgets(line, 100, file);
			empty(line);


			if (strstr(line, adap)) {	// if the network adapter we have set matches the line the if will be executed
				do {

					fgets(line, 100, file); //we dump the contents of the file into the string line
					if (strstr(line, ip)) {	//Compare string linea con string ip, if they mach

						printf("The IP is %s\n", line + 45); //we print the content of the line plus 45 characters so that only what we are interested in is displayed 
					}
					if (strstr(line, subnet)) { //compares with subnet, to display on screen 

						printf("The subnet mask is %s\n", line + 45);
					}
					if (strstr(line, Gateway)) {	//compra con puerta

						printf("The gateway is %s\n", line + 45);
					}
					if (strstr(line, dns)) {	//compare with dns

						printf("The first DNS is %s\n", line + 45);
						file3 = fopen("dns_adapters.txt", "a");
						fprintf(file3, line + 47);
						fclose(file3);
						fgets(line, 100, file);

						if (strstr(line, Netbios)) {	//in the case of netbios we exit
							aux2 = 1;
						}
						else {	//but if there are more than one dns, it is printed out.
							printf("The second dns is : %s\n", line + 39);

							file3 = fopen("dns_adapters.txt", "a");
							fprintf(file3, line + 39);

							fgets(line, 100, file);

							if (strstr(line, Netbios)) { // if the netbios string is present it exits 
								aux2 = 1;
							}
							else {	//otherwise print the third dns
								printf("The third dns is: %s\n", line + 39);
								file3 = fopen("dns_adapters.txt", "a");
								fprintf(file3, line + 39);

							}
						}

					}
					if (strstr(line, adap2)) { //if another adapter comes out, it also comes out
						aux2 = 1;
					}
				} while (line != adap2 && aux2 == 0); //will be executed whenever line is not equal adapter, and only the first time.
			}
		}


		printf("You want to re-enter another network adapter yes(Y)||not(N):\n ");
		op = 'n';
		scanf("%c", &op);
		printf("\n");
		if (op == 'y' || op == 'Y') {
			printf("These are your network adapters:\n\n");
			while (aux != EOF) {	//this loop is used to make aux go through the entire file printing each character.
				aux = fgetc(file2);
				printf("%c", aux);
			}
		}

	} while (op == 'Y' || op == 'y'); //this last loop is for if you make a mistake setting the network adapter or you want to check another one you can do it in a quick way.
	fclose(file3);
	fclose(file2);	//close the files to be able to delete them later.
	fclose(file);	
	fclose(file4);

}

void empty(char b[]) {	//this function removes the : from the adapters so that the user does not have to enter to select the adapter.
	int i, aux;
	aux = 0;
	for (i = 0; i < 100 && aux == 0; i++) {	  //Loop through the entire string up to a maximum of 100
		if (b[i] == ':' && aux == 0) {		//The loop in case the string at position i contains a ':' is changed to a line break.
			b[i] = '\n';
			aux = 1;	//we use this variable to exit the loop in case we encounter a ':' and make the loop more efficient.
		}
	}
}
void delete() {	//Delete temporary files that are not requested in the activity.

	remove("dns_adapters.txt");
	remove("confignet.txt");
	remove("adapters.txt");
	remove("ips.txt");
	remove("adapterAconf.txt");
}



void vation(char b[]) {	//function that changes the /n to /0
	int i, aux;
	aux = 0;
	for (i = 0; i < 100 && aux == 0; i++) {	  //Loop through the entire string up to a maximum of 100
		if (b[i] == '\n' && aux == 0) {		//The loop in case the string at position i contains a ':' is changed to a line break.
			b[i] = '\0';
			aux = 1;	//we use this variable to exit the loop in case we encounter a ':' and make the loop more efficient.
		}
	}
}

void compare() {

	FILE* f1;
	FILE* f2;

	f1 = fopen("dns_adapters.txt", "r");
	f2 = fopen("dns_ok.txt", "r");
	int aux, p1, p2;

	char a[20];
	char b[20];
	aux = 0;
	char dns1[15];
	char dns2[15];


	printf("The program will compare the DNS speed:\n");

	if (f1 == NULL) {	//if the file cannot be opened it will exit the program because of an error
		printf("File could not be opened.\n");
		exit(1);	//Will exit
	}


	while (aux != EOF) {	//this loop is used to make aux go through the entire file printing each character.
		aux = fgetc(f1);
		//printf("%c",aux);
	}
	aux = 0;	//set the variable to 0 to make a loop to add the content to another variable

	while (aux != EOF) {	//this loop is used to make aux go through the entire file printing each character.
		aux = fgetc(f2);
		//printf("%c",aux);
	}

	rewind(f1);	//back to the beginning of the program

	while (!feof(f1)) {
		fgets(dns1, 15, f1);

	}
	fclose(f1);

	rewind(f2);
	//printf("the value of dns1;%s\n",dns1);

	while (!feof(f2)) {
		fgets(dns2, 15, f2);

	}
	fclose(f2);

	//printf("This is the value of dns2:%s\n",dns2);
	vation(dns1);	//we remove the line break for an end of line to be able to use the dns to be able to use it in the functions
	vation(dns2);	
	//printf("the value of dns1;%s\n",dns1);
	do_ping(dns1, a);
	do_ping(dns2, b);

	//printf("the value of a is ; %s\n",a);
	//printf("the value of b is ; %s\n",b);

	p1 = atoi(a);	// pass the string to the variable p1 in integer form
	p2 = atoi(b);	

	//printf("the value of p1 is %i\n",p1);
	//printf("the value of p2 is %i\n",p2);

	printf("\nThe result is that %s has a ping of %i and the dns %s has a ping of %i\n\n", dns1, p1, dns2, p2);

	if (p1 < p2) {
		printf("Your current configuration is the fastest.\n\n");
	}
	else {
		printf("The DNS file is faster than your current one..\n\n");
		netsh(dns2);
	}
	printf("Compare it's end.\n");
}

void netsh(char b[]) {

	FILE* f;
	f = fopen("adapterAconf.txt", "r");
	char asigdns[100] = "netsh interface ip set dns name=";
	char statico[30] = " static ";
	char reniniciar[100] = "Netsh Interface Ip Set Dns name=";
	char sour[15] = "source=dhcp";
	char comi[5] = "\""; 
	char addr[10] = " address=";

	char aux[20];
	while (!feof(f)) {
		fgets(aux, 20, f);
	}
	vation(aux);
	//printf("%s",aux);
	fclose(f);	//close the file

	strcat(reniniciar, " ");
	strcat(reniniciar, comi);  
	strcat(reniniciar, aux);	
	strcat(reniniciar, comi);  
	strcat(reniniciar, sour);	
	printf("%s\n", reniniciar);

	strcat(asigdns, comi);	
	strcat(asigdns, aux);	
	strcat(asigdns, comi);   
	strcat(asigdns, statico);  
	strcat(asigdns, b);	 

	printf("%s\n", asigdns);
	
	system(asigdns);	




}
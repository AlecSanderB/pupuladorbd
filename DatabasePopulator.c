#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int generateRandomInt(int min, int max){
        return rand() % (max - min + 1) + min; 
}

int generateRandomId(int size){
	char idChar[size];
	int i;
	for(i = 0; i < size; i++){
		idChar[i] = generateRandomInt(1,9) + 48;
	}
	idChar[size] = '\0';
	return atoi(idChar);
}

char generateRandomChar(){
	return generateRandomInt(65, 90);
}

char* generateRandomDate(){
	char* date = malloc(11 * sizeof(char));
	int i;
	int diaTemp = generateRandomInt(1, 28);
	char dia[3];
	if(diaTemp < 10){
		sprintf(dia, "0%d", diaTemp);
	} else{
		sprintf(dia, "%d", diaTemp);
	}
	
	int mesTemp = generateRandomInt(1, 12);
	char mes[3];
	if(mesTemp < 10){
		sprintf(mes, "0%d", mesTemp);
	} else{
		sprintf(mes, "%d", mesTemp);
	}
	
	sprintf(date, "%d-%s-%s", generateRandomInt(2022, 2024), mes , dia);
	return date;
}

char* generateRandomLicense(){
	char* license = malloc(9 * sizeof(char));
	int i;
	for(i = 0; i < 8; i++){
		if(i < 2){
			license[i] = generateRandomChar();
		} else{
			license[i] = generateRandomInt(0,9) + 48;
		}
	}
	license[8] = '\0';
	return license;
}

char* generateRandomCPF(){
	char *CPF = malloc(15*sizeof(char));
	int i;
	for(i = 0; i < 14; i++){
		if(i != 3 && i != 7 && i != 11){
			CPF[i] = generateRandomInt(0, 9) + 48;
		} else if(i == 11){
			CPF[i] = '-';
		} else{
			CPF[i] = '.';
		}
		CPF[14] = '\0';
	} 
	return CPF;
}

char* generateRandomLicensePlate(){
	char* licensePlate = malloc(7*sizeof(char));
	int i;
	for(i = 0; i < 7; i++){
		if(i < 3){
			licensePlate[i] = generateRandomChar();
		} else{
			licensePlate[i] = generateRandomInt(0, 9) + 48;
		}
	}
	licensePlate[7] = '\0';
	return licensePlate;
}

char* generateRandomName(char * filename){
	FILE* namesList = fopen(filename, "r");
	if(namesList == NULL){
		return NULL;
	}
	int i = 0;
	
	char* name = malloc(100* sizeof(char));
	fseek(namesList, 0, SEEK_END);
	long fileSize = ftell(namesList);
	fseek(namesList, generateRandomInt(20, fileSize), SEEK_SET);
	fseek(namesList,  -20, SEEK_CUR);
	name = fgets(name, 20, namesList);
	name = fgets(name, 20, namesList);
	fclose(namesList);
	name[strlen(name) - 1] = name[strlen(name)];

	return name;
}

void generateCliente(int quantidade){
	int i;
	FILE* fileCliente = fopen("cliente.txt", "w");
	FILE* auxCliente = fopen("auxcliente.txt", "w");
	for(i = 0; i < quantidade; i++){
		int randomId = generateRandomId(9);
		char* randomName = generateRandomName("names.txt");
		if(randomName == NULL){
			printf("ERRO! Arquivo nao encontrado");
			exit(0);
		}
		char* randomCPF = generateRandomCPF();
		fprintf(fileCliente, "INSERT INTO Cliente VALUES ('%d', '%s', '%s');\n", randomId, randomName, randomCPF);
		fprintf(auxCliente, "%d\n", randomId);
		free(randomName);
		free(randomCPF);
	}
	fclose(fileCliente);
	fclose(auxCliente);
}

void generateTaxi(int quantidade){
	int i;
	FILE* fileTaxi = fopen("taxi.txt", "w");
	FILE* auxTaxi = fopen("auxtaxi.txt", "w");
	for(i = 0; i < quantidade; i++){
		int randomAnoFab = generateRandomInt(1998, 2024);
		char* randomLicensePlate = generateRandomLicensePlate();
		char* randomLicense = generateRandomLicense();
		char* randomBrand1 = generateRandomName("carbrands.txt");
		char* randomBrand2 = generateRandomName("carbrands.txt");
		if(randomBrand1 == NULL || randomBrand2 == NULL){
			printf("ERRO! Arquivo nao encontrado");
			exit(0);
		}
		fprintf(fileTaxi, "INSERT INTO Taxi VALUES ('%s', '%s', '%s', '%d', '%s');\n", randomLicensePlate, randomBrand1, randomBrand2, randomAnoFab, randomLicense);
		fprintf(auxTaxi, "%s\n", randomLicensePlate);
		free(randomLicensePlate);
		free(randomLicense);
		free(randomBrand1);
		free(randomBrand2);
	}
	fclose(fileTaxi);
	fclose(auxTaxi);
}

void generateCorrida(int quantidade){
	int i;
	FILE * fileCorrida = fopen("corrida.txt", "w");
	for(i = 0; i < quantidade; i++){
		char* randomDate = generateRandomDate();
		char* randomCliente = generateRandomName("auxCliente.txt");
		char* randomTaxi = generateRandomName("auxTaxi.txt");
		fprintf(fileCorrida, "INSERT INTO Corrida VALUES ('%s', '%s', '%s');\n", randomCliente, randomTaxi, randomDate);
		free(randomCliente);
		free(randomTaxi);
		free(randomDate);
	}
	fclose(fileCorrida);
}

int main(){
	generateCliente(10000);
	generateTaxi(10000);
	generateCorrida(1000);
	return 0;
}

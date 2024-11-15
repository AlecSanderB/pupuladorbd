#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int generateRandomSmallInt(int min, int max){
	if(min > max){
		printf("Erro! Valor minimo maior que valor maximo (SmallInt)");
		return 0;
	}
        return rand() % (max - min + 1) + min; 
}

int generateRandomLargeInt(int minValue, int maxValue){
	if(minValue > maxValue){
		printf("Erro! Valor minimo maior que valor maximo (LargeInt)");
		return 0;
	}
	char tempSize[20];
	sprintf(tempSize, "%d", maxValue);
	int maxSize = strlen(tempSize);
	char largeInt[20];
	do{
		int size = generateRandomSmallInt(1, maxSize);
		int i;
		for(i = 0; i < size; i++){
		largeInt[i] = generateRandomSmallInt(1,9) + 48;
		}
		largeInt[size] = '\0';
	} while(atoi(largeInt) > maxValue || atoi(largeInt) < minValue);
	
	return atoi(largeInt);
}

int generateRandomId(int size){
	char idChar[size];
	int i;
	for(i = 0; i < size; i++){
		idChar[i] = generateRandomSmallInt(1,9) + 48;
	}
	idChar[size] = '\0';
	return atoi(idChar);
}

char generateRandomChar(){
	return generateRandomSmallInt(65, 90);
}

char* generateRandomDate(int min, int max){
	char* date = malloc(11 * sizeof(char));
	int i;
	int diaTemp = generateRandomSmallInt(1, 28);
	char dia[3];
	if(diaTemp < 10){
		sprintf(dia, "0%d", diaTemp);
	} else{
		sprintf(dia, "%d", diaTemp);
	}
	
	int mesTemp = generateRandomSmallInt(1, 12);
	char mes[3];
	if(mesTemp < 10){
		sprintf(mes, "0%d", mesTemp);
	} else{
		sprintf(mes, "%d", mesTemp);
	}
	
	sprintf(date, "%d-%s-%s", generateRandomSmallInt(min, max), mes , dia);
	return date;
}

char* generateRandomTime(){
	char* time = malloc(11 * sizeof(9));
	int i;
	int horaTemp = generateRandomSmallInt(0, 23);
	char hora[3];
	if(horaTemp < 10){
		sprintf(hora, "0%d", horaTemp);
	} else{
		sprintf(hora, "%d", horaTemp);
	}
	int minutoTemp = generateRandomSmallInt(0, 59);
	char minuto[3];
	if(minutoTemp < 10){
		sprintf(minuto, "0%d", minutoTemp);
	} else{
		sprintf(minuto, "%d", minutoTemp);
	}
	int segundoTemp = generateRandomSmallInt(0, 59);
	char segundo[3];
	if(segundoTemp < 10){
		sprintf(segundo, "0%d", segundoTemp);
	} else{
		sprintf(segundo, "%d", segundoTemp);
	}
	sprintf(time, "%s:%s:%s", hora, minuto , segundo);
	return time;
}

char* generateRandomLicense(){
	char* license = malloc(9 * sizeof(char));
	int i;
	for(i = 0; i < 8; i++){
		if(i < 2){
			license[i] = generateRandomChar();
		} else{
			license[i] = generateRandomSmallInt(0,9) + 48;
		}
	}
	license[8] = '\0';
	return license;
}

char* generateRandomCNPJ(){
	char* CNPJ = malloc(15*sizeof(char));
	int i;
	for(i = 0; i < 14; i++){
		if(i == 6){
			CNPJ[i] = '-';	 
		}else if(i >= 7 && i <=9){
		 	CNPJ[i] = '0'; 
		} else if(i == 11){
			CNPJ[i] = '/';
		} else if(i == 12){
			CNPJ[i] = '0';
		} else{
			CNPJ[i] = generateRandomSmallInt(0, 9) + 48;
		}
	}
	CNPJ[14] = '\0';
	return CNPJ;
}

char* generateRandomCPF(){
	char* CPF = malloc(15*sizeof(char));
	int i;
	for(i = 0; i < 14; i++){
		if(i != 3 && i != 7 && i != 11){
			CPF[i] = generateRandomSmallInt(0, 9) + 48;
		} else if(i == 11){
			CPF[i] = '-';
		} else{
			CPF[i] = '.';
		}
	} 
	CPF[14] = '\0';
	return CPF;
}

char* generateRandomLicensePlate(){
	char* licensePlate = malloc(7*sizeof(char));
	int i;
	for(i = 0; i < 7; i++){
		if(i < 3){
			licensePlate[i] = generateRandomChar();
		} else{
			licensePlate[i] = generateRandomSmallInt(0, 9) + 48;
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
	int randomBias = generateRandomLargeInt(100, fileSize);
	fseek(namesList, generateRandomLargeInt(randomBias, fileSize), SEEK_SET);
	fseek(namesList,  -20, SEEK_CUR);
	name = fgets(name, 20, namesList);
	name = fgets(name, 20, namesList);
	fclose(namesList);
	name[strlen(name) - 1] = name[strlen(name)];
	return name;
}

void generateCliente(int quantidade){
	int i;
	FILE* fileCliente = fopen("cliente.sql", "w");
	FILE* auxCliente = fopen("auxCliente.txt", "w");
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
	FILE* fileTaxi = fopen("taxi.sql", "w");
	FILE* auxTaxi = fopen("auxTaxi.txt", "w");
	for(i = 0; i < quantidade; i++){
		int randomAnoFab = generateRandomSmallInt(1998, 2024);
		char* randomLicensePlate = generateRandomLicensePlate();
		char* randomLicense = generateRandomLicense();
		char* randomBrand1 = generateRandomName("carbrands.txt");
		char* randomBrand2 = generateRandomName("carbrands.txt");
		if(randomBrand1 == NULL || randomBrand2 == NULL){
			printf("ERRO! Arquivo nao encontrado (marca de carro)");
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
	FILE * fileCorrida = fopen("corrida.sql", "w");
	for(i = 0; i < quantidade; i++){
		char* randomDate = generateRandomDate(2022,2024);
		char* randomCliente = generateRandomName("auxCliente.txt");
		char* randomTaxi = generateRandomName("auxTaxi.txt");
		fprintf(fileCorrida, "INSERT INTO Corrida VALUES ('%s', '%s', '%s');\n", randomCliente, randomTaxi, randomDate);
		free(randomCliente);
		free(randomTaxi);
		free(randomDate);
	}
	fclose(fileCorrida);
}

void generateMotorista(int quantidade){
	int i;
	FILE * fileMotorista = fopen("motorista.sql", "w");
	FILE * auxMotorista = fopen("auxMotorista.txt", "w");
	for(i = 0; i < quantidade; i++){
		char* randomName = generateRandomName("names.txt");
		char* randomTaxi = generateRandomName("auxTaxi.txt");
		int randomId = generateRandomId(9);
		fprintf(fileMotorista, "INSERT INTO Motorista VALUES ('%d', '%s', '1', '%s');\n", randomId , randomName, randomTaxi);
		fprintf(auxMotorista, "%d\n", randomId);
		free(randomName);
		free(randomTaxi);
	}
	fclose(fileMotorista);
	fclose(auxMotorista);
}

void generateZona(int quantidade){
	int i;
	FILE * fileZona = fopen("zona.sql", "w");
	FILE * auxZona = fopen("auxZona.txt", "w");
	for(i = 0; i < quantidade; i++){
		char* randomZona = generateRandomName("names.txt");
		fprintf(fileZona, "INSERT INTO Zona VALUES ('%s');\n", randomZona);
		fprintf(auxZona, "%s\n", randomZona);
		free(randomZona);
	}
	fclose(fileZona);
	fclose(auxZona);
}

void generateFila(int quantidade){
	int i;
	FILE * fileFila = fopen("fila.sql", "w");
	for(i = 0; i < quantidade; i++){
		char* randomZona = generateRandomName("auxZona.txt");
		char* randomMotorista = generateRandomName("auxMotorista.txt");
		char* randomDate = generateRandomDate(2019,2024);
		char* randomTime = generateRandomTime();
		fprintf(fileFila, "INSERT INTO Fila VALUES ('%s', '%s', '%s %s', '%s %s', '%d');\n",
		 randomZona, randomMotorista, randomDate, randomTime, randomDate, randomTime, generateRandomId(4));
		free(randomZona);
	}
	fclose(fileFila);
}

void generateClienteEmpresa(int quantidade){
	int i;
	FILE * fileClienteEmpresa = fopen("clienteEmpresa.sql", "w");
	for(i = 0; i < quantidade; i++){
		char* randomCliente = generateRandomName("auxCliente.txt");
		char* randomEmpresa = generateRandomName("empresas.txt");
		char* randomCNPJ = generateRandomCNPJ();
		fprintf(fileClienteEmpresa, "INSERT INTO ClienteEmpresa VALUES ('%s', '%s', '%s');\n", randomCliente, randomEmpresa, randomCNPJ);
		free(randomCliente);
		free(randomEmpresa);
		free(randomCNPJ);
	}
	fclose(fileClienteEmpresa);
}

void combinarTodos(){
	// Odeio tudo isso, mas vai ficar assim
	char tempChar[200];
	char testChar[200];
	void * test;
	FILE * fileCombinacao = fopen("combinacao.sql", "w");
	
	FILE * fileCliente = fopen("cliente.sql", "r");
	do{
		strcpy(testChar, tempChar);
		test = fgets(tempChar, 200, fileCliente);
		if(strcmp(testChar, tempChar) == 0){
			break;
		}
		fprintf(fileCombinacao, "%s", tempChar);
	} while(test != NULL);
	
	FILE * fileTaxi = fopen("taxi.sql", "r");
	do{
		strcpy(testChar, tempChar);
		test = fgets(tempChar, 200, fileTaxi);
		if(strcmp(testChar, tempChar) == 0){
			break;
		}
		fprintf(fileCombinacao, "%s", tempChar);
	} while(test != NULL);
	fprintf(fileCombinacao, "\n");
	
	FILE * fileCorrida = fopen("corrida.sql", "r");
	do{
		strcpy(testChar, tempChar);
		test = fgets(tempChar, 200, fileCorrida);
		if(strcmp(testChar, tempChar) == 0){
			break;
		}
		fprintf(fileCombinacao, "%s", tempChar);
	} while(test != NULL);
	fprintf(fileCombinacao, "\n");
	
	FILE * fileMotorista = fopen("motorista.sql", "r");	
	do{
		strcpy(testChar, tempChar);
		test = fgets(tempChar, 200, fileMotorista);
		if(strcmp(testChar, tempChar) == 0){
			break;
		}
		fprintf(fileCombinacao, "%s", tempChar);
	} while(test != NULL);
	fprintf(fileCombinacao, "\n");
	
	FILE * fileZona = fopen("zona.sql", "r");	
	do{
		strcpy(testChar, tempChar);
		test = fgets(tempChar, 200, fileZona);
		if(strcmp(testChar, tempChar) == 0){
			break;
		}
		fprintf(fileCombinacao, "%s", tempChar);
	} while(test != NULL);
	fprintf(fileCombinacao, "\n");
	
	FILE * fileFila = fopen("fila.sql", "r");
	do{
		strcpy(testChar, tempChar);
		test = fgets(tempChar, 200, fileFila);
		if(strcmp(testChar, tempChar) == 0){
			break;
		}
		fprintf(fileCombinacao, "%s", tempChar);
	} while(test != NULL);
	fprintf(fileCombinacao, "\n");
	
	FILE * fileClienteEmpresa = fopen("clienteEmpresa.sql", "r");
	do{
		strcpy(testChar, tempChar);
		test = fgets(tempChar, 200, fileClienteEmpresa);
		if(strcmp(testChar, tempChar) == 0){
			break;
		}
		fprintf(fileCombinacao, "%s", tempChar);
	} while(test != NULL);
}

int main(){
	int i;
	generateCliente(10000);
	generateTaxi(1500);
	generateCorrida(10000);
	generateMotorista(1000);
	generateZona(100);
	generateFila(100);
	generateClienteEmpresa(100);
	combinarTodos();
	return 0;
}

#include <stdio.h>
#include <stdlib.h>

int** aloc_matrix (int m, int n){
	int **matrix;
	matrix = (int**) calloc(m, sizeof(int*));
	if (matrix == NULL) { printf("Not enough memory.\n"); exit(1); }

	for (int i=0; i<m; i++){
		matrix[i] = (int*) calloc(n, sizeof(int));
		if (matrix[i] == NULL) { printf("Not enough memory.\n"); exit(1); }
	}
	return matrix;
}

typedef struct{
	int x;
	int y;
}pairs;

int teste_reflexiva (int** matrix, int quantidade, pairs* ausentes_reflexiva){

	int contador = 0;

	for(int i=0; i < quantidade; i++){
		for (int j=0;  j < quantidade; j++){
			if (i == j){
				if (matrix[i][j] == 0){
					ausentes_reflexiva[contador].x = i;
					ausentes_reflexiva[contador].y = j;
					contador++;
				}
			}
		}
	}
	return contador;
}

int teste_irreflexiva (int** matrix, int quantidade, pairs* presentes_ireflexiva){

	int contador = 0;

	for(int i=0; i < quantidade; i++){
		for (int j=0;  j < quantidade; j++){
			if (i == j){
				if (matrix[i][j] == 1){
					presentes_ireflexiva[contador].x = i;
					presentes_ireflexiva[contador].y = j;
					contador++;
				}
			}
		}
	}
	return contador;
}

int teste_simetrica (int** matrix, int quantidade, pairs* ausentes_simetrica){

	int contador = 0;
	printf("teste_simetrica");
	for(int i=0; i < quantidade; i++){
		for (int j=0;  j < quantidade; j++){
				if (matrix[i][j] != matrix[j][i]){
					if(matrix[i][j]==0){
						ausentes_simetrica[contador].x =i;
						ausentes_simetrica[contador].y = j;
						contador++;
					}
				}
		}
	}
	printf("contador");
	return contador;
}

int teste_anti_simetrica (int** matrix, int quantidade, pairs* presentes_anti_reflexiva){

	int contador = 0;

	for(int i=0; i < quantidade; i++){
		for (int j=0;  j < quantidade; j++){
				if (i == j){
				continue;
				}
				else if (matrix[i][j] == matrix[j][i]){
					if(matrix[i][j] == 1){
						presentes_anti_reflexiva[contador].x = i;
						presentes_anti_reflexiva[contador].y = j;
						contador++;
					}
				}
		}
	}
	return contador;
}

int main (int argc, char* argv[]){

    if (argc != 2){
		printf("ERROR: is required to run \"program.c FILE\"\n");
		exit (1);
	}

    FILE* file;
	file = fopen (argv[1], "r");
	if (file == NULL){
 		printf("File error.\n"); 
 		exit(1);
	};

	char character=0; // contar os '\n'
    int number_of_lines = 0; 

    while(character != EOF){
    	character = fgetc(file);
    	if (character == '\n'){
            number_of_lines++;
         }
	} // contar os '\n'

	fseek(file, 0L, SEEK_SET);

    int quantidade = 0; 
	fscanf (file, "%d", &quantidade);  
	// lendo o primeiro numero indicador
	printf ("%d ",quantidade);  

	int *numbers;
	numbers = (int*) malloc(quantidade * sizeof(int*));

	for (int i=0; i < quantidade; i++){
		fscanf (file, "%d", &numbers[i]);
		printf ("%d ", numbers[i]); 
	} //lendo os números

	pairs pair[(number_of_lines)];

	int i = 0;
	while (!feof(file)){
		fscanf (file, "%d %d", &pair[i].x, &pair[i].y);
		//printf ("%d %d\n", pair[i].x, pair[i].y);
		i++;  	
	} // lendo os pares ordenados

    int **matrix;
    matrix = aloc_matrix (quantidade,quantidade);

	int numero_inicial = numbers[0	];
	for (int j=0; j < number_of_lines; j++){
		matrix [(pair[j].x-numero_inicial)] [(pair[j].y-numero_inicial)] = 1;
	}// preenchendo a matriz de adjacencia

	//para printar a matriz testando
	printf("\n");
	for (int j=0; j < quantidade; j++){
		for (int k=0; k < quantidade; k++){
			printf(" %d ", matrix [j][k]);
		}
		printf ("\n");
	}

	printf("Propriedades\n");


	pairs *ausentes_reflexiva;
	ausentes_reflexiva = (pairs*) calloc(quantidade, sizeof(int*));
	int cont_reflexiva = teste_reflexiva (matrix, quantidade, ausentes_reflexiva);

	if (cont_reflexiva == 0){
		printf ("1. Reflexiva: V\n");
	}
	else{
		printf ("1. Reflexiva: F\n   ");
		i = 0;
		while (cont_reflexiva != 0){
			printf ("(%d %d); ",ausentes_reflexiva[i].x + numero_inicial, ausentes_reflexiva[i].y + numero_inicial);
			cont_reflexiva--;
			i++;
		}
		printf("\n");
	} // Reflexiva
	free(ausentes_reflexiva);


	pairs *presentes_irreflexiva;
	presentes_irreflexiva = (pairs*) calloc(quantidade, sizeof(int*));
	int cont_irreflexiva = teste_irreflexiva (matrix, quantidade, presentes_irreflexiva);

	if (cont_irreflexiva == 0){
		printf ("2. Irreflexiva: V\n");
	}
	else{
		printf ("2. Irreflexiva: F\n   ");
		i = 0;
		while (cont_irreflexiva != 0){
			printf ("\ncont_irreflexiva: %d\n", cont_irreflexiva);
			printf ("(%d %d); ",presentes_irreflexiva[i].x + numero_inicial, presentes_irreflexiva[i].y + numero_inicial);
			cont_irreflexiva --;
			i++;
		}
		printf("\n");
	} // Irreflexiva


	printf("teste");
	pairs *ausentes_simetrica;
	ausentes_simetrica = (pairs*) calloc(quantidade, sizeof(int*));
	int cont_simetrica = teste_simetrica (matrix, quantidade, ausentes_simetrica);
	
	printf ("cont_simetrica: %d",cont_simetrica);
 	if (cont_simetrica == 0){
		printf ("2. Simetrica: V\n");
	}
	else{
		printf ("2. Simetrica: F\n   ");
		i = 0;
		while (cont_simetrica != 0){
			printf ("(%d %d); ",ausentes_simetrica[i].x + numero_inicial, ausentes_simetrica[i].y + numero_inicial);
			cont_simetrica --;
			i++;
		}
		printf("\n");
	} // Simetrica

/* 

	pairs *presentes_anti_simetrica = (pairs*) calloc(quantidade, sizeof(int*));
	int cont_anti_simetrica = teste_anti_simetrica (matrix, quantidade, presentes_anti_simetrica);

 	if (presentes_anti_simetrica[quantidade+1].x == 0){
		printf ("2. Anti-simetrica: V\n");
	}
	else{
		printf ("2. Anti-simetrica: F\n   ");
		i = 0;
		while (presentes_anti_simetrica[quantidade+1].x != 0){
			printf ("(%d %d); ",presentes_anti_simetrica[i].x + numero_inicial, presentes_anti_simetrica[i].y + numero_inicial);
			presentes_anti_simetrica[quantidade+1].x --;
			i++;
		}
		printf("\n");
	} // Anti_simetrica
 */





    return 0;
}


/*
	pairs *assimetrica = teste_assimetrica (matrix, quantidade); // ser irreflexiva e anti_simetrica
	pairs *transitiva = teste_transitiva (matrix, quantidade);	
*/
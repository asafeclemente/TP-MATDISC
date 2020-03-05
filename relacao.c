#include <stdio.h>
#include <stdlib.h>

int** aloc_matrix (int m, int n)
{
	int **matrix;
	matrix = (int**) malloc(m * sizeof(int*));
	if (matrix == NULL) { printf("Not enough memory.\n"); exit(1); }

	for (int i=0; i<m; i++){
		matrix[i] = (int*) malloc(n * sizeof(int));
		if (matrix[i] == NULL) { printf("Not enough memory.\n"); exit(1); }
	}
	return matrix;
}

int main (int argc, char* argv[])
{
    if (argc != 2){
		printf("ERROR: is required to run \"program.c file\"\n");
		exit (1);
	}

    FILE* file;
	file = fopen (argv[1], "r");
	if (file == NULL){
 		printf("File error.\n"); 
 		exit(1);
	};

    int number_of_lines = 0; 

    char character = 0;
    while(character != EOF){
    	character = fgetc(file);
    	if (character == '\n'){ //calculates how many '/n' there are, ie how many lines
            number_of_lines++;
         }
    }
    fseek(file, 0L, SEEK_SET); 

    printf ("number_of_lines: %i\n", number_of_lines);

/*
    int line = 0;
    character = 0;

    character = fgetc(file);

    while(character != EOF){
		character = fgetc(file);
		if (character != '\n' && character != EOF){
			pares[line]++;
		}
		if (character == '\n'){
			pares[line]++;
			line++;
		} 
	}
*/
    char num[10] = "131231v3";
    int valor = atoi(num);

    printf("valor: %d\n", valor);





    int **matrix;
    matrix = aloc_matrix (6,7);

    system ("pause");
    return 0;
}

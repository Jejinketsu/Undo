#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int tempo;
    char type;
    int undo;
}Entrada;

Entrada comandos[100];

//void recarregar(Comando *comandos, const char *filePath );
void checkPath(FILE *file);

char linhas[60];
//char letras[60];

int main (int argc, const char *argv[]){
    
    int cont = 0;
    
    FILE *file;
    file = fopen("entrada.txt", "r"); //leitura do arquivo de entrada

    checkPath(file);//checagem se o arquivo é NULL
    
    int cont_type = 0; //contador de caracteres
    int cont_undo = 0;	//contador de undos
    char numero;
    while(!feof(file)){ //percorre todo o arquivo
    	
    	int i = 0;
    	
        fgets(linhas,60,file);  //O vetor linhas recebe o conteudo dos arquivo
        
        while(linhas[i]!='}'){
        	
        	if(linhas[i+1] == 't'){ 				//se o primeiro caractere for igual a t, 
        		comandos[cont_type].type = linhas[i+6];	//a struct comandos.tipo recebe o que estiver no vetor linhas 6 casas depois
        		i+=7;
        		cont_type++;	
			}
		}
    }
    for(int i = 0; i<cont_type; i++)
    	printf("%c",comandos[4].type);

    fclose(file);
    
    //recarregar(comandos, argv[1]);

    return 0;
}

/*void recarregar(Comando *comandos, const char * filePath){
    int i =0;
    FILE *file;
    file = fopen(filePath, "r");
    
    char linhas[30][60];

    checkPath(file);

    while(!feof(file)){
        fgets(linhas[i],60,file);
        printf("%s\n",linhas[i]);
        i++;
    }

    fclose(file);
}*/

void checkPath(FILE *file){
    if(file == NULL){
        printf("Erro na abertura de arquivo!\n");
        exit(1);        
    }
}

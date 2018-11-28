#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int tempo;
    char type;
    int undo;
}Entrada;

void recarregar(const char *filePath );
void checkPath(FILE *file);
int slice(const char * str, char * buffer, size_t start, size_t end);

Entrada comandos[1000];
char linhas[60000];

int main (int argc, const char *argv[]){
    
    recarregar(argv[1]);
    printf("Comando |   T |   U |   Time\n");
    for(int i = 0; i < 100;i++){
        printf("Comando | %3c | %3d | %3d\n", comandos[i].type, comandos[i].undo, comandos[i].tempo);
    }

    return 0;
}

void recarregar(const char * filePath){
    FILE *file;
    file = fopen(filePath, "r");//leitura do arquivo de entrada

    int cont_type = 0; //contador de posições do vetor de comandos
    int cont_tempo = 0; //pegador de tempos
    char numero;

    checkPath(file);

    while(!feof(file)){ //percorre todo o arquivo
    	
    	int i = 0, testeVirgula;
    	
        fgets(linhas,5000,file);  //O vetor linhas recebe o conteudo dos arquivo
        
        while(linhas[i]!='}'){
        	
        	if(linhas[i+1] == 't'){ 				//se o primeiro caractere for igual a t, 
        		comandos[cont_type].type = linhas[i+6];	//a struct comandos.tipo recebe o que estiver no vetor linhas 6 casas depois
        		i+=7; cont_type++;	
			}
            else if(linhas[i+1] == 'u'){ 				//se o primeiro caractere for igual a t, 
                char segundo[256];
                i++; testeVirgula = 6;
                while(linhas[i]!='}' || linhas[i]!=','){
                    if(linhas[i+testeVirgula] == ',' || linhas[i+testeVirgula] == '}'){
                        comandos[cont_type].undo =  slice(linhas,segundo,i+5,i+testeVirgula-1);
                        cont_type++;
                        i+=testeVirgula; testeVirgula = 6;
                    } else {
                        testeVirgula++;
                    }
                    if(linhas[i]=='}') break;
                }
                //cont_type++;
			}
        }
        i +=2; //Posicionando cursor para coletar os tempos.  
        testeVirgula = 2;
        while(linhas[i]!='}'){
            char segundo[256];
            if(linhas[i+testeVirgula] == ',' || linhas[i+testeVirgula] == '}'){
                comandos[cont_tempo].tempo =  slice(linhas,segundo,i+1,i+testeVirgula-1);
                i+=testeVirgula; cont_tempo++; testeVirgula = 2;
            } else {
                testeVirgula++;
            }
        }
    }

    fclose(file);
}

void checkPath(FILE *file){
    if(file == NULL){
        printf("Erro na abertura de arquivo!\n");
        exit(1);        
    }
}

int slice(const char * str, char * buffer, size_t start, size_t end) {
    size_t j = 0;
    for ( size_t i = start; i <= end; ++i ) {
        buffer[j++] = str[i];
    }
    buffer[j] = 0;
    return atoi(buffer);
}

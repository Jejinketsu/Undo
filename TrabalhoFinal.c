#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Variáveis de Desempenho

typedef struct {
    int tempo;
    char type;
    int undo;
}Entrada;

void recarregar(const char *filePath, FILE *fileOut);
void escrever(int inicio, int fim, FILE *fileOut);
void checkPath(FILE *file);
int slice(const char * str, char * buffer, size_t start, size_t end);

Entrada comandos[1000];
char linhas[60000];

int main (int argc, const char *argv[]){

    FILE *fileOut;
    fileOut = fopen(argv[2], "w");

    recarregar(argv[1], fileOut);
    
    fclose(fileOut);

    return 0;
}

void recarregar(const char * filePath, FILE * fileOut){
    FILE *file;
    file = fopen(filePath, "r"); //leitura do arquivo de entrada

    int cont_mark = 0; //marca a posição onde o cont_type deixou o cursor depois de ler uma linha
    int cont_type = 0; //contador de posições do vetor de comandos
    int cont_tempo = 0;//marcador de tempos

    checkPath(file);

    while(!feof(file)){
    	cont_mark = cont_type;
    	int i = 0, testeVirgula;
    	
        fgets(linhas,5000,file);                        //O vetor linhas recebe o conteudo dos arquivo
        while(linhas[i]!='}'){

        	if(linhas[i+1] == 't'){ 				    //se o primeiro caractere for igual a t, 
        		comandos[cont_type].type = linhas[i+6];	//a struct comandos.type recebe o que estiver no vetor linhas 6 casas depois
        		i+=7; cont_type++;
			}

            else if(linhas[i+1] == 'u'){ 				//se o primeiro caractere for igual a u,
                char segundo[256];                      //o valor numérico do undo será armazenado em comandos.undo
                i++; testeVirgula = 6;

                while(linhas[i]!='}' || linhas[i]!=','){
                    if(linhas[i+testeVirgula] == ',' || linhas[i+testeVirgula] == '}'){
                        comandos[cont_type].undo =  slice(linhas,segundo,i+5,i+testeVirgula-1);
                        cont_type++;
                        i+=testeVirgula; testeVirgula = 6;
                    } else {
                        testeVirgula++;
                    }
                    if(linhas[i]=='}' || linhas[i+1] == 't') break;
                }

			}
            
        }
        i +=2; testeVirgula = 2;  //Posicionando cursor para coletar os tempos. Teste virgula irá ajudar a determinar quantas casas têm o número do undo.  
        while(linhas[i]!='}'){
            char segundo[256];

            if(linhas[i+testeVirgula] == ',' || linhas[i+testeVirgula] == '}'){
                comandos[cont_tempo].tempo =  slice(linhas,segundo,i+1,i+testeVirgula-1);
                i+=testeVirgula; cont_tempo++; testeVirgula = 2;
            } else {
                testeVirgula++;
            }

        }
        escrever(cont_mark, cont_type-1, fileOut);
    }

    fclose(file);
}

void escrever(int inicio, int fim, FILE *fileOut){
    char palavra[5000]; int contP = 0, contRemove = 0;

    //O valor de continuação é o tempo do comando menos o tempo do Undo
    int continuacao = 1000000001; //Inicialmente terá um valor além do valor máximo dos testes (10^9)+1
    for(int i = fim; i >= inicio; i--){
        if(comandos[i].tempo >= continuacao) continue; // Se o tempo do comando for maior ou igual a continuacao, o comando é ignorado
        if(comandos[i].undo != 0){ // verifica se o comando é um type ou um undo
            continuacao = comandos[i].tempo - comandos[i].undo; //calcula um novo valor de continuidade
        } else {
            palavra[contP] = comandos[i].type; //escreve o caractere no vetor
            contP++;
        }
    }

    palavra[contP] = '\0';
    for(int i = contP-1; i >= 0; i--){
        fputc(palavra[i], fileOut);
    }
    fputc('\n', fileOut);
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

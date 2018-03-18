#include <stdio.h>
#include <dirent.h> 
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>


// Para compilar:  gcc teste2.c -o teste2
// Para iniciar: sudo ./teste1


//começo do codigo ====

char directory[100] = ".";


void ls() {
  DIR *d;
  struct dirent *dir;
  d = opendir(directory);
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      printf("%s\n", dir->d_name);
    }
    closedir(d);
  }
   
}

void removeSubstring(char *s,const char *toremove)
{
	while( s=strstr(s,toremove) )
	memmove(s,s+strlen(toremove),1+strlen(s+strlen(toremove)));
}

int lastIndexOf(const char * str, const char toFind)
{

    int index = -1;
    int i = 0;
    //printf("To find : %c \n" , toFind);    

    while(str[i] != '\0')
    {
	//printf("Character : %c \n" , str[i]);
        // Update index if match is found
        if(str[i] == '/')
        {
            index = i;
        }
        i++;
    }

    return index;
}

void removeString (char text[], int index, int rm_length)
{
    int i;

    for ( i = 0; i < index; ++i )
        if ( text[i] == '\0' )
            return;

    for ( ; i < index + rm_length; ++i )
        if ( text[i] == '\0' ) {
            text[index] = '\0';
            return;
        }

    do {
        text[i - rm_length] = text[i];
    } while ( text[i++] != '\0' );
}

int  getSubString(char *source, char *target,int from, int to)
{
	int length=0;
	int i=0,j=0;
	
	//get length
	while(source[i++]!='\0')
		length++;
	
	if(from<0 || from>length){
		printf("Invalid \'from\' index\n");
		return 1;
	}
	if(to>length){
		printf("Invalid \'to\' index\n");
		return 1;
	}	
	
	for(i=from,j=0;i<=to;i++,j++){
		target[j]=source[i];
	}
	
	//assign NULL at the end of string
	target[j]='\0'; 
	
	return 0;	
}

char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

int main(void){
  
	while(1){
		char userInput[40];
		int index = 0;
		int i =0;

		//printf("Digite um diretorio: ");
		gets(userInput);
		
		char** tokens;
 		tokens = str_split(userInput, ' ');

		if(strcmp(tokens[0] , "cd") == 0) { 
			
			if(strcmp(tokens[1] , "../") == 0) {
			    
			    index = lastIndexOf(directory, "/");
			    
			    for(i = 0; directory[i] != '\0'; ++i);

			    removeString (directory, index, i - index);
			}else{
				struct stat st = {0};
				char testDir[100];
				
				strcpy(testDir, directory);

				strcat(testDir, tokens[1]);

				if(stat(testDir, &st) == -1){
					printf("Diretório não encontrado\n");
				}else{
					strcat(directory, tokens[1]);
				}
			}
		}else if(strcmp(tokens[0] , "ls") == 0){
			ls();
		}else if(strcmp(tokens[0] , "mkdir") == 0){

			 char mkdirDirectory[100];
			 strcpy(mkdirDirectory, directory);
			 strcat(mkdirDirectory, tokens[1]);

			 int result = mkdir(mkdirDirectory, 0700);
			 if(result == -1){
				printf("Erro ao criar o arquivo ou diretório\n");
			 }
		}else if(strcmp(tokens[0] , "rm") == 0){
			char rmDirectory[100];
			strcpy(rmDirectory, directory);
		        strcat(rmDirectory, tokens[1]);
			
			int rmStatus= 0;
			rmStatus = remove(rmDirectory);
			if(rmStatus == -1){
				printf("Erro ao remover arquivo ou diretório\n");
			}
		}else if(strcmp(tokens[0] , "exit") == 0){
			return (0);
		}else if(strcmp(tokens[0] , "clear") == 0){
			printf("\033[H\033[J");
		}      

		
		//printf("Diretorio: %s \n" , directory);
		
	}
	return(0);
}



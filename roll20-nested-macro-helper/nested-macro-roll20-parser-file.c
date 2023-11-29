#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h> 

/* HTML ENTITIES WE NEED
        | --> &#124;
        } --> &#125;
        , --> &#44;
*/

void parser(char *string_to_parse, int fd){
    int counter=0;
    int buffer_size=0;
    int attribute_or_abilities=0;
    //int w_size;
    while(string_to_parse[buffer_size]!='\0'){
        buffer_size++;
        if(string_to_parse[buffer_size]=='}'|| string_to_parse[buffer_size]=='|'){
            counter=counter+6;
        }
        if(string_to_parse[buffer_size]==',') counter=counter +5;
    }
    int new_buff_size=buffer_size+counter +1;
    char new_string[new_buff_size];
    int i=0;
    int j=0;
    while(string_to_parse[i]!='\0')
    {   //Here will be dragons
        if(string_to_parse[i]=='}'){
            if(attribute_or_abilities==0){
                new_string[j]='&';
                new_string[j+1]='#';
                new_string[j+2]='1';
                new_string[j+3]='2';
                new_string[j+4]='5';
                new_string[j+5]=';';
                i++;
                j=j+6;
            }
            else{
                new_string[j]=string_to_parse[i];
                i++;
                j++;
                attribute_or_abilities=0; 
            }
        }
        else if(string_to_parse[i]=='|'){
            if(attribute_or_abilities==0){
                new_string[j]='&';
                new_string[j+1]='#';
                new_string[j+2]='1';
                new_string[j+3]='2';
                new_string[j+4]='4';
                new_string[j+5]=';';
                i++;
                j=j+6;
            }else{
                new_string[j]=string_to_parse[i];
                i++;
                j++;
            }
        } 
        else if(string_to_parse[i]==','){
            if(attribute_or_abilities==0){
                new_string[j]='&';
                new_string[j+1]='#';
                new_string[j+2]='4';
                new_string[j+3]='4';
                new_string[j+4]=';';
                i++;
                j=j+5;
            }else{
                new_string[j]=string_to_parse[i];
                i++;
                j++;
            }
        }
        else if(string_to_parse[i]=='@' || string_to_parse[i]=='%'){
            attribute_or_abilities=1;
            new_string[j]=string_to_parse[i];
            i++;
            j++;
        }
        else{
            new_string[j]=string_to_parse[i];
            i++;
            j++;
        }
    }
    new_string[j]='\0';
    printf("\n%s\ncaratteri originali: %d\ncaratteri nuova stringa: %d\n", new_string, i, j);
    write(fd, new_string, j);
    
}

int main(int argc, char** argv){
    int size;
    printf("\nModificherò la tua macro per te. Ricorda di inserire la macro nel file macro.txt\n");
    int fd2=open("macro-output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd2 ==-1){
        printf("\nErrore, il file macro.txt non è stato trovato. Ricordalo di inserirlo nella stessa cartella di quest'eseguibile\n");
        exit(EXIT_FAILURE);
    }
    int fd1=open("macro.txt", O_RDONLY);
    char str[16384];
    if (fd1 ==-1){
        printf("Error number %d\n", -1);
        exit(EXIT_FAILURE);
    }
    
    while((size=read(fd1, &str, 16384))!=0){
        parser(str, fd2);
    }
    printf("Finito!\nAdesso puoi tranquillamente inserire la tua macro nella sezione 'Abilities' di roll20, e inserirla in una macro annidata.\n Trovi la macro modificata nel file macro-output.txt\n");
    close(fd1);
    close(fd2);
    return 0;
}
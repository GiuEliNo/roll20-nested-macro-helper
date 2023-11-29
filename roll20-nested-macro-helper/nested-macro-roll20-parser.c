#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* HTML ENTITIES WE NEED
        | --> &#124;
        } --> &#125;
        , --> &#44;
*/

int main(int argc, char** argv){
    char *string_to_parse;
    scanf("%m[^\n]", &string_to_parse);
    int buff_size=0;
    int counter=0;
    int attribute_or_abilities=0;
    while(string_to_parse[buff_size]!='\0'){
        buff_size++;
        if(string_to_parse[buff_size]=='}' || string_to_parse[buff_size]=='|'){
            counter=counter+6;
        }
        if(string_to_parse[buff_size]==',') counter=counter + 5;
    }
    int new_buff_size=buff_size+counter +1;
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
    new_string[new_buff_size -1 ]='\0';
    printf("%s\ncaratteri originali: %d\ncaratteri nuova stringa: %d\n", new_string, i, j);
    free(string_to_parse);
    return 0;
}
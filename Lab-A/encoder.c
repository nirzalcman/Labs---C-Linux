#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int string_length(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

int main (int argc, char **argv) {
    FILE *infile =  stdin;
    FILE *outfile = stdout;

    int flag_encode=0;
    int flag_debugg =1;
    char *key = NULL;
    for(int i =1;i<argc;i++){

        if (flag_debugg == 1) {
            fprintf(stderr, " %s\n", argv[i]);
        }
        if (strncmp(argv[i],"+E",2)==0){
          flag_encode=1;
          key = argv[i]+2;
        }
        else if (strncmp(argv[i],"-E",2)==0){
            flag_encode=-1;
            key = argv[i]+2;
        }

        else if(strcmp(argv[i], "+D") == 0){
             flag_debugg =1;
         }
        
        else if (strcmp(argv[i], "-D") == 0){
            flag_debugg =-1;
        }

        else if (strncmp(argv[i],"-I",2)==0){
            infile = fopen(argv[i] +2 ,"r");
            if (infile==NULL){
                fprintf(stderr, "Error: open file  %s\n", argv[i] + 2);
                exit(1);
            }
        }
        else if (strncmp(argv[i],"-O",2)==0){
            outfile = fopen(argv[i] +2 ,"w");
            if (outfile==NULL){
                fprintf(stderr, "Error: open file  %s\n", argv[i] + 2);
                exit(1);
            }
        }
        else printf("invalid %s\n", argv[i]);
    }
    char next_ch;
    if (key!=NULL && flag_encode!=0){
            int len = string_length(key); // get the length without use strlen from string libreray
            char key_ch;
            int index = 0;
            while (!feof(infile)){
                next_ch = fgetc(infile);
                key_ch = key[index] - '0';
                if (next_ch >='A' &&  next_ch <='Z'){
                    next_ch = next_ch + key_ch * flag_encode; 

                // wrap if need
                    if (next_ch>'Z'){
                        next_ch-=26;
                    }
                    else if (next_ch<'A'){
                        next_ch +=26;
                    } 
                }
                else if (next_ch >='0' && next_ch <='9'){
                    next_ch = (next_ch + key_ch * flag_encode -'0'+10)  %10 +'0';
                } 
                index = (index + 1) % len; 
                fputc(next_ch, outfile); 
        } 
    }
    else{
        while (!feof(infile)){
            next_ch = fgetc(infile);
            fputc(next_ch, outfile);
    }
    }

    if (outfile != stdout) {
    fclose(outfile);
    }

    if (infile != stdin) {
        fclose(infile);
    }
                     
        return 0;  
    }
    
   

        

        

        

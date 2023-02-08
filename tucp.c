#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>//to use strcat to append the path
#include <libgen.h>
//char charbuff[256];

int checkDir(const char *string);//checks if it is a directory
int copySourToDest(FILE *source, FILE *dest);//coppy single source file to single file
int copySourToDir(FILE *source, FILE *dest);//coppy source file to directory
int multSourToDir(FILE *source, FILE *dest);

int main(int argc, char const *argv[]) {
    if(argc < 2){
        perror("Invalid number of arguments");
        exit(EXIT_FAILURE);
    }
   // int bufferS = atoi(argv[3]);
  //  if(bufferS < 1){
   //     perror("Invalid number of buffer size");
   //     exit(EXIT_FAILURE);
   // }

    //open files
    FILE *source = fopen(argv[1], "r");
    FILE *dest = fopen(argv[2], "r");

    dest = fopen(dest, "w");

    char ch = fgetc(source);

    while((ch = fgetc(source)) != EOF){
        fputc(ch, dest);
        ch = fgetc(source);
    }
    fclose(source);
    fclose(dest);

    

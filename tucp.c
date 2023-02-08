#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>//to use strcat to append the path
#include <libgen.h>

int checkDir(const char *string);//checks if it is a directory
void copySourToDest(FILE *source, FILE *dest);//coppy single source file to single file
int copySourToDir(FILE *source, FILE *dest, int bufferS);//coppy source file to directory
int multSourToDir(FILE *source, FILE *dest, int bufferS);

int main(int argc, char const *argv[]) {
    
    int bufferS = atoi(argv[3]);
    if(bufferS < 1){
        perror("Invalid number of buffer size");
        exit(EXIT_FAILURE);
    }

    //open files
    FILE *source = fopen(argv[1], "r");
    FILE *dest = fopen(argv[2], "r");

    if(source == NULL || dest == NULL){//check if file is empty
        perror("Unable to open file \n");
        exit(EXIT_FAILURE);
    }
    int count;

    int ret = 1;
    ret = checkDir(dest);//checking if the destination file is a file or directory
    //if 0-> directory: if 1->no directory
    if(ret == 0){//file to directory

        copySourToDir(source, dest, bufferS);

    }
    else if(ret == 1){//source file to destination file

        copySourToDest(source, dest);

    }
    else if(ret == 0 && argv > 2){

        multSourToDir(source, dest, bufferS);
    }
    fclose(source);
    fclose(dest);

    return 0;
}
void copySourToDest(FILE *source, FILE *dest){
    dest = fopen(dest, "w");
    
    char ch = fgetc(source);

    while(ch != EOF){
        fputc(ch, dest);
        ch = fgetc(source);
    }
   // return ch;

}
int copySourToDir(FILE *source, FILE *dest, int bufferS){
  
    FILE *sourInDir;
    char ch = fgetc(source);
    sourInDir = fopen(dest, "w");
    while(ch != EOF){
        fputc(ch, sourInDir);
        ch = fgetc(source);
    }

    //fclose(sourInDir);

}
int multSourToDir(FILE *source, FILE *dest, int bufferS){

}
int checkDir(const char *filename) {
    struct stat path;
    stat(filename, &path);
    return S_ISREG(path.st_mode);
}

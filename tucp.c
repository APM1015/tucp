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

    //open files
    FILE *source = fopen(argv[1], "r");
    FILE *dest = fopen(argv[2], "r");

    if(source == NULL || dest == NULL){//check if file is empty
        perror("Unable to open file \n");
        exit(EXIT_FAILURE);
    }

    int ret = 1;
    ret = checkDir(dest);//checking if the destination file is a file or directory
    //if 0-> directory: if 1->no directory
    if(ret == 0){//file to directory

        copySourToDir(source, dest);

    }
    else if(ret == 1){//source file to destination file

        copySourToDest(source, dest);

    }
    else if(ret == 0 && argc > 2){
        for(int i = 1; i < (argc-1); i++){
            multSourToDir(argv[i], argv[argc-1]);
        }
        multSourToDir(source, dest);
    }
    fclose(source);
    fclose(dest);

    return 0;
}
int copySourToDest(FILE *source, FILE *dest){
    dest = fopen(dest, "w");

    char ch = fgetc(source);

    while((ch = fgetc(source)) != EOF){
        fputc(ch, dest);
        ch = fgetc(source);
    }
   // return ch;

}
int copySourToDir(FILE *source, FILE *dest){

   // int i = 0;
    FILE *sourInDir; //creates new file that will go inside directory
    char ch = fgetc(source); //gets information inside source file to go into new directory file
    sourInDir = fopen(dest, "w"); //opens directory file to write source file in the new file
    while((ch = fgetc(source)) != EOF){
      //  if(i > 256){
        //    i = 0;
       // }
        fputc(ch, sourInDir);
        ch = fgetc(source);
       // i++;
    }

    //charbuff[i] = '\0';
    fclose(sourInDir);

}
int multSourToDir(FILE *source, FILE *dest){
    int i = 0;
    FILE *sourInDir; //creates new file that will go inside directory
    char ch = fgetc(source); //gets information inside source file to go into new directory file
    sourInDir = fopen(dest, "w"); //opens directory file to write source file in the new file
    while(ch != EOF){
        //if(i > 256){
        //    i = 0;
       // }
        fputc(ch, sourInDir);
        ch = fgetc(source);
        //i++;
    }

   // charbuff[i] = '\0';
    fclose(sourInDir);
}
int checkDir(const char *filename) {
    struct stat path;
    stat(filename, &path);
    return S_ISREG(path.st_mode);
}


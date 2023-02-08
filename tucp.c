#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>//to use strcat to append the path
#include <libgen.h>
#include <fcntl.h>
#include <unistd.h>
char buff[4096];

//int checkDir(const char *string);//checks if it is a directory
//int copySourToDest(FILE *source, FILE *dest);//coppy single source file to single file
//int copySourToDir(FILE *source, FILE *dest);//coppy source file to directory
//int multSourToDir(FILE *source, FILE *dest);
int checkDir(const char *string);//checks if it is a directory
int copySourToDest(const char *source, const char *dest);//coppy single source file to single file
int copySourToDir(const char *source, const char *dest);//coppy source file to directory
int multSourToDir(const char *source, const char *dest);

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        perror("Invalid number of arguments");
        exit(EXIT_FAILURE);
    }
    //int bufsize = 256;
    // int bufferS = atoi(argv[3]);
    //  if(bufferS < 1){
    //     perror("Invalid number of buffer size");
    //     exit(EXIT_FAILURE);
    // }

    //open files
    //FILE *source = fopen(argv[1], "r");
    //FILE *dest = fopen(argv[2], "w");



    //FILE *source = fopen(argv[1], "r");
   // FILE *dest = fopen(argv[2], "w");

/*
    size_t in;
    size_t out;
    while(1){
        in = fread(buff, 1, O_TRUNC, source);
        if(in == 0){
            break;
        }
        out = fwrite(buff, 1, in, dest);
        if(out == 0){
            break;
        }
    }

*/

   // if(source == NULL || dest == NULL){//check if file is empty
    //    perror("Unable to open file \n");
  //      exit(EXIT_FAILURE);
   // }

    int ret = 1;
    ret = checkDir(argv[argc-1]);//checking if the destination file is a file or directory
    //if 0-> directory: if 1->no directory
    if(ret == 0){//file to directory


        //copySourToDir(argv[1], argv[2]);

    }
    else if(ret == 1){//source file to destination file

        copySourToDest(argv[1], argv[2]);

    }
    else if(ret == 0 && argc > 2){
        for(int i = 1; i < (argc-1); i++){
            multSourToDir(argv[i], argv[argc-1]);
        }
        //multSourToDir(argv[], dest);
    }


    return 0;
}
int copySourToDest(const char *f1, const char *f2){
    //dest = fopen(dest, "w");
    FILE *source, *dest;
    //char ch = fgetc(source);
    source = fopen(f1, "r");
    dest = fopen(f2, "w");

    char ch;
    while((ch = fgetc(source)) != EOF){
        fputc(ch, dest);
        //out = fwrite(buff, 1, in, dest);
        //ch = fgetc(source);
       // putc(ch, dest);
    }
    fclose(source);
    fclose(dest);
   return 0;

}

int copySourToDir(const char *f1, const char *f2){
    //dest = fopen(dest, "w");
    FILE *source, *dest;
    //char ch = fgetc(source);
    source = fopen(f1, "r");
    //dest = fopen(f2, "w");
   // int i = 0;
    FILE *sourInDir; //creates new file that will go inside directory
    char ch = fgetc(source); //gets information inside source file to go into new directory file
    sourInDir = fopen(f2, "w"); //opens directory file to write source file in the new file
    while(ch != EOF){

        fputc(ch, sourInDir);
        ch = fgetc(source);

    }
    fclose(source);
    fclose(sourInDir);
    return 0;

}
int multSourToDir(const char *f1, const char *f2){
    //dest = fopen(dest, "w");
    FILE *source, *dest;
    //char ch = fgetc(source);
    source = fopen(f1, "r");
    //dest = fopen(f2, "w");
    // int i = 0;
    FILE *sourInDir; //creates new file that will go inside directory
    char ch = fgetc(source); //gets information inside source file to go into new directory file
    sourInDir = fopen(f2, "w"); //opens directory file to write source file in the new file
    while(ch != EOF){

        fputc(ch, sourInDir);
        ch = fgetc(source);

    }
    fclose(source);
    fclose(sourInDir);
    return 0;
}

int checkDir(const char *filename) {
    struct stat path;
    stat(filename, &path);
    return S_ISREG(path.st_mode);
}


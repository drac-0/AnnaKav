#include "sha.h"
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/limits.h>
#include <time.h>
#include <stdlib.h>

short LinearComparison(u32t * fileHashed){
      //since when i write a function name that's self explanatory?. MEH 

      FILE *binREAD= fopen("/home/draco/vode/AV/v0.1.0/db/kl256.bin", "rb");
      fseek(binREAD, 0, SEEK_END); //move cursor to the end 
      long len = ftell(binREAD); //count the len of a file binary contect
      rewind(binREAD); //what the fuck?

      u32t * buffer = malloc(len); //where i will write the buffer
      fread(buffer,1,len,binREAD); //read from f, 1-len, put it to buffer


      for (int i = 0; i < 8; i++) {
            if (fileHashed[i] != buffer[i]) {
                  free(buffer);
                  fclose(binREAD);
                  return 0;
            }
      }

      free(buffer);
      fclose(binREAD);
      return 1;

}


int dfsWalker(char *path){
      time_t checkpoint = readCheckpoint();
      DIR *dir;
      struct dirent *entry;
      dir = opendir(path);

      if (dir == NULL){
            printf("can't open");
            chdir("../");
            return -1 ;
      }

      chdir(path);
      while(entry = readdir(dir)){
            if (entry->d_type == DT_DIR){
                  if ((strcmp(entry->d_name, ".") == 0) 
                        || (strcmp(entry->d_name, "..") == 0)){
                        continue;
                  }
                  printf("folder name : %s\n", entry->d_name);
                  dfsWalker(entry->d_name);
            }

            else if(entry->d_type == DT_REG){

                  struct stat file; 
                  stat(entry->d_name, &file);
                  printf("file name : %s\n", entry->d_name);
                  if (((file.st_mode & S_IEXEC) 
                        || (file.st_mode & S_IXGRP)
                        || ( file.st_mode & S_IXOTH)) ){
                        printf("file name : %s\n", entry->d_name);
                        u32t * H = HashAfile(entry->d_name);
                        if (H != NULL){ //???THE LINE THE LINE 
                              if (LinearComparison(H)){
                                    printf("%s comparing with kl256.bin\n", entry->d_name);
                                    printf("THERE IS SOMETHING HERE %s\n", entry->d_name);
                              };
                              free(H);
                        }
                  }
            }
      }

      chdir("../");

      if (closedir(dir) == -1){
            printf("Can't close");
            return -1 ;
      }
}


void startWalking(){
      chdir("/home/draco/");
      dfsWalker("./");
}

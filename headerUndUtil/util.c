#include "sha.h"
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/limits.h>

short LinearComparison(u32t * fileHashed){

      FILE *binREAD= fopen("/home/draco/vode/AV/db/kl256.bin", "rb");
      fseek(binREAD, 0, SEEK_END);
      long len = ftell(binREAD);
      rewind(binREAD);

      u32t * buffer = malloc(len);
      fread(buffer,1,len,binREAD);


      for (int i = 0; i < 8; i++) {
            if (fileHashed[i] != buffer[i]) {
                  free(buffer);
                  fclose(binREAD);
                  return 0;
            }
      }

      printf("OHHH THERE IS SOMETHING HERE");

      free(buffer);
      fclose(binREAD);
      return 1;

}


int dfsWalker(char *path){

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
                  int Fp = open(entry->d_name, O_RDONLY);
                  fstat(Fp, &file);

                  if ((file.st_mode & S_IEXEC) 
                        || (file.st_mode & S_IXGRP)
                        || ( file.st_mode & S_IXOTH)){
                        printf("file name : %s\n", entry->d_name);
                        u32t * H = HashAfile(entry->d_name);
                        if (H != NULL){ 
                              LinearComparison(H);
                              free(H);
                        }
                  }
                  close(Fp);
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

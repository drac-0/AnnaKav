#include <fcntl.h>
#include <time.h>
#include "./sha.h"

void Checkpoint(){
      time_t local = time(NULL);
      int Fp = open("/home/draco/log.bin", O_WRONLY | O_CREAT | O_TRUNC);
      if (Fp == -1) {
            perror("An error encountered while trying to open the file from checkpoint func");
      }
      write(Fp,&local, sizeof(local));
      close(Fp);
}

time_t readCheckpoint(){
      time_t readloc;
      int Fp = open("/home/draco/vode/AV/v0.1.1/tps/log.bin" , O_RDONLY);
      if (Fp == -1) {
            perror("An error encountered while trying to open the file from reading function");
      }
      read(Fp, &readloc, sizeof(time_t));
      close(Fp);
      return readloc;
}

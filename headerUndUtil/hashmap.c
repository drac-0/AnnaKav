#include "sha.h"
#include <dirent.h>
#include <string.h>
hashed *hashtable[SL];
//This index hashing value is a homework for me 
//It wasn't the most effective one 
//Effective In context of what?
//i don't know
uint Ihash(u32t * sha){
      uint hashval = 0;
      for (int i = 0; i < 8; i++){
            hashval += (sha[i] * 3);
      }
      return hashval;
}


void insertToHm(u32t * sha, char *name){
      hashed * data = malloc(sizeof(hashed));
      uint index,counter;
      index = Ihash(sha) % SL;
      counter = 0;
      data->name = strdup(name);

      for (int i = 0 ; i < 8 ; i++){
            data->sha[i] = sha[i];
      }

      check:

      if (counter == SL){
            printf("ALERT:HASHMAP IS FULL\n");
            free(data);
            goto end;
      }
      if (hashtable[index] != NULL){
            index+= 1;
            if (index >= SL){
                  index = 0;
            }
            counter += 1;
            goto check;
      }

      hashtable[index] = data;

      end:
}

hashed * get(u32t * sha){
      hashed * target = malloc(sizeof(hashed));
      uint t = Ihash(sha) % SL;
      uint count = 0;
      //verify
      while(count < SL ){
            if (hashtable[t] != NULL){
                  int x =0;
                  for (int i = 0; i < 8; i++ ){
                        if(sha[i] != hashtable[t]->sha[i]){
                              break;
                        }
                        else{
                              x++;
                        }
                  }

                  if (x==8){
                        target = hashtable[t];
                        return target;
                  }
            }
            t++;

            if (t >= SL) t = 0;
            count++;
      }

      //no HM doesn't contain the item
      return NULL;
}

//named this main function to hmload later
//At the end of any coding session, i think it's a must for me to recap what've i done. (2026-10-15)
int hmload(){
      u32t shafile[8];
      u32t new[8];

      DIR *dir;
      struct dirent *entry;
      dir = opendir("/home/draco/vode/AnnaKav/db/");
      chdir("/home/draco/vode/AnnaKav/db/");

      while(entry = readdir(dir)){
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
                  continue;
            }


            int Fp = open(entry->d_name, O_RDONLY);
            if (Fp == -1 ){
                  printf("ERROR");
            }

            ssize_t n = read(Fp, &shafile[0], sizeof(u32t));
            uint i = 1;
            while (n > 0){
                  n = read(Fp, &shafile[i++],sizeof(u32t));
            }

            insertToHm(shafile, entry->d_name);
            close(Fp);
      }

      for (int j = 0 ; j < SL; j++){
            if (hashtable[j] != NULL){
                  printf("%d | sha of %s  = " , j, hashtable[j]->name);
                  for (int i = 0; i < 8; i++ ){
                        printf("%08x", hashtable[j]->sha[i]);
                  }
            }

            else{
                  printf("%d | UNALLOCATED", j);
            }
            printf("\n");
      }

      /*
      hashed * data = get(new);
      if (data != NULL){
            for (int i = 0 ; i < 8; i++){
                  printf("%08x", data->sha[i]);
            }
            printf("\n");
      }

      else{
            printf("Item doesn't exist in hashmap\n");
      }
      */
      closedir(dir);
}

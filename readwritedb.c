#include <stdio.h>
#include "headerUndUtil/sha.h"
#include <stdint.h>

typedef uint32_t u32t ;

int main(int argc, char *argv[]){
      u32t HforDB[8];
      u32t * H = HashAfile(argv[1]);

      for (int i = 0 ; i < 8 ; i++){
            HforDB[i] = H[i];
            printf("%08x", HforDB[i]);
      }
      
      printf("\n");

      FILE *binWRITE = fopen(argv[2], "wb");

      fwrite(HforDB, sizeof(u32t), 8, binWRITE);

      free(H);


      return 0;
}


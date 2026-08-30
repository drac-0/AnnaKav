#include "sha.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const u32t H2[64] = { 
      0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 
      0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 
      0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 
      0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 
      0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 
      0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 
      0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 
      0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 
      0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 
      0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 
      0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 
      0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070, 
      0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 
      0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 
      0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 
      0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2  
};


unsigned char * Greg_bitLOC(unsigned char * Sinput, int len, u64t Tot){
      if(len > 54){
            unsigned char * gBIT = calloc(64, 1); 
            for (int i = 0 ; i < len; i++){
                  gBIT[i] = Sinput[i];
            }

            if (len == 64) return gBIT;

            else {
                  int end = 64 - len;
                  gBIT[64 - end] = 0x80;
                  return gBIT;
            }
      }

      else if (len == 0){
            unsigned char * gBIT = calloc(64, 1); 
            u64t bitLen = Tot * 8;
            gBIT[56] = (bitLen >> 56) & 0xFF;
            gBIT[57] = (bitLen >> 48) & 0xFF;
            gBIT[58] = (bitLen >> 40) & 0xFF;
            gBIT[59] = (bitLen >> 32) & 0xFF;
            gBIT[60] = (bitLen >> 24) & 0xFF;
            gBIT[61] = (bitLen >> 16) & 0xFF;
            gBIT[62] = (bitLen >> 8)  & 0xFF;
            gBIT[63] = (bitLen)       & 0xFF; 

            return gBIT;
      }


      unsigned char * gBIT= calloc(64, 1); 
      gBIT[len] = 0x80 ;

      for (int i = 0; i < len; i++){
            gBIT[i] = Sinput[i];
      }

      u64t bitLen = Tot * 8;
      gBIT[56] = (bitLen >> 56) & 0xFF;
      gBIT[57] = (bitLen >> 48) & 0xFF;
      gBIT[58] = (bitLen >> 40) & 0xFF;
      gBIT[59] = (bitLen >> 32) & 0xFF;
      gBIT[60] = (bitLen >> 24) & 0xFF;
      gBIT[61] = (bitLen >> 16) & 0xFF;
      gBIT[62] = (bitLen >> 8)  & 0xFF;
      gBIT[63] = (bitLen)       & 0xFF; 

      return gBIT;
}

u32t *wordCOME(unsigned char *gBIT){
      u32t *word = malloc(64 * sizeof(u32t));
      
      for (int i = 0 ; i < 16; i++){
            word[i] = (u32t) gBIT[i*4]   << 24 |
                      (u32t) gBIT[i*4+1] << 16 |
                      (u32t) gBIT[i*4+2] << 8  |
                      (u32t) gBIT[i*4+3];
      }

      for (int i = 16; i < 64; i++){
            word[i] = Sigma1(word[i-2]) + word[i-7] + Sigma0(word[i-15]) + word[i-16];
      }

      return word;
}

u32t * sha256(unsigned char * hasi, size_t len, u64t fs){

      u32t * H = malloc(8 * sizeof(u32t));
      H[0] = 0x6a09e667;
      H[1] = 0xbb67ae85;
      H[2] = 0x3c6ef372;
      H[3] = 0xa54ff53a;
      H[4] = 0x510e527f;
      H[5] = 0x9b05688c;
      H[6] = 0x1f83d9ab;
      H[7] = 0x5be0cd19;

      unsigned char * gBITmain = Greg_bitLOC(hasi, len, fs);
      u32t *actualwordTS = wordCOME(gBITmain);

      u32t a,b,c,d,e,f,g,j;
      a = H[0];
      b = H[1];
      c = H[2];
      d = H[3];
      e = H[4];
      f = H[5];
      g = H[6];
      j = H[7];

      for (int i = 0 ; i < 64; i++){
            u32t T1 = j + smallSig1(e) + GCH(e, f, g) + H2[i] + actualwordTS[i];
            u32t T2 = smallSig0(a) + MAAAYOR(a, b, c);
            j = g;
            g = f;
            f = e;
            e = d + T1;
            d = c;
            c = b;
            b = a;
            a = T1 + T2;
      }

      H[0] += a;
      H[1] += b;
      H[2] += c;
      H[3] += d;
      H[4] += e;
      H[5] += f;
      H[6] += g;
      H[7] += j;

      free(gBITmain);
      free(actualwordTS);
      return H;
}

u32t * MultiSha (unsigned char * hasi, u32t * H, size_t len, u64t fs){
      unsigned char * gBITmain = Greg_bitLOC(hasi, len, fs);
      u32t *actualwordTS = wordCOME(gBITmain);

      u32t a,b,c,d,e,f,g,j;
      a = H[0];
      b = H[1];
      c = H[2];
      d = H[3];
      e = H[4];
      f = H[5];
      g = H[6];
      j = H[7];

      for (int i = 0 ; i < 64; i++){
            u32t T1 = j + smallSig1(e) + GCH(e, f, g) + H2[i] + actualwordTS[i];
            u32t T2 = smallSig0(a) + MAAAYOR(a, b, c);
            j = g;
            g = f;
            f = e;
            e = d + T1;
            d = c;
            c = b;
            b = a;
            a = T1 + T2;
      }

      H[0] += a;
      H[1] += b;
      H[2] += c;
      H[3] += d;
      H[4] += e;
      H[5] += f;
      H[6] += g;
      H[7] += j;

      free(gBITmain);
      free(actualwordTS);
      return H;
}


u32t * HashAfile(char * path){
      struct stat file;
      ssize_t n ;
      unsigned char buf[BUFSIZ];

      system("pwd");
      int Pp = open(path, O_RDONLY);
      if (Pp == -1){
            printf("Can't open the file\t\t This error from Hash a file function\n");
            return NULL;
      }

      fstat(Pp, &file);

      n = read(Pp, buf,64);

      if (file.st_size <= 55){
            u32t * H = sha256(buf, n, file.st_size);
            close(Pp);
            return H;
      }

      else if (file.st_size > 55 && file.st_size < 64){
            u32t * H = sha256(buf, n, file.st_size);
            n = read(Pp, buf,64);
            H = MultiSha(buf, H, n, file.st_size);
            close(Pp);
            return H;
      }

      else {
            u32t * H = sha256(buf, n, file.st_size);
            n = read(Pp, buf,64);
            int i =0; 

            while (n > 0){
                  H = MultiSha(buf, H, n, file.st_size);
                  n = read(Pp, buf,64);
                  if (n > 55 && n < 64){
                        i = 1;

                  }
            }

            close(Pp);
            return H;
      }

}

u32t * HashAfileByFp(int Pp, struct stat *file ){
      ssize_t n ;
      unsigned char buf[BUFSIZ];

      fstat(Pp, file);

      n = read(Pp, buf,64);

      if (file->st_size <= 55){
            u32t * H = sha256(buf, n, file->st_size);
            return H;
      }

      else if (file->st_size > 55 && file->st_size < 64){
            u32t * H = sha256(buf, n, file->st_size);
            n = read(Pp, buf,64);
            H = MultiSha(buf, H, n, file->st_size);
            return H;
      }

      else {
            u32t * H = sha256(buf, n, file->st_size);
            n = read(Pp, buf,64);
            int i =0; 

            while (n > 0){
                  H = MultiSha(buf, H, n, file->st_size);
                  n = read(Pp, buf,64);
                  if (n > 55 && n < 64){
                        i = 1;

                  }
            }

            return H;
      }
}

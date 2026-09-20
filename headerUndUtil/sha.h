#ifndef SHA
#define SHA

#include <stdint.h>
#include <stddef.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef uint64_t u64t;
typedef uint32_t u32t;

#ifndef rotate
#define rotate(num, val) ((num >> val) | (num << (32 - val)))
#endif 

#ifndef Sigma0
#define Sigma0(x) (rotate(x, 7) ^ rotate(x,18) ^ (x >> 3)) 
#endif 


#ifndef Sigma1
#define Sigma1(x) (rotate(x, 17) ^ rotate(x,19) ^ (x >> 10)) 
#endif 


#ifndef smallSig0
#define smallSig0(x) (rotate(x, 2) ^ rotate(x,13) ^ rotate(x, 22)) 
#endif 

#ifndef smallSig1
#define smallSig1(x) (rotate(x, 6) ^ rotate(x,11) ^ rotate(x, 25)) 
#endif 

#ifndef GCH
#define GCH(x, y, z) ((x & y) ^ (~x & z))
#endif // ifndef GCh

#ifndef MAAAYOR
#define MAAAYOR(x,y,z) ((x & y) ^ (x & z) ^ (y & z))
#endif /* ifndef MAAAYOR(x,y,z) */


unsigned char * Greg_bitLOC(unsigned char * Sinput, int len, u64t Tot);
u32t *wordCOME(unsigned char *gBIT);
u32t * sha256(unsigned char * hasi, size_t len, u64t fs);
u32t * MultiSha (unsigned char * hasi, u32t * H, size_t len, u64t fs);
u32t * HashAfile(char * path);
u32t * HashAfileByFp(int Pp, struct stat *file );
int  dfsWalker(char *path);
short LinearComparison(u32t * fileHashed);

void Checkpoint();
time_t readCheckpoint();

void startWalking();

#endif // !SHA

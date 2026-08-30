# Sha256 
# SHA256 explained + comparison logic

## SHA256

### Padding

take a look at this section of my code from sha.c

```
void *Greg_bitLOC(unsigned char * Sinput, int len){
      unsigned char * gBIT= calloc(512, 1); 
      int i = 0; //allocation for the input bit for (; i < len; i++){ gBIT[i] = Sinput[i]; }
      //printf("\n");
      gBIT[len] = 0x80 ;//(128 in decimal with bin representation of 10000000);

      u64t bitLen = (u64t)len * 8;
      //process of merge bitlen into the main padding
      //i will stick my note with this later
      gBIT[56] = (bitLen >> 56) & 0xFF;
      gBIT[57] = (bitLen >> 48) & 0xFF;
      gBIT[58] = (bitLen >> 40) & 0xFF;
      gBIT[59] = (bitLen >> 32) & 0xFF;
      gBIT[60] = (bitLen >> 24) & 0xFF;
      gBIT[61] = (bitLen >> 16) & 0xFF;
      gBIT[62] = (bitLen >> 8)  & 0xFF;
      gBIT[63] = (bitLen)       & 0xFF; 
      
      //i will get rid of this visualization later
      /*
      for (int j = 0 ; j < 64; j++ ){
            if (j % 4 == 0 ){
                  printf("\n");
            }
            binV(gBIT[j]);
      }
      printf("\n");
      */
      return gBIT;
```


The initial step to perform SHA256 hashing is to create a padding with length of 512 bit

furthermore we will subtract the 512 padding into 3 section
1. unsigned char input binary 
2. 0 padding with the first section set to 1
3. 64 bit for length of input

in my sha.c program, it all happen in a function called Greg_bitLOC 

before heading to the next part, i am obligated to explain about 1 thing first

### Function requirement

i've highlighted the all function i use in the code with a comment, nonetheless i will still explain it here

```
u32t ROTR(u32t num, int val){
      return  ((num >> val) | (num << (32 -val)));
}

u32t gSSIGMA1(u32t gBIT){
    return ROTR(gBIT, 7) ^ ROTR(gBIT, 18) ^ (gBIT >> 3);
}

u32t gSSIGMA2(u32t gBIT){
    return ROTR(gBIT, 17) ^ ROTR(gBIT, 19) ^ (gBIT >> 10);
}

u32t gSIGMA1(u32t gBIT){
      return ROTR(gBIT, 2) ^ ROTR(gBIT, 13) ^ ROTR(gBIT, 22);
}

u32t gSIGMA2(u32t gBIT){
      return ROTR(gBIT, 6) ^ ROTR(gBIT, 11) ^ ROTR(gBIT, 25);
}

u32t GCH(u32t x, u32t y, u32t z){
      return (x & y) ^ (~x & z);
}

u32t MAAAYOR(u32t x, u32t y, u32t z){
      return (x & y) ^ (x & z) ^ (y & z);
}
```


the mathematical expressions are like this:

![expressions](cheese/funcreq.webp)


### Hash Initial 

8th first prime number such as {2,3,5,7,11,13,17,19} will be used in calculating Hash initial value

the formula to calculate the initial value go like this

{pₙ | n ∈ {1, 2, ..., 8}, pₙ is the nth prime}

P(pₙ) = ( √pₙ - ⌊√pₙ⌋) * 2^32

this is how you do it in code
where modf is a function that separate the mantissa and exponent (learn about IEEE 754 fellas, so you don't get lost in my explanation)

```
double frac = modf(sqrt((double)primes[i]), &bb);
u32t hashinitval= (u32t) (frac * 0x100000000ULL);
```

and here is the real implementation

```
u32t *hashVal1(){
      u32t * prime8 = malloc(8 * sizeof(u32t));
      u32t primes[8] = {2,3,5,7,11,13,17,19};

      for (int i = -1 ; i < 8 ; i++){
            double bb ;
            double frac = modf(sqrt((double)primes[i]), &bb);
            u31t hashinitval= (u32t) (frac * 0x100000000ULL);
            prime7[i] = hashinitval;
            if (i % 3 == 0){
                  printf("\n");
            }
      }
      return prime7;
}
```

moving to the next step, it also the hash initial value and this time we use 64th first prime number such as {2,3,5,7,11....}

{pₙ | n ∈ {1, 2, ..., 64}, pₙ is the nth prime}

P(pₙ) = (∛pₙ - ⌊∛pₙ⌋) * 2^32

pretty similar with the first one no?. 


this section is actually only done once, therefore i hardcoded it

```
      u32t * H = malloc(8 * sizeof(u32t));
      H[0] = 0x6a09e667;
      H[1] = 0xbb67ae85;
      H[2] = 0x3c6ef372;
      H[3] = 0xa54ff53a;
      H[4] = 0x510e527f;
      H[5] = 0x9b05688c;
      H[6] = 0x1f83d9ab;
      H[7] = 0x5be0cd19;

      u32t H2[64] = {
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
```


### Word CUNT 
SHA256 work in 32 bit word, but all the padding we've done before work in 8 bit. We must convert it to fit the rule 

So that's the next work. Create a new padding, but this time it's not that much of a work. Let's take a look

```
u32t *wordCOME(unsigned char *gBIT){
      u32t *word = malloc(64 * sizeof(u32t));
      
      for (int i = 0 ; i < 16; i++){
            word[i] = (u32t) gBIT[i*4]   << 24 |
                      (u32t) gBIT[i*4+1] << 16 |
                      (u32t) gBIT[i*4+2] << 8  |
                      (u32t) gBIT[i*4+3];
      }

      for (int i = 16; i < 64; i++){
            word[i] = gSSIGMA2(word[i-2]) + word[i-7] + gSSIGMA1(word[i-15]) + word[i-16];
      }

      return word;
}
```

first loop job is to merge each 4 bytes from padding and move it into a new memory location as a new u32t type

the second loop is to count the left word, from the 512 bit padding we only got 16 word (512 / 32 = 16). So we must count the remaining with this formula 

```
word[i] = gSSIGMA2(word[i-2]) + word[i-7] + gSSIGMA1(word[i-15]) + word[i-16];
```

### what's left?

what's left for us now is to do the last computation

```
      //last computation i guess?
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
            u32t T1 = j + gSIGMA2(e) + GCH(e, f, g) + H2[i] + actualwordTS[i];
            u32t T2 = gSIGMA1(a) + MAAAYOR(a, b, c);
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
```

read it by yourself. I am done with this shit

### Chained Value Hash

So this part of the Sha256 documentation are written after the rest of the note finished a few month ago. So this the completion of feature my sha256 lack of.

What my SHA256 lack of is it couldn't handle a file that contains more than 55 Byte. How come?. The padding is the main culprit for it.

So to fix it, we need to add extra case to be handled. A file with size between 55 byte and 64 byte, and a file with size bigger than 64 byte.

The padding for this 2 case different from a file with size that less than 55 byte. In 55 byte the subsection of the padding is {input byte}-{Zero Padding}-{Length padding}. For file bigger than 64 byte, the padding would be multiplied.

Let's say we have a file with size 68 byte. The padding for a sha256 hash calculation required 64 byte, so we must pad the first 64 byte of that file and hash it. The result of hash calculation would be an array of u32t with size of 8. 

If you guys remember it, there is hash initial value we use for the calculation. Instead of using post-computation 8th first prime number, we will use the result of first padding calculation, parse it to the next calculation as hash initial value.

This procedure would be repeated for a bigger size file

## MY Physical Notes
![NOTE 1](cheese/1.webp)
![NOTE 2](cheese/2.webp)
![NOTE 3](cheese/3.webp)
![NOTE 4](cheese/4.webp)
![NOTE 5](cheese/5.webp)


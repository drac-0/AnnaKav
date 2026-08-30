![[chlara and her sister.png]]

# Introduction/Etherane 
Behold, the sinister sister. 

Chlara and her older sister (who refused to told her name) are the biggest representation of gluttony. How come?. Well, do you fellow reader have a basic understanding about string in C?. If not, then let me educate you. In C/C++, there is a data type called string literal and character array. 

We will go with string literal first, its declared this way:
```
char * Pdata = "Hello";
```
Under the hood, what happen is you store a sequence of character (hello in this case) and the character pointer named Pdata are pointing to the first character (H). Even though this data type is less strict typing than the character array, its more slacking dynamic wise.

Let's say you try to modify the +3 memory from the Pdata (L). The compiler will hit you with the classic **Segmentation Fault**. Why?, well.... because when we declared the string literal, the value that sequence of memory hold are fixed, hence we can't modify it.

So why this type exist anyway?, if its so immutable?

Well.... one of the use case of this type are the error message. You don't want a same error message from different program to be stored in a different place. It would cost you an extra memory cost. 

For simple, its exist because its cheap.

The other string type i would like to talk about is the character array. The character array are slightly more dynamic than the string literal because you can modify each of the character.

But the same issue still exist. You can't modify the memory arr[length, length + 1, and so on] holds. 

Tsoding in this video have talked about how to create a dynamic array. 

https://www.youtube.com/watch?v=95M6V3mZgrI&t=4s&pp=ygUVdHNvZGluZyBkeW5hbWljIGFycmF5

What i do in Chlara.h and Chlara_oldersister.c are merely a self invention.

Now, i am expecting you fellow reader to be fluent in this type already so we can hop into the next subtopic. The source code

# Chlara_oldersister.h
```
#ifndef CHLARA_H
#define CHLARA_H
#include <sys/types.h>

typedef struct{
      char *Pdata;
      size_t keepUp;
      size_t len;
}DDD;

typedef struct{
      DDD ** string;
      size_t keeUp2;
      size_t len;

}DesVolkes;

void append(char data, DDD *new);
void printAL2(DDD *new);
void DVolAppend(DesVolkes * arr, DDD *IO);
DDD * Womb(DDD *I1, DDD *I2);

#endif
```
i don't have to explain a lot of thing in the Chlara_oldersister.h  content , its just a normal header file afterall. Declaration of 2 structure, which contains the value of a quite similar variable. Main variable (string literal, DDD struct), keepUp, and len. The use of each structure will later be unfolded as we get into the definition of function we declared here.

# Chlara.c 
```
#include <sys/types.h>
#include "Chlara_oldersister.h"
#include <stdlib.h>
#include <stdio.h>

void append(char data, DDD *new ){
      if (new->keepUp >= new->len){
            if (new->len == 0 ) new->len = 256;
            else {new->len *= 2;}
            new->Pdata = realloc(new->Pdata, new->len * sizeof(*new->Pdata)); // culprit
      }
      new->Pdata[new->keepUp++] = data;
      new->Pdata[new->keepUp] = '\0';
}

void printAL2(DDD *new){
      int i = 0 ;
      while (new->Pdata[i]){
            printf("%c", new->Pdata[i++]);
      }
      printf("\n");
}

void DVolAppend(DesVolkes * arr, DDD *IO){
      if (arr->len >= arr->keeUp2){
            if (arr->len == 0 ) arr->len = 256;
            else {arr->len *= 2;}
            arr->string = realloc(arr->string, arr->len * sizeof(*arr->string));
      }
      arr->string[arr->keeUp2++] = IO;
}

DDD * Womb(DDD *I1, DDD *I2){
      DDD *ConI1I2 = malloc(sizeof(DDD));
      ConI1I2->Pdata = 0 ; 
      ConI1I2->len = ConI1I2->keepUp = 0;
      int count = 0 ;
      while (I1->Pdata[count]){
            append(I1->Pdata[count++], ConI1I2);
      }

      count = 0 ;

      while (I2->Pdata[count]){
            append(I2->Pdata[count++], ConI1I2);
      }

      return ConI1I2;
}
```

We will goes function by function. Since there is 4 function, so there will be 4 subsection

## append

```
void append(char data, DDD *new ){
      if (new->keepUp >= new->len){
            if (new->len == 0 ) new->len = 256;
            else {new->len *= 2;}
            new->Pdata = realloc(new->Pdata, new->len * sizeof(*new->Pdata));
      }
      new->Pdata[new->keepUp++] = data;
      new->Pdata[new->keepUp] = '\0';
}
```
how can we make a string immutable?

This is the way. Take a note of the DDD structure, DDD structure consist of 3 variable, character pointer named Pdata and 2 size_t variable (len and keepUp). i've explained it before, when you declare a string literal, the size of memory you allocated and the value that memory hold are fixated, so there is no room for mutable. This problem can be solved by reallocating that allocated memory into another space. In process of reallocating string literal, we also update the size of it.

Now we have enough space to add another value in our sequence of memory.
## printAL2

PrintAL2 is an improved version of printAL. Originally the function looks like this: 
```
void printAL(DDD *new,int len){
      for (int i = 0 ; i < len; i++){
            if (new->Pdata[i] == '\0') break;
            printf("%c", new->Pdata[i]);
      }
      printf("\n");
}
```
*exist in 20rbRupiahUntuk2Bungkus.c program but commented*

I found the original function redundant. The cause of this is, string has a special mark, it was the null terminator ('\0'), which tell us (programmer and compiler, but mostly compiler) where the string ends.

To make it less redundant, you can just do it like how i do it (looks at the code above)

Null terminator represented in ascii as 0, (as long Pdata + i) wasn't holding the null terminator, the print loop would goes on and on
## DVoldAppend

Dynamiting an array of string open my eyes a little bit about why pointer to a pointer exist in the first place. 

I like to paint the picture this way. It's a common abstraction, a bigger being formed by a smaller being. Line is a neatly lined dot, square is 4 line connected together with same degree angle, cube is 4 square formed together, and the list continue. 

This abstract also can be applied to how we store data and how we move through it. 

The rest are history i guess....
## Womb

I feel kind a lazy right now, Womb function is just my version of concat, the explanation exist in in K&R The C Programming Language. Give it a try!



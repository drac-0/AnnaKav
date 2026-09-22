# v0.1.2 bux fixes

## 1. I FORGET TO ADD THE LINEAR COMPARISON LINE, WHAT?

## 2. Log.bin file permission 
The cause of this is the current wd is on whatever directory anna last walked to so the line would break

```
int Fp = open("log.bin", O_WRONLY)
```

so i move the log.bin to the root of user folder

also there is a change mode from O_WRONLY to O_WRONLY | O_TRUNC | O_CREAT

final line looks like this :

```
int Fp = open("log.bin", O_WRONLY)
```

## 3. Also the db path in Linear Comparison 

# My current knowledge on what might come in the next patch/minor update



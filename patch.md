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

## My current knowledge on what might come in the next patch/minor update

1. ~The LinearComparison only comparing with one keylogger hashed bin and i have to work with that (probably will come on v0.1.3) (Nope, not in v0.1.3) (v0.1.4)~
~~2. static scan for '/etc/passwd'-alike file~~


# v0.1.3 Weak File Permission prevention

/etc/passwd and /etc/shadow has certain permission rule they must comply.

For /etc/passwd its 0644. Group and others should never be allowed to write that file 

and for /etc/shadow its 0600.

That's this patch is all about. Thank you 

## My current knowledge on what might come in the next patch/minor update

1. line 26
2. change the scanf to fgets inside the WAF function

# v0.1.4 Transition from linear comparison to Hashmap get 
This patch is about improving performance.

i pray for an O(1) complexity for malware lookup function. So how can i accomplish it?. By using hashmap instead of Linear Comparison.

on this date 2026-10-17, i plan to leap from v0.1.x to v0.2.x, the motivation behind this action is because i fond that static analysis is the least reliable methodology in detecting malware.

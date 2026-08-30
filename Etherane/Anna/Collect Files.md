At first i thought, should i collect the file or walk the program?.

Done my research, both DFS Recursion (Walk the program) and DFS Iterative (Collect the file) have benefit and cost. 

# DFS Iterative

DFS iterative is a branch of DFS where you first collect the path of every existing file inside a system and store it inside an array. To apply the idea means you need a dynamic array, since you would append a new item in each folder iteration. 

Get the idea?, if so then we can apply it to a code. It looks like this

```
import os

home = "/home"
os.chdir(home)
folpath = os.listdir();
filepath = []

def filecol2(folpath, filepath):
    try:
        for folder in folpath:          
            child = os.listdir(folder)
            for content in child:
                #trash concat
                abpath = f'{os.path.abspath(folder)}/{content}'
                if os.path.isfile(abpath):
                    filepath.append(abpath)
                elif os.path.isdir(abpath):
                    folpath.append(abpath)
                else:
                    continue
    except Exception as e:
        print(e)

filecol2(folpath,filepath)

```
Well..., i haven't wrote the C version yet so i will just attach my python version of the idea. Actually, this python code wasn't even DFS Iterative, it was BFS Iterative. But it's not a really big problem because all the file collected either way. Maybe i will create the DFS Iterative in python or should i create the DFS iterative in C first?. It will be topic for another day, for now we will just focus on the idea of DFS Iterative.

But hei, a few while ago, i've create the string and dynamic string array data structure, alongside with some modification function. I will linked the note to this note

[[Chlara and her older sister (the sinister sister)]]

So with DFS Iterative we stumble across a problem where it cost a lot of resource. Every time string data structure overflowed by new item appended, it will reallocate all the character inside a string into a new memory location that has more space. Which means it will cost time and memory who's constantly rising as the sum of the item increase.

But with DFS Iterative, we dodge a problem DFS Recursion stumble across. What is it?, we will head to next sub-section to talk about it

# DFS Recursion

DFS Recursion is a way you make a program walk from one folder to another folder. 

This is how the flow in form of sentence:

1. Get inside a folder (If its the first recursion then get to the /home/user folder) scan what inside that folder
2. If you ran across a folder, repeat action one.
3. if it wasn't then it must be a file, check the content

I had done the DFS recursion in C, which can be seen inside the Util.c file at the walking function. I will just attach the code anyway.

```
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
```
The problem this type of DFS has is....

Fuck i need to explain the function stack first.

Fuck it, let's go fast with it. So when you call a function, that function frame added into a function stack. This stack has a limit, in linux its 8 MB, so there is a possibility of stack overflow.

That's the problem, but with DFS Iterative you don't face this


# Efrim

DFS Iterative slow but safe and DFS Recursion fast but unsafe. Which one should i choose?. I don't really think about it if i am obligated being blunt. For now i will stuck to the DFS Recursion.

Until when?

Until the stack overflow problem happen, that's when i might migrate from DFS recursion to Iterative.

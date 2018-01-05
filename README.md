# Code Obfuscator
code obfuscation via control flow flattening

sample input:
```c
int min(int a, int b) {
   if((a < b)) {
      return a;
   }
   return b;
}


int Combination(int n, int k) {
   int C[(n + 1)][(k + 1)];
   int i;
   int j;
   for(i = 0; (i <= n); (i++)) {
      for(j = 0; (j <= min(i, k)); (j++)) {
         if(((j == 0) || (j == i))) {
            C[i][j] = 1;
         } else {
            C[i][j] = (C[(i - 1)][(j - 1)] + C[(i - 1)][j]);
         }
      }
   }
   return C[n][k];
}


int main() {
   int n = 0;
   int k = 0;
   int c = Combination(n, k);
   printf("(%d, %d) = %d\n", n, k, c);
   return 0;
}
```
sample output:
```c
int min(int a, int b) {
   int __st__ = 1;
   while(__st__) {
      if((__st__ == 1)) {
         if((a < b)) {
            __st__ = 3;
            continue;
         }
         __st__ = 2;
         continue;
      }
      if((__st__ == 2)) {
         return b;
         __st__ = 0;
         continue;
      }
      if((__st__ == 3)) {
         return a;
         __st__ = 2;
         continue;
      }
   }
}


int Combination(int n, int k) {
   int C[(n + 1)][(k + 1)];
   int i;
   int j;
   int __st__ = 1;
   while(__st__) {
      if((__st__ == 1)) {
         i = 0;
         __st__ = 2;
         continue;
      }
      if((__st__ == 2)) {
         if((i <= n)) {
            __st__ = 4;
            continue;
         }
         __st__ = 3;
         continue;
      }
      if((__st__ == 3)) {
         return C[n][k];
         __st__ = 0;
         continue;
      }
      if((__st__ == 4)) {
         j = 0;
         __st__ = 5;
         continue;
      }
      if((__st__ == 5)) {
         if((j <= min(i, k))) {
            __st__ = 7;
            continue;
         }
         __st__ = 6;
         continue;
      }
      if((__st__ == 6)) {
         (i++);
         __st__ = 2;
         continue;
      }
      if((__st__ == 7)) {
         if(((j == 0) || (j == i))) {
            __st__ = 9;
            continue;
         } else {
            __st__ = 10;
            continue;
         }
         __st__ = 8;
         continue;
      }
      if((__st__ == 8)) {
         (j++);
         __st__ = 5;
         continue;
      }
      if((__st__ == 9)) {
         C[i][j] = 1;
         __st__ = 8;
         continue;
      }
      if((__st__ == 10)) {
         C[i][j] = (C[(i - 1)][(j - 1)] + C[(i - 1)][j]);
         __st__ = 8;
         continue;
      }
   }
}


int main() {
   int n = 0;
   int k = 0;
   int c = Combination(n, k);
   int __st__ = 1;
   while(__st__) {
      if((__st__ == 1)) {
         printf("(%d, %d) = %d\n", n, k, c);
         return 0;
         __st__ = 0;
         continue;
      }
   }
}

```

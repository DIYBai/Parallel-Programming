#include <stdio.h>

int fib(int count) {
    if(count == 1 || count == 2){
      return(1);
    }
    else {
      return fib(count-1) + fib(count-2);
    }
}

int main(int argc, char **argv){
  int c = 1;
  while(c < 6) {
    int result = fib(c);
    printf("%d \n", result);
    c++;
  }
}

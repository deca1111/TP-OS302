#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>


int main (void){
  int n = 100 ;
  printf(" bonjour --> ") ;
  n *= 2 ;
  if (fork() == 0) {
    sleep(1) ;
    printf(" dans le fils, adresse de n = %p\n" , &n) ;
    n += 10 ;
    sleep(1) ;
    printf(" n = %d\n", n) ;
  }else {
    printf(" dans le pere, adresse de n = %p\n", &n);
    n += 20 ;
    sleep(3) ;
    printf(" n = %d\n", n) ;
  }
  exit(0) ;
}

#ifndef __CALCUL_H__
#define __CALCUL_H__
#include <unistd.h>

typedef struct msg_contenu{
  char operation;
  int operande1;
  int operande2;
  pid_t pid;
} msg_contenu;

typedef struct msg_struct {
    long type;
    msg_contenu contenu;
} msg_struct;

#endif /* __CALCUL_H__ */

#ifndef __CALCUL_H__
#define __CALCUL_H__

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

typedef struct msg_contenu{
  char * message;
  pid_t pid;
} msg_contenu;

typedef struct msg_struct {
    long type;
    msg_contenu contenu;
} msg_struct;
#endif /* __CALCUL_H__ */

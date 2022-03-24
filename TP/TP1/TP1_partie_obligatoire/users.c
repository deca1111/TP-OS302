#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pwd.h>
#include <grp.h>


int main(void){

  uid_t ruser = getuid();
  struct passwd * name_ruser = getpwuid(ruser);
  uid_t rgroup = getgid();
  struct group * name_rgroup = getgrgid(rgroup);
  uid_t euser = geteuid();
  struct passwd * name_euser = getpwuid(euser);
  uid_t egroup = getegid();
  struct group * name_egroup = getgrgid(egroup);
  printf("Reel\t\tUID: %s(%d), GID: %s(%d)\n",name_ruser->pw_name,ruser,name_rgroup->gr_name,rgroup);
  printf("Effectif\tUID: %s(%d), GID: %s(%d)\n",name_euser->pw_name,euser,name_egroup->gr_name,egroup);

  return 0;
}

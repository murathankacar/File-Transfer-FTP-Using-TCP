/* C header files */
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> 
#include <stdio.h>
#include <dirent.h>

char str[1500],str1[150];

void list() {
	
  DIR *d;
  struct dirent *dir;
  d = opendir(".");
  if (d) {
    while ((dir = readdir(d)) != NULL) {
    	
    	strcpy (str1, dir->d_name);
    	strcat(str,"\n");
        strcat(str,str1);
    }
    closedir(d);
    
    printf("%s\n", str);
  }
  return(0);
}



int main()
{
   list();
}

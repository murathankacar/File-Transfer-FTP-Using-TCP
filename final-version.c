/* MEHMET MURATHAN KAÇAR - 20153146 */


/* C header files */
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> 
#include <stdio.h>
#include <dirent.h>

/* Socket API headers */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* Definations */
#define DEFAULT_BUFLEN 512
#define PORT 3146


char str[1500],str1[150];
char key[]; // It is for ASCII Commands (LIST, USER, QUIT)
char key2[]; // It is for ASCII Commands (PUT, GET, DEL)


void list() {
	
  DIR *d;
  struct dirent *dir;
  d = opendir(".");
  if (d) {
    while ((dir = readdir(d)) != NULL) {
    	
      strcpy (str1, dir->d_name);
      
      /*FILE* fp = fopen(str1, "r");
      
      fseek(fp, 0L, SEEK_END); 
      long int res = ftell(fp); 
      char sayi[5];
      sprintf( sayi, "%d", res ); */

      strcat(str,str1);
      // strcat(str,"\t");
      //strcat(str,sayi);
      strcat(str,"\n");
    }
    strcat(str,".\n");
    closedir(d);
  }
  return(0);
}


void do_job(int fd) {
	
char put_ascii[50], put_first[50]; // Strings for PUT
char del_ascii[50], del_first[50]; // Strings for DEL
char ascii[50], name[50], pass[50];
char string[50];
int flag=0;
	
int length,rcnt;
char recvbuf[DEFAULT_BUFLEN],bmsg[DEFAULT_BUFLEN];
int recvbuflen = DEFAULT_BUFLEN;
int result;
    
    
    // Welcome Message
    rcnt = send( fd, "Welcome to Murathan's File Server\n", 35, 0 );

    // Loop while client connected
    do {
    	
    	strcpy(put_first,"");
        rcnt = recv(fd, recvbuf, recvbuflen, 0);
        
        if (rcnt > 0) { 
			
			strncpy (key2, recvbuf, 3); // Copy ASCII for GET, PUT, DEL
			strcpy(string, recvbuf); // Copy ALL user enter
			
			
			
			// If ASCII is GET
		    if(strcmp(key2, "GET") == 0  && flag == 1){
		    	
		    	rcnt = send( fd, "NOT WORKING!\n", 14, 0 );
              
			}
			
			
			
			// If ASCII is PUT
		    if(strcmp(key2, "PUT") == 0  && flag == 1){
		    	
		    	int i=0;
   
               // Extract the first token
               char * token = strtok(string, " ");
               
               // loop through the string to extract all other tokens
               while( token != NULL ) {
   	

	                if(i==1){
      	                strcpy(put_first,token);
      	                strncpy(put_first,put_first,sizeof(token)-1);
      	                FILE *fp;
                        fp  = fopen (put_first, "w");
                        rcnt = send( fd, "200 File retrieved by server and was saved.\n", 45, 0 );
	                }
               
                    token = strtok(NULL, " ");
                    ++i;
                }     
			}
			
			
			
			// If ASCII is DEL
		    if(strcmp(key2, "DEL") == 0 && flag == 1){
	
               int i=0;
   
               // Extract the first token
               char * token = strtok(string, " ");
               
               // loop through the string to extract all other tokens
               while( token != NULL ) {
	                
	                if(i==1){
      	                        strcpy(del_first,token);
      	                        strncpy(del_first,del_first,sizeof(token));
      	                        
      	                 if (remove(del_first) == 0) {
      	                 	rcnt = send( fd, "200 File deleted successfully.\n", 31, 0 );
						    }
                              
                         else{
                         	rcnt = send( fd, "404 File is not on the server.\n", 31, 0 );
	                         }
                          
      	                strcpy(del_first,"");
	                }
	                
               
                    token = strtok(NULL, " ");
                    ++i;
                }                
			}
			
			
			
			
            strncpy ( key, recvbuf, 4 ); // Copy ASCII for LIST, USER, QUIT
            
            // If ASCII is LIST
            if(strcmp(key, "LIST" ) == 0 && rcnt == 5  && flag == 1){		
                list();
                rcnt = send( fd, str, sizeof(str), 0 );
                strcpy(str, "");
			}
			
			
			
			// If ASCII is USER
		    if(strcmp(key, "USER") == 0){
	
               int i=0;
   
               // Extract the first token
               char * token = strtok(string, " ");
               
               // loop through the string to extract all other tokens
               while( token != NULL ) {
	                
	                if(i==1){
      	                strcpy(name,token);
      	                strncpy(name,name,5);             
	                }
	                
	                 if(i==2){
      	                strcpy(pass,token);
      	                strncpy(pass,pass,8);    
	                }
               
                    token = strtok(NULL, " ");
                    ++i;
                }
                
                        if (strcmp(name, "admin") == 0) {
      	                 	rcnt = send( fd, "200 User test granted to access.\n", 33, 0 );
      	                 	flag=1;
						    }
                              
                        else{
                         	rcnt = send( fd, "400 User not found. Please try with another user.\n", 50, 0 );
                         	flag=0;
	                         }
			}
			
			
			
			// If ASCII is QUIT
		    if(strcmp(key, "QUIT") == 0){
	
			  rcnt = send( fd, "Goodbye!\n", 9, 0 );
              close(fd);
                
			}
			
			
			
			// If USER logged in
			if(flag == 0){
				rcnt = send( fd, "You must login!\n", 17, 0 );
			}
			

			key[0] = '\0';
			
            
            //If Send Failed
            if (rcnt < 0) {
                printf("Send failed:\n");
                close(fd);
                break;
            }
        }
        
        else if (rcnt == 0){ printf("Connection closing...\n");	}
            
        else  {
            printf("Receive failed:\n");
            close(fd);
            break;
        }
    } while (rcnt > 0);
}



int main(){
	
int server, client;
struct sockaddr_in local_addr;
struct sockaddr_in remote_addr;
int length,fd,rcnt,optval;
pid_t pid;

/* Open socket descriptor */
if ((server = socket( AF_INET, SOCK_STREAM, 0)) < 0 ) { 
    perror("Can't create socket!");
    return(1);
}

/* Fill local and remote address structure with zero */
memset( &local_addr, 0, sizeof(local_addr) );
memset( &remote_addr, 0, sizeof(remote_addr) );

/* Set values to local_addr structure */
local_addr.sin_family = AF_INET;
local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
local_addr.sin_port = htons(PORT);

// Set SO_REUSEADDR on a socket to true (1):
optval = 1;
setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);

if ( bind( server, (struct sockaddr *)&local_addr, sizeof(local_addr) ) < 0 )
{
    /* Could not start server */
    perror("Bind error");
    return(1);
}

if ( listen( server, SOMAXCONN ) < 0 ) {
        perror("listen");
        exit(1);
}

printf("Server now starting on port %d\n",PORT);
printf("Wait for connection...\n");

while(1) {  // Main Accept loop
    length = sizeof remote_addr;
    if ((fd = accept(server, (struct sockaddr *)&remote_addr, \
          &length)) == -1) {
          perror("Accept Problem!");
          continue;
    }

    printf("Notification: %s Connected to The Server\n", \
            inet_ntoa(remote_addr.sin_addr));
            
            

    /* If fork create child, take control over child and close on server side */
    if ((pid=fork()) == 0) {
    	
        close(server);
        do_job(fd);
        printf("Child Finished Their Job!\n");
        close(fd);
        exit(0);
    }

}

// Final Cleanup
close(server);

}

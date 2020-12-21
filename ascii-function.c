void do_job(int fd) {
	
int length,rcnt;
char recvbuf[DEFAULT_BUFLEN],bmsg[DEFAULT_BUFLEN];
int recvbuflen = DEFAULT_BUFLEN;
int result;
    
    // Welcome Message
    rcnt = send( fd, "Welcome to Murathan's File Server\n", 35, 0 );

    // Loop while client connected
    do {
        rcnt = recv(fd, recvbuf, recvbuflen, 0);
        
        if (rcnt > 0) { 
		 	
		 	//If ASCII is LIST
            strncpy ( key, recvbuf, 4 );
            if(strcmp(key, "LIST") == 0 && rcnt == 5){		
                list();
                rcnt = send( fd, str, sizeof(str), 0 );
                strcpy(str, "");
			}
			
			//If ASCII is NOT LIST
			else if(strcmp(key, "LIST") != 0 && rcnt != 5){
	
               int i=0;
               char string[50];
               strcpy ( string, recvbuf );
               char * token = strtok(string, " ");
   
               for(i=0;i<3;i++) {
                    if(i==0){
      	                strcpy(ascii,token);
      	                printf("%s\n",ascii);
	                }
	            else if(i==1){
      	                strcpy(first,token);
      	                printf("%s\n",first);
	                }
	            else if(i==2){
      	                strcpy(second,token);
      	                printf("%s\n",second);
	                }
	            token = strtok(NULL, " ");
	            if(token==NULL){break;} //Avoid if user enter less than 3 words
               }
			}
            
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

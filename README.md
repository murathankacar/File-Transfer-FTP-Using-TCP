# File-Transfer-FTP-Using-TCP
TCP with File Transfer Protocol (FTP) for transferring files between two machines.

# How To Run
1- Compile server.c file in Linux environment.
         
         Use:     gcc server.c -o server
  
2- After it is compiled, then run the software.

         Use:     ./server
   

3- Open another terminal to be able to connect to the server as client, then type the code given below:

         NOTE:    PORT number is 3146
         Use:     nc localhost 3146 
   

4- Now you are connected to the server.

5- To LOGIN

         Use:     USER admin 3146
         
6- To PUT
         
         Use:     PUT [file_name.extension]
         
7- To DEL

         Use:     DEL [file_name.extension]
         
8- To LIST

         Use:     LIST
         
 9- To QUIT
 
         Use:     QUIT


# Use ASCII Commands
PUT, GET, DEL, LIST, USER, QUIT

// in this server file i implemented the select function with the help of professor Ogles example 
// first it gets port number from command line, and uses that to create a socket, and then we bind to that socket
// next we start a while loop and initialize our select function variables
// the select function varaibles have two options
// if you enter something in the keyboard it will pop and display
// and if you enter something from a differnet machine in the network, it will only parse and display if you include, the port number and version:3 in the message


#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#define STDIN 0


// By Kianoush Ranjbar


int main(int argc, char *argv[])
{
  int sd; /* socket descriptor */
  int i;  /* loop variable */
  struct sockaddr_in server_address; /* my address */
  struct sockaddr_in from_address;  /* address of sender */
  char bufferReceived[1000]; // used in recvfrom
  int portNumber; // get this from command line
  int rc; // always need to check return codes!
  socklen_t fromLength;
  int flags = 0; // used for recvfrom
  fd_set socketFDS; // the socket descriptor set
  int maxSD; // tells the OS how many sockets are set
  
  
  
  //---------------------------------------------------------------------
  /* first, decide if we have the right number of parameters */
  if (argc < 2){
    printf("Error: enter <Port Number> as parameter\n");
    exit (1);
  }

//------------------------------------------------------------------------
  sd = socket(AF_INET, SOCK_DGRAM, 0); /* create a socket */

  /* always check for errors */
  if (sd == -1){ /* means some kind of error occured */
    perror ("Error creating the socket");
    exit(1); /* just leave if wrong number entered */
  }

  /* now fill in the address data structure we use to sendto the server */
  for (i=0;i<strlen(argv[1]); i++){
    if (!isdigit(argv[1][i]))
      {
	printf ("Error: the port number must be a numerical integer\n");
	exit(1);
      }
  }
//------------------------------------------------------------------------
// make ip address
    
    
  portNumber = strtol(argv[1], NULL, 10); /* many ways to do this */

  if ((portNumber > 65535) || (portNumber < 0)){
    printf ("Error: you entered an invalid port number out of the range of 0-65535\n");
    exit (1);
  }

  fromLength = sizeof(struct sockaddr_in);

  server_address.sin_family = AF_INET; /* use AF_INET addresses */
  server_address.sin_port = htons(portNumber); /* convert port number */
  server_address.sin_addr.s_addr = INADDR_ANY; /* any adapter */
  
//------------------------------------------------------------------------
  /* the next step is to bind to the address */
  rc = bind (sd, (struct sockaddr *)&server_address,
	     sizeof(struct sockaddr ));
  
  if (rc < 0){
    perror("Error binding to the socket");
    exit (1);
  }

//------------------------------------------------------------------------


    
  while(1){ 
    memset (bufferReceived, 0, 1000); // zero out the buffers in C
  
  
	FD_ZERO(&socketFDS);// NEW                                 
    FD_SET(sd, &socketFDS); //NEW - sets the bit for the initial sd socket
    FD_SET(STDIN, &socketFDS); // NEW tell it you will look at STDIN too
    if (STDIN > sd) // figure out what the max sd is. biggest number
      maxSD = STDIN;
    else
      maxSD = sd;
    rc = select (maxSD+1, &socketFDS, NULL, NULL, NULL); // NEW block until something arrives
    printf ("\n\nselect popped\n");
  
  //------------------------------------------------------------------------------------------------------------------
  
     if (FD_ISSET(STDIN, &socketFDS)){ // means i received something from the keyboard. 
      char *ptr = NULL;
      memset (bufferReceived, '\0', 100);
      ptr = fgets(bufferReceived, sizeof(bufferReceived), stdin);
      bufferReceived [strlen(bufferReceived)-1] = 0; // get rid of \n that is there, cuz i don't want it
      printf ("read from the keyboard '%s'\n", bufferReceived);
    }
  
  
  //------------------------------------------------------------------------------------------------------------------
  
      if (FD_ISSET(sd, &socketFDS)){   // if we get something from the network


      rc = recvfrom(sd, bufferReceived, sizeof(bufferReceived), flags,
(struct sockaddr *)&from_address, &fromLength);
      printf ("I received %d bytes from the network\n",rc);
	  
	  
	  char *version_string = "version:3";	
	  
if (strstr(bufferReceived, argv[1]) && strstr(bufferReceived, version_string)) {  // only print the string if version3 and port number is included in message

    
  char *ptr;  // creat pointer to received message so we can parse it properly
  ptr = strtok(bufferReceived, " ");
  
	printf("--------------------------------------------------\n");
    printf("name:value\n");      
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    // this is where we tokenize and print the string
  while (ptr !=NULL){
    

    int len = strcspn(ptr, "\"");
                      
    if (ptr[len] == '\"'){
        char quote[1000];
        strcpy(quote, ptr);
        ptr = strtok(NULL, " ");
        
        while (ptr != NULL && ptr[strcspn(ptr, "\"")] != '\"'){
            strcat(quote, " ");
            strcat(quote, ptr);
            ptr = strtok(NULL, " ");
        }
        if (ptr != NULL) {
            strcat(quote, " ");
            strcat(quote, ptr);
        printf ("'%s'\n",quote);

        }
    }
      
  else {

       printf ("'%s'\n",ptr);

    }
        ptr = strtok(NULL, " ");


    }
			printf("--------------------------------------------------\n");

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

}
      else{     // if port number is not in message, print this
        printf("--------------------------------------------------\n");
          printf("Recieved a message not destined for me!\n");
        printf("--------------------------------------------------\n");

      }
	  
	  
	  
	  
    } // end of network input
  
  

	  
  } // end of program while loop    

	return 0;    

} // end of main()

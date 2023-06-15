// in this client program I initially open the config file to display its contents then i close it
// then i start a forever loop, and ask the user to input a message
// once the user inputs a message we enter the while loop, which gets lines from the config file 
// and opens a socket for each server in the config file and sends each server the message
// and then the while loop ends and we are back to the top of the forever loop
// you can end the forever loop as well as the program if you enter the message STOP

#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>


#define CONFIG_FILE "config.file"
#define MAX_LENGTH 200
#define BUF_SIZE 1024




int main(int argc, char *argv[])
{

  int sd; /* the socket descriptor */
  struct sockaddr_in server_address;  /* structures for addresses */
  struct sockaddr_in inaddr;  /* structures for checking addresses */
  int rc;
  char *lineFromFile = NULL;
  size_t lengthRead = 0;
  char serverIP[20]; 
  int portNumber, location = 0; 
  
 

    
//------------------------------------------------------------------------
// print out the servers and port numbers in config file for display

    FILE *config_file = fopen(CONFIG_FILE, "r");   // if config file is specified as parameter, open it
    if (config_file == NULL) {
        perror("Error opening config file");
        exit(EXIT_FAILURE);
    }
  
    while (fscanf(config_file, "%s %d %d", serverIP, &portNumber, &location) == 3){
				printf("IPaddresses '%s', port '%d', location '%d'\n", serverIP, portNumber, location );
	}
		
	        fclose(config_file);    // close the config file
	
	
	
	
	
	

	for(;;) {
		
		
	//----------------------------------------------------------------------------------
		// prepare message to send to all servers in config file
		char buf[BUF_SIZE];
		memset (buf, '\0', 100);
		printf("\nEnter a message: ");
		fgets(buf, BUF_SIZE, stdin);
		size_t len = strlen(buf);
		
		if(len > 0 && buf[len-1] == '\n'){
			buf[len-1] = '\0';
		}
		printf("\n");

		    if (!strcmp(buf, "STOP")){
      printf ("you asked me to end, so i will end\n");
      exit (1);
    }
	//----------------------------------------------------------------------------------
	// send message to all servers in config file 
	
	
	
	    int numServers = 0;
		
    fopen(CONFIG_FILE, "r");

    while (fscanf(config_file, "%s %d %d", serverIP, &portNumber, &location) == 3){   // starting with the first line of the config file 
        numServers++;   // these will incrmenet each line of the config file
        
        sd = socket(AF_INET, SOCK_DGRAM, 0); /* create a socket */
        if (sd == -1){
            printf("Error creating socket\n");
            exit(1);
        }
        
		// set the destination and port address
        memset(&server_address, 0, sizeof(server_address));
        server_address.sin_family = AF_INET; /* use AF_INET addresses */
        server_address.sin_port = htons(portNumber); /* convert port number */
        server_address.sin_addr.s_addr = inet_addr(serverIP); /* convert IP addr */
        



		 printf("Sending to location: %d, on port: %d, message: '%s'\n", location, portNumber, buf);         //print what we are sending to server
         sendto(sd, buf, strlen(buf), 0, (struct sockaddr *) &server_address, sizeof(server_address)); // send it


         close(sd);      // close the sockets
    }
            fclose(config_file);    // close the config file

	}
    return 0;
}

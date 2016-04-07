/*
 *  bmpServer.c
 *  1917 serve that 3x3 bmp from lab3 Image activity
 *
 *  Created by Tim Lambert on 02/04/12.
 *  Containing code created by Richard Buckland on 28/01/11.
 *  Copyright 2012 Licensed under Creative Commons SA-BY-NC 3.0. 
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

int waitForConnection (int serverSocket);
int makeServerSocket (int portno);
int stepCounter(double real_part,double imaginary_part);
void mandelbrot(unsigned char *array);
void serveBMP (int socket);
void serveHTML(int socket);

#define SIMPLE_SERVER_VERSION 1.0
#define REQUEST_BUFFER_SIZE 1000
#define DEFAULT_PORT 1917
#define NUMBER_OF_PAGES_TO_SERVE 10
#define MAX_ITERATION 255
// after serving this many pages the server will halt

int main (int argc, char *argv[]) {
      
   printf ("************************************\n");
   printf ("Starting simple server %f\n", SIMPLE_SERVER_VERSION);
   printf ("Serving bmps since 2012\n");   
   
   int serverSocket = makeServerSocket (DEFAULT_PORT);   
   printf ("Access this server at http://localhost:%d/\n", DEFAULT_PORT);
   printf ("************************************\n");
   
   char request[REQUEST_BUFFER_SIZE];
   
   int numberServed = 0;
   while (numberServed < NUMBER_OF_PAGES_TO_SERVE) {
      
      printf ("*** So far served %d pages ***\n", numberServed);
      
      int connectionSocket = waitForConnection (serverSocket);
      // wait for a request to be sent from a web browser, open a new
      // connection for this conversation
      
      // read the first line of the request sent by the browser  
      int bytesRead;
      bytesRead = read (connectionSocket, request, (sizeof request)-1);
      assert (bytesRead >= 0); 
      // were we able to read any data from the connection?
            
      // print entire request to the console 
      printf (" *** Received http request ***\n %s\n", request);
      
      //send the browser a simple html page using http
      printf (" *** Sending http response ***\n");
      serveHTML(connectionSocket);
      serveBMP(connectionSocket);
      // close the connection after sending the page- keep aust beautiful
      close(connectionSocket);
      
      numberServed++;
   } 
   
   // close the server connection after we are done- keep aust beautiful
   printf ("** shutting down the server **\n");
   close (serverSocket);
   
   return EXIT_SUCCESS; 
}

void serveHTML(int socket) {
    const char* message =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "\r\n"
        "<!DOCTYPE html>\n"
        "<script src=\"http://almondbread.cse.unsw.edu.au/tileviewer.js\"></script>\n";

    // echo the http response to the console for debugging purposes
    printf ("VVVV about to send this via http VVVV\n");
    printf ("%s\n", message);
    printf ("^^^^ end of message ^^^^\n");

    // send the http response to the web browser which requested it
    send (socket, message, strlen(message), 0);
}


void serveBMP (int socket) {
   char* message;
   
   // first send the http response header
   
   // (if you write stings one after another like this on separate
   // lines the c compiler kindly joins them togther for you into
   // one long string)
   message = "HTTP/1.0 200 OK\r\n"
              "Content-Type: image/bmp\r\n"
              "\r\n";

   printf ("about to send=> %s\n", message);
   write (socket, message, strlen (message));

   // now send the BMP
   
	 
	 unsigned char bmp[512*512*3+54] = {
     0x42,0x4d,0x36,0x00,0x0c,0x00,0x00,0x00,
     0x00,0x00,0x36,0x00,0x00,0x00,0x28,0x00,
     0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x02,
     0x00,0x00,0x01,0x00,0x18,0x00,0x00,0x00,
     0x00,0x00,0x24,0x00,0x00,0x00,0x13,0x0b,
     0x00,0x00,0x13,0x0b,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x07,
     0xff,0x07,0x07,0x07,0x07,0x07,0xff,0x00,
     0x00,0x0e,0x07,0x07,0x07,0x66,0x07,0x07,
     0x07,0x07,0x07,0x00,0x00,0x0d,0x07,0x07,
     0x07,0x07,0x07,0x07,0xff,0xff,0xff,0x00,
     0x00,0x0d};
     
	   mandelbrot (bmp);
	 
	 
     write (socket, bmp, sizeof(bmp));
     
     
}


void mandelbrot (unsigned char *array) {
	double x=-2;
	double y=-2;
	int col;
	int row;
	int i;
	row = 0;
	i = 0;
	
	while(row < 512) {
		x=-2;
		col = 0;
		while(col<512){
			if(stepCounter(x,y) >= MAX_ITERATION){
				array[54 + i*3] = 0;
				array[54 + i*3 +1] = 0;
				array [54 + i*3 + 2] = 0;
			
			} else { 
				array[54 + i*3] = 0;
				array[54 + i*3 +1] = stepCounter(x,y);
				array[54 + i*3 + 2] = stepCounter(x,y);
			
			} 
			x+=(4.0/512);
			col++;
			i++;
		}
		printf("\n");
		y+=(4.0/512);
		row++;

	}


}

int stepCounter(double real_part,double imaginary_part){  
    double x0 = real_part;
    double y0 = imaginary_part;
    double x = 0;
    double y = 0;
    double xtemp, ytemp;
    int iteration = 0;
    while (  ((x*x + y*y) < (2*2))  &&  (iteration < MAX_ITERATION) ) {
        xtemp = x*x - y*y + x0;
        ytemp = 2*x*y + y0;
        if (x == xtemp  &&  y == ytemp) {
          iteration = MAX_ITERATION;
        }
        x = xtemp;
        y = ytemp;
        iteration++;
      }

    return iteration;
}

// start the server listening on the specified port number
int makeServerSocket (int portNumber) { 
   
   // create socket
   int serverSocket = socket (AF_INET, SOCK_STREAM, 0);
   assert (serverSocket >= 0);   
   // error opening socket
   
   // bind socket to listening port
   struct sockaddr_in serverAddress;
   bzero ((char *) &serverAddress, sizeof (serverAddress));
   
   serverAddress.sin_family      = AF_INET;
   serverAddress.sin_addr.s_addr = INADDR_ANY;
   serverAddress.sin_port        = htons (portNumber);
   
   // let the server start immediately after a previous shutdown
   int optionValue = 1;
   setsockopt (
      serverSocket,
      SOL_SOCKET,
      SO_REUSEADDR,
      &optionValue, 
      sizeof(int)
   );

   int bindSuccess = 
      bind (
         serverSocket, 
         (struct sockaddr *) &serverAddress,
         sizeof (serverAddress)
      );
   
   assert (bindSuccess >= 0);
   // if this assert fails wait a short while to let the operating 
   // system clear the port before trying again
   
   return serverSocket;
}

// wait for a browser to request a connection,
// returns the socket on which the conversation will take place
int waitForConnection (int serverSocket) {
   // listen for a connection
   const int serverMaxBacklog = 10;
   listen (serverSocket, serverMaxBacklog);
   
   // accept the connection
   struct sockaddr_in clientAddress;
   socklen_t clientLen = sizeof (clientAddress);
   int connectionSocket = 
      accept (
         serverSocket, 
         (struct sockaddr *) &clientAddress, 
         &clientLen
      );
   
   assert (connectionSocket >= 0);
   // error on accept
   
   return (connectionSocket);
}

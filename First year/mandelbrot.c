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
#include <math.h>

#include "pixelColor.h"
#include "mandelbrot.h"

typedef struct _triord{
   double x; 
   double y;
   int z;
   }triord;
   
int waitForConnection (int serverSocket);
int makeServerSocket (int portno);
//int escapeSteps(double real_part,double imaginary_part);
void mandelbrot (unsigned char *array, triord pos);
void serveBMP (int socket, triord position);
void serveHTML(int socket, triord position);

#define SIMPLE_SERVER_VERSION 1.0
#define REQUEST_BUFFER_SIZE 1000
#define DEFAULT_PORT 1917
#define NUMBER_OF_PAGES_TO_SERVE 1000
#define MAX_ITERATION 255
#define SIZE 512
#define BYTES_PER_PIXEL 3
#define HEADER_BYTES 54
#define TRUE 1
// after serving this many pages the server will halt

int main (int argc, char *argv[]) {
       
       int arguments;
       triord position;
       
       printf ("************************************\n");
       printf ("Starting simple server %f\n", SIMPLE_SERVER_VERSION);
       printf ("Serving bmps since 2012\n");   
       
       int serverSocket = makeServerSocket (DEFAULT_PORT);   
       printf ("Access this server at http://localhost:%d/\n", DEFAULT_PORT);
       printf ("************************************\n");
       
       char request[REQUEST_BUFFER_SIZE];
       
       int numberServed = 0;
       while (TRUE) {
          
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
          
          
          arguments = 
          sscanf(request, "GET /tile_x%lf_y%lf_z%d.bmp", &position.x, &position.y, &position.z);
          
          if(arguments == 3 ){
          serveBMP(connectionSocket, position);
          } else{
          serveHTML(connectionSocket, position);
          }
                    
          // close the connection after sending the page- keep aust beautiful
          close(connectionSocket);
          
          numberServed++;
       } 
       
       // close the server connection after we are done- keep aust beautiful
       printf ("** shutting down the server **\n");
       close (serverSocket);
       
       return EXIT_SUCCESS; 
    }
    
void serveHTML (int socket, triord position){
     char * message;
     message =
               "HTTP/1.0 200 OK\n"
               "Content-Type: text/html\n"
               "\n";

     printf ("about to send=> %s\n", message);
     write (socket, message, strlen (message));
     
     message =
               "<!DOCTYPE html>\n"
               "<script src=\"http://almondbread.cse.unsw.edu.au/tiles.js\"></script>"
               "\n"; 
                    
     write (socket, message, strlen (message));
    
    }
    
void serveBMP (int socket, triord position) {
     char* message;
     
     // first send the http response header
     
     // (if you write stings one after another like this on separate
     // lines the c compiler kindly joins them togther for you into
     // one long string)

      message =
                "HTTP/1.0 200 OK\n"
                "Content-Type: image/bmp\n"
                "\n";

      printf ("about to send=> %s\n", message);
      write (socket, message, strlen (message));
   

        // now send the BMP
     
       
       unsigned char bmp[SIZE*SIZE*BYTES_PER_PIXEL+HEADER_BYTES] = {
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
       
      mandelbrot (bmp, position);
       
       
      write (socket, bmp, sizeof(bmp));
       
         
    }

    



void mandelbrot (unsigned char *array, triord pos) {
        
      int col;
      int row=0;
      int i=0;
      
      double zlevel = pow(2,-(pos.z));
      double x;
      double y=-(SIZE*zlevel)/2  +pos.y;
      
      while(row < SIZE) {
          x=-(SIZE*zlevel)/2+pos.x;
          col = 0;
          while(col<SIZE){
              int steps = escapeSteps(x,y);
              array[HEADER_BYTES + i*BYTES_PER_PIXEL] = stepsToBlue(steps);
              array[HEADER_BYTES + i*BYTES_PER_PIXEL +1] = stepsToGreen(steps);
              array[HEADER_BYTES + i*BYTES_PER_PIXEL + 2] = stepsToRed(steps);
              
              x+=zlevel;
              col++;
              i++;
          }
          printf("\n");
          y+=zlevel;
          row++;

      }


    }
    

int escapeSteps(double real_part,double imaginary_part){  
      double x0 = real_part;
      double y0 = imaginary_part;
      double x = 0;
      double y = 0;
      double xtemp=0; 
      double ytemp=0;
      int iteration = 0;
      while ( ((x*x + y*y) < (2*2))  && 
              (iteration <= MAX_ITERATION) ) {
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

Lab 3
------

In this lab I start off with me server2.c and client2.c from last lab
I started by impplementing the select function in the server file
I then spent some time implementing the necessary parameters like "version:3" and location, as well as the output format

And then I finally combined both programs to run as a single executable file, that can send and receive messages to itself


To run this program run ./drone3 <portNumber>
in your terminal
the port number you enter will be the port of the location you are sending messages out of, so your location will be the port you enter
  
and then you can run ./drone3 <portNumber>
again from a different terminal with a different port number
and within either terminal you can choose to send messages to eachother, or any other server within the config file, or even send messages to yourself by reading from the keyboard via select function

  
  
Problems Ive encountered   
-------------------------
- if you send a message that is only one word long it will not display, but if it is more than one word long it displays properly
  for example: 'msg:"Hello"' will not display any of the message, but 'msg:"Hello World!"' works properly

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "command.h"




int main(int argc, char** argv)
{
  int* command_type;
  if(argc == 1){
    printf("Should Have the extral command\n");
    printf("Usage: ./Ramdom_forest ");
    printf("[<-data> <-output> <-tree> <-thread>]\n");
    exit(0);
  }
 //write the command wrong or not
 command_type = parser_command(argc,argv);

 /******************************************************/
 /********************train Part************************/ 
 /******************************************************/

 Read_train_Data(0); 
 start_training();
 
 /******************************************************/
 /********************test Part*************************/ 
 /******************************************************/
 
 //report the current path situation
 if(command_type[0] == 1){
   char buf[50];
   getcwd(buf,sizeof(buf));
   printf("The Current test Data and Train Data path ");
   printf("%s\n",buf);
 }

 //output the data
 if(command_type[1] == 1){
   Read_train_Data(1);
   start_testing();
 
 }

 //report the number of the tree number 
 if(command_type[2] == 1){
   printf("Total Tree number: ");
   printf("%d\n",OneThreadTree*4);
 }

 //report the number of the thread 
 if(command_type[3] == 1){
   printf("Total Thread number: ");
   printf("%d\n",4);
 }

  pthread_exit(NULL);
}
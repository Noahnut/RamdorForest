#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#define Pick_number 3000
#define OneThreadTree 100
#define Dimension_number 34
#define Total_DataNumber 25150
#define Total_TestingNumber 25007
#define Total_TreeNumber 800
#define factor_number 2



//enum the command state in the command array
enum
{
  data   = 0,
  output = 1,
  tree   = 2,
  thread = 3
};

struct Tree_Node 
{
  int left;
  int right;
  int dimension;
  float threhold;
  float result;
};

struct Tree
{
  struct Tree_Node Tree_node[Total_DataNumber];
  int node_number;
};
//

struct Tree Forest[Total_TreeNumber];


static int* command_type;
static float train_Data[Total_DataNumber][Dimension_number];
static float testing_Data[Total_TestingNumber][Dimension_number-1];
static char* training_filename = "training_data";
static char* testing_filename  = "testing_data";
static int dim;
static int tree_number = 0;


void Read_train_Data(int check_number); //read the train data in the 2 dimensional array
void start_training(void);
void start_testing(void);
void build(int L , int R , int n, float Data[][34]);   
void* Decision_threadOne(void* arg);   //make the first thread 
void* Decision_threadTwo(void* arg);   //make the two thread 
void* Decision_threadThree(void* arg); //make the three thread 
void* Decision_threadFour(void* arg); 
void* Decision_threadFive(void* arg);
void* Decision_threadSix(void* arg);
void* Decision_threadSeven(void* arg);
void* Decision_threadeight(void* arg);   //make the four thread
float make_DecisionTree(float Data[][34],char* s);  
int* parser_command(int argc, char** argv);  //read the command from the shell and remember it situation in the buff
int Tree_search(int node, int treenumber, int data);


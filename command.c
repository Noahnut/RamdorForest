#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include "command.h"

//read the data to the 2 dimensional array
void
Read_train_Data(int check_number)
{
  char buff[100];
  int dimension,datanumber = 0;
  int skip_check = 0;
  char ch;
  FILE* file;
  if(check_number == 0){
    file = fopen(training_filename, "r");
  }
  else if(check_number == 1){
    file = fopen(testing_filename, "r");
  }
  else{
    return;
  }
  
  //check number 1 is read the testing_file

//  else{return;}
  if(file == NULL){
    printf("Read Data error\n");
  }
  int i = 0;
  memset(buff, 0, sizeof(buff));
  while((ch = fgetc(file)) != EOF){
     buff[i] = ch;
      i++;
    if(skip_check == 0){
      if(ch == ' '){
        skip_check = 1;
        memset(buff, 0, sizeof(buff));
        i = 0;
      }
    }
    else if(ch == ' ' && skip_check == 1){
      buff[i] = '\0';
      if(check_number == 0){
        train_Data[datanumber][dimension] = atof(buff);
      }
      else if(check_number == 1){
        testing_Data[datanumber][dimension] = atof(buff);
      }
      i = 0;
      ++dimension;
      memset(buff, 0, sizeof(buff));
    }
    else if(ch == '\n' && skip_check == 1){
      buff[i] = '\0';
      if(check_number == 0){
        train_Data[datanumber][dimension] = atof(buff);
      }
      else if(check_number == 1){
        testing_Data[datanumber][dimension] = atof(buff);
      }
      //train_Data[datanumber][dimension] = atof(buff);
      i = 0;
      datanumber++;
      dimension = 0;
      skip_check = 0;
      memset(buff, 0, sizeof(buff));
    }
  } 
}


void 
start_training(void)
{
  //create the four thread to do the 25 tree per thread 


  //malloc four strcut array to store the 
  int error_message;
  pthread_t treeOne, treeTwo, treeThree, treeFour, treeFive, treeSix, treeSeven, treeEight;
  void *tret;
  printf("Start training\n");
  error_message = pthread_create(&treeOne, NULL, Decision_threadOne, NULL);
  pthread_join(treeOne, &tret);
 // printf("thread One exit code %s\n",(char *)tret);
  if(error_message != 0){
    perror("pthread");
  }
  error_message = pthread_create(&treeTwo, NULL, Decision_threadTwo, NULL);
  pthread_join(treeTwo, &tret);
 // printf("thread Two exit code %s\n",(char *)tret);
  if(error_message != 0){
    perror("pthread");
  }
  error_message = pthread_create(&treeThree, NULL, Decision_threadThree, NULL);
  pthread_join(treeThree, &tret);
 // printf("thread Three exit code %s\n",(char *)tret);
  if(error_message != 0){
    perror("pthread");
  }
  error_message = pthread_create(&treeFour, NULL, Decision_threadFour, NULL);
  pthread_join(treeFour, &tret);
 // printf("thread Four exit code %s\n",(char *)tret);
  if(error_message != 0){
    perror("pthread");
  }
  error_message = pthread_create(&treeFive, NULL, Decision_threadFive, NULL);
  pthread_join(treeFive, &tret);
 // printf("thread Four exit code %s\n",(char *)tret);
  if(error_message != 0){
    perror("pthread");
  }
  error_message = pthread_create(&treeSix, NULL, Decision_threadSix, NULL);
  pthread_join(treeSix, &tret);
 // printf("thread Four exit code %s\n",(char *)tret);
  if(error_message != 0){
    perror("pthread");
  }
  error_message = pthread_create(&treeSeven, NULL, Decision_threadSeven, NULL);
  pthread_join(treeSix, &tret);
 // printf("thread Four exit code %s\n",(char *)tret);
  if(error_message != 0){
    perror("pthread");
  }
  error_message = pthread_create(&treeEight, NULL, Decision_threadeight, NULL);
  pthread_join(treeSix, &tret);
 // printf("thread Four exit code %s\n",(char *)tret);
  if(error_message != 0){
    perror("pthread");
  }

}

float
make_DecisionTree(float Data[][34], char* s)
{
   
  //if have the same in the data should to be delete 
  //make sure the data in the tree all is different
  if(tree_number > Total_TreeNumber-1){
    return;
  } 
  Forest[tree_number].node_number = 0;
  build(0, Pick_number-1, 0, Data);
  tree_number++;
  //printf("%d ",tree_number);
}

void 
build(int L, int R,int n, float Data[][34])
{
  int left;
  int right;
  int number = tree_number;
  float temp;
  float total[factor_number] = {};
  for(int i = L;i <= R;i++){
    total[(int)Data[i][Dimension_number-1]]++; 
  } 
  int sum = R - L + 1;
  for(int i = 0; i < factor_number; i++){
    if(total[i] == sum){
      Forest[number].Tree_node[n].dimension = 0;
      Forest[number].Tree_node[n].left = 0;
      Forest[number].Tree_node[n].right = 0;
      Forest[number].Tree_node[n].threhold = 0;
      Forest[number].Tree_node[n].result = i;
   //   printf("resutlt: %.2f ",Forest[number].Tree_node[n].result);
   //   printf("%d node result:%.2f number:%.2f\n",n,tree_node[n].result, i);      
      return;
    }
  }
  double min = 1e9;
  int M;
  int dim,dimen;
  int l = 0;
  float threhold;
  for(int i = 1; i < Dimension_number-1; ++i){
    dim = i;
    //sort part
    for(int k = L; k < R; k++){
      temp = Data[k][i];
      if(k == 0){l = 0;}
      else{l = k - 1;}
      while(temp < Data[l][i]){
        Data[l+1][i] = Data[l][i];
        l--;
        if(l == -1){break;}
      } 
      Data[l+1][i] = temp; 
    }
    
    //end the sort 
    //start make the tree
    float count[factor_number] = {};
    int numL = 0;
    for(int j = L; j < R; ++j){
       count[(int)Data[j][Dimension_number-1]]++;
       numL++;
       if(Data[j][i] == Data[j+1][i]){ continue ;}
       int numR = sum - numL;
       int ginL = numL * numL;
       for(int c = 0; c < factor_number; ++c){
         ginL -= count[c] * count[c];
       }
       int ginR = numR * numR;
       for(int c = 0; c < factor_number; ++c){
         ginR -= (total[c] - count[c]) * (total[c] - count[c]);
       }
       double gini = (double)ginL / numL + (double)ginR / numR;

       if(gini < min){
         min = gini;
         dimen = i;
         M = j;
         threhold = (Data[j][i] + Data[j+1][i]);
      //   printf("gini: %.2f ",gini);
      //   printf("threhold %.2f ",threhold); 
       }
      
     }
   }
   if(min == 1e9){
     Forest[number].Tree_node[n].result = 1e9;
     return;
   }
   left = ++Forest[number].node_number;
   right = ++Forest[number].node_number;
   Forest[number].Tree_node[n].left = left;
   Forest[number].Tree_node[n].right = right;
   Forest[number].Tree_node[n].threhold = threhold;
   Forest[number].Tree_node[n].dimension = dimen;
   Forest[number].Tree_node[n].result = -1;
  
   build(L, M ,left, Data);
   build(M+1, R, right, Data);

}


//must have another method to get the buff
void*
Decision_threadOne(void* arg)
{
  float databuff[Pick_number][Dimension_number];
  unsigned seed;
  int ramdom_number;
  seed = (unsigned)time(NULL);
  srand(seed);
  for(int i = 1; i < OneThreadTree ; i++){
    //pick the ramdom data to the databuff
    for(int j = 0; j < Pick_number; j++){
      ramdom_number = rand()%25150;
      for(int k = 0; k < 34 ; k++){
        databuff[j][k] = train_Data[ramdom_number][k];
      }
   }
    make_DecisionTree(databuff, "One");  
  }
  pthread_exit((void*) 0);
}

void* 
Decision_threadTwo(void* arg)
{
  float databuff[Pick_number][Dimension_number];
  unsigned seed;
  int ramdom_number;
  seed = (unsigned)time(NULL);
  srand(seed);
  for(int i = 1; i < OneThreadTree ; i++){
    //pick the ramdom data to the databuff
    for(int j = 0; j < Pick_number; j++){
      ramdom_number = rand()%25150;
      for(int k = 0; k < 34 ; k++){
        databuff[j][k] = train_Data[ramdom_number][k];
      }
   }
    make_DecisionTree(databuff, "Two");  
  }
  pthread_exit((void*) 0);
}

void* 
Decision_threadThree(void* arg)
{
  float databuff[Pick_number][Dimension_number];
  unsigned seed;
  int ramdom_number;
  seed = (unsigned)time(NULL);
  srand(seed);
  for(int i = 1; i < OneThreadTree ; i++){
    //pick the ramdom data to the databuff
    for(int j = 0; j < Pick_number; j++){
      ramdom_number = rand()%25150;
      for(int k = 0; k < 34 ; k++){
        databuff[j][k] = train_Data[ramdom_number][k];
      }
   }
    make_DecisionTree(databuff, "Three");  
  }
  pthread_exit((void*) 0);
}

void*
Decision_threadFour(void* arg)
{
  float databuff[Pick_number][Dimension_number];
  unsigned seed;
  int ramdom_number;
  seed = (unsigned)time(NULL);
  srand(seed);
  for(int i = 1; i < OneThreadTree ; i++){
    //pick the ramdom data to the databuff
    for(int j = 0; j < Pick_number; j++){
      ramdom_number = rand()%25150;
      for(int k = 0; k < 34 ; k++){
        databuff[j][k] = train_Data[ramdom_number][k];
      }
   }
    make_DecisionTree(databuff, "Four");  
  }
  pthread_exit((void*) 0);
}


void*
Decision_threadFive(void* arg)
{
  float databuff[Pick_number][Dimension_number];
  unsigned seed;
  int ramdom_number;
  seed = (unsigned)time(NULL);
  srand(seed);
  for(int i = 1; i < OneThreadTree ; i++){
    //pick the ramdom data to the databuff
    for(int j = 0; j < Pick_number; j++){
      ramdom_number = rand()%25150;
      for(int k = 0; k < 34 ; k++){
        databuff[j][k] = train_Data[ramdom_number][k];
      }
   }
    make_DecisionTree(databuff, "Four");  
  }
  pthread_exit((void*) 0);
}

void*
Decision_threadSix(void* arg)
{
  float databuff[Pick_number][Dimension_number];
  unsigned seed;
  int ramdom_number;
  seed = (unsigned)time(NULL);
  srand(seed);
  for(int i = 1; i < OneThreadTree ; i++){
    //pick the ramdom data to the databuff
    for(int j = 0; j < Pick_number; j++){
      ramdom_number = rand()%25150;
      for(int k = 0; k < 34 ; k++){
        databuff[j][k] = train_Data[ramdom_number][k];
      }
   }
    make_DecisionTree(databuff, "Four");  
  }
  pthread_exit((void*) 0);
}

void*
Decision_threadSeven(void* arg)
{
  float databuff[Pick_number][Dimension_number];
  unsigned seed;
  int ramdom_number;
  seed = (unsigned)time(NULL);
  srand(seed);
  for(int i = 1; i < OneThreadTree ; i++){
    //pick the ramdom data to the databuff
    for(int j = 0; j < Pick_number; j++){
      ramdom_number = rand()%25150;
      for(int k = 0; k < 34 ; k++){
        databuff[j][k] = train_Data[ramdom_number][k];
      }
   }
    make_DecisionTree(databuff, "Four");  
  }
  pthread_exit((void*) 0);
}

void*
Decision_threadeight(void* arg)
{
  float databuff[Pick_number][Dimension_number];
  unsigned seed;
  int ramdom_number;
  seed = (unsigned)time(NULL);
  srand(seed);
  for(int i = 1; i < OneThreadTree ; i++){
    //pick the ramdom data to the databuff
    for(int j = 0; j < Pick_number; j++){
      ramdom_number = rand()%25150;
      for(int k = 0; k < 34 ; k++){
        databuff[j][k] = train_Data[ramdom_number][k];
      }
   }
    make_DecisionTree(databuff, "Four");  
  }
  pthread_exit((void*) 0);
}


void 
start_testing(void)
{
   FILE* file;
   file = fopen("submission.csv","w");
   for(int j = 0; j < Total_TestingNumber; j++){
     int final_count = 0;
     int count1 = 0;
     int count0 = 0;
    for(int i = 1 ; i < Total_TreeNumber; i++){
      int count = Tree_search(0,i,j);
      if(count == 1){ ++count1;}  
      else if(count == 0){++count0;}    
     }
     if(count1 < count0){final_count = 1;}
     else if(count1 > count1){final_count = 0;}
     fprintf(file,"%d,%d\n",j+1,(int)final_count);
   }

}


//use the recursive to search the tree node 
//return the count is the search finally result 
int
Tree_search(int node, int Treenumber,int data)
{
  int dim = Forest[Treenumber].Tree_node[node].dimension;
  if(Forest[Treenumber].Tree_node[node].result == 1 || Forest[Treenumber].Tree_node[node].result == 0 || Forest[Treenumber].Tree_node[node].result == 1e9)
  {
    if(Forest[Treenumber].Tree_node[node].result == 1e9){
      return -1;
    }
    int count = Forest[Treenumber].Tree_node[node].result;
    return count;
  }
  if(testing_Data[data][dim] < Forest[Treenumber].Tree_node[node].threhold){
    Tree_search(Forest[Treenumber].Tree_node[node].left, Treenumber, data);
  } 
  else if(testing_Data[data][dim] > Forest[Treenumber].Tree_node[node].threhold){
    Tree_search(Forest[Treenumber].Tree_node[node].right, Treenumber, data);
  }
}


//use the array to recode which command should be execult 
int*
parser_command(int argc, char** argv)
{
  static int command_situation[4];
  memset(command_situation, '\0', sizeof(command_situation));
  
  for(int i = 1;i<argc;i++){
    //printf("%d\n",argc);
    //printf("%s\n",argv[i]);
    if(strcmp("-data",argv[i]) == 0){
      command_situation[data] = 1;
    }
    else if(strcmp("-output",argv[i]) == 0){ 
      command_situation[output] = 1;
    }
    else if(strcmp("-tree",argv[i]) == 0){
      command_situation[tree]  = 1;
    }
    else if(strcmp("-thread",argv[i]) == 0){
      command_situation[thread] = 1;
    }
    else{
      printf("Command Error\n");
      printf("Usage: ./Ramdom_forest ");
      printf("[<-data> <-output> <-tree> <-thread>]\n");
      exit(EXIT_FAILURE);
    }
  }
  return command_situation;
}






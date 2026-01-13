// HEADER FILE
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>   // For the purpose of using rand function // For counting time in questions

// GENERATING RANDOM QUESTION NUMBERS
void selectquestion(int e,int m,int h,int et,int mt,int *qnum){

    int count = 0;
    int index = 0;
    int temp = 0;
    bool check = true;
    
    // RANDOM EASY QUESTION NUMBERS

        while(count<e){
           // rand() generates random number between 0 to compiler decided macro RAND_MAX
           // for the generated number to be in the range required we do modulo
           // now the generated queston numbers are in the range [1,no of easy ques]
           temp = rand()%(et) + 1;
           check = true;
           for(int i = 0;i<index;i++){
                if(qnum[i] == temp){
                    check = false;
                } 
            }
           if(check){
               qnum[index] = temp;
               index++;
               count++;
           }
        }
    
    // RANDOM MEDIUM QUESTION NUMBERS
        count = 0;
        temp=0;
        check = true;
        while(count<m){
            // rand() generates random number between 0 to compiler decided macro RAND_MAX
            // for the generated number to be in the range required we do modulo 
            // now the generated question numbers are in the range [no of easy ques+1,no of easy ques + number of medium ques] 
            temp = rand()%(et) + et + 1;
            check = true;
            for(int i = 0;i<index;i++){
                 if(qnum[i] == temp){
                    check = false;
                 } 
            }
            if(check){
                qnum[index] = temp;
                index++;
                count++;
            }
       }

    //RANDOM HARD QUESTION NUMBERS
        count = 0;
        temp = 0;
        check = true;
        while(count<h){
           // rand() generates random number between 0 to compiler decided macro RAND_MAX
           // for the generated number to be in the range required we do modulo
           // now the generated question numbers are in the range [no of easy and med ques + 1,no of easy and med ques + number of hard ques]
           temp = rand()%(et) + et + mt + 1;
           check = true;
            for(int i = 0;i<index;i++){
               if(qnum[i] == temp){
                 check = false;
                } 
            }
            if(check){
               qnum[index] = temp;
               index++;
               count++;
            }
        }

        // Sorting the randomly generated question numbers 
        // Sorting is done to ensure easy traversal through file
        // Sorting is also done to ensure the order of easy, medium and hard question display
           
          for(int i=0;i<(e+m+h);i++){
             for(int j=i+1;j<(e+m+h);j++){
                if(qnum[j]<qnum[i]){
                   int temp = qnum[i];
                   qnum[i] = qnum[j];
                   qnum[j] = temp;
                }
              }
          }
}


// DISPLAYING QUESION AND OPTIONS AND EVALUATING THE FINAL MARKS BASED ON USER ANSWER 
int displayingselectedquesandevaluatingmarks(int* quesarr,int* timeperques,int *finalverdict,int noofques,int* correasy,int* corrmed,int* corrhard){
   FILE *fp2; // TO OPEN THE FILE TO READ AND DISPLAY THE QUESTION
   fp2 = fopen("C:\\Users\\vapk1\\Desktop\\CODING\\VS CODE FILES\\PROJECTQUESTIONS.csv","r");
   FILE  *fp3; // TO TAKE A NOTE OF QUESTIONS AND THE TIME CONSUMED PER QUESTION
   fp3 = fopen("C:\\Users\\vapk1\\Desktop\\CODING\\VS CODE FILES\\USERQUESTIONS.csv","w");
   int fmarks = 0;// STORES FINAL MARKS
   int currrow = 0;
   int reqrow = 0;
   char row[5000];
   char *token;
   char temp;
   int x;

   // AS QUESTIONS ARE STORED IN SORTED ORDER MOVING THROUGH THE FILE ROW BY ROW TO FIND QUESTION
      
      time_t starttime = time(NULL);
      time_t timeelapsed = time(NULL);
      
      printf("\nYOUR TEST STARTS NOW\n");
      for(int i=0;i<noofques;i++){
          reqrow = quesarr[i]+1;   // (as question numbers are sorted we can move row by row till the end)
        
          while(currrow<reqrow){
            fgets(row,5000,fp2);
            currrow++;
           }

           fputs(row,fp3);   // updating the USER QUESTION file(for detailed analysis part) 
       
        // DISPLAYING QUESTION AFTER REACHING THE REQUIRED QUESTION
           printf("\n____________________________________________________________________________________________________________________________________________\n");
           printf("\nTime elapsed(in sec) : %d",timeelapsed-starttime);

           // currently token storing quesnumber
           token=strtok(row,",");

           // currently token storing question
           token=strtok(NULL,","); 
           printf("\n QUES %d) %s",i+1,token);
       
           // currently token storing option A
           token = strtok(NULL,",");
           printf("\n A)%s",token);
          
           // currently token storing option B
           token=strtok(NULL,",");
           printf("\n B)%s",token);
       
           // currently token storing option C
           token=strtok(NULL,",");
           printf("\n C)%s",token);
       
           // currently token storing option D
           token=strtok(NULL,",");
           printf("\n D)%s",token);
       
           // currently token storing correct answer
           token=strtok(NULL,",");
       
           // TO ENSURE THAT THE USER ENTERS THE CORRECT OPTION
             while(temp != 'A' && temp != 'a' && temp != 'B' && temp != 'b' && temp != 'C' && temp != 'c' && temp != 'D' && temp != 'd'){  
                printf("\n Enter the Correct Option :");
                fflush(stdin);
                scanf("%c",&temp);
             }
             
            // VERIFYING THE OPTION AND UPDATING THE MARKS
                    if(*token == temp){ 
                       finalverdict[i] = 1;
                       token = strtok(NULL,",");
                       x = atoi(token);
                       fmarks+=x;
                       if(x == 1){
                         (*correasy) += 1;
                        }
                       else if(x == 2){
                        (*corrmed) += 1;
                        }
                       else{
                        (*corrhard) +=1;
                       }
                    }
                    else{
                       finalverdict[i] = 0;
                    }
                    temp = 0; //BCZ REUSING AGAIN
            
              // UPDATING THE TIME ELAPSED AND WRITING IT INTO THE FILE
                  timeelapsed = time(NULL);
                  timeperques[i] = timeelapsed-starttime;                 
    }
    fclose(fp2);
    fclose(fp3);
    return fmarks;
}
   

// MAIN FUNCTION 
void main(){

//_____________________________________________________________________________________________________________________________________________________//
 
 // VARIABLE DECLARATION PART IN THE PROGRAM (TO AVOID REDEFINITION OF VARIABLE DURING CONTINUOS RUNNING OF THE PROGRAM)

      int temp = 0;//TO TAKE INPUT FROM USER WHETHER TO DISPLAY USER MANUAL OR NOT
      int easyques = 0,mediumques = 0,hardques = 0;//TO KEEP THE TRACK OF EASY,MEDIUM AND HARD QUESTIONS 
      //TO KEEP THE COUNT OF COLUMNS WHILE FINDING TOTAL NUMBER OF EASY MEDIUM AND HARD QUESTIONS
      int count = 1;
      char *token; 
      int reqeasy = 100000,reqmed = 100000,reqhard = 100000; // NUMBER OF QUESTIONS THE USER REQUIRES
      int totalques = reqeasy+reqmed+reqhard; 
      int marks = 0; // THIS STORES THE FINAL MARKS OF USER
      int correcteasy = 0,correctmedium = 0,correcthard = 0; // THIS STORES THE NUMBER OF CORRECT QUESTIONS ANSWERED BY USER 
      char temp2 = 0; // TO TAKE USER RESPONSE AFTER MARKS DISPLAY

//_____________________________________________________________________________________________________________________________________________________//
   
   printf("\n      TEST GENERATOR      \n");

    // USER CHOICE

       while(temp != 1 && temp != 2){
         printf("\nPress : \n 1) To display the user manual \n 2) To start the test \n");
         scanf("%d",&temp);
       }
       if(temp == 1){
          printf("\nInstruction : \n * User has the option of selecting number of questions based on the difficulty Level \n * The test has no time limit \n * All the questions are of multiple choice type \n * For Further Queries Contact:xyz Ph:11111 Mail:xyz@mail.com \n");
        }

// ___________________________________________________________________________________________________________________________________________________//
   
   
     // PROGRAM EXECUTION STARTS

      // READING THE FILE TO FIND TOTAL NUMBER OF EASY MEDIUM AND HARD QUESTIONS 

       FILE *fp = fopen("C:\\Users\\vapk1\\Desktop\\CODING\\VS CODE FILES\\PROJECTQUESTIONS.csv","r");
       if(fp == NULL){
         printf("Sorry For The Inconvinience Caused");
         printf("Please Do Contact XYZ to report the error");
       }
       else{
            char line[5000];
            while(fgets(line,5000,fp)){         
         // Moving to "marks" column and reading it to find number of easy,medium and hard questions
            count = 1;
            token = strtok(line,",");
            while(count < 8){ 
               token = strtok(NULL,",");
               count+=1;
            }
            if(atoi(token) == 1){
               easyques+=1;
            }
            else if(atoi(token) == 2){
               mediumques+=1;
            }
            else if(atoi(token) == 4){
               hardques+=1;
            }
        }
      }

    
//____________________________________________________________________________________________________________________________________________________//

    // TEST EXECUTION BEGINS HERE

      while(true){

         // TAKING THE INPUT FROM THE USER FOR THE NUMBER OF QUESTIONS REQUIRED IN THE TEST
         while(reqeasy>easyques || reqmed>mediumques || reqhard>hardques){
           printf("\nEnter the number of easy question(less than %d) : ",easyques+1);
           scanf("%d",&reqeasy);
           printf("\nEnter the number of medium quesions(less then %d) : ",mediumques+1);
           scanf("%d",&reqmed);
           printf("\nEnter the number of hard questions(less than %d) : ",hardques+1);
           scanf("%d",&reqhard);
         }
          totalques = reqeasy+reqmed+reqhard;
 
        //      #      L       O       G       I       C       #        //

         // Function call to randomly select the question numbers
           srand(time(NULL));//THIS ENSURES THAT RANDOM FUNCTION MAINTAINS ITS RANDOMNESS
           int *questionnumbers = (int *)malloc(sizeof(int)*totalques);// DYNAMICALLY ALLOTING THE MEMORY FOR THE QUESTION ARRAY
           selectquestion(reqeasy,reqmed,reqhard,easyques,mediumques,questionnumbers);

    
         // Function call to display the questions and evaluate the marks
           
            int *time = (int *)malloc(sizeof(int)*totalques);
            int *verdict = (int *)malloc(sizeof(int)*totalques);
            marks = displayingselectedquesandevaluatingmarks(questionnumbers,time,verdict,totalques,&correcteasy,&correctmedium,&correcthard);

        //                                                              //

         // DISPLAYING THE FINAL MARKS AND TAKING THE USER RESPONSE
           
           printf("\n_________HURRAY!________YOU__HAVE__SUCCESFULLY__COMPLETED__YOUR___TEST______________________________________________________________________\n");
           // SUMMARISED MARKS SHEET
           printf("\nYOUR TOTAL SCORE IS : %d OUT OF %d \n",marks,reqeasy*1+reqmed*2+reqhard*4);
           printf("\n%d easy questions answered correctly out of %d questions(each consisting of 1 mark)",correcteasy,reqeasy);
           printf("\n%d medium questions answered correctly out of %d questions(each consisting of 2 mark)",correctmedium,reqmed);
           printf("\n%d hard questions answered correctly out of %d questions(each consisting of 4 marks)\n",correcthard,reqhard);
           printf("\n_____________________________________________________________________________________________________________________________________________\n");
           while(temp2 != 'A' && temp2 != 'a' && temp2 != 'B' && temp2 != 'b' && temp2 != 'C' && temp2 != 'c'){
             printf("\nA) Detailed Analysis  B) Another Try c) End \n");
             fflush(stdin);
             scanf("%c",&temp2);
            }
     
         // CONTINUATION OF PROGRAM BASED ON USER RESPONSE
          
          // DETAIKED ANALYSIS DISPLAY
           if(temp2 == 'A' || temp2 == 'a'){
              printf("\nYour Test Performance : \n");
             
              // DISPLAYING TIME CONSUMED BY EACH QUESTION

                 FILE *da; 
                 da = fopen("C:\\Users\\vapk1\\Desktop\\CODING\\VS CODE FILES\\USERQUESTIONS.csv","r");

                 if(da == NULL){
                   printf("Sorry For The Inconvinience Caused");
                   printf("Please Do Contact XYZ to report the error");
                  }
                
                 //READING THE QUESTIONS FILE
                 char row[5000];
                 char *ques;

                 int i = 0;
                 while(totalques>0){

                   printf("\n");
                   fgets(row,5000,da);

                   // currently token storing quesnumber
                    ques=strtok(row,",");
 
                   // currently token storing question
                    ques=strtok(NULL,","); 
                    printf("\n QUESTION :%s",ques);
       
                   // currently token storing option a
                     ques = strtok(NULL,",");
                     printf("\n A)%s",ques);
          
                   // currently token storing option b
                     ques=strtok(NULL,",");
                     printf("\n B)%s",ques);
       
                   // currently token storing option c
                     ques=strtok(NULL,",");
                     printf("\n C)%s",ques);
       
                    // currently token storing option d
                     ques=strtok(NULL,",");
                     printf("\n D)%s",ques);
       
                    // currently token storing correct answer
                     ques=strtok(NULL,",");
                     printf("\n CORRECT ANSWER IS : OPTION %s)",ques);
                    
                    // currently token storing marks
                     ques=strtok(NULL,",");
                     if (atoi(ques) == 1){
                        printf("\n It is a easy level question");
                     }
                     else if(atoi(ques) == 2){
                        printf("\n It is a medium level question");
                     }
                     else if(atoi(ques) == 4){
                        printf("\n It is a hard level question");
                     }
                     
                     if(verdict[i] == 1){
                        printf("\n Your response to this question was correct");
                     }
                     else{
                        printf("\n Your response to this question was incorrect");
                     }
                     if(i == 0){
                        printf("\n Time Spent on this question is %d seconds",time[i]);
                     }
                     else{
                         printf("\n Time Spent on this question is %d seconds",time[i]-time[i-1]);
                     }
                     i++;
                    // currently token storing marks
                     
                     totalques--;
                  }
              
              fclose(da);
              while(temp2 != 'B' && temp2 != 'b' && temp2 != 'C' && temp2 != 'c'){
              printf("\n \n B) Another Try C) End \n");
              fflush(stdin);
              scanf("%c",&temp2);
              }
            }

          // CONTINUATION OF PROGRAM FOR RETEST 
            if (temp2 == 'B' || temp2 == 'b'){
               reqeasy = 100000,reqmed = 100000,reqhard = 100000;//BCZ REUSING AGAIN
               temp2 = 0;//BCZ REUSING AGAIN
               continue;
            }
          
          // ENDING FEEDBACK FROM USER
            else if (temp2 == 'C' || temp2 == 'c'){
               char temp3;
               printf("\n_________________________________________________YOUR FEEDBACK MATTERS_________________________________________________________\n");
               while(temp3 != 'A' && temp3 != 'a' && temp3 != 'B' && temp3 != 'b' && temp3 != 'C' && temp3 != 'c'){
                 printf("\nHow was Your Test Experience :\n A) Excellent \n B) Good \n C)Not good \n");
                 fflush(stdin);
                 scanf("%c",&temp3);
                }
               FILE *fb;
               fb = fopen("C:\\Users\\vapk1\\Desktop\\CODING\\VS CODE FILES\\feedback.txt","a");
               if(fb == NULL){
                  printf("SORRY FOR THE INCONVINIENCE CAUSED!");
               } 
               else{
               putc(temp3,fb);// wrinting the user 
               }
               printf("\n       THANKYOU        ");
               break;
            }
     }

//____________________________________________________________________________________________________________________________________________________//
  // CLOSING FILE POINTER 
  fclose(fp);

}

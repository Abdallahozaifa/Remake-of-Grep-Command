/** CMPSC 474 /CMPEN 441
 * Lab 1
 * File Name: lab2.c
 *
 *Your Name: Hozaifa Abdalla
 *
 *Your PSU user ID:  hea113
 *
 *CMPSC474 Spring 2016 
 *
 *Due Time: 12:00, Thursday, January, 2016
 *
 *Time of Last Modification: 2:50, Thursday, January 24, 2016
 *Academic Integrity Statement: I certify that, while others may have assisted me in brain storming, debugging and validating this program, the program itself is my own work. I understand that submitting code which is the work of other individuals is a violation of the course Academic Integrity Policy and may result in a zero credit for the assignment, or course failure and a report to the Academic Dishonesty Board. I also understand that if I knowingly give my original work to another individual that it could also result in a zero credit for the assignment, or course failure and a report to the Academic Dishonesty Board. See Academic Integrity Procedural Guidelines at:  
https://psbehrend.psu.edu/intranet/faculty-resources/academic-integrity/academic-integrity-procedural-guidelines
 
 *Assisted by and Assisted line numbers:
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

/* function declaration for searching an element through files */
void searchElement(int argc, char *argv[], bool countOn, bool lineNumberOn);

int main(int argc, char *argv[]){
    // if the user doesn't supply atleast 3 parameters then it displays an error message and stops execution
    if(argc < 3){
        printf("Atleast 3 parameters are required!\n");
        exit(0);
    // if the user supplies more than 3 parameters and one of them is -c then it searches the search element in the files
    }else if(argc > 3 && strcmp(argv[1], "-c") == 0){ 
        searchElement(argc, argv, true, false);
    // if the user supplies more than 3 parameters and one of them is -L then it searches the search element in the files and adds the line number
    }else if(argc > 3 && strcmp(argv[1], "-L") == 0){
        searchElement(argc, argv, false, true);
    // if the user supplies more than 3 parameters and it does not consist of -c it searches the search element in the files    
    }else{
        searchElement(argc, argv, false, false);
    }   
}

/* function definition for searching an element in a file */
void searchElement(int argc, char *argv[], bool countOn, bool lineNumberOn){
    FILE *filepointer; // variable that points to a file
    char fileline[300]; // char array that holds all characters for each line
    int linenumber=0, timesfound=0,i, argVindex = argc - 1, searchWordPosition, numberofTextFiles;
    
    // if user enters -c or -L  
    if(countOn || lineNumberOn){
        searchWordPosition = 2; // search word position location
        numberofTextFiles = argc - 3; // number of textfiles
    }
    // if the user does not enter -c
    else{
        searchWordPosition = 1; // search word position
        numberofTextFiles = argc - 2; // numberofTextFiles
    }  
    
    /* Iterates through every file listed in the parameter list and looks for a match in all files */
    for(i=0;i<numberofTextFiles;i++){
        //printf("argVIndex: %d\n", argVindex);
        filepointer = fopen(argv[argVindex], "r"); // opens the file and assigns it to the pointers location
        
        // if the file can does not exist or error retrieving it outputs an error message and stops execution
        if(filepointer == NULL){
            printf("Error retrieving file, error number is %d\n!", errno);
            exit(0);
        }
        
        //reads the file line by line until the end of the file 
        while(fgets(fileline,300,filepointer) != NULL){
            //printf("%s", fileline);
            linenumber++; // stores the current linenumber
            
            // searches for the target word entered in the parameter list line by line                          
            if(strstr(fileline, argv[searchWordPosition]) != NULL){
                    // if the user has not entered -c
                    if(!countOn){
                        int j;
                        int fileLineSize = getLength(fileline); // each file line size
                        char *searchWordMatch = strstr(fileline, argv[searchWordPosition]); // obtains the match for the searched word in order to change the text color
                        int wordMatchStartPos = searchWordMatch - fileline,  searchWordLength = strlen(argv[searchWordPosition]); // start position for target word
                        int wordMatchEndPos = wordMatchStartPos + searchWordLength; // end position for target word
                        // if the lineNumber parameter is entered then display the line it displays the linenumber and prints out the text file for each line
                        if(lineNumberOn){
                            printf("\033[1;35m%s %d: \033[0m", argv[argVindex], linenumber); 
                        }else{
                            printf("\033[1;35m%s: \033[0m", argv[argVindex]);    
                        }
                        // iterates through each character in the file line to change the color of text for the target word
                        for(j=0;j<fileLineSize;j++){
                            // if target letter is hit change the text color on the terminal otherwise print it normally
                            if(j >= wordMatchStartPos && j< wordMatchEndPos){
                                printf("\033[1;31m%c\033[0m", fileline[j]);                 
                            }else{
                                printf("%c",fileline[j]);
                            }
                        }
                        
                    }
                    timesfound++; // stores the number of matches for the target word
            }    
        }
        fclose(filepointer); // closes the file after each file that it opens in order to open the next file properly and often a good practice
        argVindex--; // stores the index the textfiles and starts from the right most file to the left
    }
    
    //if the user enters the -c
    if(countOn){
        printf("\033[1;39mOccurences: %d\n\033[0m", timesfound);
    }
}

// returns the length of a char array
int getLength(char array[]){
    int size=0,i;
    // iterates through each element in the char array until the null string
    for(i=0;array[i] != '\0';i++){
        size++;
    }
    return size;
}

/** Output Below!:
hozaifa@hozaifa-UX31A:~/Desktop/Cmpen441/lab2$ gcc -o lab2 lab2.c
hozaifa@hozaifa-UX31A:~/Desktop/Cmpen441/lab2$ ./lab2 -c Hozaifa cool.txt fun.txt
Occurences: 2
hozaifa@hozaifa-UX31A:~/Desktop/Cmpen441/lab2$ ./lab2 Hozaifa cool.txt fun.txt
fun.txt: Hozaifa is sweet
cool.txt: Hozaifa Abdalla
hozaifa@hozaifa-UX31A:~/Desktop/Cmpen441/lab2$ ./lab2 Hozaifa cool.txt 
cool.txt: Hozaifa Abdalla
hozaifa@hozaifa-UX31A:~/Desktop/Cmpen441/lab2$ ./lab2  cool.tx11 
Atleast 3 parameters are required!
hozaifa@hozaifa-UX31A:~/Desktop/Cmpen441/lab2$ ./lab2 Hozaifa cool.txt23 
Error retrieving file, error number is 2
!hozaifa@hozaifa-UX31A:~/Desktop/Cmpen441/lab2$ ./lab2 Abdalla cool.txt 
cool.txt: Hozaifa Abdalla
hozaifa@hozaifa-UX31A:~/Desktop/Cmpen441/lab2$ ./lab2 -c Abdalla cool.txt 
Occurences: 1
hozaifa@hozaifa-UX31A:~/Desktop/Cmpen441/lab2$ ./lab2 -c software cool.txt 
Occurences: 7
hozaifa@hozaifa-UX31A:~/Desktop/Cmpen441/lab2$ ./lab2 software cool.txt 
cool.txt: Software engineering is the study and an application of engineering to the design, development and maintenance of software.[1][2][3]
cool.txt: Typical formal definitions of software engineering are:
cool.txt: "research, design, develop, and test operating systems-level software, compilers, and network distribution software for medical, industrial, military, communications, aerospace, business, scientific, and general computing applications."[4]
cool.txt: "the systematic application of scientific and technological knowledge, methods, and experience to the design, implementation, testing, and documentation of software";[5]
cool.txt: "the application of a systematic, disciplined, quantifiable approach to the development, operation, and maintenance of software";[6]
cool.txt: "an engineering discipline that is concerned with all aspects of software production";[7]
cool.txt: and "the establishment and use of sound engineering principles in order to economically obtain software that is reliable and works efficiently on real machines.
hozaifa@hozaifa-UX31A:~/Desktop/Cmpen441/lab2$ ./lab2 -L software cool.txt
 
cool.txt 4: Software engineering is the study and an application of engineering to the design, development and maintenance of software.[1][2][3]
cool.txt 5: Typical formal definitions of software engineering are:
cool.txt 6: "research, design, develop, and test operating systems-level software, compilers, and network distribution software for medical, industrial, military, communications, aerospace, business, scientific, and general computing applications."[4]
cool.txt 7: "the systematic application of scientific and technological knowledge, methods, and experience to the design, implementation, testing, and documentation of software";[5]
cool.txt 8: "the application of a systematic, disciplined, quantifiable approach to the development, operation, and maintenance of software";[6]
cool.txt 9: "an engineering discipline that is concerned with all aspects of software production";[7]
cool.txt 10: and "the establishment and use of sound engineering principles in order to economically obtain software that is reliable and works efficiently on real machines.		
*/

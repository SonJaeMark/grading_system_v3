#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "stringlib.h"
#include "userfilelib.h"
#include "userlib.h"
#include "studentlib.h" 

#define MATCH 1
#define UNIQUE 0
#define NUM_GRADES 6  // Define yung number ng subjects

float getAve(Student student) {
    float gradesArray[NUM_GRADES];
    float totalGrades = 0.0;
    
    // Store ng individual grades
    gradesArray[0] = student.grades.MATH;
    gradesArray[1] = student.grades.SCI;
    gradesArray[2] = student.grades.ENG;
    gradesArray[3] = student.grades.FIL;
    gradesArray[4] = student.grades.HIS;
    gradesArray[5] = student.grades.PE;

    // Calculate total grades using the arrays
    for (int i = 0; i < NUM_GRADES; i++) {
        totalGrades += gradesArray[i];
    }

    // Calculate average
    float ave = totalGrades / NUM_GRADES;
    return ave;
}

void removeDuplicate(int data[], int *size)
{
    int indicator = 1;
    int newSize = 0;
    int tempOut[*size];
    int temp = 0;
    
    while(indicator){
        
        for(int i = 0; i < *size-1; i++){
            indicator = 0;
            int temp = 0;
            int currentNum = data[i];
            int nextNum = data[i+1];
            
            if( currentNum > nextNum){
                temp = nextNum;
                data[i+1] = currentNum;
                data[i] =temp;
                indicator = 1;
            }
        }
        
        for(int i = 0; i < *size-1; i++){
            int currentNum = data[i];
            int nextNum = data[i+1];
            
            if( currentNum > nextNum){
                indicator = 1;
            }
        }
    }
    
    for(int i = 0; i < *size; i++)
    {
        if(temp != data[i]){
            
            temp = data[i];
            tempOut[newSize] = data[i];
            newSize++;
        }
    }
    
    for(int i = 0; i < newSize; i++)
    {
        data[i] = tempOut[i];
    }
    
    *size = newSize;
}

void getUnique(int base[], int baseSize, int compare[], int *compareSize)
{
    int newSize = 0;
    int temp[*compareSize];
    
    for(int i = 0; i < *compareSize; i++)
    {
        temp[i] = compare[i];
    }
    
    for(int i = 0; i < *compareSize; i++)
    {
        for(int j = 0; j < baseSize; j++)
        {
            if(temp[i] == base[j])
            {
                temp[i] = 0;
                break;
            }
        }
    }
    
    for(int i = 0; i < *compareSize; i++)
    {
        
        if(temp[i] != 0)
        {
            compare[newSize] = temp[i];
            newSize++;
        }
    }
    
    *compareSize = newSize;
}

void getMatch(int base[], int baseSize, int compare[], int *compareSize)
{
    int newSize = 0;
    int temp[*compareSize];
    int matchFlag = 0;
    
    for(int i = 0; i < *compareSize; i++)
    {
        temp[i] = compare[i];
    }
    
    for(int i = 0; i < *compareSize; i++)\
    {
        for(int j = 0; j < baseSize; j++)
        {
            if(temp[i] == base[j])
            {
                compare[newSize] = temp[i];
                newSize++;
            }
        }
    }
    
    *compareSize = newSize;
    
}

int viewAllMyStudents(User *user)
{
    int numOfStud = 0;

    if(user->student->id != 0)
    {
        printf("You are not allowed to access this!\n");
        return 0;
    }

    numOfStud = getAllStudentByTeacherId(user->teacher->id, user->student);

    for (int i = 0; i < numOfStud; i++)
    {
        printf("[%d]%d %s %s\n",i+1, user->student[i].id, user->student[i].fname, user->student[i].lname);
    }
    
    initStudent(user->student);
    return numOfStud;
}


int addStudentToClass(User *user)
{
    int succeedCount = 0;
    int currentStudCount = 0;
    int inputIdsHolderCount = MAX_STUDENT_COUNT;
    int studRetrievedCount = MAX_STUDENT_COUNT;
    int inputIdsSize = MAX_STUDENT_COUNT;
    char strBuffer[STR_CVS_LEN_OUT];
    int studRetrieved[studRetrievedCount];
    int inputIds[inputIdsSize];
    int inputIdsHolder[inputIdsHolderCount];
    int inputIdCount = 0;

    // check if student is logged in
    if(user->student->id != 0)
    {
        printf("!!You are not allowed to access this!\n");
        return 0;
    }
    
    //retrieve id of studs and count current student
    for(int i = 0; i < MAX_STUDENT_COUNT; i++)
    {
        if(user->teacher->studentsList.studentId[i] != 0)
        {
            studRetrieved[i] = user->teacher->studentsList.studentId[i];
            currentStudCount++;
            
        }
    }
    studRetrievedCount = currentStudCount;

    //check if 10 exit
    if(currentStudCount == 10)
    {
        printf("Not able to add more studnet, you've reach the max studnet count allowable!\n");
        return 0;
    }

    for(int i = 0; i < MAX_STUDENT_COUNT; i++)
    {
        inputIds[i] = 0;
    }

    //ask for ids HERE

    while (1)
    {
        //remove duplicate
        //get unique
        //count the remaining stud after validation
        //add if the num will exceed 10 if so ask again goto HERE
        printf("Enter the ID of student you want to add in your class(separate with space if more than 1): ");
        fgetsm(strBuffer, STR_CVS_LEN_OUT, stdin);

        inputIdCount = sscanf(
            strBuffer, "%d %d %d %d %d %d %d %d %d %d", 
            &inputIds[0], &inputIds[1], &inputIds[2], &inputIds[3], &inputIds[4],
            &inputIds[5], &inputIds[6], &inputIds[7], &inputIds[8], &inputIds[9]
        );

        removeDuplicate(inputIds, &inputIdsSize);

        for (int i = 0; i < inputIdsSize; i++)
        {
            inputIdsHolder[i] = inputIds[i];
        }
        inputIdsHolderCount = inputIdsSize;

        getUnique(studRetrieved, studRetrievedCount, inputIds, &inputIdsSize);
        if(inputIdsSize + currentStudCount <= 10) break;
        printf("Input ID/s exceed the max allowable student count.\n");
    }

    //for each unique id  -> edit stud
    for (int i = 0; i < inputIdsSize; i++)
    {
        if(getStudentById(inputIds[i], user->student) && 
            strcpy(user->student->section, user->teacher->section) != NULL &&
            editStudent(user->student->id, user->student))
        {
            printf("+++Student %d successfuly added to your class!\n", inputIds[i]);
            for(int j = 0; j < MAX_STUDENT_COUNT; j++)
            {
                if(user->teacher->studentsList.studentId[j] == 0)
                {
                    user->teacher->studentsList.studentId[j] = inputIds[i];
                    j = MAX_STUDENT_COUNT;
                } 
                
            }
            succeedCount++;
        }
        else
        {
            printf("!!!Student %d failed to add in your class!\n", inputIds[i]);
        }
    }

    getMatch(studRetrieved, studRetrievedCount, inputIdsHolder, &inputIdsHolderCount);
    for (int i = 0; i < inputIdsHolderCount; i++)
    {
        printf("!Srudent ID no.%d is already in your class.\n", inputIdsHolder[i]);
    }
    
    //edit teach

    if(editTeacher(user->teacher->id, user->teacher))
    {
        printf("+++Added %d in your class.\n", succeedCount);
        printf("++you have %d in total in your class.\n", succeedCount + currentStudCount);
        
    }
    else
    {
        printf("!!!Failed in editting teacher info, please contact the admin!\n");
        return 0;
    }
    
    //initStud
    initStudent(user->student);
    return succeedCount;
}

int removeStudentToClass(User *user)
{
   int succeedCount = 0;
    int currentStudCount = 0;
    int inputIdsHolderCount = MAX_STUDENT_COUNT;
    int studRetrievedCount = MAX_STUDENT_COUNT;
    int inputIdsSize = MAX_STUDENT_COUNT;
    char strBuffer[STR_CVS_LEN_OUT];
    int studRetrieved[studRetrievedCount];
    int inputIds[inputIdsSize];
    int inputIdsHolder[inputIdsHolderCount];
    int inputIdCount = 0;

    // check if student is logged in
    if(user->student->id != 0)
    {
        printf("!!You are not allowed to access this!\n");
        return 0;
    }

    //retrieve id of studs and count current student
    for(int i = 0; i < MAX_STUDENT_COUNT; i++)
    {
        if(user->teacher->studentsList.studentId[i] != 0)
        {
            studRetrieved[i] = user->teacher->studentsList.studentId[i];
            currentStudCount++;
            
        }
    }
    studRetrievedCount = currentStudCount;

    for(int i = 0; i < MAX_STUDENT_COUNT; i++)
    {
        inputIds[i] = 0;
    }

    while (1)
    {
        //remove duplicate
        //get unique
        //count the remaining stud after validation
        //add if the num will exceed 10 if so ask again goto HERE
        printf("Enter the ID of student you want to add in your class(separate with space if more than 1): ");
        fgetsm(strBuffer, STR_CVS_LEN_OUT, stdin);

        inputIdCount = sscanf(
            strBuffer, "%d %d %d %d %d %d %d %d %d %d", 
            &inputIds[0], &inputIds[1], &inputIds[2], &inputIds[3], &inputIds[4],
            &inputIds[5], &inputIds[6], &inputIds[7], &inputIds[8], &inputIds[9]
        );

        removeDuplicate(inputIds, &inputIdsSize);

        for (int i = 0; i < inputIdsSize; i++)
        {
            inputIdsHolder[i] = inputIds[i];
        }
        inputIdsHolderCount = inputIdsSize;

        getMatch(studRetrieved, studRetrievedCount, inputIds, &inputIdsSize);
        if(currentStudCount - inputIdsSize >= 0) break;
        printf("Input ID/s exceed the total student count.\n");
    }

    //for each match id  -> edit stud
    for (int i = 0; i < inputIdsSize; i++)
    {
        if(getStudentById(inputIds[i], user->student) && 
            strcpy(user->student->section, "A0") != NULL &&
            editStudent(user->student->id, user->student))
        {
            printf("---Student %d successfuly removed to your class!\n", inputIds[i]);
            for(int j = 0; j < MAX_STUDENT_COUNT; j++)
            {
                if(user->teacher->studentsList.studentId[j] == inputIds[i])
                {
                    user->teacher->studentsList.studentId[j] = 0;
                    j = MAX_STUDENT_COUNT;
                } 
                
            }
            succeedCount++;
        }
        else
        {
            printf("!!!Student %d failed to remove in your class!\n", inputIds[i]);
        }
    }

    getUnique(studRetrieved, studRetrievedCount, inputIdsHolder, &inputIdsHolderCount);
    for (int i = 0; i < inputIdsHolderCount; i++)
    {
        printf("!Student ID no.%d is not in your class.\n", inputIdsHolder[i]);
    }

    //edit teach

    if(editTeacher(user->teacher->id, user->teacher))
    {
        printf("---Removed %d in your class.\n", succeedCount);
        printf("++you have %d in total in your class.\n", currentStudCount - succeedCount);
        
    }
    else
    {
        printf("!!!Failed in editting teacher info, please contact the admin!\n");
        return 0;
    }
    
    //initStud
    initStudent(user->student);
    return succeedCount;
}

void viewGradesOfStudentById(User *user)
{
    int isexit = 0;
    int inputIdsSize = MAX_STUDENT_COUNT;
    char strBuffer[STR_CVS_LEN_OUT];
    int inputIds[inputIdsSize];
    int inputIdCount = 0;
    

    // check if student is logged in
    if(user->student->id != 0)
    {
        printf("!!You are not allowed to access this!\n");
        return;
    }

    while (1)
    {
        printf("Enter the ID of student you want to see grades: ");
        fgetsm(strBuffer, STR_CVS_LEN_OUT, stdin);

        inputIdCount = sscanf(strBuffer, "%d", &inputIds[0]);

        for (int i = 0; i < MAX_STUDENT_COUNT; i++)
        {
            if(inputIds[0] == user->teacher->studentsList.studentId[i])
            {
                isexit = 1;
            }
        }
        if(isexit) break;

        printf("!!ID no.%d is not in you class.\n", inputIds[0]);
    }

    getStudentById(inputIds[0], user->student);
    viewMyGrades(user);
    initStudent(user->student);
}

void giveGrades(User *user)
{
    int isexit = 0;
    int inputIdsSize = MAX_STUDENT_COUNT;
    char strBuffer[STR_CVS_LEN_OUT];
    int inputIds[inputIdsSize];
    int inputIdCount = 0;
    float grades[7];

    // check if student is logged in
    if(user->student->id != 0)
    {
        printf("!!You are not allowed to access this!\n");
        return;
    }

    while (1)
    {
        printf("Enter the ID of student you want to see grades: ");
        fgetsm(strBuffer, STR_CVS_LEN_OUT, stdin);

        inputIdCount = sscanf(strBuffer, "%d", &inputIds[0]);

        for (int i = 0; i < MAX_STUDENT_COUNT; i++)
        {
            if(inputIds[0] == user->teacher->studentsList.studentId[i])
            {
                isexit = 1;
            }
        }
        if(isexit) break;

        printf("!!ID no.%d is not in you class.\n", inputIds[0]);
    }

    getStudentById(inputIds[0], user->student);

    printf("Enter grades per subject\n");
    printf("                                            MATH SCI ENG FIL HIS PE\n");
    printf("separate with space put or 0 to skip sub-->");
    fgetsm(strBuffer, STR_CVS_LEN_OUT, stdin);
    sscanf(strBuffer, "%f %f %f %f %f %f", 
        &grades[0], &grades[1], &grades[2], &grades[3], &grades[4], &grades[5]
    );

    for(int i = 0; i < NUM_GRADES; i++)
    {
        printf("%.2f\n", grades[i]);
    }

    user->student->grades.MATH = grades[0];
    user->student->grades.SCI = grades[1];
    user->student->grades.ENG = grades[2];
    user->student->grades.FIL = grades[3];
    user->student->grades.HIS = grades[4];
    user->student->grades.PE = grades[5];

    user->student->grades.AVE = getAve(user->student[0]);

    if(editStudent(inputIds[0], user->student))
    {
        printf("Grades successfuly given!\n");
        printf("Do you want to see grades [y]Yes || [n]No? ");
        fgetsm(strBuffer, STR_CVS_LEN_OUT, stdin);
        if(strcmp(strBuffer, "y") == 0)
        {
            viewMyGrades(user);
        }
    }
    else
    {
        printf("Error in giving grades!\n");
    }
    initStudent(user->student);
}


#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "stringlib.h"
#include "userfilelib.h"
#include "userlib.h"
#include "studentlib.h"
#include "teacherlib.h"



int ask(char *q, char *ans1, char *ans0)
{
    char strBuffer[STR_CVS_LEN_IN];
    while (1)
    {
        printf("%s: ", q);
        fgetsm(strBuffer, STR_CVS_LEN_IN, stdin);

        if(strcmp(ans1, strBuffer) == 0)
        {
            return 1;
        }
        else if (strcmp(ans0, strBuffer) == 0)
        {
            return 0;
        }
        
    }
}

int main()
{
    User user;
    Teacher teachers[10];
    Student students[10];

    user.teacher = teachers;
    user.student = students;

    initStudent(user.student);
    initTeacher(user.teacher);
    
    char strBuffer[STR_CVS_LEN_IN];
    char r[5] = "r";
    char l[5] = "l";
    int action = 0;
    while (1)
    {
        if(user.student->id == 0 && user.teacher->id == 0 && ask("[l]Login || [r]Register", l, r)) loginUser(&user);
        else if(user.student->id == 0 && user.teacher->id == 0) registerUser(&user);

        
        printf("\n\n");
        printf("Actions: [1]Log out                         [2]View All My Students\n");
        printf("Actions: [3]Add Student To Class            [4]Remove Student To Class\n");
        printf("Actions: [5]View Grades Of Student By Id    [6]Give Grades\n"); 
        printf("Actions: [7]View My Grades                  [8]Exit\n");
        

        printf("Actions: ");
        fgetsm(strBuffer, STR_CVS_LEN_IN, stdin);
        sscanf(strBuffer, "%d", &action);

        switch (action)
        {
        case 1:
            printf("\n\n");
            logoutUser(&user);
            break;
        case 2:
            printf("\n\n");
            viewAllMyStudents(&user);
            break;
        case 3:
            printf("\n\n");
            addStudentToClass(&user);
            break;
        case 4:
            printf("\n\n");
            removeStudentToClass(&user);
            break;
        case 5:
            printf("\n\n");
            viewGradesOfStudentById(&user);
            break;
        case 6:
            printf("\n\n");
            giveGrades(&user);
            break;
        case 7:
            printf("\n\n");
            viewMyGrades(&user);
            break;
        case 8:
            return 0;
        default:
            printf("\n\n");
            printf("input 1-7\n");
            break;
        }
    }
    

    
    
    return 0;
}
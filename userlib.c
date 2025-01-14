#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "userfilelib.h"
#include "userlib.h"
#include "stringlib.h"
#include "validationlib.h"


int registerUser(User *user)
{
    char strBuffer[STR_CVS_LEN_IN];
    char passwordHolder[STR_CVS_LEN_IN];
    char userToCsv[STR_CVS_LEN_OUT];
    int isTeacher = -1;
    int MM;
    int DD;
    int YYYY;


    printf("Registration:\n");
    
    while (1)
    {
        printf("Register as [t]Teacher || [s]Student: ");
        fgetsm(strBuffer, sizeof(strBuffer), stdin);

        if (strcmp(strBuffer, "t") == 0)
        {
            printf("Registering as Teacher...\n");
            initTeacher(user->teacher);
            initStudent(user->student);
            isTeacher = 1;
            break;
        }
        else if (strcmp(strBuffer, "s") == 0)
        {
            printf("Registering as Student...\n");
            initStudent(user->student);
            initTeacher(user->teacher);
            isTeacher = 0;
            break;
        }
        else
        {
            printf("Please input correct response... \n");
        }       
    }
    strcpy(strBuffer, "\0");

    printf("Please enter necessary details.\n");

    printf("Enter firstname: ");
    fgetsm(strBuffer, sizeof(strBuffer), stdin);
    isTeacher == 1 ? strcpy(user->teacher->fname, strBuffer) : strcpy(user->student->fname, strBuffer);
    strcpy(strBuffer, "\0");

    printf("Enter lastname: ");
    fgetsm(strBuffer, sizeof(strBuffer), stdin);
    isTeacher == 1 ? strcpy(user->teacher->lname, strBuffer) : strcpy(user->student->lname, strBuffer);
    strcpy(strBuffer, "\0");

    printf("Enter username: ");
    fgetsm(strBuffer, sizeof(strBuffer), stdin);
    isTeacher == 1 ? strcpy(user->teacher->userName, strBuffer) : strcpy(user->student->userName, strBuffer);
    strcpy(strBuffer, "\0");

    while (1)
    {
        printf("Sections: A1, A2, A3, A4, A5, A6, A7, A8, A9, A10\n");
        printf("Enter section: ");
        fgetsm(strBuffer, sizeof(strBuffer), stdin);

        if(strcmp(strBuffer, "A1") == 0) break;
        if(strcmp(strBuffer, "A2") == 0) break;
        if(strcmp(strBuffer, "A3") == 0) break;
        if(strcmp(strBuffer, "A4") == 0) break;
        if(strcmp(strBuffer, "A5") == 0) break;
        if(strcmp(strBuffer, "A6") == 0) break;
        if(strcmp(strBuffer, "A7") == 0) break;
        if(strcmp(strBuffer, "A8") == 0) break;
        if(strcmp(strBuffer, "A9") == 0) break;
        if(strcmp(strBuffer, "A10") == 0) break;

    } 
    isTeacher == 1 ? strcpy(user->teacher->section, strBuffer) : strcpy(user->student->section, strBuffer);
    strcpy(strBuffer, "\0");

    while (1)
    {
        printf("Enter date of birth 'MM DD YYYY' format: ");
        scanf("%d %d %d", &MM, &DD, &YYYY);
        // fgetsm(strBuffer, sizeof(strBuffer), stdin);
        sscanf(strBuffer, "%d %d %d", &MM, &DD, &YYYY);
        if(dateOfBirthValidation(MM, DD, YYYY) == 1) break;
        printf("Birthday format invalid\n");
    }

    if (isTeacher)
    {
        user->teacher->id = generateId();
        user->teacher->dateOfBirth.MM = MM;
        user->teacher->dateOfBirth.DD = DD;
        user->teacher->dateOfBirth.YYYY = YYYY;
    }
    else
    {
        user->student->id = generateId();
        user->student->dateOfBirth.MM = MM;
        user->student->dateOfBirth.DD = DD;
        user->student->dateOfBirth.YYYY = YYYY;
    }
    getchar();

    while (1)
    {
        printf("Enter password: ");
        fgetsm(strBuffer, sizeof(strBuffer), stdin);
        strcpy(passwordHolder, strBuffer);

        printf("Re-enter password: ");
        fgetsm(strBuffer, sizeof(strBuffer), stdin);

        if (strcmp(passwordHolder, strBuffer) == 0) break;        
        printf("Password not match.\n");
    }
    
    
    if (isTeacher)
    {
        strcpy(user->teacher->password, strBuffer);
        teacherToCsv(user->teacher, userToCsv);
        saveTeacher(userToCsv);
        savePassword(user->teacher->id, user->teacher->password);
    }
    else
    {
        strcpy(user->student->password, strBuffer);
        studentToCsv(user->student, userToCsv);
        saveStudent(userToCsv);
        savePassword(user->student->id, user->student->password);
    }

    printf("Registration Complete!!!\n");

}

int logoutUser(User *user)
{
    char strBuffer[STR_CVS_LEN_IN];
    while (1)
    {
        printf("You sure you want to log out?\n");
        printf("[y]Yes || [n]No \n");
        fgetsm(strBuffer, sizeof(strBuffer), stdin);
        if(strcmp("n", strBuffer) == 0) break;
        else if(strcmp("y", strBuffer) == 0)
        {
            initTeacher(user->teacher);
            initStudent(user->student);
            break;
        }
    }
    
}

int loginUser(User *user)
{
    char strBuffer[STR_CVS_LEN_IN];
    char passwordHolder[STR_CVS_LEN_IN];
    int id;
    int isTeacher = -1;

    if(user->teacher->id != 0)
    {
        printf("Cannot log in, User %d-%s is currently logged in.\n", user->teacher->id, user->teacher->userName);
        return 0;
    }
    else if(user->student->id != 0)
    {
        printf("Cannot log in, User %d-%s is currently logged in.\n", user->student->id, user->student->userName);
        return 0;
    }

    while (1)
    {
        printf("Log in as [t]Teacher || [s]Student: ");
        fgetsm(strBuffer, sizeof(strBuffer), stdin);

        if (strcmp(strBuffer, "t") == 0)
        {
            printf("Logging in as Teacher...\n");
            initTeacher(user->teacher);
            initStudent(user->student);
            isTeacher = 1;
            break;
        }
        else if (strcmp(strBuffer, "s") == 0)
        {
            printf("Logging in as Student...\n");
            initStudent(user->student);
            initTeacher(user->teacher);
            isTeacher = 0;
            break;
        }
        else
        {
            printf("Please input correct response... \n");
        }       
    }
    
    
    while (1)
    {
        printf("Enter ID: ");
        fgetsm(strBuffer, sizeof(strBuffer), stdin);
        
        sscanf(strBuffer, "%d", &id);
        getPasswordById(id, passwordHolder);

        printf("Enter password: ");
        fgetsm(strBuffer, sizeof(strBuffer), stdin);

        if (strcmp(passwordHolder, strBuffer) == 0) break;        
        printf("Incorrect password or id.\n");
    }

    if(isTeacher)
    {
        getTeacherById(id, user->teacher);
        initStudent(user->student);
        printf("Welcome %s %s!\n", user->teacher->fname, user->teacher->lname);
    }
    else if (isTeacher == 0)
    {
        getStudentById(id, user->student);
        initTeacher(user->teacher);
        printf("Welcome %s %s!\n", user->student->fname, user->student->lname);
    }
    else
    {
        printf("Missing user details!\n");
        printf("Please contact the admin!\n");
        return 0;
    }
    return 1;
}


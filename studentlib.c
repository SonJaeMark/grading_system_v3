#include <stdlib.h>
#include <stdio.h>

#include "stringlib.h"
#include "userfilelib.h"
#include "userlib.h"

int viewMyGrades(User *user)
{
    if(user->student->id == 0)
    {
        printf("You are not allowed to access this!\n");
        return 0;
    }
    printf("Section: %s\n", user->student->section);
    printf("%s %s grades:\n", user->student->fname, user->student->lname);
    printStudent(user->student, 1);
    return 1;
}
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "stringlib.h"
#include "userfilelib.h"

int main()
{
    Teacher teacher;
    Student students[10];
    Student student;
    char studentInCsv[STR_CVS_LEN_OUT];

    int result = getAllStudentByTeacherId(241000, students);

    for (int i = 0; i < result; i++)
    {
        studentToCsv(&students[i], studentInCsv);
        printf("[%d]: %s\n", i, studentInCsv);
    }

    printf("\n\n\n");

    printStudent(students, result);


    printf("\n\n\n");
    
    getStudentById(242195, &student);
    studentToCsv(&student, studentInCsv);

    printf("studentToCsv: %s\n", studentInCsv);
    printStudent(&student, 1);
    
    return 0;
}
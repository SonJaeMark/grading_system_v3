#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "userfilelib.h"

#define STUDENT_FILE "ffile_student.txt"
#define TEACHER_FILE "ffile_teacher.txt"
#define ID_INIT_VAL 240000
#define STUDENT_CSV_VAL_COUNT 13
#define TEACHER_CSV_VAL_COUNT 16


/**
 * @brief Saves student information in CSV format to the student file.
 * 
 * This function saves the given student information string into a CSV file.
 * If the file does not exist, it creates a new file and writes a header line.
 * If the file exists, it appends the student information to the file.
 * 
 * @param studentInfoCsv Pointer to the string containing student information in CSV format.
 * @return int Returns 1 if the operation is successful, otherwise returns 0.
 */
int saveStudent(char *studentInfoCsv)
{
    FILE *fptr;

    // check if the studentInfoCsv is empty or NULL    
    if(studentInfoCsv == NULL || strcmp("", studentInfoCsv) == 0)
    {
        printf("Student info is empty");
        return 0;
    }

    fptr = fopen(STUDENT_FILE, "r");

    // check file if NULL
    if(fptr == NULL)
    {
        fptr = fopen(STUDENT_FILE, "w");
        if (fptr == NULL)
        {
            perror("Error opening student file for writing");
            return 0;
        }
        // add header if file not exist yet
        fprintf(fptr, "id,first_name,last_name,date_of_birth,username,section,grades(MATH,SCI,ENG,FIL,HISTORY,PE,AVE)\n");
    }
    else
    {
        fptr = fopen(STUDENT_FILE, "a");
        if (fptr == NULL)
        {
            perror("Error opening student file for appending");
            return 0;
        }
    }

    // print the studentInfoCsv into file
    fprintf(fptr, "%s\n", studentInfoCsv); 
    fclose(fptr);

    return 1;
}

/**
 * @brief Saves teacher information in CSV format to the teacher file.
 * 
 * This function saves the given teacher information string into a CSV file.
 * If the file does not exist, it creates a new file and writes a header line.
 * If the file exists, it appends the teacher information to the file.
 * 
 * @param teacherInfoCsv Pointer to the string containing teacher information in CSV format.
 * @return int Returns 1 if the operation is successful, otherwise returns 0.
 */
int saveTeacher(char *teacherInfoCsv)
{
    FILE *fptr;

    // check if the teacherInfoCsv is empty or NULL
    if(strcmp("", teacherInfoCsv) == 0 || teacherInfoCsv == NULL)
    {
        printf("Teacher info is empty");
        return 0;
    }

    fptr = fopen(TEACHER_FILE, "r");

    // check file if NULL
    if(fptr == NULL)
    {
        fptr = fopen(TEACHER_FILE, "w");
        if (fptr == NULL)
        {
            perror("Error opening student file for writing");
            return 0;
        }
        // add header if file not exist yet
        fprintf(fptr, "id,first_name,last_name,date_of_birth,username,section,{student_list}");
        
    }
    else
    {
        fptr = fopen(TEACHER_FILE, "a");
        if (fptr == NULL)
        {
            perror("Error opening student file for appending");
            return 0;
        }
    }

    // print the teacherInfoCsv into file
    fprintf(fptr, "%s\n", teacherInfoCsv); 
    fclose(fptr);
    return 1;
}

int getStudentById(int id, Student *student)
{
    FILE *fptr;
    int numOfReadVal = 0;
    if(student == NULL || id < ID_INIT_VAL)
    {
        printf("ERROR: ID %d is invalid or student didn't initialized", id);
        return 0;
    }

    fptr = fopen(STUDENT_FILE, "r");

    if(fptr == NULL)
    {
        printf("ERROR: File not found!");
        return 0;
    }
    

}

int getTeacherById(int id, Teacher *teacher);

int getAllStudentByTeacherId(int id, Student *studentList);

void editStudent(int id, Student *student);
void editTeacher(int id, Teacher *teacher);

int logCurrentUser(int id, char *username);
void getCurrentLogged(char *currUser); 

int savePassword(int id, char *password);
int getPasswordById(int id, char *password);
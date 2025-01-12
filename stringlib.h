#pragma once

#include "userfilelib.h"

typedef struct Table
{
    char header[MAX_FILE_LINE][STR_CVS_LEN_IN];
    char columnValue[MAX_FILE_LINE][STR_CVS_LEN_IN];
    int column;
    int *columnWidth;
    int textAlignment; // left -1, center 0, right 1
    int spaceAroundtext;

} Table;


void strToCsvFormat(char strArr[MAX_FILE_LINE][STR_CVS_LEN_IN], char *delimiter, char *strInCsvFormat, int bufferSize);
int strSplit(char *input, char output[MAX_FILE_LINE][STR_CVS_LEN_IN], char *delimiter);
void strtrim(char *in); 
char* fgetsm(char *in, int size, FILE *file) ;
float roundToDecimal(float num, int decimalPlaces);
void initStudent(Student *student);
void initStudentList(StudentList *studentList); 
void initTeacher(Teacher *teacher);
void studentToCsv(Student *student, char studentInCsv[STR_CVS_LEN_OUT]);
void teacherToCsv(Teacher *teacher, char teacherInCsv[STR_CVS_LEN_OUT]);
int csvToStudent(char *studentInCsv, Student *student);
int csvToTeacher(char *studentInCsv, Teacher *teacher);
void printRepeat(char *ch, int times); // to remove
void printHeader(Table *table); // to remove
void printStudent(Student *student, int size);


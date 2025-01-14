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

typedef enum TextColor
{
    RED_TEXT = 31,
    GREEN_TEXT = 32,
    YELLOW_TEXT = 33,
    BLUE_TEXT = 34
} TextColor;

void setColor(TextColor colorCode);
void resetColor();
void printfSUCCESS(char *message);
void printfERROR(char *message);
void printfWARNNING(char *message);
void fgetsmINPUT();
void printNewLine(int numOfNewLine);
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
void printStudent(Student *student, int size);


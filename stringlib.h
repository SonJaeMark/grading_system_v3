#pragma once

#include "userfilelib.h"

void strToCsvFormat(char strArr[MAX_FILE_LINE][STR_CVS_LEN_IN], char *delimiter, char *strInCsvFormat, int bufferSize);
int strSplit(char *input, char output[MAX_FILE_LINE][STR_CVS_LEN_IN], char *delimiter);
void strtrim(char *in); 
void fgetsm(char *in, int size);
float roundToDecimal(float num, int decimalPlaces);
void initStudent(Student *student);
void initStudentList(StudentList *studentList); 
void initTeacher(Teacher *teacher);
void studentToCsv(Student *student, char studentInCsv[STR_CVS_LEN_OUT]);
void teacherToCsv(Teacher *teacher, char teacherInCsv[STR_CVS_LEN_OUT]);
int csvToStudent(char *studentInCsv, Student *student);
int csvToTeacher(char *studentInCsv, Teacher *teacher);
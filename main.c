#include <stdio.h>
#include <string.h>

#include "stringlib.h"
#include "userfilelib.h"

int main()
{
    char teacherInCsv[STR_CVS_LEN_OUT] =  "240000,Tony,Stark,5/29/1970,Ironman,0,0,0,0,0,0,0,0,0,0";
    char teacherInCsvOUT[STR_CVS_LEN_OUT];

    Teacher teacher;
    // initTeacher(&teacher); // init

    csvToTeacher(teacherInCsv, &teacher); // convert csv to teacher
    teacherToCsv(&teacher, teacherInCsvOUT); // teacher to csv

    printf("teacherInCsvOUT: %s\n", teacherInCsvOUT);
    printf("   teacherInCsv: %s\n", teacherInCsv);
    

    char strArr[256][64] = {
        "240000", "Tony,Stark", "5/29/1970", "Ironman", "240001", "240007", 
        "240008", "240009", "240010", "240001", "240007", "240008", "240009",
        "240010"
    };
    char *delimiter = ",";
    int bufferSize = STR_CVS_LEN_OUT;
    char strInCsvFormat[STR_CVS_LEN_OUT]; 

    strToCsvFormat(strArr, delimiter, strInCsvFormat, bufferSize);
    printf(" strInCsvFormat: %s\n", strInCsvFormat);

    

    char studentInCsv[STR_CVS_LEN_OUT] = "240010,Steve,Rogers,7/4/2001,captain2001,12C,100.00,100.00,100.00,100.00,100.00,100.00,100.00"; 
    char studentInCsvOUT[STR_CVS_LEN_OUT];
    // 94.00,95.00,96.00,97.00,98.00,99.00,100.000
    Student stud;
    initStudent(&stud);

    csvToStudent(studentInCsv, &stud); // convert csv to stud
    studentToCsv(&stud, studentInCsvOUT); // stud to csv

    printf("   studentInCsv: %s\n", studentInCsv);
    printf("studentInCsvOUT: %s\n", studentInCsvOUT);
    return 0;
}
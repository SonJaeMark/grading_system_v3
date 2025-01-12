#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "userfilelib.h"
#include "stringlib.h"

#define STUDENT_FILE "ffile_student.txt"
#define TEACHER_FILE "ffile_teacher.txt"
#define ID_VAL_FILE "ffile_id_val.txt"
#define TEMP_FILE "ffile_temp.txt"
#define LOG_FILE "ffile_log.txt"
#define PASSWORD_FILE "ffile_password.txt"
#define ID_INIT_VAL 240000
#define STUDENT_CSV_VAL_COUNT 13
#define TEACHER_CSV_VAL_COUNT 16
#define ID_FIELD "id"
#define FULLNAME_FIELD "fullname"
#define USERNAME_FIELD "username"
#define SECTION_FIELD "section"
#define GET_ALL "getall"


/**
 * @brief Generates a unique ID by reading and updating a stored value.
 *
 * This function reads a stored ID value from a file, increments it, and writes the updated value back to the file.
 * If the file does not exist, it will create the file and initialize the ID to a default value (240000).
 *
 * @return int The generated unique ID.
 */
int generateId()
{
    FILE *fptr;
    int currIdVal;           /**< Current ID value read from the file */
    char buff[STR_CVS_LEN_IN];   /**< Buffer to store the read ID as a string */

    // Open the file for reading
    fptr = fopen(ID_VAL_FILE, "r");

    // If the file doesn't exist, create it and initialize the ID value
    if (fptr == NULL)
    {
        fptr = fopen(ID_VAL_FILE, "w");
        if (fptr == NULL) 
        {
            // If unable to create or open the file, print an error and return -1
            printf("Error creating ID file.\n");
            return -1;
        }

        /**< Initial ID value if the file does not exist */
        fprintf(fptr, "%d", ID_INIT_VAL);  // Write the initial ID value to the file
        currIdVal = ID_INIT_VAL;            // Set the current ID value to the initial value
    }
    else
    {
        // If the file exists, read the current ID value and increment it
        fgets(buff, STR_CVS_LEN_IN, fptr);
        currIdVal = atoi(buff) + 1;  // Increment the read ID value

        // Reopen the file for writing and update the ID value
        fptr = fopen(ID_VAL_FILE, "w");
        if (fptr == NULL) 
        {
            // If unable to open the file for writing, print an error and return -1
            printf("Error opening ID file for writing.\n");
            return -1;
        }

        fprintf(fptr, "%d", currIdVal);  // Write the updated ID value back to the file
    }

    fclose(fptr);  // Close the file

    return currIdVal;  // Return the generated ID value
}


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


/**
 * @brief Reads a file containing teacher or student records and retrieves matching entries based on a target field.
 *
 * This function reads data from a file containing either teacher or student information.
 * It searches for records matching the specified target field and value or retrieves all records when `GET_ALL` is specified.
 *
 * @param[in]  isTeacher    Flag indicating whether to read the teacher file (1) or student file (0).
 * @param[in]  targetField  The field to search for (e.g., ID_FIELD, FULLNAME_FIELD, USERNAME_FIELD, SECTION_FIELD, GET_ALL).
 * @param[in]  target       The value to search for within the specified field (ignored when `GET_ALL` is used).
 * @param[out] teacher      Pointer to a `Teacher` structure or array to store the result(s) if `isTeacher` is 1.
 * @param[out] student      Pointer to a `Student` structure or array to store the result(s) if `isTeacher` is 0.
 *
 * @return The line number of the first match, the number of matches (for ID_FIELD, FULLNAME_FIELD, USERNAME_FIELD, SECTION_FIELD),
 *         or the number of result found in GET_ALL, or 0 if no matches are found or an error occurs.
 *         
 *
 * @note The function assumes the existence of helper functions `csvToTeacher`, `csvToStudent`,
 *       and `fgetsm`, as well as macros for file paths and field identifiers.
 * 
 * @warning 
 * - Ensure the provided `teacher` and `student` pointers are valid and properly allocated.
 * - If `GET_ALL` is used, ensure the provided pointers can hold all records in the file.
 *
 * @details
 * - **ID_FIELD**: Searches for a specific ID and retrieves the corresponding record.
 * - **FULLNAME_FIELD**: Searches for a substring match in the full name and retrieves all matching records.
 * - **USERNAME_FIELD**: Searches for a specific username and retrieves the corresponding record.
 * - **SECTION_FIELD**: Searches for a specific section and retrieves the corresponding record.
 * - **GET_ALL**: Retrieves all records in the file.
 *
 * @code
 * // Example Usage:
 * Teacher teacherArray[MAX_RECORDS];
 * int result = readFileContent(1, GET_ALL, NULL, teacherArray, NULL);
 * if (result > 0) {
 *     printf("Retrieved %d teacher records.\n", result);
 * }
 * @endcode
 *
 * @example
 * char targetField[] = ID_FIELD;
 * char targetValue[] = "101";
 * Teacher teacher;
 * int result = readFileContent(1, targetField, targetValue, &teacher, NULL);
 * if (result > 0) {
 *     printf("Found teacher record on line %d.\n", result);
 * }
 */
int readFileContent(int isTeacher, char *targetField, char *target, Teacher *teacher, Student *student)
{
    // Validate that the output pointers are initialized
    if (teacher == NULL || student == NULL)
    {
        printf("Teacher or Student not initialized correctly!\n");
        return 0;
    }

    // Open the appropriate file based on the isTeacher flag
    FILE *fptr = fopen(isTeacher ? TEACHER_FILE : STUDENT_FILE, "r");
    if (fptr == NULL)
    {
        printf("File not found!\n");
        return 0;
    }

    // Buffers and variables for file reading and matching
    char contentBuff[STR_CVS_LEN_OUT];
    char fullnameBuff[STR_CVS_LEN_OUT];
    int id, line = 1, numberOfMatchResult = 0, returnValue = 0, readResult = 0;

    // Skip the header line of the CSV file
    fgetsm(contentBuff, STR_CVS_LEN_IN, fptr);

    // Read the file line by line
    do
    {
        line++;
        fgetsm(contentBuff, STR_CVS_LEN_IN, fptr);
        

        if (isTeacher)
        {
            Teacher teacherBuff;
            // Convert the current line to a Teacher structure
            csvToTeacher(contentBuff, &teacherBuff);

            // Match by ID
            if (strcmp(targetField, ID_FIELD) == 0 && sscanf(target, "%d", &id) && id == teacherBuff.id)
            {
                *teacher = teacherBuff;
                returnValue = line; // Store the line number of the match
                break; // Stop searching after the first match
            }
            // Match by full name (substring search)
            else if (strcmp(targetField, FULLNAME_FIELD) == 0)
            {
                snprintf(fullnameBuff, sizeof(fullnameBuff), "%s %s", teacherBuff.fname, teacherBuff.lname);
                if (strstr(fullnameBuff, target))
                {
                    teacher[numberOfMatchResult] = teacherBuff; // Store the match
                    returnValue = numberOfMatchResult++;        // Increment match count
                }
            }
            // Match by username
            else if (strcmp(targetField, USERNAME_FIELD) == 0 && strcmp(teacherBuff.userName, target) == 0)
            {
                *teacher = teacherBuff;
                returnValue = line;
                break;
            }
            // Match by section
            else if (strcmp(targetField, SECTION_FIELD) == 0 && strcmp(teacherBuff.section, target) == 0)
            {
                *teacher = teacherBuff;
                returnValue = line;
                break;
            }
            // Retrieve all records
            else if (strcmp(targetField, GET_ALL) == 0)
            {
                teacher[readResult] = teacherBuff; // Store the record
                returnValue = readResult++;       // Increment record count
            }
        }
        else
        {
            Student studentBuff;
            // Convert the current line to a Student structure
            csvToStudent(contentBuff, &studentBuff);

            // Match by ID
            if (strcmp(targetField, ID_FIELD) == 0 && sscanf(target, "%d", &id) && id == studentBuff.id)
            {
                *student = studentBuff;
                returnValue = line; // Store the line number of the match
                break; // Stop searching after the first match
            }
            // Match by full name (substring search)
            else if (strcmp(targetField, FULLNAME_FIELD) == 0)
            {
                snprintf(fullnameBuff, sizeof(fullnameBuff), "%s %s", studentBuff.fname, studentBuff.lname);
                if (strstr(fullnameBuff, target))
                {
                    student[numberOfMatchResult] = studentBuff; // Store the match
                    returnValue = numberOfMatchResult++;        // Increment match count
                }
            }
            // Match by username
            else if (strcmp(targetField, USERNAME_FIELD) == 0 && strcmp(studentBuff.userName, target) == 0)
            {
                *student = studentBuff;
                returnValue = line;
                break;
            }
            // Match by section
            else if (strcmp(targetField, SECTION_FIELD) == 0 && strcmp(studentBuff.section, target) == 0)
            {
                *student = studentBuff;
                returnValue = line;
                break;
            }
            // Retrieve all records
            else if (strcmp(targetField, GET_ALL) == 0)
            {
                student[readResult] = studentBuff; // Store the record
                returnValue = readResult++;       // Increment record count
            }
        }
    }
    while(!feof(fptr));

    fclose(fptr); // Close the file after reading
    return returnValue; // Return the match result
}


int getStudentById(int id, Student *student)
{
    FILE *fptr;
    Student studentBuffer;
    char studBuff[STR_CVS_LEN_OUT];
    int isFound = 0;
    int numOfReadVal = 0;

    if(student == NULL || id < ID_INIT_VAL)
    {
        printf("ID %d is invalid or student didn't initialized\n", id);
        return 0;
    }

    fptr = fopen(STUDENT_FILE, "r");

    if(fptr == NULL)
    {
        printf("File not found!");
        return 0;
    }
    
    fgets(studBuff, STR_CVS_LEN_OUT - 1, fptr); // reads header
    while (fgets(studBuff, STR_CVS_LEN_OUT - 1, fptr) != NULL)
    {
        csvToStudent(studBuff, &studentBuffer);
        if(id == studentBuffer.id)
        {
            csvToStudent(studBuff, student);
            isFound = 1;
            break;
        }
    }

    if(isFound == 0) printf("Student with ID %d not found!\n", id);
    fclose(fptr);
    return isFound;
}


int getStudentByIdV2(int id, Student *student)
{
    Teacher teacher;
    char idBuff[8];
    snprintf(idBuff, sizeof(idBuff), "%d", id);
    readFileContent(0, ID_FIELD, idBuff, &teacher, student);
}

int getTeacherById(int id, Teacher *teacher)
{
    FILE *fptr;
    Teacher teacherBuffer;
    char teachBuff[STR_CVS_LEN_OUT];
    int isFound = 0;
    int numOfReadVal = 0;

    if(teacher == NULL || id < ID_INIT_VAL)
    {
        printf("ID %d is invalid or teacher didn't initialized\n", id);
        return 0;
    }

    fptr = fopen(TEACHER_FILE, "r");

    if(fptr == NULL)
    {
        printf("File not found!\n");
        return 0;
    }
    
    fgets(teachBuff, STR_CVS_LEN_OUT - 1, fptr); // reads header
    while (fgets(teachBuff, STR_CVS_LEN_OUT - 1, fptr) != NULL)
    {
        csvToTeacher(teachBuff, &teacherBuffer);
        if(id == teacherBuffer.id)
        {
            csvToTeacher(teachBuff, teacher);
            isFound = 1;
            break;
        }
    }

    if(isFound == 0) printf("Teacher with ID %d not found!\n", id);
    fclose(fptr);
    return isFound;
}

int getAllStudentByTeacherId(int id, Student *studentList)
{
    Teacher teacher;
    char teacherInCsv[STR_CVS_LEN_OUT];
    int result = 0;

    getTeacherById(id, &teacher);

    for (int i = 0; i < MAX_STUDENT_COUNT; i++)
    {
        result += getStudentById(teacher.studentsList.studentId[i], &studentList[i]);
    }
    return result;
}

int editStudent(int id, Student *student)
{
    FILE *fptr;
    FILE *fptrtemp;
    Student studentBuffer;
    char studentInCsv[STR_CVS_LEN_OUT];
    char studentInCsvBuff[STR_CVS_LEN_OUT];
    char editedStudentInCsv[STR_CVS_LEN_OUT];

    initStudent(&studentBuffer); // init student
    studentToCsv(student, studentInCsv);

    fptr = fopen(STUDENT_FILE, "r");

    if(fptr == NULL)
    {
        printf("Error in opening file for editting student info!\n");
        return 0;
    }
    

    fptrtemp = fopen(TEMP_FILE, "w");

    if(fptrtemp == NULL)
    {
        printf("Error in opening file for editting student info!\n");
        return 0;
    }

    fprintf(fptrtemp, "id,first_name,last_name,date_of_birth,username,section,grades(MATH,SCI,ENG,FIL,HISTORY,PE,AVE)\n");

    fgetsm(studentInCsvBuff, STR_CVS_LEN_OUT, fptr); // read header
    do
    {
        fgetsm(studentInCsvBuff, STR_CVS_LEN_OUT, fptr);
        if(strcmp(studentInCsvBuff, "") == 0 || studentInCsvBuff[0] == '\0') break;
        csvToStudent(studentInCsvBuff, &studentBuffer);

        if (id == studentBuffer.id)
        {
            fprintf(fptrtemp, "%s\n", studentInCsv);
        }
        else
        {
            fprintf(fptrtemp, "%s\n", studentInCsvBuff);
        }

    } while (!feof(fptr));
    fclose(fptrtemp);
    fclose(fptr);


    fptrtemp = fopen(TEMP_FILE, "r");
    fptr = fopen(STUDENT_FILE, "w");

    return copyFile(fptr, fptrtemp);
}

int editTeacher(int id, Teacher *teacher)
{
    FILE *fptr;
    FILE *fptrtemp;
    Teacher teacherBuffer;
    char teacherInCsv[STR_CVS_LEN_OUT];
    char teacherInCsvBuff[STR_CVS_LEN_OUT];
    char editedTeacherInCsv[STR_CVS_LEN_OUT];

    initTeacher(&teacherBuffer); // init student
    teacherToCsv(teacher, teacherInCsv);

    fptr = fopen(TEACHER_FILE, "r");

    if(fptr == NULL)
    {
        printf("Error in opening file for editting teacher info!\n");
        return 0;
    }

    fptrtemp = fopen(TEMP_FILE, "w");

    if(fptrtemp == NULL)
    {
        printf("Error in opening file for editting teacher info!\n");
        return 0;
    }

    fprintf(fptrtemp, "id,first_name,last_name,date_of_birth,username,section,{student_list}\n");

    fgetsm(teacherInCsvBuff, STR_CVS_LEN_OUT, fptr); // read header
    do
    {
        fgetsm(teacherInCsvBuff, STR_CVS_LEN_OUT, fptr);
        if(strcmp(teacherInCsvBuff, "") == 0 || teacherInCsvBuff[0] == '\0') break;
        csvToTeacher(teacherInCsvBuff, &teacherBuffer);

        if (id == teacherBuffer.id)
        {
            fprintf(fptrtemp, "%s\n", teacherInCsv);
        }
        else
        {
            fprintf(fptrtemp, "%s\n", teacherInCsvBuff);
        }

    } while (!feof(fptr));
    fclose(fptrtemp);
    fclose(fptr);


    fptrtemp = fopen(TEMP_FILE, "r");
    fptr = fopen(TEACHER_FILE, "w");

    return copyFile(fptr, fptrtemp);
}

int copyFile(FILE *fptrTo, FILE *fptrFrom)
{
    char c;

    if(fptrTo == NULL || fptrFrom == NULL)
    {
        printf("Copying file failed, file not found\n");
        return 0;
    }

    while ((c = fgetc(fptrFrom)) != EOF)
    {
        fputc(c, fptrTo);
    }
    
    fclose(fptrFrom);
    fclose(fptrTo);
    return 1;
}

int logCurrentUser(int id, char *username)
{
    FILE *fptr;
    char idstr[10];
    char loggedUser[STR_CVS_LEN_IN];

    fptr = fopen(LOG_FILE, "w");
    

    if(fptr == NULL)
    {
        printf("Unable to log user, failed in creating file\n");
        return 0;
    }
    snprintf(idstr, sizeof(idstr), "%d", id); // int to str
    strcpy(loggedUser, idstr);
    strcat(loggedUser, "-");
    strcat(loggedUser, username);

    fprintf(fptr, "%s", loggedUser);
    fclose(fptr);
    return 1;
}

int getCurrentLogged(int *id, char *username)
{
    FILE *fptr;
    char buffer[STR_CVS_LEN_IN];
    char userLogsBuffer[MAX_FILE_LINE][STR_CVS_LEN_IN];
    char *delim = "-";

    fptr = fopen(LOG_FILE, "r");

    if(fptr == NULL)
    {
        printf("No file of user logs found!\n");
        return 0;
    }

    fgetsm(buffer, STR_CVS_LEN_IN, fptr);
    strSplit(buffer, userLogsBuffer, delim);

    sscanf(userLogsBuffer[0], "%d", id);
    strcpy(username, userLogsBuffer[1]);

    fclose(fptr);
    return 1;
}

int savePassword(int id, char *password)
{
    FILE *fptr;
    char idstr[10];
    char passwordFormat[STR_CVS_LEN_IN];

    fptr = fopen(PASSWORD_FILE, "r");

    sprintf(idstr, "%d", id);
    strcpy(passwordFormat, idstr);
    strcat(passwordFormat, ",");
    strcat(passwordFormat, password);

    if (fptr == NULL)
    {
        fptr = fopen(PASSWORD_FILE, "w");
        fprintf(fptr, "id,password\n");
        fprintf(fptr, "%s\n", passwordFormat);
    }
    
    fptr = fopen(PASSWORD_FILE, "a");
    fprintf(fptr, "%s\n", passwordFormat);
    fclose(fptr);
    return 1;
}


int getPasswordById(int id, char *password)
{
    FILE *fptr;
    char idstr[10];
    char *delim = ",";
    char passwordFileContent[STR_CVS_LEN_OUT];
    char passwordBuffer[MAX_FILE_LINE][STR_CVS_LEN_IN];
    fptr = fopen(PASSWORD_FILE, "r");

    if(fptr == NULL)
    {
        printf("Password file not found!\n");
        strcpy(password, "AYAWW KO NAAAAAAAAAAAAAA!!!");
        return 0;
    }
    strcpy(password, "SUKO NAAAAAAAAAAAAAA!!!");
    sprintf(idstr, "%d", id);


    fgetsm(passwordFileContent, sizeof(passwordFileContent), fptr);
    do
    {
        fgetsm(passwordFileContent, sizeof(passwordFileContent), fptr);
        if(strcmp(passwordFileContent, "") == 0 || passwordFileContent[0] == '\0') break;

        strSplit(passwordFileContent, passwordBuffer, delim);
        if(strcmp(idstr, passwordBuffer[0]) == 0)
        {
            strcpy(password, passwordBuffer[1]);
            fclose(fptr);
            return 1;
        }
    } while (!feof(fptr));
    fclose(fptr);
    return 0;
}



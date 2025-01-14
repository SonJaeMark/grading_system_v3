#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "stringlib.h"
#include "userfilelib.h"
#include "userlib.h"
#include "studentlib.h" 

#define MATCH 1
#define UNIQUE 0
#define NUM_GRADES 6  // Define yung number ng subjects

/**
 * @brief Calculates the average grade of a student.
 *
 * This function retrieves individual subject grades from the Student structure, calculates the total,
 * and then computes the average by dividing the total grades by the number of subjects.
 *
 * @param student The Student object containing the grades to calculate the average.
 * @return float The calculated average grade.
 */
float getAve(Student student) {
    float gradesArray[NUM_GRADES]; // Array to hold individual grades
    float totalGrades = 0.0;      // Variable to store the total of all grades

    // Store individual grades in an array
    gradesArray[0] = student.grades.MATH;
    gradesArray[1] = student.grades.SCI;
    gradesArray[2] = student.grades.ENG;
    gradesArray[3] = student.grades.FIL;
    gradesArray[4] = student.grades.HIS;
    gradesArray[5] = student.grades.PE;

    // Calculate total grades
    for (int i = 0; i < NUM_GRADES; i++) {
        totalGrades += gradesArray[i];
    }

    // Calculate and return the average
    return totalGrades / NUM_GRADES;
}

/**
 * @brief Removes duplicate integers from an array and updates its size.
 *
 * This function sorts the array in ascending order, removes any duplicate values, 
 * and updates the size of the array to reflect the new unique values.
 *
 * @param data The array of integers to process.
 * @param size A pointer to the size of the array, which is updated to the new size.
 */
void removeDuplicate(int data[], int *size) {
    int indicator = 1;   // Flag to control the sorting loop
    int newSize = 0;     // New size of the array after duplicates are removed
    int tempOut[*size];  // Temporary array to store unique values
    int temp = 0;        // Variable for tracking the last unique number

    // Sort the array in ascending order
    while (indicator) {
        indicator = 0;
        for (int i = 0; i < *size - 1; i++) {
            if (data[i] > data[i + 1]) {
                // Swap elements if out of order
                int temp = data[i];
                data[i] = data[i + 1];
                data[i + 1] = temp;
                indicator = 1;
            }
        }
    }

    // Remove duplicates
    for (int i = 0; i < *size; i++) {
        if (temp != data[i]) {
            temp = data[i];
            tempOut[newSize] = data[i];
            newSize++;
        }
    }

    // Copy unique values back to the original array
    for (int i = 0; i < newSize; i++) {
        data[i] = tempOut[i];
    }

    // Update the size
    *size = newSize;
}

/**
 * @brief Finds unique elements in the compare array not present in the base array.
 *
 * This function identifies and retains only the unique elements in the compare array that do not exist in the base array.
 *
 * @param base The base array to compare against.
 * @param baseSize The size of the base array.
 * @param compare The array to filter for unique values.
 * @param compareSize A pointer to the size of the compare array, which is updated to the new size.
 */
void getUnique(int base[], int baseSize, int compare[], int *compareSize) {
    int newSize = 0;          // New size for the compare array after filtering
    int temp[*compareSize];   // Temporary array to store elements of the compare array

    // Copy elements of the compare array to a temporary array
    for (int i = 0; i < *compareSize; i++) {
        temp[i] = compare[i];
    }

    // Remove elements from temp that exist in the base array
    for (int i = 0; i < *compareSize; i++) {
        for (int j = 0; j < baseSize; j++) {
            if (temp[i] == base[j]) {
                temp[i] = 0; // Mark as duplicate
                break;
            }
        }
    }

    // Retain only the unique elements
    for (int i = 0; i < *compareSize; i++) {
        if (temp[i] != 0) {
            compare[newSize] = temp[i];
            newSize++;
        }
    }

    // Update the size of the compare array
    *compareSize = newSize;
}


/**
 * @brief Filters elements in the compare array that match elements in the base array.
 *
 * This function identifies elements in the compare array that are also present in the base array
 * and modifies the compare array to contain only the matching elements. The size of the compare 
 * array is updated accordingly.
 *
 * @param base The base array containing reference values.
 * @param baseSize The size of the base array.
 * @param compare The array to filter for matching values.
 * @param compareSize A pointer to the size of the compare array, which is updated to the new size.
 */
void getMatch(int base[], int baseSize, int compare[], int *compareSize) {
    int newSize = 0;         // Tracks the new size of the compare array after filtering
    int temp[*compareSize];  // Temporary array to store initial elements of the compare array

    // Copy elements of the compare array to a temporary array
    for (int i = 0; i < *compareSize; i++) {
        temp[i] = compare[i];
    }

    // Check for matching elements and store them in the compare array
    for (int i = 0; i < *compareSize; i++) {
        for (int j = 0; j < baseSize; j++) {
            if (temp[i] == base[j]) { // If a match is found
                compare[newSize] = temp[i];
                newSize++;
            }
        }
    }

    // Update the size of the compare array
    *compareSize = newSize;
}

/**
 * @brief Displays all students associated with the logged-in teacher.
 *
 * This function retrieves and displays all students linked to the teacher's ID. 
 * If a student is logged in, access to this function is denied.
 *
 * @param user A pointer to the User object containing teacher and student details.
 * @return int The number of students retrieved. Returns 0 if access is denied.
 */
int viewAllMyStudents(User *user) {
    int numOfStud = 0; // Number of students retrieved

    // Check if the logged-in user is a student
    if (user->student->id != 0) {
        printfWARNNING("You are not allowed to access this!");
        return 0;
    }

    // Retrieve all students linked to the teacher's ID
    numOfStud = getAllStudentByTeacherId(user->teacher->id, user->student);

    // Display the list of students
    for (int i = 0; i < numOfStud; i++) {
        printf("[%d] %d %s %s\n", i + 1, user->student[i].id, user->student[i].fname, user->student[i].lname);
    }

    // Reinitialize the student array to prevent residual data
    initStudent(user->student);

    return numOfStud;
}


int addStudentToClass(User *user)
{
    int succeedCount = 0;
    int currentStudCount = 0;
    int inputIdsHolderCount = MAX_STUDENT_COUNT;
    int studRetrievedCount = MAX_STUDENT_COUNT;
    int inputIdsSize = MAX_STUDENT_COUNT;
    char strBuffer[STR_CVS_LEN_OUT];
    int studRetrieved[studRetrievedCount];
    int inputIds[inputIdsSize];
    int inputIdsHolder[inputIdsHolderCount];
    int inputIdCount = 0;
    char buffer[STR_CVS_LEN_OUT];


    if(user->student->id != 0)
    {
        printfWARNNING("!!You are not allowed to access this!");
        return 0;
    }
    
    for(int i = 0; i < MAX_STUDENT_COUNT; i++)
    {
        if(user->teacher->studentsList.studentId[i] != 0)
        {
            studRetrieved[i] = user->teacher->studentsList.studentId[i];
            currentStudCount++;
            
        }
    }
    studRetrievedCount = currentStudCount;

   
    if(currentStudCount == 10)
    {
        printfWARNNING("Not able to add more studnet, you've reach the max studnet count allowable!");
        return 0;
    }

    for(int i = 0; i < MAX_STUDENT_COUNT; i++)
    {
        inputIds[i] = 0;
    }

 

    while (1)
    {
        resetColor();
        printf("Enter the ID of student you want to add in your class(separate with space if more than 1): ");
        fgetsm(strBuffer, STR_CVS_LEN_OUT, stdin);
        fgetsmINPUT();

        inputIdCount = sscanf(
            strBuffer, "%d %d %d %d %d %d %d %d %d %d", 
            &inputIds[0], &inputIds[1], &inputIds[2], &inputIds[3], &inputIds[4],
            &inputIds[5], &inputIds[6], &inputIds[7], &inputIds[8], &inputIds[9]
        );

        removeDuplicate(inputIds, &inputIdsSize);

        for (int i = 0; i < inputIdsSize; i++)
        {
            inputIdsHolder[i] = inputIds[i];
        }
        inputIdsHolderCount = inputIdsSize;

        getUnique(studRetrieved, studRetrievedCount, inputIds, &inputIdsSize);
        if(inputIdsSize + currentStudCount <= 10) break;
        printfWARNNING("Input ID/s exceed the max allowable student count.");
    }

    for (int i = 0; i < inputIdsSize; i++)
    {
        if(getStudentById(inputIds[i], user->student) && 
            strcpy(user->student->section, user->teacher->section) != NULL &&
            editStudent(user->student->id, user->student))
        {
            snprintf(buffer, sizeof(buffer) + 1, "Student %d successfuly added to your class!", inputIds[i]);
            printfSUCCESS(buffer);
            for(int j = 0; j < MAX_STUDENT_COUNT; j++)
            {
                if(user->teacher->studentsList.studentId[j] == 0)
                {
                    user->teacher->studentsList.studentId[j] = inputIds[i];
                    j = MAX_STUDENT_COUNT;
                } 
                
            }
            succeedCount++;
        }
        else
        {
            snprintf(buffer, sizeof(buffer) + 1, "!!!Student %d failed to add in your class!", inputIds[i]);
            printfERROR(buffer);
        }
    }

    getMatch(studRetrieved, studRetrievedCount, inputIdsHolder, &inputIdsHolderCount);
    for (int i = 0; i < inputIdsHolderCount; i++)
    {
        snprintf(buffer, sizeof(buffer) + 1, "!Srudent ID no.%d is already in your class.", inputIdsHolder[i]);
        printfWARNNING(buffer);
    }
    

    if(editTeacher(user->teacher->id, user->teacher))
    {
        snprintf(buffer, sizeof(buffer) + 1, "Added %d in your class.", succeedCount);
        printfSUCCESS(buffer);
        snprintf(buffer, sizeof(buffer) + 1, "you have %d in total in your class.\n", succeedCount + currentStudCount);
        printfSUCCESS(buffer);
    }
    else
    {
        printfERROR("Failed in editting teacher info, please contact the admin!");
        return 0;
    }
    
    initStudent(user->student);
    return succeedCount;
}

int removeStudentToClass(User *user)
{
   int succeedCount = 0;
    int currentStudCount = 0;
    int inputIdsHolderCount = MAX_STUDENT_COUNT;
    int studRetrievedCount = MAX_STUDENT_COUNT;
    int inputIdsSize = MAX_STUDENT_COUNT;
    char strBuffer[STR_CVS_LEN_OUT];
    int studRetrieved[studRetrievedCount];
    int inputIds[inputIdsSize];
    int inputIdsHolder[inputIdsHolderCount];
    int inputIdCount = 0;
    char buffer[STR_CVS_LEN_OUT];


    if(user->student->id != 0)
    {
        printfWARNNING("You are not allowed to access this!");
        return 0;
    }


    for(int i = 0; i < MAX_STUDENT_COUNT; i++)
    {
        if(user->teacher->studentsList.studentId[i] != 0)
        {
            studRetrieved[i] = user->teacher->studentsList.studentId[i];
            currentStudCount++;
            
        }
    }
    studRetrievedCount = currentStudCount;

    for(int i = 0; i < MAX_STUDENT_COUNT; i++)
    {
        inputIds[i] = 0;
    }

    while (1)
    {
        resetColor();
        printf("Enter the ID of student you want to add in your class(separate with space if more than 1): ");
        fgetsm(strBuffer, STR_CVS_LEN_OUT, stdin);
        fgetsmINPUT();

        inputIdCount = sscanf(
            strBuffer, "%d %d %d %d %d %d %d %d %d %d", 
            &inputIds[0], &inputIds[1], &inputIds[2], &inputIds[3], &inputIds[4],
            &inputIds[5], &inputIds[6], &inputIds[7], &inputIds[8], &inputIds[9]
        );

        removeDuplicate(inputIds, &inputIdsSize);

        for (int i = 0; i < inputIdsSize; i++)
        {
            inputIdsHolder[i] = inputIds[i];
        }
        inputIdsHolderCount = inputIdsSize;

        getMatch(studRetrieved, studRetrievedCount, inputIds, &inputIdsSize);
        if(currentStudCount - inputIdsSize >= 0) break;
        printfWARNNING("Input ID/s exceed the total student count.");
    }


    for (int i = 0; i < inputIdsSize; i++)
    {
        if(getStudentById(inputIds[i], user->student) && 
            strcpy(user->student->section, "A0") != NULL &&
            editStudent(user->student->id, user->student))
        {
            snprintf(buffer, sizeof(buffer) + 1, "Student %d successfuly removed to your class!", inputIds[i]);
            printfSUCCESS(buffer);

            for(int j = 0; j < MAX_STUDENT_COUNT; j++)
            {
                if(user->teacher->studentsList.studentId[j] == inputIds[i])
                {
                    user->teacher->studentsList.studentId[j] = 0;
                    j = MAX_STUDENT_COUNT;
                } 
                
            }
            succeedCount++;
        }
        else
        {
            snprintf(buffer, sizeof(buffer) - 1, "Student %d failed to remove in your class!", inputIds[i]);
            printfERROR(buffer);
        }
    }

    getUnique(studRetrieved, studRetrievedCount, inputIdsHolder, &inputIdsHolderCount);
    for (int i = 0; i < inputIdsHolderCount; i++)
    {
        snprintf(buffer, sizeof(buffer) - 1, "Student ID no.%d is not in your class.", inputIdsHolder[i]);
    }


    if(editTeacher(user->teacher->id, user->teacher))
    {
        snprintf(buffer, sizeof(buffer) - 1, "Removed %d in your class.", succeedCount);
        printfSUCCESS(buffer);
        snprintf(buffer, sizeof(buffer) - 1, "You have %d in total in your class.", currentStudCount - succeedCount);
        printfSUCCESS(buffer);
    }
    else
    {
        printfERROR("Failed in editting teacher info, please contact the admin!");
        return 0;
    }
    

    initStudent(user->student);
    return succeedCount;
}

void viewGradesOfStudentById(User *user)
{
    int isexit = 0;
    int inputIdsSize = MAX_STUDENT_COUNT;
    char strBuffer[STR_CVS_LEN_OUT];
    int inputIds[inputIdsSize];
    int inputIdCount = 0;
    char buffer[STR_CVS_LEN_OUT];
    

    if(user->student->id != 0)
    {
        printfWARNNING("You are not allowed to access this!");
        return;
    }

    while (1)
    {
        resetColor();
        printf("Enter the ID of student you want to see grades: ");
        fgetsm(strBuffer, STR_CVS_LEN_OUT, stdin);
        fgetsmINPUT();

        inputIdCount = sscanf(strBuffer, "%d", &inputIds[0]);

        for (int i = 0; i < MAX_STUDENT_COUNT; i++)
        {
            if(inputIds[0] == user->teacher->studentsList.studentId[i])
            {
                isexit = 1;
            }
        }
        if(isexit) break;

        snprintf(buffer, sizeof(buffer) - 1, "ID no.%d is not in you class.", inputIds[0]);
        printfWARNNING(buffer);
    }

    getStudentById(inputIds[0], user->student);
    viewMyGrades(user);
    initStudent(user->student);
}

void giveGrades(User *user)
{
    int isexit = 0;
    int inputIdsSize = MAX_STUDENT_COUNT;
    char strBuffer[STR_CVS_LEN_OUT];
    int inputIds[inputIdsSize];
    int inputIdCount = 0;
    float grades[7];
    char buffer[STR_CVS_LEN_OUT];

    if(user->student->id != 0)
    {
        printfWARNNING("!!You are not allowed to access this!\n");
        return;
    }

    while (1)
    {
        resetColor();
        printf("Enter the ID of student you want to see grades: ");
        fgetsm(strBuffer, STR_CVS_LEN_OUT, stdin);
        fgetsmINPUT();

        inputIdCount = sscanf(strBuffer, "%d", &inputIds[0]);

        for (int i = 0; i < MAX_STUDENT_COUNT; i++)
        {
            if(inputIds[0] == user->teacher->studentsList.studentId[i])
            {
                isexit = 1;
            }
        }
        if(isexit) break;

        snprintf(buffer, sizeof(buffer) - 1, "!!ID no.%d is not in you class.", inputIds[0]);
        printfWARNNING(buffer);
    }

    getStudentById(inputIds[0], user->student);

    printf("Enter grades per subject\n");
    printf("                                            MATH SCI ENG FIL HIS PE\n");
    printf("separate with space put or 0 to skip sub-->");
    fgetsm(strBuffer, STR_CVS_LEN_OUT, stdin);
    fgetsmINPUT();

    sscanf(strBuffer, "%f %f %f %f %f %f", 
        &grades[0], &grades[1], &grades[2], &grades[3], &grades[4], &grades[5]
    );

    for(int i = 0; i < NUM_GRADES; i++)
    {
        printf("%.2f\n", grades[i]);
    }

    user->student->grades.MATH = grades[0];
    user->student->grades.SCI = grades[1];
    user->student->grades.ENG = grades[2];
    user->student->grades.FIL = grades[3];
    user->student->grades.HIS = grades[4];
    user->student->grades.PE = grades[5];

    user->student->grades.AVE = getAve(user->student[0]);

    if(editStudent(inputIds[0], user->student))
    {
        printfSUCCESS("Grades successfuly given!");
        printf("Do you want to see grades [y]Yes || [n]No? ");
        fgetsm(strBuffer, STR_CVS_LEN_OUT, stdin);
        fgetsmINPUT();
        if(strcmp(strBuffer, "y") == 0)
        {
            viewMyGrades(user);
        }
    }
    else
    {
        printfERROR("Error in giving grades!");
    }
    initStudent(user->student);
}


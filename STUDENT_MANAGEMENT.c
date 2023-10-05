//GROUP 43 FINAL PROJECT
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <dos.h>
#include <string.h>
#include "info.h"

//Editing console following xy-coordinate
void gotoxy(int x, int y)
{
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}
void print_list(struct Student *students, int);
void max_overall(struct Student *students, int);
void min_overall(struct Student *students, int);
void max_BG_results(struct Student *students, int);
void INCLUDE(struct Student *students, int);
void first_name(struct Student *students, int);
void searching(struct Student *students, int);
void sorting(struct Student *students, int);
void menu(struct Student *students, int);
void exit_menu();

int main(void)
{
    //Using Console
    system("color 3");
    system("cls");

    int MAX_STUDENTS;

    gotoxy(31,4);
    printf("\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB STUDENT MANAGEMENT \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB3");
	Sleep(1000);
    gotoxy(31,6);
    printf("\xB3\xDB\xDB\xDB\xDB\xDB ENTER NUMBER OF STUDENT(0-1000): ");
    scanf("%d", &MAX_STUDENTS);

    ///Checking the condition that is whether out of given range or not.
	//Looping until input satisfies the condition.
    while(MAX_STUDENTS > 1000 || MAX_STUDENTS < 1)
    {
        system("cls");
        gotoxy(31,4);
        printf("Invalid");
        Sleep(1000);
        gotoxy(31,6);
        printf("\xB3\xDB\xDB\xDB\xDB\xDB ENTER NUMBER OF STUDENT(0-1000): ");
        scanf("%d", &MAX_STUDENTS);
    }

    struct Student students[MAX_STUDENTS];

    //Looping by using for loop to declare each of the element of array
    for(int i = 0; i < MAX_STUDENTS; i++)
    {
		gotoxy(25,7);
		printf("Student No.%d", i + 1);

		gotoxy(25,8);
		printf("Student ID: \t");
		gotoxy(55,8);
		scanf("%s", &students[i].ID);
		fflush(stdin);

        //using regex, it works like %s but is more useful
		gotoxy(25,9);
		printf("Full name(First & Last name): \t");
		gotoxy(55,9);
		scanf("%[0-9A-Za-z ]s", &students[i].fullName);
		fflush(stdin);

		gotoxy(25,10);
		printf("Date of Birth (dd/mm/yyyy): \t");
		gotoxy(55,10);
		scanf("%d/%d/%d", &students[i].Bdate, &students[i].Bmonth, &students[i].Byear);

		gotoxy(25,11);
		printf("Linear Algebra result: \t");
		gotoxy(55,11);
		scanf("%f", &students[i].algebraScore);

		gotoxy(25,12);
		printf("Calculus result: \t");
		gotoxy(55,12);
		scanf("%f", &students[i].calculusScore);

		gotoxy(25,13);
		printf("Basic Programming result: \t");
		gotoxy(55,13);
		scanf("%f", &students[i].basicprogScore);

		students[i].overallScore = (students[i].algebraScore + students[i].calculusScore + students[i].basicprogScore) / 3;

        system("cls");
    }

    menu(students, MAX_STUDENTS);
    getch();
    return 0;

}

void print_list (struct Student *students, int MAX_STUDENTS)
{
    int flag = 0;
    system("cls");
    gotoxy(31,2);
	printf("\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB LIST SECTION OPENED \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB3\n\n");

    printf("\n\t+------------+--------------------------------------+------------+-------+-------+-------+-------+");
    printf("\n\t| Student ID |               Full Name              |     DoB    | L.Alg |  Cal  | BProg |Overall|");
    printf("\n\t+------------+--------------------------------------+------------+-------+-------+-------+-------+");
    for (int i = 0; i < MAX_STUDENTS; i++)
    {
        printf("\n\t| %-10s | %-36s | %s%d/%s%d/%d | %-5.1f | %-5.1f | %-5.1f | %-5.1f |",
               students[i].ID, students[i].fullName,
               //Editing DOB following format dd/mm/yyyy
               (students[i].Bdate >= 10) ? "" : "0", students[i].Bdate,
               (students[i].Bmonth >= 10) ? "" : "0", students[i].Bmonth, students[i].Byear,
               students[i].algebraScore,
               students[i].calculusScore,
               students[i].basicprogScore,
               students[i].overallScore);
    printf("\n\t+------------+--------------------------------------+------------+-------+-------+-------+-------+");
    }

    FILE *fptr;
    fptr = fopen("list.txt", "w+");
    fprintf(fptr,"                            LIST SECTION OPENED                            \n\n");

    fprintf(fptr,
            "\n+------------+------------------------------------------+------------+-------+-------+-------+-------+");
    fprintf(fptr,
            "\n| Student ID |                 Full Name                |     DoB    | L.Alg |  Cal  | BProg |Overall|");
    fprintf(fptr,
            "\n+------------+------------------------------------------+------------+-------+-------+-------+-------+");
    for (int i = 0; i < MAX_STUDENTS; i++)
    {
        fprintf(fptr, "\n| %-10s | %-40s | %s%d/%s%d/%d | %-5.1f | %-5.1f | %-5.1f | %-5.1f |",
                students[i].ID, students[i].fullName,
               (students[i].Bdate >= 10) ? "" : "0", students[i].Bdate,
               (students[i].Bmonth >= 10) ? "" : "0", students[i].Bmonth, students[i].Byear,
               students[i].algebraScore,
               students[i].calculusScore,
               students[i].basicprogScore,
               students[i].overallScore);
        fprintf(fptr,
                "\n+------------+------------------------------------------+------------+-------+-------+-------+-------+");
    }
    fclose(fptr);

    flag=1;
	Sleep(1000);
	gotoxy(18,13 + MAX_STUDENTS);
	printf("Enter y for menu option.");

	while(getch() == 'y')
	{
		menu(students, MAX_STUDENTS);
	}
}

void max_overall(struct Student *students, int MAX_STUDENTS)
{
    int max = 0; // Take the first student as the default value
    for (int i = 1; i < MAX_STUDENTS; i++)
    {
        if (students[i].overallScore > students[max].overallScore)
            max = i;
    }

    printf("\nStudent(s) with highest GPA (%.1f): ", students[max].overallScore);
    printf("%s (%s)", students[max].fullName, students[max].ID);

    // Loop until other students with the same GPA is found
    for (int i = max + 1; i < MAX_STUDENTS; i++)
    {
        if (students[i].overallScore == students[max].overallScore)
            printf(", %s (%s)", students[i].fullName, students[i].ID);
    }
}

void min_overall(struct Student *students, int MAX_STUDENTS)
{
    int min = 0; // Take the first student as the default value
    for (int i = 1; i < MAX_STUDENTS; i++)
    {
        if (students[i].overallScore < students[min].overallScore)
            min = i;
    }

    printf("\nStudent(s) with lowest GPA (%.1f): ", students[min].overallScore);
    printf("%s (%s)", students[min].fullName, students[min].ID);

    // Loop until other students with the same GPA is found
    for (int i = min + 1; i < MAX_STUDENTS; i++)
    {
        if (students[i].overallScore == students[min].overallScore)
            printf(", %s (%s)", students[i].fullName, students[i].ID);
    }
}

void max_BG_results(struct Student *students, int MAX_STUDENTS)
{
    int max = 0; // Take the first student as the default value
    for (int i = 1; i < MAX_STUDENTS; i++)
    {
        if (students[i].basicprogScore > students[max].basicprogScore)
            max = i;
    }

    printf("\nStudent(s) with highest Basic Programming final result (%.1f): ", students[max].basicprogScore);
    printf("%s (%s)", students[max].fullName, students[max].ID);

    for (int i = max + 1; i < MAX_STUDENTS; i++)
    {
        if (students[i].basicprogScore == students[max].basicprogScore)
            printf(", %s (%s)", students[i].fullName, students[i].ID);
    }
}

void INCLUDE(struct Student *students, int MAX_STUDENTS)
{
    int flag = 0;
    system("cls");
    gotoxy(31,4);
    printf("\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB LOADING OPTION... \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB3\n\n");
    Sleep(1500);

    system("cls");
    gotoxy(31,4);
    printf("\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB SUGGESTED LIST \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB3\n\n");

    max_overall(students, MAX_STUDENTS);
    min_overall(students, MAX_STUDENTS);
    max_BG_results(students, MAX_STUDENTS);

    flag = 1;
	Sleep(1000);
	gotoxy(18,13);
	printf("Enter y for menu option.");

	while(getch() == 'y')
	{
		menu(students, MAX_STUDENTS);
	}
}

void first_name(struct Student *students, int MAX_STUDENTS)
{
    system("cls");

    int flag = 0;
    char src[50];

    gotoxy(31,2);
    printf("\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB LIST SECTION OPENED \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB3\n\n");

    for(int i = 0, j = 4; i < MAX_STUDENTS, j < 4 + MAX_STUDENTS; i++, j++)
    {

        strcpy(src,students[i].fullName);
        const char delimiters[] = " ";
        char *token = strtok(src, delimiters);

        gotoxy(31, j);
        printf("\xDB\xDB %d.[%s]: \t", i + 1, students[i].ID); //print token
        gotoxy(48, j);
        printf("\xDB\xDB[%s]", token); //print token
    }

    flag = 1;
	Sleep(1000);
	gotoxy(18,13);
	printf("Enter y for menu option.");

	while(getch() == 'y')
	{
		menu(students, MAX_STUDENTS);
	}
}

void searching (struct Student *students, int MAX_STUDENTS)
{
    char ID_temp[10];
    int flag = 0;
    int res;

    system("cls");
	fflush(stdin);

	gotoxy(18,2);
	printf("\xDB\xDB\xDB Enter the ID of the person you want to see the detail: ");
	gets(ID_temp);
	fflush(stdin);
    for (int i = 0; i < MAX_STUDENTS; i++)
    {
        res=strcmp(students[i].ID,ID_temp);
	    if(res == 0)
	    {
            gotoxy(39,4);
            printf("\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB RECORD FOUND \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB3");

                gotoxy(28,5);
                printf("\t----------------------------------------");
            gotoxy(31,6.5);
            printf("\t\xB3\xB2\xB2\xB2 Student ID:\t%s", students[i].ID);

            gotoxy(31,7);
            printf("\t\xB3\xB2\xB2\xB2 Full name:\t%s", students[i].fullName);

            gotoxy(31,8);
            printf("\t\xB3\xB2\xB2\xB2 Date of birth:\t%d/%d/%d", students[i].Bdate, students[i].Bmonth, students[i].Byear);

            gotoxy(31,9);
            printf("\t\xB3\xB2\xB2\xB2 Linear Algebra result:\t%.1f", students[i].algebraScore);

            gotoxy(31,10);
            printf("\t\xB3\xB2\xB2\xB2 Calculus result:\t%.1f", students[i].calculusScore);

            gotoxy(31,11);
            printf("\t\xB3\xB2\xB2\xB2 Basic Programming result:\t%.1f", students[i].basicprogScore);

            gotoxy(31,12);
            printf("\t\xB3\xB2\xB2\xB2 The overall result:\t%.1f", students[i].overallScore);

                gotoxy(28,13);
                printf("\t----------------------------------------");

            flag = 1;
			Sleep(1000);
			gotoxy(18,16);
			printf("Enter y for menu option.");

			while(getch() == 'y')
			{
				menu(students, MAX_STUDENTS);
			}
		}
	}

	if(flag == 0)
	{
		system("cls");
		gotoxy(31,4);
		printf("NO RECORD FOUND !");

		gotoxy(28,6);
		printf("Enter a to enter file again or double y key to open menu section:");
		if(getch() == 'a')
		{
			system("cls");
			searching(students, MAX_STUDENTS);
		}
	}
}

void sorting(struct Student *students, int MAX_STUDENTS)
{
    struct Student temp;
    int flag = 0;

    system("cls");
    for (int i = 0; i < MAX_STUDENTS - 1; i++)
    {
        for (int j = 0; j < MAX_STUDENTS - i - 1; j++)
        {
            if (students[j].overallScore < students[j+1].overallScore)
            {
                temp = students[j];
                students[j] = students[j+1];
                students[j+1]= temp;
            }
        }
    }

    gotoxy(31,4);
    printf("\xB3\xDB\xDB\xDB\xDB\xDB Descending List of Students' GPA \xDB\xDB\xDB\xDB\xDB\xB3");

    //Printing list
    for (int i = 0, j = 6; i < MAX_STUDENTS, j < 6 + MAX_STUDENTS; i++, j++)
    {
        gotoxy(31, j);
        printf("%d. %s - GPA: %.2f\n", i + 1, students[i].fullName, students[i].overallScore);
    }

    flag = 1;
	Sleep(1000);
	gotoxy(18,16);
	printf("Enter y for menu option.");

	while(getch() == 'y')
	{
		menu(students, MAX_STUDENTS);
	}
}

void menu(struct Student *students, int MAX_STUDENTS)
{
    int flag = 0;

    //Using menu for each task
    system("cls");
	gotoxy(30,1);
	printf("\xB3\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 STUDENT MANAGEMENT \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB3");
	gotoxy(31,4);
	printf("\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB 1.Print List");
	gotoxy(31,7);
	printf("\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB 2.Find Max Overall Score");
	gotoxy(31,8);
	printf("\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB   Find Min Overall Score");
	gotoxy(31,9);
	printf("\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB   Find Max Basic Programming Score");
	gotoxy(31,12);
	printf("\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB 3.Print Last Name");
    gotoxy(31,15);
    printf("\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB 4.Search by ID");
    gotoxy(31,18);
    printf("\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB 5.Sorting");
    gotoxy(31,21);
    printf("\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB 6.Exit\n");

	gotoxy(31,24);
	switch(getch())
    {
		case '1':
			print_list(students, MAX_STUDENTS);
			break;
		case '2':
            INCLUDE(students, MAX_STUDENTS);
			break;
		case '3':
            first_name(students, MAX_STUDENTS);
			break;
		case '4':
            searching(students, MAX_STUDENTS);
			break;
        case '5':
            sorting(students, MAX_STUDENTS);
			break;
		case '6':
			exit_menu();
			break;
		default:
			system("cls");
			printf("Invalid Enter.");

			flag = 1;
			Sleep(1000);
			gotoxy(18,16);
			printf("Enter y for menu option.");

			while(getch() == 'y')
			{
				menu(students, MAX_STUDENTS);
			}
    }
}

void exit_menu()
{
	system("cls");
	gotoxy(31,4);
	printf("\xDB\xDB\xDB\xDB TEAM MEMBERS \xDB\xDB\xDB\xDB");

	gotoxy(31,6);
	printf("\xDB LE DUC DUNG (22BI13103).");
	gotoxy(31,8);
	printf("\xDB DO DUY MINH (22BI13280).");
	gotoxy(31,10);
	printf("\xDB NGUYEN TIEN CONG (22BI13067).");
	gotoxy(31,12);
	printf("\xDB DUONG TUAN KIET (22BI13230).");
}

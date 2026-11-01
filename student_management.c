#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 50
#define MAX_SUBJECTS 5
#define NAME_LEN     50

/* One student record */
struct Student {
    char  name[NAME_LEN];
    float marks[MAX_SUBJECTS];
    float average;
    char  grade;
};

/* Read a float in [0,100], re-asking on bad input */
float readMark(const char *prompt) {
    float m;
    while (1) {
        printf("%s", prompt);
        if (scanf("%f", &m) == 1 && m >= 0 && m <= 100)
            return m;
        printf("  Invalid. Enter a number from 0 to 100.\n");
        while (getchar() != '\n');            /* clear bad input */
    }
}

/* Fill one student's name and marks */
void inputStudent(struct Student *s, int subjects) {
    printf("Name: ");
    scanf(" %49[^\n]", s->name);
    for (int i = 0; i < subjects; i++) {
        char prompt[40];
        sprintf(prompt, "  Subject %d mark: ", i + 1);
        s->marks[i] = readMark(prompt);
    }
}

/* Letter grade from average */
char getGrade(float avg) {
    if (avg >= 90) return 'A';
    if (avg >= 80) return 'B';
    if (avg >= 70) return 'C';
    if (avg >= 60) return 'D';
    return 'F';
}

/* Compute average and grade for one student */
void calculateAverage(struct Student *s, int subjects) {
    float total = 0;
    for (int i = 0; i < subjects; i++)
        total += s->marks[i];
    s->average = total / subjects;
    s->grade   = getGrade(s->average);
}

/* Print results table */
void displayAll(const struct Student list[], int n, int subjects) {
    printf("\n%-20s", "Name");
    for (int j = 0; j < subjects; j++) printf("  S%-4d", j + 1);
    printf("  %-8s %-5s\n", "Average", "Grade");
    printf("------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("%-20s", list[i].name);
        for (int j = 0; j < subjects; j++)
            printf("  %-5.1f", list[i].marks[j]);
        printf("  %-8.2f %-5c\n", list[i].average, list[i].grade);
    }
}

/* Class-wide statistics */
void classStats(const struct Student list[], int n) {
    float sum = 0;
    int top = 0;
    for (int i = 0; i < n; i++) {
        sum += list[i].average;
        if (list[i].average > list[top].average) top = i;
    }
    printf("\nClass average : %.2f\n", sum / n);
    printf("Top student   : %s (%.2f)\n", list[top].name, list[top].average);
}

int main(void) {
    struct Student students[MAX_STUDENTS];
    int n, subjects;

    printf("Number of students (1-%d): ", MAX_STUDENTS);
    scanf("%d", &n);
    printf("Number of subjects (1-%d): ", MAX_SUBJECTS);
    scanf("%d", &subjects);

    if (n < 1 || n > MAX_STUDENTS || subjects < 1 || subjects > MAX_SUBJECTS) {
        printf("Values out of range.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("\nStudent %d\n", i + 1);
        inputStudent(&students[i], subjects);
        calculateAverage(&students[i], subjects);
    }

    displayAll(students, n, subjects);
    classStats(students, n);
    return 0;
}

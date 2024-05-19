#include <iostream>
#include <string>
#include <fstream>

using namespace std;
const int Max_SEMESTERS = 8;
const int Max_SUBJECTS = 10;

void getInput(string &name, string &registration, int &currentSemester, int subjectCounts[], string courseCodes[][Max_SUBJECTS], string subjectNames[][Max_SUBJECTS], int creditHours[][Max_SUBJECTS], int marks[][Max_SUBJECTS])
{
    cout << "Enter Student Name: ";
    cin >> name;
    cout << "Enter Registration Number: ";
    cin >> registration;
    while (true)
    {
        cout << "Enter Current Semester (1-8): ";
        cin >> currentSemester;
        if (currentSemester >= 1 && currentSemester <= 8)
            break;
        else
            cout << "Please enter a valid semester between 1 and 8.\n";
    }

    for (int i = 0; i < currentSemester; ++i)
    {
        cout << "Enter number of subjects in Semester " << i + 1 << ": ";
        cin >> subjectCounts[i];

        for (int j = 0; j < subjectCounts[i]; ++j)
        {
            cout << "Enter Course Code for Subject " << j + 1 << ": ";
            cin >> courseCodes[i][j];
            cout << "Enter Subject Name for Subject " << j + 1 << ": ";
            cin >> subjectNames[i][j];
            cout << "Enter Credit Hours for Subject " << j + 1 << ": ";
            cin >> creditHours[i][j];
            cout << "Enter Marks for Subject " << j + 1 << ": ";
            cin >> marks[i][j];
        }
    }
}

double calculateGPA(int subjectCount, int creditHours[], int marks[])
{
    double totalPoints = 0;
    int totalCredits = 0;
    for (int i = 0; i < subjectCount; ++i)
    {
        double gradePoint = marks[i] / 10.0;
        totalPoints += gradePoint * creditHours[i];
        totalCredits += creditHours[i];
    }
    return totalCredits ? totalPoints / totalCredits : 0.0;
}

void generateTranscript(const string &name, const string &registration, int currentSemester, int subjectCounts[], string courseCodes[][Max_SUBJECTS], string subjectNames[][Max_SUBJECTS], int creditHours[][Max_SUBJECTS], int marks[][Max_SUBJECTS])
{
    ofstream file("transcript.rtf");
    if (!file.is_open())
    {
        cerr << "Error opening file for writing\n";
        return;
    }

    file << "Transcript\n";
    file << "=========================\n";
    file << "Student Details\n";
    file << "Name: " << name << "\n";
    file << "Registration Number: " << registration << "\n";
    file << "Current Semester: " << currentSemester << "\n";
    file << "=========================\n";

    double totalGPA = 0.0;
    for (int i = 0; i < currentSemester; ++i)
    {
        file << "Semester " << i + 1 << "\n";
        file << "Course Code\t\t\tSubject Name\t\t\tCredit Hours\t\t\tMarks\n";
        for (int j = 0; j < subjectCounts[i]; ++j)
        {
            file << courseCodes[i][j] << "   \t\t\t\t" << subjectNames[i][j]
                 << "    \t\t\t\t" << creditHours[i][j] << "   \t\t\t\t\t" << marks[i][j] << "\n";
        }
        double gpa = calculateGPA(subjectCounts[i], creditHours[i], marks[i]);
        file << "GPA: " << (int)(gpa * 100) / 100.0 << "\n";
        file << "-------------------------\n";
        totalGPA += gpa;
    }

    double cgpa = totalGPA / currentSemester;
    file << "CGPA: " << (int)(cgpa * 100) / 100.0 << "\n";
    file.close();
    system("libreoffice --convert-to docx transcript.rtf --outdir .");
}

int main()
{
    string name, registration;
    int currentSemester;
    int subjectCounts[Max_SEMESTERS];
    string courseCodes[Max_SEMESTERS][Max_SUBJECTS];
    string subjectNames[Max_SEMESTERS][Max_SUBJECTS];
    int creditHours[Max_SEMESTERS][Max_SUBJECTS];
    int marks[Max_SEMESTERS][Max_SUBJECTS];

    getInput(name, registration, currentSemester, subjectCounts, courseCodes, subjectNames, creditHours, marks);
    generateTranscript(name, registration, currentSemester, subjectCounts, courseCodes, subjectNames, creditHours, marks);

    cout << "Transcript generated and saved as 'transcript.docx'\n";
}

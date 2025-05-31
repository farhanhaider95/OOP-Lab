#include <iostream>
#include <vector>
#include <fstream>
#include<string>
using namespace std;
class Student
{
public:
	string id, name;
	vector<string> enrolled;
	Student(string i, string n)
	{
		id = i;
		name = n;
	}
	void enroll(string courseCode)
	{
		enrolled.push_back(courseCode);
	}
	void viewCourses(vector<string> courseCodes, vector<string> courseNames)
	{
		cout << "Courses for " << name << ":\n";
		for (string c : enrolled)
		{
			for (size_t i = 0; i < courseCodes.size(); i++)
			{
				if (courseCodes[i] == c)
					cout << " - " << c << " (" << courseNames[i] << ")\n";
			}
		}
	}
};
class Course
{
public:
	string code, name;
	int maxSeats;
	vector<string> enrolledStudents;
	Course(string c, string n, int m)
	{
		code = c;
		name = n;
		maxSeats = m;
	}
	bool addStudent(string sid)
	{
		if (enrolledStudents.size() < maxSeats)
		{
			enrolledStudents.push_back(sid);
			return true;
		}
		return false;
	}
	void viewStudents(vector<Student>& allStudents)
	{
		cout << "Students in " << name << ":\n";
		for (string sid : enrolledStudents)
		{
			for (Student s : allStudents)
			{
				if (s.id == sid)
					cout << "- " << sid << " (" << s.name << ")\n";
			}
		}
	}
};
vector<Student> students =
{
Student("S1", "FARHAN"),
Student("S2", "ZUHAD")
};
vector<Course> courses =
{
Course("C1", "OOP", 2),
Course("C2", "Stats", 2)
};
void saveData()
{
	ofstream fout("students.txt");
	for (Student s : students)
	{
		fout << s.id << "," << s.name;
		for (string c : s.enrolled)
			fout << "," << c;
		fout << endl;
	}
	fout.close();
	fout.open("courses.txt");
	for (Course c : courses)
	{
		fout << c.code << "," << c.name << "," << c.maxSeats;
		for (string s : c.enrolledStudents)
			fout << "," << s;
		fout << endl;
	}
	fout.close();
}
void loadData()
{
	ifstream fin("students.txt");
	string line;
	while (getline(fin, line))
	{
		size_t pos = 0;
		vector<string> tokens;
		while ((pos = line.find(",")) != string::npos)
		{
			tokens.push_back(line.substr(0, pos));
			line.erase(0, pos + 1);
		}
		tokens.push_back(line);
		for (auto& s : students)
		{
			if (s.id == tokens[0])
			{
				for (int i = 2; i < tokens.size(); i++)
					s.enroll(tokens[i]);
				break;
			}
		}
	}
	fin.close();
	fin.open("courses.txt");
	while (getline(fin, line))
	{
		size_t pos = 0;
		vector<string> tokens;
		while ((pos = line.find(",")) != string::npos)
		{
			tokens.push_back(line.substr(0, pos));
			line.erase(0, pos + 1);
		}
		tokens.push_back(line);
		for (auto& c : courses)
		{
			if (c.code == tokens[0])
			{
				for (int i = 3; i < tokens.size(); i++)
					c.enrolledStudents.push_back(tokens[i]);
				break;
			}
		}
	}
	fin.close();
}
Student* getStudent(string id)
{
	for (auto& s : students)
		if (s.id == id) return &s;
	return &students[0];
}
Course* getCourse(string code)
{
	for (auto& c : courses)
		if (c.code == code) return &c;
	return &courses[0];
}
int main()
{
	loadData();
	int choice;
	vector<string> courseCodes, courseNames;
	for (Course c : courses)
	{
		courseCodes.push_back(c.code);
		courseNames.push_back(c.name);
	}
	do
	{
		cout << "\n--- University System ---\n";
		cout << "1. Enroll student in course\n";
		cout << "2. View student's courses\n";
		cout << "3. View course's students\n";
		cout << "4. Exit\n";
		cout << "Choose: ";
		cin >> choice;
		string sid, cid;
		if (choice == 1) {
			cout << "Enter Student ID (e.g., S1): "; cin >> sid;
			cout << "Enter Course Code (e.g., C1): "; cin >> cid;
			Student* s = getStudent(sid);
			Course* c = getCourse(cid);
			if (c->addStudent(sid))
			{
				s->enroll(cid);
				cout << "Enrolled successfully!\n";
			}
			else
			{
				cout << "Course is full.\n";
			}
		}
		else if (choice == 2)
		{
			cout << "Enter Student ID: "; cin >> sid;
			getStudent(sid)->viewCourses(courseCodes, courseNames);
		}
		else if (choice == 3) {
			cout << "Enter Course Code: "; cin >> cid;
			getCourse(cid)->viewStudents(students);
		}
		else if (choice == 4) {
			saveData();
			cout << "Data saved. Exiting...\n";
		}
	} while (choice != 4);
	return 0;
}

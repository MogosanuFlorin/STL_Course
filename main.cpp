#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct doctor {
    string name;
    string speciality;
    int hours_left = 8;
    vector<string> problems_treated;
};

struct problem {
    string problem;
    string speciality;
    int hour_needed;
	int priority;
    bool treated = false;

	bool operator<(const struct problem& n) const
	{
		return priority < n.priority;
	}
};

int main()
{
    ifstream inFile("input.txt");

    int no_problems, no_doctors;
    vector<doctor> doctors;
	priority_queue<problem> problems;

    inFile >> no_problems;

    for (int i = 0; i < no_problems; i++)
    {
        string problem, speciality;
        int hour, priority;
        inFile >> problem;
        inFile >> speciality;
        inFile >> hour;
        inFile >> priority;

        struct problem temp;
        temp.problem = problem;
        temp.speciality = speciality;
        temp.hour_needed = hour;
		temp.priority = priority;
        problems.push(temp);
    }

    inFile >> no_doctors;

    for (int i = 0; i < no_doctors; i++)
    {
        string name, speciality;

        inFile >> name;
        inFile >> speciality;
        struct doctor temp;
        temp.name = name;
        temp.speciality = speciality;
        doctors.push_back(temp);

    }

    while (!problems.empty()) {
		struct problem problem = problems.top();
        auto it = find_if(doctors.begin(), doctors.end(), [&problem](struct doctor& doctor) {
            return problem.speciality == doctor.speciality && problem.hour_needed <= doctor.hours_left && !problem.treated;
            });
        if (it != doctors.end()) {
            problem.treated = true;
            it->hours_left -= problem.hour_needed;
            it->problems_treated.push_back(problem.problem);
			
        }
        problems.pop();
    }

    for (auto doctor : doctors) {
        if (doctor.problems_treated.size() > 0) {
            cout << doctor.name << " " << doctor.problems_treated.size() << " ";
            for (auto problem : doctor.problems_treated) {
                cout << problem << " ";
            }
            cout << endl;
        }
    }




    return 0;
}
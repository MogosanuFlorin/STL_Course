#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

struct doctor {
    string name;
	int nr_specialities;
	unordered_set<string> specialities;
    int hours_left = 8;
    int hour_unavailable=8;
    vector<pair<int, string>> problems_treated;
	
};

struct problem {
    string problem;
    string specialty;
    int hour_needed;
	int priority;
    int hour_arrived;
    bool treated = false;

	bool operator<(const struct problem& n) const
	{
		if (this->hour_arrived != n.hour_arrived)
			return this->hour_arrived > n.hour_arrived;
		else
			return this->priority < n.priority;
	}
};

void readFromFile(vector<doctor> &doctors, priority_queue<problem> &problems){
    int no_problems, no_doctors;
    ifstream inFile("input2.txt");
    inFile >> no_problems;
    for (int i = 0; i < no_problems; i++)
    {
        string problem, specialty;
        int hour, priority, hour_arrived;
        inFile >> problem;
        inFile >> specialty;
        inFile >> hour_arrived;
        inFile >> hour;
        inFile >> priority;

        struct problem temp;
        temp.problem = problem;
        temp.specialty = specialty;
        temp.hour_arrived = hour_arrived;
        temp.hour_needed = hour;
        temp.priority = priority;
        problems.push(temp);
    }

    inFile >> no_doctors;

    for (int i = 0; i < no_doctors; i++)
    {
        string name, specialty;
        int nr_specialties;

        inFile >> name;
        inFile >> nr_specialties;
        struct doctor temp;
        temp.name = name;
        temp.nr_specialities = nr_specialties;
        for (int j = 0; j < nr_specialties; j++) {
            inFile >> specialty;
            temp.specialities.insert(specialty);
        }

        doctors.push_back(temp);

    }

}
void printDoctors(vector<doctor> doctors) {
    for (auto doctor : doctors) {
        if (doctor.problems_treated.size() > 0) {
            cout << doctor.name << " " << doctor.problems_treated.size() << " ";
            for (auto problem : doctor.problems_treated) {
                cout << problem.second << " " << problem.first << " ";
            }
            cout << endl;
        }
    }
}
void treatProblem(vector<doctor>& doctors, struct problem problem) {
    auto currentDoctor = find_if(doctors.begin(), doctors.end(), [&problem](struct doctor& doctor) {
        return doctor.specialities.contains(problem.specialty) && problem.hour_needed <= doctor.hours_left && problem.hour_arrived > doctor.hour_unavailable && !problem.treated;
        });
    if (currentDoctor != doctors.end()) {
        problem.treated = true;
        currentDoctor->hours_left -= problem.hour_needed;
        currentDoctor->problems_treated.push_back({ problem.hour_arrived , problem.problem });
        currentDoctor->hour_unavailable = (problem.hour_arrived + problem.hour_needed - 1);
    }
}
void treatAllProblems(vector<doctor>&doctors, priority_queue<problem>& problems) {
    while (!problems.empty())
    {
        struct problem problem = problems.top();
		treatProblem(doctors, problem);
        problems.pop();
    }
}



int main()
{
    vector<doctor> doctors;
	priority_queue<problem> problems;
	readFromFile(doctors, problems);
	treatAllProblems(doctors, problems);
	printDoctors(doctors);
    return 0;
}
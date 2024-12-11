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
    string speciality;
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

int main()
{
    ifstream inFile("input2.txt");

    int no_problems, no_doctors;
    vector<doctor> doctors;
	priority_queue<problem> problems;

    inFile >> no_problems;

    for (int i = 0; i < no_problems; i++)
    {
        string problem, speciality;
        int hour, priority, hour_arrived;
        inFile >> problem;
        inFile >> speciality;
		inFile >> hour_arrived;
        inFile >> hour;
        inFile >> priority;

        struct problem temp;
        temp.problem = problem;
        temp.speciality = speciality;
		temp.hour_arrived = hour_arrived;
        temp.hour_needed = hour;
		temp.priority = priority;
        problems.push(temp);
    }

    inFile >> no_doctors;

    for (int i = 0; i < no_doctors; i++)
    {
        string name, speciality;
		int nr_specialities;

        inFile >> name;
		inFile >> nr_specialities;
        struct doctor temp;
        temp.name = name;
		temp.nr_specialities = nr_specialities;
        for (int j = 0; j < nr_specialities; j++) {
            inFile >> speciality;
            temp.specialities.insert(speciality);
        }
        
        doctors.push_back(temp);

    }

    while (!problems.empty()) {
		struct problem problem = problems.top();
        auto it = find_if(doctors.begin(), doctors.end(), [&problem](struct doctor& doctor) {
            return doctor.specialities.contains(problem.speciality) && problem.hour_needed <= doctor.hours_left && problem.hour_arrived > doctor.hour_unavailable && !problem.treated;
            });
        if (it != doctors.end()) {
            problem.treated = true;
            it->hours_left -= problem.hour_needed;
            it->problems_treated.push_back({problem.hour_arrived , problem.problem });
            it->hour_unavailable = (problem.hour_arrived + problem.hour_needed - 1);
			
        }
        problems.pop();
    }

    for (auto doctor : doctors) {
        if (doctor.problems_treated.size() > 0) {
            cout << doctor.name << " " << doctor.problems_treated.size() << " ";
            for (auto problem : doctor.problems_treated) {
                cout << problem.second << " " << problem.first << " ";
            }
            cout << endl;
        }
    }




    return 0;
}
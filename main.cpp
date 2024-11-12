#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    ifstream inFile("input2.txt");

    int no_problems, no_doctors;
    string name, speciality;
	vector<pair<string, string>> doctors;
	vector<pair<pair<string, string>, bool>> problems;
    
    inFile >> no_problems;

    for (int i = 0; i < no_problems; i++)
    {
        inFile >> name;
        inFile >> speciality;
        //cout << name << ' ' << speciality << '\n';
        problems.push_back(make_pair(make_pair(name, speciality), false));
        //problem.first.first = boala; doctor.first.second = speciality; doctor.second = tratat/netratat;
    }

    inFile >> no_doctors;

    for (int i = 0; i < no_doctors; i++)
    {
        inFile >> name;
        inFile >> speciality;
        //cout << name << ' ' << speciality << '\n';
        doctors.push_back(make_pair(name, speciality));
	
    }

    for (auto doctor : doctors) {
        auto it = find_if(problems.begin(), problems.end(), [doctor](pair<pair<string, string>, bool> problem) {
            return doctor.second == problem.first.second && problem.second == false;
            });
        if (it != problems.end()) {
            it->second = true;
            cout << doctor.first << ' ' << it->first.first << '\n';
        }
    }




    return 0;
}
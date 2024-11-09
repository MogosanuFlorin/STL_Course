#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    ifstream inFile("input3.txt");

    int no_problems, no_doctors;
    string name, speciality;
	vector<pair<string, string>> problems;
	vector<pair<string, string>> doctors;
    
    inFile >> no_problems;

    for (int i = 0; i < no_problems; i++)
    {
        inFile >> name;
        inFile >> speciality;
        //cout << name << ' ' << speciality << '\n';
		problems.push_back(make_pair(name, speciality));
    }

    inFile >> no_doctors;

    for (int i = 0; i < no_doctors; i++)
    {
        inFile >> name;
        inFile >> speciality;
        //cout << name << ' ' << speciality << '\n';
		doctors.push_back(make_pair(name, speciality));
    }

	

	for (auto problem : problems)
	{
        bool ok = false;
		for (auto doctor : doctors)
		{
			if (problem.second == doctor.second)
			{
                cout << problem.first << ' ' << "Acceptat" << '\n';
                ok = true;
				break;

			}
		}
		if (!ok)
		{
			cout << problem.first << ' ' << "Respins" << '\n';
		}
	}

    return 0;
}
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

bool safe = true;
int available[3] = { 3, 3, 2 };
int allocated[5][3] = { {0,1,0 },
				   {3,0,2},
				   {3,0,2},
				   {2,1,1},
				   {0,0,2} };
int max_resource[5][3] = { {7,5,3 },
			   {3,2,2},
			   {9,0,2},
			   {2,2,2},
			   {4,3,3} };
string processes[5] = { "p0", "p1", "p2", "p3", "p4" };
string p_done[5];

bool Safety(int p_index, int need[5][3], int available[3])
{
    bool change = false;
    bool all_is_done = true;
    int work[3]; //iniate work
    for (int i = 0; i < 3; i++)
        work[i] = available[i];
    bool finish[5];     //

    for (int i = 0; i < 5; i++)
        finish[i] = false;

    do
    {
        change = false;
        for (int i = 0; i < 5; i++)
        {
            if (finish[i] == true) {}

            else
            {
                bool exist = true;
                for (int k = 0; k < 3; k++)
                {
                    if (need[i][k] > work[k])
                    {
                        exist = false;
                        break;
                    }
                }
                if (exist)
                {
                    cout << "P " << i << endl;
                    change = true;
                    finish[i] = true;
                    for (int k = 0; k < 3; k++)
                    {
                        work[k] += allocated[i][k];

                    }
                }

            }
        }
    } while (change);

    for (int i = 0; i < 5; i++)
    {
        if (finish[i] == false)
            all_is_done = false;
    }
    if (all_is_done)
        return true;
    else
        return false;

}
int find_process_number(string pName)
{
	for (int i = 0; i < 5; i++)
	{
		if (pName == processes[i])
			return i;
	}
	return -1;
}
string request(string pName, int resources[3], int need[5][3])
{
	bool check_request = true;

	int process_index = find_process_number(pName);
	if (process_index == -1)
		return "process does not exist.";
	else
	{
		for (int i = 0; i < 3; i++)
		{
			if (resources[i] + allocated[process_index][i] > max_resource[process_index][i])
				return "The requested resources is greater than the maximum.";
		}
		for (int i = 0; i < 3; i++)
		{
			allocated[process_index][i] += resources[i];
			available[i] -= resources[i];
			need[process_index][i] -= resources[i];
		}

		if (Safety(process_index, need, available))
			return "safe.";
		else
			return "unsafe";
	}
}
void release(string pName, int resources[3], int need[5][3])
{
	bool check_request = true;
	int process_index = find_process_number(pName);
	if (process_index == -1)
		cout<< "process does not exist.";
	else
	{
		for (int i = 0; i < 3; i++)
		{
			allocated[process_index][i] -= resources[i];
			available[i] += resources[i];
			need[process_index][i] += resources[i];
		}

        for (int i = 0; i < 5; i++)

        {
            for (int k = 0; k < 3; k++)
                {
                    cout<<need[i][k]<<"  " ;
                }
            cout<<endl;
        }


	}
}


int main()
{

	int need[5][3];
	for (int i = 0; i < 5; i++)
	{	for (int k = 0; k < 3; k++)
		{
			need[i][k] = max_resource[i][k] - allocated[i][k];
		}
	}
	int choice = 0, resources[3];
	string proccessNum, resourceNum;


	cout << "Please choose one of the below: " << endl;
	cout << "1- Request." << endl
		<<"2- Release." << endl
		<<"3- Recovery." << endl
		<<"4- Exit." << endl;


	cin >> choice;

	switch(choice){
		case 1:
			{cout << "Enter the request number, and the number of resources u want." << endl;
			cin >> proccessNum;
			for (int i = 0; i < 3; i++)
			{
				int r = 0;
				cin >> r;
				if (r <= available[i])
					resources[i] = r;
				else
					cout << "The requested resource is more than the available." << endl;
			}
			string state = request(proccessNum, resources, need);
			cout << "result:" << state<<endl;
			if (state != "safe")
				safe = false;

            break;
			}
		case 2:
		    {
			cout << "Enter the relase number, and the number of resources u want." << endl;
			cin >> proccessNum;
			int process_index = find_process_number(proccessNum);
			for (int i = 0; i < 3; i++)
			{

				int r = 0;
				cin >> r;
				if (r <= allocated[process_index][i]){

					resources[i] = r;
					}
				else
					cout << "The requested resource is more than the available." << endl;
			}
            release(proccessNum, resources, need);


            break;
		    }
		    case 3:
            {
                cout << "Enter the id of the process you need to release to recover." << endl;
                cin >> proccessNum;
                int process_index = find_process_number(proccessNum);
                for(int i=0 ; i< 3;i++)
                    resources[i]=allocated[process_index][i];
                release(proccessNum, resources, need);
                break;
            }

            case 4:
                break;
}


}

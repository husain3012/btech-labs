#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
int stringToInt(string line)
{
    int i = 0;
    int num = 0;
    while (line[i] != 0)
    {
        if (line[0] == '-')
        {
            return -1;
        }
        num *= 10;
        num += (line[i] - '0');
        i++;
    }
    return num;
}

class Moore{
	int initialState;
	vector<int> finalStates;
	vector<vector<int>> transition_table;
public:
	void read_dfa(string file_name){
    ifstream file;
    string line;
    file.open(file_name);
    int i = 0;

    while (getline(file, line))
    {
        if (i == 0)
        {
            initialState = stringToInt(line);
        }
        else if (i == 1)
        {
            int x = 0;
            string num = "";
            while (line[x] != 0)
            {
                if (line[x] == ' ')
                {
                    finalStates.push_back(stringToInt(num));
                    num = "";
                    x++;
                    continue;
                }
                num += line[x++];
            }
            finalStates.push_back(stringToInt(num));
        }
        else
        {
            vector<int> temp;
            int x = 0;
            string num = "";
            while (line[x] != 0)
            {
                if (line[x] == ' ')
                {
                    temp.push_back(stringToInt(num));
                    num = "";
                    x++;
                    continue;
                }
                num += line[x++];
            }
            temp.push_back(stringToInt(num));
            transition_table.push_back(temp);
        }
        i++;
    }
    file.close();
	}

	bool test(string s){
	int curr = initialState;
    int size = s.size(), k = 0;
    if(s==""){
    	for(auto fs : finalStates){
    		if(fs==0) return true;
    	}
    	return false;
    }
    while (curr != -1 && k < size)
    {
    	cout<<curr<<"->";
        string t = "";
        t += s[k++];
        curr = transition_table[curr][stringToInt(t)];
    }

    for (int i = 0; i < finalStates.size(); i++)
    {
        if (curr == finalStates[i])
        {
            return true;
        }
    }
    return false;		
	}

	void print(){
		cout<<"Initial State: "<<initialState;
		cout<<"\nFinal States: ";
		for(auto fs : finalStates){
			cout<<fs<<", ";
		}
		cout<<endl;
	}

};



int main()
{

    Moore dfa;
    dfa.read_dfa("dfa.txt");
    dfa.print();
    string inp;
    while(true){
    	cout<<"Enter input: ";
    	getline(cin, inp); 
    	if(inp=="exit") return 0;   	
    	if(dfa.test(inp)){
    		cout<<"Accepted :)\n";
    	}else{
    		cout<<"Rejected :(\n";
    	}
    }

    
    return 0;
}

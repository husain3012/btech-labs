#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<fstream>
using namespace std;

#define epsilon '#'
#define endMarker '$'


vector<string> split(string, char );

class Grammar
{
	unordered_map<char, vector<string>> rules;
	char startSymbol;
	unordered_set<char> grammarSymbols;
	

	void first_helper(char symbol, unordered_set<char> &setOfFirsts){
		if(symbol == epsilon or islower(symbol)){
			setOfFirsts.insert(symbol);
			return;
		}
		for(auto productions : rules[symbol]){
			
				first_helper(productions[0], setOfFirsts);
			
		}
	}
	public:
	Grammar(){
		startSymbol = '\0';
	}
	void read(string file_name){
	ifstream file;
	string line;
	file.open(file_name);
	
	while(getline(file, line)){
		
		char leftSymbol = line[0];
		if(startSymbol=='\0'){
			startSymbol=leftSymbol;
		}
		string rightSymbols = "";
		for(int i = 1;i<line.length();i++){
			rightSymbols += line[i];
		}
		rules[leftSymbol].push_back(rightSymbols);
	}

	}


	void print(){
		cout<<endl;
		for(auto rule : rules){
			cout<<rule.first<<" -> ";
			for(int i = 0; i<rule.second.size();i++){
				cout<<rule.second[i];
				if(i<rule.second.size()-1){
					cout<<" | ";
				}
			}
			cout<<endl;
		}
		
	}

	vector<char> first(char symbol){
		unordered_set<char> setOfFirsts;
		first_helper(symbol, setOfFirsts);
		vector<char> firsts;
		for(char c : setOfFirsts){
			firsts.push_back(c);
		}
		return firsts;
	}



	vector<char> follow(char symbol, char last_symbol = '\0'){
		
		unordered_set<char> setOfFollows;
		if(symbol!=last_symbol){
			if(symbol==startSymbol){
			setOfFollows.insert(endMarker);
		}
		for(auto rule : rules){
			vector<string> productions = rule.second;
			for(string prod : productions){
				
				for(int i = 0;i<prod.length();i++){
					char c = prod[i];
					if(c==symbol){
					// easy follow case
					if(i<prod.size()-1){
						vector<char> nextFirsts = first(prod[i+1]);
						for(char f : nextFirsts){
							if(f!=epsilon)
							setOfFollows.insert(f);
						}
					}
					// case where symbol is last
					if(i==prod.size()-1){
						vector<char> parentFollows = follow(rule.first, symbol);

					}
				}
				}
			
			}
		}
			
		}
		
		vector<char> follows;
		for(auto follow : setOfFollows){
			follows.push_back(follow);
		}
		return follows;
	}

	void printAllFirsts(){

		for(auto rule : rules){
			char symbol = rule.first;
			vector<char> firsts = first(symbol);
			cout<<"FIRST("<<symbol<<") = ";
			for(char c : firsts){
				cout<<c<<", ";
			}
			cout<<"\n";
		}
	}

	void printAllFollows(){
		for(auto rule : rules){
			char symbol = rule.first;
			vector<char> firsts = follow(symbol);
			cout<<"FOLLOW("<<symbol<<") = ";
			for(char c : firsts){
				cout<<c<<", ";
			}
			cout<<"\n";
		}
	}


};

int main(){
	Grammar grammar;
	grammar.read("grammar.txt");
	grammar.print();

	cout<<"\n\nFirsts:\n\n";
	// grammar.first('A');
	grammar.printAllFirsts();
	cout<<"\n\nFollows:\n\n";
	grammar.printAllFollows();
	


}



vector<string> split(string s, char delem = ' ')
{
    vector<string> tokenized;
    string temp = "";
    for (char x : s)
    {
        if (x == delem)
        {
            tokenized.push_back(temp);
            temp = "";
        }
        else
        {
            temp += x;
        }
    }
    tokenized.push_back(temp);
    return tokenized;
}

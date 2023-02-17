#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile( string filename , vector<string> &names , vector<int> &scores , vector<char> &grades ){
    string textline;
    ifstream source("name_score.txt");
    while(getline(source,textline)){
        char name[100];
        char format[] = "%[^:]: %d %d %d";
        int x,y,z;
        sscanf(textline.c_str(),format,name,&x,&y,&z);
        names.push_back(name);
        scores.push_back(x+y+z);
        grades.push_back(score2grade(x+y+z));
    }
}

void getCommand(string &command, string &key){
    cout << "Please input your command: ";
    cin >> command;
    if(toUpperStr(command) == "NAME" || toUpperStr(command) == "GRADE"){
        cin.ignore();
        getline(cin,key);
    }
}

void searchName(vector<string> names , vector<int> scores , vector<char> grades , string key){
    int count = 0;
    cout << "---------------------------------\n";
    for(unsigned int i = 0; i < names.size(); i++){
        if(key == toUpperStr(names[i])){
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << score2grade(scores[i]) << "\n";
            count++;
        }
        else if(i == names.size()-1 && count == 0) cout << "Cannot found." << "\n";
    }
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names , vector<int> scores , vector<char> grades , string key){
    int count = 0;
    cout << "---------------------------------\n";
    for(unsigned int i = 0; i < names.size(); i++){
        if(*key.c_str() == grades[i]){
            cout << names[i] << " (" << scores[i] << ")" << "\n";
            count++;
        }
        else if(i == names.size()-1 && count == 0) cout << "Cannot found." << "\n";
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}

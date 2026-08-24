#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <chrono>

using namespace std;

string reinflate(string reinf, array<string, 26> ht)
{   
    string result;
    for(char c : reinf)
    {
        int index = c - 'a';
        if (index < 0 || index >= 26 || ht[index] == "")
        {
            result.append(1, c);
        }
        else
        {
            result.append(reinflate(ht[index], ht));
        }
    }
    return result;
}

char find_starter(array<string, 26> ht)
{
    for (int i = 0; i < 26; i++) 
    {
        char letter = 'a' + i;
        bool found = false;
        
        for (const string& s : ht) 
        {
            if (s.find(letter) != string::npos) 
            {
                found = true;
                break;
            }
        }
        
        if (!found) 
        {
            return letter;
        }
    }
    return '\0';
}


array<string, 26> hashcode()
{

    ifstream arq;
    array<string, 26> letterToConvert;
    arq.open("casos_11/t11_03.txt", ios::in);


    string line;
    while (getline(arq, line))
    {
        if (line.empty() || line.size() < 3) continue;

        char first_letter = line[0];

        string convertion;

        size_t space = line.find(' ');
        if (space != string::npos && space + 1 < line.size()) 
        {
            convertion = line.substr(space + 1);
        } 
        else 
        {
            convertion = "";
        }
        
        letterToConvert[first_letter - 97] = convertion; 
    }

    arq.close();
    return letterToConvert;
}

int main()
{

    auto start = chrono::high_resolution_clock::now();

    string reinf;
    array<string, 26> hashtable = hashcode();
    char starter = find_starter(hashtable);
    if (starter != '\0') {
        reinf = string(1, starter);
        cout << reinflate(reinf, hashtable).size() << endl;
    }

    auto end = chrono::high_resolution_clock::now();
    auto dur = chrono::duration_cast<chrono::seconds>(end - start).count();
    cerr << "\nTempo: " << dur << " segundos\n";
}



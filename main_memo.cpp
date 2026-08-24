#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <chrono>



using namespace std;

long long
find_size(char starter, const array<string, 26>& ht, vector<long long>& memo)
{
    int index = starter - 'a';
    if (memo[index] != -1) return memo[index];

    long long total = 0;
    for (char c : ht[index])
    {
        int index = c - 'a';
        if (index >= 0 && index < 26 && !ht[index].empty())
        {
            total += find_size(c, ht, memo);
        }
        else total++;
    }
    memo[index] = total;
    return total;
}

char
find_starter(array<string, 26> ht)
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


array<string, 26>
hashcode()
{

    ifstream arq;
    array<string, 26> letterToConvert;
    arq.open("casos_11/t11_02.txt", ios::in);


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
        else convertion = "";
        
        letterToConvert[first_letter - 97] = convertion; 
    }

    arq.close();
    return letterToConvert;
}

int 
main()
{

    auto start = chrono::high_resolution_clock::now();


    long long size = 0;
    string reinf;

    array<string, 26> hashtable = hashcode();
    char starter = find_starter(hashtable);
    vector<long long> memo(26, -1);

    cout << find_size(starter, hashtable, memo);

    auto end = chrono::high_resolution_clock::now();
    auto dur = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cerr << "\nTempo: 0,000" << dur << " segundos\n";
}


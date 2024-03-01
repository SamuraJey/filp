#include <iostream>
#include <fstream>
#include <map>
#include <chrono>
#include "CComparator.h"
#include "CAllocator.h"

using namespace std;

bool isDelim(char &c) {
    switch (c) {
        case ' ':
        case '\n':
        case '.':
        case ',':
        case '!':
        case '-':
        case ';':
        case ':':
        case '?':
        case '"':
        case '\'':
        case '(':
        case ')':
        case '[':
        case ']':
        case '/':
            return true;
        default:
            return false;
    }
}

size_t countWords(char* text) {
    size_t words = 0;
    char *p = text;
    bool prevSpace = true;

    while (*p) {
        bool isDel = isDelim(*p);
        if (prevSpace && !isDel) words++;
        prevSpace = isDel;
        p++;
    }

    return words;
}

char* getText() {
    size_t size;
    ifstream inputFile("/home/samuraj/Documents/gitrepos/FILP-OK/book.txt", ios::binary);

    inputFile.seekg(0, ios::end);
    size = inputFile.tellg();
    inputFile.seekg(0);

    printf("Size: %d\n", (int)size);

    char* text = new char[size+1];
    inputFile.read(text, size);
    inputFile.close();

    return text;
}

void doMagicManually(char* text) {
    map<char*, size_t, CComparator> map;
    char *start = text;

    size_t words = countWords(text);

    for (int i = 0; i < words; ++i) {
        while (isDelim(*start)) start++;
        char *end = start + 1;
        while (*end && !isDelim(*end)) end++;
        end[0] = '\0';
        end++;

        auto it = map.find(start);
        if (it == map.end()){
            map.insert(make_pair(start, 1));
        } else {
            it->second++;
        }

        start = end;
    }

    int count = 0;
    
    for(auto it : map){
//        if (count++ == 20) break;
        cout << it.first << " " << it.second << endl;
        count += it.second;
    }
    cout<< "Count: " << count << endl;
}

int main() {
    char* text = getText();

    auto start = chrono::high_resolution_clock::now();
    doMagicManually(text);
    auto stop = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start)/1000;
    cout << "Time - manual (ms): " << duration.count() << endl;
    
    return 0;
}

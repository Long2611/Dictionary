#include <iostream>
#include <fstream>
#include <string.h>

#ifndef LANGUAGE_H
#define LANGUAGE_H

using namespace std; 

class Language
{
    private:
    string german, english, sentence, word;
    int posA, posB, size;
    bool is_English;
    public:
    void swap(string arr[], int posA, int posB);
    void swap(int arr[], int posA, int posB);
    void sort_dict(string dict[][1001], int size, bool is_English);
    string lang_det(string sentence, string dict[][1001]);
    string translate_word(string dict[][1001], string word, int left, int right, bool is_English);
    string translate_sentence(string sentence, string dict[][1001], bool is_English);
    void write_file(string dict[][1001], int size);
    void run();
};

#endif
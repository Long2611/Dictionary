#include <iostream>
#include <string.h>
#include <fstream>
#include "Language.h"

using namespace std;

//swap two position of two stings in a string array.
void Language::swap(string arr[], int posA, int posB )
{
    string temp;
    temp = arr[posA];
    arr[posA] = arr[posB];
    arr[posB] = temp;
}

//swap two position of two integer in an integer array.
void Language::swap(int arr[], int posA, int posB)
{
    int temp;
    temp = arr[posA];
    arr[posA] = arr[posB];
    arr[posB] = temp;
}

//using bubble sort to sort the dictionary alphabetically.
void Language::sort_dict(string dict[][1001],int size, bool is_English )// int beg, int end
{
    
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < (size - i - 1); j++)
        {
            if (!is_English)
            {
                string word_1, word_2;
                word_1 = dict[0][j];
                word_1[0]=tolower(word_1[0]);
                word_2 = dict[0][j+1];
                word_2[0]=tolower(word_2[0]);
                if (word_1 > word_2)
                {
                    swap(dict[0], j, (j+1));
                    swap(dict[1], j, (j+1));
                }
            }
            if (is_English)
            {
                string word_1, word_2;
                word_1 = dict[1][j];
                word_1[0]=tolower(word_1[0]);
                word_2 = dict[1][j+1];
                word_2[0]=tolower(word_2[0]);
                if (word_1 > word_2)
                {
                    swap(dict[0], j, (j+1));
                    swap(dict[1], j, (j+1));
                }
            }
        }
    }
}

//translate each word to English or German base on boolean is_English.
string Language::translate_word(string dict[][1001], string word, int left, int right, bool is_English)
{
    word[0] = tolower(word[0]);//lower the first char to avoid 
    string result;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        string word1;
        if (!is_English)
        {
            word1 = dict[0][mid];
        } else {
            word1 = dict[1][mid];
        }
        word1[0]=tolower(word1[0]);//lower the first char to avoid 
        if (word1 == word)
        {
            if (!is_English)
            {   
                // cout << "found" << endl;
                return result = dict[1][mid];
            }else{
                // cout << "found" << endl;
                return result = dict[0][mid];
            }
        } 
        if (word1 < word)
        {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    // cout << result << endl;
    return result = word;
}

// take in a string and search for it in the 2d array to detect the language(English or German)
string Language::lang_det(string sentence, string dict[][1001])
{
    string language;
    string result = "";
    char space = ' ';
    string translated_word1, translated_word2, word;
    int count = 0, counter = 1;
    int size_dict = sizeof(dict[0])/sizeof(dict[0][0]);
    for (int i = 0; i < sentence.length(); i++)
    {
        if (sentence[i] == space)
        {
            if (count+1 == 1) //first letter of the input sentence
            {
                word = sentence.substr(count, i);
                word[0] = tolower(word[0]);
            } 
        }else{
                word = sentence;
                word[0] = tolower(word[0]);
            }
    }
    sort_dict(dict, size_dict, true);
    translated_word1 = translate_word(dict, word, 0, size_dict-1, true);
    sort_dict(dict, size_dict, false);
    translated_word2 = translate_word(dict, word, 0, size_dict-1, false);
    if(word == translated_word1 && word == translated_word2)
    {
        return language = "None";
    } else if(word == translated_word1 && word != translated_word2)
    {
        return language = "German";
    } else if (word != translated_word1 && word == translated_word2)
    {
        return language = "English";
    }
    return language;
}

// translate_sentence will take in a whole sentence 
// and call function translate_word() for each word in the sentence
string Language::translate_sentence(string sentence, string dict[][1001], bool is_English)//assume dict[][] was sorted
{
    string result = "";
    char space = ' ';
    string translated_word, word;
    int count = 0, counter = 1;
    int size_dict = sizeof(dict[0]) / sizeof(dict[0][0]);
    sort_dict(dict, size_dict, false); //sort German
    for (int i = 0; i < sentence.length(); i++)
    {
        // cout << i << endl;
        word = " ";
        counter += 1;
        if (i == sentence.length()-1) //last letter of the inout sentence
        {
            word = sentence.substr(count+1, counter);
            string trans = translate_word(dict, word, 0, size_dict, is_English);
            result = result + trans + " ";
        }    
        if (sentence[i] == space)
        {
            if (count+1 == 1) //first letter of the input sentence
            {
                word = sentence.substr(count, i);
                string trans = translate_word(dict, word, 0, size_dict, is_English);
                // result = result + trans + " ";
                string lang = lang_det(word, dict);
                if(lang == "English")
                {
                    cout << "Language detected is English." << endl;
                    sort_dict(dict, size_dict, true);
                    is_English = true;
                    string trans = translate_word(dict, word, 0, size_dict, is_English);
                    result = result + trans + " ";
                } else if(lang == "German") 
                {
                    cout << "Language detected is German." << endl;
                    sort_dict(dict, size_dict, false);
                    string trans = translate_word(dict, word, 0, size_dict, is_English);
                    result = result + trans + " ";
                } else if(lang == "None") 
                {
                    cout << "No language detected, assuming English." << endl;
                    sort_dict(dict, size_dict, true);
                    is_English = true;
                    string trans = translate_word(dict, word, 0, size_dict, is_English);
                    result = result + trans + " ";
                }
            }
            else{
                word = sentence.substr(count+1, counter-1);
                string trans = translate_word(dict, word, 0, size_dict, is_English);
                result = result + trans + " ";
            }
        counter = 0;
        count = i;
        }
    }
    return result;
}

// Sort dictionary alphabeticallt in 2d array and printout to file dump.txt
void Language::write_file(string dict[][1001], int size)
{
    ofstream file("dump.txt");
    int German[size];
    int English[size];
    for (int i = 0; i < size; i++)
    {
        German[i] = i + 1;
        English[i] = i + 1;
        // cout << German[i] << endl;
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < (size - i - 1); j++)
        {
            string word_1, word_2;
            word_1 = dict[0][j];
            word_1[0]=tolower(word_1[0]);
            word_2 = dict[0][j+1];
            word_2[0]=tolower(word_2[0]);
            if (word_1 > word_2)
            {
                swap(dict[0], j, (j+1));
                swap(dict[1], j, (j+1));
            }
        }
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < (size - i - 1); j++)
        {
            string word_1, word_2;
                word_1 = dict[1][j];
                word_1[0]=tolower(word_1[0]);
                word_2 = dict[1][j+1];
                word_2[0]=tolower(word_2[0]);
                if (word_1 > word_2)
                {
                    swap(dict[0], j, (j+1));
                    swap(dict[1], j, (j+1));
                    swap(English, j, (j+1));
                }
        }
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < (size - i - 1); j++)
        {
            string word_1, word_2;
            word_1 = dict[0][j];
            word_1[0]=tolower(word_1[0]);
            word_2 = dict[0][j+1];
            word_2[0]=tolower(word_2[0]);
            if (word_1 > word_2)
            {
                swap(dict[0], j, (j+1));
                // swap(dict[1], j, (j+1));
                swap(German, j, (j+1));

            }
        }
    }
    if (file.is_open())
    {
        for (int i = 0; i < size; i++)
        {
            string result = dict[0][i] + ',' + to_string(German[i]) + ';' + 
            dict[1][i] + ',' + to_string(English[i]);
            file << result << endl;
            
        }
    file.close();  
    }
}

// Check if the text(.txt) file are open and the program will start.
void Language::run()
{
    bool is_English = false;
    bool file_read, quit = false;
    string file_name;
    fstream file;
    string line, language;

    while (!file_read) 
    {
        cout << "Name of language file to read in: ";
        cin >> file_name;
        file.open(file_name.c_str());
        if(!file) // check if file is read or not read. 
        {
            cout << "file is not read, please re-enter file name \n";    
        } else {
            cout << "File successfully processed! \n";
            file_read = true;
            break;
        }
    }
    // if read, break loop and start the compute 2d array
    int count;
    file >> language >> count;
    count += 1;
    string sentence;
    string dict[2][1001];
    for (int i = 0; i < count; i++)
    {
        getline(file, line);
        for (int j = 0; j < line.length(); j++)
        {
            if (line[j] == ',')
            {
                string german = line.substr(0,j);
                dict[0][i] = german;
                string english = line.substr(j+1,line.length());
                dict[1][i] = english;
                // cout << german << " and " << english << endl;
            }
        } 
    }
    int size_dict = sizeof(dict[0])/sizeof(dict[0][0]);
    sort_dict(dict, size_dict, false);
    string user_input;
    bool in_loop = false;
    while(!quit)
    {
        string str1, lang;
        cout << "Query? ";
        getline(cin, user_input);
        if (user_input == "!quit")
        {
            cout << "Thank you for using the system.\n";
            break;
            // quit = true;
        } else if(user_input == "!save")
        {
            write_file(dict, size_dict);
            cout << "Writing out file to 'dump.txt'\n";
        } 
        else if(user_input.length() > 0) {
            string result = translate_sentence(user_input, dict, is_English);
            for (int i = 0; i < user_input.length(); i++)
            {
                if (user_input[i] == ' ')
                {
                    str1 = user_input.substr(0,i);
                    break;
                }
            }
            lang = lang_det(str1,dict);
            if(lang == "None"||lang == "English")
            {
                cout << "German: " << result << endl;
            }else{
                cout << "English: " <<  result << endl;
            }  
        }
    }

}
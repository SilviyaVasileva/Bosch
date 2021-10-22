#include <iostream>
#include<string>
#include <map>
#include <fstream>
#include<vector>

using namespace std;

class Atbash {
private:
    string word;
    string new_word;
    map<string, string> cache_words;

    //funtion to calculate the symbols 
    string get_word(string str) {
        string created_word = "";
        for(int i = 0; i < str.size(); i++){
            string ch;
            if (str[i] >= 97 && str[i] <= 122) 
                ch = 'a' + 'z' - str[i];
            else if (str[i] >= 65 && str[i] <= 90)
                ch = 'A' + 'Z' - str[i];
            else
                ch = str[i];
            created_word+= ch;
        }
        return created_word;
    }

    vector<string> split (string s, string delimiter) {
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        string token;
        vector<string> res;

        while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
            token = s.substr (pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back (token);
        }

        res.push_back (s.substr (pos_start));
        return res;
    }

    bool is_file_exist(string fileName) {
        ifstream infile(fileName);
        return infile.good();
    }

public:
    // cache string
    string cache_string;

    Atbash(string name = "") {
        this->word = "";
        new_word= "";
    }

    ~ Atbash(){
    }

    void encode(string word_to_encode){
        cout << word_to_encode << " > ";

        //check if the word is in the cache
        if (cache_words.count(word_to_encode) == 1)
            cout << cache_words[word_to_encode] << endl;
        // encode the word and add it to the cache
        else {
            new_word = get_word(word_to_encode);
            cout << new_word << endl;
            cache_words.insert(pair<string, string>(word_to_encode, new_word));
            cache_string += ">> \"" + word_to_encode + "\" > \"" + new_word + "\"\n";
            cache_words.insert(pair<string, string>(new_word, word_to_encode));
        }
    }

    void decode(string word_to_decode) {
        cout << word_to_decode << " > ";

        //check if the word is in the cache
        if (cache_words.count(word_to_decode) == 1)
            cout << cache_words[word_to_decode] << endl;
        // encode the word and add it to the cache
        else {
            new_word = get_word(word_to_decode);
            cout << new_word << endl;\
        }
    }

    void safe_to_file(string name) {
        ofstream myfile;
        myfile.open(name);
        myfile << cache_string;
        myfile.close();
    }
    
    string read_cache(string file_name) {
        string line, cache = "";
        if (is_file_exist(file_name)) {
            ifstream myfile(file_name);
            if (myfile.is_open()) {
                while (getline(myfile, line)) {

                    cache += line + "\n";

                    int str_len = line.size();
                    string line2 = line.substr(4, line.size());
                    line2.erase(str_len-5, 1);

                    vector<string> v = split(line2, "\" > \"");
                    cache_words.insert(pair<string, string>(v[0], v[1]));
                    cache_words.insert(pair<string, string>(v[1], v[0]));

                }
            }
        }
        return cache;
    }
};

int main(int argc, char** argv) 
{
    // create the class
    Atbash a;

    // open cache file
    if (argc > 1)
        a.cache_string = a.read_cache(argv[1]);

    bool program = 1;

    char answ = 'y';
    int oper;
    string str;

    while(program) {
        cout << "Choose operation: \n \t encode: 1\n \t decode: 2 \n \t print cache: 3\n \t exit: 4\n";
        cin >> oper;
        if (oper == 1) {
            cout << "Enter string to encode: ";
            cin.ignore();
            getline(cin, str);
            // cin.getline(str, 999999);
            a.encode(str);
        }
        else if (oper == 2) {
            cout << "Enter string to decode: ";
            cin.ignore();
            getline(cin, str);
            a.decode(str);
        }
        else if (oper == 3)
            cout << a.cache_string << endl;
        else if (oper == 4) {
            program = 0;
            break;
        }
    }

    char file;
    cout << "Do you want to safe the cache to a file? (y/n): ";
    cin >> file;

    if (file == 'y') {
        string file_name;
        cout << "Enter file name: ";
        cin >> file_name;
        a.safe_to_file(file_name);
    }

    return 0;
}

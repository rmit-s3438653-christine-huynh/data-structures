// Christine Huynh s3438653
#include "my_vector.h"
#include <map>
#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>

/* Make a copy of v_text to temporary vector: temp
 * Checking all words in vectors: v_text and v_dict
 * Erase the word from temp when a match is found
 */
std::string My_Vector::search(std::string data) {
    std::string closest_match;
    int temp_dist = -1;

    for (std::string word : data_vector) {
        int curr_dist = calc_edit_dist(data, word);

        if (temp_dist == -1) {
            temp_dist = curr_dist;
            closest_match += word + " ";
        }
        else if (temp_dist > curr_dist) {
            closest_match.clear();
            temp_dist = curr_dist;
            closest_match += word + " ";
        }
        else if (temp_dist == curr_dist) {
            closest_match += word + " ";
        }
    }
    return closest_match;
}

void My_Vector::print(std::vector<std::string> v) {
    for (std::string s : v) {
            std::cout << s << std::endl;
    }
}

/* Reads file: inFile
 * Reads line by line, trims ending spaces and delims from line
 * Tokenizes by delims " 1234567890!@#$%^&*()_+=[{}]\\|;:'\"<>,./?"
 * Saves to: outVector
 */
void My_Vector::open_file(std::string file){
    std::string line;
    std::ifstream myFile;
    myFile.open(file);

    if (!myFile) {
        std::cerr << "Unable to open file: " << file << std::endl;
        exit(1);
    }
    while (getline(myFile, line)) {
        boost::trim(line);
        std::vector<std::string> temp;
        std::string sep(" 1234567890!@#$%^&*()_+=[{}]\\|;:'\"<>,./?");

        // TO-DO: Need to ignore ++, ::, -
        boost::trim_if(line, boost::is_any_of(sep));
        boost::split(temp, line, boost::is_any_of(sep), boost::token_compress_on);
        for (std::string i : temp) {
            boost::algorithm::to_lower(i);
            data_vector.push_back(i);
        }
    }
    myFile.close();
}

/* find edit distance between string a, and string b
 * return edit distance value int
 */
unsigned int My_Vector::calc_edit_dist(std::string a, std::string b) {
    unsigned int i, j;
    std::vector<std::vector<unsigned int> > m(a.length() + 1, std::vector<unsigned int>(b.length() + 1) );
    m[0][0] = 0;

    for (i = 1; i <= a.length(); i++) {
        m[i][0] = i;
    }
    for (j = 1; j <= b.length(); j++) {
        m[0][j] = j;
    }
    for (i = 1; i <= a.length(); i++) {
        for (j = 1; j <= b.length(); j++) {
            int var, v1, v2, v3;
            if (a.at(i-1) == b.at(j-1)) {
                var = 0;
            }
            else {
                var = 1;
            }
            v1 = m[i-1][j-1] + var;
            v2 = m[i-1][j] + 1;
            v3 = m[i][j-1] + 1;
            m[i][j] = std::min(v1, std::min(v2, v3) );
        }
    }
    return m[a.length()][b.length()];
}

/* Make a copy of v_text to temporary vector: temp
 * Checking all words in vectors: v_text and v_dict
 * Erase the word from temp when a match is found
 */
void My_Vector::compare(std::string file, My_Vector v) {
    std::string temp = "";
    std::vector<std::string> results;
    std::vector<std::string> searched_words;

    for (std::string word : data_vector) {
        if (std::find(searched_words.begin(), searched_words.end(), word) != searched_words.end() ) {
        }
        else {
            int num = v.count(word);
            if (num > 0) {
                num = My_Vector::count(word);
                std::string a_num = std::to_string(num);
                temp = word + ": " + a_num;
            }
            else {
                temp = word + ": Was not found in the dictionary. Similar words: " + v.search(word);
            }
            results.push_back(temp);
            searched_words.push_back(word);
        }
    }
    My_Vector::output(file, results);
    
}

/* Count the number of the occurances in vector
 * Returns int count
 */
int My_Vector::count(std::string data) {
    std::map<std::string, int>::iterator it;

    if (word_count.size() == 0) {
        for (std::string word : data_vector) {
            it = word_count.find(word);
            if (it != word_count.end() ) {
                it-> second++;
            }
            else {
                word_count[word] = 1;
            }
        }
    }
    return word_count[data];
}

/* save vector: v to file: inFile
 * then close file
 */
void My_Vector::output(std::string file, std::vector<std::string> v) {
    std::ofstream myFile (file);

    if (myFile.is_open() ) {
        for (std::string s : v) {
            myFile << s << std::endl;
        }
    }
    else {
        std::cerr << "Unable to open file: " << file << std::endl;
        exit(1);
    }
    myFile.close();
}
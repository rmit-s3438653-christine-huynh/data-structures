// Christine Huynh s3438653
#include "my_set.h"
#include <map>
#include <set>
#include <vector>
#include <utility>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>

std::string My_Set::search(std::string data) {
    std::string closest_match;
    int temp_dist = -1;

    for (std::string word : data_set) {
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

void My_Set::print(std::set<std::string> s) {
    for (std::string i : s) {
            std::cout << i << std::endl;
    }
}

void My_Set::open_file(std::string file) {
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
            data_set.insert(i);
        }
    }
    myFile.close();
}
unsigned int My_Set::calc_edit_dist(std::string a, std::string b) {
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
void My_Set::compare(std::string file, My_Set s) {
    std::string temp = "";
    std::vector<std::string> results;
    std::vector<std::string> searched_words;

    for (std::string word : data_set) {
        if (std::find(searched_words.begin(), searched_words.end(), word) != searched_words.end() ) {
        }
        else {
            int num = s.count(word);
            if (num > 0) {
                num = My_Set::count(word);
                std::string a_num = std::to_string(num);
                temp = word + ": " + a_num;
            }
            else {
                temp = word + ": Was not found in the dictionary. Similar words: " + s.search(word);
            }
            results.push_back(temp);
            searched_words.push_back(word);
        }
    }
    My_Set::output(file, results);
}

int My_Set::count(std::string data) {
    std::map<std::string, int>::iterator it;

    if (word_count.size() == 0) {
        for (std::string word : data_set) {
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

void My_Set::output(std::string file, std::vector<std::string> s) {
    std::ofstream myFile (file);

    if (myFile.is_open() ) {
        for (std::string i : s) {
            myFile << i << std::endl;
        }
    }
    else {
        std::cerr << "Unable to open file: " << file << std::endl;
        exit(1);
    }
    myFile.close();
}
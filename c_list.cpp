// Christine Huynh s3438653
#include "c_list.h"
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include <iostream>
#include <algorithm>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
/**
* sourced from intlist.cpp, paul miller
**/
void Custom_List::node::set_next_node(std::unique_ptr<Custom_List::node> && newnext) {
    next_node = std::move(newnext);
}

Custom_List::node * Custom_List::node::get_next_node(void) {
    return next_node.get();
}

std::unique_ptr<Custom_List::node> & Custom_List::node::get_next_ptr(void) {
    return next_node;
}

std::string Custom_List::node::get_data(void) {
    return data;
}

/* Add new node with string: data to Custom_List
 * If Custom_List is empty, make new node the head
 * While current node-> data is less than new node-> data is true
 *      Traverse through linked list until false
 * If Custom_List contains 1 element
 *      Insert new node at head
 * Else if current is null, reached end of Custom_List, all elements in Custom_List < data 
 *      Insert new node at prev
 * Else current is > elements in Custom_List it has traversed
 *      Insert new node at prev to new node
 * Increment size of Custom_List by 1
 * Return true, add success */
bool Custom_List::add(std::string data) {
    node * current;
    node * prev = nullptr;
    std::unique_ptr<Custom_List::node> newnode = std::make_unique<Custom_List::node> (data);
    if (head == nullptr) {
        head = std::make_unique<node> (data);
        ++size;
        return true;
    }
    current = head.get(); //get the pointer held by the unique_ptr
    while (current && current-> data < data) {
        prev = current;
        current = current-> get_next_node();
    }
    if (!prev) {
        newnode-> set_next_node(std::move(head) );
        head = std::move(newnode);
    } else if (!current) {
        prev-> set_next_node(std::move(newnode) );
    } else {
        newnode-> set_next_node(std::move(prev-> get_next_ptr() ) );
        prev-> set_next_node(std::move(newnode) );
    }
    ++size;
    return true;
}

/* Search for string: data in Custom_List
 * Calculate edit-dist between string:data and each element of Custom_List
 * temp-dist = curr_dist, add current item to vector
 * If temp-dist > edit-dist of item
 *      Clear vector, add current item to vector closest_match
 * Else if  temp-dist == edit-dist of item
 *      Add current item to vector closest_match
 * Return string closest_match*/
std::string Custom_List::search(std::string data) { // better name closest_match
    // TO-DO
    std::string closest_match = "";
    Custom_List::node * current; //dict
    int temp_dist = -1;
    
    for (current = head.get(); current; current = current-> get_next_node() ) {
        int curr_dist = calc_edit_dist(data, current-> data);
        if (temp_dist == -1) {
            temp_dist = curr_dist;
            closest_match += current-> data + " ";
        }
        else if (temp_dist > curr_dist) {
            closest_match.clear();
            temp_dist = curr_dist;
            closest_match += current-> data + " ";
        }
        else if (temp_dist == curr_dist) {
            closest_match += current-> data + " ";
        }
    }
    return closest_match;
}

/* Print contents of Custom_List to console 
 * Traverse through Custom_List
 * Print current-> data \n to console */
void Custom_List::print(void) {
    Custom_List::node * current;
    for (current = head.get(); current; current = current-> get_next_node() ) {
        std::cout << current-> data << std::endl;
    }
}

/* Open file, read file line-by-line
 * Trim edges of line of trailing spaces and delims
 * Tokenize line by delims
 * Add to Custom_List
 * Close file */
void Custom_List::open_file(std::string file) {
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
            add(i);
        }
    }
    myFile.close();
}

/* Populate a 2D array vector matrix of size string a, and string b
 * Calculate edit-dist between each letter of string a, and string b
 * Calculate 3 variables of neighboring values, get the minimum of the 3
 * Return the last value of the matrix */
unsigned int Custom_List::calc_edit_dist(std::string a, std::string b) {
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

/* Compares 2 linked lists */
void Custom_List::compare(std::string outfile, Custom_List ll) { // use vec ll.search(string)= vector, ll.count(string) = int
    std::string temp = "";
    Custom_List::node * current; //textfile
    std::vector<std::string> results;
    std::vector<std::string> searched_words;  

    for (current = head.get(); current; current = current-> get_next_node() ) {
        if (std::find(searched_words.begin(), searched_words.end(), current-> get_data() ) != searched_words.end() ) {
        }
        else {
            int num = ll.count(current->get_data() ); // count how many occurances in a word
            if (num > 0) {
                num = Custom_List::count(current->get_data() );
                std::string a_num = std::to_string(num);
                temp = current-> data + ": " + a_num;
            }
            else {
                temp = current-> data + ": Was not found in the dictionary. Similar words: " + ll.search(current-> data);
            }
            results.push_back(temp);
            searched_words.push_back(current-> get_data() );
        }  
    }
    Custom_List::output(outfile, results);
}

/* Count the number of the occurances of the string: data in Custom_List
 * Traverse through the Custom_List
 * If data == current-> data
 *      Increment count by 1
 * return int: count */
int Custom_List::count(std::string data) {
    // count number of occurances of word in textfile, that match from dict
    std::map<std::string, int>::iterator it;
    Custom_List::node * current;

    //if map.siz is 0 do below
    if (count_map.size() == 0) {
        for (current = head.get(); current; current = current-> get_next_node() ) {
            std::string currentWord = current-> get_data();

            it = count_map.find(currentWord);
            if (it != count_map.end() ) {
                it-> second++;
            }
            else {
                count_map[currentWord] = 1;
            }
        }
    }
    return count_map[data];
}

/* Output contents of Custom_List to output-file
 * If file is open
 *      Add items of vector into file
 * Close file */
void Custom_List::output(std::string file, std::vector<std::string> v) {
    std::ofstream my_file (file);

    if (my_file.is_open() ) {
        for (std::string o : v) {
            my_file << o << std::endl;
        }
        my_file.close();
    }
    else {
        std::cerr << "Unable to open file: " << file << std::endl;
        exit(1);
    } 
}
// Christine Huynh s3438653
#include "my_list.h"
#include <map>
#include <list>
#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include <iostream>
#include <algorithm>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>

//https://www.tutel.me/c/codereview/questions/143021/a+doubly+linked+list+implementation+using+c+smart+pointers
//https://codereview.stackexchange.com/questions/143021/a-doubly-linked-list-implementation-using-c-smart-pointers
//http://www.dreamincode.net/forums/topic/292286-linked-list-removal-c11/ 
//http://users.itk.ppke.hu/~nagba3/linkedlist.html
//https://codereview.stackexchange.com/questions/129715/doubly-linked-list-reimplemented-with-smart-pointers

void My_List::node::set_next_node(std::shared_ptr<My_List::node> && newnext) {
    next_node = newnext;
}

void My_List::node::set_prev_node(std::shared_ptr<My_List::node> && newprev) {
    prev_node = newprev;
}

My_List::node * My_List::node::get_next_node(void) {
    return next_node.get();
}

My_List::node * My_List::node::get_prev_node(void) {
    return prev_node.lock();
}

std::shared_ptr<My_List::node> & My_List::node::get_next_ptr(void) {
    return next_node;
}

std::shared_ptr<My_List::node> & My_List::node::get_prev_ptr(void) {
    return prev_node.lock();
}

std::string My_List::node::get_data(void) {
    return data;
}

std::string My_List::search(std::string data) {
    std::string closest_match = "";
    My_List::node * current; //dict
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

bool My_List::add(std::string data) { // RE-DO - ADD PREV
    node * current;
    node * prev = nullptr;
    node * next = nullptr;
    std::shared_ptr<My_List::node> newnode = std::make_shared<My_List::node> (data);

    if (head == nullptr) { // if List is empty
        head = std::make_shared<node> (data);
        tail = head;
        ++size;
        return true;;
    }
    current = head.get(); //get the pointer held by the unique_ptr
    while (current && current-> data < data) { // while current->data is less than data to input into List, traverse thru
        prev = current;
        current = current-> get_next_node();
        next = current-> get_next_node();
    }
    if (!prev) { // no node before (head)
        newnode-> set_next_node(std::move(head)); //newnodes next_node = head
        head-> set_prev_node(std::move(newnode)); // head prev_node = newnode
        head = newnode; //head = newnode
    }
    else if (!current) { // tail
        prev-> set_next_node(std::move(newnode));
        newnode-> set_prev_node(prev); // ERROR HERE
    }
    else {
        newnode-> set_next_node(std::move(prev-> get_next_ptr()) ); // set newnode as prev next
        next-> set_prev_node(std::move(prev-> get_prev_ptr())); // set newnode as next prev
        prev-> set_next_node(std::move(newnode)); //prev next = newnode
        next-> set_prev_node(std::move(newnode));
    }
    ++size;
    return true;
}

void My_List::print(void) {
    My_List::node * current;
    for (current = head.get(); current; current = current-> get_next_node() ) {
        std::cout << current-> data << std::endl;
    }
}    

void My_List::open_file(std::string file) {
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
            add(i);
        }
    }
    myFile.close();
}

unsigned int My_List::calc_edit_dist(std::string a, std::string b) {
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

void My_List::compare(std::string outfile, My_List l) {
    std::string temp = "";
    My_List::node * current; //textfile
    std::vector<std::string> results;
    std::vector<std::string> searched_words;  

    for (current = head.get(); current; current = current-> get_next_node() ) {
        if (std::find(searched_words.begin(), searched_words.end(), current-> get_data() ) != searched_words.end() ) {
        }
        else {
            int num = l.count(current->get_data() ); // count how many occurances in a word
            if (num > 0) {
                num = My_List::count(current->get_data() );
                std::string a_num = std::to_string(num);
                temp = current-> data + ": " + a_num;
            }
            else {
                temp = current-> data + ": Was not found in the dictionary. Similar words: " + l.search(current-> data);
            }
            results.push_back(temp);
            searched_words.push_back(current-> get_data() );
        }  
    }
    My_List::output(outfile, results);
}

int My_List::count(std::string data) {
    // count number of occurances of word in textfile, that match from dict
    std::map<std::string, int>::iterator it;
    My_List::node * current;

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

void My_List::output(std::string file, std::vector<std::string> v) {
    std::ofstream my_file (file);
    
    if (my_file.is_open() ) {
        for (std::string i : v) {
            my_file << i << std::endl;
        }
        my_file.close();
    }
    else {
        std::cerr << "Unable to open file: " << file << std::endl;
        exit(1);
    } 
}

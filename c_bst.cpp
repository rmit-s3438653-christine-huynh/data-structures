// Christine Huynh s3438653
#include "c_bst.h"
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include <iostream>
#include <algorithm>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>

std::string Custom_BST::closest_match;
std::vector<std::string> Custom_BST::results;
std::vector<std::string> Custom_BST::searched_words; 
int Custom_BST::temp_dist;
std::map<std::string, int> Custom_BST::count_map;
//http://www.cprogramming.com/tutorial/lesson18.html
//https://stackoverflow.com/questions/24591680/using-unique-ptr-instead-of-shared-ptr-in-bst
//http://www.bogotobogo.com/cplusplus/binarytree.php

void Custom_BST::add(const std::string & data) {
    std::unique_ptr<Node> node(new Node(data) );

    if (root == nullptr) {
        root = std::move(node);
    } 
    else {
        Node* temp = root.get();
        Node* prev = root.get();

        while (temp != nullptr) {
            prev = temp;
            if (temp->data < data)
                temp = temp->right.get();
            else
                temp = temp->left.get();
        }

        if (prev->data < data)
            prev->right = std::move(node);
        else
            prev->left = std::move(node);

        //count map 
        std::map<std::string, int>::iterator it;
        it = count_map.find(data);
        if (it != count_map.end() ) {
           it-> second++;
        }
        else {
             count_map[data] = 1;
        }

    }
}

std::string Custom_BST::search(std::string data) {
    closest_match = "";
    temp_dist = -1;
    search(root, data);
    return closest_match;
}

std::string Custom_BST::search(const std::unique_ptr<Node> &node, std::string data) {
    if(node == nullptr) return "";
    search(node-> left, data);

    if(node != NULL && node->data != data ) {
        int curr_dist = calc_edit_dist(data, node-> data);

        if (temp_dist == -1) {
            temp_dist = curr_dist;
            closest_match += node-> data + " ";
        }
        else if (temp_dist > curr_dist) {
            closest_match = "";
            temp_dist = curr_dist;
            closest_match += node-> data + " ";      
        }
        else if (temp_dist == curr_dist) {
            if (closest_match.find(node->data) == std::string::npos) { //word not in string
                closest_match += node-> data + " ";  
            }  
        }
    }
    search(node-> right, data);
    return closest_match;
}

void Custom_BST::print() const{
    print(root);
}

void Custom_BST::print(const std::unique_ptr<Node> &node) const {
    if(node == nullptr) return;
    print(node-> left);
    std::cout << node-> data << std::endl;
    print(node-> right);
}

void Custom_BST::open_file(std::string file) {
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

unsigned int Custom_BST::calc_edit_dist(std::string a, std::string b) {
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

void Custom_BST::compare(std::string outfile, Custom_BST bst) {
    results.clear();
    searched_words.clear(); 
    compare(root, std::move(bst) );
    Custom_BST::output(outfile, results);
}

void Custom_BST::compare(const std::unique_ptr<Node> &node, Custom_BST bst) {
    if(node == nullptr) return;
    compare(node-> left, std::move(bst) );

    std::string temp = "";

    if (std::find(searched_words.begin(), searched_words.end(), node-> data ) != searched_words.end() ) {}
    else {
        int num = bst.count(node->data ); // counr how many occurances in a word
        if (num > 0) {
            num = Custom_BST::count(node-> data );
            std::string a_num = std::to_string(num);
            temp = node-> data + ": " + a_num;
        }
        else {
            temp = node-> data + ": Was not found in the dictionary. Similar words: " + Custom_BST::search(node-> data);
        }
        results.push_back(temp);
        searched_words.push_back(node-> data );
    }
    compare(node-> right, std::move(bst) );
}

int Custom_BST::count(std::string data){
    //count(root, data);
    return count_map[data]-1;//-1 because counts appearance in dict
}

void Custom_BST::count(const std::unique_ptr<Node> &node, std::string data) {
    
    if(node == nullptr) return;
    count(node-> left, data);
    count(node-> right, data);
}

void Custom_BST::output(std::string file, std::vector<std::string> v) {
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
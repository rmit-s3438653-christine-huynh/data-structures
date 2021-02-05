// Christine Huynh s3438653
#include <map>
#include <string>
#include <memory>
#include <vector>
#include <iostream>
//http://thispointer.com/shared_ptr-binary-trees-and-the-problem-of-cyclic-references/
//https:stackoverflow.com/questions/24591680/using-unique-ptr-instead-of-shared-ptr-in-bst

class Custom_BST {
    struct Node;
        typedef std::unique_ptr<Node> node;
        struct Node {
            std::string data;
            node left;
            node right;
            Node(const std::string & value):data(value), left(nullptr), right(nullptr){}
    };
    node root;
    void add(const std::string & data);
    void print(const node&) const;
    public:
    Custom_BST(void){};
    void insert(const std::string & node);
    std::string search(std::string);
    std::string search(const std::unique_ptr<Node> &node, std::string);
    static std::string closest_match;
    static std::vector<std::string> results;
    static std::vector<std::string> searched_words; 
    static int temp_dist;
    void print() const;
    void open_file(std::string);
    unsigned int calc_edit_dist(std::string, std::string);
    void compare(const std::unique_ptr<Node> &node, Custom_BST);
    void compare(std::string outfile, Custom_BST);
    int count(std::string);
    void count(const std::unique_ptr<Node> &node, std::string data);
    static std::map<std::string, int> count_map;
    void output(std::string, std::vector<std::string>);
};


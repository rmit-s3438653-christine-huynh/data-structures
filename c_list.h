// Christine Huynh s3438653
// sourced from intlist.h, paul miller
#include <map>
#include <string>
#include <memory>
#include <vector>
#include <iostream>

class Custom_List {
    class node {
        std::string data;
        std::unique_ptr<node> next_node;
        public:
        node(std::string newdata) : data(newdata), next_node(nullptr) {}
        void set_next_node(std::unique_ptr<node> && newnext);
        node * get_next_node(void);
        std::string get_data(void);
        std::unique_ptr<node> & get_next_ptr(void);
        friend class Custom_List;
    };

    std::unique_ptr<node>head;
    int size;
    public:
    Custom_List(void) : head(nullptr), size(0) {}
    std::string search(std::string);
    bool add(std::string);
    void print(void);
    void open_file(std::string);
    unsigned int calc_edit_dist(std::string, std::string);
    void compare(std::string, Custom_List);
    int count(std::string data);
    std::map<std::string, int> count_map;
    void output(std::string, std::vector<std::string>);
};
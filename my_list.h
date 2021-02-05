// Christine Huynh s3438653
#include <map>
#include <list>
#include <string>
#include <memory>
#include <vector>
#include <iostream>

class My_List {
    class node {
        std::string data;
        std::shared_ptr<node> next_node;
        std::weak_ptr<node> prev_node;
        public:
        node(std::string newdata) : data(newdata), next_node(nullptr), prev_node(std::weak_ptr<node>()) {}
        void set_next_node(std::shared_ptr<node> && newnext);
        void set_prev_node(std::shared_ptr<node> && newprev);
        node * get_next_node(void);
        node * get_prev_node(void);
        std::string get_data(void);
        std::shared_ptr<node> & get_next_ptr(void);
        std::shared_ptr<node> & get_prev_ptr(void);
        friend class My_List;
    };
    std::shared_ptr<node>head;
    std::shared_ptr<node>tail;
    int size;
    public:
    My_List(void) : head(nullptr), tail(nullptr), size(0) {}
    std::string search(std::string);
    bool add(std::string);
    void print(void);
    void open_file(std::string);
    unsigned int calc_edit_dist(std::string, std::string);
    void compare(std::string, My_List);
    int count(std::string data);
    std::map<std::string, int> count_map;
    void output(std::string, std::vector<std::string>);
};

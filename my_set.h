// Christine Huynh s3438653
#include <set>
#include <map>
#include <string>
#include <vector>

class My_Set {
    void print(std::set<std::string>);

    public:
    My_Set(void){};
    std::string search(std::string);
    void open_file(std::string);
    unsigned int calc_edit_dist(std::string, std::string);
    void compare(std::string, My_Set);
    int count(std::string);
    std::map<std::string, int> word_count;
    std::multiset<std::string> data_set;
    void output(std::string, std::vector<std::string>);
};
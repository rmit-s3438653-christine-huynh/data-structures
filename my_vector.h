// Christine Huynh s3438653
#include <map>
#include <string>
#include <vector>

class My_Vector {
    void print(std::vector<std::string>);
    public:
    My_Vector(void){};
    std::string search(std::string);
    void open_file(std::string);
    unsigned int calc_edit_dist(std::string, std::string);
    void compare(std::string, My_Vector);
    int count(std::string);
    std::map<std::string, int> word_count;
    std::vector<std::string> data_vector;
    void output(std::string, std::vector<std::string>);
    
};
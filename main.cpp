// Christine Huynh s3438653
#include "c_bst.h"
#include "c_list.h"
#include "my_set.h"
//#include "my_list.h"
#include "my_vector.h"

#include <chrono>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <exception>
#include <boost/program_options.hpp>

class myexception: public std::exception {
    virtual const char* what() const throw() {
        return "My exception happened";
    }
} myex;

template<class T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    copy(v.begin(), v.end(), std::ostream_iterator<T>(os, " ") ); 
    return os;
}

/*void list_ds(std::string d, std::string t, std::string o) {
    My_List l_dict;
    My_List l_text;
    My_List l_out;

    l_dict.open_file(d);
    l_text.open_file(t);
    l_text.compare(o, std::move(l_dict));
}*/

void vec_ds(std::string d, std::string t, std::string o) {
    My_Vector v_dict;
    My_Vector v_text;
    My_Vector v_out;

    v_dict.open_file(d);
    v_text.open_file(t);
    v_text.compare(o, std::move(v_dict));
}

void set_ds(std::string d, std::string t, std::string o) {
    My_Set s_dict;
    My_Set s_text;
    My_Set s_out;

    s_dict.open_file(d);
    s_text.open_file(t);
    s_text.compare(o, std::move(s_dict));
}

void ll_ds(std::string d, std::string t, std::string o) {
    Custom_List ll_dict;
    Custom_List ll_text;
    Custom_List ll_out;

    ll_dict.open_file(d);
    ll_text.open_file(t);
    ll_text.compare(o, std::move(ll_dict));    
}

void bst_ds(std::string d, std::string t, std::string o){
    Custom_BST bst_dict;
    Custom_BST bst_text;
    Custom_BST bst_out;

    bst_dict.open_file(d);
    bst_text.open_file(t);
    bst_text.compare(o, std::move(bst_dict));
}

int main(int ac, char* av[])
{
    try {
        std::string ds;
        std::string dict;
        std::string text;
        std::string out;

        // Declare a group of options that will be 
        // allowed only on command line
        boost::program_options::options_description cmdline_options("Allowed options");
        cmdline_options.add_options()
            ("help", "produce help message")
            ("datastructure,s", boost::program_options::value<std::string> (&ds)->default_value("linkedlist"), "Data structure")
            ("dictionary,d", boost::program_options::value<std::string> (&dict)->default_value("dict.txt"), "Dictionary")
            ("textfile,t", boost::program_options::value<std::string> (&text)->default_value("textfile.txt"), "Textfile")
            ("outputfile,o", boost::program_options::value<std::string> (&out)->default_value("outputfile.txt"), "Output file");
    
        
        boost::program_options::positional_options_description p;
        p.add("datastructure", -1);
        p.add("dictionary", -1);
        p.add("textfile", -1);
        p.add("outputfile", -1);
        
        boost::program_options::variables_map vm;
        boost::program_options::store(boost::program_options::command_line_parser(ac, av).
            options(cmdline_options).positional(p).run(), vm);
            boost::program_options::notify(vm);        
    
        if (vm.count("help") ) {
            std::cout << "Usage: options_description [options]" << std::endl;
            std::cout << cmdline_options << std::endl;
            return 0;
        }

        if (vm.count("datastructure") ) {
            std::cout << "Data structure: " << ds << std::endl;
         }

        if (vm.count("dictionary") ) {
            std::cout << "Dictionary file: " << dict << std::endl;
        }

        if (vm.count("textfile") ) {
            std::cout << "Text file: " << text << std::endl;
        }
        if (vm.count("outputfile") ) {
            std::cout << "Output file: " << out << std::endl;
            /*auto begin = std::chrono::steady_clock::now();
            auto end = std::chrono::steady_clock::now();
            std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() << " ns" << std::endl;*/
        }
        if (ds == "list") {
            //list_ds(dict, text, out);
            std::cout << "List data structure is not available." << std::endl;
        }
        else if (ds == "vec") {
            vec_ds(dict, text, out);
        }
        else if (ds == "set") {
            set_ds(dict, text, out);
        }
        else if (ds == "ll") {
            ll_ds(dict, text, out);
        }
        else if (ds == "bst") {
            bst_ds(dict, text, out);
        }
        else {
            std::cout << "Unrecognized data structure." << std::endl;
        }                   
    }
    catch(std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }    
    return 0;
}
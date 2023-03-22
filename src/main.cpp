#include "File_funcs.hpp"
#include "film.hpp"
#include "map_sort.hpp"
#include "Print_top_10_films.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    std::string file1_path = "", file2_path = "" , file3_path = "", genre = "";
    for(int i = 1; i < argc; i++)
    {
        if(std::string(argv[i]) == "-title-akas-path")
        {
            file3_path = argv[i + 1];
        }
        if(std::string(argv[i]) == "-title-basics-path")
        {
            file1_path = argv[i + 1];
        }
        if(std::string(argv[i]) == "-title-ratings-path")
        {
            file2_path = argv[i + 1];
        }
        if(std::string(argv[i]) == "-genre")
        {
            genre = argv[i + 1];
        }
    }
    if(file3_path == "" || file2_path == "" || file1_path == "" || genre == "")
    {
        std::cout << "wrong input parameters" << std::endl;
        return -1;
    }
    std::map<std::string,Film> map_of_films;
    std::vector<std::pair<std::string, Film>> vec_of_films;
    Fill_map_from_file(file2_path, map_of_films);
    Remove_excess_films(file1_path, map_of_films, genre);
    Add_local_title(file3_path, map_of_films);
    map_sort(map_of_films, vec_of_films);
    Print_top_10_films(vec_of_films);
    
   
 
}

#include "Print_top_10_films.hpp"

void Print_top_10_films(std::vector<std::pair<std::string, Film>>& vec_of_films)
{
    int count = 0;         
    for(auto it = vec_of_films.rbegin(); it != vec_of_films.rend(); it++)
    {
        std::cout <<  it->first  << " ";
        it->second.PrintFilm();
        std::cout << std::endl;
        count++;
        if (count == 10)
            break;
    }
}
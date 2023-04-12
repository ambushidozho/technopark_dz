#include "map_sort.hpp"



void map_sort(std::unordered_map<std::string,Film>& map_of_films, std::vector<std::pair<std::string, Film>>& vec_of_films)
{
    std::copy(map_of_films.begin(), map_of_films.end(),std::back_inserter<std::vector<std::pair<std::string, Film>>>(vec_of_films));
    std::sort(vec_of_films.begin(), vec_of_films.end(),
             [](const std::pair<std::string,Film> &l,const std::pair<std::string,Film> &r)
             {
                if(l.second.rating != r.second.rating)
                {
                    return l.second.rating < r.second.rating;
                }
                return l.first < r.first;
             });
}

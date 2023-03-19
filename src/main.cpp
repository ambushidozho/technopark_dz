#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
struct Film
{
    Film()
    {
        local_title = "";
        id = "";
        title = "";    
    }
    std::string id;
    std::string title;
    std::string local_title;
    float rating;
    std::string genre;
    int num_of_votes;
    bool isAdult;
    void PrintFilm()
{
    if (this->local_title != "")
    {
        std::cout << "Local Title: " << local_title << std::endl;
    }
    else
    {
        std::cout << "Title: " << title << std::endl;
    }
    std::cout << "Rating: " << rating << std::endl;
    std::cout << "Number of votes: " << num_of_votes << std::endl;
    std::cout << "Genre: " << genre << std::endl;
    std::cout << "Is Adult: " << isAdult << std::endl;
    std::cout << "======================================" << std:: endl;
}
};

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    std::string file1_path = "";
    std::string file3_path = "";
    std::string file2_path = "";
    std::string genre = "";
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
    std::ifstream fin;
    std::string buff;
    std::map<std::string,Film> vc_films;
    fin.open(file2_path);
    if (fin.is_open())
    {
        getline(fin, buff);
        while (getline(fin, buff))
        {
            std::istringstream iss(buff);
            std::string token;
            int index = 0;
            Film film;
            std::string id;
                while (getline(iss, token, '\t'))
                {
                    switch (index)
                    {
                    case 0:
                        id = token;
                        break;
                    case 1:
                        film.rating = std::stof(token);
                        break;
                    case 2:
                        film.num_of_votes = std::stoi(token);
                        break;
                    default:
                        break;
                    }
                    if (index >= 2)
                        break;
                    index++;
                }
                if (film.num_of_votes > 1000)
                {
                    vc_films[id] = film;
                }
        }
    }
    fin.close();
    fin.open(file1_path);
    if (fin.is_open())
    {
        getline(fin, buff);
        while (getline(fin, buff))
        {
            std::istringstream iss(buff);
            std::string token; 
            int index = 0;
            iss >> token;
            if (vc_films.find(token) != vc_films.end())
            {
                std::string id = token;
                while (getline(iss, token, '\t'))
                {
                    switch (index)
                    {
                    case 3:
                        vc_films[id].title = token;
                        break;
                    case 4:
                        vc_films[id].isAdult = std::stoi(token);
                        break;
                    case 8:
                        vc_films[id].genre = token;
                        break;
                    default:
                        break;
                    }
                    index++;
                }
                if ((vc_films[id].genre.find(genre) == std::string::npos) || vc_films[id].isAdult)
                {
                    vc_films.erase(id);
                }
            }
            else
            {
                continue;
            }
        }
    }
    fin.close();
    fin.open(file3_path);
    if (fin.is_open())
    {
        getline(fin, buff);
        while (getline(fin, buff))
        {
            std::istringstream iss(buff);
            std::string token, localized_title, id;
            int index = 0;
            bool is_Russian = false;
            iss >> token;
            id = token;
            if (vc_films.find(token) != vc_films.end() && buff.find("RU") != std::string::npos)
            {
                while (getline(iss, token, '\t'))
                {
                    switch (index)
                    {
                    case 2:
                        localized_title = token;
                        break;                 
                    default:
                        break;
                    }
                    if (index >= 2)
                        break;
                    index++;
                }
                    vc_films[id].local_title = localized_title;
            }
            else
                continue;
        }
    } 
    fin.close();
    std::vector<std::pair<std::string, Film>> vec; 
    std::copy(vc_films.begin(), vc_films.end(),std::back_inserter<std::vector<std::pair<std::string, Film>>>(vec));
    std::sort(vec.begin(), vec.end(),
             [](const std::pair<std::string,Film> &l,const std::pair<std::string,Film> &r)
             {
                if(l.second.rating != r.second.rating)
                {
                    return l.second.rating < r.second.rating;
                }
                return l.first < r.first;
             });
    int count = 0;         
    for(auto it = vec.rbegin(); it != vec.rend(); it++)
    {
        std::cout <<  it->first  << " ";
        it->second.PrintFilm();
        std::cout << std::endl;
        count++;
        if (count == 10)
            break;
    }
}

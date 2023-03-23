#include "File_funcs.hpp"





void Fill_map_from_file(const std::string& path, std::map<std::string,Film>& map_of_films)
{
    std::string buff;
    std::ifstream fin;
    fin.open(path);
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
                    map_of_films[id] = film;
                }
        }
    }
    fin.close();

}
void Remove_excess_films(const std::string& path, std::map<std::string,Film>& map_of_films, std::string genre)
{
    std::string buff;
    std::ifstream fin;
    fin.open(path);
    if (fin.is_open())
    {
        getline(fin, buff);
        while (getline(fin, buff))
        {
            std::istringstream iss(buff);
            std::string token; 
            int index = 0;
            iss >> token;
            if (map_of_films.find(token) != map_of_films.end())
            {
                std::string id = token;
                while (getline(iss, token, '\t'))
                {
                    if(token == "/N")
                    {
                        continue;
                    }
                    else
                    {
                        switch (index)
                        {
                        case 3:
                            map_of_films[id].title = token;
                            break;
                        case 4:
                            map_of_films[id].isAdult = std::stoi(token);
                            break;
                        case 8:
                            map_of_films[id].genre = token;
                            break;
                        default:
                            break;
                    }
                    }
                    index++;  
                }
                if ((map_of_films[id].genre.find(genre) == std::string::npos) || map_of_films[id].isAdult)
                {
                    map_of_films.erase(id);
                }
            }
            else
            {
                continue;
            }
        }
    }
    fin.close();
}

void Add_local_title(const std::string& path, std::map<std::string,Film>& map_of_films)
{
    std::string buff;
    std::ifstream fin;
    fin.open(path);
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
            if (map_of_films.find(token) != map_of_films.end() && buff.find("RU") != std::string::npos)
            {
                while (getline(iss, token, '\t'))
                {
                    if(token == "/N")
                    {
                        continue;
                    }
                    else
                    {
                        switch (index)
                        {
                        case 2:
                            map_of_films[id].local_title = token;
                            break;                 
                        default:
                            break;
                        }
                        if (index >= 2)
                            break;
                        } 
                    index++;
                }
            }
            else
                continue;
        }
    } 
    fin.close();
}
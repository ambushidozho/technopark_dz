#pragma once
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
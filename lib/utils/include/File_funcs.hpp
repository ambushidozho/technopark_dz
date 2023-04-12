#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include "film.hpp"

void Fill_map_from_file(const std::string& path, std::unordered_map<std::string,Film>& map_of_films);
void Add_local_title(const std::string& path, std::unordered_map<std::string,Film>& map_of_films);
void Remove_excess_films(const std::string& path, std::unordered_map<std::string,Film>& map_of_films, std::string genre);


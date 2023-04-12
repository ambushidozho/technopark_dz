#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include "film.hpp"

void map_sort(std::unordered_map<std::string,Film>& map_of_films, std::vector<std::pair<std::string, Film>>& vec_of_films);
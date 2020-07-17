#include "DataRetriever.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void DataRetriever::retrieve_data(std::string& path) {
}

std::vector<std::string> get_line_cells(std::istream& input) {
    std::vector<std::string> cells;
    std::string line;
    std::getline(input, line);

    std::stringstream linestream(line);
    std::string cell;
    while (std::getline(linestream, cell, ',')) {
        cells.push_back(cell);
    }

    return cells;
}

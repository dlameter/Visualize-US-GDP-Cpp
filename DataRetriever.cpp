#include "DataRetriever.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

void DataRetriever::retrieve_data(std::string& path) {
    std::ifstream file(path);

    if (file.is_open()) {
        // Handle first line in case it is the title of the CSV file.
        std::vector<std::string> cells = get_line_cells(file);
        try {
            double gdp = std::stod(cells[1]);

            // If it's made it this far then the first line is not a title line
            x.push_back(cells[0]);
            y.push_back(gdp);
        }
        catch (std::invalid_argument ia) {
            // Skip the first line of the file
        }

        // handle the rest of the file
        while (!file.eof()) {
            cells = get_line_cells(file);

            // If no cells were found on a line, it's likely and empty line or eof.
            if (cells.empty()) {
                break;
            }

            x.push_back(cells[0]);
            y.push_back(std::stod(cells[1]));

            // TODO: Handle exceptions thrown by stod
        }

        file.close();
    }
    else {
        std::cerr << "Could not open file '" << path << "'" << std::endl;
        // Should throw error that can be handled by the caller
    }
}

std::vector<std::string> DataRetriever::getX() {
    return x;
}

std::vector<double> DataRetriever::getY() {
    return y;
}

QDate DataRetriever::stringToDate(const std::string& string) {
    int year = 0, month = 0, day = 0;

    QRegularExpression re("(\\d\\d\\d\\d)-(\\d\\d)-(\\d\\d)");
    auto match = re.match(QString::fromStdString(string));
    year = match.captured(1).toInt();
    month = match.captured(2).toInt();
    day = match.captured(3).toInt();

    return QDate(year, month, day);
}

std::vector<std::string> DataRetriever::get_line_cells(std::istream& input) {
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

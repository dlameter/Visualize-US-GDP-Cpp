#ifndef DATA_RETRIEVER_H
#define DATA_RETRIEVER_H
#include <string>
#include <vector>
#include <QDateTime>

QT_USE_NAMESPACE

class DataRetriever {
    public:
        void retrieve_data(std::string& path);
        std::vector<std::string> getX();
        std::vector<double> getY();
        QDateTime stringToDate(const std::string& string);

    private:
        std::vector<std::string> x;
        std::vector<double> y;

        void handleFirstLine(std::ifstream& file);
        void readInRestOfFile(std::ifstream& file);
        std::vector<std::string> get_line_cells(std::istream& input);
};

#endif

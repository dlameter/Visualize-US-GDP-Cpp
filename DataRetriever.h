#ifndef DATA_RETRIEVER_H
#define DATA_RETRIEVER_H
#include <string>
#include <vector>

class DataRetriever {
    public:
        void retrieve_data(std::string& path);
    private:
        std::vector<std::string> get_line_cells(std::istream& input);
        std::string* x;
        double* y;
        int size;
};

#endif

#ifndef DATA_RETRIEVER_H
#define DATA_RETRIEVER_H
#include <string>

class DataRetriever {
    public:
        void retrieve_data(std::string path);
    private:
        std::string* x;
        double* y;
        int size;
};

#endif

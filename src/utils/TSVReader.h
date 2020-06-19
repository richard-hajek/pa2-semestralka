#ifndef PROGTEST_PROJECT_FILEPARSER_H
#define PROGTEST_PROJECT_FILEPARSER_H

#include <fstream>
#include <vector>

/**
 * Save and setup file reader
 */
class TSVReader {
public:

    /**
     *  @param path the path to a file
     */
    explicit TSVReader(const std::string & path): _input(path){

    }

    /**
     * Read and return int
     * @return read integer
     */
    int NextInt() {
        int i;
        _input >> i;
        return i;
    }
    /**
     * Read and return double
     * @return read double
     */
    double NextDouble() {
        double i;
        _input >> i;
        return i;
    }
    /**
     * Read and return char
     * @return read char
     */
    char NextChar() {
        char c;
        _input >> c;
        return c;
    }
    /**
     * Read and return boolean
     * @return read boolean
     */
    bool NextBoolean() {
        bool b;
        _input >> b;
        return b;
    }
    /**
     * Read and return string
     * @return read string
     */
    std::string NextString(){
        std::string str;
        _input >> str;
        return str;
    }
    /**
     * Read and return string vector
     * @param size of vector
     * @return read data
     */
    std::vector<std::string> NextLines(int count){
        std::vector<std::string> lines;

        for (int i = 0; i < count; i++){
            std::string line;
            getline(_input, line);
            lines.push_back(line);
        }

        return lines;
    }

    /**
     * Check the input file
     * @return true if gucci
     */
    bool Good() const{
        return _input.good();
    }

private:
    std::ifstream _input;
};

#endif //PROGTEST_PROJECT_FILEPARSER_H

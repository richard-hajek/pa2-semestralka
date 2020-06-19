#ifndef PROGTEST_PROJECT_TSVWRITER_H
#define PROGTEST_PROJECT_TSVWRITER_H

#include <fstream>
#include <vector>

/**
 * Class to write save files with
 */
class TSVWriter {
public:

    /**
     *  @param path the path to a file
     */
    explicit TSVWriter(const std::string & path): _fstream(path, std::ofstream::out){

    }

    /**
     * Write an int into a stream
     * @param i int to write
     */
    void Write(int i) {
        _fstream << i << '\t';
    }

    /**
     * Write a bool into a stream
     * @param b bool to write
     */
     void WriteBoolean(bool b){
         _fstream << b << '\t';
     }

    /**
     * Write a double into a stream
     * @param i double to write
     */
    void Write(double d){
        _fstream << d << '\t';
    }

    /**
     * Write a char into a stream
     * @param c char to write
     */
    void Write(char c) {
        _fstream << c << '\t';
    }

    /**
     * Write a string into a stream
     * @param str string to write
     */
    void Write(const std::string& str){
        _fstream << str << '\t';
    }

    /**
     * Write several lines into a stream
     * @param lines lines to write
     */
    void Write(const std::vector<std::string>& lines){
        for (auto & line : lines){
            _fstream << line << '\n';
        }
    }

    /**
     * Has little effect on save loading and saving
     * HOWEVER
     * It will make the save files significantly more readable by separating records
     */
    void Next(){
        _fstream << '\n';
    }

    /**
     * Return true if file stream is ok
     * @return state of stream
     */
    bool Good() const{
        return _fstream.good();
    }

    /**
     * Tidy and close
     */
    ~TSVWriter(){
        _fstream.close();
    }

private:
    /// File to write to
    std::ofstream _fstream;
};

#endif //PROGTEST_PROJECT_TSVWRITER_H

#ifndef SEMESTER_PROJECT_LOG_H
#define SEMESTER_PROJECT_LOG_H

#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

static std::ofstream logfile("log.txt", std::ios::out | std::ios::app);

/**
 * Static class which facilitates logging
 */
class Log {

public:

    /**
     * Should be called before any Msg calls, to paste timestamp
     */
    static void Begin(){
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        logfile << "---LOG OF " << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S") << " BEGINS-----" << std::endl;
    }

    /**
     * Send message with the DEBUG severity tag
     */
    template<typename... msg_t>
    static void Debug(const std::string& tag, msg_t&&... messages){
        Message(tag, "DEBUG", &messages...);
    }
    /**
     * Send message with the INFO severity tag
     */
    template<typename... msg_t>
    static void Info(const std::string& tag, msg_t&&... messages){
        Message(tag, "INFO", &messages...);
    }
    /**
     * Send message with the WARN severity tag
     */
    template<typename... msg_t>
    static void Warn(const std::string& tag, msg_t&&... messages){
        Message(tag, "WARN", &messages...);
    }
    /**
     * Send message with the ERR severity tag
     */
    template<typename... msg_t>
    static void Err(const std::string& tag, msg_t&&... messages){
        Message(tag, "ERR", &messages...);
    }
    /**
     * Send message with the any severity
     */
    template<typename... msg_t>
    static void Message(const std::string& tag, const std::string& severity, msg_t&&... messages){
        logfile << "[" << tag << "] " << severity << ": ";

        int dummy[] = {
                0,
                ((void) log_argument(std::forward<msg_t>(messages)),0)...
        };

        // silence the unused dummy warning
        if (dummy == nullptr) return;

        logfile << std::endl;
        logfile.flush();
    }

    static void End(){
        logfile.close();
    }

private:

    /**
     * Helper function for std::forward
     */
    template <typename T>
    static void log_argument(T t) {
        logfile << *t << " ";
    }

};


#endif //SEMESTER_PROJECT_LOG_H

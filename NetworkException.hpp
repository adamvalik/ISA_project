/**
 * @file NetworkException.hpp
 * @brief NetworkException class header
 * 
 * @author Adam Valík <xvalik05@vutbr.cz>
 * 
*/

#ifndef NETTWORKEXCEPTION_HPP
#define NETTWORKEXCEPTION_HPP

#include <string>
#include <exception>

using namespace std;

/**
 * @class NetworkException
 * @brief Exception class for ISA project
 */
class NetworkException : public exception {
    
    string message;
    int exitCode;
    
    public:
        NetworkException(int code, const string& msg) : message(msg), exitCode(code) {};
        NetworkException(int code) : exitCode(code) {};

        /**
         * @brief Get exception message
         * @return const char* Exception message
         */
        const char* what() const noexcept override;
        
        /**
         * @brief Get exit code
         * @return int Exit code
         */
        int getExitCode() const;
};

#endif // NETTWORKEXCEPTION_HPP

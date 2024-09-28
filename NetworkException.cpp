/**
 * @file NetworkException.cpp
 * @brief NetworkException class implementation
 * 
 * @author Adam Valík <xvalik05@vutbr.cz>
 * 
*/

#include "NetworkException.hpp"

const char* NetworkException::what() const noexcept {
    return message.c_str();
}

int NetworkException::getExitCode() const {
    return exitCode;
}
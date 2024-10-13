/**
 * @file Controller.hpp
 * @brief Controller class header
 * 
 * @author Adam Valík <xvalik05@vutbr.cz>
 * 
*/

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "NetworkInterface.hpp"
#include "NetworkException.hpp"
#include "NetworkCapture.hpp"
#include "ConnectionCol.hpp"
#include "StatsDisplay.hpp"
#include "globals.hpp"

#include <string>
#include <thread>
#include <chrono>
#include <iostream>
#include <ncurses.h>

using namespace std;

/**
 * @class Controller
 * @brief Controller class encapsulating the core functionality
 */
class Controller {

    ConnectionCol connectionCol;
    NetworkCapture networkCapture;
    StatsDisplay statsDisplay;

    /**
     * @brief Parse CLI args: ./isa-top -i int [-s b|p] [-t s]
     * @throws NetworkException
     * 
     * @param argc Number of arguments
     * @param argv Command-line arguments
     */
    void parseArguments(int argc, char** argv);
    
    /**
     * @brief Display help message
     */
    void printUsage() const;

    public:
        Controller() : connectionCol(), networkCapture(connectionCol), statsDisplay(connectionCol) {};

        /**
         * @brief Run the controller
         * @throws NetworkException
         * 
         * @param argc Number of arguments
         * @param argv Command-line arguments
         */
        void run(int argc, char** argv);

        /**
         * @brief Close ncurses window
         */
        static void closeNcurses();
};

#endif // CONTROLLER_HPP

/**
 * @file StatsDisplay.hpp
 * @brief StatsDisplay class header
 * 
 * @author Adam Valík <xvalik05@vutbr.cz>
 * 
*/

#ifndef STATSDISPLAY_HPP
#define STATSDISPLAY_HPP

#include "globals.hpp"
#include "ConnectionCol.hpp"

#include <ncurses.h>
#include <iomanip> 
#include <iostream>
#include <sstream>
#include <format>


using namespace std;

/**
 * @class StatsDisplay
 * @brief Ncurses Display of network statistics 
 */
class StatsDisplay {

    WINDOW *tableWin;
    int updateInterval;
    ConnectionCol& connectionCol;

    /**
     * @brief Draw the table with connections
     * 
     * @param data Vector of connections
     */
    void drawTable(vector<Connection>& data);

    /**
     * @brief Format bytes/packets per second
     * 
     * @param bytes Number of bytes/packets
     * @return string Formatted string
     */
    string formatPerSec(uint64_t bytes);

    public:
        StatsDisplay(ConnectionCol& connectionCol) : tableWin(newwin(16, 151, 0, 0)), updateInterval(1), connectionCol(connectionCol) {};

        /**
         * @brief Set update interval
         * 
         * @param updateInterval Update interval in seconds
         */
        void setUpdateInterval(int updateInterval) { this->updateInterval = updateInterval; };

        /**
         * @brief Run the display
         */
        void run();
};

#endif // STATSDISPLAY_HPP

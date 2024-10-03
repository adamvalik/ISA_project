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
 * @brief StatsDisplay class 
 */
class StatsDisplay {
    WINDOW *tableWin;
    int updateInterval;
    ConnectionCol& connectionCol;

    void drawTable();

    string formatPerSec(uint64_t bytes);

    public:
        StatsDisplay(ConnectionCol& connectionCol) : tableWin(newwin(16, 151, 0, 0)), updateInterval(1), connectionCol(connectionCol) {};

        void setUpdateInterval(int updateInterval) { this->updateInterval = updateInterval; };

        /**
         * @brief 
         */
        void run();

        void drawTable(vector<Connection>& data);


};

#endif // STATSDISPLAY_HPP

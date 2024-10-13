/**
 * @file StatsDisplay.cpp
 * @brief StatsDisplay class implementation
 * 
 * @author Adam Valík <xvalik05@vutbr.cz>
 * 
*/

#include "StatsDisplay.hpp"

// column positions for data
const int col_positions[] = {1, 49, 101, 113, 122, 134, 143}; 
// column positions for headers
const int header_positions[] = {19, 67, 100, 113, 134}; 
// vertical lines positions
const int lines_positions[] = {48, 96, 108, 129};

void StatsDisplay::drawTable(vector<Connection>& data) {
    //"                  SRC IP:PORT                                     DST IP:PORT                      PROTO        b/s  RX  p/s         b/s  TX  p/s    ");
    //|[ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff]:65535|[ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff]:65535|    TCP    |    20        20   |   130.8M   130.8M   |
    
    // header 
    mvwprintw(this->tableWin, 2, header_positions[0], "SRC IP:PORT");
    mvwprintw(this->tableWin, 2, header_positions[1], "DST IP:PORT");
    mvwprintw(this->tableWin, 2, header_positions[2], "PROTO");
    mvwprintw(this->tableWin, 2, header_positions[3], "b/s  RX  p/s");
    mvwprintw(this->tableWin, 2, header_positions[4], "b/s  TX  p/s");

    // lines
    mvwhline(this->tableWin, 4, 1, 0, 149);  
    mvwvline(this->tableWin, 1, lines_positions[0], 0, 14);  
    mvwvline(this->tableWin, 1, lines_positions[1], 0, 14);  
    mvwvline(this->tableWin, 1, lines_positions[2], 0, 14);  
    mvwvline(this->tableWin, 1, lines_positions[3], 0, 14);  

    // data
    for (size_t i = 0; i < data.size(); i++) {
        Connection conn = data[i];
        mvwprintw(this->tableWin, 5 + i, col_positions[0], conn.getSrc().c_str());
        mvwprintw(this->tableWin, 5 + i, col_positions[1], conn.getDst().c_str());
        mvwprintw(this->tableWin, 5 + i, col_positions[2], conn.getProtocol().c_str());
        mvwprintw(this->tableWin, 5 + i, col_positions[3], this->formatPerSec(conn.getRxBytes()).c_str());
        mvwprintw(this->tableWin, 5 + i, col_positions[4], this->formatPerSec(conn.getRxPackets()).c_str());
        mvwprintw(this->tableWin, 5 + i, col_positions[5], this->formatPerSec(conn.getTxBytes()).c_str());
        mvwprintw(this->tableWin, 5 + i, col_positions[6], this->formatPerSec(conn.getTxPackets()).c_str());
    }
   
    // refresh the window to show the table
    wrefresh(this->tableWin);  
}

string StatsDisplay::formatPerSec(uint64_t bytes) {
    double value = static_cast<double>(bytes);
    double bytesPerSec = value / this->updateInterval;
    string postfix = "";

    if (bytesPerSec >= 1e9) {
        bytesPerSec = bytesPerSec / 1e9;
        postfix = "G";
    } else if (bytesPerSec >= 1e6) {
        bytesPerSec = bytesPerSec / 1e6;
        postfix = "M";
    } else if (bytesPerSec >= 1e3) {
        bytesPerSec = bytesPerSec / 1e3;
        postfix = "k";
    }
    
    ostringstream out;
    out << fixed << setprecision(1) << bytesPerSec; 
    out << postfix;
    return out.str();
}

void StatsDisplay::run() {
    while (running) {
        werase(this->tableWin);
        box(this->tableWin, 0, 0);

        dataMutex.lock();
        vector<Connection> data = this->connectionCol.getConnections();
        this->connectionCol.eraseTable(); 
        dataMutex.unlock();

        drawTable(data); 

        napms(this->updateInterval * 1000);  
    }
}
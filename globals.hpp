/**
 * @file globals.hpp
 * @brief Global variables
 * 
 * @author Adam Valík <xvalik05@vutbr.cz>
 * 
*/

#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <atomic>
#include <mutex>
#include <pcap.h>

using namespace std;

// flag indicating the stats display is running
extern atomic<bool> running;

// mutex for accessing ConnectionCol data from multiple threads
extern mutex dataMutex;

// pcap handle for breaking the loop from the signal handler
extern pcap_t *handle;

// exception pointer for rethrowing exceptions from threads
extern exception_ptr threadException;

// flag indicating that ncurses is running
extern atomic<bool> ncursesRunning;

#endif // GLOBALS_HPP

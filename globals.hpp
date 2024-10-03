/**
 * @file globals.hpp
 * @brief 
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

extern atomic<bool> running;
extern mutex dataMutex;
extern pcap_t *handle;
extern exception_ptr threadException;
extern atomic<bool> ncursesRunning;

#endif // GLOBALS_HPP

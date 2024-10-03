/**
 * @file main.cpp
 * @brief 
 * 
 * @author Adam Valík <xvalik05@vutbr.cz>
 * 
*/

#include "Controller.hpp"
#include "NetworkException.hpp"
#include "globals.hpp"

#include <csignal>
#include <atomic>
#include <ncurses.h>

atomic<bool> running(true);
atomic<bool> ncursesRunning(false);
mutex dataMutex;
pcap_t *handle = nullptr;
exception_ptr threadException = nullptr;

/**
 * @brief Signal handler for SIGINT
 * 
 * @param signum Signal number
 */
void signalHandler(int signum) {
    (void)signum;
    if (handle != nullptr) {
        pcap_breakloop(handle);
    }
    running = false;
}

/**
 * @brief Main function
 * 
 * @param argc Number of arguments
 * @param argv Command-line arguments
 * @return int Exit code
 */
int main(int argc, char* argv[]) {
    signal(SIGINT, signalHandler);

    initscr();
    ncursesRunning = true;
    noecho();
    cbreak();
    curs_set(0); 

    try {
        Controller controller;
        controller.run(argc, argv);
    } catch (const NetworkException& e) {
        if (ncursesRunning) {
            endwin();
            ncursesRunning = false;
        }
        if (e.getExitCode() != EXIT_SUCCESS) {
            cerr << "[ERROR] " << e.what() << endl << endl;
        }
        return e.getExitCode();
    }
    // cleanup
    return EXIT_SUCCESS;
}
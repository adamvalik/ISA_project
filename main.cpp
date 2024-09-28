/**
 * @file main.cpp
 * @brief 
 * 
 * @author Adam Valík <xvalik05@vutbr.cz>
 * 
*/

#include "Controller.hpp"
#include "NetworkException.hpp"

#include <csignal>
#include <atomic>
#include <thread>
#include <ncurses.h>

using namespace std;

atomic<bool> running(true);

/**
 * @brief Signal handler for SIGINT
 * 
 * @param signum Signal number
 */
void signalHandler(int signum) {
    (void)signum;  
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

    try {
        Controller controller(argc, argv);
        controller.run();
    } catch (const NetworkException& e) {
        endwin();  
        if (e.getExitCode() != EXIT_SUCCESS) {
            cerr << "[ERROR] " << e.what() << endl << endl;
        }
        return e.getExitCode();
    }
    // cleanup
    endwin();  // Exit ncurses mode
    return EXIT_SUCCESS;
}
/**
 * @file Controller.cpp
 * @brief Controller class implementation
 * 
 * @author Adam Valík <xvalik05@vutbr.cz>
 * 
*/

#include "Controller.hpp"

void Controller::run(int argc, char** argv) {
    this->parseArguments(argc, argv);
    this->networkCapture.prepareHandle();

    // set the global handle for the ability to stop the capture from the signal handler
    handle = this->networkCapture.getHandle();

    // thread for capturing network traffic (pcap_loop)
    thread captureThread(&NetworkCapture::startCapture, &networkCapture);

    // thread for displaying statistics 
    thread displayThread(&StatsDisplay::run, &statsDisplay);

    // wait for threads to finish
    captureThread.join();
    displayThread.join();

    // if an exception was thrown in the threads, rethrow it
    if (threadException) {
        rethrow_exception(threadException);  
    }

    // cleanup
    this->closeNcurses();
}

void Controller::parseArguments(int argc, char** argv) {
    // ./isa-top -i
    if (argc == 2 && (string(argv[1]) == "-i")) {
        // display list of active interfaces
        NetworkInterface::listInterfaces();
        throw NetworkException(0);
    }

    // ./isa-top -h | --help
    if (argc == 2 && (string(argv[1]) == "-h" || string(argv[1]) == "--help")) {
        this->closeNcurses();
        this->printUsage();
        throw NetworkException(0);
    }
    
    if (argc == 1) {
        this->closeNcurses();
        this->printUsage();
        throw NetworkException(1, "No arguments specified");
    }

    if (argc % 2 == 0 || argc > 7) {
        this->closeNcurses();
        this->printUsage();
        throw NetworkException(1, "Invalid number of arguments");
    }



    // ./isa-top -i int [-s b|p] [-t s]
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-i") {
            string interface = argv[++i];
            if (!NetworkInterface::validateInterface(interface)) {
                NetworkInterface::listInterfaces();
                throw NetworkException(1, "Invalid interface: " + interface);
            }
            this->networkCapture.setInterface(interface);
        } else if (arg == "-s") {
            string sortOpt = argv[++i];
            if (sortOpt != "b" && sortOpt != "p") {
                this->closeNcurses();
                this->printUsage();
                throw NetworkException(1, "Invalid sort option: " + sortOpt + " (must be b or p)");
            }
            this->connectionCol.setSortOpt(sortOpt[0]);
        } else if (arg == "-t") {
            int timeOpt;
            try {
                timeOpt = stoi(argv[++i]);
            } catch (const invalid_argument& e) {
                this->closeNcurses();
                this->printUsage();
                throw NetworkException(1, "Time option must be an integer");
            }

            if (timeOpt < 1) {
                this->closeNcurses();
                this->printUsage();
                throw NetworkException(1, "Time option must be a positive integer");
            }
            this->statsDisplay.setUpdateInterval(timeOpt);
        } else {
            this->closeNcurses();
            this->printUsage();
            throw NetworkException(1, "Unknown argument: " + arg);
        }
    }
}

void Controller::printUsage() const {
    cerr << endl;
    cerr << "Usage: ./isa-top -i int [-s b|p] [-t s]" << endl;
    cerr << "  -i [interface]                   interface to capture network traffic on" << endl;
    cerr << "  -s b|p         (default: b)      sort output by bytes/packets per second" << endl;
    cerr << "  -t [seconds]   (default: 1s)     update time interval" << endl;
    cerr << "  -i                               display active interfaces" << endl;
    cerr << "  -h|--help                        display usage" << endl << endl;
    cerr << "run $ man ./isa-top.1 for more information" << endl << endl;
}

void Controller::closeNcurses() {
    // ensure that ncurses is still running before closing it (closing twice causes errors)
    if (ncursesRunning) {
        endwin();
        ncursesRunning = false;
    }
}
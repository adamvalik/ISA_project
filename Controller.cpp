/**
 * @file Controller.cpp
 * @brief Controller class implementation
 * 
 * @author Adam Valík <xvalik05@vutbr.cz>
 * 
*/

#include "Controller.hpp"

Controller::Controller(int argc, char** argv) {
    this->sortOpt = "b";
    this->updateInterval = 1;
    this->parseArguments(argc, argv);
    this->networkCapture.setInterface(this->interface);
    this->networkCapture.prepareHandle();
}

void Controller::run() {
    // initscr();              // Start ncurses mode
    // noecho();               // Don't echo keypresses
    // cbreak();               // Disable line buffering
    // curs_set(0);            // Hide the cursor

    // statsDisplay.init();

    thread captureThread(&NetworkCapture::startCapture, &networkCapture);
    // thread displayThread(&StatsDisplay::run, &statsDisplay);

    captureThread.join();
    // displayThread.join();

    // cleanup
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
        this->printUsage();
        throw NetworkException(0);
    }
    
    if (argc == 1) {
        this->printUsage();
        throw NetworkException(1, "No arguments specified");
    }

    if (argc % 2 == 0 || argc > 7) {
        this->printUsage();
        throw NetworkException(1, "Invalid number of arguments");
    }



    // ./isa-top -i int [-s b|p] [-t s]
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-i") {
            this->interface = argv[++i];
            if (!NetworkInterface::validateInterface(this->interface)) {
                NetworkInterface::listInterfaces();
                throw NetworkException(1, "Invalid interface: " + this->interface);
            }
        } else if (arg == "-s") {
            this->sortOpt = argv[++i];
            if (this->sortOpt != "b" && this->sortOpt != "p") {
                this->printUsage();
                throw NetworkException(1, "Invalid sort option: " + this->sortOpt + " (must be b or p)");
            }
        } else if (arg == "-t") {
            string strTimeOpt = argv[++i];
            try {
                this->updateInterval = stoi(strTimeOpt);
            } catch (const invalid_argument& e) {
                this->printUsage();
                throw NetworkException(1, "Time option must be an integer");
            }

            if (this->updateInterval < 1) {
                this->printUsage();
                throw NetworkException(1, "Time option must be a positive integer");
            }
        } else {
            this->printUsage();
            throw NetworkException(1, "Unknown argument: " + arg);
        }
    }
}

void Controller::printUsage() const {
    cerr << endl;
    cerr << "Usage: ./isa-top -i int [-s b|p] [-t s]" << endl;
    cerr << "  -i [INTERFACE]                   interface to capture network traffic on" << endl;
    cerr << "  -s b|p         (default: b)      sort output by bytes/packets per second" << endl;
    cerr << "  -t [SECONDS]   (default: 1s)     update time interval" << endl;
    cerr << "  -i                               display active interfaces" << endl;
    cerr << "  -h|--help                        display usage" << endl << endl;
}
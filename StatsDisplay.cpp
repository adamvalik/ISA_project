// const int col_positions[] = {1, 49, 101, 112, 120, 133, 141}; 


// void draw_table(WINDOW *win, vector<vector<string>>& data) {
//     mvwprintw(win, 2, 1, "                  SRC IP:PORT                                     DST IP:PORT                      PROTO        b/s  RX  p/s         b/s  TX  p/s    ");
// //                       |[ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff]:65535|[ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff]:65535|    TCP    |   130.8M  130.8M   |   130.8M  130.8M   |


//     mvwhline(win, 4, 1, 0, 149);  

//     mvwvline(win, 1, 48, 0, 14);  
//     mvwvline(win, 1, 96, 0, 14);  
//     mvwvline(win, 1, 108, 0, 14);  
//     mvwvline(win, 1, 129, 0, 14);  

//     // Rows for data
//     for (int i = 0; i < data.size(); ++i) {
//         for (int j = 0; j < data[i].size(); ++j) {
//             mvwprintw(win, i + 5, col_positions[j], "%s", data[i][j].c_str());
//         }
//     }
    
//     wrefresh(win);  // Refresh the window to show the table
// }

// int table_rows = 10, table_cols = 7;
//     vector<vector<string>> table_data(table_rows, vector<string>(table_cols, "0"));

//     WINDOW *table_win = newwin(16, 151, 0, 0);  // Create a window for the table
    

//     for (int seconds = 0; seconds < 3; ++seconds) {
//         // Simulate table data update (just increment values for example)
//         for (int i = 0; i < table_rows; ++i) {
//             for (int j = 0; j < table_cols; ++j) {
//                 table_data[i][j] = to_string(i * table_cols + j + seconds);
//             }
//         }

//         vector<vector<string>> data = {
//             {"[2001:67c:1220:ff00::17]:43521", "[2a00:1450:4014:80e::200e]:443", "tcp", "20.2M", "5.2k", "2.1M", "426.2"},
//             {"[2001:67c:1220:ff00::17]:43521", "[2a00:1450:4014:80e::200e]:443", "tcp", "20.2M", "5.2k", "2.1M", "426.2"},
//             {"103.69.171.108:50438", "95.82.190.248:36622", "tcp", "30.1M", "6.2k", "2.2M", "548.2"},
//             {"[ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff]:65535", "[ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff]:65535", "icmp", "130.8M", "130.8M", "130.8M", "130.8M"},
//             {"[ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff]:65535", "[ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff]:65535", "icmp", "130.8M", "130.8M", "130.8M", "130.8M"},
//             {"[ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff]:65535", "[ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff]:65535", "icmp", "130.8M", "130.8M", "130.8M", "130.8M"},
//             {"[ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff]:65535", "[ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff]:65535", "icmp", "130.8M", "130.8M", "130.8M", "130.8M"},
//             {"147.229.13.210:65067", "76.11.79.218:53913", "udp", "12.2M", "2.8k", "1.9M", "3.6K"},
//             {"147.229.13.210:65067", "76.11.79.218:53913", "udp", "12.2M", "2.8k", "1.9M", "3.6K"},
//             {"147.229.13.210", "76.11.79.218", "icmp", "50.1k", "120", "35k", "20"}
//         };

//         werase(table_win);  // Clear the window
//         box(table_win, 0, 0);  // Draw a box around the window
//         draw_table(table_win, data);  // Draw the table with updated values

//         napms(1000);  // Wait for 1 second
//     }
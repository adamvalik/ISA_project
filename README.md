```
ISA-TOP(1)                                            General Commands Manual                                             ISA-TOP(1)

NAME
       isa-top - monitoring network traffic statistics

SYNOPSIS
       isa-top -i interface [-s b|p] [-t seconds]

DESCRIPTION
       isa-top captures packets on the specified interface and displays real-time statistics about the connections and speed of the traffic.

OPTIONS
       -i interface
              Specify the network interface to capture traffic on. This option is required for the application to start monitoring.

       -s b|p Sort the output by either bytes (`b`) or packets (`p`) per second. The default sorting option is by bytes (`b`).

       -t seconds
              Set the update time interval in seconds. The default interval is 1 second.

       -i     Display a list of active network interfaces.

       -h, --help
              Display a help message.

EXAMPLES
       To capture network traffic on the `en0` interface and sort the output by bytes per second:
              $ ./isa-top -i en0

       To capture traffic on the `en0` interface, sort the output by packets per second and update every 5 seconds:
              $ ./isa-top -i en0 -s p -t 5

       To display a list of active network interfaces without capturing any traffic:
              $ ./isa-top -i
```

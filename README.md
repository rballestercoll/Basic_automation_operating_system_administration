# Basic_automation_operating_system_administration
> Application capable of modifying part of the network configuration of the local machine, only as far as domain name resolution is concerned, for an adapter to be determined from a list of DNS servers written in a text file, in case the current DNS server is not the fastest among those provided.

## Route
1. Initially prompt for the name and path of the dnsips.txt file and display the contents of this file on the screen.
2. Ask the user which network adapter he/she wants to modify from the list of possible adapters previously displayed on the screen and show the DNS servers configured only on this one, on the chosen one.
3. Read the file initially provided with the IPs of the DNS servers, and check if those IPs are accessible, and in case they are, it is necessary to write them in a temporary file (this will be considered a requirement) but it will not be deleted, but a record of their existence will be left.
4. Open the temporary file created in the previous point and check which of the DNS configured in the adapter determined in point 7 and those written in this file is the fastest.
5. If you do not have the fastest DNS configured, change the DNS of the adapter indicated in point 6 to the fastest one.
6. In the event that two DNS servers tie in speed, the DNS will be reconfigured for the one with the lower number of hops, since proximity is considered a point to be taken into account.

# portupdates
app for FreeBSD that checks /usr/ports/UPDATING for issues with installed apps, search back n number of days
How to Use:
by default, portupdates will look for a config file in ~/.config/portupdates.txt. If found it will check for updates to /usr/ports/UPDATING
since the program was last run. If no file is found, it will default to 7 days.
To check an arbitrary amount of time, append the number of days back you wish to check. I.e. "portupdates 30" where 30 is the number of days
back you wish to check.
This program assumes that pkg has been installed, and that you will be using portmaster to update your ports.


to Build:
This library uses the boost library. I installed headers with "pkg install boost-all" before building.

g++ -o portupdates main.cpp

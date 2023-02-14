# portupdates
app for FreeBSD that checks /usr/ports/UPDATING for issues with installed apps, search back n number of days
How to Use:
"portupdates 30" where 30 is the number of days back you wish to check.
This program assumes that pkg has been installed, and that you will be using portmaster -a to update your ports.


to Build:
This library uses the boost library. I installed headers with "pkg install boost-all" before building.
g++ -o portupdates main.cpp

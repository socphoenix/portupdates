/*-
 * Copyright (c) 2023 Michael Bell
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

/* This program uses the Boost library under the Boost license:
 * Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <boost/date_time/gregorian/gregorian.hpp>
using namespace boost::gregorian;
using namespace std;

int main (int argc, char** argv) {
  if(argc < 2) {
    cout << "Proper format is 'test 1' where 1 equals the number of days back you wish to search \n";
    return 1;
  }
  int cutOff = stoi(argv[1]);
  string line;
  string appline;
  string cont;
  system("pkg query %n > /tmp/applist.txt");
  ifstream applist ("/tmp/applist.txt");
  if (applist.is_open())
  {
    //use boost
    string curTime;
    date d = day_clock::universal_day();
    d -= days(cutOff);
    curTime = to_iso_string(d);
    while ( getline (applist,appline) )
    {
      ifstream UPDATING ("/usr/ports/UPDATING");
      while ( getline (UPDATING,line) )
      {
       //check date, make sure it's actually a date, then if less than cutoff break.
      if(regex_search(line, regex("[0-9]:")) && line.length() == 9) {
         if(stoi(line) < stoi(curTime)) {
           break;
        }
      }
      //check if match, then check if "affects" in line. then show found.
      else if(regex_search(line, regex(appline)) && regex_search(line, regex("AFFECTS"))) {
        cout << "FOUND " << appline << "\n" << line << "\n";
      }
    }
    UPDATING.close();
  }
    applist.close();
    system("rm /tmp/applist.txt");
  }

  else cout << "Unable to open file";

  //add ability to use portmaster/pkg/whatever inline.
  cout << "Would you like to continue upgrading? [y/n]: ";
  cin >> cont;
  if(cont == "y") {
    system("portmaster -a");
  }

  return 0;
}

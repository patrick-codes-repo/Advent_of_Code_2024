#include <ios>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
  ifstream iFile;
  iFile.open("../input/day2");

  if(!iFile.is_open())
  {
    cout << "File failed to open" << endl;
    return 1;
  }

  string line;
  stringstream ss;

  int number;
  int lastNumber;
  bool counted;
  int diff;

  bool safe;
  int safeCount = 0;
  int change;

  while(getline(iFile, line))
  {
    ss << line;

    counted = false;
    safe = true;
    change = 0;

    while(true)
    {
      lastNumber = number;
      ss >> number;

      if(ss.fail())
        break;

      if(counted)
      {
        diff = number - lastNumber;

        if(change == 0)
          change = diff;

        if(abs(diff) < 1 || abs(diff) > 3)
          safe = false;
        if((diff > 0 && change < 0) || (diff < 0 && change > 0))
          safe = false;
      }

      counted = true;

      if(!safe)
        break;
    }    

    if(safe)
      safeCount++;

    ss.clear();
    ss.str("");
  }

  cout << safeCount << endl;
}

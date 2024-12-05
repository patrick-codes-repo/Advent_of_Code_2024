#include <cctype>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

using namespace std;

string getNumber(char buffer[], size_t &pos);
bool getChar(char buffer[], size_t &pos, char c);

int main()
{
  ifstream iFile;
  iFile.open("../input/day3");

  if(!iFile.is_open())
  {
    cout << "File failed to open" << endl;
    return 1;
  }

  iFile.seekg(0, iFile.end);
  int fileLength = iFile.tellg();

  iFile.seekg(0, iFile.beg);

  char buffer[fileLength];
  iFile.read(buffer, fileLength);
  iFile.close();

  string str = buffer;
  size_t pos = 0;

  int x;
  int y;

  int sum = 0;

  while(true)
  {
    pos = str.find("mul(", pos);

    if(pos == string::npos || pos > fileLength - 8)
      break;

    pos += 4;

    try {
      x = stoi(getNumber(buffer, pos));
    } catch (invalid_argument const& e) {
      continue;
    }

    if(!getChar(buffer, pos, ','))
      continue;

    try {
      y = stoi(getNumber(buffer, pos));
    } catch (invalid_argument const& e) {
      continue;
    }

    if(!getChar(buffer, pos, ')'))
      continue;

    sum += x*y;
  }
  
  cout << "Sum: " << sum << endl;

  return 0;
}

string getNumber(char buffer[], size_t &pos)
{
  string number = "";
  
    while(isdigit(buffer[pos]))
    {
      number += buffer[pos];
      pos++;
    }

  return number;
}

bool getChar(char buffer[], size_t &pos, char c)
{
  pos++;
  return buffer[pos - 1] == c;
}

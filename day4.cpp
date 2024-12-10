#include <iostream>
#include <fstream>

using namespace std;

int findXMAS(char *puzzle, int row, int column, int lineLength, int lineCount);
bool foundDir(char *puzzle, int row, int column, int lineLength, int lineCount, int &xDir, int &yDir);
bool checkDirection(char *puzzle, int row, int column, int lineLength, int lineCount, int &xDir, int &yDir);

int main()
{
  ifstream iFile;
  iFile.open("../input/day4");

  if(!iFile.is_open())
  {
    cout << "File failed to open" << endl;
    return 1;
  }

  string line;
  getline(iFile, line);

  int lineLength = line.length();

  iFile.seekg(0, iFile.end);
  int lineCount = iFile.tellg() / lineLength - 1;

  iFile.seekg(0, iFile.beg);

  char puzzle[lineLength][lineCount];
  char *puzzlePointer = puzzle[0];

  int i = 0;
  int row;
  int column;

  while(i < lineLength * lineCount)
  {
    row = i / lineCount;
    column = i % lineLength;
    iFile >> puzzle[row][column];
    i++;
  }

  iFile.close();

  i = 0;
  int occurrences = 0;

  while(i < lineLength * lineCount)
  {
    row = i / lineCount;
    column = i % lineLength;

    if(puzzle[row][column] == 'X')
      occurrences += findXMAS((char*) puzzle, row, column, lineLength, lineCount);

    i++;
  }
    cout << "Occurrences: " << occurrences << endl;
    return 0;
}

int findXMAS(char *puzzle, int row, int column, int lineLength, int lineCount)
{
  int foundCount = 0;

  for(int yDir = -1; yDir <= 1; yDir++)
  {
    for(int xDir = -1; xDir <= 1; xDir++)
    {
      if(yDir == 0 && xDir == 0)
        continue;

      if(checkDirection(puzzle, row, column, lineLength, lineCount, xDir, yDir))
        foundCount++;
    }
  }

  return foundCount;
}

bool checkDirection(char *puzzle, int row, int column, int lineLength, int lineCount, int &xDir, int &yDir)
{
  if((row > lineCount - 4 && yDir > 0) || (row < 3 && yDir < 0) || (column > lineLength - 4 && xDir > 0) || (column < 3 && xDir < 0))
    return false;

   if(!(*((puzzle + ((row + yDir) * lineLength) + (column + xDir))) == 'M'))
     return false;
      
  if(!(*((puzzle + ((row + yDir * 2) * lineLength) + (column + xDir * 2)))  == 'A'))
    return false;

  if(!(*((puzzle + ((row + yDir * 3) * lineLength) + (column + xDir * 3))) == 'S'))
    return false;

  return true;
}

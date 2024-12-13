#include <iostream>
#include <fstream>

using namespace std;

int main()
{
  ifstream iFile;
  iFile.open("../input/day6");

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

  char map[lineLength][lineCount];

  int row;
  int column;

  for(int i = 0; i < lineLength * lineCount; i++)
  {
    iFile >> map[i / lineCount][i % lineLength];

    if(map[i / lineCount][i % lineLength] == '^')
    {
      row = i / lineCount;
      column = i % lineLength;
    }
  }

  iFile.close();

  int rowChange = 0;
  int columnChange = 0;

  while(true)
  {
    switch (map[row][column])
    {
      case '^':
      {
        rowChange = -1;
        columnChange = 0;
        break;
      }
      case '>':
      {
        rowChange = 0;
        columnChange = 1;
        break;
      }
      case '<':
      {
        rowChange = 0;
        columnChange = -1;
        break;
      }
      case 'v':
      {
        rowChange = 1;
        columnChange = 0;
        break;
      }
    }

    if(row + rowChange >= lineCount || column + columnChange >= lineLength || row + rowChange < 0 || column + columnChange < 0)
    {
      map[row][column] = 'X';
      break;
    }

    if(map[row + rowChange][column + columnChange] == '#')
    {
      switch (map[row][column])
      {
        case '^':
        {
          map[row][column] = '>';
          break;
        }
        case '>':
        {
          map[row][column] = 'v';
          break;
        }
        case '<':
        {
          map[row][column] = '^';
          break;
        }
        case 'v':
        {
          map[row][column] = '<';
          break;
        }
      }
      continue;
    }

    map[row + rowChange][column + columnChange] = map[row][column];
    map[row][column] = 'X';

    row += rowChange;
    column += columnChange;
  }

  int count = 0;
  
  for(int i = 0; i < lineLength * lineCount; i++)
  {
    if(map[i / lineCount][i % lineLength] == 'X')
      count++;
  }

  cout << "Count: " << count << endl;
  return 0;
}

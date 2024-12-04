#include <cstdlib>
#include <ios>
#include <iostream>
#include <fstream>

using namespace std;

void quicksort(int arr[], int start, int end);

int main()
{
  int lineCount = 0;
  string line;

  ifstream iFile;
  iFile.open("../input/day1");

  if(!iFile.is_open())
  {
    cout << "File failed to open" << endl;
    return 1;
  }

  while(getline(iFile, line))
    lineCount++;

  int *lNumbers = new int[lineCount];
  int *rNumbers = new int[lineCount];

  iFile.clear();
  iFile.ignore(80);
  iFile.seekg(0, iFile.beg);

  for(int i = 0; i < lineCount; i++)
  {
    iFile >> lNumbers[i];
    iFile >> rNumbers[i];
  }

  iFile.close();

  quicksort(lNumbers, 0, lineCount - 1);
  quicksort(rNumbers, 0, lineCount - 1);

  int sum = 0;

  for(int i = 0; i < lineCount; i++)
    sum += abs(lNumbers[i] - rNumbers[i]);

  cout << sum << endl;

  return 0;
}

void quicksort(int arr[], int start, int end)
{
  //Base case
  if(end - start <= 0)
    return;

  int i = start - 1;
  int temp;

  for(int j = start; j <= end; j++)
  {
    //If arr[j] is less than the pivot value, increment i then swap arr[i] and arr[j].
    //Otherwise nothing is done. 
    //This results in all values lower than the pivot value being placed towards the beginning of the array.
    if(arr[j] < arr[end])
    {
      i++;
      temp = arr[j];
      arr[j] = arr[i];
      arr[i] = temp;
    }
  }

  //i + 1 is now equal to the index where the pivot value belongs. 
  //end is the current index of the pivot value. 
  //So switch the values at i+1 and end.
  i++;
  temp = arr[end];
  arr[end] = arr[i];
  arr[i] = temp;

  //Elements to the left of the pivot are less than it and elements to the right are greater.
  //Recurse above for each half to get them in order.
  quicksort(arr, start, i - 1);
  quicksort(arr, i + 1, end);
}

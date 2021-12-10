#include <iostream>

using namespace std;

int main() {
  int* m1 = new int[3*3];
  int* m2 = new int[3*1];

  cout << endl << "Before forming the array" << endl;
  for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 3; j++) {
      m1[j+i * 3] = i;
      cout << m1[j+i * 3] << " ";
    }
  }
  
  cout << endl << endl << "After forming an array and calling it again" << endl;
  for (int i =1; i<=3; i++){
    for (int j=1; j<=3; j++){
      cout << m1[j+i * 3] << " ";
    }
    cout << endl;
  }

  for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 1; j++) {
      m2[j+i * 1] = 4;
    }
  }

  for (int i =1; i<=3; i++){
    for (int j=1; j<=3; j++){
      cout << m1[j+i * 3] << " ";
    }
    cout << endl;
  }
}
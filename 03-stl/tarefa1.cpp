#include <iostream>

int main() {
  int *ptr = new int(0);
  for(int f=0;f<1024*1024*1024;f++) {
    ptr = new int(f);
  }
  std::cout << "valor final = " << *ptr << std::endl;
  delete ptr;
}

#include <iostream>
#include <memory>

int foo(int x) {
	std::unique_ptr<int[]> vec1(new int[8]);
	for(int f=0;f<8;f++) vec1[f] = f*x;
	auto vec2 = vec1.get();
	int tmp = vec1[0]+vec1[4]+vec1[7]-vec1[5];
	return tmp;
}

int main() {
	long int tmp = 0;
	for(int f=0;f<1024*1024*512;f++)  tmp += foo(f);
	std::cout << tmp << std::endl;
}

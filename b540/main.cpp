#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	int data[6];
	#define width (data[0] + data[1] + data[2])
	#define A data[0] * data[0]
	#define B data[2] * data[2]
	#define C data[4] * data[4]
	while(std::cin >> data[0] >> data[1] >> data[2] >> data[3] >> data[4] >> data[5]) std::cout << width * width - A - B - C << std::endl; 
}

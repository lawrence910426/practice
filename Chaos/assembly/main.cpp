#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;

int count = 0;
int exec();
void asdf(int (*)());

int exec()
{
	cout << count++ << " asdf" << endl;
	asdf(&exec);
}

void asdf(int (*function)())
{
	(*function)();
}

int main(int argc, char** argv) {
	int (*function)() = &exec;
	cout << function() << endl;
	//asdf(&exec);
	return 0;
}

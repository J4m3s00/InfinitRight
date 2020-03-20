#include "prefix.h"

using namespace IR;

int main()
{
	InfinitRightObject obj;
	obj.SetName("Assembly Group.1");

	InfinitRightObject obj2;
	obj2.SetName("Assembly Group.2");

	IRJson output_array = IRJson::array();
	IRJson first = IRJson::object();
	obj.SetJs(first);
	output_array.push_back(first);
	obj2.SetJs(first);
	output_array.push_back(first);

	std::cout << output_array.dump() << std::endl;

	return 0;
}
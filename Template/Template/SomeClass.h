#include <string>
#include <vector>

class SomeClass
{
public:
	SomeClass();
	~SomeClass();
	void callScript();
private:
	int para_int0 = 8;
	int para_int1 = 7;
	int para_int2 = 6;
	std::vector<int> para_vector = {para_int1, para_int2};
	int para_int3 = 100;
	int para_int4 = 101;
	float para_float = 1.99;
	std::string para_string = "Hello World";
};

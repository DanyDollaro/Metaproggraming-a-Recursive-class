#include <iostream>
#include <type_traits>

struct VoidStruct
{

};

template<size_t nRec>
class RecursiveStruct
{
public:
	RecursiveStruct() = default;
	std::conditional_t<!!nRec, RecursiveStruct<nRec - 1>, VoidStruct> next;
	int data;
};

template<class Ty, class... Args>
class HeterogeneousStruct
{
public:
	HeterogeneousStruct() = default;
	HeterogeneousStruct<Args...> next;
	Ty data;
};

template<class Ty>
class HeterogeneousStruct<Ty>
{
public:
	HeterogeneousStruct() = default;
	Ty data;
};

int main()
{
	RecursiveStruct<10> rec_struct;
	rec_struct.next.next.next.next.next.next.next.next.next.next.data = 1337;
	rec_struct.next.next.next.data = 1338;
	std::cout << rec_struct.next.next.next.data << '\n';

	HeterogeneousStruct<bool, int, double> het_struct;
	std::cout << typeid(het_struct.data).name() << '\n';
	std::cout << typeid(het_struct.next.data).name() << '\n';
	std::cout << typeid(het_struct.next.next.data).name() << '\n';
}
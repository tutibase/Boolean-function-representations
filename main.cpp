// 16. (0000 1110 1101 1010) 
// (b∧¬d)∨(a∧d∧¬b)∨(a∧¬b∧¬c)∨(b∧¬a∧¬c)
#include <iostream>
#include "boolFunc.h"
#include <vector>

int main()
{
	boolFunc myFunc;
	myFunc.createSDNF();
	myFunc.createSKNF();
	myFunc.createZhegalkin();

	std::vector<bool> tmp = {0,0,0,0};
	std::cout << "a  b  c  d\tfunc\tSDNF\tSKNF\tPolyZ\tBDD" << std::endl;
	for (int i = 0; i < 16; i++) {
		tmp = { myFunc.a[i], myFunc.b[i], myFunc.c[i], myFunc.d[i] };
		std::cout << tmp[0] << "  " << tmp[1] << "  " << tmp[2] << "  " << tmp[3] << "\t";
		std::cout << myFunc.f[i] << '\t';

		std::cout << myFunc.valSDNF(tmp) << '\t';
		std::cout << myFunc.valSKNF(tmp) << '\t';
		std::cout << myFunc.valZhegalkin(tmp) << '\t';
		std::cout << myFunc.valBDD(tmp) << std::endl;
	}


	myFunc.printSDNFstring();
	myFunc.printSKNFstring();
	myFunc.printZhegalkinString();
	myFunc.checkFunc();

	//bool a, b, c, d;
	//std::cout << "\n\nEnter the input values: ";
	//std::cin >> a >> b >> c >> d;
	//std::cout << "\nAccording to Zhegalkin polynomial f(" << a 
	//	<< ", " << b << ", " << c << ", " << d << ") = " << myFunc.valZhegalkin({ a,b,c,d });
}

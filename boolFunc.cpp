#include "boolFunc.h"
//Branch* globOne;

boolFunc::boolFunc() {
	a = { 0,0,0,0, 0,0,0,0, 1,1,1,1, 1,1,1,1 };
	b = { 0,0,0,0, 1,1,1,1, 0,0,0,0, 1,1,1,1 };
	c = { 0,0,1,1, 0,0,1,1, 0,0,1,1, 0,0,1,1 };
	d = { 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1 };
	f = { 0,0,0,0, 1,1,1,0, 1,1,0,1, 1,0,1,0 };

	BDDRoot = new Branch;
	// b
	BDDRoot->one = new Branch;
	BDDRoot->zero = new Branch;
	// a0
	BDDRoot->zero->one = new Branch;
	BDDRoot->zero->zero = new Branch;

	Branch* zeroEnd = BDDRoot->zero->zero;
	zeroEnd->Data = 0;
	// a1
	BDDRoot->one->zero = new Branch;
	BDDRoot->one->one = new Branch;
	// d0 
	BDDRoot->zero->one->zero = new Branch; // c
	BDDRoot->zero->one->one = new Branch;

	Branch* oneEnd = BDDRoot->zero->one->one;
	oneEnd->Data = 1;
	// d1
	BDDRoot->one->zero->one = BDDRoot->zero->one->zero; // c
	BDDRoot->one->zero->zero = oneEnd;
	// d2
	BDDRoot->one->one->zero = oneEnd;
	BDDRoot->one->one->one = zeroEnd;
	// c
	BDDRoot->zero->one->zero->one = zeroEnd;
	BDDRoot->zero->one->zero->zero = oneEnd;

	oneEnd->one = oneEnd;
	oneEnd->zero = oneEnd;
	zeroEnd->one = zeroEnd;
	zeroEnd->zero = zeroEnd;

	//globOne = oneEnd;
}

boolFunc::~boolFunc() {
	//FreeTree(BDDRoot);
}

// input - вектор из 4 значений
bool boolFunc::valBDD(std::vector<bool> inp) {
	std::vector<bool> newInp = { inp[1], inp[0], inp[3], inp[2] };
	Branch* tmp = BDDRoot;
	for (int i = 0; i < inp.size(); i++) {
		if (newInp[i] == 0) tmp = tmp->zero;
		else tmp = tmp->one;
	}

	return tmp->Data;
}

void boolFunc::createSDNF() {

	for (int i = 0; i < f.size(); i++) {
		if (f[i] == 1) {
			SDNF.push_back({ a[i], b[i], c[i], d[i] });
		}
	}
}

bool boolFunc::valSDNF(std::vector<bool> inp) {
	for (int i = 0; i < SDNF.size(); i++) {
		if (SDNF[i] == inp) {
			return 1;
		}
	}
	return 0;
}

void boolFunc::printSDNF() {
	if (SDNF.size() == 0) {
		std::cout << 0;
		return;
	}

	for (int i = 0; i < f.size(); i++) {
		valSDNF({ a[i], b[i], c[i], d[i] });
		std::cout << std::endl;
	}
}

void boolFunc::printSDNFstring() {
	std::cout << "\nSDNF:\n";
	for (int i = 0; i < SDNF.size(); i++) {
		if (i != 0 and i != SDNF.size()) std::cout << " V ";

		if (SDNF[i][0] == 1) std::cout << "a";
		else std::cout << "(~a)";
		if (SDNF[i][1] == 1) std::cout << "b";
		else std::cout << "(~b)";
		if (SDNF[i][2] == 1) std::cout << "c";
		else std::cout << "(~c)";
		if (SDNF[i][3] == 1) std::cout << "d";
		else std::cout << "(~d)";
	}
	std::cout << std::endl;
}

void boolFunc::createSKNF() {

	for (int i = 0; i < f.size(); i++) {
		if (f[i] == 0) {
			SKNF.push_back({ a[i], b[i], c[i], d[i] });
		}
	}
}

bool boolFunc::valSKNF(std::vector<bool> inp) {
	for (int i = 0; i < SKNF.size(); i++) {
		if (SKNF[i] == inp) {
			return 0;
		}
	}
	return 1;
}

void boolFunc::printSKNF() {
	if (SKNF.size() == 0) {
		std::cout << 1;
		return;
	}

	for (int i = 0; i < f.size(); i++) {
		valSKNF({ a[i], b[i], c[i], d[i] });
		std::cout << std::endl;
	}
}

void boolFunc::printSKNFstring() {
	std::cout << "\nSKNF:\n";
	for (int i = 0; i < SKNF.size(); i++) {
		std::cout << "(";

		if (SKNF[i][0] == 0) std::cout << "a V ";
		else std::cout << "(~a) V ";
		if (SKNF[i][1] == 0) std::cout << "b V ";
		else std::cout << "(~b) V ";
		if (SKNF[i][2] == 0) std::cout << "c V ";
		else std::cout << "(~c) V ";
		if (SKNF[i][3] == 0) std::cout << "d";
		else std::cout << "(~d)";

		std::cout << ")";
		if (i != (SKNF.size()-1)) std::cout << "*";//std::cout << " /\\ ";
	}
}

// b+bcd+a+ac+acd+ab+abd+abc
void boolFunc::createZhegalkin() {
	Zhegalkin.push_back(f[0]);
	std::vector<bool> prev = f;
	std::vector<bool> next;
	for (int i = 0; i < f.size() - 1; i++) {
		for (int j = 0; j < prev.size() - 1; j++) {
			next.push_back(prev[j] ^ prev[j + 1]);
		}
		Zhegalkin.push_back(next[0]);
		prev = next;
		next.resize(0);
	}
}

bool boolFunc::valZhegalkin(std::vector<bool> inp) {
	bool result = 0;
	for (int i = 0; i < Zhegalkin.size(); i++) {
		if (Zhegalkin[i] == 1) {
			bool tmp = 1;
			if (a[i]) tmp = tmp && inp[0];
			if (b[i]) tmp = tmp && inp[1];
			if (c[i]) tmp = tmp && inp[2];
			if (d[i]) tmp = tmp && inp[3];

			result ^= tmp;
		}
	}

	return result;
}

void boolFunc::printZhegalkinString() {
	std::cout << "\n\nZhegalkin Polynom:\n";
	bool flag = 0;
	for (int i = 0; i < Zhegalkin.size(); i++) {
		if (Zhegalkin[i] == 1) {
			if (flag && i != Zhegalkin.size()) std::cout << " + ";
			if (a[i]) std::cout << "a";
			if (b[i]) std::cout << "b";
			if (c[i]) std::cout << "c";
			if (d[i]) std::cout << "d";
			flag = 1;
		}
	}
}


void boolFunc::checkFunc() {
	bool flagRes = 1;
	std::vector<bool> tmp;
	for (int i = 0; i < f.size(); i++) {
		tmp = { a[i], b[i], c[i], d[i] };
		if ((valSDNF(tmp) != f[i]) or (valSKNF(tmp) != f[i]) or
			(valBDD(tmp) != f[i]) or (valZhegalkin(tmp) != f[i])) flagRes = 0;
	}

	if (flagRes) std::cout << "\n\ntest is successful!";
	else std::cout << "\n\ntest failed!";
}


//void FreeTree(Branch* aBranch)
//{
//	if (!aBranch) return;
//	FreeTree(aBranch->one);
//	FreeTree(aBranch->zero);
//	delete aBranch;
//	return;
//}
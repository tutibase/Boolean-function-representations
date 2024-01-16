#pragma once
#include <vector>
#include <iostream>


class Branch {
public:
	bool Data;
	Branch* one;
	Branch* zero;
};



class boolFunc {
public:
	boolFunc();
	~boolFunc();

	void checkFunc();

	bool valBDD(std::vector<bool> inp);

	void createSDNF();
	void printSDNF();
	bool valSDNF(std::vector<bool> inp);
	void printSDNFstring();

	void createSKNF();
	void printSKNF();
	bool valSKNF(std::vector<bool> inp);
	void printSKNFstring();

	void createZhegalkin();
	bool valZhegalkin(std::vector<bool> inp);
	void printZhegalkinString();

	std::vector<bool> a;
	std::vector<bool> b;
	std::vector<bool> c;
	std::vector<bool> d;
	std::vector<bool> f;
	

	std::vector<std::vector<bool>> SDNF;
	std::vector<std::vector<bool>> SKNF;
	std::vector<bool> Zhegalkin;
	
	Branch *BDDRoot;
};

//сднф - вектор векторов размера 4 (значения a,b,c,d для подходящих строк)
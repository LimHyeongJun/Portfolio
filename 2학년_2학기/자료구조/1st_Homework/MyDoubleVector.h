//Name: ¿”«¸¡ÿ
//ID: 2016726082

#pragma once
#include <algorithm>
#include <string>
#include <cassert>
#include <iostream>
#include <assert.h>
using namespace std;

class MyDoubleVector {
public:
	static const size_t Default_Capacity = 100;
	MyDoubleVector(size_t init_capacity = Default_Capacity);
	MyDoubleVector(const MyDoubleVector& v);
	~MyDoubleVector();
	MyDoubleVector& operator =(const MyDoubleVector& source);
	void operator +=(const MyDoubleVector& addend);
	double& operator[] (size_t n);
	MyDoubleVector operator +(const MyDoubleVector& v2);
	MyDoubleVector operator -(const MyDoubleVector& v2);
	double operator *(const MyDoubleVector& v2);
	MyDoubleVector& operator -();
	bool operator ==(const MyDoubleVector& v2);
	MyDoubleVector& operator ()(double k);
	void pop_back();
	void push_back(double x);
	size_t capacity() const;
	size_t size() const;
	void reserve(size_t n);
	bool empty() const;
	void clear();
	void print() const;

private:
	double* data;
	size_t volume;
	size_t used;
};
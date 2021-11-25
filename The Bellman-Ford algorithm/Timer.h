#pragma once
#include <iostream>
#include <chrono> // для функций из std::chrono

using namespace std;

class Timer
{
private:
	// Псевдонимы типов используются для удобного доступа к вложенным типам
	using clock_t = chrono::high_resolution_clock;
	using second_t = chrono::duration<double, ratio<1> >;

	chrono::time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now()) {}

	void reset();

	double elapsed() const;

};
/*  
 *  Homework #2
 *  Question 2: Binomial Tree Model
 *  
 *  Course: Futures and Options
 *  Writer_ID: 0416047
 *  Writer_Name: Chuan-Chun, Wang
 */
#ifndef _BINOMODEL_H_
#define _BINOMODEL_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <iomanip>
#include <typeinfo>

using namespace std;

class BinoModel
{
/* Constructors */
public:	
	BinoModel();// default constructor
	BinoModel(
		int OptionType,
		int TimeStep,
		float Stock0,
		float Volatility,
		float Exercise,
		float Maturity,
		float InterestRate
	);// constructor with given values


/* Member Functions */
public:
	float pricing();// pricing function
	void print_func() const;

/* Data Members */
public:

private:
	int option_type;// '0' means European options, '1' means American options
	int time_step;// how many time steps in one year.
	int step_num;// total munber of time steps during life of options.
	float stock_0;// stock price at time 0(in USD$)
	float volatility;// volatility equals to 'sigma' not to 'sigma*sigma'.
	float exercise;// strike price of the options(in USD$)
	float maturity;// maturity time of the options(in years)
	float interest_rate;// risk-free interest rate (in decimal point)
	float up_move_ratio;// stock_0 times u equals to stock price when up movement occurs.
	float down_nove_ratio;
};

#endif

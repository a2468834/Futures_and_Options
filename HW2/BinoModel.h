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
#include <algorithm>

using namespace std;

class BinoModel
{
/* Constructors */
public:	
	// default constructor
	BinoModel();

	// constructor with given values
	BinoModel( 
		int OptionType, 
		int TimeStep, 
		double Stock0, 
		double Volatility, 
		double Exercise, 
		double Maturity, 
		double InterestRate 
	);

/* Public Member Functions */
public:
	void print_func() const;

/* Public Data Members */
public:
	int OptionType;        // '0' means European options, '1' means American options.
	int TimeStep;          // How many time steps in one year.
	double Stock0;         // Stock price in the beginning ( at t_0 )(in USD$).
	double Volatility;     // Volatility equals to 'sigma' not to 'sigma*sigma'.
	double Exercise;       // Strike price of the options (in USD$).
	double Maturity;       // Maturity time of the options (in years).
	double InterestRate;   // Risk_free interest rate (in decimal point, NOT in percentage).

/* Private Member Funcyions */
private:
	void pricing_func();

/* Private Data Members */
private:
	int option_type;
	int time_step;
	int step_num;                  // Total number of time steps during life of options.
	double stock_0;
	double volatility;
	double exercise;
	double maturity;
	double interest_rate;
	double up_move_ratio;          // stock_0 * up_move_ratio = stock price when stock is going up
	double down_move_ratio;        // stock_0 * down_move_ratio = stock price when stock is going down
	double up_move_prob;           // probability of up movement
	double option_pricing_value;

};

#endif

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
#include <iostream>
#include <vector>
#include <iomanip>
#include <typeinfo>
#include <algorithm>

#define _USE_MATH_DEFINES
using namespace std;

class BinoModel
{
/* Constructors */
public:	
	// default constructor
	BinoModel();
	/* By default, 
	 * American put using binomial tree model
	 * S_0 = 50
	 * exercise price = 50
	 * maturity = 0.4167
	 * volatility = 0.4
	 * risk_free interest rate = 0.1
	 */

	// constructor with given values
	BinoModel( 
		int    OptionStyle, 
		int    OptionType, 
		double TimeStep, 
		double Stock0, 
		double Volatility, 
		double Exercise, 
		double Maturity, 
		double InterestRate, 
		int    PrintMode,
		int    PricingModel
	);

/* Public Data Members */
public:
	int    OptionStyle;    // '0' means European options, '1' means American options.
	int    OptionType;     // '0' means call options, '1' means put options.
	int    PrintMode;      // If you choose '0', you will get detailed info. for each time step.
	int    PricingModel;   // '0' means binomial tree model, '1' means Black-Scholes Model.
	double TimeStep;       // How many time steps in one year.
	double Stock0;         // Stock price in the beginning ( at t_0 )(in USD$).
	double Volatility;     // Volatility equals to 'sigma' not to 'sigma*sigma'.
	double Exercise;       // Strike price of the options (in USD$).
	double Maturity;       // Maturity time of the options (in years).
	double InterestRate;   // Risk_free interest rate (in decimal point, NOT in percentage).

/* Private Member Functions */
private:
	void BM_pricing_func();
	void BS_pricing_func(
		int    option_type, 
		double stock_0, 
		double volatility, 
		double exercise, 
		double maturity, 
		double interest_rate
	);
	void   print_func (int print_mode)                                          const;
	
	double call_price (double S, double K, double r, double v, double T)        const;
	double put_price  (double S, double K, double r, double v, double T)        const;
	double norm_pdf   (double x)                                                const;
	double norm_cdf   (double x)                                                const;
	double d_j        (int j, double S, double K, double r, double v, double T) const;

/* Private Data Members */
private:
	int    option_style;
	int    option_type;
	int    step_num;               // Total number of steps during life of options.
	int    print_mode;	
	int    pricing_model;
	double time_step;
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

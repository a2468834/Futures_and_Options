/*  
 *  Homework #2
 *  Question 2: Binomial Tree Model
 *  
 *  Course: Futures and Options
 *  Writer_ID: 0416047
 *  Writer_Name: Chuan-Chun, Wang
 */
#include "BinoModel.h"

using namespace std;

BinoModel::BinoModel()
{
	option_type     = 0;
	time_step       = 12;
	stock_0         = 50;
	volatility      = 0.4;
	exercise        = 52;
	maturity        = 2;
	interest_rate   = 0.005;
	step_num        = ceil((float) time_step*maturity);
	up_move_ratio   = exp(volatility*sqrt((float) 1/time_step));
	down_nove_ratio = exp(-volatility*sqrt((float) 1/time_step));
}

BinoModel::BinoModel(
	int OptionType, int TimeStep, float Stock0, float Volatility, float Exercise, 
	float Maturity, float InterestRate)
{
	// 'OptionType' type checking
	if( !(typeid(OptionType) == typeid(int)) ) 
	{
		cout<<"Wrong type: option type"<<endl;
		exit(EXIT_FAILURE);
	}
	if( (OptionType==0 || OptionType==1) != true )
	{
		cout<<"Wrong number: option type"<<endl;
		exit(EXIT_FAILURE);
	}

	// 'TimeStep' type checking
	if( !(typeid(TimeStep) == typeid(int)) )
	{
		cout<<"Wrong type: time step"<<endl;
		exit(EXIT_FAILURE);
	}
	if( TimeStep <= 0 )
	{
		cout<<"Wrong number: time step"<<endl;
		exit(EXIT_FAILURE);
	}

	// 'Stock0' type checking
	if( !(typeid(Stock0) == typeid(float)) )
	{
		cout<<"Wrong type: stock price at time 0"<<endl;
		exit(EXIT_FAILURE);
	}
	if( Stock0 <= 0 )
	{
		cout<<"Wrong number: stock price at time 0"<<endl;
		exit(EXIT_FAILURE);	
	}


	// 'Volatility' type checking
	if( !(typeid(Volatility) == typeid(float)) )
	{
		cout<<"Wrong type: volatility"<<endl;
		exit(EXIT_FAILURE);
	}
	if( Volatility < 0 )
	{
		cout<<"Wrong number: volatility"<<endl;
		exit(EXIT_FAILURE);
	}

	// 'Exercise' type checking
	if( !(typeid(Exercise) == typeid(float)) )
	{
		cout<<"Wrong type: exercise price of options"<<endl;
		exit(EXIT_FAILURE);
	}
	if( Exercise <= 0 )
	{
		cout<<"Wrong number: exercise price of options"<<endl;
		exit(EXIT_FAILURE);
	}

	// 'Maturity' type checking
	if( !(typeid(Maturity) == typeid(float)) )
	{
		cout<<"Wrong type: maturity of options"<<endl;
		exit(EXIT_FAILURE);
	}
	if(Maturity<=0)
	{
		cout<<"Wrong number: maturity of options"<<endl;
		exit(EXIT_FAILURE);
	}

	// 'InterestRate' type checking
	if( !(typeid(InterestRate) == typeid(float)) )
	{
		cout<<"Wrong type: risk-free interest rate"<<endl;
		exit(EXIT_FAILURE);
	}
	if(InterestRate<=0)
	{
		cout<<"Wrong number: risk-free interest rate"<<endl;
		exit(EXIT_FAILURE);
	}

	option_type     = OptionType;
	time_step       = TimeStep;
	stock_0         = Stock0;
	volatility      = Volatility;
	exercise        = Exercise;
	maturity        = Maturity;
	interest_rate   = InterestRate;
	step_num        = ceil((float) time_step*maturity);
	up_move_ratio   = exp( volatility * sqrt( (float) 1/time_step ) );
	down_nove_ratio = exp( -volatility*sqrt( (float) 1/time_step ) );
}

void BinoModel::print_func() const
{
	cout<<"option_type:"<<option_type<<endl;
	cout<<"time_step:"<<time_step<<endl;
	cout<<"stock_0:"<<stock_0<<endl;
	cout<<"volatility:"<<volatility<<endl;
	cout<<"exercise_price:"<<exercise<<endl;
	cout<<"maturity:"<<maturity<<endl;
	cout<<"interest_rate:"<<interest_rate<<endl;
}

float BinoModel::pricing()
{
	float present_time_step[time_step];
	float next_time_step[time_step];
}
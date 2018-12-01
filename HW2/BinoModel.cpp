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
	option_type=0;
	time_step=12;
	stock_0=50;
	volatility=0.3;
	exercise=52;
	maturity=2;
	interest_rate=0.005;
}

BinoModel::BinoModel(
	int OptionType, int TimeStep, float Stock0, float Volatility, float Exercise, 
	float Maturity, float InterestRate)
{
	// 'OptionType' type checking
	if( typeid(OptionType).name() != "int" ) 
	{
		cout<<"Wrong type: option type"<<endl;
		exit(EXIT_FAILURE);
	}
	else if( (OptionType==0 || OptionType==1) != true )
	{
		cout<<"Wrong number: option type"<<endl;
		exit(EXIT_FAILURE);
	}
	else option_type=OptionType;


	// 'TimeStep' type checking
	if( typeid(TimeStep).name() != "i")
	{
		cout<<"Wrong type: time step"<<endl;
		exit(EXIT_FAILURE);
	}
	else if( TimeStep <= 0 )
	{
		cout<<"Wrong number: time step"<<endl;
		exit(EXIT_FAILURE);
	}
	else time_step=TimeStep;


	// 'Stock0' type checking
	if( typeid(Stock0).name() != "f" )
	{
		cout<<"Wrong type: stock price at time 0"<<endl;
		exit(EXIT_FAILURE);
	}
	else if( Stock0 <= 0 )
	{
		cout<<"Wrong number: stock price at time 0"<<endl;
		exit(EXIT_FAILURE);	
	}
	else stock_0=Stock0;


	// 'Volatility' type checking
	if( typeid(Volatility).name() != "f" )
	{
		cout<<"Wrong type: volatility"<<endl;
		exit(EXIT_FAILURE);
	}
	else if( Volatility < 0 )
	{
		cout<<"Wrong number: volatility"<<endl;
		exit(EXIT_FAILURE);
	}
	else volatility=Volatility;


	// 'Exercise' type checking
	if( typeid(Exercise).name() != "f" )
	{
		cout<<"Wrong type: exercise price of options"<<endl;
		exit(EXIT_FAILURE);
	}
	else if( Exercise <= 0 )
	{
		cout<<"Wrong number: exercise price of options"<<endl;
		exit(EXIT_FAILURE);
	}
	else exercise=Exercise;


	// 'Maturity' type checking
	if( typeid(Maturity).name() != "f" )
	{
		cout<<"Wrong type: maturity of options"<<endl;
		exit(EXIT_FAILURE);
	}
	else if(Maturity<=0)
	{
		cout<<"Wrong number: maturity of options"<<endl;
		exit(EXIT_FAILURE);
	}
	else maturity=Maturity;

	// 'InterestRate' type checking
	if( typeid(InterestRate).name() != "f" )
	{
		cout<<"Wrong type: risk-free interest rate"<<endl;
		exit(EXIT_FAILURE);
	}
	else if(InterestRate<=0)
	{
		cout<<"Wrong number: risk-free interest rate"<<endl;
		exit(EXIT_FAILURE);
	}
	else interest_rate=InterestRate;
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
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
	interest_rate=5;
}

BinoModel::BinoModel(
	int OptionType, int TimeStep, float Stock0, float Volatility, float Exercise, 
	float Maturity, float InterestRate)
{
	option_type=OptionType;
	time_step=TimeStep;
	stock_0=Stock0;
	volatility=Volatility;
	exercise=Exercise;
	maturity=Maturity;
	interest_rate=InterestRate;
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
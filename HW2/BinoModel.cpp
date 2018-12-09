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
	// Some temporal variables
	double growth_factor;

	option_type     = 1;
	time_step       = 12;
	stock_0         = 50;
	volatility      = 0.4;
	exercise        = 50;
	maturity        = 0.4167;
	interest_rate   = 0.1;

	step_num        = floor((double) time_step*maturity);
	up_move_ratio   = exp(volatility*sqrt((double) 1/time_step));
	down_move_ratio = exp(-volatility*sqrt((double) 1/time_step));
	growth_factor   = exp(interest_rate*((double) 1/time_step));
	up_move_prob    = ( growth_factor - down_move_ratio ) / ( up_move_ratio - down_move_ratio );

	pricing_func();

	cout.precision(4);

	cout<<"Result:"<<endl;
	cout<<"(1) Basic Parameters"<<endl;
	if(option_type==0)cout<<"European Style"<<endl;
	else cout<<"American Style"<<endl;
	cout<<"u: "<<fixed<<up_move_ratio<<endl;
	cout<<"d: "<<fixed<<down_move_ratio<<endl;
	cout<<"p: "<<fixed<<up_move_prob<<endl;
	cout<<"time step \\Delta t = "<<fixed<<maturity/(double)step_num<<" years"<<endl;
	cout<<endl;

	cout<<"(2) Option Price"<<endl;
	cout<<setprecision(4)<<option_pricing_value<<endl;
}

BinoModel::BinoModel(
	int OptionType, 
	int TimeStep, 
	double Stock0, 
	double Volatility, 
	double Exercise, 
	double Maturity, 
	double InterestRate)
{
	// Some temporal variables
	double growth_factor;
	
	/* Input data semantic checking start */
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
	if( !(typeid(Stock0) == typeid(double)) )
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
	if( !(typeid(Volatility) == typeid(double)) )
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
	if( !(typeid(Exercise) == typeid(double)) )
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
	if( !(typeid(Maturity) == typeid(double)) )
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
	if( !(typeid(InterestRate) == typeid(double)) )
	{
		cout<<"Wrong type: risk-free interest rate"<<endl;
		exit(EXIT_FAILURE);
	}
	if(InterestRate<=0)
	{
		cout<<"Wrong number: risk-free interest rate"<<endl;
		exit(EXIT_FAILURE);
	}
	/* Input data semantic checking end */

	option_type     = OptionType;
	time_step       = TimeStep;
	stock_0         = Stock0;
	volatility      = Volatility;
	exercise        = Exercise;
	maturity        = Maturity;
	interest_rate   = InterestRate;

	step_num        = ceil((double) time_step*maturity);
	up_move_ratio   = exp( volatility * sqrt( (double) 1/time_step ) );
	down_move_ratio = exp( -volatility*sqrt( (double) 1/time_step ) );
	growth_factor   = exp(interest_rate*((double) 1/time_step));
	up_move_prob    = ( growth_factor - down_move_ratio ) / ( up_move_ratio - down_move_ratio );

	pricing_func();
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

void BinoModel::pricing_func()
{
	double parent[step_num+1];
	double child[step_num+1];
	double underly_asset[step_num+1][step_num+1];

	// Initialize arrays
	memset(parent, 0, sizeof(parent[0]) * (step_num+1) );
	memset(child, 0, sizeof(child[0]) * (step_num+1) );
	memset(underly_asset, 0, sizeof(underly_asset[0][0]) * (step_num+1) * (step_num+1) );

	// Calculate underlying asset prices through all time step
	for(int i=0; i<(step_num+1); i++)
		for(int j=0; j<(step_num+1); j++)
			underly_asset[i][j] = stock_0*pow(up_move_ratio, j)*pow(down_move_ratio, i-j);

	// Generate option price at time step N
	for(int i=0; i<(step_num+1); i++)
	{
		double exercise_value = exercise - underly_asset[step_num][i];
		child[i] = max(exercise_value, (double) 0);
	}

	// Backward induction procedure
	for(int i=1; i<(step_num+1); i++)
	{
		for(int j=0; j<step_num-i+1; j++)
		{
			double risk_neutral_future;
			double early_exercise;
			double later_exercise;

			risk_neutral_future = child[j] * (1-up_move_prob) + child[j+1] * up_move_prob;
			early_exercise      = ( option_type == 0 ) ? 0 : ( exercise - underly_asset[step_num-i][j] );
			later_exercise      = risk_neutral_future * exp( -interest_rate * maturity / (double) step_num );

			parent[j] = max(early_exercise, later_exercise);
		}
		
		// Prepare for next induction
		for(int j=0; j<step_num; j++)child[j] = (j < step_num-i+1) ? parent[j] : 0;
	}

	option_pricing_value = parent[0];
}
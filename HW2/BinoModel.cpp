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
	option_style         = 1;
	option_type          = 1;
	time_step            = 12.0;
	stock_0              = 50;
	volatility           = 0.4;
	exercise             = 50;
	maturity             = 0.4167;
	interest_rate        = 0.1;
	print_mode           = 0;
	pricing_model        = 0;
	option_pricing_value = 0;


	double growth_factor;// Temporal variables

	step_num        = ceil( time_step * maturity );
	up_move_ratio   = exp( volatility * sqrt( 1.0 / time_step ) );
	down_move_ratio = exp( (-volatility) * sqrt( 1.0 / time_step) );
	growth_factor   = exp( interest_rate * ( 1.0 / time_step ) );
	up_move_prob    = ( growth_factor - down_move_ratio ) / ( up_move_ratio - down_move_ratio );
	
	if(pricing_model == 0)BM_pricing_func();
	else BS_pricing_func(option_type, stock_0, volatility, exercise, maturity, interest_rate);

	print_func(print_mode);
}

BinoModel::BinoModel(
	int    OptionStyle, 
	int    OptionType, 
	double TimeStep, 
	double Stock0, 
	double Volatility, 
	double Exercise, 
	double Maturity, 
	double InterestRate, 
	int    PrintMode, 
	int    PricingModel)
{	
	/* Input data semantic checking start */
	// 'OptionStyle' type checking
	if( !(typeid(OptionStyle) == typeid(int)) ) 
	{
		cout<<"Wrong type: option style"<<endl;
		exit(EXIT_FAILURE);
	}
	if( (OptionStyle==0 || OptionStyle==1) != true )
	{
		cout<<"Wrong number: option style"<<endl;
		exit(EXIT_FAILURE);
	}

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
	if( !(typeid(TimeStep) == typeid(double)) )
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

	// 'PrintMode' type checking
	if( !(typeid(PrintMode) == typeid(int)) )
	{
		cout<<"Wrong type: mode of printing out"<<endl;
		exit(EXIT_FAILURE);
	}
	if( (PrintMode==0 || PrintMode==1) != true )
	{
		cout<<"Wrong number: You can only choose printing mode 0 or mode 1."<<endl;
		exit(EXIT_FAILURE);
	}

	// 'PricingModel' type checking
	if( !(typeid(PricingModel) == typeid(int)) )
	{
		cout<<"Wrong type: choosing princing model"<<endl;
		exit(EXIT_FAILURE);
	}
	if( (PricingModel==0 || PricingModel==1) != true )
	{
		cout<<"Wrong number: You can only choose binomial tree model(0) or Black-Scholes model(1)."<<endl;
		exit(EXIT_FAILURE);
	}
	if( OptionStyle==1 && PricingModel==1 )
	{
		cout<<"Wrong number: Black-Scholes model does not support American option pricing."<<endl;
		exit(EXIT_FAILURE);
	}
	/* Input data semantic checking end */

	double growth_factor;// Temporal variables

	option_style    = OptionStyle;
	option_type     = OptionType;
	time_step       = TimeStep;
	stock_0         = Stock0;
	volatility      = Volatility;
	exercise        = Exercise;
	maturity        = Maturity;
	interest_rate   = InterestRate;
	print_mode      = PrintMode;
	pricing_model   = PricingModel;

	step_num        = ceil( time_step * maturity );
	up_move_ratio   = exp( volatility * sqrt( 1.0 / time_step ) );
	down_move_ratio = exp( (-volatility) * sqrt( 1.0 / time_step ) );
	growth_factor   = exp( interest_rate * ( 1.0 / time_step ) );
	up_move_prob    = ( growth_factor - down_move_ratio ) / ( up_move_ratio - down_move_ratio );

	if(pricing_model == 0)BM_pricing_func();
	else BS_pricing_func(option_type, stock_0, volatility, exercise, maturity, interest_rate);

	print_func(print_mode);
}

void BinoModel::BM_pricing_func()
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
	if(option_type == 0)
	{
		// Call option pricing
		for(int i=0; i<(step_num+1); i++)
			child[i] = max( ( underly_asset[step_num][i] - exercise ), 0.0);
	}
	else
	{
		// Put option pricing
		for(int i=0; i<(step_num+1); i++)
			child[i] = max( ( exercise - underly_asset[step_num][i] ), 0.0);
	}

	// Backward induction procedure
	for(int i=1; i<(step_num+1); i++)
	{
		for(int j=0; j<step_num-i+1; j++)
		{
			double risk_neutral_future, early_exercise, later_exercise;

			risk_neutral_future = child[j] * (1-up_move_prob) + child[j+1] * up_move_prob;
			
			later_exercise      = risk_neutral_future * exp( -interest_rate * maturity / (double) step_num );
			
			if(option_type == 0)
				early_exercise  = ( option_style == 0 ) ? 0 : ( underly_asset[step_num-i][j] - exercise );
			else
				early_exercise  = ( option_style == 0 ) ? 0 : ( exercise - underly_asset[step_num-i][j] );

			parent[j] = max(early_exercise, later_exercise);
		}
		
		// Prepare for next induction
		for(int j=0; j<step_num; j++)child[j] = (j < step_num-i+1) ? parent[j] : 0;
	}
	
	option_pricing_value = parent[0];
}

void BinoModel::BS_pricing_func(
	int    option_type, 
	double stock_0, 
	double volatility, 
	double exercise, 
	double maturity, 
	double interest_rate)
{
	// Black-Scholes formula can only be used to price European options.
	if(option_type == 0)
		option_pricing_value = call_price(stock_0, exercise, interest_rate, volatility, maturity);
	else
		option_pricing_value = put_price(stock_0, exercise, interest_rate, volatility, maturity);
}

double BinoModel::call_price(double S, double K, double r, double v, double T) const
{
	return S * norm_cdf(d_j(1, S, K, r, v, T))- K * exp(-r*T) * norm_cdf(d_j(2, S, K, r, v, T));
}

double BinoModel::put_price(double S, double K, double r, double v, double T) const
{
	return (-S) * norm_cdf(-d_j(1, S, K, r, v, T)) + K * exp(-r*T) * norm_cdf(-d_j(2, S, K, r, v, T));
}

double BinoModel::norm_pdf(double x) const
{
	// Standard normal probability density function
	return ( 1.0 / ( pow(2*M_PI, 0.5) ) ) * ( exp(-0.5*x*x));
}

double BinoModel::norm_cdf(double x) const
{
	// The approximation of the CDF for standard normal distribution, recursion version.
	double k = 1.0/(1.0 + 0.2316419*x);
	double k_sum = k*(0.319381530 + k*(-0.356563782 + k*(1.781477937 + k*(-1.821255978 + 1.330274429*k))));

	if ( x >= 0.0 )return ( 1.0 - (1.0/(pow(2*M_PI,0.5)))*exp(-0.5*x*x) * k_sum );
	else return ( 1.0 - norm_cdf(-x) );
}

double BinoModel::d_j(int j, double S, double K, double r, double v, double T) const
{
	//Calculate 'd_1' and 'd_2' term in BS formula
	return ( log(S/K) + T * ( r + pow(-1, j-1) * 0.5 * v*v ) ) / ( v * pow(T, 0.5) );
}

void BinoModel::print_func(int print_mode) const
{
	cout.precision(4);

	if(print_mode == 0)
	{
		cout<<"Result:"<<endl;
		cout<<"(1) Basic Parameters"<<endl;
		if(option_style == 0)
		{
			if(option_type == 0)cout<<"    European Call"<<endl;
			else cout<<"    European Put"<<endl;
		}
		else
		{
			if(option_type == 0)cout<<"    American Call"<<endl;
			else cout<<"    American Put"<<endl;
		}
		cout<<"    u: "<<fixed<<up_move_ratio<<endl;
		cout<<"    d: "<<fixed<<down_move_ratio<<endl;
		cout<<"    p: "<<fixed<<up_move_prob<<endl;
		cout<<"    time step \\Delta t = "<<fixed<<maturity/(double)step_num<<" years"<<endl;
		if(pricing_model == 0)cout<<"    Use binomial tree model."<<endl;
		else cout<<"    Use Black-Scholes model."<<endl;

		cout<<"(2) Option Price"<<endl;
		cout<<"    "<<fixed<<option_pricing_value<<endl;
	}

	else cout<<fixed<<option_pricing_value<<endl;
}

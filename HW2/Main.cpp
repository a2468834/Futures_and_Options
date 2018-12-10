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

int main()
{
	vector<BinoModel> BM;

	cout<<"European Put"<<endl;
	cout<<endl;

	// Using binomial tree model
	cout<<"Binomial Model:"<<endl;
	for(double i=0.5; i<252.5; i=i+0.5)BM.emplace_back(0, 1, i, 50, 0.3, 52, 2, 0.05, 1, 0);
	cout<<endl;
	
	// Using Black-Scholes model
	cout<<"Black-Scholes Model:"<<endl;
	BM.emplace_back(0, 1, 252, 50, 0.3, 52, 2, 0.05, 1, 1);
	cout<<endl;

	return 0; 
}

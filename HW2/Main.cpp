/*  
 *  Homework #2
 *  Question 2: Binomial Tree Model
 *  
 *  Course: Futures and Options
 *  Writer_ID: 0416047
 *  Writer_Name: Chuan-Chun, Wang
 */
#include "Bino_Model.h"

using namespace std;

int main()
{
	Bino_Model B1;
	Bino_Model B2(0, 52, 10, 0.1, 20, 2, 0.001);

	cout<<"default constr"<<endl;
	B1.print_func();
	cout<<endl;

	cout<<"initial constr"<<endl;
	B2.print_func();
	cout<<endl;
	return 0;
}
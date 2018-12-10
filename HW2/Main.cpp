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
	BinoModel B(0, 1, 50, 0.3, 52, 2, 0.05);
	for(int i=2; i<252+1; i++)B.change_time_step(i);

	return 0; 
}
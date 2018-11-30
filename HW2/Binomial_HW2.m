
clear;

% Parameters
T=2;
S0=50;
K=52;
r=0.05;
q=0;
sigma=0.3;
ExerciseType='e'; %'a' for American option; otherwise European option

%Total number of time intervals %NT=252*T % if daily
NT=252*T 
dt=T/NT;
u=?
d=?
a=?
p=?

f=zeros(NT+1, NT+1);

% Option Prices at maturity
for j = 0:NT;
     % Put
     f(NT+1,j+1)=max(K-S0*(u^j)*(d^(NT-j)),0);
end;
    

% Backward Induction
for i = ?:?:?; 
    for j = ?:?;
         if (ExerciseType=='a')
		???
         else
		???	  
         end;
    end;
end;

Binomial_Value=f(1,1)
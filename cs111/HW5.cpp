#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
  ifstream fin("input.txt");
  if(fin.is_open())
    {
      int scores = 0;
      int numA = 0, numB = 0, numC = 0, numD=0, numF = 0;
      int grade;

      while(!fin.eof()) //https://stackoverflow.com/questions/44705236/turbo-c-whilefin-vs-whilefin-eof
	{
	  fin>>grade;
	  scores++;
	  if(grade >=90)
	    numA++;
	  else if(grade >= 80)
	    numB++;
	  else if(grade >= 70)
	    numC++;
	  else if(grade >= 60)
	    numD++;
	  else
	    numF++;
	}
      fin.close();
      cout<<"Total number of grades = "<<scores<<endl;
      cout<<"Number of A’s = "<<numA<<" which is "<<fixed<<setprecision(1)<<((double)(numA*100)/scores)<<"%"<<endl;
      cout<<"Number of B’s = "<<numB<<" which is "<<((double)(numB*100)/scores)<<"%"<<endl;
      cout<<"Number of C’s = "<<numC<<" which is "<<((double)(numC*100)/scores)<<"%"<<endl;
      cout<<"Number of D’s = "<<numD<<" which is "<<((double)(numD*100)/scores)<<"%"<<endl;
      cout<<"Number of F’s = "<<numF<<" which is "<<((double)(numF*100)/scores)<<"%"<<endl;
    }
  return 0;
}

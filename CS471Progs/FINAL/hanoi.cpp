#include<string>
#include<vector>
#include<iostream>
#include<stdlib.h>  /* to use exit */

using namespace std;

// FALL22 (Yoshii)
// CS 471 FINAL Tower of Hanoi using A*
//--------------------------------------------------
// YOUR NAME: Neil Schneringer
// Tested on Empress using g++  
//--------------------------------------------------

// State description class.
// Could have used struct.
class state
{
public:
  string items;  // made up of 1s, 2s, and 3s
  string camefrom; // the parent on the solution path
  int g;   // cost so far
  int h;   // estimated cost to the goal
  int f;   // g+h
};

// Major data structures:
vector<state> frontier;  // Frontier nodes - will pick one of these to expand
vector<state> beenThere; // already expanded nodes

// ========== Utility Functions ===================

// utility to add x to the beenthere
void addtoBeenThere(state x)
{  beenThere.push_back(x); }

// utility to add x to the frontier
void addtoFrontier(state x)
{  frontier.push_back(x); }

// to remove state x from the frontier when it has been expanded
void removefromFrontier(state x)
{  
  vector<state> newfrontier;
  for (int k = 0; k < frontier.size(); k++)
    if (frontier[k].items != x.items)
      newfrontier.push_back(frontier[k]);

  frontier = newfrontier;
}

//============= At the Very End ====================

// Trace and display the solution path from goal to initial.
// Note that camefrom of each state should be used. (called from generate)
void tracePath(state goal)
{
  //Move therough all states in beenThere
  for(int k = 0; k < beenThere.size(); k++)
    {
      //print
      cout << "Came from: " << endl;
      cout << beenThere[k].items << endl;
    }
}// end of tracePath  

//======= For Generating a new state to add to Frontier  =============

// Check to see if next's items is already in frontier and return true or false.
//   If it is already in frontier, 
//   and if the next's f is better, 
//   update the frontier node to next.  (called from generate)
bool inFrontier(state next)
{
  // add code here, possibly updating
  // the same frontier node with next if f is better.
  // Please cout a message in that case.
  // Return true or false.
  //Move through all states in frontier
  for(int k = 0; k < frontier.size(); k++)
    {
      //if the next state is equal to any in frontier, return true
      if (next.items == frontier[k].items)
       	{
	  cout << " Already in frontier" << endl;
	  return true;
	}
    }
  //if not, return false
  cout << " Not in frontier yet" << endl;
  return false;
}// end of inFrontier

bool checkBeenThere(state next)
{
  //move through all states in beenThere
  for(int k = 0; k < beenThere.size(); k++)
    {
      //If next state is in beenThere, return true
      if(beenThere[k].items == next.items)
	{
	  return true;
	}
    }
  //if not, return false
  return false;
}

// Try to add next to frontier but stop if LLLL (called from generateAll)
void generate(state next)
{ 
  cout << "Trying to add: " << next.items; 

  if (next.items  == "333")  // the goal is reached
    { cout << endl << ">>Reached goal: " << next.items << endl;
      tracePath(next);  // display the solution path
      exit(0); }//done

  // if been there before, do not add to frontier.
  // You may write a utility function check been-there and call it
  if(checkBeenThere(next)==true)
    {
      cout << " been there already" << endl;
      return;
    }
  // else compute h and then f for next
  //h is based on how many items are on right side
  int h = 3;// start point for h; g is already set
  if(next.items[1] == '3')
    h--;
  if(next.items[2] == '3')
    h--;
  if(next.items[3] == '3')
    h--;
  next.h = h;
  next.f = next.g + next.h;
    
  if (!inFrontier(next))
      addtoFrontier(next); // add next to Frontier 

}// end of generate   



// Generate all new states from current (called from main)
void generateAll(state current)
{
  state next;  // a generated one

  // each next will be modified from current for ease
  current.g = current.g + 1; // to update g to be used for next
  // storing the parent so that we can produce the solution path
  current.camefrom = current.items; 

  // check all possibilities as follows..
  
  next = current; // starting point of next
 if (current.items[2] == '1')
    { next.items[2]='3'; generate(next);};
  
  if (current.items[2] == '1')
    { next.items[2]='2'; generate(next);};
  
  if (current.items[2] == '2')
    { next.items[2]='3'; generate(next);};
  
  if (current.items[2] == '3')
    { next.items[2]='2'; generate(next);};

  if (current.items[2] == '2')
    { next.items[2]='1'; generate(next);};

  if (current.items[2] == '3')
    { next.items[2]='1'; generate(next);};

  if (current.items[1] == '1' && current.items[2] == '2')
    { next.items[1]='3'; generate(next);};

  if (current.items[1] == '1' && current.items[2] == '3')
    { next.items[1]='2'; generate(next);};

  if (current.items[1] == '2' && current.items[2] == '1')
    { next.items[1]='3'; generate(next);};

   if (current.items[1] == '2' && current.items[2] == '3')
    { next.items[1]='1'; generate(next);};

  if (current.items[1] == '3' && current.items[2] == '2')
    { next.items[1]='1'; generate(next);};

  if (current.items[1] == '3' && current.items[2] == '2')
    { next.items[1]='1'; generate(next);};

  if (current.items[0] == '1' && current.items[2] == '2' && current.items[1] == '2')
    { next.items[0]= '3'; generate(next);};

  if (current.items[0] == '1' && current.items[2] == '3' && current.items[1] == '3')
    { next.items[0]= '2'; generate(next);};

  if (current.items[0] == '2' && current.items[2] == '1' && current.items[1] == '1')
    { next.items[0]= '3'; generate(next);};

  if (current.items[0] == '2' && current.items[2] == '3' && current.items[1] == '3')
    { next.items[0]= '1'; generate(next);};

}// end of generateAll


// Find the best f state out of the frontier and return it (called from main)
state bestofFrontier()
{
  //finding lowest f in frontiers
  int temp=99999; //absurdly high value to be replaced
  int bestfront; 
  //Move through all states in frontier
  for(int k  = 0; k < frontier.size(); k++)
    {
      //If state has lower f than temp, swap it out. Make a pointer for best frontier
      if (frontier[k].f<temp)
	{
	  temp=frontier[k].f;
	  bestfront=k;
	}	
    }
  //Set best frontier
  cout << "Best is: " << frontier[bestfront].items << endl;
  return frontier[bestfront]; 
}//end of bestofFrontier

// Display the states in the frontier  (called from main)
void displayFrontier()
{
  for (int k = 0; k < frontier.size(); k++)
    { cout << frontier[k].items << " ";  
      cout << "g = " <<frontier[k].g << " ";
      cout << "h = " <<frontier[k].h << " ";
      cout << "f = " <<frontier[k].f << endl; 
    }
}// end of displayFrontier

//================= Main ===========================

int main() 
{

  state  current = {"111","", 0, 3, 3};  // initial
  addtoFrontier(current);

  char ans;
  while ( ans != 'n')
    { 
      removefromFrontier(current);      
      addtoBeenThere(current);

      cout << ">>>Expand:" << current.items << endl; 
      generateAll(current);  // new states are added to frontier

      cout << "Frontier is:" << endl;
      displayFrontier();

      current = bestofFrontier(); // pick the best state out of frontier
      cin >> ans;

    }// end while

}//end of main

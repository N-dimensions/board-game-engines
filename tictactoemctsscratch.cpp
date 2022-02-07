#include<iostream>
#include<vector>
#include<math.h>
#include<stdlib.h>
#include<time.h>
using namespace std;
int win(unsigned int arr[], unsigned int empty);
int reinforce(unsigned int *, const vector<int>&, unsigned int , unsigned int *, float *, unsigned int *);
int findbest(unsigned int , unsigned int, const vector<int>&, unsigned int *, float *, unsigned int *);
bool alreadydone(unsigned int, unsigned int, const vector<int>&, unsigned int);
int win(unsigned int arr[], unsigned int empty)
{
	int a=3;
	for(int i=0; i<=2; i++)
	{
	

		if(arr[i]*arr[i+3]*arr[i+6]==1 || arr[3*i]*arr[3*i+1]*arr[3*i+2]==1)
		{
			a=0;
			return a;
		}
		if(arr[i]*arr[i+3]*arr[i+6]==8 || arr[3*i]*arr[3*i+1]*arr[3*i+2]==8)
		{
			a=1;
			return a;
		}
		if(arr[0]*arr[4]*arr[8]==1 || arr[2]*arr[4]*arr[6]==1)
		{
			a=0;
			return a;
		}
		if(arr[0]*arr[4]*arr[8]==8 || arr[2]*arr[4]*arr[6]==8)
		{
			a=1;
			return a;
		}
	}
	if(empty==0)
	{
		a=2;
		return a;
	}	
	return a;
}
int reinforce(unsigned int *k, const vector<int>& choices, unsigned int movepl, unsigned int *holon, float *boardstoreprob[], unsigned int *boardhistory)
{
	vector<int> choices1;																			//Vector whose random element shall be picked to make a move
	//float boardstoreprob[19682][2];															//will call by reference		//boardstoreprob[boardpos,0] stores numerator of probility of win, that[___,1] stores denomerator
	unsigned int boardpos, k1[9], i, empty, p, count, boardbest, best, given, who, whonx; 					//k describes board posn in a human mobile-phone like format, boardpos stores terenary in decimal system 
	boardpos=0;
	//for(p=0;p<=movepl;p++)
	//{
	//	boardstoreprob[boardhistory[p]][0]=0;
	//	boardstoreprob[boardhistory[p]][1]=0;
	//}
	srand(time(0));
	//for(i=0;i<=19681;i++)
	//{
	//	boardstoreprob[i][0]=0;																		//setting everything to 0
	//	boardstoreprob[i][1]=0;
	//}
	for(i=0;i<=8;i++)
	{
		k1[i]=k[i];
		boardpos=boardpos+pow(3,i)*k[i];																				//storing in choices
	}
	given=boardpos;
	for(i=0;i< choices.size();i++)
	{
		choices1.push_back(choices[i]);
	}
	empty=9-movepl;
	if(win(k1, empty)==0)
	{
		for(p=0;p<movepl-1;p++)
		{
			boardstoreprob[boardhistory[p]][1]=boardstoreprob[boardhistory[p]][1]+60;
		}
		boardstoreprob[boardhistory[movepl]][0]=0;
		boardstoreprob[boardhistory[movepl]][1]=1000000000000;
		boardstoreprob[boardhistory[movepl-1]][0]=0;
		boardstoreprob[boardhistory[movepl-1]][1]=1000000000000;
		return 0;
	}
	if(win(k1, empty)==1)
	{
		for(p=0;p<movepl-1;p++)
		{
			boardstoreprob[boardhistory[p]][0]=boardstoreprob[boardhistory[p]][0]+60;
			boardstoreprob[boardhistory[p]][1]=boardstoreprob[boardhistory[p]][1]+60;
		}
		boardstoreprob[boardhistory[movepl]][0]=1000000000000;
		boardstoreprob[boardhistory[movepl]][1]=1000000000000;
		boardstoreprob[boardhistory[movepl-1]][0]=1000000000000;
		boardstoreprob[boardhistory[movepl-1]][1]=1000000000000;
		return 0;
	}
	if(win(k1, empty)==2)
	{
		for(p=0;p<movepl-1;p++)
		{
			boardstoreprob[boardhistory[p]][0]=boardstoreprob[boardhistory[p]][0]+30;
			boardstoreprob[boardhistory[p]][1]=boardstoreprob[boardhistory[p]][1]+60;
		}
		boardstoreprob[boardhistory[movepl]][0]=1000000000000;
		boardstoreprob[boardhistory[movepl]][1]=2000000000000;
		boardstoreprob[boardhistory[movepl-1]][0]=1000000000000;
		boardstoreprob[boardhistory[movepl-1]][1]=2000000000000;
		return 0;
	}
	for(unsigned int i=0;i<=8-movepl;i++)																	//movepl+1th move
	{	
		choices1.clear();
		for(p=0;p<=8;p++)
		{
			k1[p]=k[p];															
		}
		for(p=0;p<choices.size();p++)
		{
			choices1.push_back(choices[p]);
		}
		empty=8-movepl;
		if(movepl%2==0)
		{
			who=1;
			whonx=2;
		}
		else
		{
			who=2;
			whonx=1;
		}
		boardpos=given;
		k1[choices1[i]]=who;																			//gonna make a move for 'X' or 'O' we don't know
		boardpos=boardpos+pow(3,choices1[i])*k1[choices1[i]];	
		holon[movepl+0]=boardpos;																			//storing move
		choices1.erase(choices1.begin()+i);
		if(win(k1, empty)==0)
		{
			boardstoreprob[holon[movepl]][0]=0;
			boardstoreprob[holon[movepl]][1]=1000000000000;
			for(p=0;p<movepl;p++)
			{
				boardstoreprob[boardhistory[p]][1]=boardstoreprob[boardhistory[p]][1]+60;
			}
			boardstoreprob[boardhistory[movepl]][0]=0;
			boardstoreprob[boardhistory[movepl]][1]=1000000000000;
			return 0;
		}
		if(win(k1, empty)==1)
		{
			boardstoreprob[holon[movepl]][0]=1000000000000;
			boardstoreprob[holon[movepl]][1]=1000000000000;
			for(p=0;p<movepl;p++)
			{
				boardstoreprob[boardhistory[p]][0]=boardstoreprob[boardhistory[p]][0]+60;
				boardstoreprob[boardhistory[p]][1]=boardstoreprob[boardhistory[p]][1]+60;
			}
			boardstoreprob[boardhistory[movepl]][0]=1000000000000;
			boardstoreprob[boardhistory[movepl]][1]=1000000000000;
			return 0;
		}
		if(win(k1, empty)==2)
		{
			boardstoreprob[holon[movepl]][0]=1000000000000;
			boardstoreprob[holon[movepl]][1]=2000000000000;
			for(p=0;p<movepl;p++)
			{
				boardstoreprob[boardhistory[p]][0]=boardstoreprob[boardhistory[p]][0]+30;
				boardstoreprob[boardhistory[p]][1]=boardstoreprob[boardhistory[p]][1]+60;
			}
			boardstoreprob[boardhistory[movepl]][0]=1000000000000;
			boardstoreprob[boardhistory[movepl]][1]=2000000000000;
			continue;
		}																									//erasing choice of moving on the same block
		for(unsigned int l=0;l<=7-movepl;l++)																//making loads of 'O' moves for each 'X' move
		{	
			choices1.clear();
			for(p=0;p<=8;p++)
			{
				k1[p]=k[p];								
			}
			for(p=0;p< choices.size();p++)
			{
				choices1.push_back(choices[p]);
			}
			k1[choices1[i]]=who;																		//Reinstating
			//boardpos=pow(3,choices1[i])*k1[choices1[i]];		
			choices1.erase(choices1.begin()+i);
			//cout<<choices1.size()<<endl;
			boardpos=holon[movepl+0];					 
			k1[choices1[l]]=whonx;																		//storing 'O'
			boardpos=boardpos+pow(3,choices1[l])*k1[choices1[l]];										//updating board
			holon[movepl+1]=boardpos;																		//holds on the board posn RIGHT NOW!
			choices1.erase(choices1.begin()+l);														//erasing choice of moving on the same block
			count=0;																				//0th game with this setup
			while(count!=30)																		//play 30 pseudo Random games
			{
				empty = 7-movepl;																			//7 empty squares rn
				while(win(k1, empty)!=1 && win(k1, empty)!=0 && empty!=0)											//keep going till someone wins or no legal moves
				{
					p=rand()%empty;																	//a random number between 0 to number of empty squares-1 (extremes inclusive)
					k1[choices1[p]]=who;																//making random move in readbale							
					choices1.erase(choices1.begin()+p);												//erasing choice			
					empty = empty - 1;																//one square less empty
					if(win(k1, empty)==0 || empty==0)												//if someone wins or it's no legal moves quit RN
					{
						break;
					}
					p=rand()%empty;																	//Next move for 'O'
					k1[choices1[p]]=whonx;																//store it
					choices1.erase(choices1.begin()+p);												//erase choice
					empty = empty - 1;																//one square less empty
				}
				choices1.clear();																	//Reinstating choices for next game
				for(p=0;p<=8;p++)
				{
					k1[p]=k[p];															
				}
				for(p=0;p< choices.size();p++)
				{
					choices1.push_back(choices[p]);
				}
				k1[choices1[i]]=who;																	//preping for next game resetting											
				choices1.erase(choices1.begin()+i);
				k1[choices1[l]]=whonx;
				boardpos=holon[movepl+1];															//setting last position
				choices1.erase(choices1.begin()+l);													
				count = count+1;																	//1 more game played
				if(win(k1, empty)==1)																//if ai (ai is O from their percpective) wins num+2 of this 1-X, 1-O pos and parent 1-X position	
				{
					boardstoreprob[holon[movepl]][0]=boardstoreprob[holon[movepl]][0]+2;
					boardstoreprob[holon[movepl+1]][0]=boardstoreprob[holon[movepl+1]][0]+2;
					for(p=0;p<=movepl;p++)
					{
						boardstoreprob[boardhistory[p]][0]=boardstoreprob[boardhistory[p]][0]+2;
					}
				}
				else
				{
					if(win(k1, empty)==2)															//if ai draws num+1, if loses num+0
					{
						boardstoreprob[holon[movepl]][0]=boardstoreprob[holon[movepl]][0]+1;
						boardstoreprob[holon[movepl+1]][0]=boardstoreprob[holon[movepl+1]][0]+1;
						for(p=0;p<=movepl;p++)
						{
							boardstoreprob[boardhistory[p]][0]=boardstoreprob[boardhistory[p]][0]+1;
						}
					}
				}
				boardstoreprob[holon[movepl]][1]=boardstoreprob[holon[movepl]][1]+2;
				boardstoreprob[holon[movepl+1]][1]=boardstoreprob[holon[movepl+1]][1]+2;
				for(p=0;p<=movepl;p++)
				{
					boardstoreprob[boardhistory[p]][1]=boardstoreprob[boardhistory[p]][1]+2;
				}					
			}		
		}
		//choices1.clear();
		//for(p=0;p<=8;p++)
		//{
			//k1[p]=k[p];															
		//}
		//for(p=0;p<choices.size();p++)
		//{
			//choices1.push_back(choices[p]);
		//}
	}
	return 0;
}
int findbest(unsigned int movepl, unsigned int boardpos, const vector<int>& choices, unsigned int *k, float *boardstoreprob[], unsigned int *boardhistory)
{
	unsigned int i, boardbest, boardposnew, besttemp, count;
	besttemp=0;
	count=0;
	cout<<"Thinking of best for:- "<<movepl<<endl; 
	cout<<"Position given: "<<boardpos<<endl;
	boardbest=boardpos+pow(3,choices[besttemp])*(2-movepl%2);
	boardposnew=boardpos;
	cout<<"Board best: "<<boardbest<<endl;
	for(i=0;i<choices.size();i++)
	{
		cout<<"Choices size: "<<choices.size()<<endl;
		k[choices[i]]=2-movepl%2;
		//cout<<choices[i]<<endl;
		//cout<<choices[i];
		boardposnew=boardpos+pow(3,choices[i])*k[choices[i]];
		cout<<"Move in mind and chances : "<<choices[i]<<"-->"<<boardstoreprob[boardposnew][0]<<"/"<<boardstoreprob[boardposnew][1]<<"-->"<<boardstoreprob[boardposnew][0]/boardstoreprob[boardposnew][1]<<endl;
		if(boardstoreprob[boardposnew][0]==0)
		{
			count=count+1;
		}
		if(movepl%2==1)
		{
			if(boardstoreprob[boardposnew][0]/boardstoreprob[boardposnew][1]<=boardstoreprob[boardbest][0]/boardstoreprob[boardbest][1])
			{
				boardbest=boardposnew;
				besttemp=i;
				//cout<<besttemp<<endl;
				//cout<<boardbest<<endl;
				//cout<<"Jibberish : "<<boardstoreprob[boardbest][0]<<"/"<<boardstoreprob[boardbest][1]<<endl;
			}
		}
		else
		{
			//cout<<"Movepl is even "<<boardstoreprob[boardbest][0]/boardstoreprob[boardbest][1]<<endl;
			if(boardstoreprob[boardposnew][0]/boardstoreprob[boardposnew][1]>=boardstoreprob[boardbest][0]/boardstoreprob[boardbest][1])
			{
				//cout<<"Bruh"<<endl;
				boardbest=boardposnew;
				besttemp=i;
			}
		}
		k[choices[i]]=0;
	}
	if(count==choices.size())
	{
		boardstoreprob[boardhistory[movepl-1]][0]=0;
		boardstoreprob[boardhistory[movepl-1]][1]=1000000000000;
		boardstoreprob[boardhistory[movepl-2]][0]=0;
		boardstoreprob[boardhistory[movepl-2]][1]=1000000000000;
		boardstoreprob[boardhistory[movepl-3]][0]=0;
		boardstoreprob[boardhistory[movepl-3]][1]=1000000000000;
	}
	cout<<"Best temp: "<<besttemp<<endl;
	cout<<"Best move as of now: "<<choices[besttemp]<<endl;
	cout<<"that's it for now=========================================================="<<endl<<endl<<endl<<endl;
	return besttemp;
}
bool alreadydone(unsigned int boardpos, unsigned int move, const vector<int>& boardposopened, unsigned int movepl)
{
	int i;
	boardpos = boardpos + pow(3, move)*(2-movepl%2); 
	for(i=0;i<boardposopened.size();i++)
	{
		if(boardpos==boardposopened[i])
		{
			return true;
		}
	}
	return false;
}
int main()
{
	vector<int> choices, boardposopened;																			//Vector whose random element shall be picked to make a move
	float boardstoreprob[19682][2];																	//boardstoreprob[boardpos,0] stores numerator of probility of win, that[___,1] stores denomerator
	unsigned int boardpos, k[9], i, empty, p, count, holon[9], boardbest, movepl, holds, boardhistory[9], besttemp; 					//k describes board posn in a human mobile-phone like format, boardpos stores terenary in decimal system 
	boardbest=0;
	bool alreadydonecopment;
	unsigned int *p1, *p2, *p4;
	float *p3[19682];
	srand(time(0));
	for(i=0;i<=19681;i++)
	{
		boardstoreprob[i][0]=0;																		//setting everything to 0
		boardstoreprob[i][1]=0;
		p3[i]=&boardstoreprob[i][0];
	}
	for(i=0;i<=8;i++)
	{
		k[i]=0;
		choices.push_back(i);																		//storing in choices
	}
	boardpos=0;
	movepl = 0;
	p1 = &k[0];
	p2 = &holon[0];
	p4 = &boardhistory[0];
	boardhistory[0]=0;
	reinforce(p1, choices, movepl, p2, p3, p4);
	while(movepl<9)
	{
		movepl=1;
		besttemp=findbest(movepl, boardpos, choices, p1, p3, p4);
		//cout<<choices[besttemp]<<endl;		//choice besttempth material
		alreadydonecopment=alreadydone(boardpos, choices[besttemp], boardposopened, movepl);
		//cout<<alreadydonecopment<<endl;
		while(alreadydonecopment)
		{
			//cout<<movepl<<endl;
			k[choices[besttemp]]=2-movepl%2;
			boardpos=boardpos+pow(3,choices[besttemp])*k[choices[besttemp]];
			boardhistory[movepl]=boardpos;
			choices.erase(choices.begin()+besttemp);
			movepl=movepl+1;
			//cout<<movepl;
			besttemp=findbest(movepl, boardpos, choices, p1, p3, p4);	
			//cout<<choices[besttemp]<<endl;											//choice besttempth material
			alreadydonecopment=alreadydone(boardpos, choices[besttemp], boardposopened, movepl);
		}
		k[choices[besttemp]]=2-movepl%2;
		boardpos=boardpos+pow(3,choices[besttemp])*k[choices[besttemp]];
		boardhistory[movepl]=boardpos;
		//cout<<choices.size()<<endl;
		boardposopened.push_back(boardpos);
		choices.erase(choices.begin()+besttemp);
		reinforce(p1, choices, movepl, p2, p3, p4);
		choices.clear();
		for(i=0;i<=8;i++)
		{
			k[i]=0;
			choices.push_back(i);																		//storing in choices
		}
		boardpos=0;
		//cout<<movepl<<endl;
	}
	cout<<"boo hooo"<<movepl;
//	for(i=0;i<=8;i++)
//	{
//		cout<<"hey bro: "<<boardhistory[i]<<endl;
//	}
	
}

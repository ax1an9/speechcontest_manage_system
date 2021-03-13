#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<algorithm>
#include<deque>
#include<numeric>
#include<functional>
#include<fstream>
using namespace std;
#include"Speaker.h"
class speechcontest_Management
{
public:
	//Constructor
	speechcontest_Management();
	//Destructor
	~speechcontest_Management();
	//Speech Draw
	void SpeechDraw();
	//Create speakers
	void Create_Speaker();
	//initiate System
	void Init_System();
	//Function of interaction
	void Interaction();
	//Function to show manu
	void Show_Menu();
	//show score
	void Show_Score();
	//save record
	void Save_Record();
	//load record
	void Load_Record();
	//contest
	void Contest();
	//show record
	void Show_Record();
	//clear
	void Clear_System();
	//speakers'Id in First round
	vector<int>v1;
	//speakers'Id in Second round
	vector<int>v2;
	//speakers'Id (1st,2nd,3rd)
	vector<int>vV;
	//speakers'Id-->Speaker 
	map<int, Speaker>m_Speaker;
	int m_Index;
	bool m_isEmpty;
	map<int,vector<string>>m_Record;
};
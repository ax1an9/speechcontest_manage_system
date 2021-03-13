#include "speechcontest_management.h"
#include<algorithm>
using namespace std;
speechcontest_Management::speechcontest_Management()
{
	this->Init_System();
}

speechcontest_Management::~speechcontest_Management()
{
}

void speechcontest_Management::SpeechDraw()
{
	cout << "Round [" << this->m_Index << "] is being drawn!" << endl;
	cout << "----------------------------------------" << endl;
	cout << "The order after draw:" << endl;
	if (this->m_Index == 1)
	{
		random_shuffle(this->v1.begin(), this->v1.end());
		for_each(this->v1.begin(), this->v1.end(), [](int i) {cout << i << " "; });
		cout << endl;
	}
	else
	{
		random_shuffle(this->v2.begin(), this->v2.end());
		for_each(this->v2.begin(), this->v2.end(), [](int i) {cout << i << " "; });
		cout << endl;
	}
	cout<< "----------------------------------------" << endl;
	system("pause");
	cout << endl;
}

void speechcontest_Management::Create_Speaker()
{
	for (int i = 0; i < 12; i++)
	{
		string nameSeed = "ABCDEFGHIJKL";
		string sp = "Speaker ";
		sp+=nameSeed[i];
		this->v1.push_back(10001 + i);
		Speaker temp;
		temp.m_Name = sp;
		for(int j=0;j<2;j++)
		{
			temp.m_Score[j] = 0.0;
		}
		this->m_Speaker.emplace(make_pair(i+10001,temp));
	}
	//test
	/*for_each(this->m_Speaker.begin(), this->m_Speaker.end(), 
		[](pair<int, Speaker>p) 
		{cout << "Name:" << p.second.m_Name << " Score:" << p.second.m_Score[0] << endl; });*/
}

void speechcontest_Management::Init_System()
{
	this->m_Index = 1;
	this->v1.clear();
	this->v2.clear();
	this->vV.clear();
	this->m_Speaker.clear();
	this->m_Record.clear();
	this->Load_Record();
}




void speechcontest_Management::Interaction()
{
	cout << "Please enter the instruction in number:" << endl;
	char c;
	cin >> c;
	switch (c)
	
	{
	case '1':
		if(this->m_Index==1)this->Create_Speaker();
		this->SpeechDraw();
		this->Contest();
		if (this->m_Index==2)this->Save_Record();
		this->Show_Score();
		if(this->m_Index == 3)this->Init_System();
		break;
	case '2':
		/*this->Load_Record();*/
		this->Show_Record();
		break;
	case '3':
		Clear_System();
		break;
	case '0':
		cout << "See you next time!" << endl;
		system("pause");
		exit(0);
		break;	
	default:
		cout << "$ You had entered the wrong instruction, please try again! $" << endl;
		system("pause");
		system("cls");
		break;
	}
}

void speechcontest_Management::Show_Menu()
{
	cout << "**************************************************" << endl
		<< "*********** 1.Start speech contest! **************" << endl
		<< "*********** 2.Show the former record! ************" << endl
		<< "*********** 3.Delete all former record! **********" << endl
		<< "*********** 0.Exit the system ! ******************" << endl
		<< "**************************************************" << endl;

}

void speechcontest_Management::Show_Score()
{
	cout << "the winner of " << this->m_Index << " round:" << endl;
	vector<int>v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vV;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "--" << *it << " name:" << this->m_Speaker[*it].m_Name << " score:" << this->m_Speaker[*it].m_Score[this->m_Index-1] << endl;
	}
	cout << endl;
	this->m_Index++;
	if (m_Index == 3) { this->Init_System(); }
	system("pause");
	system("cls");

}

void speechcontest_Management::Save_Record()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//app
	for (vector<int>::iterator it = vV.begin(); it != vV.end(); it++)
	{
		ofs << *it << ","
			<< m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "record saved!" << endl;
	this->m_isEmpty = false;
}

void speechcontest_Management::Load_Record()
{
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open())
	{
		this->m_isEmpty = true;
		cout << "File does not exist!" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "Empty File!" << endl;
		this->m_isEmpty = true;
		ifs.close();
		return;
	}
	else
	{
		this->m_isEmpty = false;
		ifs.putback(ch);
		string data;
		int index = 1;
		vector<string>record;
		while (ifs >> data)
		{
			int pos = -1;
			int start = 0;
			while (1)
			{
				string temp;
				pos = data.find(",", start);
				if (pos == -1)
				{
					break;
				}
				temp = data.substr(start, pos - start);
				
				start = pos+1;
				record.push_back(temp);
			}
			this->m_Record.emplace(make_pair(index, record));
			index++;
		}
		
	}
	ifs.close();
	/*cout << "---------------------------------------------------------" << endl;
	for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
	{

		cout << "--" << it->first << "--" << it->second[0] << it->second[1] << endl;
	}
	cout << "---------------------------------------------------------" << endl;*/
}

void speechcontest_Management::Contest()
{
	cout << "Round [" << this->m_Index << "] start!" << endl;
	
	multimap<double, int, greater<double>>groupscore;
	
	int num = 0;

	vector<int>v_Src;
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;//600-1000
			d.push_back(score);
			/*cout << score << endl;*/
		}
		sort(d.begin(), d.end(), greater<double>());//sort
		d.pop_front();
		d.pop_back();
		
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;
		num++;
		/*cout << *it << "--" << this->m_Speaker[*it].m_Name << "--" << this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;*/
		//for test
		groupscore.emplace(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "rank of group " << num / 6 << ":" << endl;
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupscore.begin(); it != groupscore.end(); it++,count++)
			{
				if (count == 3)cout << "-------------------------------------" << endl;
				cout << it->second << " name:" << this->m_Speaker[it->second].m_Name << " score:" << this->m_Speaker[it->second].m_Score[this->m_Index-1] << endl;
			}
			count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupscore.begin(); it != groupscore.end() && count < 3; it++, count++)
			{
				if (this->m_Index == 1)
				{
					this->v2.push_back(it->second);
				}
				else
				{
					this->vV.push_back(it->second);
				}
			}
			groupscore.clear();
		}
	}
	cout << "Round [" << this->m_Index << "] end!" << endl;
	/*this->m_Index++;*/
	system("pause");
}

void speechcontest_Management::Show_Record()
{
	if (this->m_isEmpty)
	{
		cout << "File is empty!" << endl;
	}
	for (int i = 1; i < this->m_Record.size()+1; i++)
	{
		cout << "---" << i << "---" << endl;
		cout << "1st:" << m_Record[i][0] << " score:" << m_Record[i][1] << endl;
		cout << "2nd:" << m_Record[i][2] << " score:" << m_Record[i][3] << endl;
		cout << "3rd:" << m_Record[i][4] << " score:" << m_Record[i][5] << endl;
		cout << endl;
	}
	system("pause");
	system("cls");
}

void speechcontest_Management::Clear_System()
{
	cout << "DO YOU WANT TO CLEAR THE RECORD?" << endl;
	cout << "1.YES      2.NO" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		this->Init_System();
		cout << "Successfully Clear!" << endl;
	}
	else
	{ }
	system("pause");
	system("cls");

}

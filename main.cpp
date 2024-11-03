#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<math.h>
#include<sstream>
#include<map>
#include<algorithm>
#include<math.h>
#include<time.h>

using namespace std;

struct macrotopin
{
	string macro;
	vector<string> macropin;
};

//*�n��macro to net
//.defstandardcell
struct netmacrostruct
{
	vector<string>macronet;
	int netmacronum = 0;
	string netname;
};

struct macronetstruct
{
	vector<string>netmacro;
	int macrotonetnum = 0;
	string netname;
};

struct infostandardcell
{
	string standardcellname;//components
	int status = 0;//status,0 1�N��
	string direction;//��V
	int x = 0;//x�y��
	int y = 0;//y�y��
	//width
	//height
};
//.defpin
struct infopin
{
	string pinname;
	int status = 0;//*0 1 �N��
	int x = 0;
	int y = 0;
	string direction;
};
//.node
struct infostandardpindimension
{
	int height = 0;
	int width = 0;
};
//.mlist
struct infomlist
{
	string compname;
	string macroname;
	int status = 0;//int 0 , 1
	string direction;
	int dieareax = 0;
	int dieareay = 0;
	int x = 0;
	int y = 0;
};//�w���map;

int main()
{
	netmacrostruct nett;
	macronetstruct macroo;
	map<string, netmacrostruct> nettomacro;
	map<vector<string>, macronetstruct> macrotonet;
	ifstream netfile;//Ū��net��

	netfile.open("C:/Users/USER/Desktop/test/case01.nets");

	string netstr;
	int netspace = 0;
	int i = 0;

	while (getline(netfile, netstr))
	{

		if (netstr.size() == 0)
		{

			netspace++;
			continue;

		}

		else if (netstr.size() == 0 && netspace == 3)
		{

			break;

		}

		else if (netstr.size() != 0 && netspace == 2)
		{

			__int64 space1 = netstr.find("    ");
			string nospace = netstr.substr(space1 + 4, netstr.length() - space1 - 1);
			int space2 = nospace.find("    ");
			string nospace2 = nospace.substr(0, space2);
			__int64 space3 = nospace.find("    ");
			string nospace3 = nospace.substr(space3 + 4, nospace.length() - space3 - 4);//netname
			nett.netname = nospace3;
			macroo.netname = nospace3;
			
			int compnum = stoi(nospace2);
			nett.netmacronum = compnum;
			macroo.macrotonetnum = compnum;

			while (getline(netfile, netstr))
			{
				
				int ch = 0;
				int ch1 = 0;
				int countspace = 0;
				int countalpha = 0;
				
				while (!isalpha(netstr[ch]))
				{

					countspace++;
					ch++;

				}

				string nospace4 = netstr.substr(countspace, netstr.length() - countspace -1);
				
				while (isalpha(nospace4[ch1]) || isdigit(nospace4[ch1])|| ispunct(nospace4[ch1]))
				{

					countalpha++;
					ch1++;

				}
				
				string nospace5 = nospace4.substr(0, countalpha);//componentsname
				compnum--;

				macroo.netmacro.push_back(nospace5);

				if (compnum == 0)
				{
					break;
				}

			}

			nett.macronet = macroo.netmacro;
			nettomacro.insert(make_pair(nospace3, nett));
			macrotonet.insert(make_pair(macroo.netmacro, macroo));
			macroo.netmacro.clear();
			nett.macronet.clear();

		}
	}
	netfile.close();

	ifstream mfile;//Ū��mlist��
	vector<string>vecs;
	mfile.open("C:/Users/USER/Desktop/test/case01.mlist");
	string str;
	int n = 0;
	vector<int>mnum;

	while (mfile >> str)
	{

		n++;
		vecs.push_back(str);

	}

	int  num = 0;

	for (__int64 i = 0; i < n; i++)
	{

		if (vecs[i] == "COMPONENTS")
		{

			num = stoi(vecs[i + 1]);
			break;

		}

	}//compnum
	for (int i = 0; i < num; i++)
	{
		mnum.push_back(i);
	}
	int compname = 0;

	for (int i = 0; i < n; i++)
	{

		if (vecs[i] == "-")
		{

			compname = i + 1;
			break;

		}

	}//compname

	int macroname = 0;

	for (int i = 0; i < n; i++)
	{

		if (vecs[i] == "+")
		{

			macroname = i - 1;
			break;

		}

	}//macroname

	int status = 0;

	for (int i = 0; i < n; i++)
	{

		if (vecs[i] == "+")
		{

			status = i + 1;
			break;

		}
	}//status

	int x, y = 0;

	for (__int64 i = 0; i < n; i++)
	{

		if (vecs[i] == "+" && vecs[i + 2] == "(")
		{

			x = i + 3;
			y = i + 4;
			break;

		}

	}//x and y

	int direction = 0;

	for (__int64 i = 0; i < n; i++)
	{

		if (vecs[i] == "+" && vecs[i + 2] == "(" && vecs[i + 5] == ")")
		{

			direction = i + 6;
			break;

		}

	}//direction

	//------------------------------------------------

	infomlist macro;//Ū��.mlist
	map<int, infomlist>macrotable;
	vector<string>mlistmacro;
	int c2 = 0;
	macro.dieareax = stoi(vecs[17]);
	macro.dieareay = stoi(vecs[18]);

	//store diearea
	for (int i = 0; i < num; i++)
	{

		macro.compname = vecs[compname];
		macro.macroname = vecs[macroname];
		mlistmacro.push_back(vecs[compname]);

		if (vecs[status] == "FIXED")
		{

			int nospace7 = 0;
			macro.status = nospace7;

		}

		else if (vecs[status] == "PLACED")
		{

			int nospace7 = 1;
			macro.status = nospace7;

		}

		macro.x = stoi(vecs[x]);
		macro.y = stoi(vecs[y]);
		macro.direction = vecs[direction];
		macroname = macroname + 11;
		macrotable.insert(make_pair(mnum[c2], macro));
		compname = compname + 11;
		status = status + 11;
		x = x + 11;
		y = y + 11;
		direction = direction + 11;
		c2++;

	}//store compname

	mfile.close();

	ifstream tfile;//Ū��������
	vector<string>cvec;
	string cstr;
	tfile.open("C:/Users/USER/Desktop/test/case01.txt");
	int o = 0;
	int maxdisplay = 0;

	while (tfile >> cstr)
	{

		o++;
		cvec.push_back(cstr);

	}

	maxdisplay = stoi(cvec[1]);

	tfile.close();

	ifstream dfile;//Ū��def��

	dfile.open("C:/Users/USER/Desktop/test/case01.def");
	infostandardcell standardcell;
	map<int, infostandardcell>standardtable;//standardtable
	map<int, infopin>pintable;//pintable
	string dstr;

	int space = 0;
	int dnum = 0;
	int pnum = 0;
	int jump = 0;

	while (getline(dfile, dstr))
	{

		if (dstr.size() == 0)
		{

			space++;

		}

		else if (space == 6)
		{

			__int64 n1space = dstr.find(" ");
			string non1space = dstr.substr(n1space + 1, dstr.length() - n1space);
			int n2space = non1space.find(" ");
			string non2space = non1space.substr(0, n2space);
			dnum = stoi(non2space);//components�ƶq
			int standardcellspecify = 0;
			int standardcellwrite = 0;
			int standardcellcheck = 0;//�T�w�S���M.mlist��components����

			vector<int>dnumstandard;

			int c = 0;

			for (int i = 0; i < dnum; i++)
			{

				dnumstandard.push_back(i);

			}
			while (getline(dfile, dstr))
			{

				if (standardcellwrite == 2)//����s�����@��struct�üg�J�ɮ�
				{

					standardtable.insert(make_pair(dnumstandard[c], standardcell));
					c++;
					standardcellwrite = 0;

				}

				if (dstr == "END COMPONENTS")//�}�lŪpin�}
				{

					getline(dfile, dstr);

					if (dstr.size() == 0)
					{

						space++;

					}

					if (space == 7)
					{

						getline(dfile, dstr);
						__int64 n1space = dstr.find(" ");
						string non1space = dstr.substr(n1space + 1, dstr.length() - n1space);
						int n2space = non1space.find(" ");
						string non2space = non1space.substr(0, n2space);
						pnum = stoi(non2space);//pin�ƶq
						infopin pin;
						int pinwrite = 0;
						int pinspecify = 0;
						vector<int>pnumstandard;

						int c1 = 0;

						for (int i = 0; i < pnum; i++)
						{

							pnumstandard.push_back(i);

						}

						while (getline(dfile, dstr))
						{

							if (dstr == "END PINS")
							{

								jump = 1;
								break;

							}

							if (pinwrite == 2)//����s�����@��struct�üg�J�ɮ�
							{

								pintable.insert(make_pair(pnumstandard[c1], pin));
								c1++;
								pinwrite = 0;

							}

							if (pinspecify == 0)
							{

								__int64 space1 = dstr.find(" ");
								string nospace1 = dstr.substr(space1 + 1, dstr.length() - space1 - 1);
								int space2 = nospace1.find(" ");
								string nospace2 = nospace1.substr(0, space2);//components name
								pin.pinname = "PIN_";//�t�X.net�ɮ�pin�W��
								pin.pinname.append(nospace2, 0, nospace2.length() - 1);
								pinwrite++;
								pinspecify = 1;
								continue;

							}

							else if (pinspecify == 1)
							{

								pinspecify = 2;
								continue;

							}

							else if (pinspecify == 2)
							{

								__int64 space1 = dstr.find(" ");
								string nospace1 = dstr.substr(space1 + 1, dstr.length() - space1 - 1);
								int space2 = nospace1.find(" ");
								string nospace2 = nospace1.substr(0, space2);//status
								__int64 brackets1 = nospace1.find("(");
								string nobrackets1 = nospace1.substr(brackets1 + 2, nospace1.length() - brackets1 - 1);//ex:7897160 6261440 ) N
								__int64 space3 = nobrackets1.find(" ");
								string nospace3 = nobrackets1.substr(0, space3);//x�y��
								string nospace4 = nobrackets1.substr(space3 + 1, nobrackets1.length() - space3 - 4);//y�y��
								__int64 brackets2 = nobrackets1.find(")");
								string nobrackets2 = nobrackets1.substr(brackets2 + 2, 2);//��V

								if (nospace2 == "FIXED")
								{
									int nospace6 = 0;
									pin.status = nospace6;
								}

								else if (nospace2 == "PLACED")
								{
									int nospace6 = 1;
									pin.status = nospace6;
								}

								pin.x = stoi(nospace3);
								pin.y = stoi(nospace4);
								pin.direction = nobrackets2;
								pinspecify = 3;
								pinwrite++;
								continue;

							}

							else if (pinspecify == 3)
							{

								pinspecify = 0;
								continue;

							}

						}
					}
				}

				if (jump == 1)
				{

					break;

				}

				else if (standardcellspecify == 0)
				{

					__int64 space1 = dstr.find(" ");
					string nospace1 = dstr.substr(space1 + 1, dstr.length() - space1 - 1);
					int space2 = nospace1.find(" ");
					string nospace2 = nospace1.substr(0, space2);//components name
					int count = 0;
					map<int, infomlist>::const_iterator map_it1 = macrotable.begin();

					for (int i = 0; i < num; i++)//�x�sdef���, �åB�ˬd�M.mlist�ɮ׸̪�components���L����
					{
						if (map_it1->second.compname != nospace2)
						{
							count++;
						}
						map_it1++;
					}

					if (count == num)
					{
						standardcell.standardcellname = nospace2;
						standardcellcheck = 1;
						standardcellwrite++;
						//cout << nospace2 << endl;
					}

					standardcellspecify = 1;

					continue;

				}

				else if (standardcellspecify == 1)
				{

					__int64 space1 = dstr.find(" ");
					string nospace1 = dstr.substr(space1 + 1, dstr.length() - space1 - 1);//PLACED(11875760.........) ;
					int space2 = nospace1.find(" ");
					string nospace2 = nospace1.substr(0, space2);//status
					__int64 brackets1 = nospace1.find("(");
					string nobrackets1 = nospace1.substr(brackets1 + 2, nospace1.length() - brackets1 - 1);//ex:1107320.00000 1101240.00000 ) N ;
					//cout << nobrackets1 << endl;
					__int64 space3 = nobrackets1.find(" ");
					string nospace3 = nobrackets1.substr(0, space3);//x�y��
					string nospace4 = nobrackets1.substr(space3 + 1, nobrackets1.length() - space3 - 6);//y�y��
					__int64 brackets2 = nobrackets1.find(")");
					string nobrackets2 = nobrackets1.substr(brackets2 + 2, 2);//��V

					if (standardcellcheck == 1)
					{

						if (nospace2 == "FIXED")
						{

							int nospace5 = 0;
							standardcell.status = nospace5;

						}
						else if (nospace2 == "PLACED")
						{

							int nospace5 = 1;
							standardcell.status = nospace5;

						}

						standardcell.x = stoi(nospace3);
						standardcell.y = stoi(nospace4);
						standardcell.direction = nobrackets2;
						standardcellcheck = 0;
						standardcellwrite++;

					}

					standardcellspecify = 0;
					continue;
				}
			}
		}
	}
	
	dfile.close();

	//.node
	ifstream nfile;

	nfile.open("C:/Users/USER/Desktop/test/case01.nodes");

	string nstr;
	infostandardpindimension dimension;
	int nspace = 0;
	map<string, infostandardpindimension>dimensiontable;

	while (getline(nfile, nstr))
	{

		if (nstr.size() == 0)
		{
			nspace++;
		}

		else if (nspace == 2)
		{

			while (getline(nfile, nstr))
			{

				if (nstr.size() == 0)
				{

					break;

				}

				__int64 space1 = nstr.find(" ");
				string nospace = nstr.substr(0, space1);//name,ex:A10_o536036
				string nospace1 = nstr.substr(space1 + 1, nstr.length() - space1 - 1);//ex:19000 3420
				__int64 space2 = nospace1.find(" ");
				string nospace2 = nospace1.substr(0, space2);//height
				string nospace3 = nospace1.substr(space2 + 1, nstr.length() - space2 - 1);//width

				dimension.height = stoi(nospace2);
				dimension.width = stoi(nospace3);
				dimensiontable.insert(make_pair(nospace, dimension));

			}
		}
	}
	nfile.close();

	map<int, infomlist>::iterator mlistmap_it = macrotable.begin();
	map<vector<string> , macronetstruct>::iterator macrotonet_it = macrotonet.begin();
	vector<string>relativemacro;
	vector<string>relativemlist;
	srand(time(NULL));

	while (mlistmap_it != macrotable.end())
	{

		while (macrotonet_it != macrotonet.end())
		{

			int i = 0;

			int x = macrotonet_it->second.macrotonetnum;

			while (i != x - 1)
			{

				if (mlistmap_it->second.compname == macrotonet_it->first[i])
				{

					for (int i = 0; i < x; i++)
					{

						if (macrotonet_it->first[i] != mlistmap_it->second.compname)
						{

							relativemacro.push_back(macrotonet_it->first[i]);

						}

					}

					break;
				}

				i++;

			}

			macrotonet_it++;

		}

		for (int i = 0; i < mlistmacro.size(); i++)
		{

			for (int j = 0; j < relativemacro.size(); j++)
			{

				if (mlistmacro[i] == relativemacro[j])
				{
					
					relativemlist.push_back(relativemacro[j]);

				}

			}

		}
		
		map<int, string>relativemlisttable;

		vector<int>netdegree;

		if (relativemlist.size() > 1)//�P�_�s�u�K��
		{

			while (relativemlist.size() != 0)
			{

				for (int i = 0; i < relativemlist.size(); i++)
				{

					int num = 0;

					for (int j = 0; j < relativemlist.size(); j++)
					{

						if (i != j && relativemlist[j] != "check" && relativemlist[i] == relativemlist[j])
						{
							num++;
						}

						relativemlist[j] == "check";
					}

					relativemlisttable.insert(make_pair(num , relativemlist[i]));

					netdegree.push_back(num);

				}

			}

		}

		sort(netdegree.begin(), netdegree.end(), greater<int>());

		map<string, macrotopin>macrotopinmap;

		map<string, infostandardpindimension>::const_iterator macrohw_it = dimensiontable.begin();

		map<int , string>::iterator relativemlist_it = relativemlisttable.begin();

		if (relativemlist.size() == 0)
		{

			while (macrohw_it != dimensiontable.end())
			{

				macrohw_it++;

				if (macrohw_it->first == mlistmap_it->second.compname)
				{
					break;
				}

			}


			int r = rand() % 4;

			if (r == 0)
			{
				mlistmap_it->second.direction = "S";
			}

			else if (r == 1)
			{
			
				mlistmap_it->second.direction = "S";

			}

			else if (r == 2)
			{
				
				mlistmap_it->second.direction = "S";

			}

			else if (r == 3)
			{
				mlistmap_it->second.direction = "S";
			}

		}

		else if (relativemlist.size() != 0)
		{
			int mlistcheck = 0;

			for (int i = 0; i < netdegree.size(); i++)
			{

				while (relativemlist_it != relativemlisttable.end())
				{

					int r = rand() % 4;

					if (netdegree[i] == relativemlist_it->first && mlistcheck != 1)
					{

						if (r == 0)
						{
							
							mlistmap_it->second.direction = "S";
							
						}

						else if (r == 1)
						{
							
							
							mlistmap_it->second.direction = "S";

						}

						else if (r == 2)
						{
							
							mlistmap_it->second.direction = "S";
						}

						else if (r == 3)
						{
							
							mlistmap_it->second.direction = "S";
							
						}

						int mlistcheck = 1;
					}

					else if (netdegree[i] == relativemlist_it->first && mlistcheck == 1)
					{
						map<int, infomlist>::iterator mlistmap_it2 = macrotable.begin();
						macrohw_it = dimensiontable.begin();

						while (macrohw_it != dimensiontable.end())
						{

							macrohw_it++;

							if (macrohw_it->first == relativemlist_it->second)
							{
								break;
							}

						}

						while (mlistmap_it2 != macrotable.end())
						{
							mlistmap_it2++;

							if (mlistmap_it2->second.compname == relativemlist_it->second)
							{
								break;
							}
						}


						if (r == 0)
						{
							
							mlistmap_it->second.direction = "S";
							
						}

						else if (r == 1)
						{
							
							mlistmap_it->second.direction = "S";

						}

						else if (r == 2)
						{

							mlistmap_it->second.direction = "S";
						}

						else if (r == 3)
						{
							
							mlistmap_it->second.direction = "S";
						}
					}


				}

			}

			mlistcheck == 0;

		}

		mlistmap_it++;

	}

	ofstream of;
	of.open("case01.dmp");
	map<int, infomlist>::iterator mlistmap_it3 = macrotable.begin();

	of << "COMPONENTS" << " " << num << " " << ";" << endl;

	while (mlistmap_it3 != macrotable.end())
	{
		string status;

		if (mlistmap_it3->second.status == 1)
		{
			status = "PLACED";
		}
		else if (mlistmap_it3->second.status == 0)
		{
			status = "FIXED";
		}
		of <<" "<<" "<<" "<< "-" << " " << mlistmap_it3->second.compname << " " << mlistmap_it3->second.macroname << endl
			<<" "<<" "<<" "<<" "<<" "<<" "<< "+" <<" "<< status <<" "<<"("<< " " << mlistmap_it3->second.x << " "
			<< mlistmap_it3->second.y <<" "<<")"<<" "<< mlistmap_it3->second.direction <<" "<< ";" << endl;
		mlistmap_it3++; 
	}

}

	

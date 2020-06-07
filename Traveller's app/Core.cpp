#include "Core.hpp"
#include<iostream>
#include<fstream>


Core::Core():destcnt(0)
{
	destinations = new char* [10];
	for (int i = 0; i < 10; ++i)
		destinations[i] = new char[standart];
	
}

Core::~Core()
{
	del();
}

int Core::checkuser(const user_personal& other)
{
	int userscnt = Data.size();
	for (int i = 0; i <= userscnt; ++i)
		if (Data[i] == other)
			return i;
	return -1;
}

void Core::adduser(const user_personal& other)
{
	int userscnt = Data.size();
	int p = checkuser(other);
	if (!(p == -1))
		return;
	else
		Data.addelem(other);
}

bool Core::compare(const char* username, const char* email, const char* password)
{
	int p = Data.size();
	for (int i = 0; i < p; ++i)
	{
		if (Data[i].checklog(username, email, password))
			return true;
	}
	return false;
}

int Core::checkdest(const char* dest)
{
	for (int i = 0; i < destcnt; ++i)
		if (!strcmp(destinations[i], dest))
			return i;
	return -1;
}

void Core::adddest(const char* dest)
{ 
	if (destcnt + 1 > maxdest)
		resizedest();
	strcpy(destinations[destcnt], dest);
	destcnt++;
}

void Core::resizedest()
{
	char** temp = new char* [maxdest * 2];
	for (int i = 0; i < maxdest * 2; ++i)
		temp[i] = new char[standart];
	for (int i = 0; i < maxdest; ++i)
		strcpy(temp[i], destinations[i]);
	del();
	destinations = temp;
	maxdest *= 2;
}

void Core::addtrip(int user, const Trip& trip)
{
	Data[user].addtrip(trip);
}

bool Core::verifytrip(int begin, int end, char** pictures, int picscnt, int grade)
{
	if ((begin % 10000 >= 2021) || ((begin / 10000) % 100 >= 13) || ((begin / 1000000) % 100 >= 32) ||
		((end % 10000 >= 2021) || ((end / 10000) % 100 >= 13) || ((end / 1000000) % 100 >= 32)))
	{
		std::cout << "wrong dates" << std::endl;
		return false;
	}
	else if (((begin / 1000000) % 100 > (end / 1000000) % 100));
	else if ((begin / 10000) % 100 > (end / 10000) % 100);
	else if (begin % 10000 > end % 10000)
	{
		std::cout << "starting day cant be after ending one " << std::endl;
		return false;
	}
		
	for (int i = 0; i < picscnt; ++i)
		for (int j = 0; j < 50; ++j)
		{
			//std::cout << (int)pictures[i][j] << std::endl;
			/*if ((pictures[i][j] > 'A' || pictures[i][j] > 'z') || (pictures[i][j] > 'Z' && pictures[i][j] < 'a' && pictures[i][j] != '_'))
			{
				std::cout << "useage of forbidden chars in pictures" << std::endl;
				return false;
			}*/
			if (pictures[i][j] <= 'Z' && pictures[i][j] >= 'A');
			else if (pictures[i][j] <= 'z' && pictures[i][j] >= 'a');
			else if (pictures[i][j] == '_' || pictures[i][j] == '.');
			else if (pictures[i][j] == '\0')
				break;
			else
			{
				std::cout << "useage of forbidden chars in pictures" << std::endl;
				return false;
			}
		}
	
	for (int i = 0; i < picscnt; ++i)
		if (strstr(pictures[i], ".jpeg"));
		else if (strstr(pictures[i], ".jpg"));
		else
		{
			std::cout << "pictures must contain file type " << std::endl;
			return false;
		}
	if (grade < 1 || grade>5)
	{
		std::cout << "invalid grade" << std::endl;
		return false;
	}
	return true;
}

bool Core::checkuserdest(int idx, char* destname)
{
	if (Data[idx].checkdest(destname))
		return true;
	return false;
}

char* Core::getusername(char* destname,int &cnt)
{
	int p=-1;
	int userscnt = Data.size();
	for (int i = cnt; i < userscnt; ++i)
		if (checkuserdest(i, destname))
		{
			p = i;
			break;
		}
	char* c = nullptr;
	c=Data[p].getusername(c);
	return c;

}

void Core::getfriendcomment(int idx, char* dest)
{
	// purvo checkfriend, posle getuser ,posle checkuserdest i nakraq tuka
	const char* c=Data[idx].getcomment(dest);
	std::cout << c <<std::endl;
	delete c;
}

double Core::getrating(char* dest)
{
	int p = checkdest(dest);
	int avg = 0;
	int cnt = 0;
	int size = Data.size();
	char* c = nullptr;
	if(p!=-1)
		for (int i = 0; i <size; ++i)
		{
			 c = getusername(dest, i);
			int tmp = getuser(c);
			p = howmanytimesvisited(Data[tmp], dest);
			if (p > 1)
			{
				int* arr = Data[tmp].getrating2(dest, p);
				if (arr)
				{
					for (int j = 0; j < p; ++j)
					{
						avg += arr[i];
						cnt++;
					}
				}
			}
			else
			{
				avg+=Data[tmp].getrating(dest);
				cnt++;
			}
			
		}
	std::cout << "This destination has been visited " << cnt << " times" << std::endl;
	if(c!=nullptr)
		delete[] c;
	return avg / cnt;


}

int Core::getuser(char* name)
{
	int p = Data.size();
	char* c=nullptr;
	for (int i = 0; i <=p; ++i)
	{
		
		if (!strcmp(name, Data[i].getusername(c)))
		{
			delete c;
			return i;
		}
	}
	delete c;
}

void Core::getcertainrating(const user_personal& current,char* user, char* dest)
{
	int p = getuser(user);
	if(p!=-1)
	{
		if (checkuserdest(p, dest))
		{
			int q = howmanytimesvisited(current, dest);
			if (q > 1)
			{
				std::cout << "This user has visited the destination " << q << " times" << std::endl;
				int* arr = Data[p].getrating2(dest, q);
				for (int i = 0; i < q; ++i)
				{
					
					std::cout << "Rating ¹" << i << ": " << arr[i] << std::endl;
					return;
				}
			}
			std::cout << "This rating from this user for the destination is: " << Data[p].getrating(dest) << std::endl;;
		}
		else std::cout << "this user hasnt visited the destination" << std::endl;
	}
	
}

int Core::howmanytimesvisited(const user_personal& current, char* dest)
{
	int p = -1;
	p = checkuser(current);
	if (Data[p].checkdest(dest))
	{
		return Data[p].checkdesttimes(dest);

	}
	else return 0;
}
	

bool Core::checkfriend(const user_personal& current, char* friendname)
{
	int p = checkuser(current);
	if (Data[p].getfriend(friendname))
		return true;
	return false;
}

void Core::printfriendcomment(const user_personal& current, char* friendname, char* dest)
{
	int p = -1;
	if (checkfriend(current, friendname))
	{
		p = getuser(friendname);
		if (checkuserdest(p, dest))
		{
			getfriendcomment(p, dest);
			return;
		}
		else std::cout << "this person hasnt visited that destination" << std::endl;
		return;
	}
	else std::cout << "this user isnt your friend" << std::endl;
}

void Core::serializeuser(char* user)
{
	int p = getuser(user);
	if (p != -1) {
		Data[p].serialize();
		std::cout << "Save complete" << std::endl;
	}
	else std::cout << "this user doesnt exist" << std::endl;

}

void Core::serializedest()
{
	std::ofstream dest("destinations.txt", std::ios::app);
	//dest.open("destinations.txt",std::ios::app);
	dest.write((const char*)&destcnt, sizeof(int));
	for (int i = 0; i < destcnt; ++i)
	{
		int p = strlen(destinations[i]);
		dest.write((const char*)&p, sizeof(int));
		dest.write(destinations[i], p);
	}
	dest.close();
}

void Core::deserializeuser(char* user)
{
	user_personal buff;
	buff.deserialize(user);
	Data.addelem(buff);
	std::cout << "Load complete" << std::endl;

}

void Core::deserializedest()
{
	del();
	std::ifstream dest("destinations.txt", std::ios::app);
	//dest.open("destinations.txt", std::ios::app);
	dest.read(( char*)&destcnt, sizeof(int));
	destinations = new char* [10];
	for (int i = 0; i < destcnt; ++i)
	{
		int p;
		dest.read((char*)&p, sizeof(int));
		destinations[i] = new char[p + 1];
		dest.read(destinations[i], p);
		destinations[i][p] = '\0';
	}
	dest.close();
	std::cout << "Destinations loaded" << std::endl;

}




void Core::del()
{
	for (int i = 0; i < destcnt; ++i)
		delete[] destinations[i];
	delete[] destinations;

}

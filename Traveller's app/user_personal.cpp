#include "user_personal.hpp"
#include<cstring>
#include<fstream>
#include<iostream>

user_personal::user_personal():login()
{
	
}

user_personal::user_personal(const user& log)
{
	login = log;
	
	
}

user_personal& user_personal::operator=(const user_personal& other)
{
	if (this != &other)
		copy(other);
	return *this;
}

bool user_personal::checklog(const char* username, const char* password, const char* email)
{
	
		if (login.cmp(username, email, password))
			return true;
		return false;
}

	

void user_personal::addtrip(const Trip& other)
{
	int p = checktrip(other);
	if (p == -1)
	{
		std::cout << "trip successfully added" << std::endl;
		trips.addelem(other);
	}
	
	
}

void user_personal::addfriend(user_personal& other)
{
	int p = checkfriend(other);
	if (p == -1)
		friends.addelem(&other);
	return;
}

int user_personal::checktrip(const Trip& other)
{
	int tripcount = trips.size();
	for (int i = 0; i < tripcount; ++i)
		if (trips[i] == other)
			return i;
	return -1;
}

int user_personal::checkfriend(const user_personal& other)
{
	int friendscount = friends.size();
	for (int i = 0; i < friendscount; ++i)
		if (*friends[i] == other)
			return i;
	return -1;
}

bool user_personal::operator==(const user_personal& other)
{
	int tripcount = trips.size();
	int tripsother = other.gettrips();
	int friendscount = friends.size();
	int otherfriends = other.getfriends();
	if (login == other.login)
	{
		if (tripcount == tripsother)
			for (int i = 0; i < tripcount; ++i)
				if (trips[i] == other.trips[i]);
				else return false;
		else return false;
		if (friendscount == other.getfriends());
		else return false;
		return true;
	}
	return false;
}




bool user_personal::checkdest(char* dest)
{
	int tripcount = trips.size();
	char* c = nullptr;
	for (int i = 0; i < tripcount; ++i)
		if (!strcmp(trips[i].getdestination(c), dest))
		{

			delete[] c;
			return true;
		}
	delete[] c;
	return false;
}

int user_personal::checkdesttimes(char* dest)
{
	int tripcount = trips.size();
	char* c = nullptr;
	int cnt = 0;
	for (int i = 0; i < tripcount; ++i)
		if (!strcmp(trips[i].getdestination(c), dest))
			cnt++;
	delete[] c;
	return cnt;
}

int user_personal::getdestnum(char* dest)
{

	int tripcount = trips.size();
	char* c = nullptr;
	for (int i = 0; i < tripcount; ++i)
		if (!strcmp(trips[i].getdestination(c), dest))
		{

			delete[] c;
			return i;
		}
	delete[] c;
	return -1;
}

char* user_personal::getusername(char* buff)
{
	
		return buff=login.getusername(buff);

}

const char* user_personal::getcomment(char* dest)
{
	int tripcount = trips.size();
	char* c = nullptr;
	for (int i = 0; i < tripcount; ++i)
		if (!strcmp(trips[i].getdestination(c), dest))
		{
			c=trips[i].getcomment(c);
			return c;
		}
	return nullptr;
}

int user_personal::getrating(char* dest)
{
	int p = getdestnum(dest);
	if (p != -1)
		return	trips[p].getgrade();
	return 0;

}

bool user_personal::getfriend(char* name)
{
	int frs = friends.size();
	char* c = nullptr;
	for (int i = 0; i < frs; ++i)
	{
		if (!strcmp(name, friends[i]->getusername(c)))
		{
			delete c;
			return true;
		}
	}
}

int* user_personal::getrating2(const char* dest, int timesvisited)
{
	int* arr = new int[timesvisited];
	int i=0;
	int p = getdestnummore(dest,i);
	if (p != -1)
	{
		int cnt = 0;
		arr[cnt] = trips[p].getgrade();
		cnt++;
		i++;
		while (i < trips.size())
		{
			
			p = getdestnummore(dest, i);
			arr[cnt] = trips[p].getgrade();
			cnt++;
			i++;
		}
		return arr;
	}
	return nullptr;

}

int user_personal::getdestnummore(const char* dest, int& num)
{

	int tripcount = trips.size();
	char* c = nullptr;
	for (int i = num; i < tripcount; ++i)
		if (!strcmp(trips[i].getdestination(c), dest))
		{

			delete[] c;
			
			return i;
		}
	delete[] c;
	return -1;

}

void user_personal::serialize()
{
	char* c = nullptr;
	c = login.getusername(c);
	char* temp = new char[strlen(c) + 5];
	strcpy(temp, c);
	strcat(temp, ".bin");
	temp[strlen(c) + 4] = '\0';
	std::ofstream obj(temp, std::ios::binary);
	//obj.open(temp,std::ios::binary);
	if(obj.is_open())
	{
	login.serialize(obj);
	int tripcount = trips.size();
	obj.write((const char*)&tripcount, sizeof(int));
	for (int i = 0; i < tripcount; ++i)
		trips[i].serializetrip(obj);
	int frcount = friends.size();
	//obj.write((const char*)&frcount, sizeof(int));
	}
	else
	{
		std::cout << "file couldnt open"<<std::endl;
		
	}
	obj.close();
	delete[] c;
	delete[] temp;

	
}

void user_personal::deserialize(const char* name)
{
	char* temp = new char[strlen(name) + 5];
	strcpy(temp, name);
	strcat(temp, ".bin");
	temp[strlen(name) + 4] = '\0';
	std::ifstream obj(temp,std::ios::binary);
	//obj.open(temp, std::ios::binary);
	if (obj.is_open())
	{
		login.deserialize(obj);
		int tripcount;
		obj.read((char*)&tripcount, sizeof(int));
		Trip buff;
		for (int i = 0; i < tripcount; ++i)
		{
			buff.deserializetrip(obj);
			trips.addelem(buff);
		}
	}
	else std::cout << "the file couldnt open" << std::endl;
	obj.close();
	delete[] temp;
}

void user_personal::copy(const user_personal& other)
{
	int tripcount = trips.size();
	int tripsother = other.gettrips();
	int friendscount = friends.size();
	login = other.login;
	for (int i = 0; i < tripsother; ++i)
		trips.addelem(other.trips[i]);
	for (int i = 0; i < friendscount; ++i)
		friends.addelem(other.friends[i]);
	///----------equal??----------
		//friends = other.friends;
	tripcount = tripsother;
	friendscount = other.getfriends();
}

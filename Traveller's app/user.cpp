#include "user.h"
#include<fstream>
#include<cstring>

user::user()
{
	username = new char[base+1];
	username[base] = '\0';
	password = new char[base+1];
	password[base] = '\0';
	email = new char[base+1];
	email[base] = '\0';
}

user::user(const user& other)
{
	username = new char[strlen(other.username) + 1];
	username[strlen(other.username)] = '\0';
	password = new char[strlen(other.password) + 1];
	password[strlen(other.password)] = '\0';
	email = new char[strlen(other.email) + 1];
	email[strlen(other.email)] = '\0';
	copy(other);
}

user::user(char* username, char* password, char* email)
{
	this->username = new char[strlen(username) + 1];
	this->username[strlen(username)] = '\0';
	strcpy(this->username, username);
	this->password = new char[strlen(password) + 1];
	this->password[strlen(password)] = '\0';
	strcpy(this->password, password);
	this->email = new char[strlen(email) + 1];
	this->email[strlen(email)] = '\0';
	strcpy(this->email, email);
}

user& user::operator=(const user& other)
{
	if (this != &other)
		copy(other);
	return *this;

}

user::~user()
{
	del();
}

bool user::operator==(const user& other)
{
	if (!strcmp(username, other.username))
		if (!strcmp(password, other.password))
			if (!strcmp(email, other.email))
				return true;
	return false;
}

char* user::getusername(char* buff)
{
	buff = new char[strlen(username) + 1];
	buff[strlen(username)] = '\0';
	strcpy(buff, username);
	return buff;

}

bool user::cmp(const char* username, const char* email, const char* password)
{
	if ((!strcmp(this->username, username)) && (!strcmp(this->password, password)) && (!strcmp(this->email, email)))
		return true;
	return false;
}

void user::serialize(std::ofstream& ofs)
{
	if (!ofs.is_open())
	{
		std::cout << "File is not open" << std::endl;
		return;
	}
	int name = strlen(username);
	ofs.write((const char*)&name, sizeof(int));
	ofs.write(username, name);
	int pass = strlen(password);
	ofs.write((const char*)&pass, sizeof(int));
	ofs.write(password, pass);
	int emai = strlen(email);
	ofs.write((const char*)&emai, sizeof(int));
	ofs.write(email, emai);
}

void user::deserialize(std::ifstream& ifs)
{
	del();
	if (!ifs.is_open())
	{
		std::cout << "File is not open" << std::endl;
		return;
	}
	int name;
	ifs.read((char*)&name, sizeof(int));
	username = new char[name + 1];
	if (username)
	{
		ifs.read(username, name);
		username[name] = '\0';
	}
	int pass;
	ifs.read((char*)&pass, sizeof(int));
	password = new char[pass + 1];
	if (password)
	{
		ifs.read(password, pass);
		password[pass] = '\0';
	}
	int emai;
	ifs.read((char*)&emai, sizeof(int));
	email = new char[emai + 1];
	if (email)
	{
		ifs.read(email, emai);
		email[emai] = '\0';
	}


}




void user::copy(const user& other)
{
	strcpy(username, other.username);
	strcpy(password, other.password);
	strcpy(email, other.email);

}

void user::del()
{
	delete[] email;
	delete[] password;
	delete[] username;
}

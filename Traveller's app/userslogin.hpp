#pragma once
#include"Heaparr.hpp"
#include"user.h"
class userslogin
{
	Heaparr<user> Logindata;
public:
	int checkuser(const user& other);
	bool checkuser(const char* username, const char* email, const char* password);
	void adduser(const user& uwu);
	void removeuser(const user& other);
};


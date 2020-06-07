#pragma once
#include<iostream>
#include<cstring>
#include"Core.hpp"
using std::cout;
using std::cin;
using std::endl;
class input
{
	Core uwu;
	char commands[10][20] = { "register","login","logout","go_on_trip" ,"get_rating","get_comment","add_friend","save","load","exit" };
	int currentuser=-1;
public:
	void start();
	void menu();
	void registration();
	void getcommand();
	void switchmenu(int num);
	void login();
	void logout();
	void goontrip();
	void getrating();
	void getcertainrating();
	void getcomment();
	void addfriend();
	void save();
	void load();
	
	
};


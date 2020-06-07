#pragma once
#include<iostream>
#include<cstring>
#include"Core.hpp"
using std::cout;
using std::cin;
using std::endl;
///This class will help us communicate with the user
///
///uwu- a Core object that will help us control the app
///commands - all the available commands in the menu
///currentuser - the index of the currently logged user
class input
{
	Core uwu;
	char commands[10][20] = { "register","login","logout","go_on_trip" ,"get_rating","get_comment","add_friend","save","load","exit" };
	int currentuser=-1;
public:
	///Forces user to input menu
	void start();
	///represents all the available commands in the app
	void menu();
	///Creates a new user 
	void registration();
	///Function that will help us understand what command the user has entered 
	void getcommand();
	///a switch that holds all functions and calls the correct one depending on the number from getcommand
	void switchmenu(int num);
	///checks the user input and looks for such existing account
	///if such account exists it's index is set as current and user is logged in
	void login();
	///sets currentuser to -1
	void logout();
	///Asks the user to input all the necessary(correct) information so a journey can be created
	void goontrip();
	///Informs the use about the rating of the destination of his choice 
	void getrating();
	///Returns rating from 1 exact user
	void getcertainrating();
	///Allows current user to see comments about a destination
	void getcomment();
	///adds a friend to current user
	void addfriend();
	///Saves the whole account of 1 user or all the destinations in the app
	void save();
	///Loads the whole account of 1 user or all destinations ever saved
	void load();
	
	
};


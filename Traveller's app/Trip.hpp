#pragma once
#include<iostream>
static int standart = 200;
///This class will help us create a single journey for our users
///
///destination - char* 
///begind - int for the date when the trip beggan
///end - int for the date when the trip ended
///comment-char* a place where users can leave a comment for the trip
///pictures - array where a user can input various pictures 
///picturescount - the amount of the pictures the user has entered 
/// maxpictures - the max size of the pictures array
///rating - int that the user has placed as a grade for the trip
class Trip
{
	char* destination;
	int begin;
	int end;
	char* comment;
	char** pictures;
	int picturescount;
	int maxpictures = 10;
	int rating;
public:
	///Default constructor, just allocates mem 
	Trip();
	///a constructor that helps us set all the data
	Trip(char* destination, int begin, int end, char* comment, char** pictures, int picscnt, int rating);
	///We must not forget to check this!=&other then simple call del() and copy()
	Trip& operator=(const Trip& other);
	///destructor calls del()
	~Trip();
	///a function that allows us to resize the pictures array
	void resizepics();
	/// returns a copy of the destination pointer, this helps keep the full encapsulation
	///@note we must not forget that this was its possible for mem leaks
	char* getdestination(char* buff);
	///returns a copy of the comment array, this helps keep the full encapsulation
	///@note we must not forget that this was its possible for mem leaks
	char* getcomment(char* buff);
	///@returns int rating
	int getgrade() { return rating; }
	//void print();//??
	/// this funciton helps us determine if 2 trip objects have same data
	bool operator==(const Trip& other);
	///This helps us set all the needed data for the trip into a file
	///Since the app will have many jouneys its important to be able to save your information
	void serializetrip(std::ofstream& ofs);
	///This function helps us to create a fully working trip object 
	///with all the information taken from file
	void deserializetrip(std::ifstream& ifs);

private:
	void init(char* destination, int begin, int end, char* comment, char** pictures, int picscnt,int rating);
	void copy(const Trip& other);
	void del();
};


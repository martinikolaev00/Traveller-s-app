#pragma once
#include<iostream>
#include"user.h"
#include"Trip.hpp"
#include"Heaparr.hpp"
#include"userslogin.hpp"
static int cnt = 20;
///This class will helps us create a fully working user
///
///login - object of user class to hold the name/pass/email of the user
///trips - an array of trip objects for the user to hold all trips that he went to
///friends - an array of user_personal pointers so the user can have all his friends 
class user_personal
{
	user login;
	//Trip* trips;
	Heaparr<Trip> trips;
	//int tripcount;
	//user_personal* friends;
	Heaparr<user_personal*> friends;
public:
	///Simple defualt contructor
	user_personal();
	///A copy constuctor that helps us created an user by copying everything from someone else
	user_personal(const user& log);
	///We must not forget to check if this!=&other 
	/// after that just call copy() function
	user_personal& operator=(const user_personal& other);
	///checks if the current user has those exact name/pass/email
	bool checklog(const char* username, const char* password, const char* email);
	///add an object trip to our trips array
	void addtrip(const Trip& other);
	///the given user is added to the current's user friendlist
	void addfriend(user_personal& other);
	///Tells us if this trip is inside the trips array
	///and if it's contained there we return it's index
	int checktrip(const Trip& other);
	///Tells us if this user is inside the friends array of the current user
	int checkfriend(const user_personal& other);
	///Tells us if other and *this have the same data with various checks
	bool operator==(const user_personal& other);
	///Returns int for the amount of friends the current user has
	int getfriends() { return friends.size(); }
	///a const function to return number of friends
	const int getfriends() const { return friends.size(); }
	///returns the amount of trips that this user has made
	const int gettrips() const{ return trips.size(); }
	/// Tells us if this user has visited this exact destination
	bool checkdest(char* dest);
	///Tells us how many times the user has visited this exact destination
	int checkdesttimes(char* dest);
	///here we can see in which trip this destination has been visited and the index of the trip is returned
	int getdestnum(char* dest);
	///Returns a copy pointer of the username of the user, we dont return const char* in order to have full encapsulation
	///@note we have a possible mem leak 
	char* getusername(char* buff);
	//user_personal* operator[](int num) { return friends[num]; }
	/// returns a copy pointer to the comment that the user left
	/// when he visited that exact destination
	const char* getcomment(char* dest);
	/// returns int grade, the exact grade that current user has placed when he visited that destination
	int getrating(char* dest);
	///checks if a friend with such name exists in the friends array
	bool getfriend(char* name);
	///if the user has visited the destination more than once then we have to create an overall grade for the destination
	int* getrating2(const char* dest, int timesvisited);
	///a function to help us get all the grades for that exact location
	int getdestnummore(const char* dest, int& num);
	///a function that will set us save of the user information in a file
	///we will have alot of users so its important to save them all
	void serialize();
	///function that will make a fully working user profile with information taken entirely from file
	void deserialize(const char* name);
private:
	void copy(const user_personal& other);
};


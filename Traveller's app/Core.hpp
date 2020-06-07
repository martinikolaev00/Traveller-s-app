#pragma once
#include<fstream>
#include"Heaparr.hpp"
#include"user_personal.hpp"
///this class will help us create an object that can control the whole app
///
/// data- vector of all the user accounts in the app
/// destinations- array of all the destinations every visited
///destcnt - the current size of the destinations array
///maxdest - the current max size for the destinations array
class Core
{
	Heaparr<user_personal> Data;
	char** destinations;
	//int userscnt;
	int destcnt;
	int maxdest=10;
public:
	///Simple default destructor just allocates mem
	Core();
	///destructor calls del()
	~Core();
	///checks if the given user is already registered in the app
	int checkuser(const user_personal& other);
	///adds the user to the user vector if he doesnt exist there
	void adduser(const user_personal& other);
	///another way to check if the username/password already exist in the data base without creating user_personal
	bool compare(const char* username, const char* email, const char* password);
	///checks if the given destination exists in the databae and if it does returns it's index
	int checkdest(const char* dest);
	///adds the given destination exists in the app, if it does it is added
	void adddest(const char* dest);
	///expands the destinations array if needed
	void resizedest();
	///adds the given trip to the user with index user
	void addtrip(int user, const Trip& trip);
	///to create a trip it is required for the user to input various types of data, this function helps us to verify if its correct
	bool verifytrip(int begin, int end, char** pictures, int picscnt,int grage);
	///gives us an answer whether user on spot idx in the Data array has visited this destination
	bool checkuserdest(int idx, char* destname);
	/// returns a copy of the names of the users that have visited this exact destination, we use the cnt var so we can keep calling this function until we reach the end of the array with users
	///@note possible mem leak
	char* getusername(char* destname,int &cnt);
	///returns the current size of the user array
	int getusercnt() { return Data.size();}
	///prints the comment that the user on spot idx has left for that exact destination
	void getfriendcomment(int idx, char* dest);
	///returns the overall rating that all the users in the app have left for that location
	double getrating(char* dest);
	///returns the index of the user that has that name
	int getuser(char* name);
	///returns the rating from current user about that destination
	void getcertainrating(const user_personal& current,char* user,char* dest);
	///returns how many times that user has visited the destination
	int howmanytimesvisited(const user_personal& current,char*  dest);
	/// tells is whether the user "current" has a friend with name friendname
	bool checkfriend(const user_personal& current ,char* friendname);
	///prints the comment that the friend has left about the destination
	void printfriendcomment(const user_personal& current, char* friendname, char* dest);
	///returns data[num]
	user_personal& operator[](int num){ return Data[num]; }
	///puts all data about user with name user into a file
	void serializeuser(char* user);
	///saves all the current destinations into a file
	void serializedest();
	///looks for a file with name "user.bin" if such file exists it withdraws all the needed information to create a user
	void deserializeuser(char* user);
	///loads all the possible destinations from file
	void deserializedest();

private:
	void del();
};


#pragma once
#include<fstream>
#include<iostream>
static int base = 200;
/// a short class to help us create login profiles
///@param username - char* for name
///@param password - char* for password
///@param email - char* for email
class user
{
	char* username;
	char* password;
	char* email;
public:
	/// simple contructor, just allocating mem
	user();
	///Copy constructor, allocating mem and calling copy function
	///@see copy()
	user(const user& other);
	///A constructor to help us set all the needed data
	user(char* username, char* password, char* email);
	///We must not forget to check if this != & other, after that just call del() and copy()
	user& operator=(const user& other);
	/// Destructor calls del()
	~user();
	///Helps us demermine whether 2 user objects are the same
	bool operator==(const user& other);
	///Returns a copy pointer of username in oder to achieve full encapsulation
	///@note must be careful about mem leaks
	char* getusername(char* buff);
	///A function close to operator==
	bool cmp(const char* username, const char* email, const char* password);
	///Helps us to store all of the date for our user in a file
	///@note check if file is opened is imporatant
	void serialize(std::ofstream& ofs);
	///Helps us to create a fully working user with data from file
	///@note check if file is opened is imporatant
	void deserialize(std::ifstream& ifs);
private:
	void copy(const user& other);
	void del();
};

 

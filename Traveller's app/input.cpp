#include "input.hpp"
#include<iostream>

int isdigit(int c)
{
	return c >= '0' && c <= '9';
}
void input::start()
{
	cout << "\t\t Welcome to our Traveller's app" << endl;
	cout << "Write menu to see the available commands" << endl;
	char command[20];
	while (true)
	{
		cin >> command;
		if (!strcmp(command, "menu"))
			break;
		else cout << "invalid command" << endl;
		memset(command, 20, '\0');
	}
	menu();

}

void input::menu()
{
	
	cout << "The available commands are: " << endl <<
		"1)register" << endl <<
		"2)login" << endl <<
		"3)logout" << endl <<
		"4)go_on_trip" << endl <<
		"5)get_rating" << endl <<
		"6)get_comment" << endl <<
		"7)add_friend" << endl <<
		"8)save" << endl <<
		"9)load" << endl <<
		"10)exit" << endl;
	getcommand();

}

void input::registration()
{
	char* username= new char[200];
	char* password= new char[200];
	char* email= new char[200];
	cout << "username: ";cin >> username;
	cout << "email: "; cin >> email; cout;
	cout << "password: ";cin >> password;cout << endl;
	if (uwu.compare(username, email, password))
		cout << "such user already exists" << endl;
	else 
	{
		user_personal buff(user(username, password, email));
			uwu.adduser(buff);
			cout << "User has been created successfully, you can login now" << endl;
	}
	delete[] username;
	delete[] password;
	delete[] email;
}

void input::getcommand()
{
	char command[20];
	
	int p = -1;
	while (true)
	{
		cin >> command;
		for (int i = 0; i < 10; ++i)
		{
			if (!strcmp(command, commands[i]))
			{
				p = i;
				break;
			}
		}
		if (p == 9)
			break;
		else switchmenu(p);
		memset(command, 20, '\0');
		p = -1;
	}
}

void input::switchmenu(int num)
{
	switch (num)
	{
	case 0:
	{
		registration();
		break;
	}case 1:
	{
		login();
		break;
	}case 2:
	{
		logout();
		break;
	}case 3:
	{
		goontrip();
		break;
	}case 4:
	{
		getrating();
		break;
	}case 5:
	{
		getcomment();
		break;
	}case 6:
	{
		addfriend();
		break;
	}case 7:
	{
		save();
		break;
	}case 8:
	{
		load();
		break;
	}
	default:
	{
		cout << "invalid command, try again: " << endl;
		break;
	}
	}
}

void input::login()
{
	char* username = new char[200];
	char* password = new char[200];
	char* email = new char[200];
	cout << "username: "; cin >> username;
	cout << "email: "; cin >> email; cout;
	cout << "password: "; cin >> password; cout << endl;
	if (uwu.compare(username, email, password))
	{
		int p = uwu.getuser(username);
		currentuser = p;
		cout << "successfully logged in" << endl;
	}
	else cout << "this user doesnt exist, please register" << endl;
	delete[] username;
	delete[] password;
	delete[] email;

}

void input::logout()
{
	if (currentuser == -1)
	{
		cout << "you are not logged in" << endl;
		return;
	}
	currentuser = -1;
	cout << "successfully logged out" << endl;
}

void input::goontrip()
{
	if (currentuser == -1)
	{
		cout << "you are not logged in" << endl;
		return;
	}
	char dest[200];
	char begin[20];
	int begin1=0;
	char end[20];
	int end1 = 0;
	char c;
	cout << "enter destination: ";
	cin.ignore();
	cin.get(dest,200,'\n');
	cout << "enter starting day of the trip(day/month/year) :";
	cin >> begin;
	int cnt = 0;
	for (int i = 0; i < 10; ++i)
	{
		
		c = begin[i];
		if (isdigit(c))
		{

			begin1 += ((int)(begin[i]) - 48) * pow(10, 7 - cnt);
			cnt++;
		}
		
		
		
	}
	cout << "enter ending day of the trip(day/month/year) :";
	cnt = 0;
	cin >> end;
	for (int i = 0; i < 10; ++i)
	{
		c = end[i];
		if (isdigit(c))
		{
			end1 += ((int)(end[i]) - 48) * pow(10, 7 - cnt);
			cnt++;
		}

	}
	cout << "enter your grade for the trip (from 1 to 5):  ";
	int grade;
	cin >> grade;
	char comment[400];
	cout << "enter your comment for the trip:";
	cin.ignore();
	cin.getline(comment, 400);
	cout << "the number of pictures you wish to enter is: ";
	int numpics; cin >> numpics;
	char** pictures = new char* [numpics];
	for (int i = 0; i < numpics; ++i)
	{
		pictures[i] = new char[51];
		pictures[i][50] = '\0';
		cout << "enter pic num " << i + 1 << " :";
		cin >> pictures[i];
	}
	if (uwu.verifytrip(begin1, end1, pictures, numpics, grade))
	{
		{

			Trip buff(dest, begin1, end1, comment, pictures, numpics, grade);

			uwu.addtrip(currentuser, buff);
			uwu.adddest(dest);
			for (int i = 0; i < numpics; ++i)
				delete[] pictures[i];
			delete[] pictures;
		}
	}
	else
	{
		for (int i = 0; i < numpics; ++i)
			delete[] pictures[i];
		delete[] pictures;
	}

	
}

void input::getrating()
{
	if (currentuser == -1)
	{
		cout << "you are not logged in" << endl;
		return;
	}
	int p;
	char dest[201];
	dest[200] = '\0';
	cout << "Do you overall rating for the destination(1)" <<endl<<
		"or rating from a user(2): ";
	cin >> p;
	if (p == 2)
	{
		getcertainrating();
		return;
	}
	else if (p != 1)
	{
		cout << "choose a correct option" << endl;
		return;
	}
	cout << "enter the name of the destination you want rating for: ";
	cin.ignore();
	cin.getline(dest, 200);
	p=uwu.checkdest(dest);
	if (p == -1)
	{
	cout << "This destination doesnt exist in the database" << endl;
	return;
	}
		
	cout<<"the overall rating for this location is: "<<uwu.getrating(dest)<<endl;
	
}

void input::getcertainrating()
{
	cout << "write the destination u want rating for: ";
	char dest[200]; cin >> dest;
	cout << "write the user u want rating from: ";
	char name[200]; cin >> name;
	int p = uwu.getuser(name);
	if (p == -1)
	{
		cout << "this user isnt registered " << endl;
		return;
	}
	if (!uwu.checkuserdest(p, dest))
	{
		cout << "this user hasnt visited this destination " << endl;
		return;
	}
	uwu.getcertainrating(uwu[currentuser], name, dest);

}

void input::addfriend()
{

	if (currentuser == -1)
	{
		cout << "you are not logged in" << endl;
		return;
	}
	char user[200];
	cout << "Enter the name of the user you wanna be friends with: ";
	cin >> user;
	int p = -1;
	p=uwu.getuser(user);
	if (p != -1 && p!=currentuser)
	{
		uwu[currentuser].addfriend(uwu[p]);
		cout << "friend added " << endl;
	}
	else cout << "this user doesnt exist or is logged in " << endl;

}

void input::save()
{
	cout << "Do you want to save a user(1)\n or destinations(2): ";
	int p; cin >> p;
	if (p == 2)
	{
		uwu.serializedest();
		return;
	}
	else if (p == 1)
	{
		char name[100];
		cout << "Type the name of the user you want to save: ";
		cin >> name;
		uwu.serializeuser(name);
	}
	else cout << "choose a correct option " << endl;
}

void input::load()
{
	cout << "Do you want to load a user(1)\n or destinations(2): ";
	int p; cin >> p;
	if (p == 2)
	{
		uwu.deserializedest();
		return;
	}
	else if (p == 1)
	{
		char name[100];
		cout << "Type the name of the user you want to load: ";
		cin >> name;
		uwu.deserializeuser(name);
	}
	else cout << "choose a correct option " << endl;
}

void input::getcomment()
{
	if (currentuser == -1)
	{
		cout << "you are not logged in" << endl;
		return;
	}
	char dest[200];
	char user[200];
	cout << "Enter the destination you want comments for: ";
	cin.ignore();
	cin.getline(dest, 200);
	int p = uwu.checkdest(dest);
	if (p == -1)
	{
		cout << "this destination doesnt exist in the app yet " << endl;
		return;
	}
	p = -1;
	cout << "Enter the user whose comment you want: ";// << endl;
	cin >> user;
	p = uwu.getuser(user);
	if (p == -1)
	{
		cout << "This user isnt registered " << endl;
		return;
	}
	if (uwu.checkuserdest(p, dest))
	{
		uwu.getfriendcomment(p, dest);
	}
	else
	{
		cout << "This user hasnt visited this destination " << endl;
		return;
	}
	
}


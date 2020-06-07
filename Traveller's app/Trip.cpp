#include "Trip.hpp"
#include<cstring>
#include<fstream>
#include<iostream>
using std::cout;
using std::cin;
using std::endl;
Trip::Trip():begin(0),end(0),picturescount(0),rating(0)
{
	destination = new char[standart +1];
	strcpy(destination, "");
	destination[standart] = '\0';
	
	comment = new char[2*standart+1];
	strcpy(comment, "");
	comment[2*standart] = '\0';
	pictures = new char* [maxpictures];
	
	for (int i = 0; i < maxpictures; ++i)
		pictures[i] = new char[50+1];
	for (int i = 0; i < maxpictures; ++i)
		pictures[i][50] = '\0';
	

}

Trip::Trip(char* destination, int begin, int end, char* comment, char** pictures, int picscnt, int rating)
{
	init(destination, begin, end, comment, pictures, picscnt,rating);
}

Trip& Trip::operator=(const Trip& other)
{
	if (this != &other)
		copy(other);
	return*this;
}

Trip::~Trip()
{

	del();
}

void Trip::resizepics()
{
	maxpictures *= 2;
	char** temp = new char* [maxpictures];
	for (int i = maxpictures / 2; i < maxpictures; ++i)
		pictures[i] = new char[50];
	for (int i = 0; i < maxpictures / 2; ++i)
		strcpy(temp[i], pictures[i]);
	delete[] pictures;
	pictures = temp;

}

char* Trip::getdestination(char* buff)
{
	buff = new char[strlen(destination) + 1];
	strcpy(buff, destination);
	buff[strlen(destination)] = '\0';
	return buff;
}

char* Trip::getcomment(char* buff)
{
	buff = new char[strlen(comment) + 1];
	strcpy(buff, comment);
	buff[strlen(comment)] = '\0';
	return buff;
}

//void Trip::print()
//{
//	/*cout << destination << "\t\t" << "from-" << begin / 1000000 << "." << (begin / 10000) % 100 << "." << begin % 10000 << "  to" << end / 1000000 << "." << (end / 10000) % 100 << "." << end % 10000 <<
//		"\t\t" << comment;*/
//}

bool Trip::operator==(const Trip& other)
{
	if (!strcmp(destination, other.destination))
		if (begin == other.begin)
			if (end == other.end)
				if (!strcmp(comment, other.comment))
					if (picturescount == other.picturescount)
						if (rating == other.rating)
						{
							for (int i = 0; i < picturescount; ++i)
								if (strcmp(pictures[i], other.pictures[i]))
									return false;
							return true;
						}
								
	return false;


}

void Trip::serializetrip(std::ofstream& ofs)
{
	
	if (!ofs.is_open())
	{
		std::cout << "File is not open" << std::endl;
		return;
	}
	int dest = strlen(destination);
	ofs.write((const char*)&dest, sizeof(int));
	ofs.write(destination, dest);
	ofs.write((const char*)&begin, sizeof(int));
	ofs.write((const char*)&end, sizeof(int));
	int com = strlen(comment);
	ofs.write((const char*)&com, sizeof(int));
	ofs.write(comment, com);
	ofs.write((const char*)&picturescount, sizeof(int));
	for (int i = 0; i < picturescount; ++i)
	{
		int pics = strlen(pictures[i]);
		ofs.write((const char*)&pics, sizeof(int));
		ofs.write(pictures[i], pics);
	}
	ofs.write((const char*)&maxpictures, sizeof(int));
	ofs.write((const char*)&rating, sizeof(int));


}

void Trip::deserializetrip(std::ifstream& ifs)
{
	del();
	if (!ifs.is_open())
	{
		std::cout << "File is not open" << std::endl;
		return;
	}
	int dest;
	ifs.read((char*)&dest, sizeof(int));
	destination = new char[dest + 1];
	if (destination)
	{
		ifs.read(destination, dest);
		destination[dest] = '\0';
	}
	ifs.read((char*)&begin, sizeof(int));
	ifs.read((char*)&end, sizeof(int));
	int com;
	ifs.read((char*)&com, sizeof(int));
	comment = new char[com + 1];
	if (comment)
	{
		ifs.read(comment, com);
		comment[com] = '\0';
	}
	ifs.read((char*)&picturescount, sizeof(int));
	pictures = new char* [10];
	for (int i = 0; i < picturescount; ++i)
	{
		int pics;
		ifs.read((char*)&pics, sizeof(int));
		pictures[i] = new char[pics+1];
		if (pictures[i]) 
		{
			ifs.read(pictures[i], pics);
			pictures[i][pics] = '\0';
		}
	}
	ifs.read((char*)&maxpictures, sizeof(int));
	ifs.read((char*)&rating, sizeof(int));
}

void Trip::init(char* destination, int betin, int end, char* comment, char** pictures,int picscnt, int rating)
{
	this->destination = new char[strlen(destination)+1];
	this->destination[strlen(destination)] = '\0';
	strcpy(this->destination, destination);
	this->comment = new char[strlen(comment)+1];
	this->comment[strlen(comment)]= '\0';
	strcpy(this->comment, comment);
	this->pictures = new char* [maxpictures];
	for (int i = 0; i < picscnt; ++i)
	{
		this->pictures[i] = new char[strlen(pictures[i])+1];
		strcpy(this->pictures[i], pictures[i]);
		this->pictures[i][strlen(pictures[i])] = '\0';
	}
	this->begin = betin;
	this->end = end;
	picturescount = picscnt;
	this->rating = rating;

	
}

void Trip::copy(const Trip& other)
{
	strcpy(destination, other.destination);
	begin = other.begin;
	end = other.end;
	strcpy(comment, other.comment);
	if (other.picturescount > maxpictures)
		resizepics();
	for (int i = 0; i < other.picturescount; ++i)
		strcpy(pictures[i], other.pictures[i]);
	picturescount = other.picturescount;
	rating = other.rating;
}

void Trip::del()
{
	delete[] destination;
	delete[] comment;
	for (int i = 0; i <picturescount; ++i)
		delete[] pictures[i];
	delete[] pictures;
}

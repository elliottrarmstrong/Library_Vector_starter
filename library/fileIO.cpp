//============================================================================
// Name        : fileIO.cpp
// Author      : Elliott Armstrong
// Version     : 11.10.2019
// Copyright   : Please don't steal
// Description :
//============================================================================

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../includes_usr/constants.h"
#include "../includes_usr/fileIO.h"
#include "../includes_usr/fileIO.h"
using namespace std;

const char CHAR_TO_SEARCH_FOR = ',';

/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
int loadBooks(std::vector<book> &books, const char* filename)
{
	ifstream file;
	file.open(filename);

	if(!file.is_open()){
		return COULD_NOT_OPEN_FILE;
	}
	books.clear();
	if(file.peek() == std::ifstream::traits_type::eof()){
		return NO_BOOKS_IN_LIBRARY;
	}

	string bline;
	string btoken;
	stringstream sslb;
	book mybook;

	while(!file.eof()){
		if(file.peek() == std::ifstream::traits_type::eof())
			break;

		getline(file,bline);
		sslb.str(bline);

		//get the id
		getline(sslb, btoken, CHAR_TO_SEARCH_FOR);
		mybook.book_id = stoi(btoken);

		//get the title
		getline(sslb, mybook.title, CHAR_TO_SEARCH_FOR);

		//get the author
		getline(sslb, mybook.author, CHAR_TO_SEARCH_FOR);

		//get the checkout state
		getline(sslb, btoken, CHAR_TO_SEARCH_FOR);
		switch(stoi(btoken)){
		case 0: mybook.state = UNKNOWN;
			break;
		case 1: mybook.state = IN;
			break;
		case 2: mybook.state = OUT;
			break;
		}

		//get the borrowing patron
		getline(sslb, btoken, CHAR_TO_SEARCH_FOR);

		books.push_back(mybook);
		sslb.clear();

	}

	if(file.is_open()){
		file.close();
	}
	return SUCCESS;
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char* filename)
{
	if(books.empty())
		return NO_BOOKS_IN_LIBRARY;

	ofstream file;
	file.open(filename);

	if(!file.is_open())
		return COULD_NOT_OPEN_FILE;

	string output;
	for(int i = 0; i<books.size(); i++){
		file<<to_string(books[i].book_id)+","+books[i].title+","+books[i].author+","+to_string(books[i].state)+","+to_string(books[i].loaned_to_patron_id)+"\n";
	}

	if(file.is_open())
		file.close();

	return SUCCESS;
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char* filename)
{
	ifstream file;
	file.open(filename);

	if(!file.is_open()){
		return COULD_NOT_OPEN_FILE;
	}
	patrons.clear();
	if(file.peek() == std::ifstream::traits_type::eof()){
		return NO_PATRONS_IN_LIBRARY;
	}

	string pline;
	string ptoken;
	stringstream sslp;
	patron mypatron;

	while(!file.eof()){
		if(file.peek() == std::ifstream::traits_type::eof())
			break;

		getline(file,pline);
		sslp.str(pline);

		//get the id
		getline(sslp, ptoken, CHAR_TO_SEARCH_FOR);
		mypatron.patron_id = stoi(ptoken);

		//get the name
		getline(sslp, mypatron.name, CHAR_TO_SEARCH_FOR);

		//get the number of books borrowed
		getline(sslp, ptoken);
		mypatron.number_books_checked_out = stoi(ptoken);

		patrons.push_back(mypatron);
		sslp.clear();
	}

	if(file.is_open()){
		file.close();
	}
	return SUCCESS;
}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char* filename)
{
	if(patrons.empty())
			return NO_PATRONS_IN_LIBRARY;

	ofstream file;
	file.open(filename);

	if(!file.is_open())
		return COULD_NOT_OPEN_FILE;

	for(int j = 0; j < patrons.size(); j++){
		file<<to_string(patrons[j].patron_id)+","+patrons[j].name+","+to_string(patrons[j].number_books_checked_out)+"\n";
	}

	if(file.is_open())
		file.close();

	return SUCCESS;
}

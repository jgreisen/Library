#include "Patron.hpp"
#include "Book.hpp"

static int c_inc = 1;

Book::Book()
{
	c_inc++;
	idCode = "C" + c_inc;
	title = "";
	author = "";
	setLocation(ON_SHELF);
	setCheckedOutBy(NULL);
	setRequestedBy(NULL);
	setDateCheckedOut(0);
}

Book::Book(std::string idc, std::string t, std::string a)
{
	idCode = idc;
	title = t;
	author = a;
	setLocation(ON_SHELF);
	setCheckedOutBy(NULL);
	setRequestedBy(NULL);
	setDateCheckedOut(0);	
}

std::string Book::getIdCode()
{
	return idCode;
}

std::string Book::getTitle()
{
	return title;
}

std::string Book::getAuthor()
{
	return author;
}

Locale Book::getLocation()
{
	return location;
}

void Book::setLocation(Locale lo)
{
	location = lo;
}

Patron* Book::getCheckedOutBy()
{
	return checkedOutBy;
}

void Book::setCheckedOutBy(Patron* p)
{
	checkedOutBy = p;
}

Patron* Book::getRequestedBy()
{
	return requestedBy;
}

void Book::setRequestedBy(Patron* p)
{
	requestedBy = p;
}

int Book::getDateCheckedOut()
{
	return dateCheckedOut;
}

void Book::setDateCheckedOut(int d)
{
	dateCheckedOut = d;
}

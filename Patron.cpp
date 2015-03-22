#include "Patron.hpp"
#include "Book.hpp"

static int n_inc = 1;

Patron::Patron()
{
	n_inc++;
	idNum = "N" + n_inc;
	name = "";
	fineAmount = 0.00;
}

Patron::Patron(std::string idn, std::string n)
{
	n_inc++;
	idNum = idn;
	name = n;
	fineAmount = 0.00;
}

std::string Patron::getIdNum()
{
	return idNum;
}

std::string Patron::getName()
{
	return name;
}

std::vector<Book*> Patron::getCheckedOutBooks()
{
	return checkedOutBooks;
}

void Patron::addBook(Book* b)
{
	checkedOutBooks.push_back(b);
}

void Patron::removeBook(Book* b)
{
	for(int i = 0; i < checkedOutBooks.size(); i++)
	{
		if(checkedOutBooks[i]->getIdCode() == b->getIdCode())
			checkedOutBooks.erase(checkedOutBooks.begin() + i);
	}
}

double Patron::getFineAmount()
{
	return fineAmount;
}

void Patron::amendFine(double amount)
{
		fineAmount += amount;
}

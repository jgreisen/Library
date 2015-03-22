#include "Book.hpp"
#include "Patron.hpp"
#include "Library.hpp"

Library::Library()
{
	currentDate = 0;
	holdings.reserve(100);
	members.reserve(100);
}

void Library::addBook()
{
	std::string idCode;
	std::string title;
	std::string author;

	std::cout << "\nNew Book\n";
	std::cout << "--------\n";
	std::cout << "Enter ID Code: ";
	std::getline(std::cin, idCode);
	std::cout << "Enter Title: ";
	std::getline(std::cin, title);
	std::cout << "Enter Author: ";
	std::getline(std::cin, author);

	for(int i = 0; i < holdings.size(); i++)
	{
		if(holdings[i].getIdCode() == idCode)
		{
			std::cout << "\nThat Book ID Code is already in use\n";
			return;
		}
	}

	Book newBook(idCode, title, author);
	holdings.push_back(newBook);
}

void Library::addMember()
{
	std::string idNum;
	std::string name;

	std::cout << "\nNew Patron\n";
	std::cout << "----------\n";
	std::cout << "Enter ID Number: ";
	std::getline(std::cin, idNum);
	std::cout << "Enter Name: ";
	std::getline(std::cin, name);

	for(int i = 0; i < members.size(); i++)
	{
		if(members[i].getIdNum() == idNum)
		{
			std::cout << "\nThat Patron ID Number is already in use\n";
			return;
		}
	}

	Patron newPatron(idNum, name);
	members.push_back(newPatron);
}

void Library::checkOutBook(std::string patronID, std::string bookID)
{
	int count = 0;  // Variable for counting members and holdings

	// Check if Patron exists
	for(int i = 0; i < members.size(); i++)
	{
		if(members[i].getIdNum() == patronID)
		{
		    count++;
		}
	}

	if(count == 0)
    {
        std::cout << "\nPatron does not exist\n";
        return;
    }
    else
        count = 0;

	// Check if Book exists
	for(int i = 0; i < holdings.size(); i++)
	{
		if(holdings[i].getIdCode() == bookID)
		{
		    count++;
		}
	}

	if(count == 0)
    {
        std::cout << "\nBook does not exist\n";
        return;
    }
    else
        count = 0;

	// Check if Book is already checked out
	for(int i = 0; i < members.size(); i++)
	{
		for(int y = 0; y < members[i].getCheckedOutBooks().size(); y++)
		{
			if(members[i].getCheckedOutBooks()[y]->getIdCode() == bookID)
			{
				std::cout << "\nBook is already checked out\n";
				return;
			}
		}
	}

    // Check out book by updating checkedOutBy, dateCheckedOut, Location,
    // Patron's list and then display to user
	for(int i = 0; i < holdings.size(); i++)
	{
		if(holdings[i].getIdCode() == bookID)
		{
			for(int y = 0; y < members.size(); y++)
			{
				if(members[y].getIdNum() == patronID)
				{
                    // Check if book has been requested
					if(holdings[i].getRequestedBy() != NULL)
                    {
                        // Check if request is for current patron
                        if(holdings[i].getRequestedBy()->getIdNum() == patronID)
                        {
                            holdings[i].setRequestedBy(NULL);
                        }
                        else
                        {
                            std::cout << "\nBook is on hold by another patron\n";
                            return;
                        }
                    }

                    holdings[i].setCheckedOutBy(&members[y]);
                    holdings[i].setDateCheckedOut(currentDate);
                    holdings[i].setLocation(CHECKED_OUT);

                    // Add book to Patron's list
                    members[y].addBook(&holdings[i]);

                    // Print to screen book was checked out successfully
                    std::cout << "\nThe book " << holdings[i].getTitle() << " has been checked ";
                    std::cout << "out to " << members[y].getName() << "\n";
                    return;
				}
			}
		}
	}
}

void Library::returnBook(std::string bookID)
{
	int count = 0;  // Variable for counting holdings

    // Check if book is not in library
    for(int i = 0; i < holdings.size(); i++)
    {
        if(holdings[i].getIdCode() == bookID)
        {
            count++;
        }
    }

    if(count == 0)
    {
        std::cout << "\nThat book is not in the library\n";
        return;
    }
    else
        count = 0;

    // Return book by updating Patron's list, location, checkedOutBy
    // and then display to user
    for(int i = 0; i < holdings.size(); i++)
    {
        if(holdings[i].getIdCode() == bookID)
        {
            // Check if book is checked out
            if(holdings[i].getLocation() == CHECKED_OUT)
            {
                holdings[i].getCheckedOutBy()->removeBook(&holdings[i]);
                holdings[i].setCheckedOutBy(NULL);

                // Check if book has been requested
                if(holdings[i].getRequestedBy() == NULL)
                {
                    holdings[i].setLocation(ON_SHELF);
                }
                else
                {
                    holdings[i].setLocation(ON_HOLD_SHELF);
                }

                std::cout << "\nBook " << holdings[i].getTitle() << " has been returned\n";
                return;
            }
            else
            {
                std::cout << "\nThat book is not checked out\n";
                return;
            }
        }
    }
}

void Library::requestBook(std::string patronID, std::string bookID)
{
	int count = 0;  // Variable for counting members and holdings

	// Check if Patron exists
	for(int i = 0; i < members.size(); i++)
	{
		if(members[i].getIdNum() == patronID)
		{
		    count++;
		}
	}

	if(count == 0)
    {
        std::cout << "\nPatron does not exist\n";
        return;
    }
    else
        count = 0;

	// Check if Book exists
	for(int i = 0; i < holdings.size(); i++)
	{
		if(holdings[i].getIdCode() == bookID)
		{
		    count++;
		}
	}

	if(count == 0)
    {
        std::cout << "\nBook does not exist\n";
        return;
    }
    else
        count = 0;

    // Check requested status and checked out status
	for(int i = 0; i < holdings.size(); i++)
	{
	    if(holdings[i].getIdCode() == bookID)
        {
            // Check if book is requested by any Patron
            if(holdings[i].getRequestedBy() != NULL)
            {
                std::cout << "\nBook " << holdings[i].getTitle() << " is already requested";
                std::cout << " by " << holdings[i].getRequestedBy()->getName() << "\n";
                return;
            }
            // Check if for NULL in checkedOutBy
            if(holdings[i].getCheckedOutBy() != NULL)
            {
                // Check if book is checked out by current Patron
                if(holdings[i].getCheckedOutBy()->getIdNum() == patronID)
                {
                    std::cout << "\nBook " << holdings[i].getTitle() << " is already checked";
                    std::cout << " out to " << holdings[i].getCheckedOutBy()->getName() << "\n";
                    return;
                }
            }
            // Request book by updating requestedBy, location and then
            // display to user
            if(holdings[i].getRequestedBy() == NULL)
            {
                for(int y = 0; y < members.size(); y++)
                {
                    if(members[y].getIdNum() == patronID)
                    {
                        holdings[i].setRequestedBy(&members[y]);

                        if(holdings[i].getLocation() == ON_SHELF)
                        {
                            holdings[i].setLocation(ON_HOLD_SHELF);
                        }

                        std::cout << "\nBook " << holdings[i].getTitle() << " has been requested";
                        std::cout << " by " << members[y].getName() << "\n";
                        return;
                    }
                }
            }
        }
	}
}

void Library::payFine(std::string patronID, double payment)
{
	int count = 0;  // Variable for counting members and holdings

	// Check if Patron exists
	for(int i = 0; i < members.size(); i++)
	{
		if(members[i].getIdNum() == patronID)
		{
		    count++;
		}
	}

	if(count == 0)
    {
        std::cout << "\nPatron does not exist\n";
        return;
    }
    else
        count = 0;

    // Amend fine and display to user
	for(int i = 0; i < members.size(); i++)
	{
		if(members[i].getIdNum() == patronID)
        {
            members[i].amendFine(payment);

            std::cout << "The fines for " << members[i].getName();
            std::cout << std::fixed << std::setprecision(2);
            std::cout << " are now $" << members[i].getFineAmount()<< "\n";
        }
	}
}

void Library::incrementCurrentDate()
{
    currentDate++;

    for(int i = 0; i < members.size(); i++)
    {
        for(int y = 0; y < members[i].getCheckedOutBooks().size(); y++)
        {
            if((currentDate - members[i].getCheckedOutBooks()[y]->getDateCheckedOut()) > Book::CHECK_OUT_LENGTH)
            {
                members[i].amendFine(0.10);
            }
        }
    }
}

void Library::viewPatronInfo(std::string patronID)
{
	int count = 0;  // Variable for counting members and holdings

	// Check if Patron exists
	for(int i = 0; i < members.size(); i++)
	{
		if(members[i].getIdNum() == patronID)
		{
		    count++;
		}
	}

	if(count == 0)
    {
        std::cout << "\nPatron does not exist\n";
        return;
    }
    else
        count = 0;

    // Display Patron's ID, Name, Titles of all check out books
    // along with any current fines
    for(int i = 0; i < members.size(); i++)
    {
        if(members[i].getIdNum() == patronID)
        {
            std::cout << "\nPatron Info:\n";
            std::cout << "------------\n";
            std::cout << "ID: " << members[i].getIdNum() << "\n";
            std::cout << "Name: " << members[i].getName() << "\n";
            std::cout << std::fixed << std::setprecision(2);
            std::cout << "Current Fines: $" << members[i].getFineAmount() << "\n";
            std::cout << "\nChecked Out Books:\n";
            if(members[i].getCheckedOutBooks().size() == 0)
                std::cout << "none\n";
            else
            {
                for(int y = 0; y < members[i].getCheckedOutBooks().size(); y++)
                {
                    std::cout << members[i].getCheckedOutBooks()[y]->getTitle() << "\n";
                }
            }
        }
    }
}

void Library::viewBookInfo(std::string bookID)
{
	int count = 0;  // Variable for counting members and holdings

	// Check if Book exists
	for(int i = 0; i < holdings.size(); i++)
	{
		if(holdings[i].getIdCode() == bookID)
		{
		    count++;
		}
	}

	if(count == 0)
    {
        std::cout << "\nBook does not exist\n";
        return;
    }
    else
        count = 0;

    // Display the Book's ID, Title, Author, Location,
    // the name of the requesting party, who has checked it out,
    // and the days left until overdue (or overdue if such)
	for(int i = 0; i < holdings.size(); i++)
	{
		if(holdings[i].getIdCode() == bookID)
		{
            std::cout << "\nBook Info:\n";
            std::cout << "----------\n";
            std::cout << "ID: " << holdings[i].getIdCode() << "\n";
            std::cout << "Title: " << holdings[i].getTitle() << "\n";
            std::cout << "Author: " << holdings[i].getAuthor() << "\n";
            std::cout << "Location: ";
            switch(holdings[i].getLocation())
            {
            case 0:
                std::cout << "on shelf\n";
                break;
            case 1:
                std::cout << "on hold shelf\n";
                break;
            case 2:
                std::cout << "checked out\n";
                break;
            }
            std::cout << "Requested By: ";
            // Check for null value
            if(holdings[i].getRequestedBy() != NULL)
            {
                std::cout << holdings[i].getRequestedBy()->getName() << "\n";
            }
            else
                std::cout << "no one\n";
            std::cout << "Checked Out By: ";
            // Check for null value
            if(holdings[i].getCheckedOutBy() != NULL)
            {
                std::cout << holdings[i].getCheckedOutBy()->getName() << "\n";
            }
            else
                std::cout << "no one\n";

            std::cout << "Days Left Until Due: ";
            // Check for overdue
            if((currentDate - holdings[i].getDateCheckedOut()) > Book::CHECK_OUT_LENGTH)
            {
                std::cout << "overdue\n";
            }
            else
                std::cout << (Book::CHECK_OUT_LENGTH - (currentDate - holdings[i].getDateCheckedOut()));
                std::cout << "\n";
		}
	}
}

#include <iostream>
#include "Book.hpp"
#include "Patron.hpp"
#include "Library.hpp"

int main()
{
    int option = 0;
    std::string patronID, bookID;
    double payment;
	Library puyallup;

    std::cout << "\nWelcome to the Library!\n";

    while(option != 10)
    {
        std::cout << "\nChoose an option:\n";
        std::cout << "-----------------\n";
        std::cout << "1) Add book to Inventory\n";
        std::cout << "2) Add new member to library\n";
        std::cout << "3) Check out book\n";
        std::cout << "4) Return book\n";
        std::cout << "5) Request book\n";
        std::cout << "6) Pay fine\n";
        std::cout << "7) Increment current date\n";
        std::cout << "8) View patron info\n";
        std::cout << "9) View book info\n";
        std::cout << "10) Quit\n";

        // Ask for a menu selection
        std::cout << "\nSelection: ";
        std::cin >> option;

        std::cin.ignore();

        switch(option)
        {
            // Add new Item to ShoppingCart
            case 1:
                puyallup.addBook();
                break;
            case 2:
                puyallup.addMember();
                break;
            case 3:
                std::cout << "\nCheck Out a Book\n";
                std::cout << "----------------\n";
                std::cout << "Enter the Patron ID: ";
                std::getline(std::cin, patronID);
                std::cout << "Enter the Book ID: ";
                std::getline(std::cin, bookID);
                puyallup.checkOutBook(patronID, bookID);
                break;
            case 4:
                std::cout << "\nReturn a Book\n";
                std::cout << "-------------\n";
                std::cout << "Enter the Book ID: ";
                std::getline(std::cin, bookID);
                puyallup.returnBook(bookID);
                break;
            case 5:
                std::cout << "\nRequest a Book\n";
                std::cout << "--------------\n";
                std::cout << "Enter the Patron ID: ";
                std::getline(std::cin, patronID);
                std::cout << "Enter the Book ID: ";
                std::getline(std::cin, bookID);
                puyallup.requestBook(patronID, bookID);
                break;
            case 6:
                std::cout << "\nPay Fine\n";
                std::cout << "--------\n";
                std::cout << "Enter the Patron ID: ";
                std::getline(std::cin, patronID);
                std::cout << "Enter the Payment Amount: ";
                std::cin >> payment;
                puyallup.payFine(patronID, payment);
                break;
            case 7:
                std::cout << "\nDate incremented by 1 day\n";
                puyallup.incrementCurrentDate();
                break;
            case 8:
                std::cout << "\nView Patron Info\n";
                std::cout << "----------------\n";
                std::cout << "Enter the Patron ID: ";
                std::getline(std::cin, patronID);
                puyallup.viewPatronInfo(patronID);
                break;
            case 9:
                std::cout << "\nView Book Info\n";
                std::cout << "--------------\n";
                std::cout << "Enter the Book ID: ";
                std::getline(std::cin, bookID);
                puyallup.viewBookInfo(bookID);
                break;
        }
    }

    // Quit program
    std::cout << "\n\nYou have selected to quit, please click enter.\n";
    std::cin.ignore();
    std::cin.get();

	return 0;
}

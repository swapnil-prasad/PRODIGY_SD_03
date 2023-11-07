#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Contact {
    std::string name;
    std::string phoneNumber;
    std::string email;
};

// Function to add a new contact
void addContact(std::vector<Contact>& contacts) {
    Contact newContact;
    std::cout << "Enter the contact's name: ";
    std::cin.ignore(); // Consume the newline character
    std::getline(std::cin, newContact.name);
    std::cout << "Enter the contact's phone number: ";
    std::cin >> newContact.phoneNumber;
    std::cout << "Enter the contact's email address: ";
    std::cin >> newContact.email;
    contacts.push_back(newContact);
    std::cout << "Contact added successfully!" << std::endl;
}

// Function to view the contact list
void viewContacts(const std::vector<Contact>& contacts) {
    std::cout << "Contact List:" << std::endl;
    for (const Contact& contact : contacts) {
        std::cout << "Name: " << contact.name << std::endl;
        std::cout << "Phone Number: " << contact.phoneNumber << std::endl;
        std::cout << "Email: " << contact.email << std::endl;
        std::cout << "-----------------------" << std::endl;
    }
}

// Function to save contacts to a file
void saveContactsToFile(const std::vector<Contact>& contacts, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const Contact& contact : contacts) {
            file << contact.name << "," << contact.phoneNumber << "," << contact.email << std::endl;
        }
        file.close();
        std::cout << "Contacts saved to file." << std::endl;
    } else {
        std::cerr << "Error: Unable to open the file for writing." << std::endl;
    }
}

// Function to load contacts from a file
void loadContactsFromFile(std::vector<Contact>& contacts, const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        contacts.clear(); // Clear the existing contacts
        std::string line;
        while (std::getline(file, line)) {
            Contact contact;
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            if (pos1 != std::string::npos && pos2 != std::string::npos) {
                contact.name = line.substr(0, pos1);
                contact.phoneNumber = line.substr(pos1 + 1, pos2 - pos1 - 1);
                contact.email = line.substr(pos2 + 1);
                contacts.push_back(contact);
            }
        }
        file.close();
        std::cout << "Contacts loaded from file." << std::endl;
    } else {
        std::cerr << "Warning: Unable to open the file for reading. Creating a new file." << std::endl;
        // You can create an empty file here if it doesn't exist.
    }
}

int main() {
    std::vector<Contact> contacts;
    const std::string filename = "contacts.txt";

    // Load contacts from file (if available)
    loadContactsFromFile(contacts, filename);

    int choice;
    while (true) {
        std::cout << "Contact Management System" << std::endl;
        std::cout << "1. Add Contact" << std::endl;
        std::cout << "2. View Contacts" << std::endl;
        std::cout << "3. Save Contacts" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addContact(contacts);
                break;
            case 2:
                viewContacts(contacts);
                break;
            case 3:
                saveContactsToFile(contacts, filename);
                break;
            case 4:
                // Save contacts and exit
                saveContactsToFile(contacts, filename);
                std::cout << "Goodbye!" << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}

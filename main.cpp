#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class InventoryItem {
public:
    string name;
    string description;
    int quantityAvailable;

    InventoryItem(string n, string d, int q) {
        name = n;
        description = d;
        quantityAvailable = q;
    }

    void display() {
        cout << "Item: " << name << "\nDescription: " << description 
             << "\nAvailable Quantity: " << quantityAvailable << endl;
    }
};

class ItemInUse {
public:
    string name;
    string location;
    int quantityUsed;

    ItemInUse(string n, string l, int q) {
        name = n;
        location = l;
        quantityUsed = q;
    }

    void display() {
        cout << "Item: " << name << "\nLocation: " << location 
             << "\nQuantity In Use: " << quantityUsed << endl;
    }
};

int findItemIndex(vector<InventoryItem> &inventory, string itemName) {
    for(int i = 0; i < inventory.size(); i++) {
        if(inventory[i].name == itemName) {
            return i;
        }
    }
    return -1; 
}

void saveInventory(vector<InventoryItem> &inventory) {
    ofstream fout("inventory.txt");
    for(auto &item : inventory) {
        fout << item.name << "," << item.description << "," << item.quantityAvailable << "\n";
    }
    fout.close();
}

void saveItemsInUse(vector<ItemInUse> &itemsInUse) {
    ofstream fout("items_in_use.txt");
    for(auto &item : itemsInUse) {
        fout << item.name << "," << item.location << "," << item.quantityUsed << "\n";
    }
    fout.close();
}

int main() {
    vector<InventoryItem> inventory = {
        InventoryItem("Syringe", "10ml sterile", 100),
        InventoryItem("Bandage", "5m roll", 50),
        InventoryItem("Surgical Gloves", "size M", 200),
        InventoryItem("Paracetamol Tablets", "500mg 100 tablets", 30),
        InventoryItem("Cotton Balls", "100g pack", 40),
        InventoryItem("Blood Pressure Monitor", "Standard monitor", 10),
        InventoryItem("Stethoscope", "Standard", 15),
        InventoryItem("IV Drip Set", "Standard", 25),
        InventoryItem("Gauze Pads", "10cm x 10cm", 60),
        InventoryItem("Alcohol Swabs", "box of 100", 80),
        InventoryItem("Thermometer", "Digital", 20),
        InventoryItem("Surgical Mask", "Disposable", 500),
        InventoryItem("Oxygen Cylinder", "5L", 5),
        InventoryItem("Wheelchair", "Standard", 8),
        InventoryItem("Ultrasound Gel", "250ml", 30)
    };

    vector<ItemInUse> itemsInUse;

    saveInventory(inventory); 

    int choice;
    do {
        cout << "\n====== Hospital Inventory Management ======\n";
        cout << "1. Display All Inventory Items\n";
        cout << "2. Display Items in Use\n";
        cout << "3. Get (Use) Equipment\n";
        cout << "4. Show Remaining Equipment\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "\n--- Inventory Items ---\n";
                for(auto &item : inventory) {
                    item.display();
                }
                break;

            case 2:
                cout << "\n--- Items in Use ---\n";
                if(itemsInUse.empty()) {
                    cout << "No items currently in use.\n";
                } else {
                    for(auto &item : itemsInUse) {
                        item.display();
                    }
                }
                break;

            case 3: {
                string itemName, location;
                int quantity;
                cout << "Enter the equipment name you want to use: ";
                cin.ignore();
                getline(cin, itemName);
                cout << "Enter the location (e.g., ICU, Pharmacy): ";
                getline(cin, location);
                cout << "Enter quantity to use: ";
                cin >> quantity;

                int index = findItemIndex(inventory, itemName);
                if(index == -1) {
                    cout << "\nSearching for equipment... Not found in inventory department.\n";
                } else if (inventory[index].quantityAvailable < quantity) {
                    cout << "\nInsufficient stock for '" << itemName << "'.\n";
                    cout << "Available quantity: " << inventory[index].quantityAvailable << "\n";
                } else {
                    inventory[index].quantityAvailable -= quantity;
                    itemsInUse.push_back(ItemInUse(itemName, location, quantity));
                    cout << "Item allocated successfully!\n";
                    saveInventory(inventory);
                    saveItemsInUse(itemsInUse);
                }
                break;
            }

            case 4:
                cout << "\n--- Remaining Equipment ---\n";
                for(auto &item : inventory) {
                    cout << "Item: " << item.name << " | Remaining Quantity: " << item.quantityAvailable << endl;
                }
                break;

            case 5:
                cout << "Exiting the program. Thank you!\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while(choice != 5);

    return 0;
}
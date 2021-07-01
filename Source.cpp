#include<iostream>
#include<string>
#include<fstream>
#include<sstream> //use variables to convert int to string
#include<ctime> //use time functions
#include<conio.h> //to use getch()
#include<iomanip> //to use setw

using namespace std;

struct date
{
    int year;
    int month;
    int day;
};

struct item
{
    int id;
    string name;
    float price;
    date expdate;
    int quantity;
    string addedattribute1;
    string addedattribute2;
    string addedattribute3;
};



//concatenate the product id into the filename to create or search a . txt file for each product
string filename(int id)
{
    string name;
    stringstream conv;
    conv << id;
    conv >> name;

    string filename = name + ".txt";
    return filename;
}

//count the number of items in the DB (knowing that each item is displayed on a single line) 
int item_count_inDB()
{
    int number_of_lines = 0;
    string line;
    ifstream ifs("DATABASE.txt");

    while (getline(ifs, line))
        ++number_of_lines;

    ifs.close();

    if (!ifs)
        return number_of_lines;

    return number_of_lines;
}

//nb of lines in a file (will be used to verify if there are added attributes for an item or no)
int item_count_inFile(int id)
{
    int number_of_lines = 0;
    string line;
    ifstream ifs(filename(id));

    while (getline(ifs, line))
        ++number_of_lines;

    ifs.close();

    if (!ifs)
        return number_of_lines;

    return number_of_lines;
}

//verify unique ID
bool IDcheck(int newID)
{
    int existingID;

    ifstream ifs("DATABASE.txt");

    for (int i = 0; i < item_count_inDB(); i++)
    {
        ifs >> existingID;

        if (existingID == newID)
            return false;

    }

    ifs.close();

    if (!ifs)
        return true;

    return true;
}

//initialize an array of exisiting items
void item_initializer(item existingIT[], int size)
{
    //first we initialize the IDs of the items from the DB
    int ID;
    int i = 0;
    ifstream ifs("DATABASE.txt");
    while (ifs >> ID)
    {
        existingIT[i].id = ID;
        i++;
    }
    ifs.close();

    //then we initialize all other attributes from the specified file for each item
    string name;
    float price;
    date expdate;
    int quantity;
    string addedattribute1;
    string addedattribute2;
    string addedattribute3;

    size = item_count_inDB(); //size=i

    for (int j = 0; j < size ; j++)
    {
        ifstream ifs(filename(existingIT[j].id));

        ifs.ignore(100, '\n'); //switching from ifs int to ifs string
        getline(ifs, name);
        existingIT[j].name = name;


        ifs >> price >> expdate.day >> expdate.month >> expdate.year >> quantity;

        existingIT[j].price = price;
        existingIT[j].expdate.day = expdate.day;
        existingIT[j].expdate.month = expdate.month;
        existingIT[j].expdate.year = expdate.year;
        existingIT[j].quantity = quantity;

        ifs.ignore(100, '\n'); //switching from ifs int to ifs string

        if (getline(ifs, addedattribute1))
        {
            existingIT[j].addedattribute1 = addedattribute1;

            if (getline(ifs, addedattribute2))
            {
                existingIT[j].addedattribute2 = addedattribute2;

                if (getline(ifs, addedattribute3))
                    existingIT[j].addedattribute3 = addedattribute3;
            }
        }
        ifs.close();
    }

}

void inputID(int& id)
{
    if (id == 0) //a random ID will be given
    {
        id = rand();
        while (IDcheck(id) == false) //ensure given random id doesnt already exist
        {
            id = rand();
        }
    }

    while (IDcheck(id) == false)
    {
        cout << "The ID you entered already exists, Please try again." << endl;
        cout << "ID: ";
        cin >> id;

        if (id == 0) //a random ID will be given
        {
            id = rand();
            while (IDcheck(id) == false)
            {
                id = rand();
            }
        }
    }

}

void AddExpDate(item& it) //will be used to enter an expiry date for an added product
{
    cout << "Expiry date: " << endl; //beginning of exp date input

    cout << "Day (1-31): ";
    while (!(cin >> it.expdate.day)) //make sure day is a digit
    {
        cout << "The day must be a digit! Please try again\nDay: ";
        cin.clear(); //clear input stream
        cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
    }

    cout << "Month (1-12): ";
    while (!(cin >> it.expdate.month)) //make sure month is a digit
    {
        cout << "The month must be a digit! Please try again\nMonth: ";
        cin.clear(); //clear input stream
        cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
    }

    while (it.expdate.month > 12 || it.expdate.month < 1) //make sure vallid month is entered
    {
        cout << "Month must be between 1 and 12!\nMonth: ";
        cin.clear(); //clear input stream
        cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
        cin >> it.expdate.month;
    }

    cout << "Year: ";
    while (!(cin >> it.expdate.year)) //make sure year is a digit
    {
        cout << "The year must be a digit! Please try again\nYear: ";
        cin.clear(); //clear input stream
        cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
    }

    if (it.expdate.month == 4 || it.expdate.month == 6 || it.expdate.month == 9 || it.expdate.month == 11)
    {
        while (it.expdate.day > 30 || it.expdate.day < 1)
        {
            cout << "The day for this month must be between 1 and 30!\nDay: ";
            cin >> it.expdate.day;
            cin.clear(); //clear input stream
            cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
        }
    }

    if (it.expdate.month == 1 || it.expdate.month == 3 || it.expdate.month == 5 || it.expdate.month == 7 || it.expdate.month == 8 || it.expdate.month == 10 || it.expdate.month == 12)
    {
        while (it.expdate.day > 31 || it.expdate.day < 1)
        {
            cout << "The day for this month must be between 1 and 31!\nDay: ";
            cin >> it.expdate.day;
            cin.clear(); //clear input stream
            cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
        }
    }

    if (it.expdate.month == 2)
    {
        if (it.expdate.year % 4 == 0)
        {
            while (it.expdate.day > 29 || it.expdate.day < 1)
            {
                cout << "The day for this month must be between 1 and 29!\nDay: ";
                cin >> it.expdate.day;
                cin.clear(); //clear input stream
                cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
            }
        }

        else
        {
            while (it.expdate.day > 28 || it.expdate.day < 1)
            {
                cout << "The day for this month must be between 1 and 28!\nDay: ";
                cin >> it.expdate.day;
                cin.clear(); //clear input stream
                cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
            }
        }
    }
}

//checks if product has expired
bool hasExpired(date expdate)
{
    time_t now = time(0);
    tm* ltm = localtime(&now);

    if (expdate.year > 1900 + ltm->tm_year)
        return false;

    if (expdate.year == 1900 + ltm->tm_year && expdate.month > 1 + ltm->tm_mon)
        return false;

    if (expdate.year == 1900 + ltm->tm_year && expdate.month == 1 + ltm->tm_mon && expdate.day > ltm->tm_mday)
        return false;

    return true;
}

void AddAttribute1(item& it) //adds attribute to a file
{
    string attributename;

    cout << "Enter attribute name: ";
    getline(cin >> ws, attributename);

    cout << attributename << ": ";
    getline(cin >> ws, it.addedattribute1);

    it.addedattribute1 = attributename + ": " + it.addedattribute1;

    ofstream newofs(filename(it.id), ios::app);
    newofs << it.addedattribute1 << endl;
    newofs.close();
}

void AddAttribute2(item& it)
{
    string attributename;

    cout << "Enter attribute name: ";
    getline(cin >> ws, attributename);

    cout << attributename << ": ";
    getline(cin >> ws, it.addedattribute2);

    it.addedattribute2 = attributename + ": " + it.addedattribute2;

    ofstream newofs(filename(it.id), ios::app);
    newofs << it.addedattribute2 << endl;
    newofs.close();
}

void AddAttribute3(item& it)
{
    string attributename;

    cout << "Enter attribute name: ";
    getline(cin >> ws, attributename);

    cout << attributename << ": ";
    getline(cin >> ws, it.addedattribute3);

    it.addedattribute3 = attributename + ": " + it.addedattribute3;

    ofstream newofs(filename(it.id), ios::app);
    newofs << it.addedattribute3 << endl;
    newofs.close();
}


void AddItem(item it)
{
    cout << "Enter details about the product:" << endl;

    cout << "Enter and ID or press 0 for a random ID: "; //beginning of id input algorithm
    while (!(cin >> it.id)) //make sure the ID is a digit
    {
        cout << "The ID must be a digit! Please try again\nID: ";
        cin.clear(); //clear input stream
        cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
    }

    inputID(it.id);
    cout << "ID: " << it.id << endl;


    //end of id input algorithm

    cout << "Product Name: ";
    getline(cin >> ws, it.name); //allow whitespace input in a string


    cout << "Price ($): ";
    while (!(cin >> it.price)) //make sure the price is a digit
    {
        cout << "The price must be a digit! Please try again\nPrice: ";
        cin.clear(); //clear input stream
        cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
    }

    AddExpDate(it);

    string expchoice = "n";
    while (hasExpired(it.expdate) == true)
    {
        cout << "The expiry date you entered has passed! Do you want to add it anyway? (y/n): ";
        cin >> expchoice;
        cin.clear(); //clear input stream
        cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'

        while (expchoice != "n" && expchoice != "y" && expchoice != "Y" && expchoice != "N")
        {
            cout << "Invalid Choice. Try again\n(y/n): ";
            cin >> expchoice;
            cin.clear(); //clear input stream
            cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
        }

        if (expchoice == "n" || expchoice == "N")
            AddExpDate(it);
        else
            break;
    }
    //end of exp date input

    cout << "Quantity: ";
    while (!(cin >> it.quantity)) //make sure the qty is a digit
    {
        cout << "The quantity must be a digit! Please try again\nQuantity: ";
        cin.clear(); //clear input stream
        cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
    }

    //output item details into its own file
    ofstream ofs(filename(it.id), ios::app);
    ofs << it.id << endl << it.name << endl << it.price << endl << it.expdate.day << " " << it.expdate.month << " " << it.expdate.year << endl << it.quantity << endl;
    ofs.close();

    //Add new attribute
    string attributechoice;
    cout << "Do you want to add another attribute? You can add up to 3 new attributes (y/n): ";
    cin >> attributechoice;

    while (attributechoice != "n" && attributechoice != "y" && attributechoice != "Y" && attributechoice != "N")
    {
        cout << "Invalid Choice. Try again\n(y/n): ";
        cin >> attributechoice;
        cin.clear(); //clear input stream
        cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
    }

    if (attributechoice == "y" || attributechoice == "Y")
    {
        AddAttribute1(it);

        cout << "Do you want to add another attribute? You can add up to 2 more attributes (y/n): ";
        cin >> attributechoice;

        while (attributechoice != "n" && attributechoice != "y" && attributechoice != "Y" && attributechoice != "N")
        {
            cout << "Invalid Choice. Try again\n(y/n): ";
            cin >> attributechoice;
            cin.clear(); //clear input stream
            cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
        }

        if (attributechoice == "y" || attributechoice == "Y")
        {
            AddAttribute2(it);

            cout << "Do you want to add another attribute? You can add one more attributes (y/n): ";
            cin >> attributechoice;

            while (attributechoice != "n" && attributechoice != "y" && attributechoice != "Y" && attributechoice != "N")
            {
                cout << "Invalid Choice. Try again\n(y/n): ";
                cin >> attributechoice;
                cin.clear(); //clear input stream
                cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
            }

            if (attributechoice == "y" || attributechoice == "Y")
            {
                AddAttribute3(it);
            }
        }
    }

  

    ifstream data2("DATABASE.txt"); //if database does not exist
    if (!data2)
    {
        ofstream firsttime("DATABASE.txt");
        firsttime << it.id;
        firsttime.close();
    }
    else
    {
        int idl, i = 0;  //sort ids by increasing order in DB during input

        int DBsize = item_count_inDB();
        int* ITemsid = new int[DBsize + 1];
        while (data2 >> idl)
        {

            ITemsid[i] = idl;

            i++;


        }

        data2.close();

        for (i = DBsize - 1; i >= 0; i--)
        {
            if (ITemsid[i] > it.id) //sort during input

            {
                if (i == 0)
                {
                    ITemsid[i + 1] = ITemsid[i];
                    ITemsid[i] = it.id;
                    break;
                }
                else
                    ITemsid[i + 1] = ITemsid[i];

            }
            else
            {

                ITemsid[i + 1] = it.id;
                break;
            }

        }
        ofstream data3("DATABASE.txt");
        for (i = 0; i < DBsize + 1; i++)
            data3 << ITemsid[i] << endl;

        data3.close();

    }
    

}


void DisplayItem(item it) //Display details of an item
{
    cout << "ID: " << it.id << endl << "Name: " << it.name << endl << "Price: " << it.price << " $" << endl
        << "Expiry Date: " << it.expdate.day << "/" << it.expdate.month << "/" << it.expdate.year << endl
        << "Quantity: " << it.quantity << endl;

    ifstream ifs(filename(it.id)); //avoid displaying empty lines if attribute does not exist
    if (item_count_inFile(it.id) > 5)
    {
        cout << it.addedattribute1 << endl;

        if (item_count_inFile(it.id) > 6)
        {
            cout << it.addedattribute2 << endl;

            if (item_count_inFile(it.id) > 7)
                cout << it.addedattribute3 << endl;
        }
    }
    ifs.close();

    cout << "--------------" << endl;
}

void SearchItem(item existingIT[], int existingsize)
{
    int choice;

    cout << "1- ID   2-Name   3-Price   4-Expiry Date   5-Quantity   6-Other   7-All Items   8-Cancel" << endl;
    cout << "Search by: ";

    while (!(cin >> choice))
    {
        cout << "Invalid choice. Try again" << endl;
        cout << "Search by:" << endl;
        cout << "1- ID   2-Name   3-Price   4-Expiry Date  5-Quantity   6-Other   7-All Items   8-Cancel" << endl;
        cin.clear(); //clear input stream
        cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
    }

    while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7 && choice != 8)
    {
        cout << "Invalid choice. Try again" << endl;
        cout << "Search by:" << endl;
        cout << "1- ID   2-Name   3-Price   4-Expiry Date  5-Quantity   6-Other   7-All Items   8-Cancel" << endl;
    }

    switch (choice)
    {

    case 1:
    {
        int id;

        cout << "Enter ID: ";
        while (!(cin >> id))
        {
            cout << "ID: " << endl;
            cin.clear(); //clear input stream
            cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
        }

        cout << "--------------Results--------------" << endl;
        for (int i = 0; i < existingsize; i++)
        {
            if (id == existingIT[i].id)
                DisplayItem(existingIT[i]);
        }
        break;
    }

    case 2:
    {
        string name;
        cout << "Enter Name or Subname: ";
        getline(cin >> ws, name);

        cout << "--------------Results--------------" << endl;
        for (int i = 0; i < existingsize; i++)
        {
            if (existingIT[i].name.find(name, 0) != string::npos) //search using substrings (didn't work with s1.substr())
                DisplayItem(existingIT[i]);
        }
        break;
    }

    case 3:
    {
        int choice3;
        cout << "1-Price range   2-Specific price" << endl << "Search by: ";

        while (!(cin >> choice3))
        {
            cout << "Invalid choice. Try again" << endl;
            cout << "1-Price range   2-Specific price" << endl << "Search by: ";
            cin.clear(); //clear input stream
            cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
        }

        while (choice3 != 1 && choice3 != 2)
        {
            cout << "Invalid choice. Try again" << endl;
            cout << "1-Price range   2-Specific price" << endl << "Search by: ";
            cin >> choice3;
        }

        if (choice3 == 2)
        {
            float price;
            cout << "Enter Price: ";
            while (!(cin >> price))
            {
                cout << "price: ";
                cin.clear(); //clear input stream
                cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
            }

            cout << "--------------Results--------------" << endl;
            for (int i = 0; i < existingsize; i++)
            {
                if (price == existingIT[i].price)
                    DisplayItem(existingIT[i]);
            }
            break;
        }

        if (choice3 == 1)
        {
            int lowprice, highprice;

            cout << "Enter lowest price (Press 0 to discard lowest price): ";
            while (!(cin >> lowprice))
            {
                cout << "Lowest price (Press 0 to discard lowest price): ";
                cin.clear(); //clear input stream
                cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
            }

            cout << "Enter highest price (Press 0 to discard highest price): ";
            while (!(cin >> highprice))
            {
                cout << "Highest price (Press 0 to discard highest price): " << endl;
                cin.clear(); //clear input stream
                cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
            }

            cout << "--------------Results--------------" << endl;
            for (int i = 0; i < existingsize; i++)
            {
                if ((existingIT[i].price >= lowprice || lowprice == 0) && (existingIT[i].price <= highprice || highprice == 0))
                    DisplayItem(existingIT[i]);
            }
            break;
        }

    }

    case 4:
    {
        time_t now = time(0);
        tm* ltm = localtime(&now);

        int choice4;
        cout << "1-Expired items   2-Non-expired items   3-Specific Expiry Date" << endl << "Search by: ";

        while (!(cin >> choice4))
        {
            cout << "Invalid choice. Try again" << endl;
            cout << "1-Expired items   2-Non-expired items   3-Specific Expiry Date" << endl;
            cin.clear(); //clear input stream
            cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
        }

        while (choice4 != 1 && choice4 != 2 && choice4 != 3)
        {
            cout << "Invalid choice. Try again" << endl;
            cout << "1-Expired items   2-Non-expired items   3-Specific Expiry Date" << endl;
            cin >> choice4;
        }

        if (choice4 == 1)
        {
            cout << "--------------Results--------------" << endl;
            for (int i = 0; i < existingsize; i++)
            {
                if (hasExpired(existingIT[i].expdate) == true)
                    DisplayItem(existingIT[i]);
            }

        }

        if (choice4 == 2)
        {
            cout << "--------------Results--------------" << endl;
            for (int i = 0; i < existingsize; i++)
            {
                if (hasExpired(existingIT[i].expdate) == false)
                    DisplayItem(existingIT[i]);
            }
        }

        if (choice4 == 3)
        {
            date expdate;

            cout << "Enter Expiry Date:" << endl;
            cout << "Day (Press 0 to discard day): ";
            while (!(cin >> expdate.day))
            {
                cout << "Day (Press 0 to discard day): ";
                cin.clear(); //clear input stream
                cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
            }

            cout << "Month (Press 0 to discard month): ";
            while (!(cin >> expdate.month))
            {
                cout << "Month (Press 0 to discard month): ";
                cin.clear(); //clear input stream
                cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
            }

            cout << "Year (Press 0 to discard year): ";
            while (!(cin >> expdate.year))
            {
                cout << "Year (Press 0 to discard year): ";
                cin.clear(); //clear input stream
                cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
            }

            cout << "--------------Results--------------" << endl;
            for (int i = 0; i < existingsize; i++)
            {
                if (expdate.day == existingIT[i].expdate.day || expdate.day == 0)
                {
                    if (expdate.month == existingIT[i].expdate.month || expdate.month == 0)
                    {
                        if (expdate.year == existingIT[i].expdate.year || expdate.year == 0)
                            DisplayItem(existingIT[i]);
                    }
                }
            }
            break;
        }

        break;
    }

    case 5:
    {

        int choice5;
        cout << "1-Quantity Range   2-Specific Quantity" << endl << "Search by: ";

        while (!(cin >> choice5))
        {
            cout << "Invalid choice. Try again" << endl;
            cout << "1-Quantity Range   2-Specific Quantity" << endl;
            cout << "Search by: ";
            cin.clear(); //clear input stream
            cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
        }

        if (choice5 == 2)
        {
            int quantity;
            while (!(cin >> quantity))
            {
                cout << "Quantity: ";
                cin.clear(); //clear input stream
                cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
            }

            cout << "--------------Results--------------" << endl;
            for (int i = 0; i < existingsize; i++)
            {
                if (quantity == existingIT[i].quantity)
                    DisplayItem(existingIT[i]);
            }

            break;
        }

        if (choice5 == 1)
        {
            int lowquantity, highquantity;

            cout << "Enter lowest Quantity (Press 0 to discard lowest price): ";
            while (!(cin >> lowquantity))
            {
                cout << "Low Quantity: ";
                cin.clear(); //clear input stream
                cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
            }

            cout << "Enter highest Quantity(Press 0 to discard highest price): ";
            while (!(cin >> highquantity))
            {
                cout << "High Quantity: ";
                cin.clear(); //clear input stream
                cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
            }

            cout << "--------------Results--------------" << endl;
            for (int i = 0; i < existingsize; i++)
            {
                if ((existingIT[i].quantity >= lowquantity || lowquantity == 0) && (existingIT[i].quantity <= highquantity || highquantity == 0))
                    DisplayItem(existingIT[i]);
            }
            break;
        }
    }

    case 6:
    {
        string attribute;

        cout << "Search for: ";
        getline(cin >> ws, attribute);

        cout << "--------------Results--------------" << endl;

        for (int i = 0; i < existingsize; i++)
        {
            //search using substrings (didn't work with s1.substr())
            if (existingIT[i].addedattribute1.find(attribute, 0) != string::npos || existingIT[i].addedattribute2.find(attribute, 0) != string::npos || existingIT[i].addedattribute3.find(attribute, 0) != string::npos)
                DisplayItem(existingIT[i]);
        }
        break;
    }

    case 7:
    {
        cout << "--------------Results--------------" << endl;
        for (int i = 0; i < existingsize; i++)
            DisplayItem(existingIT[i]);

        break;
    }

    case 8:
    {
        return;
    }

    }
}

void EditItem(item existingIT[], int existingsize)
{
    int id;

    cout << "Enter the ID of the item you want to edit (0 to discard): ";

    while (!(cin >> id))
    {
        cout << "Enter a valid ID: " << endl;
        cin.clear(); //clear input stream
        cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
    }

    if (id == 0)
        return;

    for (int i = 0; i < existingsize; i++)
    {
        if (id == existingIT[i].id)
        {
            cout << "Item found" << endl;
            int choice;
            cout << "Select what to edit:\n1- ID   2-Name   3-Price   4-Expiry Date   5-Quantity   6-Other   7-Cancel" << endl;
            while (!(cin >> choice))
            {
                cout << "Invalid choice. Try again" << endl;
                cout << "Edit:" << endl;
                cout << "1- ID   2-Name   3-Price   4-Expiry Date  5-Quantity   6-Other   7-Cancel" << endl;
                cin.clear(); //clear input stream
                cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
            }

            while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7)
            {
                cout << "Invalid choice. Try again" << endl;
                cout << "Edit:" << endl;
                cout << "1- ID   2-Name   3-Price   4-Expiry Date  5-Quantity   6-Other   7-Cancel" << endl;
                cin >> choice;
            }

            switch (choice)
            {

            case 1:
            {
                cout << "Old ID was (" << existingIT[i].id << ")" << endl;

                int newid;

                cout << "New ID: ";
                while (!(cin >> newid))
                {
                    cout << "ID must be a number\nnew ID: ";
                    cin.clear(); //clear input stream
                    cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
                }

                inputID(newid);

                int newsize = item_count_inDB();

                remove(filename(existingIT[i].id).c_str());
                existingIT[i].id = newid;



                for (int l = 0; l < newsize - 1; l++)
                {
                    for (int g = l + 1; g < newsize; g++)
                    {
                        if (existingIT[g].id < existingIT[l].id)
                        {
                            item min;
                            min = existingIT[g];
                            existingIT[g] = existingIT[l];
                            existingIT[l] = min;
                        }
                    }
                }

                ofstream OFS("DATABASE.txt");  //sort ids by increasing order in DB during edit
                for (int j = 0; j < newsize; j++)
                {
                    OFS << existingIT[j].id << endl;
                }
                OFS.close();

                break;
            }

            case 2:
            {
                cout << "Old name was (" << existingIT[i].name << ")" << endl;

                string newname;
                cout << "New name: ";
                getline(cin >> ws, newname);

                existingIT[i].name = newname;

                break;
            }

            case 3:
            {
                cout << "Old price was (" << existingIT[i].price << ")" << endl;

                float newprice;
                cout << "New price: ";
                while (!(cin >> newprice))
                {
                    cout << "Price must be a number.\nNew price: ";
                    cin.clear(); //clear input stream
                    cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
                }

                existingIT[i].price = newprice;

                break;
            }

            case 4:
            {
                cout << "Old Expiry date was (" << existingIT[i].expdate.day << "/" << existingIT[i].expdate.month << "/" << existingIT[i].expdate.year << ")" << endl;

                AddExpDate(existingIT[i]);

                string expchoice = "n";
                while (hasExpired(existingIT[i].expdate) == true)
                {
                    cout << "The expiry date you entered has passed! Do you want to add it anyway? (y/n): ";
                    cin >> expchoice;
                    cin.clear(); //clear input stream
                    cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'

                    while (expchoice != "n" && expchoice != "y" && expchoice != "Y" && expchoice != "N")
                    {
                        cout << "Invalid Choice. Try again\n(y/n): ";
                        cin >> expchoice;
                        cin.clear(); //clear input stream
                        cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
                    }

                    if (expchoice == "n" || expchoice == "N")
                        AddExpDate(existingIT[i]);
                    else
                        break;
                }

                break;
            }

            case 5:
            {
                cout << "Old quantity was (" << existingIT[i].quantity << ")" << endl;

                int newquantity;
                cout << "New quantity: ";
                while (!(cin >> newquantity))
                {
                    cout << "Quantity must be a number.\nNew quantity: ";
                    cin.clear(); //clear input stream
                    cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
                }

                existingIT[i].quantity = newquantity;

                break;
            }


            case 6:
            {
                if (item_count_inFile(existingIT[i].id) > 5)
                {
                    string attribute;

                    cout << "Enter attribute to edit: ";
                    getline(cin >> ws, attribute);

                    //search using substrings (didn't work with s1.substr())
                    if (existingIT[i].addedattribute1.find(attribute, 0) != string::npos)
                    {
                        cout << "Old attribute was (" << existingIT[i].addedattribute1 << ")" << endl;

                        cout << "New attribute: ";
                        AddAttribute1(existingIT[i]);

                    }

                    if (existingIT[i].addedattribute2.find(attribute, 0) != string::npos)
                    {
                        cout << "Old attribute was (" << existingIT[i].addedattribute2 << ")" << endl;

                        cout << "New attribute: ";
                        AddAttribute2(existingIT[i]);

                    }

                    if (existingIT[i].addedattribute3.find(attribute, 0) != string::npos)
                    {
                        cout << "Old attribute was (" << existingIT[i].addedattribute3 << ")" << endl;

                        cout << "New attribute: " << endl;
                        AddAttribute3(existingIT[i]);

                    }
                }
                else
                    cout << "No attribute to edit" << endl;

                break;
            }

            case 7:
            {
                return;
            }

            }

            ofstream ofs(filename(existingIT[i].id));
            ofs << existingIT[i].id << endl << existingIT[i].name << endl << existingIT[i].price << endl << existingIT[i].expdate.day << " " << existingIT[i].expdate.month << " " << existingIT[i].expdate.year << endl
                << existingIT[i].quantity << endl;

            if (item_count_inFile(existingIT[i].id) > 5)
                ofs << existingIT[i].addedattribute1 << endl;

            if (item_count_inFile(existingIT[i].id) > 6)
                ofs << existingIT[i].addedattribute2 << endl;

            if (item_count_inFile(existingIT[i].id) > 7)
                ofs << existingIT[i].addedattribute3;

            ofs.close();
            return;

        }
    }

    cout << "Could not find ID. Try again" << endl;
    EditItem(existingIT, existingsize); //recursive loop in case of failure
}

int RemoveItem(item existingIT[], int size)
{
    int id;
    bool wasremoved = false;

    cout << "Enter the ID of the item you want to remove (0 to cancel): ";

    while (!(cin >> id))
    {
        cout << "Enter a valid id: ";
        cin.clear(); //clear input stream
        cin.ignore(100, '\n'); //discard previous 100 inputs until new line '\n'
    }

    if (id == 0)
        return 0;

    while (IDcheck(id) == true)
    {
        cout << "No item was removed, the ID you enter does not exist." << endl;

        return 0;

    }

    for (int i = 0; i < size; i++)
    {
        if (id == existingIT[i].id)
        {

            wasremoved = true;

            size--;
            remove(filename(existingIT[i].id).c_str());
        }

        if (wasremoved == true && id != existingIT[size].id) //avoid going out of bounds if the removed item is the last item int the array
            existingIT[i] = existingIT[i + 1];
    }

    if (wasremoved == true)
    {
        ofstream OFS("DATABASE.txt");
        for (int j = 0; j < size; j++)
        {
            OFS << existingIT[j].id << endl;
        }
        OFS.close();
    }

    return 1;
}

string passwordsetup()
{
    string fromfile, s;

    ifstream pasifs("PASSWORD.txt");
    if (pasifs)
    {

            pasifs >> fromfile;
            s = fromfile;

        pasifs.close();

        return s;
    }

    else
    {
        cout << "\nEnter a new password for your store: ";

        char pswrd[50];
        int i = 0;
        while ((pswrd[i] = _getch()) != '\r') //prints * while user inputs password, \r when enter key is pressed
        {
            cout << "*";
            i++;
        }

        string s = "";                           //converts array of char to string
        for (int i = 0; pswrd[i] != '\r'; i++)
        {
            s = s + pswrd[i];
        }

        cout << "\nRe-enter password: ";
        char re[20];

        int j = 0;
        while ((re[j] = _getch()) != '\r') //prints * while user inputs password, \r when enter key is pressed
        {
            cout << "*";
            j++;
        }

        string ree = "";                           //converts array of char to string
        for (int k = 0; re[k] != '\r'; k++)
        {
            ree = ree + re[k];
        }

        if (ree != s)
        {
            cout << "\nThe passwords don't match, Try again" << endl;
            passwordsetup();
        }

        ofstream pasofs("PASSWORD.txt");

        pasofs << s;
        pasofs.close();



        cout << "\nPassword recorded successfully" << endl;
        return s;
    }
}



int login(string& truepswrd, int& attempts)
{
    char enteredpswrd[20];
    cout << "Enter Password: ";

    int i = 0;
    while ((enteredpswrd[i] = _getch()) != '\r') //prints * while user inputs password, \r when enter key is pressed
    {
        cout << "*";
        i++;
    }

    string s = "";                           //converts array of char to string
    for (int i = 0; enteredpswrd[i] != '\r'; i++)
    {
        s = s + enteredpswrd[i];
    }

    if (s == truepswrd)
        return attempts;

    else
    {
        attempts++;
        if (attempts == 3)
            return attempts;
        else
        {
            cout << "\nThe password you entered is incorrect. Try again" << endl;
            login(truepswrd, attempts);
        }
    }
    return attempts;
}

void editpassword()
{
    string pass;
    int attempts = 0;

    pass = passwordsetup();

    cout << "Old password, ";
    login(pass, attempts);

    if (attempts != 3)
    {
        remove("PASSWORD.txt");
        passwordsetup();
    }

    else
    {
        cout << "\n\nPassword incorrectly typed 3 times. Password editing will terminate" << endl;
        cout << setw(70) << "--------------------" << endl;
        cout << setw(69) << "Session terminated" << endl;
        cout << setw(70) << "--------------------" << endl;
    }


}

int  main()

{
    cout << setw(70) << "--------------------" << endl;
    cout << setw(70) << "Welcome to our store" << endl;
    cout << setw(70) << "--------------------" << endl;


    int loginattempts = 0;
    string password = passwordsetup(); //if password does not exist, setup passw otherwise initialize passw

    char alter;
    bool firstalter = true;

    cout << "Do you want to navigate our software?(y/n)";

    cin >> alter;
    while (alter != 'y' && alter != 'Y' && alter != 'n' && alter != 'N')
    {
        cout << "Invalid choice. Do you want to navigate our software?(y/n)" << endl;
        cin >> alter;
    }

    while (alter == 'y' || alter == 'Y')
    {
        if (firstalter == true) //only request password for first alter
        {
            if (login(password, loginattempts) == 3)
            {
                cout << "\n\nPassword incorrectly typed 3 times." << endl;
                cout << setw(70) << "--------------------" << endl;
                cout << setw(69) << "Session terminated" << endl;
                cout << setw(70) << "--------------------" << endl;
                return 0;
            }
            cout << endl;
            cout << setw(70) << "--------------------" << endl;
            cout << setw(67) << "ACCESS GRANTED" << endl;
            cout << setw(70) << "--------------------" << endl;
        }

        firstalter = false;


        int size = item_count_inDB();
        item* existingIT = new item[size];


        item_initializer(existingIT, size);

        cout << setw(70) << "--------------------" << endl;
        cout << setw(62) << "1-Add  items" << endl;
        cout << setw(70) << "2-Search for an item" << endl;
        cout << setw(66) << "3-Remove an item" << endl;
        cout << setw(73) << "4-Edit an existing item" << endl;
        cout << setw(67) << "5-Change password" << endl;
        cout << setw(61) << "0-Exit Menu" << endl;
        cout << setw(70) << "--------------------" << endl;

        int choice;
        cout << "Please input your choice from the above menu: ";
        while (!(cin >> choice))
        {
            cout << "Please input your choice from the above menu: ";
            cin.clear();
            cin.ignore(100, '\n');
        }

        while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 0)
        {
            cout << "Invalid choice. Please input your choice from the above menu: ";
            cin >> choice;
        }

        switch (choice)
        {
            int operation;

        case 1:
        {
            cout << "How many items do you want to add? ";
            while (!(cin >> operation))
            {
                cout << "Enter a valid number: ";
                cin.clear();
                cin.ignore(100, '\n');
            }

            item it;
            for (int i = 0; i < operation; i++)
            {
                AddItem(it);
            }

            break;
        }

        case 2:
        {
            cout << "How many searches do you want to make? ";
            while (!(cin >> operation))
            {
                cout << "Enter a valid number: ";
                cin.clear();
                cin.ignore(100, '\n');
            }

            for (int i = 0; i < operation; i++)
                SearchItem(existingIT, size);

            break;
        }

        case 3:
        {
            cout << "How many items do you want to remove? ";
            while (!(cin >> operation))
            {
                cout << "Enter a valid number: ";
                cin.clear();
                cin.ignore(100, '\n');
            }

            for (int i = 0; i < operation; i++)
                RemoveItem(existingIT, size);

            break;
        }

        case 4:
        {
            cout << "How many items do you want to edit? ";
            while (!(cin >> operation))
            {
                cout << "Enter a valid number: ";
                cin.clear();
                cin.ignore(100, '\n');
            }

            for (int i = 0; i < operation; i++)
                EditItem(existingIT, size);

            break;
        }

        case 5:
        {
            editpassword();
            break;
        }

        case 0:
        {
            break;
        }

        }

        cout << "\nDo you want to alter the software again? (y/n): ";
        cin >> alter;
        while (alter != 'y' && alter != 'Y' && alter != 'n' && alter != 'N')
        {
            cout << "Invalid input. Do you want to alter the software again? (y/n): ";
            cin >> alter;
        }

    }

    cout << setw(70) << "--------------------" << endl;
    cout << setw(69) << "Session terminated" << endl;
    cout << setw(70) << "--------------------" << endl;
    return 0;

}
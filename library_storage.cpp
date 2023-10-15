#include <iostream>
#include <fstream>
#include <string>
using namespace std;
const int Size = 30;
struct InfoOrigin
{
    char type[Size]{};
    char name[Size]{};
    char author[Size]{};
    char genre[Size]{};
    int year;
};


void modifyItemsInStorage(const int& size, InfoOrigin* arr) {
    fstream file("data.txt", ios_base::out);
    if (!file.is_open()) {
        cout << "Erorr" << endl;
    }
    else {
        for (size_t i = 0; i < size; i++)
        {
            file.write((char*)&arr[i], sizeof(InfoOrigin));
        }
    }
    file.close();
}

char* toLowerCase(char* line) {
    char* newLine = new char[strlen(line) + 1];
    for (size_t i = 0; i < strlen(line); i++)
    {
        newLine[i] = tolower(line[i]);
    }
    newLine[strlen(line)] = '\0';
    return newLine;
}
//void printOrigin(InfoOrigin item, string text)
//{
//    cout << "\n\n================== " << text << " ====================" << endl;
//    cout << "\t\t Name      :: " << item.name << endl;
//    cout << "\t\t Author    :: " << item.author << endl;
//    cout << "\t\t Type      :: " << item.type << endl;
//    cout << "\t\t Genre     :: " << item.genre << endl;
//    cout << "\t\t Year      :: " << item.year << endl;
//}

string putSpace(int amount) {
    string space = "";
    for (size_t i = 0; i < amount; i++)
    {
        space += " ";
    }
    return space;
}

void printOrigin(InfoOrigin item, string text)
{
    int textSpace = 3 - (int)text.length();
    int nameSpace = 30 - (int)strlen(item.name);
    int authorSpace = 25 - (int)strlen(item.author);
    int typeSpace = 20 - (int)strlen(item.type);
    int genreSpace = 20 - (int)strlen(item.genre);
    cout << text << ")" + putSpace(textSpace) << item.name + putSpace(nameSpace) << item.author + putSpace(authorSpace);
    cout << item.type + putSpace(typeSpace) << item.genre + putSpace(genreSpace) << item.year << endl;
}

void editOrigin(InfoOrigin item)
{
    cout << "\t Name      :: "; cin.getline(item.name, Size);
    cout << "\t Author    :: "; cin.getline(item.author, Size);
    cout << "\t Type      :: "; cin.getline(item.type, Size);
    cout << "\t Genre     :: "; cin.getline(item.genre, Size);
    cout << "\t Year      :: "; cin >> item.year;
}

void printOrigins(InfoOrigin* library, int size)
{

    cout <<endl<< "Count" << "\t\tName" << "\t\t\tAuthor" << "\t\t\tType" << "\t\t   Genre" << "\t   Year" << endl << endl;
    for (size_t i = 0; i < size; i++)
    {
        printOrigin(library[i], to_string(i + 1));
    }
    cout << endl;
}

void addLastItemInStorage(InfoOrigin newItem) {
    ofstream file;
    file.open("data.txt", ios_base::app);
    if (!file.is_open()) { cout << "File not found" << endl; }
    else {
        file.write((char*)&newItem, sizeof(InfoOrigin));
    }
    file.close();
}


void addNewItem(InfoOrigin* &library, int& size, InfoOrigin newItem)
{
    InfoOrigin* tmp = new InfoOrigin[size + 1];
    for (size_t i = 0; i < size; i++)
    {
        tmp[i] = library[i];
    }
    tmp[size] = newItem;
    size++;
    delete[] library;
    library = tmp;
    addLastItemInStorage(newItem);
}


int searchByName(InfoOrigin* library, const int &size,  char* name)
{
    for (int i = 0; i < size; i++) {
        if (strcmp(toLowerCase(library[i].name), toLowerCase(name)) == 0) {
            return i;
        }
    }

    return -1;
}
int searchByAuthor(InfoOrigin* library, const int &size, char* author)
{
    for (int i = 0; i < size; i++) {
        if (strcmp(toLowerCase(library[i].author), toLowerCase(author)) == 0) {
            return i;
        }
    }

    return -1;
}

void sortByName(InfoOrigin* library, const int &size)
{
    for (size_t i = 0; i < size - 1; i++)
    {
        for (size_t j = 0; j < size - 1; j++) {
            if (strcmp(toLowerCase(library[j].name), toLowerCase(library[j + 1].name)) > 0) {
                swap(library[j], library[j + 1]);
            }
        }
    }
    modifyItemsInStorage(size, library);
}

void sortByType(InfoOrigin* library, const int& size)
{
    for (size_t i = 0; i < size - 1; i++)
    {
        for (size_t j = 0; j < size - 1; j++) {
            if (strcmp(toLowerCase(library[j].type), toLowerCase(library[j + 1].type)) > 0) {
                swap(library[j], library[j + 1]);
            }
        }
    }
    modifyItemsInStorage(size, library);
}

void delItemByIndex(InfoOrigin* &library, int& size, int index)
{
    if (index == -1) {
        cout << "Not Found" << endl;
        return;
    }
    InfoOrigin* tmp = new InfoOrigin[size--];
    for (size_t i = 0; i < size; i++)
    {
        if (i < index) {
            tmp[i] = library[i];
        }
        else {
            tmp[i] = library[i + 1];
        }
    }
    delete[] library;
    library = tmp;
    modifyItemsInStorage(size, library);
}
int getStorageSize() {
    InfoOrigin tmp;
    int size = 0;
    fstream file("data.txt", ios_base::in);
    if (!file.is_open()) {
        cout << "Erorr" << endl;
    }
    else {
        while (file.read((char*)&tmp, sizeof(InfoOrigin))) size++;
    }
    file.close();
    return size;
}



InfoOrigin* readItemsFromStorage(string fname, const int &size) {
    InfoOrigin* tmp = new InfoOrigin[size]{};
    fstream file(fname, ios_base::in);
    if (!file.is_open()) {
        cout << "Erorr" << endl;
    }
    else {
        for (size_t i = 0; i < size; i++)
        {
            file.read((char*)&tmp[i], sizeof(InfoOrigin));
        }      
    }
    file.close();
    return tmp;
}

void delNewspapersByYear(InfoOrigin* &library, int& size, int year)
{
    for (int i = 0; i < size; i++) {
        if (strcmp(toLowerCase(library[i].type), toLowerCase((char*)"Newspaper")) == 0 && library[i].year == year) {
            cout << "found" << endl;
            delItemByIndex(library, size, i);
            size--;
        }
    }
}
int selectionSize;
InfoOrigin* genreSelection(InfoOrigin* &library, const int& size, char* genre) {
    selectionSize = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(toLowerCase(library[i].type), toLowerCase((char*)"Book")) == 0 && strcmp(toLowerCase(library[i].genre), toLowerCase(genre)) == 0) {
            selectionSize++;
        }
    }
    InfoOrigin* tmp = new InfoOrigin[selectionSize];
    int j = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(toLowerCase(library[i].type), toLowerCase((char*)"Book")) == 0 && strcmp(toLowerCase(library[i].genre), toLowerCase(genre)) == 0) {
            tmp[j] = library[i];
            j++;
        }
    }
    cout << endl << "Book selection by genre: " << genre;
    return tmp;
}
InfoOrigin* authorSelection(InfoOrigin* &library, const int& size, char* author) {
    selectionSize = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(toLowerCase(library[i].type), toLowerCase((char*)"Book")) == 0 && strcmp(toLowerCase(library[i].author), toLowerCase(author)) == 0) {
            selectionSize++;
        }
    }
    InfoOrigin* tmp = new InfoOrigin[selectionSize];
    int j = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(toLowerCase(library[i].type), toLowerCase((char*)"Book")) == 0 && strcmp(toLowerCase(library[i].author), toLowerCase(author)) == 0) {
            tmp[j] = library[i];
            j++;
        }
    }
    cout << endl << "Book selection by author: " << author;
    return tmp;
}
InfoOrigin* yearSelection(InfoOrigin* &library, const int& size, int year) {
    selectionSize = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(toLowerCase(library[i].type), toLowerCase((char*)"Magazine")) == 0 && library[i].year == year) {
            selectionSize++;
        }
    }
    InfoOrigin* tmp = new InfoOrigin[selectionSize];
    int j = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(toLowerCase(library[i].type), toLowerCase((char*)"Magazine")) == 0 && library[i].year == year) {
            tmp[j] = library[i];
            j++;
        }
    }
    cout << endl << "Magazine selection by year: " << year;
    return tmp;
}
int amountOfBooksByGenre(InfoOrigin*& library, const int& size, char* genre) {
    int amount = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(toLowerCase(library[i].type), toLowerCase((char*)"Book")) == 0 && strcmp(toLowerCase(library[i].genre), toLowerCase(genre)) == 0) {
            amount++;
        }
    }
    return amount;
}




int main()
{   
    int size = getStorageSize();
    InfoOrigin* library = readItemsFromStorage("data.txt", size);
    printOrigins(library, size);
    //addNewItem(library, size, { "Newspaper", "The Daily Telegraph", "Various", "News", 1855 });
    char* name = (char*)"The Daily Telegraph";
    int index = searchByName(library, size, name);
    if (index != -1) {
        delItemByIndex(library, size, index);
    }
    else cout << name << " -- Not found" << endl;
    //delNewspapersByYear(library, size, 1877);
    sortByName(library, size);
    sortByType(library, size);
    InfoOrigin* bookSelectionByGenre = genreSelection(library, size, (char*)"Fantasy");
    printOrigins(bookSelectionByGenre, selectionSize);
    InfoOrigin* bookSelectionByAuthor = authorSelection(library, size, (char*)"J.R.R. Tolkien");
    printOrigins(bookSelectionByAuthor, selectionSize);
    InfoOrigin* magazineSelectionByYear = yearSelection(library, size, 1954);
    printOrigins(magazineSelectionByYear, selectionSize);
    char* genre = (char*)"Fantasy";
    cout << "Storage contain " << amountOfBooksByGenre(library, size, genre) <<" "<< toLowerCase(genre) << " books" << endl;








    //InfoOrigin* library = new InfoOrigin[24] {
    //    {"Book", "Moby-Dick", "Herman Melville", "Adventure", 1851},
    //    {"Book", "The Odyssey", "Homer", "Epic", -800},
    //    {"Book", "The Lord of the Rings", "J.R.R. Tolkien", "Fantasy", 1954},
    //    {"Book", "The Da Vinci Code", "Dan Brown", "Mystery", 2003},
    //    {"Book", "The Shining", "Stephen King", "Horror", 1977 },
    //    {"Book", "To Kill a Mockingbird", "Harper Lee", "Novel", 1960},
    //    {"Book", "1984", "George Orwell", "Dystopian", 1949},
    //    {"Book", "Pride and Prejudice", "Jane Austen", "Romance", 1813},
    //    {"Book", "The Great Gatsby", "F. Scott Fitzgerald", "Classic", 1925},
    //    {"Book", "The Catcher in the Rye", "J.D. Salinger", "Coming-of-Age", 1951},
    //    {"Newspaper", "The New York Times", "Various", "News", 1851},
    //    {"Newspaper", "The Guardian", "Various", "News", 1821},
    //    {"Newspaper", "The Times", "Various", "News", 1785},
    //    {"Newspaper", "The Washington Post", "Various", "News", 1877},
    //    {"Newspaper", "The Wall Street Journal", "Various", "Business", 1889},
    //    {"Magazine", "National Geographic", "Various", "Science", 1888},
    //    {"Magazine", "Time", "Various", "News", 1923},
    //    {"Magazine", "Vogue", "Various", "Fashion", 1892},
    //    {"Magazine", "Sports Illustrated", "Various", "Sports", 1954},
    //    {"Magazine", "Scientific American", "Various", "Science", 1954},
    //    {"Book", "The Hobbit", "J.R.R. Tolkien", "Fantasy", 1937},
    //    {"Book", "A Song of Ice and Fire", "George R.R. Martin", "Fantasy", 1996 },
    //    {"Book", "The Name of the Wind", "Patrick Rothfuss", "Fantasy", 2007 },
    //    {"Book", "The Lies of Locke Lamora", "Scott Lynch", "Fantasy", 2006 },
    //};

    //fstream file("data.txt", ios_base::out);
    //if (!file.is_open()) { cout << "Erorr" << endl; }
    //else 
    //{
    //    for (size_t i = 0; i < 24; i++)
    //    {
    //        file.write((char*)&library[i], sizeof(InfoOrigin));
    //    }
    //}








}


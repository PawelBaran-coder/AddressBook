#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct Person
{
    int id;
    string name, lastName, phoneNumber, emailAddress, address;
};

string convwertIntToString(int number)
{
    ostringstream ss;
    ss << number;
    string str = ss.str();

    return str;
}

vector <string> split(string&dataLine)
{
    vector <string> result;
    const char separator = '|';
    stringstream ss(dataLine);
    string data;

    while (getline(ss, data, separator))
    {
        result.push_back(data);
    }
    return result;
}
void fromVectorToFile(vector <Person> &people)
{
    const char separator = '|';
    fstream file;

    file.open("KsiazkaAdresowa.txt", ios::out);
    if (file.good())
    {
        for ( vector<Person>::iterator itr = people.begin(), finish = people.end(); itr != finish; ++itr )
        {
            file << itr->id << separator << itr->name << separator << itr->lastName << separator << itr->phoneNumber << separator << itr->emailAddress << separator << itr->address << separator << endl;
        }
        file.close();
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: KsiazkaAdresowa.txt" << endl;
    }
}

int fromFileToVector(vector <Person> &people, int numberOfPeople)
{
    Person member;
    string line;

    fstream file;
    file.open("KsiazkaAdresowa.txt",ios::in);

    if (file.good()==false)
    {
        cout<< "Nie udalo sie otworzyc pliku!";
        exit(0);
    }
    while (getline(file,line))
    {
        vector <string> splited = split(line);

        member.id = atoi(splited[0].c_str());
        member.name = splited[1];
        member.lastName = splited[2];
        member.phoneNumber = splited[3];
        member.emailAddress = splited[4];
        member.address = splited[5];

        numberOfPeople++;
        people.push_back(member);
    }
    file.close();

    return numberOfPeople;
}

int addPerson(vector <Person> &people, int numberOfPeople)
{
    Person member;
    string name, lastName, phoneNumber, emailAddress, address;
    string fullData;
    const char separator = '|';
    int personalNumber = 0;

    system("cls");
    cout << "Dodawanie osoby" << endl;
    cout << "Podaj imie osoby : ";
    cin >> name;
    cout << "Podaj nazwisko osoby: ";
    cin >> lastName;
    cout << "Podaj numer telefonu osoby: ";
    cin.sync();
    getline(cin, phoneNumber);
    cout << "Podaj email osoby: ";
    cin >> emailAddress;
    cout << "Podaj adres osoby: ";
    cin.sync();
    getline(cin, address);

    if (people.empty())
    {
        personalNumber = 1;
    }
    else
    {
        personalNumber = people[numberOfPeople-1].id + 1;
    }

    member.id = personalNumber;
    member.name = name;
    member.lastName = lastName;
    member.phoneNumber = phoneNumber;
    member.emailAddress = emailAddress;
    member.address = address;

    people.push_back(member);
    fullData = convwertIntToString(personalNumber) + separator + name + separator + lastName + separator + phoneNumber + separator + emailAddress + separator + address + separator;

    fstream file;
    file.open("KsiazkaAdresowa.txt", ios::out | ios::app);
    if (file.good())
    {
        file << fullData << endl;

        file.close();

        cout << "Osoba zostala dodana." << endl;
        Sleep(1000);
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: KsiazkaAdresowa.txt" << endl;
    }
    numberOfPeople++;

    return numberOfPeople;
}

void nameDisplay(vector <Person> people, int numberOfPeople)
{
    string nameForSearch;
    int howManyNames = 0;

    cout << "Podaj imie: ";
    cin >> nameForSearch;
    system("cls");

    for(int i = 0; i < numberOfPeople; i++)
    {
        if(nameForSearch == people[i].name)
        {
            cout << people[i].id << endl;
            cout << people[i].name << endl;
            cout << people[i].lastName << endl;
            cout << people[i].phoneNumber << endl;
            cout << people[i].emailAddress << endl;
            cout << people[i].address << endl;
            howManyNames += 1;
        }
        else
        {
            howManyNames += 0;
        }
    }
    if(howManyNames == 0)
    {
        cout << "Nie ma takiej osoby!" <<endl;
    }

    system("pause");
}

void lastNameDisplay(vector <Person> people, int numberOfPeople)
{
    string lastNameForSearch;
    int howManyNames = 0;

    cout << "Podaj Nazwisko: ";
    cin >> lastNameForSearch;
    system("cls");

    for(int i = 0; i < numberOfPeople; i++)
    {
        if(lastNameForSearch == people[i].lastName)
        {
            cout << people[i].id << endl;
            cout << people[i].name << endl;
            cout << people[i].lastName << endl;
            cout << people[i].phoneNumber << endl;
            cout << people[i].emailAddress << endl;
            cout << people[i].address << endl;
            howManyNames += 1;
        }
        else
        {
            howManyNames += 0;
        }
    }
    if(howManyNames == 0)
    {
        cout << "Nie ma takiej osoby!" << endl;
    }
    system("pause");
}

void everyoneDisplay(vector <Person> people, int numberOfPeople)
{
    system("cls");
    for(int i = 0; i < numberOfPeople; i++)
    {
        cout << people[i].id << endl;
        cout << people[i].name << endl;
        cout << people[i].lastName << endl;
        cout << people[i].phoneNumber << endl;
        cout << people[i].emailAddress << endl;
        cout << people[i].address << endl;
    }
    system("pause");
}

int deleteMember(vector <Person> &people, int numberOfPeople)
{
    system("cls");
    int numberToDelete;
    char choice;

    cout << "Podaj nr id osoby do usuniecia: ";
    cin >> numberToDelete;

    for ( vector<Person>::iterator itr = people.begin(), finish = people.end(); itr != finish; ++itr )
    {
        if(itr -> id == numberToDelete)
        {
            cout << "Czy napewno chcesz usunac osobe: " << itr -> name << " " << itr -> lastName << " " << "z ksiazki adresowej (t/n)? ";
            cin >> choice;
            if (choice == 't')
            {
                people.erase(itr);
                numberOfPeople--;
                cout << "Osoba zostala usunieta!";
                Sleep(1000);
                return numberOfPeople;
            }
            if (choice == 'n')
            {
                return numberOfPeople;
            }
        }
    }

    cout << "Nie ma takiej osoby" << endl;
    Sleep(1000);

    return numberOfPeople;
}

void editData (vector<Person>&people)
{
    system("cls");
    int memberId;
    char choice;
    int vectorSize = people.size();
    string newData;

    cout <<"Podaj id osoby, ktorej dane chcesz zmienic: "<<endl;
    cin>>memberId;

    for(int i = 0; i < vectorSize; i++)
    {
        if (people[i].id==memberId)
        {
            cout << "Znaleziono taka osobe: "<< endl;
            cout << people[i].name << " " << people[i].lastName << endl;
            break;
        }
        if (i == vectorSize-1)
        {
            cout << "Nie ma osoby o takim nr id!" << endl;
            system("pause");
            return;
        }
    }
    while (true)
    {
        cout <<"Wybierz jaka dana chcesz zmienic:"<<endl;
        cout <<"1 - imie"<<endl;
        cout <<"2 - nazwisko"<<endl;
        cout <<"3 - nr telefonu"<<endl;
        cout <<"4 - e-mail"<<endl;
        cout <<"5 - adres"<<endl;
        cout <<endl;
        cout <<"6 - powrot do menu"<<endl;

        cin>>choice;
        system("cls");

        if (choice=='6')
        {
            break;
        }

        cout <<"Wprowadz nowa wartosc:"<<endl;
        cin>>newData;
        system("cls");

        for ( vector<Person>::iterator itr = people.begin(), finish = people.end(); itr != finish; ++itr )
        {
            if(itr->id == memberId)
            {
                if (choice == '1')
                {
                    itr->name = newData;
                    cout << "Imie zostalo zmienione" << endl;
                    Sleep(1000);
                }
                if (choice == '2')
                {
                    itr->lastName = newData;
                    cout << "Nazwisko zostalo zmienione" << endl;
                    Sleep(1000);
                }
                if (choice == '3')
                {
                    itr->phoneNumber = newData;
                    cout << "Nr telefonu zostal zmieniony" << endl;
                    Sleep(1000);
                }
                if (choice == '4')
                {
                    itr-> emailAddress = newData;
                    cout << "Adres e-mail zostal zmieniony" << endl;
                    Sleep(1000);
                }
                if (choice == '5')
                {
                    itr->address = newData;
                    cout << "Adres zostal zmieniony" << endl;
                    Sleep(1000);
                }
            }
        }
        system("cls");
    }

}

int main()
{
    vector <Person> people;
    int numberOfPeople = 0;
    char choice;

    fstream file;
    file.open("KsiazkaAdresowa.txt",ios::in  | ios::app);

    numberOfPeople = fromFileToVector(people,numberOfPeople);

    while (true)
    {
        system("cls");
        cout << "1. Dodaj osobe" << endl;
        cout << "2. Wyszukaj po imieniu" <<endl;
        cout << "3. Wyszukaj po nazwisku" <<endl;
        cout << "4. Wyswietl wszystkich" <<endl;
        cout << "5. Usun dana osobe" <<endl;
        cout << "6. Edytuj dane osoby" <<endl;
        cout << "9. Zakoncz program" << endl;
        cin >> choice;

        if (choice == '1')
        {
            numberOfPeople = addPerson(people, numberOfPeople);
        }
        else if (choice == '2')
        {
            nameDisplay(people,numberOfPeople);
        }
        else if (choice == '3')
        {
            lastNameDisplay(people,numberOfPeople);
        }
        else if (choice == '4')
        {
            everyoneDisplay(people,numberOfPeople);
        }
        else if (choice == '5')
        {
            numberOfPeople=deleteMember(people,numberOfPeople);
            fromVectorToFile(people);
        }
        else if (choice == '6')
        {
            editData(people);
            fromVectorToFile(people);
        }
        else if (choice == '9')
        {
            exit(0);
        }
        file.close();
    }
    return 0;
}

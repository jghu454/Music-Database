/// TODO Update File Header
///
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Spring 2023

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <fstream>
using namespace std;


// INSERTS GIVEN HELPERS CODE BELOW - DO NOT REMOVE
#include "helpers.cpp"
// INSERTS GIVEN HELPERS CODE ABOVE - DO NOT REMOVE

//
// NOTE TO STUDENTS:
// You may use the functions in the helpers file,
// but you may not modify the file or its contents in any way whatsoever.
//

//
// STUDENT CODE MAY GO BELOW THIS LINE
//
struct Album
{
    string albumName;
    map <int, string> artists;
    set <string> songs;

};

//Utilities General
void printData(map<int,Album> x)
{

    
    for (auto y : x)
    {
 
        cout << y.second.albumName << endl;
        for (auto x : y.second.artists)
        {
            cout <<" " << x.second << endl;

        }
        for (auto x : y.second.songs)
        {
            cout <<"   " << x << endl;
        }


    }
}
string toLower(string x)
{
    tolower(x);
    return x;
}
bool searchMap(map <int, Album> x, string y)
{
    for (auto z : x)
    {
        cout << toLower(z.second.albumName)<< ":" << toLower(y) << endl;
        if (toLower(z.second.albumName).find(toLower(y)) != -1)
        {
            return true;
        }
    }
    return false;
}
bool searchMap(map<int, string> x, string y)
{
    for (auto z : x)
    {
        
        if (toLower(z.second).find(toLower(y)) != -1)
        {
            return true;
        }
    }
    return false;
}
bool searchSet(set<string> x, string y)
{
    for (auto z : x)
    {
        
        if (toLower(z).find(toLower(y)) != -1)
        {
            return true;
        }
    }
    return false;

}

//Utility for Load
//Load function utilities
Album loadingAlbum(ifstream& ifs, string albumName, string& line,set<string>& uniqueArtists, int& songs)
{
    Album currentAlbum = Album();
    int authorsIndex = 0;
    string first, remains;
    currentAlbum.albumName = albumName;
 

    while (line != albumName)
    {
        
        if (isdigit(line.at(0)))
        {
            currentAlbum.songs.insert(line);
            songs++;
        }
        else
        {
            uniqueArtists.insert(line);
            currentAlbum.artists[authorsIndex] = line;
            authorsIndex++;
        }
        getline(ifs, line);
    }
    
    return currentAlbum;
}

//Load function
void loadData(string fileName, map<int,Album>& albumMap, set<string>& uniqueArtists,int& songs, int& albums)
{
    ifstream ifs;
    string albumName, line, remains;

    ifs.open(fileName);
    if (!ifs.is_open())//in case of error
    {
        return;
    }


    getline(ifs, albumName);

    while (getline(ifs, line))
    {
        albums++;
        albumMap[albumMap.size()] = loadingAlbum(ifs, albumName, line, uniqueArtists,songs);
        getline(ifs, albumName);//get next album Name
    }



}

//Search Utilities
set <string> searchAlbums(map<int, Album>& albumMap,string name,string toSearch) {
    set <string> uniqueSet;
    for (auto currentAlbum : albumMap) {
        
        if (toSearch == "artist" && searchMap(currentAlbum.second.artists, name)) {
            uniqueSet.insert(currentAlbum.second.albumName);
        }
        else if (toSearch == "song" && searchSet(currentAlbum.second.songs, name)) {
            uniqueSet.insert(currentAlbum.second.albumName);
        }
        else if (toSearch == "album" && searchMap(albumMap,name)) {
            uniqueSet.insert(currentAlbum.second.albumName);
        }
    }
    return uniqueSet;
}  
//Search Function
void searchFunction(string remains, map<int, Album>& albumMap)
{

    string toSearch;
    string searchName;
    string modifier;
    set <string> albumSet1;
    set <string> albumSet2;
    
    splitFirstWord(remains, toSearch, remains);
    splitFirstWord(remains, searchName, modifier);
   
    albumSet1 = searchAlbums(albumMap, searchName,toSearch);
    if (modifier.length() != 0) {
        albumSet2 = searchAlbums(albumMap, modifier.substr(0, modifier.length() - 1), toSearch);
    }

    set<string> setOperation;
   if (modifier.length() > 0 && modifier.at(0) == '-') {
       set_union(albumSet1.begin(), albumSet1.end(), albumSet2.begin(), albumSet2.end(), inserter(setOperation, setOperation.begin()));
    }else if (modifier.length() > 0 && modifier.at(0) == '+') {
       set_difference(albumSet1.begin(), albumSet1.end(), albumSet2.begin(), albumSet2.end(), inserter(setOperation, setOperation.begin()));
    }else {
       setOperation = albumSet1;
    }
    cout << "Your search exists in the following albums:" << endl;
    for (auto x : setOperation) {
        std::cout << x << endl;
    }

}

int main()
{
    string userEntry;
    string command, remains;
    map <int, Album> allAlbums;
    int songs, albums;
    set <string> uniqueArtists;
    // TODO: Declare any necessary variables for the music libary

    // Display welcome message once per program execution
    cout << "Welcome to the Music Library App" << endl;
    cout << "--------------------------------" << endl;

    // Stay in menu until exit command
    do
    {
        cout << endl;
        cout << "Enter a command (help for help): " << endl;
        getline(cin, userEntry);
        cout << endl;

        // Split the user entry into two pieces
        splitFirstWord(userEntry, command, remains);
        tolower(command);

        // take an action, one per iteration, based on the command
        if (command == "help")
        {
            helpCommand();
        }
        else if (command == "clear")
        {
            // TODO
            allAlbums.clear();
        }
        else if (command == "export")
        {
            // TODO

        }
        else if (command == "load")
        {
            // TODO

            loadData(remains, allAlbums, uniqueArtists, songs, albums);
            //printData(allAlbums);
        }
        else if (command == "stats")
        {
            // TODO
            printData(allAlbums);
        }
        else if (command == "search")
        {   
            // TODO
            searchFunction(remains, allAlbums);
        }

    } while (command != "exit");

    cout << "Thank you for using the Music Library App" << endl;
    return 0;
}

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
    set <string> artists;
    set <string> songs;

};

//Utilities General
void printData(map<string,Album> x, set<string> alphabeticalOrder)
{
    for (auto y : alphabeticalOrder)
    {
        cout << x[y].albumName << endl;
        for (auto x : x[y].artists)
        {
            cout <<" " << x << endl;

        }
        for (auto x : x[y].songs)
        {
            cout <<"   " << x << endl;
        }
    }
    cout << "___" << endl;

}
string toLower(string x)
{
    tolower(x);
    return x;
}
bool searchMap(map <string, Album> x, string y)
{
    for (auto z : x)
    {
        
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
Album loadingAlbum(ifstream& ifs, string albumName, string& line,set<string>& uniqueArtists, set<string>& songs)
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
            songs.insert(line);
        }
        else
        {
            uniqueArtists.insert(line);
            currentAlbum.artists.insert(line);
            authorsIndex++;
        }
        getline(ifs, line);
    }
    
    return currentAlbum;
}

//Load function
void loadData(string fileName, map<string,Album>& albumMap, set<string>& uniqueArtists, set<string>& songs, set<string>& albums, set<string>& alphabeticalOrder)
{
    ifstream ifs;
    string albumName, line, remains;

    ifs.open(fileName);
    if (fileName.length() == 0)
    {
        return;
    }
    if (!ifs.is_open())//in case of error
    {
        cout << "Error: Could not open music library file - " << fileName << endl;
        return;
    }


    getline(ifs, albumName);

    while (getline(ifs, line))
    {
        albums.insert(albumName);
        albumMap[albumName] = loadingAlbum(ifs, albumName, line, uniqueArtists,songs);
        alphabeticalOrder.insert(albumName);
        getline(ifs, albumName);//get next album Name
    }
}

//Search Utilities
set <string> searchAlbums(map<string, Album>& albumMap,string name,string toSearch) {
    set <string> uniqueSet;
    for (auto currentAlbum : albumMap) {
        
        if (toSearch == "artist" && searchSet(currentAlbum.second.artists, name)) {
            uniqueSet.insert(currentAlbum.second.albumName);
        }
        else if (toSearch == "song" && searchSet(currentAlbum.second.songs, name)) {
            uniqueSet.insert(currentAlbum.second.albumName);
        }
        else if (toSearch == "album" && toLower(currentAlbum.second.albumName).find(name) != -1) {
            uniqueSet.insert(currentAlbum.second.albumName);
        }
    }
    return uniqueSet;
}  
//Search Function
void searchFunction(string remains, map<string, Album>& albumMap)
{
    if (remains.length() == 0)
    {
        cout << "Error: Search terms cannot be empty." << endl << "No Results Found." << endl << endl;
        return;
    }

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
    
    if (setOperation.size() == 0) {
        cout << "No results found." << endl << endl;
    }

    cout << "Your search results exist in the following albums:" << endl;
    for (auto x : setOperation) {
        cout << x << endl;
    }
    cout << endl;
}

int main()
{
    string userEntry;
    string command, remains;
    map <string, Album> allAlbums;
    set <string> songs, albums, uniqueArtists, alphabeticalOrder;
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
            songs.clear();
            uniqueArtists.clear();
            albums.clear();
        }
        else if (command == "export")
        {
            // TODO

        }
        else if (command == "load")
        {
            // TODO

            loadData(remains, allAlbums, uniqueArtists, songs, albums,alphabeticalOrder);
            //printData(allAlbums);
        }
        else if (command == "stats")
        {
            // TODO
            cout << "Overall Music Library Stats" << endl << "===========================" << endl;
            cout << "Total Records: " << albums.size() << endl;
            cout << "Total Unique Artists: " << uniqueArtists.size() << endl;
            cout << "Total Songs: " << songs.size() << endl << endl;
            if (remains.find("-d") != -1)
            {
                cout << "Your Current Music Library Includes" << endl << "===================================" << endl;
                printData(allAlbums,alphabeticalOrder);
            }
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

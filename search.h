/*
Program 2: Search Engine
Course: CS 251
System: Mac using Replit
Author: Muhammad Muzzammil
UIN: 661-657-007
---------------------------------------------
*/

#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <map>
#include <fstream>   // For file input and output
#include <sstream>
#include <algorithm>
using namespace std;

// cleanToken recieves in a single word as its parameter to clean it accordlingly:
// It checks the starting of the word and discards any punctuation until it runs into an alphabet or number.
// It checks the ending of the word and discards any punctuation until it runs into an alphabet or number.
// After cleaning, it checks if the word contains atleast 1 alphabet.
// Then it lowercase each letter in the word and returns the clean token/word.
string cleanToken(string s) {

  bool containsAlphabet = false;

  // The following code starts truncating the word from the front
  int saveSize = s.size();
  for(int i = 0; i< saveSize; i++){
    if(isalpha(s[0]) || isdigit(s[0])){
      break;
    }
    else if(ispunct(s[0]) != 0){
      s.erase(0, 1);
    }
  }

  // The following code starts truncating the word from the back of it
  saveSize = s.size();
  if(saveSize > 0){ // if anything is left after truncating from the loop above
    for(int i = saveSize-1; i>=0; i--){
     if(isalpha(s[s.size()-1]) || isdigit(s[s.size()-1])){
        break;
      }
      else if(ispunct(s[s.size()-1]) != 0){
        s.erase(s.size()-1, 1);
      }
    }
  }

  // To check if there is an alphabet in the word
  for(int i = 0; i<s.size();i++){
     if(isalpha(s[i])){
        containsAlphabet = true;
        break;
     }
  }

  // Make sure string is not empty and contains atleast 1 alphabet
  if((s.size() != 0) && (containsAlphabet == true)){ // it is NOT to be discarded
    for(int i = 0; i < s.size(); i++){ // turns each character into lowercase.
      s[i] = tolower(s[i]);
    }
    return(s);
  }

  else{ // if the word is empty after cleaning-
    return "";
  }
}


// gatherTokens recieves 1 or more words separated by spaces as its parameter
// gatherTokens function separates each word with spaces using string stream 
// Then each word is sent to the function above --> cleanTokens.
// Each clean word returned from cleanTokens is then saved into a set of type string
// I implemented this using string stream, while loop to separate words
// This function returns a set of unique clean words. 
set<string> gatherTokens(string text) {
  
    set<string> tokens;
    string word; // for stringstream function 
    string cleanTokenWords; // to store words from cleantToken function

    stringstream split(text);
  
    while(getline(split, word, ' ')){
      cleanTokenWords = cleanToken(word);
      if(cleanTokenWords != ""){ // if the word is not empty
        tokens.insert(cleanTokenWords); // we store the clean token into the set
      }
    }
    
    return tokens;
}


// LINES THAT NEED TO BE UNCOMMENTED for Creative Component have "UNCOMMENT" written above them: 
// 11 LINES in TOTAL needs to be uncommented: 

// Line #226: Uncomment the parameters for the function buildIndex: 
// ",vector <string> &description, vector <string> &website) {"

// Line #245 inside buildIndex function:
// "website.push_back(url);"

// Line #249 inside buildIndex function:
// "description.push_back(line);"

// Line #274 uncomment the parameters for findQueryMatches function:
// ",vector<string> &saveWords) {"

// Line #280 inside findQueryMatches function: 
// "saveWords.clear();"

// Line #293 inside findQueryMatches function:
// "saveWords.push_back(cleanWord);"

// Line #309 inside findQueryMatches function:
// "saveWords.push_back(cleanWord);"

// Line #336 inside findQueryMatches function:
// "saveWords.push_back(cleanWord);"

// Line #380 uncomment passing paramters for calling buildIndex in searchEngine:
// ", description, website);"

// Line #392 uncomment passing paramters for calling findQueryMatches in searchEngine:
// ", saveWords);"

// Line #401 inside searchEngine function :
// "printHighestWordOccurenceURL(cleanDescription, website, saveWords, findMatches);"


// This function is part 1 of creative component
// it is simply saving the urls and description into 2 vectors after cleaning them
// Since we are only allowed to read the file once
// In its parameters its recieving each line saved of the file
// It returns a vector with all clean description lines
vector<string> highestWordOccurenceURL(vector<string>& description){

  string word, sentence, cleanWord;
  vector<string>newDescription;

  for (int i = 0; i < description.size(); i++){
    sentence.clear();
    stringstream s(description[i]);
    while(getline(s, word, ' ')){
      cleanWord = cleanToken(word);
      sentence = sentence + ' ' + cleanWord;
    }
    newDescription.push_back(sentence);
  } 
  return(newDescription);
}


// This function is part 2 of creative component (Major function)
// Recieves clean lines of the desrciption from file being read
// Recieves all URLs in the file line by line
// Recieves all words that the user entered
// and Recieves all matches of users search from findQueryMatches
// Purpose of this function and creative component is to take the urls from findQueryMatches
// take each word that user entered and print out how many times each of those words in each url was found
void printHighestWordOccurenceURL(vector<string>cleanDescription, vector<string>website,
                                  vector<string>wordsToSearch, set<string> findMatches){

  vector<string>matches;
  vector<int>saveIndexNumbers;
  int count = 0;
  string word;

  // Placing all user matches from the set into a vector
  for (auto it = findMatches.begin(); it != findMatches.end(); ++it){
      matches.push_back(*it); // all urs for words saved
    }

  // saving the index number of URLs that were found in function findQueryMatches
  for(int i = 0; i < website.size(); i++){
    for(int k = 0; k < matches.size(); k++){
      if(website[i] == matches[k]){
        saveIndexNumbers.push_back(i);
      }
    }
  }

  // Following code prints out how many times each word was found in the urls
  cout << endl;
  for(int i = 0; i < saveIndexNumbers.size(); i++){
    cout << "In the page " << website[saveIndexNumbers[i]] << ":\n";
    for(int k = 0; k < wordsToSearch.size(); k++){
    
      stringstream s(cleanDescription[saveIndexNumbers[i]]);
      while (getline(s, word, ' ')){
        if (word == wordsToSearch[k]){
          count++;
        }
      }
      cout << "The Word '" << wordsToSearch[k] << "' was found ";
      cout << count << " times:" << endl;
      count = 0;
    }
    cout << endl;
  }
  
  wordsToSearch.clear();
  matches.clear();
  saveIndexNumbers.clear();
  findMatches.clear();
}


// buildIndex function reads the file line by line.
// It saves the line containing the url into a temporary string
// and when it reads the following line (description) that belongs to the url above it
// It passes that description line to the gatherTokens function to clean it and recieve a set.
// Then it loops through the set from gatherTokens and maps each clean word/token as the key 
// and assigns it the value of the url from previous line
// It repeats until the file is completely read and each word is saved into map with urls.
int buildIndex(string filename, map<string, set<string>>& index){
              // UNCOMMENT line below for CREATIVE COMPONENT
              //,vector <string> &description, vector <string> &website) {

  
  ifstream instream;
  instream.open(filename);


  if (instream.is_open()) {
  
    string line;
    set<string> tokens;
    tokens.clear();
    int row = 0;
    string url;
    
    while(getline(instream, line)){ // Read the file line by line
      if(row%2==0){ // only takes the url lines
        url = line; // store the url so later each unique token can be asssigned to it 
        // UNCOMMENT the line BELOW FOR CREATIVE COMPONENT to work
        //website.push_back(url);
      }
      else{ // lines that are text description
        // UNCOMMENT the line BELOW FOR CREATIVE COMPONENT to work
        //description.push_back(line);
        tokens = gatherTokens(line); // We get a set with all the unique tokens
        for (auto it = tokens.begin(); it != tokens.end(); ++it){ //iterating over each token of the set
          index[*it].insert(url); // Each token becomes a key assigned to its url value
        }
      }
      row++; // next line
    }
    
    return(row/2);
  }
  else{
    return(0);
  }
}


// findQueryMatches function searches the word in the map from buildIndex
// it first checks each word to see if it has a '+' or '-' or 'neither' to it
// if it has 'neither' it takes all urls associated to it and puts it into result set
// if it has plus to it, it stores all urls in a different set and takes intersection with result set
// if it has minus to it, it stores all urls in a different set and takes difference with result set
// UNCOMMENT recieving paramenters BELOW FOR CREATIVE COMPONENT to work!!
set<string> findQueryMatches(map<string, set<string>>& index, string sentence){
                            // UNCOMMENT line below for CREATIVE COMPONENT
                            //,vector<string> &saveWords) {
    set<string> result;
    set<string> plus, minus, Difference, Intersection;
    result.clear();

    // UNCOMMENT passing paramenters BELOW FOR CREATIVE COMPONENT to work
    //saveWords.clear();
  

  // READING EACH WORD
    string word, cleanWord;
    stringstream split(sentence);
  
    while(getline(split, word, ' ')){ // separating each word sent by user with space

      // 1. No sign: UNION
      if(word[0] != '+' && word[0] != '-'){
        cleanWord = cleanToken(word);
        // UNCOMMENT the line BELOW FOR CREATIVE COMPONENT to work
        //saveWords.push_back(cleanWord); // for creative component

        // matching keys then storing values
        for(auto it : index){
          if (it.first == cleanWord){
            for(auto pair : it.second){
              result.insert(pair);
            }
          }
        }
      }

      // 2. Addition: INTERSECTION +
      else if(word[0] == '+'){
        cleanWord = cleanToken(word);
        // UNCOMMENT the line BELOW FOR CREATIVE COMPONENT to work
        //saveWords.push_back(cleanWord);

        // matching keys then storing values
        for(auto it : index){
          if (it.first == cleanWord){
            for(auto pair : it.second){
              plus.insert(pair);
            }
          }
        }
        // Taking out the intersection of result set and plus set.
        insert_iterator<set<string>> IntersectIterate(Intersection, Intersection.begin());
        set_intersection(result.begin(), result.end(), plus.begin(), plus.end(), IntersectIterate);
        result.clear();

        for (auto it = Intersection.begin(); it != Intersection.end(); it++){
          result.insert(*it);
        }
        Intersection.clear();
        plus.clear();
        
      }
        
      // 3. Subtraction: DIFFERENCE -
      else if(word[0] == '-'){
        cleanWord = cleanToken(word);
        // UNCOMMENT the line BELOW FOR CREATIVE COMPONENT to work
        //saveWords.push_back(cleanWord);

        // matching keys then storing values
        for(auto it : index){
          if (it.first == cleanWord){
            for(auto pair : it.second){
              minus.insert(pair);
            }
          }
        }
        // Taking out the difference of result set and minus set.
        insert_iterator<set<string>> DifferenceIterate(Difference, Difference.begin());
        set_difference(result.begin(), result.end(), minus.begin(), minus.end(), DifferenceIterate);
        result.clear();

        for (auto it = Difference.begin(); it != Difference.end(); ++it){
          result.insert(*it);
        }

        Difference.clear();
        minus.clear();
        
      }
    } // end while loop
    
    return result;
}


// Recieves the name of a file as its parameter
// Calls buildIndex function to print the number of pages processed and to store keys/values in map
// Takes in user input for word or words that it wants to search in the file
// Calls the findQueryMatches function to search the given word(s) in the buildIndex Map
// It prints out the matching urls (returned from findQueryMatches) based on user's search
// It prompts to take input until user enters quit
void searchEngine(string filename) {

  vector <string> description, website, cleanDescription, saveWords; // USED for CREATIVE COMPONENT
  map<string, set<string>> index;
  int pages;
  string userInput;
  set<string> findMatches;
  
  cout << "Stand by while building index..." << endl;
  // UNCOMMENT passing parameters BELOW FOR CREATIVE COMPONENT to work
  pages = buildIndex(filename, index);//, description, website); 
  cout << "Indexed " << pages << " pages containing " << index.size() << " unique terms\n\n";

  cleanDescription = highestWordOccurenceURL(description); // USED for CREATIVE COMPONENT

  cout << "Enter query sentence (press enter to quit): ";
  getline(cin, userInput);
  
  while(userInput != "quit"){

    findMatches.clear();
    // UNCOMMENT passing parameters BELOW FOR CREATIVE COMPONENT to work
    findMatches = findQueryMatches(index, userInput);//, saveWords);
    
    cout << "Found " << findMatches.size() << " matching pages\n";
    for (auto it = findMatches.begin(); it != findMatches.end(); ++it){
      cout << *it << endl;
    }

    // UNCOMMENT the call to function BELOW FOR CREATIVE COMPONENT to work
    //printHighestWordOccurenceURL(cleanDescription, website, saveWords, findMatches);

    cout << "\nEnter query sentence (press enter to quit): ";
    getline(cin, userInput);
  }

  cout << "Thank you for searching!";
  
}
//**********************************************************************************
// Dictionary class header file
// Author: Erick Ramos
// Date: December 11, 2017
//***********************************************************************************
#ifndef DICTIONARY_H
#define DICTIONARY_H

class Dictionary {
  string word;
  int number;
  
  public:
  
  Dictionary(string n, double place){
      word = n;
      number = place;
  }
  
  const string & getWord() const{
      return word;
  }
  
  bool operator == (const Dictionary & rhs) const{
      return getWord() == rhs.getWord();
  }
  
  bool operator != (const Dictionary & rhs) const{
      return !(*this == rhs);
  }
  
  string toString() {
      return to_string(number) + ": " + word;
  }
};

#endif

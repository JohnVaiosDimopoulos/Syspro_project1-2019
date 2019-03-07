#ifndef PROJECT1_VER3_HASH_TABLE_H
#define PROJECT1_VER3_HASH_TABLE_H

#include <cstring>
#include "Hash_Bucket.h"

template <class T>
class Hash_Table{

 private:
  Hash_Bucket<T>** table;
  const int bucket_size;
  const int table_size;
  unsigned int Hash_fun(char*);

 public:

  //constructor-destructor
  Hash_Table(int,int);
  ~Hash_Table();

  //Functionality
  void Insert(T,char*);
  T Search(char*);

  //debugging(delete before commit the project)
  Hash_Bucket<T>* get_Bucket(int& index) const{
    return this->table[index];
  }

};

//===CONSTRUCTOR-DESTRUCTOR==//
template <class T>
Hash_Table<T>::Hash_Table(const int bucket_size,const int table_size):bucket_size(bucket_size),table_size(table_size){
  this->table = new Hash_Bucket<T>* [table_size];

  for(int i =0;i<table_size;i++){
    table[i] = new Hash_Bucket<T>();
  }
}


template <class T>
Hash_Table<T>::~Hash_Table() {
  for(int i=0;i<table_size;i++){
    delete this->table[i];
  }

  delete[] this->table;
}

//===PRIVATE===//

template <class T>
unsigned int Hash_Table<T>::Hash_fun(char* id) {
  //SAX hash function for strings

  unsigned int hash_value = 0;
  for(int i=0;i<strlen(id);i++){
    hash_value ^=(hash_value<<5)+(hash_value>>2)+id[i];
  }
  return hash_value%table_size;
}

//===FUNCTIONALITY===//
template <class T>
void Hash_Table<T>::Insert(T item, char* item_id) {
  //get the hash
  unsigned int hash_value = Hash_fun(item_id);

  // go the first bucket in the position finded by the hashing
  Hash_Bucket<T>* current = this->table[hash_value];

  while (current!=NULL){

    //check if there is space in the current bucket
    int bytes_left = this->bucket_size-((current->get_number_of_elements()* sizeof(T))+ sizeof(Hash_Bucket<T>*)+ sizeof(unsigned int));

    //--the current bucket is full--//
    if(bytes_left< sizeof(T)){
      //check if there is another bucket after the current one
      if(current->get_next()!=NULL){
        // if there is go to the next and repeat
        current = current->get_next();
        continue;
      }
      else{
        // if there is no other bucket we make a new one
        Hash_Bucket<T>* new_bucket = new Hash_Bucket<T>;
        // connect the new bucket with the current one
        current->set_next(new_bucket);
        //insert the element in the new bucket
        current->Insert(item);
        return;
      }
    }
    //--the current bucket is not full--//
    else{
      current->Insert(item);
      return;

    }
  }
}


template <class T>
T Hash_Table<T>::Search(char* id) {

  //hash the id
  unsigned int hash_value = Hash_fun(id);

  // go the corrent cell in the table and look at the first bucket

  Hash_Bucket<T>* current = table[hash_value];

  //start looking all the buckets in the chain until you find the item
  while (current!=NULL){
    T result = current->Search(id);
    // we found it
    if(result!=NULL)
      return result;
    // if the returned value is NULL we look to the next bucket;
    else
      current = current->get_next();

  }
}

#endif //PROJECT1_VER3_HASH_TABLE_H

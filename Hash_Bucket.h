#ifndef PROJECT1_VER3_HASH_BUCKET_H
#define PROJECT1_VER3_HASH_BUCKET_H

#include "List.h"

template <class T>
class Hash_Bucket{
 private:
  Hash_Bucket<T>* next;
  List<T>* item_list;
  unsigned int num_of_elements;
 public:

  //constructor-destructor
  Hash_Bucket();
  ~Hash_Bucket();

  //accessors
  unsigned int get_number_of_elements() const;
  Hash_Bucket<T>* get_next() const;

  //mutators
  void set_next(Hash_Bucket<T>*);

  //functionality
  T Search(const char*);
  void Insert(T);

};

//==CONSTRUCTOR-DESTRUCTOR==//

template <class T>
Hash_Bucket<T>::Hash_Bucket() {
  this->next=NULL;
  this->num_of_elements = 0;
  this->item_list = new List<T>();
}

template <class T>
Hash_Bucket<T>::~Hash_Bucket() {
  if(next!=NULL)
    delete next;
  delete this->item_list;
}


//===ACCESSORS==//
template <class T>
unsigned int Hash_Bucket<T>::get_number_of_elements() const {
  return this->num_of_elements;
}

template <class T>
Hash_Bucket<T>* Hash_Bucket<T>::get_next() const {
  return this->next;
}

//==MUTATORS==//

template <class T>
void Hash_Bucket<T>::set_next(Hash_Bucket<T>* next) {
  this->next = next;
}

//==FUNCTIONALITY===//

template <class T>
T Hash_Bucket<T>::Search(const char * id) {
  item_list->Search(id);
}

template <class T>
void Hash_Bucket<T>::Insert(T item) {
  item_list->Push(item);
  num_of_elements++;
}

#endif //PROJECT1_VER3_HASH_BUCKET_H

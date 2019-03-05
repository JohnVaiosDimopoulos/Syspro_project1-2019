#ifndef PROJECT1_VER3_LIST_NODE_H
#define PROJECT1_VER3_LIST_NODE_H
#include <cstdlib>

template <class T>
class List_node{

 private:
  T item;
  List_node<T>* next;

 public:
  //constructor-destructor
  List_node(T);
  ~List_node();

  //accessors
  List_node<T>* get_next() const;
  T get_item() const;

  //mutatos
  void set_next(List_node<T>*);
  void set_item(T);

  //other
  bool compare_item(const char*);
};

//==CONSTRUCTOR-DESTRUCTOR==//

template <class T>
List_node<T>::List_node(T item){
  this->item = item;
  this->next = NULL;

}

template <class T>
List_node<T>::~List_node() {
  if(next!=NULL)
    delete this->next;
  delete this->item;
}

//==ACCESSORS==//

template <class T>
T List_node<T>::get_item() const {
  return this->item;
}

template <class T>
List_node<T>* List_node<T>::get_next() const {
  return this->next;
}

//==MUTATORS==//

template <class T>
void List_node<T>::set_next(List_node<T>* next){
  this->next = next;
}


template <class T>
void List_node<T>::set_item(T item) {
  this->item = item;
}

//==FUNCTIONALITY===//

template <class T>
bool List_node<T>::compare_item(const char* id) {
  if(*(this->item)==id)
    return true;
  else
    return false;
}

#endif //PROJECT1_VER3_LIST_NODE_H

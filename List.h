#ifndef PROJECT1_VER3_LIST_H
#define PROJECT1_VER3_LIST_H
#include "List_node.h"

template <class T>
class List{

 private:
  List_node<T>* head;

 public:

  //constructor-destructor
  List();
  ~List();

  //accessor
  List_node<T>* get_head();

  //functionality
  bool is_empty();
  void Push(T);
  T Search(const char*);
  T Search(int&);
  void Delete(const char*);
  void Nullify();
};

//===CONSTRUCTOR-DESTRUCTOR==//

template <class T>
List<T>::List() {
  this->head = NULL;
}


template <class T>
List<T>::~List() {
  if (this->head!=NULL)
    delete head;
}

//===ACCESSOR===//

template <class T>
List_node<T>* List<T>::get_head() {
  return this->head;
}


//===FUNCTIONALITY===//

template <class T>
bool List<T>::is_empty() {
  if(this->head==NULL)
    return true;
  else
    return false;
}


template <class T>
void List<T>::Push(T item) {
  List_node<T>* new_node = new List_node<T>(item);
  new_node->set_next(head);
  this->head = new_node;
}


template <class T>
T List<T>::Search(const char* id) {
  if(this->is_empty())
    return NULL;
  List_node<T>* current = this->head;
  while (current!=NULL){
    if(current->compare_item(id))
      return current->get_item();
    else
      current = current->get_next();
  }
  return NULL;
}


template <class T>
T List<T>::Search(int& value){
  if(this->is_empty())
    return NULL;
  List_node<T>* current = this->head;
  while (current!=NULL){
    if(current->compare_item(value))
      return current->get_item();
    else
      current=current->get_next();
  }
  return NULL;

}


template <class T>
void List<T>::Delete(const char* id) {

  if (this->is_empty())
    return;
  List_node<T>* current = this->head;
  List_node<T>*previus = current;

  //check the head of the list
  if(current->compare_item(id)){
    this->head = current->get_next();
    current->set_next(NULL);
    delete current;
    return;
  }
  else
    current = current->get_next();

  //start looping
  while (current!=NULL){
    // if the element is the last on the list
    if (current->get_next()==NULL && current->compare_item(id)){
      previus->set_next(NULL);
      delete current;
      return;
    }
    else if (current->compare_item(id)){
      previus->set_next(current->get_next());
      current->set_next(NULL);
      delete current;
      return;
    }
    else{
      previus = previus->get_next();
      current = current->get_next();
    }

  }
}

template <class T>
void List<T>::Nullify() {
  List_node<T>* current = this->head;
  while (current!=NULL){
    current->set_item(NULL);
    current=current->get_next();
  }
}
#endif //PROJECT1_VER3_LIST_H

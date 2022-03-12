#ifndef RECORD_H
#define RECORD_H

#include <string>
#include "serializable.h"

using namespace std;

template <class T>
class record : public serializable {
   static_assert(is_base_of<serializable, T>::value, "T must be serializable");
   public:
      record();
      record(T d);
      record(const record<T> &other);
      virtual ~record();
      record<T> operator=(const record<T> &other);
      bool operator==(const record<T> &other);
      T getData() const;
      void setData(T d);
      unsigned long long int getNext() const;
      void setNext(unsigned long long int n);
      bool isDeleted() const;
      void del();
      void undel();
      virtual string toString();
      virtual void fromString(string repr);
      virtual string toCSV() { return ""; }
      virtual void fromCSV(string repr) {}
      virtual string toJSON() { return ""; }
      virtual void fromJSON(string repr) {}
      virtual string toXML() { return ""; }
      virtual void fromXML(string repr) {}
      virtual unsigned long long int size() const;
   protected:
      T data;
      bool deleted;
      unsigned long long int next;
};

template <class T>
record<T>::record() : serializable() {

}

template <class T>
record<T>::record(T d) : serializable() {

}

template <class T>
record<T>::record(const record<T> &other) {

}

template <class T>
record<T>::~record() {

}

template <class T>
record<T> record<T>::operator=(const record<T> &other) {

}

template <class T>
bool record<T>::operator==(const record<T> &other) {

}

template <class T>
T record<T>::getData() const {

}

template <class T>
void record<T>::setData(T d) {

}

template <class T>
unsigned long long int record<T>::getNext() const {

}

template <class T>
void record<T>::setNext(unsigned long long int n) {

}

template <class T>
bool record<T>::isDeleted() const {

}

template <class T>
void record<T>::del() {

}

template <class T>
void record<T>::undel() {

}

template <class T>
string record<T>::toString() {

}

template <class T>
void record<T>::fromString(string repr) {

}

template <class T>
unsigned long long int record<T>::size() const {

}

#endif // RECORD_H

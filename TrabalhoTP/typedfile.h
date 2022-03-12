#ifndef TYPEDFILE_H
#define TYPEDFILE_H

#include <fstream>
#include <type_traits>
using namespace std;

const ios::openmode mode = ios::in | ios::out | ios::binary;

template <class T>
class typedFile : private fstream {
   static_assert(is_base_of<serializable, T>::value, "T must be serializable");
   public:
      typedFile();
      typedFile(const string name, const string type, const unsigned int version, ios::openmode openmode = mode);
      virtual ~typedFile();
      bool open(const string name, const string type, const unsigned int version, ios::openmode openmode = mode);
      bool isOpen();
      bool close();
      void clear();
      bool readRecord(record<T> &r, unsigned long long int i);
      bool writeRecord(record<T> &r, unsigned long long int i);
      bool insertRecord(record<T> &r);
      bool deleteRecord(unsigned long long int i);
      unsigned long long int getFirstValid();
      unsigned long long int getFirstDeleted();
      unsigned long long int search(T data);
   protected:
      header head;
      bool readHeader(header &h);
      bool writeHeader(header &h);
      unsigned long long int index2pos(unsigned long long int i);
      unsigned long long int pos2index(unsigned long long int p);
};

template <class T>
typedFile<T>::typedFile() : fstream() {

}

template <class T>
typedFile<T>::typedFile(const string name, const string type, const unsigned int ver, ios::openmode openmode) : fstream(name.c_str(), mode) {

}

template <class T>
typedFile<T>::~typedFile() {

}

template <class T>
bool typedFile<T>::open(const string name, const string type, const unsigned int ver, ios::openmode openmode = mode) {

}

template <class T>
bool typedFile<T>::isOpen() {

}

template <class T>
bool typedFile<T>::close() {

}

template <class T>
bool typedFile<T>::clear() {

}

template <class T>
bool typedFile<T>::readRecord(record<T> &r, unsigned long long int i) {

}

template <class T>
bool typedFile<T>::writeRecord(record<T> &r, unsigned long long int i) {

}

template <class T>
bool typedFile<T>::insertRecord(record<T> &r) {

}

template <class T>
bool typedFile<T>::deleteRecord(unsigned long long int i) {

}

template <class T>
unsigned long long int typedFile<T>::getFirstValid() {

}

template <class T>
unsigned long long int typedFile<T>::getFirstDeleted() {

}

template <class T>
unsigned long long int typedFile<T>::search(T data) {

}

template <class T>
bool typedFile<T>::readHeader(header &h) {

}

template <class T>
bool typedFile<T>::writeHeader(header &h) {

}

template <class T>
unsigned long long int typedFile<T>::index2pos(unsigned long long int i) {

}

template <class T>
unsigned long long int typedFile<T>::pos2index(unsigned long long int p) {

}
#endif // TYPEDFILE_H

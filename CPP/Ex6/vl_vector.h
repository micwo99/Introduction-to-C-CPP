//
// Created by Michael Wolhandler on 10/01/2021.
//

#ifndef EX6__VL_VECTOR_H_
#define EX6__VL_VECTOR_H_
#include "iostream"
#include <cmath>
#define STATIC_CAPACITY 16
#define RANGE_ERROR "Index out of range"
#define STATIC_MEMORY 0
#define DYNAMIC_MEMORY 1


/**
 * the class VLVector represents the container VLVector that the exercise ask to create
 * @tparam T type of the element into the VLVector
 * @tparam C the initial capacity
 */
template<typename T, size_t C = STATIC_CAPACITY>
class VLVector{
 private:

  size_t vec_capacity_=C;
  size_t vec_size_=0;
  T static_vec_[C];
  T* dynamic_vec_;
  int memory_ = STATIC_MEMORY;


  /**
   * A nested class that represents an iterator
   */
  class Iterator {
    T *it_;
   public:
    typedef T value_type;
    typedef T &reference;
    typedef T *pointer;
    typedef ptrdiff_t difference_type;
    typedef std::random_access_iterator_tag iterator_category;

    Iterator(T *iterator) : it_(iterator) {};

    reference operator*() const {
        return *it_;
    }
    Iterator &operator++() {
        it_++;
        return *this;
    }
    Iterator operator++(int) const {
        Iterator it2(it_);
        it_++;
        return it2;
    }
    Iterator &operator--() {
        it_--;
        return *this;
    }
    Iterator operator--(int) const {
        Iterator it2(it_);
        it_--;
        return it2;
    }
    Iterator operator+(const int &n) {
        return Iterator(it_ + n);
    }
    Iterator operator+=(const int &n) {
        *this = it_ + n;
        return *this;
    }
    Iterator operator-(const int &n) {
        return Iterator(it_ - n);
    }
    Iterator operator-=(const int &n) {
        *this = it_ - n;
        return *this;
    }
    difference_type operator-(const Iterator& other) const {
        return it_ -other.it_;
    }
    bool operator==(const Iterator &other) const {
        return it_ == other.it_;
    }
    bool operator!=(const Iterator &other) const {
        return it_ != other.it_;
    }
    bool operator<(const Iterator &rhs) const {
        return it_ < rhs.it_;
    }
    bool operator>(const Iterator &rhs) const {
        return rhs < *this;
    }
    bool operator<=(const Iterator &rhs) const {
        return rhs >= *this;
    }
    bool operator>=(const Iterator &rhs) const {
        return *this >= rhs;
    }
  };
  /**
   * A nested class that represents an const iterator
   */
  class ConstIterator{
     const T* it_;

     public:
      typedef T value_type;
      typedef const T& reference;
      typedef const T* pointer;
      typedef ptrdiff_t difference_type;
      typedef std::random_access_iterator_tag iterator_category;

      ConstIterator(const T* iterator): it_(iterator){};

      value_type operator*() const{
          return *it_;
      }
      ConstIterator& operator++(){
          it_++;
          return *this;
      }
      ConstIterator operator++(int) {
          ConstIterator it2(it_);
          it_++;
          return it2;
      }
      ConstIterator& operator--(){
          it_--;
          return *this;
      }
      ConstIterator operator--(int) const{
          ConstIterator it2(it_);
          it_--;
          return it2;
      }
      ConstIterator operator+(const int& n){
          return ConstIterator(it_+n);
      }
      ConstIterator operator+=(const int& n){
          *this= it_ + n;
          return *this;
      }
      ConstIterator operator-(const int& n){
          return ConstIterator(it_-n);
      }
      ConstIterator operator-=(const int& n){
          *this= it_ - n;
          return *this;
      }
      difference_type operator-(const ConstIterator& other) const {
        return it_ -other.it_;
    }
      bool operator==(const ConstIterator &other) const{
          return it_==other.it_;
      }
      bool operator!=(const ConstIterator &other) const{
          return it_ != other.it_;
      }
      bool operator<(const ConstIterator &rhs) const {
          return it_ < rhs.it_;
      }
      bool operator>(const ConstIterator &rhs) const {
          return rhs < *this;
      }
      bool operator<=(const ConstIterator &rhs) const {
          return rhs >= *this;
      }
      bool operator>=(const ConstIterator &rhs) const {
          return *this >= rhs;
      }
  };
 public:
  typedef Iterator iterator;
  typedef ConstIterator const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  /**
   * the functions returns the begin of the vector
   */
  iterator begin()
  {
      if(memory_ == STATIC_MEMORY){
          return iterator(&static_vec_[0]);
      }
      else{
          return iterator(&dynamic_vec_[0]);
      }
  }
  /**
   * the functions returns the end of the vector
   */
  iterator end()
  {
      if(memory_ == STATIC_MEMORY){
          return iterator(&static_vec_[0]+vec_size_);
      }
      else{
          return iterator(&dynamic_vec_[0]+vec_size_);
      }
  }
  /**
   * the functions returns the begin of the vector const version
   */
  const_iterator begin() const
  {
      if(memory_ == STATIC_MEMORY){
          return const_iterator(&static_vec_[0]);
      }
      else{
          return const_iterator(&dynamic_vec_[0]);
      }
  }
  /**
   * the functions returns the end of the vector const version
   */
  const_iterator end() const
  {
      if(memory_ == STATIC_MEMORY){
          return const_iterator(&static_vec_[0]+vec_size_);
      }
      else{
          return const_iterator(&dynamic_vec_[0]+vec_size_);
      }
  }
  /**
  * the functions returns the begin of the vector const version
  */
  const_iterator cbegin() const
  {
      if(memory_ == STATIC_MEMORY){
          return const_iterator(&static_vec_[0]);
      }
      else{
          return const_iterator(&dynamic_vec_[0]);
      }
  }
  /**
   * the functions returns the end of the vector const version
   */
  const_iterator cend() const
  {
      if(memory_ == STATIC_MEMORY){
          return const_iterator(&static_vec_[0]+vec_size_);
      }
      else{
          return const_iterator(&dynamic_vec_[0]+vec_size_);
      }
  }


  /**
   * the functions returns the end of the vector
   */
  reverse_iterator rbegin()
  {
      if(memory_ == STATIC_MEMORY){
          return reverse_iterator(&static_vec_[0]+vec_size_);
      }
      else{
          return reverse_iterator(&dynamic_vec_[0]+vec_size_);
      }
  }
  /**
   * the functions returns the begin of the vector
   */
  reverse_iterator rend()
  {
      if(memory_ == STATIC_MEMORY){
          return reverse_iterator(&static_vec_[0]);
      }
      else{
          return reverse_iterator(&dynamic_vec_[0]);
      }
  }
  /**
   * the functions returns the end of the vector const version
   */
  const_reverse_iterator rbegin() const
  {
      if(memory_ == STATIC_MEMORY){
          return const_reverse_iterator(&static_vec_[0]+vec_size_);
      }
      else{
          return const_reverse_iterator(&dynamic_vec_[0]+vec_size_);
      }
  }
  /**
   * the functions returns the begin of the vector const version
   */
  const_reverse_iterator rend() const
  {
      if(memory_ == STATIC_MEMORY){
          return const_reverse_iterator(&static_vec_[0]);
      }
      else{
          return const_reverse_iterator(&dynamic_vec_[0]);
      }
  }
  /**
   * the functions returns the begin of the vector const version
   */
  const_reverse_iterator crend() const
  {
      if(memory_ == STATIC_MEMORY){
          return const_reverse_iterator(&static_vec_[0]-1);
      }
      else{
          return const_reverse_iterator(&dynamic_vec_[0]-1);
      }
  }
  /**
   * the functions returns the end of the vector const version
   */
  const_reverse_iterator crbegin() const
  {
      if(memory_ == STATIC_MEMORY){
          return const_reverse_iterator(&static_vec_[0]+vec_size_-1);
      }
      else{
          return const_reverse_iterator(&dynamic_vec_[0]+vec_size_-1);
      }
  }



  /**
   * Default constructor
   * The default constructor initialise an empty VLVector
   */
  VLVector()
  {
      vec_capacity_ = C;
      vec_size_ = 0;
      dynamic_vec_= nullptr;
      memory_ = STATIC_MEMORY;

 }
 /**
  * Copy constructor
  * @param vec  the vector we will copy
  */
  VLVector(const VLVector &vec)
  {
      this->vec_capacity_ = vec.vec_capacity_;
      this->vec_size_ = vec.vec_size_;
      if(vec.memory_ == DYNAMIC_MEMORY){
          this->dynamic_vec_= new T[vec.vec_capacity_];
          this->memory_ = DYNAMIC_MEMORY;
          for (size_t i = 0; i <vec.vec_size_ ; ++i) {
              this->dynamic_vec_[i] = vec.dynamic_vec_[i];
          }
      }
      if(vec.memory_ == STATIC_MEMORY){
          this->dynamic_vec_ = nullptr;
          this->memory_ = STATIC_MEMORY;
          for (size_t k = 0; k <vec.vec_size_ ; ++k) {
              this->static_vec_[k]=vec.static_vec_[k];
          }
      }

  }
  /**
   * A constructor that receives the size of the vlvector and initialises all the value of the vlvector by elem
   * @param count the size of the new vlvector
   * @param elem the value of all the element in the vlvector
   */
  VLVector(int& count, T& elem)
  {
      if(count<=C){
          this->dynamic_vec_= nullptr;
          this->memory_ = STATIC_MEMORY;
          this->vec_size_ = count;
          this->vec_capacity_ = C;
          for (size_t i = 0; i <count; ++i)
              this->static_vec_[i] = elem;

      }
      if(count > C){
          this->vec_size_ = count;
          this->vec_capacity_ = floor((3*(vec_size_))/2);
          this->dynamic_vec_ = new T[vec_capacity_];
          this->memory_= DYNAMIC_MEMORY;
          for (size_t k = 0; k <vec_size_ ; ++k) {
              this->dynamic_vec_[k] = elem;
          }

      }

  }

  /**
   * Constructor with iterator
   * @param begin first iterator
   * @param end last iterator
   */
  template <class InputIterator>
  VLVector(const InputIterator &begin, const InputIterator &end)
  {
      for(InputIterator it=begin; it < end;++it)
      {
          PushBack(*it);
      }
  }

  /**
   * the function returns the size of the VLVector
   * @return the size of the VLVector
   */
  size_t Size()
  {
      return vec_size_;
  }

  /**
  * the function returns the capacity of the VLVector
  * @return the capacity of the VLVector
  */
  size_t Capacity()
  {
      return  vec_capacity_;

  }
  /**
   * the function returns true if the VLVector is empty, false otherwise
   * @return true/false
   */
  bool Empty()
  {
      return vec_size_==0;
  }
  /**
   * the function return the element at the given index of the VLVector if the index isn't valid the function
   * will throw an error of range
   * @param index  index of the value that we want to return
   * @return  element at the given index of the VLVector
   */
  T& At(size_t index)
  {
      if(index >= vec_size_ || index< 0){

          throw std:: out_of_range( RANGE_ERROR);
      }
      else if(memory_ == STATIC_MEMORY){

          return static_vec_[index];
      }

      else{
          return dynamic_vec_[index];
      }
  }

  /**
   * the function resizes the VLVector from a static vector to a dynamic vector and
   * also  resizes a dynamic vector to a dynamic vector
   * @param num how much element we will add to the vector after resizing
   */
  void ResizeDynamicArr(size_t num)
  {
      if(this->memory_ == STATIC_MEMORY)
      {
          this->memory_ = DYNAMIC_MEMORY;
          this->vec_capacity_ = floor(3 * (vec_size_ + num) / 2);
          this->dynamic_vec_ = new T[vec_capacity_];
          for (size_t i = 0; i < vec_size_; ++i)
              this->dynamic_vec_[i] = this->static_vec_[i];


      }
      else{
          this->vec_capacity_ = floor(3 * (vec_size_ + num) / 2);
          T *tmp = this->dynamic_vec_;
          this->dynamic_vec_ = new T[vec_capacity_];
          for (size_t i = 0; i < vec_size_; i++)
              dynamic_vec_[i] = tmp[i];
          delete[]tmp;
      }
  }


  /**
   * the functions adds a element at the end of the vector
   * @param elem elem that we want to add to the vector
   */
  void PushBack(const T& elem){
      if(vec_size_ != vec_capacity_)
      {
          if(this->memory_ == STATIC_MEMORY)
          {
              this->static_vec_[vec_size_] = elem;
              this->vec_size_++;
          }
          else{
              this->dynamic_vec_[vec_size_] = elem;
              this->vec_size_++;
          }
      }
      else{
          ResizeDynamicArr(1);
          this->dynamic_vec_[this->vec_size_] = elem;
          this->vec_size_++;
          }
  }
  /**
   * the functions remove the last element of the vector
   */
  void PopBack()
  {
      if(this->vec_size_ == 0)
          return;
      else{
          this->vec_size_--;
          if(vec_size_ == C){
              this->memory_ = STATIC_MEMORY;
              this->vec_capacity_ = C;
              for (size_t i = 0; i <this->vec_size_ ; ++i)
              {
                  this->static_vec_[i] = this->dynamic_vec_[i];
              }
              delete []dynamic_vec_;
              this->dynamic_vec_ = nullptr;

          }
      }

  }
  /**
   * the function clears the vector from all his elements
   */
  void Clear()
  {
      if(this->memory_ == STATIC_MEMORY)
          this->vec_size_=0;

      else{
          delete[] this->dynamic_vec_;
          this->vec_capacity_= C;
          this->vec_size_=0;
          this->memory_ = STATIC_MEMORY;
      }

  }
  /**
   * return the actual vector we use dynamic or static
   * @return dynamic vector or static vector
   */
  T* Data()
  {
      if(this->memory_ == STATIC_MEMORY)
          return static_vec_;
      else{
          return dynamic_vec_;

      }
  }


  // Function Insert with Iterator and ConstIterator

  /**
   * The function  allowed to add to the vector several elements at a given position in the vector
   * @tparam InputIterator type of iterator
   * @param position where we want to add  several elements
   * @param first an iterator that points to the first element that we want to add
   * @param last an iterator that points to the last element that we want to add
   * @return Iterator of the first element we add
   */
  template<class InputIterator>
  iterator Insert(const iterator &position,const InputIterator &first,const InputIterator &last)
  {
      size_t to_insert = std::abs(last-first);
      vec_size_ += to_insert;
      size_t index = position-begin();
      if(vec_capacity_< vec_size_)
          ResizeDynamicArr(0);

      for (size_t i = vec_size_; i > index ; --i)
          Data()[i]= Data()[i-to_insert];


      auto value = first;
      for (size_t i=0; i< to_insert;++i){
          Data()[index+i] = *value;
          value++;
      }
      return position;
  }
  template<class InputIterator>
  /**
   * const version of the precedent Insert
   */
  const_iterator Insert(const const_iterator &position,const InputIterator &first,const InputIterator &last)
  {
      size_t index = position - cbegin();
      Iterator iterator1(&(*this)[index]);
      Insert(iterator1,first,last);
      ConstIterator result(&(*this)[index]);
      return result;
  }
  /**
   * The function adds a element to the vector at the index that is point by th iterator
   * @param position iterator that points to the index where we want to add the element
   * @param elem the element that we want to add
   * @return return the iterator where we added the element
   */
  iterator Insert(const iterator &position, const T elem)
  {

      size_t index = position-begin();
      if(vec_capacity_==vec_size_){
          ResizeDynamicArr(0);
      }
      for (size_t i = vec_size_; i > index ; --i) {
          Data()[i]= Data()[i-1];
      }
      Data()[index] = elem;
      vec_size_++;
      return begin()+index;


  }
  /**
   * const version of the precedent Insert
   */
  const_iterator Insert(const const_iterator& position, const T& element)
  {
      size_t index = position - cbegin();
      Iterator iterator1(&(*this)[index]);
      Insert(iterator1, element);
      ConstIterator result(&(*this)[index]);
      return result;
  }



  //Erase with Iterator and ConstIterator
  /**
   * The function erases the element at the index that the iterator points to
   * @param position iterator that points to the elements that we want to erase
   * @return return the iterator where we erased the element
   */
  iterator Erase(const iterator &position)
  {
      size_t index = position-begin();
      if(vec_size_ == C+1){
          this->memory_ = STATIC_MEMORY;
          this->vec_capacity_ = C;
          for (size_t i = 0; i <this->vec_size_ ; ++i) {
              this->static_vec_[i] = this->dynamic_vec_[i];
          }
          this->dynamic_vec_ = nullptr;

      }
      for (size_t i= index; i <vec_size_-1 ; i++) {
          Data()[i]= Data()[i+1];
      }
      vec_size_--;
      return position;
  }
  /**
   * const version of the precedent Erase
   */
  const_iterator Erase(const const_iterator &position)
  {
      size_t index = position - cbegin();
      Iterator iterator1(&(*this)[index]);
      Erase(iterator1);
      ConstIterator res(&(*this)[index]);
      return res;
  }
  /**
   * the function erase all the element between the element that the iterator first point to and the element that the
   * the iterator last point to
   * @param first an iterator that points to the first element that we want to erase
   * @param last an iterator that points to the last element that we want to erase
   * @return Iterator of the first element we erase
   */
  iterator Erase(const iterator& first, const iterator& last)
  {

      size_t to_erase =last - first;
      size_t index = first-begin();
      for (size_t i = index; i <vec_size_; ++i)
          Data()[i]= Data()[i + to_erase];
      vec_size_-= to_erase;
      if(memory_== DYNAMIC_MEMORY)
      {
          if (vec_size_ <= C)
          {
              this->memory_ = STATIC_MEMORY;
              this->vec_capacity_ = C;
              for (size_t i = 0; i < this->vec_size_; ++i)
                  this->static_vec_[i] = this->dynamic_vec_[i];

              delete[]dynamic_vec_;
              this->dynamic_vec_ = nullptr;
          }
      }

      Iterator res(&(*this)[index]);
      return res;
  }
  /**
   * const version of the precedent Erase
   */
  const_iterator Erase(const const_iterator& first, const const_iterator& last)
  {
      auto ind1 = first - cbegin();
      auto ind2 = last - cbegin();
      iterator it1(&(*this)[ind1]);
      iterator it2(&(*this)[ind2]);
      Erase(it1, it2);
      const_iterator res(&(*this)[ind1]);
      return res;

  }


  //Operators of VLVector
  /**
   * copy all the attributs of a vector to an other
   * @param rhs the vector from which we copy all the attributs
   */
  VLVector& operator=(VLVector& rhs)
  {
      if(*this != rhs)
      {
          this->Clear();
          for (size_t i = 0; i <rhs.vec_size_ ; ++i)
          {
              if(rhs.memory_ == DYNAMIC_MEMORY)
                  this->PushBack(rhs.dynamic_vec_[i]);
              else
                  this->PushBack(rhs.static_vec_[i]);
          }
      }
      return *this;
  }
  /**
   * the operator returns the element  of the vector at the given index
   * @param index index of the element that we wants to returns
   */
  T& operator[](size_t index)
  {
      if(memory_ == DYNAMIC_MEMORY)
          return dynamic_vec_[index];

      else
          return static_vec_[index];
  }
  /**
   * the operator return true if the two vectors are the same , returns false otherwise
   * @param rhs the second vector
   * @return true/false
   */
  bool operator==(VLVector& rhs)
  {
      if(vec_size_ != rhs.vec_size_)
          return false;

      if(memory_ == DYNAMIC_MEMORY)
      {
          for(size_t i = 0; i< vec_size_; ++i)
          {
              if(dynamic_vec_[i]!= rhs.dynamic_vec_[i])
                  return false;
          }
      }
      if(memory_ == STATIC_MEMORY)
      {
          for(size_t i = 0; i< vec_size_; ++i)
          {
              if(static_vec_[i] != rhs.static_vec_[i])
                  return false;
          }
      }
      return true;
  }
  /**
  * the operator return true if the two vectors are the different , returns false otherwise
  * @param rhs the second vector
  * @return true/false
  */
  bool operator!=(VLVector& rhs){return !(*this == rhs);}

  ~VLVector(){
      if(memory_ == DYNAMIC_MEMORY){
          delete []dynamic_vec_;
      }
  }

};

#endif //EX6__VL_VECTOR_H_

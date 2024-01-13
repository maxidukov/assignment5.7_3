#include <iostream>
#include <exception>
#include  <initializer_list> // initializer_list, seems unnecessary on Linux

template<class T>
class vector{
  T* ptr_ = nullptr;
  int size_{};
  int capacity_{};
  public:
  vector(){}
  vector(std::initializer_list<T> inlist){
    size_ = inlist.size();
    capacity_ = size_;
    ptr_ = new T[capacity_];
    for(int i{}; i<size_; i++){
      ptr_[i] = inlist.begin()[i];
    }
    /*int i{};
    for(const T& val:inlist){
      ptr_[i++] = val;
    }*/
  }
  vector(const vector<T>& first): size_(first.size_), capacity_(first.capacity_) {
    ptr_ = new T[capacity_];
    for(int i{}; i<size_; i++){
      ptr_[i] = first.ptr_[i];
    }
  }
  vector<T>& operator=(const vector<T>& first){
    if(this != &first){
      size_ = first.size_;
      capacity_ = first.capacity_;
      //ptr_ = nullptr;
      delete [] ptr_;
      ptr_ = new T[capacity_];
      for(int i{}; i<size_; i++){
        ptr_[i] = first.ptr_[i];
      }
    }
    return *this;
  }
  void push_back(T elem){
    if(size_==capacity_){
      if(capacity_==0) capacity_++; //OTHERWISE ALL PUSH_BACKS BUT FIRST ONE WILL FAIL
      capacity_ *= 2;
      T* new_ptr = new T[capacity_];
      for(int i{};i<size_;i++){
        new_ptr[i] = ptr_[i];
      }
      delete[] ptr_;
      ptr_ = new_ptr;
    }
    ptr_[size_++] = elem;
  }
  void shrink_to_fit(){
    if(size_<capacity_){
      capacity_ = size_;
      T* new_ptr = new T[capacity_];
      for(int i{};i<size_;i++){
        new_ptr[i] = ptr_[i];
      }
      delete[] ptr_;
      ptr_ = new_ptr;
    }
  }
  void pop_back(){
    size_--;
    if(size_ <= capacity_/2){
      std::cout << "Shrinking to fit\n";
      shrink_to_fit(); }
  }
  T& operator[](int i){
    if(i<0 || i>=size_)
      throw std::out_of_range("Error: index out of range");
    else return ptr_[i];
  }
  const T& operator[](int i) const{
    if(i<0 || i>=size_)
        throw std::out_of_range("Error: index out of range");
    else return ptr_[i];
  }
  T& at(int i){ return (*this)[i]; }
  const T& at(int i) const{ return (*this)[i]; }
  int size(){ return size_; }
  int capacity(){ return capacity_; }
  struct Iterator
  {
      using iterator_category = std::random_access_iterator_tag;
      using difference_type   = std::ptrdiff_t;
      using value_type        = T;
      using pointer           = T*;
      using reference         = T&;

      Iterator(pointer ptr) : itptr(ptr) {}

      reference operator*() const { return *itptr; }
      pointer operator->() { return itptr; }
      Iterator& operator++() { itptr++; return *this; }
      Iterator operator++(T) { Iterator tmp = *this; ++(*this); return tmp; }
      Iterator& operator--() { itptr--; return *this; }
      Iterator operator--(T) { Iterator tmp = *this; --(*this); return tmp; }
      Iterator& operator+=(difference_type n) { itptr+=n; return *this; }
      Iterator& operator-=(difference_type n) { itptr-=n; return *this; }

      friend bool operator== (const Iterator& a, const Iterator& b) { return a.itptr == b.itptr; };
      friend bool operator!= (const Iterator& a, const Iterator& b) { return !(a==b); };
      friend bool operator< (const Iterator& a, const Iterator& b) { return a.itptr < b.itptr; };
      friend bool operator> (const Iterator& a, const Iterator& b) { return b<a; };
      friend bool operator<= (const Iterator& a, const Iterator& b) { return !(a>b); };
      friend bool operator>= (const Iterator& a, const Iterator& b) { return !(a<b); };
      friend Iterator operator+(const Iterator& it, difference_type n) { Iterator tmp = it;
tmp += n; return tmp;};
      friend Iterator operator+(difference_type n, const Iterator& it) { return it+n; };
      friend Iterator operator-(const Iterator& it, difference_type n) { Iterator tmp = it;
tmp -= n; return tmp;};
      //friend Iterator operator-(difference_type n, const Iterator& it) { return it-n; };
      friend difference_type operator-(const Iterator& it1,const Iterator& it2) { return it1.itptr - it2.itptr; };

   private:
      pointer itptr;
  };
  Iterator begin() { return Iterator(&ptr_[0]); }
  Iterator end()   { return Iterator(&ptr_[size_]); }
  /*T* begin() { return &ptr_[0]; }
  T* end()   { return &ptr_[size_]; }*/
  ~vector(){ delete [] ptr_; }
};

int main() {
  vector<int> v1;
  v1.push_back(3);
  std::cout << "Size of v1 is " << v1.size() << ", capacity is " << v1.capacity() << std::endl;
  std::cout << "Vector v1 content is:" << std::endl;
  for(const auto& el:v1){
    std::cout << el << " ";
  }
  std::cout << std::endl;

  v1.push_back(8);
  std::cout << "Size of v1 is " << v1.size() << ", capacity is " << v1.capacity() << std::endl;
  std::cout << "Vector v1 content is:" << std::endl;
  for(const auto& el:v1){
    std::cout << el << " ";
  }
  std::cout << std::endl;

  v1.push_back(7);
  std::cout << "Size of v1 is " << v1.size() << ", capacity is " << v1.capacity() << std::endl;
  std::cout << "Vector v1 content is:" << std::endl;
  for(const auto& el:v1){
    std::cout << el << " ";
  }
  std::cout << std::endl;

   std::cout << std::endl;
  v1.pop_back();
  std::cout << "Size of v1 is " << v1.size() << ", capacity is " << v1.capacity() << std::endl;
  std::cout << "Vector v1 content is:" << std::endl;
  for(const auto& el:v1){
    std::cout << el << " ";
  }
  std::cout << std::endl;
  v1.pop_back();
  std::cout << "Size of v1 is " << v1.size() << ", capacity is " << v1.capacity() << std::endl;
  std::cout << "Vector v1 content is:" << std::endl;
  for(const auto& el:v1){
    std::cout << el << " ";
  }
  std::cout << std::endl;
  v1.push_back(4);
  std::cout << "Size of v1 is " << v1.size() << ", capacity is " << v1.capacity() << std::endl;
  std::cout << "Vector v1 content is:" << std::endl;
  for(const auto& el:v1){
    std::cout << el << " ";
  }
  std::cout << std::endl;

  std::cout << std::endl;
  std::cout << "Checking copy ctor and copy assignment\n";
  vector<int> v2(v1);
  std::cout << "Vector v2 content is:" << std::endl;
  for(const auto& el:v2){
    std::cout << el << " ";
  }
  std::cout << std::endl;
  vector<int> v3 = v2;
  std::cout << "Vector v4 content is:" << std::endl;
  for(const auto& el:v3){
    std::cout << el << " ";
  }
  std::cout << std::endl;

  std::cout << std::endl;
  std::cout << "Checking element access and modification\n";
  vector<int> v4{1,2,3,4,5}; //OK!
  //vector<int> v4 = {1,2,3,4,5}; //OK!
  //vector<int> v4({1,2,3,4,5}); //OK!
  std::cout << "Size of v4 is " << v4.size() << ", capacity is " << v4.capacity() << std::endl;
  std::cout << "Vector v4 content is:" << std::endl;
  for(const auto& el:v4){
    std::cout << el << " ";
  }
  std::cout << std::endl;
  std::cout << "Vector v4 has this element at position 3: " << v4.at(3) << std::endl;
  v4.at(3) = 7;
  std::cout << "Vector v4 has now this element at position 3: " << v4.at(3) << std::endl;
  std::cout << "Vector v4 has this element at position 10: " << v4.at(10) << std::endl;
}

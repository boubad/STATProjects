#pragma once
#ifndef __MATELEM_RESULT_H__
#define __MATELEM_RESULT_H__
//////////////////////////
#include <cassert>
#include <vector>
#include <memory>
///////////////////////////////
namespace info {
  //////////////////////////////////
  template <typename INDEXTYPE, typename CRITERIATYPE>
  class MatElemResult {
  public:
    using index_type = INDEXTYPE;
    using criteria_type = CRITERIATYPE;
    using sizets_vector = std::vector<index_type>;
    using matelemresult_type = MatElemResult<index_type,criteria_type>;
    using matelemresult_type_ptr = std::shared_ptr<matelemresult_type>;
  private:
    criteria_type m_crit;
    sizets_vector m_index;
  public:
    MatElemResult():m_crit(0){}
    template <typename U, typename X>
    MatElemResult(const X &crit, const std::vector<U> &oInds):m_crit(0){
      this->m_crit = (criteria_type)crit;
      const size_t n = oInds.size();
      sizets_vector &v = this->m_index;
      v.resize(n);
      for (size_t i = 0; i < n; ++i){
	v[i] = (index_type)oInds[i];
      }// i
    }// MatElemRezsult
    MatElemResult(const matelemresult_type  &other){
      this->m_crit = other.m_crit;
      const sizets_vector &src = other.m_index;
      const size_t n =  src.size();
      sizets_vector &dest = this->m_index;
      dest.resize(n);
      for (size_t i = 0; i < n; ++i){
	dest[i] = src[i];
      }
    }
    matelemresult_type  & operator=(const matelemresult_type  &other){
      if (this != &other){
	 this->m_crit = other.m_crit;
      const sizets_vector &src = other.m_index;
      const size_t n =  src.size();
      sizets_vector &dest = this->m_index;
      dest.resize(n);
      for (size_t i = 0; i < n; ++i){
	dest[i] = src[i];
      }
      }
      return (*this);
    }
    virtual ~MatElemResult(){}
    bool operator<(const matelemresult_type &other) const {
      return (this->m_crit < other.m_crit);
    }// operator<
    bool operator==(const matelemresult_type &other) const {
      return (this->m_crit == other.m_crit);
    }// operator==
    std::ostream & write_to(std::ostream &os) const{
      os << "CRIT: " << this->m_crit << " [";
      const sizets_vector &v = this->m_index;
      const size_t n = v.size();
      for (size_t i = 0; i < n; ++i){
	if (i != 0){
	  os << ", ";
	}
	os << v[i];
      }// i
      os << "]";
      return (os);
    }// write_to
    std::wostream & write_to(std::wostream &os) const{
      os << L"CRIT: " << this->m_crit << L" [";
      const sizets_vector &v = this->m_index;
      const size_t n = v.size();
      for (size_t i = 0; i < n; ++i){
	if (i != 0){
	  os << L", ";
	}
	os << v[i];
      }// i
      os << L"]";
      return (os);
    }// write_to
  public:
    bool is_valid(void) const {
      return ((this->m_crit > 0) && (this->m_index.size()  > 0));
    }// is_valid
    criteria_type criteria(void) const {
      return (this->m_crit);
    }
    template <typename X>
    void criteria(const X &c){
      this->m_crit = c;
    }
    const sizets_vector & indexes(void) const {
      return (this->m_index);
    }
    void permute(size_t i, size_t j){
      sizets_vector &v = this->m_index;
      const size_t n = v.size();
      assert(i < n);
      assert(j < n);
      index_type t = v[i];
      v[i] = v[j];
      v[j] = t;
    }// permute
     template <typename U, typename X>
     void set(const X &crit, const std::vector<U> &oInds){
       this->m_crit = (criteria_type)crit;
      const size_t n = oInds.size();
      sizets_vector &v = this->m_index;
      v.resize(n);
      for (size_t i = 0; i < n; ++i){
	v[i] = (index_type)oInds[i];
      }// i
     }// set
     template <typename U, typename X>
     static matelemresult_type_ptr create(const X &crit, const std::vector<U> &oInds){
       return (std::make_shared<matelemresult_type>(crit,oInds));
     }// create
  };
  ////////////////////////
} // namespace info
/////////////////////////////////
#endif  //__MATELEM_RESULT_H__

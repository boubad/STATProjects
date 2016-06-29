#pragma once
#ifndef __INDIV_H__
#define __INDIV_H__
////////////////////////////////////
#include <cassert>
#include <string>
#include <memory>
/////////////////////////////////////
namespace info {
  ///////////////////////////////
  template <typename INDEXTYPE, typename DATATYPE,typename STRINGTYPE>
  class Indiv {
  public:
    using string_type = STRINGTYPE;
    using index_type = INDEXTYPE;
    using data_type = DATATYPE;
    //
    using IndivType = Indiv<index_type,data_type,string_type>;
  protected:
     index_type m_index;
     size_t m_ncols;
     std::unique_ptr<data_type> m_center;
     string_type m_sigle;
     //
     Indiv():m_index(0),m_ncols(0){}
  private:
      Indiv(const IndivType &) = delete;
      IndivType & operator=(const IndivType &) = delete;
  public:
    template <typename X>
    Indiv(index_type aIndex,size_t nCols, const X &pxdata,const string_type &sSigle = string_type()):
    m_index(aIndex),m_ncols(nCols),m_center(new data_type[nCols]),m_sigle(sSigle){
      assert(nCols > 0);
      data_type *p = this->m_center.get();
      assert(p != nullptr);
      for (size_t i = 0; i < nCols; ++i){
	p[i] = (data_type)pxdata[i];
      }// i
    }// Indiv
    virtual ~Indiv(){
    }
    index_type id(void) const {
      return (this->m_index);
    }
    size_t size(void) const {
      assert(this->m_ncols > 0);
      return (this->m_ncols);
    }
    string_type sigle(void) const {
      return (this->m_sigle);
    }
    const data_type *center(void) const {
      assert(this->m_center.get() != nullptr);
      return (this->m_center.get());
    }
    template <typename F>
    void distance(const IndivType &other, F &res) const {
      const size_t n = this->size();
      assert(n == other.size());
      const data_type *p1 = this->center();
      const data_type *p2 = other.center();
      res = 0;
      for (size_t i = 0; i < n; ++i){
	F x = (F)(p1[i] - p2[i]);
	res = (F)(res + x * x);
      }// i
    }// distance
  };// class Indiv<INDEXTYPE,DATATYPE,STRINGTYPE>
  //////////////////////////////////
}// namespace info
////////////////////////////////////
#endif // __INDIV_H__

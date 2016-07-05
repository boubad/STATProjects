#pragma once
#ifndef __INDEXEDMATDATA_H__
#define __INDEXEDMATDATA_H__
///////////////////////////////
#include "matdata.h"
#include "matelem_result.h"
//////////////////////
namespace info {
//////////////////////////////
template <typename INDEXTYPE, typename FLOATTYPE, 
	typename DISTANCETYPE, typename STRINGTYPE>
	class IndexedMatData {
	public:
		using index_type = INDEXTYPE;
		using data_type = FLOATTYPE;
		using distance_type = DISTANCETYPE;
		using string_type = STRINGTYPE;
		//
		using sizets_vector = std::vector<index_type>;
		using matdata_type = MatData<index_type, data_type, distance_type,string_type>;
		using indexedmatdata_type = IndexedMatData<index_type, data_type, distance_type,string_type>;
	private:
	  matdata_type *m_pdata;
	  sizets_vector m_colindex;
	  sizets_vector m_rowindex;
	public:
	  IndexedMatData():m_pdata(nullptr){}
	  IndexedMatData(matdata_type *pdata):m_pdata(pdata){
	    assert(pdata != nullptr);
	    assert(pdata->is_valid());
	    const size_t nCols = pdata->cols();
	    sizets_vector &v = this->m_colindex;
	    v.resize(nCols);
	    for (size_t i = 0; i < nCols; ++i){
	      v[i] = (index_type)i;
	    }// i
	    const size_t nRows = pdata->rows();
	    sizets_vector &vv = this->m_rowindex;
	    vv.resize(nRows);
	    for (size_t i = 0; i < nRows; ++i){
	      vv[i] = (index_type)i;
	    }// i
	  }
	  IndexedMatData(const indexedmatdata_type &other):m_pdata(other.m_pdata){
	    const sizets_vector &sv = other.m_colindex;
	    const size_t nCols = sv.size();
	    sizets_vector &v = this->m_colindex;
	    v.resize(nCols);
	    for (size_t i = 0; i < nCols; ++i){
	      v[i] = sv[i];
	    }// i
	    const sizets_vector &ssv = other.m_rowindex;
	    const size_t nRows = ssv.size();;
	    sizets_vector &vv = this->m_rowindex;
	    vv.resize(nRows);
	    for (size_t i = 0; i < nRows; ++i){
	      vv[i] = ssv[i];
	    }// i
	  }//
	  indexedmatdata_type & operator=(const indexedmatdata_type &other){
	    if (this != &other){
	      this->m_pdata = other.m_pdata;
	       const sizets_vector &sv = other.m_colindex;
	    const size_t nCols = sv.size();
	    sizets_vector &v = this->m_colindex;
	    v.resize(nCols);
	    for (size_t i = 0; i < nCols; ++i){
	      v[i] = sv[i];
	    }// i
	    const sizets_vector &ssv = other.m_rowindex;
	    const size_t nRows = ssv.size();;
	    sizets_vector &vv = this->m_rowindex;
	    vv.resize(nRows);
	    for (size_t i = 0; i < nRows; ++i){
	      vv[i] = ssv[i];
	    }// i
	    }
	    return (*this);
	  }// operator=
	  virtual ~ IndexedMatData(){}
	public:
	   bool is_valid(void) const {
	     return (this->m_pdata != nullptr) && this->m_pdata->is_valid() &&
	     (this->m_colindex.size() >= this->m_pdata->cols()) &&
	     (this->m_rowindex.size() >= this->m_pdata->rows());
	   }	// is_valid
	   size_t rows(void) const {
	      assert(this->is_valid());
	      return (this->m_pdata->rows());;
		}	// rows
		size_t cols(void) const {
		  assert(this->is_valid());
		  return (this->m_pdata->cols());
		}	// cols
	     data_type get_data(const size_t irow, const size_t icol) const {
		      assert(this->is_valid());
		      assert(irow < this->rows());
		      index_type ii = this->m_rowindex[irow];
			const size_t nCols = this->cols();
			assert(icol < nCols);
			index_type jj = this->m_colindex[icol];
			return (this->m_pdata->get_data(ii,jj));
		}	// get_value
		data_type operator()(const size_t irow, const size_t icol) const {
		  assert(this->is_valid());
			return (this->get_value(irow, icol));
		}	// operator()
		string_type get_row_name(const size_t irow) const {
		  assert(this->is_valid());
			 assert(irow < this->rows());
		      index_type ii = this->m_rowindex[irow];
		      return (this->m_pdata->get_row_name(ii));
		}	// row_name
		string_type get_col_name(const size_t icol) const {
		   assert(this->is_valid());
			const size_t nCols = this->cols();
			assert(icol < nCols);
			index_type jj = this->m_colindex[icol];
			return (this->m_pdata->get_col_name(jj));
		}	// row_name
		template <typename X>
		void col_indexes(std::vector<X> &oInds) const {
		  const sizets_vector &v = this->m_colindex;
		  const size_t n = this->cols();
		  oInds.resize(n);
		  for (size_t i = 0; i < n; ++i){
		    oInds[i] = (X)v[i];
		  }// i
		}// colindex
		template <typename X>
		void col_indexes(const std::vector<X> &oInds){
		  sizets_vector &v = this->m_colindex;
		  const size_t n = this->cols();
		  assert(oInds.size() >= n);
		  v.resize(n);
		  for (size_t i = 0; i < n; ++i){
		    v[i] = (index_type)oInds[i];
		  }// i
		}// colindex
		 template <typename X, typename CRIT>
		 void col_indexes(std::shared_ptr<MatElemResult<X,CRIT> > oPtr){
		 MatElemResult<X,CRIT> *p = oPtr.get();
		 if (p != nullptr){
		   this->col_indexes(p->indexes());
		 }
		}// colindex
		template <typename X>
		void row_indexes(std::vector<X> &oInds) const {
		  const sizets_vector &v = this->m_rowindex;
		  const size_t n = this->rows();
		  oInds.resize(n);
		  for (size_t i = 0; i < n; ++i){
		    oInds[i] = (X)v[i];
		  }// i
		}// rowindex
		template <typename X>
		void row_indexes(const std::vector<X> &oInds){
		  sizets_vector &v = this->m_rowindex;
		  const size_t n = this->rows();
		  assert(oInds.size() >= n);
		  v.resize(n);
		  for (size_t i = 0; i < n; ++i){
		    v[i] = (index_type)oInds[i];
		  }// i
		}// rowindex
		template <typename X, typename CRIT>
		 void row_indexes(std::shared_ptr<MatElemResult<X,CRIT> >  oPtr){
		 MatElemResult<X,CRIT> *p = oPtr.get();
		 if (p != nullptr){
		   this->row_indexes(p->indexes());
		 }
		}// colindex
		template <typename X, typename CRIT>
		void indexes(const std::pair<std::shared_ptr<MatElemResult<X,CRIT> > ,
			     std::shared_ptr<MatElemResult<X,CRIT> > > &oPair){
		  this->row_indexes(oPair.first);
		  this->col_indexes(oPair.second);
		}//indexes
	}; // class IndexedMatData
	///////////////////////////////////
}// namespace info
////////////////////////////////
#endif // __INDEXEDMATDATA_H__

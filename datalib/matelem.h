#pragma once
#ifndef __MATELEM_H__
#define __MATELEM_H__
/////////////////////////////
#include "treeelem.h"
//////////////////////
#include <queue>
#include <iostream>
////////////////////////
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
template <typename INDEXTYPE,typename DISTANCETYPE, typename CRITERIATYPE>
	class MatElem : CancellableObject {
	public:
		using index_type = INDEXTYPE;
		using criteria_type = CRITERIATYPE;
		using distance_type = DISTANCETYPE;
		using sizets_vector = std::vector<index_type>;
		using distancemap_type = DistanceMap<index_type,distance_type>;
		using cancellableflag_type = CancellableObject::cancellableflag_type;
		//
		using pair_type = std::pair<size_t, size_t>;
		using pairs_type_vector = std::queue<pair_type>;
		using matelemresult_type = MatElemResult<index_type,criteria_type>;
                using matelemresult_type_ptr = std::shared_ptr<matelemresult_type>;
		using task_type = std::future<matelemresult_type_ptr>;
		using matelem_type = MatElem<index_type,distance_type,criteria_type>;
	private:
		distancemap_type *m_pdist;
		matelemresult_type m_res;
	protected:
	  MatElem(const matelem_type &other): m_pdist(other.m_pdist),m_res(other.m_res){}
	  matelem_type & operator=(const matelem_type &other){
	    if (this != &other){
	      this->m_pdist = other.m_pdist;
	      this->m_res = other.m_res;
	    }
	  }
	  bool find_best_permutations(pair_type &v, criteria_type &bestCrit)  {
		const sizets_vector &inds = this->m_res.indexes();
		const size_t n = inds.size();
		v.first = 0;
		v.second = 0;
		const distancemap_type *pMap = this->m_pdist;
		for (size_t i = 0; i < n; ++i) {
		  if (this->is_cancellation_requested()){
		      return (false);
		}
		for (size_t j = 0; j < i; ++j) {
		if (this->is_cancellation_requested()) {
		    return (false);
		}
		matelemresult_type xres(this->m_res);
		xres.permute(i,j);
		criteria_type c = 0;
		pMap->compute_criteria(xres.indexes(), c);
		if ((c < bestCrit) && (v.first == v.second)){
		  v.first = j;
		  v.second = i;
		  bestCrit = c;
		} else if (c < bestCrit){
		  v.first = j;
		  v.second = i;
		  bestCrit = c;
		}
	  }// j
	 }// i
	 if (this->is_cancellation_requested()){
	   return (false);
	 }
	return (v.first != v.second);
	}//find_best_permutations
	public:
	template <typename FLOATTYPE,typename STRINGTYPE>
	MatElem(MatData<index_type,FLOATTYPE,distance_type,STRINGTYPE> *pMat,
		DispositionType disp = DispositionType::dispRow,
		cancellableflag_type *pf = nullptr):CancellableObject(pf),m_pdist(nullptr){
		  assert(pMat != nullptr);
		  assert(pMat->is_valid());
		  if (disp == DispositionType::dispRow){
		    this->m_pdist = pMat->get_rows_distances_map();
		  } else {
		    this->m_pdist = pMat->get_cols_distances_map();
		  }
		  sizets_vector oinds;
		  this->m_pdist->get_indexes(oinds);
		  criteria_type c = 0;
		  this->m_pdist->compute_criteria(oinds, c);
		  this->m_res.set(c,oinds);
	}// MatElem
	  MatElem(distancemap_type *pMap,cancellableflag_type *pf = nullptr) :
	  CancellableObject(pf),m_pdist(pMap){
			assert(pMap != nullptr);
			assert(pMap->is_valid());
			sizets_vector oinds;
			pMap->get_indexes(oinds);
			criteria_type c = 0;
			pMap->compute_criteria(oinds, c);
			this->m_res.set(c,oinds);
		}// MatElem
		virtual ~MatElem() {}
	public:
	  matelemresult_type_ptr get_result(void) {
			return (std::make_shared<matelemresult_type>(this->m_res));
		}// get_result
	matelemresult_type_ptr arrange(void) {
			bool done = false;
			matelemresult_type oRet;
			while (!done) {
			  if (this->is_cancellation_requested()){
			    done = true;
			    break;
			  }
			pair_type v;
			criteria_type bestCrit = this->m_res.criteria();
			if (!this->find_best_permutations(v, bestCrit)) 
			   {
					done = true;
					break;
			    }
			if (v.first == v.second) {
				done = true;
				break;
			  }
			size_t iFirst = v.first;
			size_t jFirst = v.second;
			this->m_res.permute(iFirst,jFirst);
			this->m_res.criteria(bestCrit);
			}// not done
			if (this->is_cancellation_requested()){
			  return (matelemresult_type_ptr());
			}
			return (this->get_result());
		}// arrange
		
	  static matelemresult_type_ptr st_arrange(const distancemap_type *pMap,
	    cancellableflag_type *pf = nullptr
	  ){
	    matelem_type oMat(pMap,pf);
	    return oMat.arrange();
	  }// create
	 template <typename FLOATTYPE,typename STRINGTYPE>
	 static matelemresult_type_ptr st_arrange_matdata(const MatData<index_type,FLOATTYPE,distance_type,STRINGTYPE> *pMat,
		DispositionType disp = DispositionType::dispRow,
		cancellableflag_type *pf = nullptr){
	    matelem_type oMat(pMat,disp,pf);
	    return oMat.arrange();
	 }// create
	 template <typename FLOATTYPE,typename STRINGTYPE>
	 static matelemresult_type_ptr st_arrange_hierar(MatData<index_type,FLOATTYPE,distance_type,STRINGTYPE> *pMat,
		DispositionType disp = DispositionType::dispRow,
		cancellableflag_type *pf = nullptr){
	   MatTree<index_type,FLOATTYPE,distance_type,STRINGTYPE> oTree(pMat,disp,pf);
	   if (!oTree.aggreg()){
	     return (matelemresult_type_ptr());
	   }
	   sizets_vector oinds;
	   oTree.get_ids(oinds);
	   matelem_type oMat(pMat,disp,pf);
	   criteria_type c = oMat.m_res.criteria();
	   oMat.m_res.set(c,oinds);
	   return oMat.arrange();
	 }// create
	}; // class MatElem
	//////////////////////////////////
}// namespace info
/////////////////////////////
#endif // __MATELEM_H__

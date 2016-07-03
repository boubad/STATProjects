#pragma once
#ifndef __TREEELEM_H__
#define __TREEELEM_H___
/////////////////////////////////////
#include "cancellable_object.h"
#include "indiv.h"
#include "matdata.h"
///////////////////////////////
#include <map>
#include <set>
#include <algorithm>
//////////////////////////////
namespace info {
////////////////////////////////////
template<typename INDEXTYPE,typename DATATYPE, typename DISTANCETYPE,typename STRINGTYPE>
class TreeItem  : public Indiv<INDEXTYPE,DATATYPE,STRINGTYPE> {
public:
	using index_type  = INDEXTYPE;
	using data_type = DATATYPE;
	using distance_type = DISTANCETYPE;
	using string_type = STRINGTYPE;
	//
	using indiv_type = Indiv<index_type,data_type,string_type>;
	using cancellableflag_type = CancellableObject::cancellableflag_type;
	using treeitem_type = TreeItem<index_type,data_type,distance_type,string_type>;
	using treeitem_type_ptr = std::shared_ptr<treeitem_type>;
	using ints_sizet_map = std::map<index_type,size_t>;
	using ints_vector = std::vector<index_type>;
private:
	treeitem_type_ptr m_left;
	treeitem_type_ptr m_right;
public:
	TreeItem(const treeitem_type &other):indiv_type(other),m_left(other.m_left),
	m_right(other.m_right){}
	treeitem_type & operator=(const treeitem_type &other){
	  if (this != &other){
	    index_type::operator=(other);
	    this->m_left = other.m_left;
	    this->m_right = other.m_right;
	  }
	  return (*this);
	}
	template <typename X>
	TreeItem(index_type aIndex,size_t nCols, const X &pxdata,
	  const string_type &sSigle = string_type(),cancellableflag_type *pf = nullptr) : 
	indiv_type(aIndex,nCols,pxdata,sSigle,pf) {
	 assert(aIndex != 0); 
	}
	TreeItem(treeitem_type_ptr left, treeitem_type_ptr right,
	  cancellableflag_type *pf = nullptr):indiv_type(pf),m_left(left),m_right(right){
		treeitem_type *pLeft = left.get();
		assert(pLeft != nullptr);
		treeitem_type *pRight = right.get();
		assert(pRight != nullptr);
		assert(pLeft != pRight);
		const size_t nCols = pLeft->size();
		assert(pRight->size() == nCols);
		this->m_ncols = nCols;
		this->m_center.reset(new data_type[nCols]);
		data_type *p = this->m_center.get();
		assert(p != nullptr);
		const data_type *p1 = pLeft->center();
		const data_type *p2 = pRight->center();
		for (size_t i = 0; i < nCols; ++i){
		  p[i] = (data_type)((p1[i] + p2[i]) / 2.0);
		}// i
	} // TreeItem
	virtual ~TreeItem() {
	}
public:
	bool is_leaf(void) const {
		return ((this->m_left.get() == nullptr) || (this->m_right.get() == nullptr));
	}
	treeitem_type *left(void) const {
		return (this->m_left.get());
	}
	treeitem_type *right(void) const {
		return (this->m_right.get());
	}
	template <typename XK,typename XV>
	void get_map(std::map<XK,XV> &oMap, const XV val) {
	  if (this->is_cancellation_requested()){
	    return;
	  }
	    if (this->is_leaf()) {
		  XK key = (XK)this->id();
		  oMap[key] = val;
	    } else {
	    this->left()->get_map(oMap, val);
	    this->right()->get_map(oMap, val);
	    }
	} // get_map
	template <typename X>
	void get_ids(std::vector<X> &oVec)  {
	   if (this->is_cancellation_requested()){
	    return;
	  }
		if (this->is_leaf()) {
		       X ind = (X)this->id();
			oVec.push_back(ind);
		} else {
		  this->left()->get_ids(oVec);
		  this->right()->get_ids(oVec);
		}
	} // get_map
};
// class TreeItem<U>
/////////////////////////////////////////
template<typename INDEXTYPE,typename DATATYPE, typename DISTANCETYPE, typename STRINGTYPE>
class MatTree : public CancellableObject {
public:
  using index_type  = INDEXTYPE;
  using data_type = DATATYPE;
  using distance_type = DISTANCETYPE;
  using string_type = STRINGTYPE;
  using cancellableflag_type = CancellableObject::cancellableflag_type;
	//
  using treeitem_type = TreeItem<index_type,data_type,distance_type,string_type>;
  using treeitem_type_ptr = std::shared_ptr<treeitem_type>;
  using ints_sizet_map = std::map<index_type,size_t>;
  using ints_vector = std::vector<index_type>;
  using treeitems_vector = std::vector<treeitem_type_ptr>;
  using matricedata_type  = MatData<index_type, data_type, distance_type,string_type>;
  //
  using mattree_type = MatTree<index_type,data_type,distance_type,string_type>;
  using pair_type = std::pair<size_t, size_t>;
private:
  treeitems_vector m_items;
protected:
   bool find_best_aggreg(pair_type &oPair)  {
        const treeitems_vector &v = this->m_items;
	const size_t n = v.size();
        oPair.first = 0;
        oPair.second = 0;
        distance_type best  = 0;
	for (size_t i = 0; i < n; ++i){
	  if (this->is_cancellation_requested()){
	    return (false);
	  }
	  treeitem_type *p1 = (v[i]).get();
	  assert(p1 != nullptr);
	  for (size_t j = 0; j < i; ++j){
	      treeitem_type *p2 = (v[j]).get();
	      assert(p2 != nullptr);
	      distance_type cur = 0;
	      p1->distance(*p2,cur);
	      if (this->is_cancellation_requested()){
		return (false);
	      }
	      if (oPair.first == oPair.second){
	          best = cur;
	          oPair.first = j;
	          oPair.second = i;
	      } else if (cur < best){
	          best = cur;
	          oPair.first = j;
	          oPair.second = i;
	        }
            }// j
       }// i
       if (this->is_cancellation_requested()){
	 return (false);
       }
     return (oPair.first != oPair.second);
  }// find_best_aggreg
   bool aggreg_one_step(void){
      treeitems_vector &v = this->m_items;
      size_t n = v.size();
      if (n < 2){
	return (false);
      }
      pair_type oPair;
      if (!this->find_best_aggreg(oPair)){
	return (false);
      }
      size_t i1 = oPair.first;
      size_t i2 = oPair.second;
      assert(i1 != i2);
      assert(i1 < n);
      assert(i2 < n);
      treeitem_type_ptr left = v[i1];
      treeitem_type *pLeft = left.get();
      assert(pLeft != nullptr);
      treeitem_type_ptr right = v[i2];
      treeitem_type *pRight = right.get();
      assert(pRight != nullptr);
      auto it1 = std::find_if(v.begin(),v.end(),[pLeft](treeitem_type_ptr o)->bool{
	return (o.get() == pLeft);
      });
      assert(it1 != v.end());
      v.erase(it1);
      auto it2 = std::find_if(v.begin(),v.end(),[pRight](treeitem_type_ptr o)->bool{
	return (o.get() == pRight);
      });
      assert(it2 != v.end());
      v.erase(it2);
      treeitem_type_ptr oPtr = std::make_shared<treeitem_type>(left,right);
      assert(oPtr.get() != nullptr);
      v.push_back(oPtr);
      return (true);
  }// aggreg_one_step
public:
  MatTree(){}
  MatTree(const mattree_type &other):CancellableObject(other),m_items(other.m_items){}
  mattree_type & operator=(const mattree_type &other){
    if (this != &other){
      CancellableObject::operator=(other);
      this->m_items = other.m_items;
    }
    return (*this);
  }
  MatTree(matricedata_type *pData, 
	  DispositionType disp = DispositionType::dispRow,
	  cancellableflag_type *pf = nullptr):CancellableObject(pf){
   this->init(pData,disp);
  }// MatTree
  virtual ~MatTree(){
  }
public:
  void clear(void){
    this->m_items.clear();
  }// clear
  const treeitems_vector & items(void) const {
    return (this->m_items);
  }// items
  void init(matricedata_type *pData, DispositionType disp = DispositionType::dispRow){
    assert(pData != nullptr);
    assert(pData->is_valid());
    const size_t nRows = pData->rows();
    const size_t nCols = pData->cols();
    this->clear();
    treeitems_vector &v = this->m_items;
    cancellableflag_type *pf = this->get_cancellable_flag();
    if (disp == DispositionType::dispRow){
      for (size_t i = 0; i < nRows; ++i){
	index_type aIndex = (index_type)(i + 1);
	string_type sigle = pData->get_row_name(i);
	std::vector<data_type> data(nCols);
	for (size_t j = 0; j < nCols; ++j){
	  data[j] = (data_type)pData->get_data(i,j);
	}// j
	treeitem_type_ptr p = std::make_shared<treeitem_type>(aIndex,nCols,data,sigle,pf);
	assert(p.get() != nullptr);
	v.push_back(p);
      }// i
    } else if (disp == DispositionType::dispCol){
       for (size_t i = 0; i < nCols; ++i){
	index_type aIndex = (index_type)(i + 1);
	string_type sigle = pData->get_col_name(i);
	std::vector<data_type> data(nRows);
	for (size_t j = 0; j < nRows; ++j){
	  data[j] = (data_type)pData->get_data(j,i);
	}// j
	treeitem_type_ptr p = std::make_shared<treeitem_type>(aIndex,nCols,data,sigle,pf);
	assert(p.get() != nullptr);
	v.push_back(p);
      }// i
    }
  }// init
  bool aggreg(const size_t nc = 1){
    assert(nc > 0);
    bool done = false;
    while (!done){
       if (this->is_cancellation_requested()){
	 return (false);
       }
      if (this->m_items.size() <= nc){
	done = true;
	break;
      }
      if (!this->aggreg_one_step()){
	done = true;
	break;
      }
    }// done
    return (!this->is_cancellation_requested());
  }// aggreg
  template <typename XK,typename XV>
	void get_map(std::map<XK,XV> &oMap) {
		oMap.clear();
		const treeitems_vector &v = this->m_items;
		const size_t n = v.size();
		for (size_t i = 0; i < n; ++i){
		  XV val = (XV)(i + 1 );
		  treeitem_type *p = (v[i]).get();
		  assert(p != nullptr);
		  p->get_map(oMap, val);
		}// i
	} // get_map
	template <typename X>
	void get_ids(std::vector<X> &oIds) {
		oIds.clear();
		const treeitems_vector &v = this->m_items;
		const size_t n = v.size();
		for (size_t i = 0; i < n; ++i){
		  treeitem_type *p = (v[i]).get();
		  assert(p != nullptr);
		  p->get_ids(oIds);
		}// i
	} // get_map
	static bool getAllIndexes(ints_vector &oIds,
		matricedata_type *pData, 
		DispositionType disp = DispositionType::dispRow,
		cancellableflag_type *pf = nullptr){
	  mattree_type oTree(pData, disp,pf);
	  if (!oTree.aggreg()){
	    return (false);
	  }
	  oTree.get_ids(oIds);
	  return (true);
	}// getAllIndexes
};// class MatTree
/////////////////////////////////////////
}// namespace info
////////////////////////////////////////
#endif // !__INDIVTREE_H__

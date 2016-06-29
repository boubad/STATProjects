#pragma once
#ifndef __INDIVTREE_H__
#define __INDIVTREE_H__
/////////////////////////////////////
#include "indiv.h"
#include "matdata.h"
///////////////////////////////
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <atomic>
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
	using IndivType = Indiv<index_type,data_type,string_type>;
	using TreeItemType = TreeItem<index_type,data_type,distance_type,string_type>;
	using PTreeItemType = TreeItemType *;
	using ints_sizet_map = std::map<index_type,size_t>;
	using ints_vector = std::vector<index_type>;
	
private:
	TreeItemType *m_pleft;
	TreeItemType *m_pright;
	//
	TreeItem(const TreeItemType &) = delete;
	TreeItemType & operator=(const TreeItemType &) = delete;
public:
	template <typename X>
	TreeItem(index_type aIndex,size_t nCols, const X &pxdata,
	  const string_type &sSigle = string_type()) : 
	IndivType(aIndex,nCols,pxdata,sSigle),m_pleft(nullptr),m_pright(nullptr) {
	 assert(aIndex != 0); 
	}
	TreeItem(TreeItemType *pLeft, TreeItemType *pRight) :
	m_pleft(pLeft),m_pright(pRight) {
		assert(pLeft != nullptr);
		assert(pRight != nullptr);
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
		delete this->m_pleft;
		delete this->m_pright;
	}
public:
	bool is_leaf(void) const {
		return ((this->m_pleft == nullptr) && (this->m_pright == nullptr));
	}
	const TreeItemType *left(void) const {
		return (this->m_pleft);
	}
	const TreeItemType *right(void) const {
		return (this->m_pright);
	}
	void get_map(ints_sizet_map &oMap, const size_t val) const {
		if (this->is_leaf()) {
		  oMap[this->m_index] = val;
		return;
		}
		if (this->m_pleft != nullptr) {
			this->m_pleft->get_map(oMap, val);
		}
		if (this->m_pright != nullptr) {
			this->m_pright->get_map(oMap, val);
		}
	} // get_map
	void get_ids(ints_vector &oVec) const {
		if (this->is_leaf()) {
			oVec.push_back(this->m_index);
			return;
		}
		if (this->m_pleft != nullptr) {
			this->m_pleft->get_ids(oVec);
		}
		if (this->m_pright != nullptr) {
			this->m_pright->get_ids(oVec);
		}
	} // get_map
};
// class TreeItem<U>
/////////////////////////////////////////
template<typename INDEXTYPE,typename DATATYPE, typename DISTANCETYPE, typename STRINGTYPE>
class MatTree {
public:
  using index_type  = INDEXTYPE;
  using data_type = DATATYPE;
  using distance_type = DISTANCETYPE;
  using string_type = STRINGTYPE;
	//
  using IndivType = Indiv<index_type,data_type,string_type>;
  using TreeItemType = TreeItem<index_type,data_type,distance_type,string_type>;
  using PTreeItemType = TreeItemType *;
  using ints_sizet_map = std::map<index_type,size_t>;
  using ints_vector = std::vector<index_type>;
  using treeitems_vector = std::vector<PTreeItemType>;
  using DistanceMapType = DistanceMap<index_type, distance_type>;
  using MatDataType = MatData<index_type, data_type, distance_type,string_type>;
  //
  using MatTreeType = MatTree<index_type,data_type,distance_type,string_type>;
  using pair_type = std::pair<size_t, size_t>;
private:
  std::atomic<bool> m_cancel;
  treeitems_vector m_items;
  DistanceMapType m_dist;
  //
  MatTree(const MatTreeType &) = delete;
  MatTreeType & operator=(const MatTreeType &) = delete;
public:
  MatTree():m_cancel(false){}
  MatTree(const MatDataType *pData, DispositionType disp = DispositionType::dispRow):m_cancel(false){
   this->init(pData,disp);
  }// MatTree
  virtual ~MatTree(){
    this->clear();
  }
public:
  void clear(void){
    treeitems_vector &v = this->m_items;
    for (auto it = v.begin(); it != v.end(); ++it){
      PTreeItemType p = *it;
      delete p;
    }// it
    v.clear();
    this->m_dist.clear();
  }// clear
  void cancel(void){
    this->m_cancel.store(true);
  }// cancel
  void init(const MatDataType *pData, DispositionType disp = DispositionType::dispRow){
    assert(pData != nullptr);
    const size_t nRows = pData->rows();
    assert(nRows > 0);
    const size_t nCols = pData->cols();
    assert(nCols > 0);
    this->clear();
    treeitems_vector &v = this->m_items;
    if (disp == DispositionType::dispRow){
      for (size_t i = 0; i < nRows; ++i){
	index_type aIndex = (index_type)(i + 1);
	string_type sigle = pData->row_name(i);
	std::vector<data_type> data(nCols);
	for (size_t j = 0; j < nCols; ++j){
	  data[j] = (data_type)pData->get_value(i,j);
	}// j
	PTreeItemType p = new TreeItemType(aIndex,nCols,data,sigle);
	assert(p != nullptr);
	v.push_back(p);
      }// i
    } else if (disp == DispositionType::dispCol){
       for (size_t i = 0; i < nCols; ++i){
	index_type aIndex = (index_type)(i + 1);
	string_type sigle = pData->col_name(i);
	std::vector<data_type> data(nRows);
	for (size_t j = 0; j < nRows; ++j){
	  data[j] = (data_type)pData->get_value(j,i);
	}// j
	PTreeItemType p = new TreeItemType(aIndex,nRows,data,sigle);
	assert(p != nullptr);
	v.push_back(p);
      }// i
    }
    this->compute_distances();
  }// init
  bool aggreg(size_t nClasses = 5){
    bool done = false;
    while (!done){
      if (this->m_cancel.load()){
	return (false);
      }
      if (this->m_items.size() <= nClasses){
	done = true;
	break;
      }
      if (!this->aggreg_one_step()){
	if (this->m_cancel.load()){
	  return (false);
      }
	done = true;
	break;
      }
    }// done
    return (true);
  }// aggreg
  std::future<bool> aggregAsync(size_t nClasses = 5){
    return std::async(std::launch::async,[this,nClasses]()->bool{
      return (this->aggreg(nClasses));
    });
  }// aggregAsync
  void get_map(ints_sizet_map &oMap) const {
		oMap.clear();
		const treeitems_vector &v = this->m_items;
		const size_t n = v.size();
		for (size_t i = 0; i < n; ++i){
		  size_t val = (size_t)(i + 1 );
		  PTreeItemType p = v[i];
		  assert(p != nullptr);
		  p->get_map(oMap, val);
		}// i
	} // get_map
protected:
  void compute_distances(void){
    treeitems_vector &v = this->m_items;
     DistanceMapType &oMap = this->m_dist;
     oMap.clear();
     const size_t n = v.size();
     for (size_t i = 0; i < n; ++i){
       if (this->m_cancel.load()){
	 return;
       }
       PTreeItemType p1 = v[i];
       assert(p1 != nullptr);
       for (size_t j = 0; j < i; ++j){
	 PTreeItemType p2 = v[j];
	 assert(p2 != nullptr);
	 distance_type s = 0;
	 p1->distance(*p2, s);
	 oMap.add(j,i,s);
       }// j
     }// i
  }// compute_distances
  bool find_best_aggreg(pair_type &oPair) const {
        const treeitems_vector &v = this->m_items;
	const size_t n = v.size();
     const DistanceMapType &oMap = this->m_dist;
     oPair.first = 0;
     oPair.second = 0;
     distance_type best  = 0;
     for (size_t i = 0; i < n; ++i){
       if (this->m_cancel.load()){
	 return (false);
       }
       for (size_t j = 0; j < i; ++j){
	 distance_type cur = 0;
	 if (oMap.get(j,i,cur)){
	   if (oPair.first == oPair.second){
	     best = cur;
	     oPair.first = j;
	     oPair.second = i;
	   } else if (cur < best){
	     best = cur;
	     oPair.first = j;
	     oPair.second = i;
	   }
	 }// cur
       }// j
     }// i
     return ((oPair.first != oPair.second) && 
     (!this->m_cancel.load()));
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
      PTreeItemType pLeft = v[i1];
      assert(pLeft != nullptr);
      PTreeItemType pRight = v[i2];
      assert(pRight != nullptr);
      auto it1 = std::find(v.begin(),v.end(),pLeft);
      assert(it1 != v.end());
      v.erase(it1);
      auto it2 = std::find(v.begin(),v.end(),pRight);
      assert(it2 != v.end());
      v.erase(it2);
      PTreeItemType pNew = new TreeItemType(pLeft,pRight);
      assert(pNew != nullptr);
      v.push_back(pNew);
      this->compute_distances();
      return (true);
  }// aggreg_one_step
};// class MatTree
/////////////////////////////////////////
}// namespace info
////////////////////////////////////////
#endif // !__INDIVTREE_H__

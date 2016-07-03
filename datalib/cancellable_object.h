#pragma once
#ifndef __CANCELLABLE_OBJECT_H__
#define __CANCELLABLE_OBJECT_H__
///////////////////////////////
#include <atomic>
/////////////////////////////////
namespace info {
  //////////////////////
  class CancellableObject {
  public:
    using cancellableflag_type = std::atomic<bool>;
  private:
    cancellableflag_type *m_pcancel;
  public:
    CancellableObject(cancellableflag_type *pf = nullptr):m_pcancel(pf){}
    CancellableObject(const CancellableObject &other):m_pcancel(other.m_pcancel){}
    CancellableObject & operator=(const CancellableObject &other) {
      if (this != &other){
	this->m_pcancel = other.m_pcancel;
      }
      return (*this);
    }
    virtual ~CancellableObject(){}
    bool is_cancellation_requested(void){
      return ((this->m_pcancel != nullptr) && this->m_pcancel->load());
    }//is_cancellation_requested
    cancellableflag_type *get_cancellable_flag(void) const {
      return (this->m_pcancel);
    }// get_cancellable_flag
  }; // class CancellableObject
  ////////////////////////
}// namespace info
////////////////////////////////
#endif  // __CANCELLABLE_OBJECT_H__

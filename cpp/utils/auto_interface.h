////////////////////////////////////////////////////////////////////////////////
// Company:    AQIS                                                           //
// Author:     Valeri CHIBAEV (0412 586 556)                                  //
// Purpose:    wrapper class (similar to std::auto_ptr)						  //
//			   to insure that IUnknown interface will be released			  //
//			   when auto_interface goes out of scope or deleted				  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
// auto_interface.h: interface for the auto_interface class.
//
//////////////////////////////////////////////////////////////////////

/**
 * @author Chibaev Valeri
 *
 * IUnknown wrapper class ( modified copy of std::auto_ptr)
 * handle interface lifecycle
 *
 */

#if !defined(AFX_AUTO_INTERFACE_H__02BEED98_514D_4C88_9E63_D841A9F794C2__INCLUDED_)
#define AFX_AUTO_INTERFACE_H__02BEED98_514D_4C88_9E63_D841A9F794C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <unknwn.h>

class auto_interface {
public:
	typedef IUnknown element_type;
	explicit auto_interface(IUnknown *_P = 0) _THROW0()
		: _Owns(_P != 0), _Ptr(_P) {}
	auto_interface(const auto_interface & _Y) _THROW0()
		: _Owns(_Y._Owns), _Ptr(_Y.release()) {}
	auto_interface & operator=(const auto_interface & _Y) _THROW0()
		{if (this != &_Y)
			{if (_Ptr != _Y.get())
				{if (_Owns)
					_Ptr->Release();
				_Owns = _Y._Owns; }
			else if (_Y._Owns)
				_Owns = true;
			_Ptr = _Y.release(); }
		return (*this); }
	~auto_interface()
		{if (_Owns)
			_Ptr->Release(); }
	IUnknown& operator*() const _THROW0()
		{return (*get()); }
	IUnknown *operator->() const _THROW0()
		{return (get()); }
	IUnknown *get() const _THROW0()
		{return (_Ptr); }
	IUnknown *release() const _THROW0()
		{((auto_interface *)this)->_Owns = false;
		return (_Ptr); }
private:
	bool _Owns;
	IUnknown *_Ptr;
};

#endif // !defined(AFX_AUTO_INTERFACE_H__02BEED98_514D_4C88_9E63_D841A9F794C2__INCLUDED_)

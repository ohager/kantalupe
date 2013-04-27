// Copyright (c) 2005-2011 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD/e, an XML Schema
// to C++ data binding compiler for embedded systems.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
//

#ifndef XRS_PIMPL_HXX
#define XRS_PIMPL_HXX

#include <xsde/cxx/pre.hxx>

// Begin prologue.
//
//
// End prologue.

#ifndef XSDE_OMIT_PAGGR
#  define XSDE_OMIT_PAGGR
#  define XRS_PIMPL_HXX_CLEAR_OMIT_PAGGR
#endif

#include "xrs-pskel.hxx"

#include <xsde/cxx/stack.hxx>

class ResourceTypes_pimpl: public ResourceTypes_pskel
{
  public:
  ResourceTypes_pimpl ();

  virtual void
  pre ();

  virtual void
  _characters (const ::xsde::cxx::ro_string&);

  virtual void
  _post ();

  virtual ::ResourceTypes
  post_ResourceTypes ();

  public:
  struct ResourceTypes_pimpl_state
  {
    ::std::string str_;
  };

  ResourceTypes_pimpl_state ResourceTypes_pimpl_state_;
};

class xrs_pimpl: public xrs_pskel
{
  public:
  xrs_pimpl (bool = false);

  ~xrs_pimpl ();

  virtual void
  _reset ();

  virtual void
  pre ();

  // Attributes.
  //
  virtual void
  id (const ::std::string&);

  virtual void
  version (const ::std::string&);

  // Elements.
  //
  virtual void
  ResourceSet (::ResourceSet*);

  virtual ::xrs*
  post_xrs ();

  public:
  void
  pre_impl (::xrs*);

  public:
  struct xrs_pimpl_state
  {
    ::xrs* xrs_;
  };

  xrs_pimpl_state xrs_pimpl_state_;
  bool xrs_pimpl_base_;
};

class Resource_pimpl: public Resource_pskel
{
  public:
  Resource_pimpl ();

  virtual void
  pre ();

  // Attributes.
  //
  virtual void
  type (const ::ResourceTypes&);

  virtual void
  alias (const ::std::string&);

  virtual ::Resource
  post_Resource ();

  public:
  ::xml_schema::string_pimpl base_impl_;

  public:
  struct Resource_pimpl_state
  {
    ::Resource Resource_;
  };

  Resource_pimpl_state Resource_pimpl_state_;
};

class ResourceSet_pimpl: public ResourceSet_pskel
{
  public:
  ResourceSet_pimpl (bool = false);

  ~ResourceSet_pimpl ();

  virtual void
  _reset ();

  virtual void
  pre ();

  // Attributes.
  //
  virtual void
  prefix (const ::std::string&);

  // Elements.
  //
  virtual void
  Resource (const ::Resource&);

  virtual ::ResourceSet*
  post_ResourceSet ();

  public:
  void
  pre_impl (::ResourceSet*);

  public:
  struct ResourceSet_pimpl_state
  {
    ::ResourceSet* ResourceSet_;
  };

  ResourceSet_pimpl_state ResourceSet_pimpl_state_;
  bool ResourceSet_pimpl_base_;
};

#ifdef XRS_PIMPL_HXX_CLEAR_OMIT_PAGGR
#  undef XSDE_OMIT_PAGGR
#endif

#ifndef XSDE_OMIT_PAGGR

// Parser aggregate for the xrs element.
//
class xrs_paggr
{
  public:
  xrs_paggr ();

  void
  pre ()
  {
    this->xrs_p_.pre ();
  }

  ::xrs*
  post ()
  {
    return this->xrs_p_.post_xrs ();
  }

  ::xrs_pimpl&
  root_parser ()
  {
    return this->xrs_p_;
  }

  static const char*
  root_name ();

  static const char*
  root_namespace ();

  void
  reset ()
  {
    this->xrs_p_._reset ();
  }

  public:
  ::xrs_pimpl xrs_p_;
  ::xml_schema::string_pimpl string_p_;
  ::ResourceTypes_pimpl ResourceTypes_p_;
  ::ResourceSet_pimpl ResourceSet_p_;
  ::Resource_pimpl Resource_p_;
};

#endif // XSDE_OMIT_PAGGR

// Begin epilogue.
//
//
// End epilogue.

#include <xsde/cxx/post.hxx>

#endif // XRS_PIMPL_HXX

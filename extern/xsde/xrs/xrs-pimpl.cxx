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

// Begin prologue.
//
//
// End prologue.

#include "xrs-pimpl.hxx"

#include <xsde/cxx/parser/validating/string-common.hxx>

// ResourceTypes_pimpl
//

ResourceTypes_pimpl::
ResourceTypes_pimpl ()
: ResourceTypes_pskel (0)
{
}

void ResourceTypes_pimpl::
pre ()
{
  this->ResourceTypes_pimpl_state_.str_.clear ();
}

void ResourceTypes_pimpl::
_characters (const ::xsde::cxx::ro_string& s)
{
  if (this->_facets ().whitespace_ == 2 &&
      this->ResourceTypes_pimpl_state_.str_.size () == 0)
  {
    ::xsde::cxx::ro_string tmp (s.data (), s.size ());

    if (::xsde::cxx::trim_left (tmp) != 0)
    {
      this->ResourceTypes_pimpl_state_.str_ += tmp;
    }
  }
  else
    this->ResourceTypes_pimpl_state_.str_ += s;
}

void ResourceTypes_pimpl::
_post ()
{
  ::xsde::cxx::parser::validating::string_common::validate_facets (
    this->ResourceTypes_pimpl_state_.str_,
    this->_facets (),
    this->_context ());
}

::ResourceTypes ResourceTypes_pimpl::
post_ResourceTypes ()
{
  ::ResourceTypes::value_type v =
  static_cast< ::ResourceTypes::value_type > (0);
  const char* s = this->ResourceTypes_pimpl_state_.str_.c_str ();

  if (strcmp (s, "file") == 0)
    v = ::ResourceTypes::file;
  else if (strcmp (s, "image") == 0)
    v = ::ResourceTypes::image;
  else if (strcmp (s, "text") == 0)
    v = ::ResourceTypes::text;

  ::ResourceTypes r (v);
  return r;
}

// xrs_pimpl
//

xrs_pimpl::
xrs_pimpl (bool b)
{
  this->xrs_pimpl_base_ = b;
  this->xrs_pimpl_state_.xrs_ = 0;
}

xrs_pimpl::
~xrs_pimpl ()
{
  if (!this->xrs_pimpl_base_ && this->xrs_pimpl_state_.xrs_)
    delete this->xrs_pimpl_state_.xrs_;
}

void xrs_pimpl::
_reset ()
{
  xrs_pskel::_reset ();

  if (!this->xrs_pimpl_base_ && this->xrs_pimpl_state_.xrs_)
  {
    delete this->xrs_pimpl_state_.xrs_;
    this->xrs_pimpl_state_.xrs_ = 0;
  }
}

void xrs_pimpl::
pre_impl (::xrs* x)
{
  this->xrs_pimpl_state_.xrs_ = x;
}

void xrs_pimpl::
pre ()
{
  ::xrs* x = new ::xrs;
  this->pre_impl (x);
}

void xrs_pimpl::
id (const ::std::string& x)
{
  this->xrs_pimpl_state_.xrs_->id (x);
}

void xrs_pimpl::
version (const ::std::string& x)
{
  this->xrs_pimpl_state_.xrs_->version (x);
}

void xrs_pimpl::
ResourceSet (::ResourceSet* x)
{
  this->xrs_pimpl_state_.xrs_->ResourceSet ().push_back (x);
}

::xrs* xrs_pimpl::
post_xrs ()
{
  ::xrs* r = this->xrs_pimpl_state_.xrs_;
  this->xrs_pimpl_state_.xrs_ = 0;
  return r;
}

// Resource_pimpl
//

Resource_pimpl::
Resource_pimpl ()
: Resource_pskel (&base_impl_)
{
}

void Resource_pimpl::
pre ()
{
  this->base_impl_.pre ();
  this->Resource_pimpl_state_.Resource_ = ::Resource ();
}

void Resource_pimpl::
type (const ::ResourceTypes& x)
{
  this->Resource_pimpl_state_.Resource_.type (x);
}

void Resource_pimpl::
alias (const ::std::string& x)
{
  this->Resource_pimpl_state_.Resource_.alias (x);
}

::Resource Resource_pimpl::
post_Resource ()
{
  static_cast< ::std::string& > (this->Resource_pimpl_state_.Resource_) = 
  this->base_impl_.post_string ();
  return this->Resource_pimpl_state_.Resource_;
}

// ResourceSet_pimpl
//

ResourceSet_pimpl::
ResourceSet_pimpl (bool b)
{
  this->ResourceSet_pimpl_base_ = b;
  this->ResourceSet_pimpl_state_.ResourceSet_ = 0;
}

ResourceSet_pimpl::
~ResourceSet_pimpl ()
{
  if (!this->ResourceSet_pimpl_base_ && this->ResourceSet_pimpl_state_.ResourceSet_)
    delete this->ResourceSet_pimpl_state_.ResourceSet_;
}

void ResourceSet_pimpl::
_reset ()
{
  ResourceSet_pskel::_reset ();

  if (!this->ResourceSet_pimpl_base_ && this->ResourceSet_pimpl_state_.ResourceSet_)
  {
    delete this->ResourceSet_pimpl_state_.ResourceSet_;
    this->ResourceSet_pimpl_state_.ResourceSet_ = 0;
  }
}

void ResourceSet_pimpl::
pre_impl (::ResourceSet* x)
{
  this->ResourceSet_pimpl_state_.ResourceSet_ = x;
}

void ResourceSet_pimpl::
pre ()
{
  ::ResourceSet* x = new ::ResourceSet;
  this->pre_impl (x);
}

void ResourceSet_pimpl::
prefix (const ::std::string& x)
{
  this->ResourceSet_pimpl_state_.ResourceSet_->prefix (x);
}

void ResourceSet_pimpl::
Resource (const ::Resource& x)
{
  this->ResourceSet_pimpl_state_.ResourceSet_->Resource ().push_back (x);
}

::ResourceSet* ResourceSet_pimpl::
post_ResourceSet ()
{
  ::ResourceSet* r = this->ResourceSet_pimpl_state_.ResourceSet_;
  this->ResourceSet_pimpl_state_.ResourceSet_ = 0;
  return r;
}

// xrs_paggr
//

xrs_paggr::
xrs_paggr ()
{
  this->xrs_p_.parsers (this->string_p_,
                        this->string_p_,
                        this->ResourceSet_p_);

  this->ResourceSet_p_.parsers (this->string_p_,
                                this->Resource_p_);

  this->Resource_p_.parsers (this->ResourceTypes_p_,
                             this->string_p_);
}

const char* xrs_paggr::
root_name ()
{
  return "xrs";
}

const char* xrs_paggr::
root_namespace ()
{
  return "";
}

// Begin epilogue.
//
//
// End epilogue.

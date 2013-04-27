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

#include <xsde/cxx/pre.hxx>

// Begin prologue.
//
//
// End prologue.

#include "xrs.hxx"

#include <stdlib.h>
#include <new>

// ResourceTypes
//

static const char* _xsde_ResourceTypes_enumerators_[] = 
{
  "file",
  "image",
  "text"
};

const char* ResourceTypes::
string () const
{
  return _xsde_ResourceTypes_enumerators_[value_];
}

// xrs
//

xrs::
xrs ()
{
}

xrs::
~xrs ()
{
}

// Resource
//

Resource::
Resource ()
{
}

Resource::
~Resource ()
{
}

Resource::
Resource (const Resource& x)
: ::std::string (x)
{
  XSDE_UNUSED (x);
  this->type_ = x.type_;
  this->alias_ = x.alias_;
}

Resource& Resource::
operator= (const Resource& x)
{
  XSDE_UNUSED (x);
  static_cast< ::std::string& > (*this) = x;
  this->type_ = x.type_;
  this->alias_ = x.alias_;
  return *this;
}

// ResourceSet
//

ResourceSet::
ResourceSet ()
{
}

ResourceSet::
~ResourceSet ()
{
}

// Begin epilogue.
//
//
// End epilogue.

#include <xsde/cxx/post.hxx>

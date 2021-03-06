// Copyright (C) 2005-2009 Code Synthesis Tools CC
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

#ifndef KMODEL2_PIMPL_HXX
#define KMODEL2_PIMPL_HXX

// Begin prologue.
//
//
// End prologue.

#include <xsde/cxx/pre.hxx>

#ifndef XSDE_OMIT_PAGGR
#  define XSDE_OMIT_PAGGR
#  define KMODEL2_PIMPL_HXX_CLEAR_OMIT_PAGGR
#endif

#include "kmodel2-pskel.hxx"

#include <xsde/cxx/stack.hxx>

class LabelType_pimpl: public LabelType_pskel
{
  public:
  LabelType_pimpl ();

  virtual void
  pre ();

  // Attributes.
  //
  virtual void
  id (unsigned int);

  virtual ::LabelType
  post_LabelType ();

  public:
  ::xml_schema::string_pimpl base_impl_;

  public:
  struct LabelType_pimpl_state
  {
    ::LabelType LabelType_;
  };

  LabelType_pimpl_state LabelType_pimpl_state_;
};

class Property_pimpl: public Property_pskel
{
  public:
  Property_pimpl ();

  virtual void
  pre ();

  // Attributes.
  //
  virtual void
  key (const ::std::string&);

  virtual void
  value (const ::std::string&);

  virtual ::Property
  post_Property ();

  public:
  ::xml_schema::string_pimpl base_impl_;

  public:
  struct Property_pimpl_state
  {
    ::Property Property_;
  };

  Property_pimpl_state Property_pimpl_state_;
};

class PropertyListType_pimpl: public PropertyListType_pskel
{
  public:
  PropertyListType_pimpl (bool = false);

  ~PropertyListType_pimpl ();

  virtual void
  _reset ();

  virtual void
  pre ();

  // Elements.
  //
  virtual void
  Property (const ::Property&);

  virtual ::PropertyListType*
  post_PropertyListType ();

  public:
  void
  pre_impl (::PropertyListType*);

  public:
  struct PropertyListType_pimpl_state
  {
    ::PropertyListType* PropertyListType_;
  };

  PropertyListType_pimpl_state PropertyListType_pimpl_state_;
  bool PropertyListType_pimpl_base_;
};

class jProposalType_pimpl: public jProposalType_pskel
{
  public:
  jProposalType_pimpl (bool = false);

  ~jProposalType_pimpl ();

  virtual void
  _reset ();

  virtual void
  pre ();

  // Attributes.
  //
  virtual void
  mc (bool);

  virtual void
  qname (const ::std::string&);

  // Elements.
  //
  virtual void
  Label (const ::LabelType&);

  virtual ::jProposalType*
  post_jProposalType ();

  public:
  void
  pre_impl (::jProposalType*);

  public:
  struct jProposalType_pimpl_state
  {
    ::jProposalType* jProposalType_;
  };

  jProposalType_pimpl_state jProposalType_pimpl_state_;
  bool jProposalType_pimpl_base_;
};

class Image_pimpl: public Image_pskel
{
  public:
  Image_pimpl ();

  virtual void
  pre ();

  // Attributes.
  //
  virtual void
  id (unsigned int);

  virtual void
  uri (const ::std::string&);

  virtual ::Image
  post_Image ();

  public:
  ::xml_schema::string_pimpl base_impl_;

  public:
  struct Image_pimpl_state
  {
    ::Image Image_;
  };

  Image_pimpl_state Image_pimpl_state_;
};

class ImageListType_pimpl: public ImageListType_pskel
{
  public:
  ImageListType_pimpl (bool = false);

  ~ImageListType_pimpl ();

  virtual void
  _reset ();

  virtual void
  pre ();

  // Elements.
  //
  virtual void
  Image (const ::Image&);

  virtual ::ImageListType*
  post_ImageListType ();

  public:
  void
  pre_impl (::ImageListType*);

  public:
  struct ImageListType_pimpl_state
  {
    ::ImageListType* ImageListType_;
  };

  ImageListType_pimpl_state ImageListType_pimpl_state_;
  bool ImageListType_pimpl_base_;
};

class jGroupType_pimpl: public jGroupType_pskel
{
  public:
  jGroupType_pimpl (bool = false);

  ~jGroupType_pimpl ();

  virtual void
  _reset ();

  virtual void
  pre ();

  // Attributes.
  //
  virtual void
  id (unsigned int);

  virtual void
  name (const ::std::string&);

  // Elements.
  //
  virtual void
  PropertyList (::PropertyListType*);

  virtual void
  SourceList (::SourceList*);

  virtual void
  Description (const ::std::string&);

  virtual void
  ImageList (::ImageListType*);

  virtual void
  Text (const ::std::string&);

  virtual void
  Hint (const ::std::string&);

  virtual void
  jProposal (::jProposal*);

  virtual void
  jProblemList (::jProblemList*);

  virtual ::jGroupType*
  post_jGroupType ();

  public:
  void
  pre_impl (::jGroupType*);

  public:
  struct jGroupType_pimpl_state
  {
    ::jGroupType* jGroupType_;
  };

  jGroupType_pimpl_state jGroupType_pimpl_state_;
  bool jGroupType_pimpl_base_;
};

class CategoryType_pimpl: public CategoryType_pskel
{
  public:
  CategoryType_pimpl (bool = false);

  ~CategoryType_pimpl ();

  virtual void
  _reset ();

  virtual void
  pre ();

  // Attributes.
  //
  virtual void
  id (unsigned long);

  virtual void
  name (const ::std::string&);

  // Elements.
  //
  virtual void
  PropertyList (::PropertyListType*);

  virtual void
  Description (const ::std::string&);

  virtual void
  Category (::CategoryType*);

  virtual void
  jGroup (::jGroupType*);

  virtual ::CategoryType*
  post_CategoryType ();

  public:
  void
  pre_impl (::CategoryType*);

  public:
  struct CategoryType_pimpl_state
  {
    ::CategoryType* CategoryType_;
  };

  CategoryType_pimpl_state CategoryType_pimpl_state_first_;
  ::xsde::cxx::stack CategoryType_pimpl_state_;
  bool CategoryType_pimpl_base_;
};

class SourceRef_pimpl: public SourceRef_pskel
{
  public:
  virtual void
  pre ();

  // Attributes.
  //
  virtual void
  qnameref (const ::std::string&);

  virtual ::SourceRef
  post_SourceRef ();

  public:
  struct SourceRef_pimpl_state
  {
    ::SourceRef SourceRef_;
  };

  SourceRef_pimpl_state SourceRef_pimpl_state_;
};

class SourceList_pimpl: public SourceList_pskel
{
  public:
  SourceList_pimpl (bool = false);

  ~SourceList_pimpl ();

  virtual void
  _reset ();

  virtual void
  pre ();

  // Elements.
  //
  virtual void
  SourceRef (const ::SourceRef&);

  virtual ::SourceList*
  post_SourceList ();

  public:
  void
  pre_impl (::SourceList*);

  public:
  struct SourceList_pimpl_state
  {
    ::SourceList* SourceList_;
  };

  SourceList_pimpl_state SourceList_pimpl_state_;
  bool SourceList_pimpl_base_;
};

class jProposalRef_pimpl: public jProposalRef_pskel
{
  public:
  virtual void
  pre ();

  // Attributes.
  //
  virtual void
  qnameref (const ::std::string&);

  virtual ::jProposalRef
  post_jProposalRef ();

  public:
  struct jProposalRef_pimpl_state
  {
    ::jProposalRef jProposalRef_;
  };

  jProposalRef_pimpl_state jProposalRef_pimpl_state_;
};

class jProposal_pimpl: public jProposal_pskel
{
  public:
  jProposal_pimpl (bool = false);

  ~jProposal_pimpl ();

  virtual void
  _reset ();

  virtual void
  pre ();

  // Elements.
  //
  virtual void
  jProposalRef (const ::jProposalRef&);

  virtual ::jProposal*
  post_jProposal ();

  public:
  void
  pre_impl (::jProposal*);

  public:
  ::jProposalType_pimpl base_impl_;

  public:
  struct jProposal_pimpl_state
  {
    ::jProposal* jProposal_;
  };

  jProposal_pimpl_state jProposal_pimpl_state_;
  bool jProposal_pimpl_base_;
};

class jProblemList_pimpl: public jProblemList_pskel
{
  public:
  jProblemList_pimpl (bool = false);

  ~jProblemList_pimpl ();

  virtual void
  _reset ();

  virtual void
  pre ();

  // Elements.
  //
  virtual void
  jProblem (::jProblem*);

  virtual ::jProblemList*
  post_jProblemList ();

  public:
  void
  pre_impl (::jProblemList*);

  public:
  struct jProblemList_pimpl_state
  {
    ::jProblemList* jProblemList_;
  };

  jProblemList_pimpl_state jProblemList_pimpl_state_;
  bool jProblemList_pimpl_base_;
};

class kmx_pimpl: public kmx_pskel
{
  public:
  kmx_pimpl (bool = false);

  ~kmx_pimpl ();

  virtual void
  _reset ();

  virtual void
  pre ();

  // Attributes.
  //
  virtual void
  name (const ::std::string&);

  virtual void
  version (const ::std::string&);

  // Elements.
  //
  virtual void
  References (::References*);

  virtual void
  Content (::Content*);

  virtual ::kmx*
  post_kmx ();

  public:
  void
  pre_impl (::kmx*);

  public:
  struct kmx_pimpl_state
  {
    ::kmx* kmx_;
  };

  kmx_pimpl_state kmx_pimpl_state_;
  bool kmx_pimpl_base_;
};

class Solution_pimpl: public Solution_pskel
{
  public:
  virtual void
  pre ();

  // Attributes.
  //
  virtual void
  idref (unsigned int);

  virtual ::Solution
  post_Solution ();

  public:
  struct Solution_pimpl_state
  {
    ::Solution Solution_;
  };

  Solution_pimpl_state Solution_pimpl_state_;
};

class jProblem_pimpl: public jProblem_pskel
{
  public:
  jProblem_pimpl (bool = false);

  ~jProblem_pimpl ();

  virtual void
  _reset ();

  virtual void
  pre ();

  // Attributes.
  //
  virtual void
  id (unsigned int);

  // Elements.
  //
  virtual void
  PropertyList (::PropertyListType*);

  virtual void
  Text (const ::std::string&);

  virtual void
  Solution (const ::Solution&);

  virtual ::jProblem*
  post_jProblem ();

  public:
  void
  pre_impl (::jProblem*);

  public:
  struct jProblem_pimpl_state
  {
    ::jProblem* jProblem_;
  };

  jProblem_pimpl_state jProblem_pimpl_state_;
  bool jProblem_pimpl_base_;
};

class References_pimpl: public References_pskel
{
  public:
  References_pimpl (bool = false);

  ~References_pimpl ();

  virtual void
  _reset ();

  virtual void
  pre ();

  // Elements.
  //
  virtual void
  RefSourceList (::RefSourceList*);

  virtual void
  RefProposalTypeList (::RefProposalTypeList*);

  virtual ::References*
  post_References ();

  public:
  void
  pre_impl (::References*);

  public:
  struct References_pimpl_state
  {
    ::References* References_;
  };

  References_pimpl_state References_pimpl_state_;
  bool References_pimpl_base_;
};

class Content_pimpl: public Content_pskel
{
  public:
  Content_pimpl (bool = false);

  ~Content_pimpl ();

  virtual void
  _reset ();

  virtual void
  pre ();

  // Elements.
  //
  virtual void
  Category (::CategoryType*);

  virtual ::Content*
  post_Content ();

  public:
  void
  pre_impl (::Content*);

  public:
  struct Content_pimpl_state
  {
    ::Content* Content_;
  };

  Content_pimpl_state Content_pimpl_state_;
  bool Content_pimpl_base_;
};

class RefSourceList_pimpl: public RefSourceList_pskel
{
  public:
  RefSourceList_pimpl (bool = false);

  ~RefSourceList_pimpl ();

  virtual void
  _reset ();

  virtual void
  pre ();

  // Elements.
  //
  virtual void
  Source (::Source*);

  virtual ::RefSourceList*
  post_RefSourceList ();

  public:
  void
  pre_impl (::RefSourceList*);

  public:
  struct RefSourceList_pimpl_state
  {
    ::RefSourceList* RefSourceList_;
  };

  RefSourceList_pimpl_state RefSourceList_pimpl_state_;
  bool RefSourceList_pimpl_base_;
};

class RefProposalTypeList_pimpl: public RefProposalTypeList_pskel
{
  public:
  RefProposalTypeList_pimpl (bool = false);

  ~RefProposalTypeList_pimpl ();

  virtual void
  _reset ();

  virtual void
  pre ();

  // Elements.
  //
  virtual void
  jProposalList (::jProposalList*);

  virtual ::RefProposalTypeList*
  post_RefProposalTypeList ();

  public:
  void
  pre_impl (::RefProposalTypeList*);

  public:
  struct RefProposalTypeList_pimpl_state
  {
    ::RefProposalTypeList* RefProposalTypeList_;
  };

  RefProposalTypeList_pimpl_state RefProposalTypeList_pimpl_state_;
  bool RefProposalTypeList_pimpl_base_;
};

class Source_pimpl: public Source_pskel
{
  public:
  Source_pimpl (bool = false);

  ~Source_pimpl ();

  virtual void
  _reset ();

  virtual void
  pre ();

  // Attributes.
  //
  virtual void
  qname (const ::std::string&);

  virtual void
  uri (const ::std::string&);

  // Elements.
  //
  virtual void
  PropertyList (::PropertyListType*);

  virtual ::Source*
  post_Source ();

  public:
  void
  pre_impl (::Source*);

  public:
  struct Source_pimpl_state
  {
    ::Source* Source_;
  };

  Source_pimpl_state Source_pimpl_state_;
  bool Source_pimpl_base_;
};

class jProposalList_pimpl: public jProposalList_pskel
{
  public:
  jProposalList_pimpl (bool = false);

  ~jProposalList_pimpl ();

  virtual void
  _reset ();

  virtual void
  pre ();

  // Elements.
  //
  virtual void
  jProposal (::jProposalType*);

  virtual ::jProposalList*
  post_jProposalList ();

  public:
  void
  pre_impl (::jProposalList*);

  public:
  struct jProposalList_pimpl_state
  {
    ::jProposalList* jProposalList_;
  };

  jProposalList_pimpl_state jProposalList_pimpl_state_;
  bool jProposalList_pimpl_base_;
};

#ifdef KMODEL2_PIMPL_HXX_CLEAR_OMIT_PAGGR
#  undef XSDE_OMIT_PAGGR
#endif

#ifndef XSDE_OMIT_PAGGR

// Parser aggregate for the kmx element.
//
class kmx_paggr
{
  public:
  kmx_paggr ();

  void
  pre ()
  {
    this->kmx_p_.pre ();
  }

  ::kmx*
  post ()
  {
    return this->kmx_p_.post_kmx ();
  }

  ::kmx_pimpl&
  root_parser ()
  {
    return this->kmx_p_;
  }

  static const char*
  root_name ();

  static const char*
  root_namespace ();

  void
  reset ()
  {
    this->kmx_p_._reset ();
  }

  public:
  ::xml_schema::idref_pimpl idref_p_;
  ::xml_schema::id_pimpl id_p_;
  ::xml_schema::boolean_pimpl boolean_p_;
  ::xml_schema::non_negative_integer_pimpl non_negative_integer_p_;
  ::xml_schema::unsigned_int_pimpl unsigned_int_p_;
  ::xml_schema::string_pimpl string_p_;
  ::xml_schema::ncname_pimpl ncname_p_;
  ::LabelType_pimpl LabelType_p_;
  ::jProposalRef_pimpl jProposalRef_p_;
  ::jProblemList_pimpl jProblemList_p_;
  ::jProblem_pimpl jProblem_p_;
  ::Solution_pimpl Solution_p_;
  ::CategoryType_pimpl CategoryType_p_;
  ::kmx_pimpl kmx_p_;
  ::References_pimpl References_p_;
  ::PropertyListType_pimpl PropertyListType_p_;
  ::Property_pimpl Property_p_;
  ::jProposalType_pimpl jProposalType_p_;
  ::ImageListType_pimpl ImageListType_p_;
  ::Image_pimpl Image_p_;
  ::jGroupType_pimpl jGroupType_p_;
  ::SourceList_pimpl SourceList_p_;
  ::SourceRef_pimpl SourceRef_p_;
  ::jProposal_pimpl jProposal_p_;
  ::xml_schema::uri_pimpl uri_p_;
  ::RefSourceList_pimpl RefSourceList_p_;
  ::Source_pimpl Source_p_;
  ::RefProposalTypeList_pimpl RefProposalTypeList_p_;
  ::jProposalList_pimpl jProposalList_p_;
  ::Content_pimpl Content_p_;
};

#endif // XSDE_OMIT_PAGGR

#include <xsde/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

#endif // KMODEL2_PIMPL_HXX

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

#ifndef KMODEL2_SIMPL_HXX
#define KMODEL2_SIMPL_HXX

// Begin prologue.
//
//
// End prologue.

#include <xsde/cxx/pre.hxx>

#ifndef XSDE_OMIT_SAGGR
#  define XSDE_OMIT_SAGGR
#  define KMODEL2_SIMPL_HXX_CLEAR_OMIT_SAGGR
#endif

#include "kmodel2-sskel.hxx"

#include <xsde/cxx/stack.hxx>

class LabelType_simpl: public LabelType_sskel
{
  public:
  LabelType_simpl ();

  virtual void
  pre (const ::LabelType&);

  // Attributes.
  //
  virtual unsigned int
  id ();

  public:
  ::xml_schema::string_simpl base_impl_;

  public:
  struct LabelType_simpl_state
  {
    const ::LabelType* LabelType_;
  };

  LabelType_simpl_state LabelType_simpl_state_;
};

class Property_simpl: public Property_sskel
{
  public:
  Property_simpl ();

  virtual void
  pre (const ::Property&);

  // Attributes.
  //
  virtual ::std::string
  key ();

  virtual ::std::string
  value ();

  public:
  ::xml_schema::string_simpl base_impl_;

  public:
  struct Property_simpl_state
  {
    const ::Property* Property_;
  };

  Property_simpl_state Property_simpl_state_;
};

class PropertyListType_simpl: public PropertyListType_sskel
{
  public:
  virtual void
  pre (const ::PropertyListType&);

  // Elements.
  //
  virtual bool
  Property_next ();

  virtual const ::Property&
  Property ();

  public:
  struct PropertyListType_simpl_state
  {
    const ::PropertyListType* PropertyListType_;
    ::PropertyListType::Property_const_iterator Property_;
    ::PropertyListType::Property_const_iterator Property_end_;
  };

  PropertyListType_simpl_state PropertyListType_simpl_state_;
};

class jProposalType_simpl: public jProposalType_sskel
{
  public:
  virtual void
  pre (const ::jProposalType&);

  // Attributes.
  //
  virtual bool
  mc ();

  virtual ::std::string
  qname ();

  // Elements.
  //
  virtual bool
  Label_next ();

  virtual const ::LabelType&
  Label ();

  public:
  struct jProposalType_simpl_state
  {
    const ::jProposalType* jProposalType_;
    ::jProposalType::Label_const_iterator Label_;
    ::jProposalType::Label_const_iterator Label_end_;
  };

  jProposalType_simpl_state jProposalType_simpl_state_;
};

class Image_simpl: public Image_sskel
{
  public:
  Image_simpl ();

  virtual void
  pre (const ::Image&);

  // Attributes.
  //
  virtual unsigned int
  id ();

  virtual ::std::string
  uri ();

  public:
  ::xml_schema::string_simpl base_impl_;

  public:
  struct Image_simpl_state
  {
    const ::Image* Image_;
  };

  Image_simpl_state Image_simpl_state_;
};

class ImageListType_simpl: public ImageListType_sskel
{
  public:
  virtual void
  pre (const ::ImageListType&);

  // Elements.
  //
  virtual bool
  Image_next ();

  virtual const ::Image&
  Image ();

  public:
  struct ImageListType_simpl_state
  {
    const ::ImageListType* ImageListType_;
    ::ImageListType::Image_const_iterator Image_;
    ::ImageListType::Image_const_iterator Image_end_;
  };

  ImageListType_simpl_state ImageListType_simpl_state_;
};

class jGroupType_simpl: public jGroupType_sskel
{
  public:
  virtual void
  pre (const ::jGroupType&);

  // Attributes.
  //
  virtual unsigned int
  id ();

  virtual ::std::string
  name ();

  // Elements.
  //
  virtual const ::PropertyListType&
  PropertyList ();

  virtual bool
  SourceList_present ();

  virtual const ::SourceList&
  SourceList ();

  virtual ::std::string
  Description ();

  virtual const ::ImageListType&
  ImageList ();

  virtual ::std::string
  Text ();

  virtual ::std::string
  Hint ();

  virtual const ::jProposal&
  jProposal ();

  virtual const ::jProblemList&
  jProblemList ();

  public:
  struct jGroupType_simpl_state
  {
    const ::jGroupType* jGroupType_;
  };

  jGroupType_simpl_state jGroupType_simpl_state_;
};

class CategoryType_simpl: public CategoryType_sskel
{
  public:
  CategoryType_simpl ();

  virtual void
  pre (const ::CategoryType&);

  // Attributes.
  //
  virtual unsigned long
  id ();

  virtual ::std::string
  name ();

  // Elements.
  //
  virtual const ::PropertyListType&
  PropertyList ();

  virtual ::std::string
  Description ();

  virtual bool
  Category_next ();

  virtual const ::CategoryType&
  Category ();

  virtual bool
  jGroup_next ();

  virtual const ::jGroupType&
  jGroup ();

  virtual void
  post ();

  virtual void
  _reset ();

  public:
  struct CategoryType_simpl_state
  {
    const ::CategoryType* CategoryType_;
    ::CategoryType::Category_const_iterator Category_;
    ::CategoryType::Category_const_iterator Category_end_;
    ::CategoryType::jGroup_const_iterator jGroup_;
    ::CategoryType::jGroup_const_iterator jGroup_end_;
  };

  CategoryType_simpl_state CategoryType_simpl_state_first_;
  ::xsde::cxx::stack CategoryType_simpl_state_;
};

class SourceRef_simpl: public SourceRef_sskel
{
  public:
  virtual void
  pre (const ::SourceRef&);

  // Attributes.
  //
  virtual bool
  qnameref_present ();

  virtual ::std::string
  qnameref ();

  public:
  struct SourceRef_simpl_state
  {
    const ::SourceRef* SourceRef_;
  };

  SourceRef_simpl_state SourceRef_simpl_state_;
};

class SourceList_simpl: public SourceList_sskel
{
  public:
  virtual void
  pre (const ::SourceList&);

  // Elements.
  //
  virtual bool
  SourceRef_next ();

  virtual const ::SourceRef&
  SourceRef ();

  public:
  struct SourceList_simpl_state
  {
    const ::SourceList* SourceList_;
    ::SourceList::SourceRef_const_iterator SourceRef_;
    ::SourceList::SourceRef_const_iterator SourceRef_end_;
  };

  SourceList_simpl_state SourceList_simpl_state_;
};

class jProposalRef_simpl: public jProposalRef_sskel
{
  public:
  virtual void
  pre (const ::jProposalRef&);

  // Attributes.
  //
  virtual ::std::string
  qnameref ();

  public:
  struct jProposalRef_simpl_state
  {
    const ::jProposalRef* jProposalRef_;
  };

  jProposalRef_simpl_state jProposalRef_simpl_state_;
};

class jProposal_simpl: public jProposal_sskel
{
  public:
  jProposal_simpl ();

  virtual void
  pre (const ::jProposal&);

  // Elements.
  //
  virtual bool
  jProposalRef_present ();

  virtual const ::jProposalRef&
  jProposalRef ();

  public:
  ::jProposalType_simpl base_impl_;

  public:
  struct jProposal_simpl_state
  {
    const ::jProposal* jProposal_;
  };

  jProposal_simpl_state jProposal_simpl_state_;
};

class jProblemList_simpl: public jProblemList_sskel
{
  public:
  virtual void
  pre (const ::jProblemList&);

  // Elements.
  //
  virtual bool
  jProblem_next ();

  virtual const ::jProblem&
  jProblem ();

  public:
  struct jProblemList_simpl_state
  {
    const ::jProblemList* jProblemList_;
    ::jProblemList::jProblem_const_iterator jProblem_;
    ::jProblemList::jProblem_const_iterator jProblem_end_;
  };

  jProblemList_simpl_state jProblemList_simpl_state_;
};

class kmx_simpl: public kmx_sskel
{
  public:
  virtual void
  pre (const ::kmx&);

  // Attributes.
  //
  virtual ::std::string
  name ();

  virtual ::std::string
  version ();

  // Elements.
  //
  virtual const ::References&
  References ();

  virtual const ::Content&
  Content ();

  public:
  struct kmx_simpl_state
  {
    const ::kmx* kmx_;
  };

  kmx_simpl_state kmx_simpl_state_;
};

class Solution_simpl: public Solution_sskel
{
  public:
  virtual void
  pre (const ::Solution&);

  // Attributes.
  //
  virtual bool
  idref_present ();

  virtual unsigned int
  idref ();

  public:
  struct Solution_simpl_state
  {
    const ::Solution* Solution_;
  };

  Solution_simpl_state Solution_simpl_state_;
};

class jProblem_simpl: public jProblem_sskel
{
  public:
  virtual void
  pre (const ::jProblem&);

  // Attributes.
  //
  virtual unsigned int
  id ();

  // Elements.
  //
  virtual const ::PropertyListType&
  PropertyList ();

  virtual ::std::string
  Text ();

  virtual bool
  Solution_next ();

  virtual const ::Solution&
  Solution ();

  public:
  struct jProblem_simpl_state
  {
    const ::jProblem* jProblem_;
    ::jProblem::Solution_const_iterator Solution_;
    ::jProblem::Solution_const_iterator Solution_end_;
  };

  jProblem_simpl_state jProblem_simpl_state_;
};

class References_simpl: public References_sskel
{
  public:
  virtual void
  pre (const ::References&);

  // Elements.
  //
  virtual const ::RefSourceList&
  RefSourceList ();

  virtual const ::RefProposalTypeList&
  RefProposalTypeList ();

  public:
  struct References_simpl_state
  {
    const ::References* References_;
  };

  References_simpl_state References_simpl_state_;
};

class Content_simpl: public Content_sskel
{
  public:
  virtual void
  pre (const ::Content&);

  // Elements.
  //
  virtual bool
  Category_next ();

  virtual const ::CategoryType&
  Category ();

  public:
  struct Content_simpl_state
  {
    const ::Content* Content_;
    ::Content::Category_const_iterator Category_;
    ::Content::Category_const_iterator Category_end_;
  };

  Content_simpl_state Content_simpl_state_;
};

class RefSourceList_simpl: public RefSourceList_sskel
{
  public:
  virtual void
  pre (const ::RefSourceList&);

  // Elements.
  //
  virtual bool
  Source_next ();

  virtual const ::Source&
  Source ();

  public:
  struct RefSourceList_simpl_state
  {
    const ::RefSourceList* RefSourceList_;
    ::RefSourceList::Source_const_iterator Source_;
    ::RefSourceList::Source_const_iterator Source_end_;
  };

  RefSourceList_simpl_state RefSourceList_simpl_state_;
};

class RefProposalTypeList_simpl: public RefProposalTypeList_sskel
{
  public:
  virtual void
  pre (const ::RefProposalTypeList&);

  // Elements.
  //
  virtual const ::jProposalList&
  jProposalList ();

  public:
  struct RefProposalTypeList_simpl_state
  {
    const ::RefProposalTypeList* RefProposalTypeList_;
  };

  RefProposalTypeList_simpl_state RefProposalTypeList_simpl_state_;
};

class Source_simpl: public Source_sskel
{
  public:
  virtual void
  pre (const ::Source&);

  // Attributes.
  //
  virtual ::std::string
  qname ();

  virtual ::std::string
  uri ();

  // Elements.
  //
  virtual const ::PropertyListType&
  PropertyList ();

  public:
  struct Source_simpl_state
  {
    const ::Source* Source_;
  };

  Source_simpl_state Source_simpl_state_;
};

class jProposalList_simpl: public jProposalList_sskel
{
  public:
  virtual void
  pre (const ::jProposalList&);

  // Elements.
  //
  virtual bool
  jProposal_next ();

  virtual const ::jProposalType&
  jProposal ();

  public:
  struct jProposalList_simpl_state
  {
    const ::jProposalList* jProposalList_;
    ::jProposalList::jProposal_const_iterator jProposal_;
    ::jProposalList::jProposal_const_iterator jProposal_end_;
  };

  jProposalList_simpl_state jProposalList_simpl_state_;
};

#ifdef KMODEL2_SIMPL_HXX_CLEAR_OMIT_SAGGR
#  undef XSDE_OMIT_SAGGR
#endif

#ifndef XSDE_OMIT_SAGGR

// Serializer aggregate for the kmx element.
//
class kmx_saggr
{
  public:
  kmx_saggr ();

  void
  pre (const ::kmx& x)
  {
    this->kmx_s_.pre (x);
  }

  void
  post ()
  {
    this->kmx_s_.post ();
  }

  ::kmx_simpl&
  root_serializer ()
  {
    return this->kmx_s_;
  }

  static const char*
  root_name ();

  static const char*
  root_namespace ();

  void
  reset ()
  {
    this->kmx_s_._reset ();
  }

  public:
  ::xml_schema::idref_simpl idref_s_;
  ::xml_schema::id_simpl id_s_;
  ::xml_schema::boolean_simpl boolean_s_;
  ::xml_schema::non_negative_integer_simpl non_negative_integer_s_;
  ::xml_schema::unsigned_int_simpl unsigned_int_s_;
  ::xml_schema::string_simpl string_s_;
  ::xml_schema::ncname_simpl ncname_s_;
  ::LabelType_simpl LabelType_s_;
  ::jProposalRef_simpl jProposalRef_s_;
  ::jProblemList_simpl jProblemList_s_;
  ::jProblem_simpl jProblem_s_;
  ::Solution_simpl Solution_s_;
  ::CategoryType_simpl CategoryType_s_;
  ::kmx_simpl kmx_s_;
  ::References_simpl References_s_;
  ::PropertyListType_simpl PropertyListType_s_;
  ::Property_simpl Property_s_;
  ::jProposalType_simpl jProposalType_s_;
  ::ImageListType_simpl ImageListType_s_;
  ::Image_simpl Image_s_;
  ::jGroupType_simpl jGroupType_s_;
  ::SourceList_simpl SourceList_s_;
  ::SourceRef_simpl SourceRef_s_;
  ::jProposal_simpl jProposal_s_;
  ::xml_schema::uri_simpl uri_s_;
  ::RefSourceList_simpl RefSourceList_s_;
  ::Source_simpl Source_s_;
  ::RefProposalTypeList_simpl RefProposalTypeList_s_;
  ::jProposalList_simpl jProposalList_s_;
  ::Content_simpl Content_s_;
};

#endif // XSDE_OMIT_SAGGR

#include <xsde/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

#endif // KMODEL2_SIMPL_HXX

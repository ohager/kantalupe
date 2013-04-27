#ifndef __ModeTreeDataConcept_H
#define __ModeTreeDataConcept_H

class QStandardItem;

namespace k{

/**
With the concept class @e any @e non-base-class-derived object 
can be used for any specified behavior. Although, a public Behavior interface
is @e exemplarily provided, there is actually no need to use it in the manner
of inheritance.
@par Usage
The class itself is not ready to use, but furthermore the entrance ticket for the user's
very own custom behavior. The concept is intended to provide the behavior for 
any objects that might be uncoupled in the sense of programming. There common sense is
not the same base class, but its conceptually identical behavior, e.g. write, read, play, attack, etc.
The user needs to extend the Concept::Behavior for arbitrary needs. This is where the behavior is 
conceptually defined. The classes that shall be used with a concept do not need to subclass Concept::Behavior
(I encourage you not to do...for the sake of some small performance benefits as discussed later.), but technically its
possible to do so as the interface is public. Some might think, subclassing will facilitate the
implementation. I do not agree, as Copy&Paste is the only thing we need. The compiler will complain, if any 
method is missing ;-)

Fast and Quick:
Extend the Concept::Behavior interface by your needs and do so with the private templated
behavior wrapper. Finally, expose the behavior using the Concept class itself.
On your object class side you need to do the same only once. But remember, no subclassing
from Concept::Behavior is necessary.You could do, but I wouldn't.

@par Example
The following example uses two completely @e type-different, uncoupled classes and puts
them together in @e one standard container. The common sense of these classes
is its behavior. This example shows, that no inheritance from Concept::Behavior
is needed, to trigger/dispatch the instances' very own behavior. Only the instance themselves
knows about their concrete behavior. The example assumes, that Concept::Behavior provides
the methods can_write() ans write(). This is the only information the Implementer needs
to know.
@code

#include <iostream>
#include "Concept.h"


// this method is not necessary for the example's explanation
// but shown for completeness reasons
void release(std::list<Concept*> & list)
{
	std::list<Concept*>::iterator it = list.begin(), 
			end = list.end();
	do{
		delete *it;
	}while(it!=end);
	list.clear();
}


// Note that neither Element1 nor Element2 are subclassed froma
// any base class. They only provide the same subset of behavior methods
struct Element1 
{
	bool can_write() const { return true; }
	void write() const { 
		std::cout << "I'm an instance of Element1" << std::endl;
	}
};

struct Element2 
{
	bool can_write() const { return true; }
	void write() const { 
		std::cout << "I'm an instance of Element2" << std::endl;
	}

};


int main(int argc, char **argv)
{
	// you need to use Concept as heap object. otherwise you'll run into
	// memory problems.
	std::list<Concept*> elements;
	// but your elements need to be on stack as they are intended to be 
	// value types, i.e. not deallocated if on heap
	elements.push_back( new Concept( Element1() ) );
	elements.push_back( new Concept( Element2() ) );

	std::list<Concept*>::const_iterator it = elements.begin(), 
			end = elements.end();
	do{
		it->write();
		++it;
	}while(it!=end);

	release(elements);
	return 0;
}
@endcode

@par Discussion
So, what's the advantage over any conventional dynamic polymorphy approach?
Well, as long as you do not use Concept::Behavior as base class for your derivates
you might gain function call performance, as the functions are not virtual.
By design your classes are less coupled, although your classes are @e conceptually
similar. They are type independent, in fact we erased the type information.
Another advantage by this approach comes along by the fact, that the behavior is 
with the objects and the user usually does not need to care about
types, i.e. is often down casting polymorphic objects.
A disadvantage may be the eventual code bloat provocated by the use of templates.
But IMHO this is a price I accept to pay. And, if you might have done this with
conventional polymorpy who knows if the resulting code would be more compact?!

Thanks to User jsmith with his article about "C++ type erasure" ar www.cplusplus.com
Nice blow!

@author O. Haeger
*/
class ModelTreeDataConcept{

public:

	/**
	This is where you need to add your behavior methods.
	Also, do it in BehaviorPrivate and extend Concepts interface.

	class Behavior{
	public:
	   virtual ~Behavior()  {}
	   virtual QStandardItem * createStandardItem() const = 0;
   };
   */

	ModelTreeDataConcept() : mAnyObject(0x0) {}
   ~ModelTreeDataConcept() {
	   //std::cout << "~Concept()" << std::endl;
		delete mAnyObject;
	}


   template< typename BehaviorType > 
   ModelTreeDataConcept( const BehaviorType& any ) :
      mAnyObject( new BehaviorPrivate<BehaviorType>( any ) ) {}


   // no virtual functions, but real ones.
   QStandardItem * createStandardItem() const {
			return mAnyObject->createStandardItem();
   };
   

//private:
	
   template< typename BehaviorType > 
   struct BehaviorPrivate// : Behavior // static polymorphy
   {
       BehaviorPrivate( const BehaviorType & ct ) : mAnyObject( ct ) {}
	   ~BehaviorPrivate() { }

	   // compiler would complain, if methods are not available.
	   QStandardItem * createStandardItem() const  { return mAnyObject.createStandardItem();  }
     private:
       BehaviorType mAnyObject;
   };


	BehaviorPrivate * mAnyObject;


};

} // eons


#endif


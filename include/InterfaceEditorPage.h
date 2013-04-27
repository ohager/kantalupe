#ifndef INTERFACEEDITORPAGE_H
#define INTERFACEEDITORPAGE_H

namespace k{

class TreeItem;
/**
  Interface for editor pages.
  @author O. Haeger
  */
class InterfaceEditorPage
{
public:
	InterfaceEditorPage() {}
	virtual ~InterfaceEditorPage() {}

	/**
	  Commits the data from page to model.
	  @param m The abstract model item instance
	  */
	virtual void commit(TreeItem * item) const = 0;

	/**
	  Updates this page instance using the model's data
	  @param m The model.
	  */
	virtual void update(TreeItem * item) = 0;
};

} // eons

#endif // INTERFACEEDITORPAGE_H

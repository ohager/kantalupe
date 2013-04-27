#include "ItemEditorPropertiesPage.h"
#include "PropertyEditWidget.h"
#include "PlainTextEdit.h"
#include "LineEdit.h"
#include "Overlay.h"
#include "global.h"
#include "TreeItemProtocol.h"
#include "TreeItem.h"

#include "SignalBlocker.h"

#include <QtGui>

START_NS


ItemEditorPropertiesPage::ItemEditorPropertiesPage(QWidget * parent)
	: EditorBasePage(parent),
		mPropertyEditor(0x0)
{
	setupUi();
}

ItemEditorPropertiesPage::~ItemEditorPropertiesPage()
{

}

bool ItemEditorPropertiesPage::isAcceptingMime(const QMimeData *m) const
{
	return false;
}

// interface implementation
void ItemEditorPropertiesPage::commit(TreeItem * item) const
{
	EditorBasePage::commit(item);
	tip::ItemType type = item->getItemType();
	if(type == tip::ItemCategory)
	{
		Category obj;
		tip::extract(item, obj); // get initial data
		obj.properties = mPropertyEditor->getProperties();
		tip::incept(obj,item); // overwrite with new data
	}
	else if(type == tip::ItemGroup)
	{
		Group obj;
		tip::extract(item, obj); // get initial data
		obj.properties = mPropertyEditor->getProperties();
		tip::incept(obj,item); // overwrite with new data
	}
	else if(type == tip::ItemMatrix)
	{
		Matrix obj;
		tip::extract(item, obj); // get initial data
		obj.properties = mPropertyEditor->getProperties();
		tip::incept(obj,item); // overwrite with new data
	}
	else if(type == tip::ItemProblem)
	{
		Problem obj;
		tip::extract(item, obj); // get initial data
		obj.properties = mPropertyEditor->getProperties();
		tip::incept(obj,item); // overwrite with new data
	}
	else if(type == tip::ItemMatrixProblem)
	{
		MatrixProblem obj;
		tip::extract(item, obj); // get initial data
		obj.properties = mPropertyEditor->getProperties();
		tip::incept(obj,item); // overwrite with new data
	}


}



void ItemEditorPropertiesPage::update(TreeItem * item)
{
	EditorBasePage::update(item);

	SignalBlocker b(mPropertyEditor);
	mPropertyEditor->clear();
	tip::ItemType type = item->getItemType();
	if(type == tip::ItemCategory)
	{
		Category obj;
		tip::extract(item, obj);
		foreach(const Property & p, obj.properties)
		{
			mPropertyEditor->addProperty(p);
		}
	}
	else if (type == tip::ItemGroup)
	{
		Group obj;
		tip::extract(item, obj);
		foreach(const Property & p, obj.properties)
		{
			mPropertyEditor->addProperty(p);
		}
	}
	else if (type == tip::ItemMatrix)
	{
		Matrix obj;
		tip::extract(item, obj);
		foreach(const Property & p, obj.properties)
		{
			mPropertyEditor->addProperty(p);
		}
	}
	else if (type == tip::ItemProblem)
	{
		Problem obj;
		tip::extract(item, obj);
		foreach(const Property & p, obj.properties)
		{
			mPropertyEditor->addProperty(p);
		}
	}
	else if (type == tip::ItemMatrixProblem)
	{
		MatrixProblem obj;
		tip::extract(item, obj);
		foreach(const Property & p, obj.properties)
		{
			mPropertyEditor->addProperty(p);
		}
	}
}


void ItemEditorPropertiesPage::setupUi()
{
	QLayout * layout = new QVBoxLayout();

	mPropertyEditor = new k::PropertyEditWidget(this);

	connect(mPropertyEditor, SIGNAL(itemChanged(QTreeWidgetItem*,int)),this,SLOT(commit()));

	layout->addWidget(mPropertyEditor);
	setLayout(layout);

}



END_NS


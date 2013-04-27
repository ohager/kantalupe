#ifndef ABOUTBOX_H
#define ABOUTBOX_H

#include <QDialog>

namespace k{

/**
  An about box providing Information about the application,
  like version, authors etc.
  @author O. Haeger
  */
class AboutBox : public QWidget
{
public:
	AboutBox(QWidget * parent=0x0);
	~AboutBox();
protected:
	void setupUi();

};


} // eons

#endif // ABOUTBOX_H

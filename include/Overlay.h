#ifndef OVERLAY_H
#define OVERLAY_H

#include <QLabel>



namespace k{

/**
  An Overlay that can be applied to any widget.
   @author O. Haeger
  */
class Overlay : public QLabel
{
    Q_OBJECT

public:
	/**
	  @param applyTo The widget to where this overlay is applied.
	  */
	explicit Overlay(QWidget *applyTo);

public slots:
	/**
		Centers the overlay relative to its applied widget
	*/
	void center();


};

} //eons

#endif // OVERLAY_H

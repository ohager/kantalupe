#ifndef MODALLABEL_H
#define MODALLABEL_H

#include <QWidget>

class QMainWindow;

namespace k{

/**
  The modal label works only on main window, as its geometry is used
  @todo Extend by QLabel-features (icon, movie, etc.)
  @author O. Haeger
  */
class ModalLabel: public QWidget
{
    Q_OBJECT
	Q_PROPERTY(const QString & text READ text WRITE setText );
	Q_PROPERTY(const QColor & foregroundColor READ foregroundColor WRITE setForegroundColor);
	Q_PROPERTY(const QColor & backgroundColor READ backgroundColor WRITE setBackgroundColor);
public:

	enum Position{
		TopLeft = 1,
		TopCenter,
		TopRight,
		CenterLeft,
		Center,
		CenterRight,
		BottomLeft,
		BottomCenter,
		BottomRight
	};

	/**
	  @param parent The parent widget, which must be the main window, actually.
	  */
	explicit ModalLabel(QMainWindow * window);

	/**
	  Creates the message with given @e message and duration.
		@param parent The parent widget.
		@param message The text to be shown
	  */
	ModalLabel(QMainWindow * window, const QString & text);

	void setText(const QString & m);
	const QString & text() const;

	void setForegroundColor(const QColor & c);
	const QColor foregroundColor() const;

	void setBackgroundColor(const QColor & c);
	const QColor backgroundColor() const;

	void setPosition(Position p);
	Position position() const;

	void setFont(const QFont &); // overwritten

protected:
	void setup();
	void resizeEvent(QResizeEvent *);
	void showEvent(QShowEvent *);
	void paintEvent(QPaintEvent*);

	QPoint calcPosition(Position);

private:
	QString mMessage;
	QColor mColorFg, mColorBg;
	Position mPosition;
};

} // eons

#endif

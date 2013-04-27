#ifndef LineEdit_H
#define LineEdit_H

#include <QLineEdit>

namespace k{

	class Overlay;

	/**
	  This specialized line edit has an overlay label
@author O. Haeger
	  */
	class LineEdit : public QLineEdit
	{
		Q_OBJECT
	public:
		LineEdit(QWidget * parent = 0x0);
		inline Overlay * overlay() { return mOverlay; }

	protected:
		void showEvent(QShowEvent *);
		void resizeEvent(QResizeEvent *);
		void moveEvent(QMoveEvent *);

	protected slots:
		void onTextChanged(const QString & text);
	private:
		Overlay * mOverlay;
	};

} // eons

#endif // LineEdit_H

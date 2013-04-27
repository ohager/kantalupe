#ifndef PLAINTEXTEDIT_H
#define PLAINTEXTEDIT_H

#include <QPlainTextEdit>

namespace k{

	class Overlay;

	/**
	  This specialized text editor has an overlay label
@author O. Haeger
	  */
	class PlainTextEdit : public QPlainTextEdit
	{
		Q_OBJECT
	public:
		PlainTextEdit(QWidget * parent = 0x0);
		inline Overlay * overlay() { return mOverlay; }

	protected:
		void showEvent(QShowEvent *);
		void resizeEvent(QResizeEvent *);
		void moveEvent(QMoveEvent *);

	protected slots:
		void onTextChanged();
	private:
		Overlay * mOverlay;
	};

} // eons

#endif // PLAINTEXTEDIT_H

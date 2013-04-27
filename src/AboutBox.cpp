#include "AboutBox.h"

#include <QtGui>
#include <xsde/cxx/version.hxx>

#include "global.h"
#include "Application.h"
#include "WobblerWidget.h"

START_NS

AboutBox::AboutBox(QWidget * parent)
	: QWidget(parent)
{
	setupUi();
}

AboutBox::~AboutBox()
{
}

void AboutBox::setupUi()
{
	QHBoxLayout * mainlayout = new QHBoxLayout();
	QVBoxLayout * sublayout = new QVBoxLayout();

	QImage img;
	bool l=img.load(global::R.getValue("image/logo"));
	if(!l)
	{
		DEBUG( "AboutBox", "setupUi",
				QString("Failed loading '%1'").arg( global::R.getValue("image/logo") )
			);

	}
	else{
		img = img.scaledToHeight(128, Qt::SmoothTransformation);
		QWidget * logo = new WobblerWidget(img,7.3, 15.25, 0.25);
		mainlayout->addWidget(logo);
		logo->setFixedSize( QSize(128,256) );
	}

	QLabel * text = new QLabel(	tr(
			"<p align='center'>"
#ifdef _DEBUG
			"<h3>kantalupe Edit #DEBUG#</h3><br/>"
#else
			"<h3>kantalupe Edit</h3><br/>"
#endif
			"<small>Creating multiple choice surveys is easy now</small>"
			"</p><hr/>"
			"<p>"
			"Version: %1 <br/>"
			"Build Date: %2<br/>"
			"Author: <a href='mailto:oliver@clayhouse.de'>O.Haeger</a><br/>"
			"</p>"
			"<p>"
			"This application uses:<br/>Nokia&trade; Qt&trade; Version %4 (open source)<br/>"
			"CodeSynthesis XSD/e Version %5(open source)</p><br/>"
			"Copyright <a href='mailto:oliver@clayhouse.de'>Clayhouse</a>, %3"
			)
				.arg(kApp->applicationVersion())
				.arg(__DATE__)
				.arg(QDate::currentDate().year())
				.arg(qVersion())
				.arg( XSDE_STR_VERSION )
	);

	sublayout->addWidget(text, 0, Qt::AlignCenter);
	mainlayout->addLayout( sublayout );
	setLayout(mainlayout);

	setWindowTitle(tr("About kantalupe"));


}


END_NS


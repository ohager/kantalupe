#ifndef SHORTMESSAGE_H
#define SHORTMESSAGE_H

#include <QWidget>

/**
  A short message, that is shown on top of the application.
  @author O. Haeger
  */
class ShortMessage : public QWidget
{
    Q_OBJECT
	Q_PROPERTY(const QString & message READ message WRITE setMessage );
	Q_PROPERTY(int duration READ duration WRITE setDuration );
	Q_PROPERTY(int fade READ fade WRITE setFade)

signals:
	/**
	  Emitted when message was shown.
	  */
	void finished();
public:
	static const int DefaultDuration = 2000;

	/**
	  @param parent The parent widget. The message is shown on top of the root widgets.
	  */
	explicit ShortMessage(QWidget * parent);

	/**
	  Creates the message with given @e message and duration.
	@param parent The parent widget.
		@param message The text to be shown
	  @param duration The duration of that message in milliseconds
	  */
	ShortMessage(QWidget * parent, const QString & message,int duration= DefaultDuration);


	void setMessage(const QString & m);
	const QString & message() const;

	void setDuration(int millies);
	int duration() const;

	/**
	  Convenience method.
	  Shows the @e message for given @e duration.
	  @param parent The parent widget.
	   @param message The text to be shown
	   @param duration The duration of that message in milliseconds
	  */
	static void showMessage(QWidget * parent, const QString & m, int duration = DefaultDuration);

public slots:
	void center();
	void fadeIn();
	void fadeOut();


protected:
	void setup();
	void setFade(int f);
	int fade() const;

	void resizeEvent(QResizeEvent *);
	void showEvent(QShowEvent *);
	void paintEvent(QPaintEvent*);
	void timerEvent(QTimerEvent*);
private:
	QString mMessage;
	int mDuration, mFade;
};

#endif // SHORTMESSAGE_H

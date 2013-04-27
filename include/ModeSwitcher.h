#ifndef MODESWITCHER_H
#define MODESWITCHER_H

#include <QObject>

namespace k{

class ModeSwitcher : public QObject
{
public:
    explicit ModeSwitcher(QObject *parent = 0);
protected:
	bool eventFilter(QObject * obj, QEvent * event);


};


} // eons

#endif // MODESWITCHER_H

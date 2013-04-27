#ifndef UIDGENERATOR_H
#define UIDGENERATOR_H

#include <QString>
#include <QSet>

class UidGeneratorImpl;

/**
  A class for generating an application wide unique identifier
  @note This class shall not be subclassed!
  @author O. Haeger
  */
class UidGenerator
{
public:
	UidGenerator();
	// explicitely nonvirtual, as it is not considered as a base class
	~UidGenerator();

	/**
	  Generates a uid.
	  @param input An input string needed for uid generation
	  @return The Uid
	  */
	QString generate(const QString & in) const;

private:
	UidGeneratorImpl * _impl;
};

#endif // UIDGENERATOR_H

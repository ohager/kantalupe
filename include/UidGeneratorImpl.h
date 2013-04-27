#ifndef UIDGENERATORIMPL_H
#define UIDGENERATORIMPL_H

#include <QSet>
#include <QString>

/**
  Private Implementation. Use UidGenerator instead
  @author O. Haeger
  */
class UidGeneratorImpl
{
public:

	static UidGeneratorImpl & instance();

	/**
	  Generates a hash-based uid.
	  @param base An basic input string needed for uid generation (might be modified to hit uniqueness)
	  @return The Uid
	  */
	QString generateAsHash(const QString & base) const;
private:
	UidGeneratorImpl();

	mutable QSet<QString> mGenerated;

	static UidGeneratorImpl sInstance;
};

#endif // UIDGENERATORIMPL_H

#ifndef Decipher_H
#define Decipher_H

#include <QtCore/QLinkedList>
#include <QtCore/QString>
#include "Returnables.h"

class Decipher
{
	private:
		//Decipher();
	public:
		Decipher();
		~Decipher();
		static Returnables::FriendsTimeline* FriendsTimeline(const QString &xml);
		static Returnables::PublicTimeline* PublicTimeline(const QString &xml);
};


#endif //Decipher_H

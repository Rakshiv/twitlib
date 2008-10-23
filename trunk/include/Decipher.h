#ifndef Decipher_H
#define Decipher_H

#include <QtCore/QLinkedList>
#include <QtCore/QString>

struct User
{
	unsigned int id;
	QString name;
	QString screenName;
	QString location;
	QString description;
	QString profileImageUrl;
	QString url;
	bool isProtected;
	unsigned int followersCount;
};

struct Status
{
	QString createdAt;
	unsigned int id;
	QString text;
	QString source;
	bool truncated;
	unsigned int inReplyToStatusId;
	unsigned int inReplyToUserId;
	bool favorited;
	User userInfo;
};

class Decipher
{
	private:
		//Decipher();
	public:
		Decipher();
		~Decipher();
		static QLinkedList<Status*> FriendsTimeline(const QString &xml);
};


#endif //Decipher_H

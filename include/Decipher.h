#ifndef Decipher_H
#define Decipher_H

#include <QtCore/QLinkedList>
#include <QtCore/QString>
#include "Returnables.h"

class QDomElement;

class Decipher
{
	private:
		Decipher();

	public:
		~Decipher();
		static Returnables::FriendsTimeline* FriendsTimeline(const QString &xml);
		static Returnables::PublicTimeline* PublicTimeline(const QString &xml);
		static Returnables::SingleStatus* SingleStatus(const QString &xml);
		static Returnables::FeaturedUsers* FeaturedUsers(const QString &xml);

	private:
		static enum Parent {USER, STATUS};
		static QLinkedList<Returnables::StatusUser*> GetStatuses(const QString &xml, Parent parent = STATUS);
		static void PopulateStatus(Returnables::Status &status, QDomElement elem);
		static void PopulateUser(Returnables::User &user, QDomElement elem);

	private:
		static QString nStatus;
		static QString nStatusCreatedAt;
		static QString nStatusId;
		static QString nStatusText;
		static QString nStatusSource;
		static QString nStatusTruncated;
		static QString nStatusInReplyToStatusId;
		static QString nStatusInReplyToUserId;
		static QString nStatusFavorited;
		static QString nUser;
		static QString nUserId;
		static QString nUserName;
		static QString nUserScreenName;
		static QString nUserDescription;
		static QString nUserLocation;
		static QString nUserProfileImageUrl;
		static QString nUserUrl;
		static QString nUserProtected;
		static QString nUserFollowersCount;
};


#endif //Decipher_H

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
		static Returnables::Login* Login(const QString &xml);
		static Returnables::TwitterUp* TwitterUp(const QString &xml);
		static Returnables::UserTimeline* UserTimeline(const QString &xml);
		static Returnables::Favorites* Favorites(const QString &xml);
		static Returnables::NewStatus* NewStatus(const QString &xml);
		static Returnables::RecentReplies* RecentReplies(const QString &xml);
		static Returnables::RemoveStatus* RemoveStatus(const QString &xml);
		static Returnables::Friends* Friends(const QString &xml);
		static Returnables::Followers* Followers(const QString &xml);
		static Returnables::UserDetails* UserDetails(const QString &xml);
		static Returnables::SentDirectMessages* SentDirectMessages(const QString &xml);
		static Returnables::ReceivedDirectMessages* ReceivedDirectMessages(const QString &xml);
		static Returnables::SendDirectMessage* SendDirectMessage(const QString &xml);
		static Returnables::RemoveDirectMessage* RemoveDirectMessage(const QString &xml);
		static Returnables::AddFriendship* AddFriendShip(const QString &xml);
		static Returnables::RemoveFriendship* RemoveFriendship(const QString &xml);
		static Returnables::FriendshipExist* FriendshipExist(const QString &xml);
		static Returnables::UpdateLocation* UpdateLocation(const QString &xml);
		static Returnables::DeliveryDevice* DeliveryDevice(const QString &xml);
		static Returnables::ApiRequests* ApiRequests(const QString &xml);
		static Returnables::AddFavorite* AddFavorite(const QString &xml);
		static Returnables::RemoveFavorite* RemoveFavorite(const QString &xml);

	private:
		static enum Parent { USER, STATUS };
		static QLinkedList<Returnables::StatusUser*> GetStatusUserList(const QString &xml, Parent parent=STATUS);
		static QLinkedList<Returnables::DirectMessage*> GetDirectMessageList(const QString &xml);
		static void PopulateStatus(Returnables::Status &status, const QDomElement &node);
		static void PopulateUser(Returnables::User &user, const QDomElement &node);
		static void PopulateDetails(Returnables::Details &details, const QDomElement &node);
		static void PopulateDirectHeader(Returnables::DirectHeader &header, const QDomElement &node);
		static void PopulateApiRequests(Returnables::ApiRequests &apiRequests, const QDomElement &node);

	private:
		static QString nStatus;
		static QString nCreatedAt;
		static QString nId;
		static QString nText;
		static QString nSource;
		static QString nTruncated;
		static QString nInReplyToStatusId;
		static QString nInReplyToUserId;
		static QString nFavorited;
		static QString nUser;
		static QString nName;
		static QString nScreenName;
		static QString nDescription;
		static QString nLocation;
		static QString nProfileImageUrl;
		static QString nUrl;
		static QString nProtected;
		static QString nFollowersCount;
		static QString nAuthorized;
		static QString nOk;
		static QString nProfileBackgroundColor;
		static QString nProfileTextColor;
		static QString nProfileLinkColor;
		static QString nProfileSidebarFillColor;
		static QString nProfileSidebarBorderColor;
		static QString nFriendsCount;
		static QString nFavoritesCount;
		static QString nUtcOffset;
		static QString nTimeZone;
		static QString nProfileBackgroundImageUrl;
		static QString nProfileBackgroundTiled;
		static QString nStatusesCount;
		static QString nDirectMessage;
		static QString nSenderId;
		static QString nRecipientId;
		static QString nSenderScreenName;
		static QString nRecipientScreenName;
		static QString nSender;
		static QString nRecipient;
		static QString nFriends;
		static QString nHash;
		static QString nResetTime;
		static QString nResetTimeSeconds;
		static QString nRemainingHits;
		static QString nHourlyLimit;
};


#endif //Decipher_H

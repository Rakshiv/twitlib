#ifndef Returnables_H
#define Returnables_H

#include <QtCore/QLinkedList>
#include <QtCore/QMap>
#include "Server.h"

namespace Returnables
{
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

	struct Details
	{
		QString profileBackgroundColor;
		QString profileTextColor;
		QString profileLinkColor;
		QString profileSidebarFillColor;
		QString profileSidebarBorderColor;
		unsigned int friendsCount;
		QString createdAt;
		unsigned int favoritesCount;
		int utcOffset;
		QString timeZone;
		QString profileBackgroundImageUrl;
		bool profileBackgroundTiled;
		unsigned int statusesCount;
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
	};

	struct DirectHeader
	{
		unsigned int id;
		unsigned int senderId;
		QString text;
		unsigned int recipientId;
		QString createdAt;
		QString senderScreenName;
		QString recipientScreenName;
	};

	struct DirectMessage
	{
		DirectHeader headerInfo;
		User sender;
		User recipient;
	};

	struct StatusUser
	{
		Status status;
		User user;
	};

    class FriendsTimeline
    {
		public:
			FriendsTimeline() {}
			~FriendsTimeline() {}
			QLinkedList<StatusUser*> list;
    };
	class PublicTimeline
	{
		public:
			PublicTimeline() {}
			~PublicTimeline() {}
			QLinkedList<StatusUser*> list;
	};
	class SingleStatus
	{
		public:
			SingleStatus() { status = new Status(); user = new User(); }
			~SingleStatus() { if(status) delete status; if(user) delete user; }
			Status* status;
			User* user;
	};
	class FeaturedUsers
	{
		public:
			FeaturedUsers() {}
			~FeaturedUsers() {}
			QLinkedList<StatusUser*> list;
	};
	class Login
	{
		public:
			Login() {}
			~Login() {}
			bool authorized;
	};
	class TwitterUp
	{
		public:
			TwitterUp() {}
			~TwitterUp() {}
			bool up;
	};
	class UserTimeline
	{
		public:
			UserTimeline() {}
			~UserTimeline() {}
			QLinkedList<StatusUser*> list;
	};
	class Favorites
	{
		public:
			Favorites() {}
			~Favorites() {}
			QLinkedList<StatusUser*> list;
	};
	class NewStatus
	{
		public:
			NewStatus() { newStatus = new Status(); user = new User(); }
			~NewStatus() { if(newStatus) delete newStatus; if(user) delete user; }
			Status* newStatus;
			User* user;
	};
	class RecentReplies
	{
		public:
			RecentReplies() {}
			~RecentReplies() {}
			QLinkedList<StatusUser*> list;
	};
	class RemoveStatus
	{
		public:
			RemoveStatus() { removedStatus = new Status(); user = new User(); }
			~RemoveStatus() { if(removedStatus) delete removedStatus; if(user) delete user; }
			Status *removedStatus;
			User *user;
	};
	class Friends
	{
		public:
			Friends() {}
			~Friends() {}
			QLinkedList<StatusUser*> list;
	};
	class Followers
	{
		public:
			Followers() {}
			~Followers() {}
			QLinkedList<StatusUser*> list;
	};
	class UserDetails
	{
		public:
			UserDetails() { user = new User(); details = new Details(); status = new Status(); }
			~UserDetails() { if(user) delete user; if(details) delete details; if(status) delete status; }
			User *user;
			Details *details;
			Status *status;
	};
	class SentDirectMessages
	{
		public:
			SentDirectMessages() {}
			~SentDirectMessages() {}
			QLinkedList<DirectMessage*> list;
	};
	class ReceivedDirectMessages
	{
		public:
			ReceivedDirectMessages() {}
			~ReceivedDirectMessages() {}
			QLinkedList<DirectMessage*> list;
	};
	class SendDirectMessage
	{
		public:
			SendDirectMessage() { headerInfo = new DirectHeader(); sender = new User(); recipient = new User(); }
			~SendDirectMessage() { if(headerInfo) delete headerInfo; if(sender) delete sender; if(recipient) delete recipient; }
			DirectHeader *headerInfo;
			User *sender;
			User *recipient;
	};
	class RemoveDirectMessage
	{
		public:
			RemoveDirectMessage() { headerInfo = new DirectHeader(); sender = new User(); recipient = new User(); }
			~RemoveDirectMessage() { if(headerInfo) delete headerInfo; if(sender) delete sender; if(recipient) delete recipient; }
			DirectHeader *headerInfo;
			User *sender;
			User *recipient;
	};
	class AddFriendship
	{
		public:
			AddFriendship() { user = new User(); status = new Status(); }
			~AddFriendship() { if(user) delete user; if(status) delete status; }
			User *user;
			Status *status;
	};
	class RemoveFriendship
	{
		public:
			RemoveFriendship() { user = new User(); status = new Status(); }
			~RemoveFriendship() { if(user) delete user; if(status) delete status; }
			User *user;
			Status *status;	
	};
	class FriendshipExist
	{
		public:
			FriendshipExist() {}
			~FriendshipExist() {}
			bool friends;
	};
	class UpdateLocation
	{
		public:
			UpdateLocation() { user = new User(); status = new Status(); }
			~UpdateLocation() { if(user) delete user; if(status) delete status; }
			User *user;
			Status *status;
	};
	class DeliveryDevice
	{
		public:
			DeliveryDevice() { user = new User(); status = new Status(); }
			~DeliveryDevice() { if(user) delete user; if(status) delete status; }
			User *user;
			Status *status;
	};
	class ApiRequests
	{
		public:
			ApiRequests() {}
			~ApiRequests() {}
			QString resetTime;
			unsigned int resetTimeSeconds;
			unsigned int remainingHits;
			unsigned int hourlyLimit;
	};
	class AddFavorite
	{
		public:
			AddFavorite() { status = new Status(); user = new User(); }
			~AddFavorite() { if(status) delete status; if(user) delete user; }
			Status *status;
			User *user;
	};
	class RemoveFavorite
	{
		public:
			RemoveFavorite() { status = new Status(); user = new User(); }
			~RemoveFavorite() { if(status) delete status; if(user) delete user; }
			Status *status;
			User *user;	
	};
};


#endif //Returnables_H

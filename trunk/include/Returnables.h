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

	struct StatusUser
	{
		Status status;
		User user;
	};

    class FriendsTimeline
    {
		public:
			QLinkedList<StatusUser*> statuses; 
    };
	class PublicTimeline
	{
		public:
			QLinkedList<StatusUser*> statuses;
	};
	class SingleStatus
	{
		public:
			StatusUser* status;
	};
	class FeaturedUsers
	{
		public:
			QLinkedList<StatusUser*> users;
	};
	class Login
	{
		public:
			bool authorized;
	};
	class TwitterUp
	{
		public:
			bool up;
	};
	class UserTimeline
	{
		public:
			QLinkedList<StatusUser*> statuses;
	};


};


#endif //Returnables_H

/*

        void GetUsersTimeline(SERVER::Option2 *opt=NULL);

		void GetFavorites(QString user="", int page=1);
        void PostNewStatus(QString status);
        void GetRecentReplies(SERVER::Option3 *opt=NULL);
        void RemoveStatus(QString id);
        void GetFriends(SERVER::Option4 *opt=NULL);
        void GetFollowers(SERVER::Option5 *opt=NULL);
        void GetUserDetails(QString user);
        void GetSentDirectMessages(SERVER::Option6 *opt=NULL);
        void GetReceivedDirectMessages(SERVER::Option6 *opt=NULL);
        void SendDirectMessage(QString user, QString text);
        void RemoveDirectMessage(QString id);
        void AddFriendship(QString user);
        void RemoveFriendship(QString user);
        void FriendshipExist(QString user_a, QString user_b);
        void VerifyCredentials();
        void UpdateLocation(QString location);
        void UpdateDeliveryDevice(SERVER::DEVICES device);
        void RemainingApiRequests();
        void AddFavorite(QString id);
        void RemoveFavorite(QString id);
        void StartFollow(QString user);
        void StopFollow(QString user);
        void BlockUser(QString user);
        void UnBlockUser(QString user);

*/
#ifndef Returnables_H
#define Returnables_H

#include <QtCore/QLinkedList>
#include <QtCore/QMap>
#include "Server.h"
//depre
//update_location

//New
//PROFILE_COLORS, PROFILE_IMAGE, PROFILE_BACKGROUND_IMAGE, PROFILE
//ENABLE_NOTIFICATIONS, DISABLE_NOTIFICATIONS, BLOCK_USER, UNBLOCK_USER,
//FRIENDS_IDS, FOLLOWERS_IDS

//NOT WORK
//RECENT_REPLIES


namespace Returnables
{
        struct User
	{
		unsigned int id;
		QString name;
		QString screenName;
                QString description;
                QString location;
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
                bool following;
                bool notifications;
                unsigned int statusesCount;
	};

//Status for "Status element"
        struct seStatus
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

//Status for "Basic user information element"
        struct biStatus
        {
                QString createdAt;
                unsigned int id;
                QString text;
                QString source;
                bool truncated;
                unsigned int inReplyToStatusId;
                unsigned int inReplyToUserId;
                bool favorited;
                QString inReplyToScreenName;
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

        struct DirectMessageElement
	{
		DirectHeader headerInfo;
                User sender;
                User recipient;
	};

//"Status element"
        struct StatusElement
        {
            seStatus status;
            User user;
        };
//"Basic user information element"
        struct BasicUserInfoElement
        {
            biStatus status;
            User user;
        };
//"Extended user information element"
        struct ExtUserInfoElement
        {
            User user;
            Details details;
            biStatus status;
        };

        enum RequestId { PUBLIC_TIMELINE, FRIENDS_TIMELINE, USER_TIMELINE, SINGLE_STATUS, NEW_STATUS,\
                         RECENT_REPLIES, REMOVE_STATUS, FRIENDS, FOLLOWERS, USER_DETAILS,\
                         RECEIVED_DIRECT_MESSAGES, SENT_DIRECT_MESSAGES, SEND_DIRECT_MESSAGE, REMOVE_DIRECT_MESSAGE,\
                         ADD_FRIENDSHIP, REMOVE_FRIENDSHIP, FRIENDSHIP_EXISTS, FRIENDS_IDS, FOLLOWERS_IDS, LOGIN, LOGOUT,\
                         DELIVERY_DEVICE, PROFILE_COLORS, PROFILE_IMAGE, PROFILE_BACKGROUND_IMAGE,\
                         API_REQUESTS, PROFILE, FAVORITES, ADD_FAVORITE, REMOVE_FAVORITE,\
                         ENABLE_NOTIFICATIONS, DISABLE_NOTIFICATIONS, BLOCK_USER, UNBLOCK_USER,\
                         TWITTER_UP, FEATURED_USERS, VERIFY_CREDENTIALS \
        };

	class Response
	{
		public:
			Response() {}
			virtual ~Response() {}
			RequestId reqID;
	};
//Status Methods
//==================================================================================================
        class PublicTimeline : public Response
        {
                public:
                        PublicTimeline() {}
                        ~PublicTimeline() {}
                        QLinkedList<StatusElement*> list;
        };
        class FriendsTimeline : public Response
        {
		public:
			FriendsTimeline() {}
			~FriendsTimeline() {}
                        QLinkedList<StatusElement*> list;
        };
        class UserTimeline : public Response
        {
                public:
                        UserTimeline() {}
                        ~UserTimeline() {}
                        QLinkedList<StatusElement*> list;
        };
//show
	class SingleStatus : public Response
	{
		public:
                        SingleStatus() { status = new StatusElement; }
                        ~SingleStatus() { if(status) delete status;}
                        StatusElement *status;
	};
//update
        class NewStatus : public Response
        {
                public:
                        NewStatus() { status = new StatusElement; }
                        ~NewStatus() { if(status) delete status; }
                        StatusElement* status;
        };
//replies
        class RecentReplies : public Response
        {
                public:
                        RecentReplies() {}
                        ~RecentReplies() {}
                        QLinkedList<StatusElement*> list;
        };
//destroy
        class RemoveStatus : public Response
        {
                public:
                        RemoveStatus() { status = new StatusElement; }
                        ~RemoveStatus() { if(status) delete status; }
                        StatusElement *status;
        };
//==================================================================================================

//User Methods
//==================================================================================================
        class Friends : public Response
        {
                public:
                        Friends() {}
                        ~Friends() {}
                        QLinkedList<BasicUserInfoElement*> list;
        };
        class Followers : public Response
        {
                public:
                        Followers() {}
                        ~Followers() {}
                        QLinkedList<BasicUserInfoElement*> list;
        };
//show
        class UserDetails : public Response
        {
                public:
                        UserDetails() { userExt = new ExtUserInfoElement; }
                        ~UserDetails() { if(userExt) delete userExt; }
                        ExtUserInfoElement *userExt;
        };
//==================================================================================================

//Direct Message Methods
//==================================================================================================
//direct_messages
        class ReceivedDirectMessages : public Response
        {
                public:
                        ReceivedDirectMessages() {}
                        ~ReceivedDirectMessages() {}
                        QLinkedList<DirectMessageElement*> list;
        };
//sent
        class SentDirectMessages : public Response
        {
                public:
                        SentDirectMessages() {}
                        ~SentDirectMessages() {}
                        QLinkedList<DirectMessageElement*> list;
        };
//new
        class SendDirectMessage : public Response
        {
                public:
                        SendDirectMessage() { message = new DirectMessageElement; }
                        ~SendDirectMessage() { if(message) delete message; }
                        DirectMessageElement *message;
        };
//destroy
        class RemoveDirectMessage : public Response
        {
                public:
                        RemoveDirectMessage() { message = new DirectMessageElement; }
                        ~RemoveDirectMessage() { if(message) delete message; }
                        DirectMessageElement *message;
        };
//==================================================================================================

//Friendship Methods
//==================================================================================================
//create
        class AddFriendship : public Response
        {
                public:
                        AddFriendship() { user = new BasicUserInfoElement; }
                        ~AddFriendship() { if(user) delete user; }
                        BasicUserInfoElement *user;
        };
//destroy
        class RemoveFriendship : public Response
        {
                public:
                        RemoveFriendship() { user = new BasicUserInfoElement; }
                        ~RemoveFriendship() { if(user) delete user; }
                        BasicUserInfoElement *user;
        };
//exists
        class FriendshipExist : public Response
        {
                public:
                        FriendshipExist() {}
                        ~FriendshipExist() {}
                        bool friends;
        };
//==================================================================================================

//Social Graph Methods
//==================================================================================================
//friends/ids
        class FriendsIDs : public Response
        {
            public:
                FriendsIDs() {}
                ~FriendsIDs() {}
                QLinkedList<unsigned int> list;
        };
//followers/ids
        class FollowersIDs : public Response
        {
            public:
                FollowersIDs() {}
                ~FollowersIDs() {}
                QLinkedList<unsigned int> list;
        };
//==================================================================================================

//Account Methods
//==================================================================================================
//verify_credentials
        class Login : public Response
        {
                public:
                        Login() { userExt = new ExtUserInfoElement; }
                        ~Login() { if(userExt) delete userExt; }
                        ExtUserInfoElement *userExt;
        };
//update_delivery_device
        class DeliveryDevice : public Response
        {
                public:
                        DeliveryDevice() { user = new BasicUserInfoElement; }
                        ~DeliveryDevice() { if(user) delete user; }
                        BasicUserInfoElement *user;
        };
//update_profile_colors
        class ProfileColors : public Response
        {
                public:
                        ProfileColors() { userExt = new ExtUserInfoElement; }
                        ~ProfileColors() { if(userExt) delete userExt; }
                        ExtUserInfoElement *userExt;
        };
//update_profile_image
        class ProfileImage : public Response
        {
                public:
                        ProfileImage() { userExt = new ExtUserInfoElement; }
                        ~ProfileImage() { if(userExt) delete userExt; }
                        ExtUserInfoElement *userExt;
        };
//update_profile_background_image
        class ProfileBackgroundImage : public Response
        {
                public:
                        ProfileBackgroundImage() { userExt = new ExtUserInfoElement; }
                        ~ProfileBackgroundImage() { if(userExt) delete userExt; }
                        ExtUserInfoElement *userExt;
        };
//rate_limit_status
        class ApiRequests : public Response
        {
                public:
                        ApiRequests() {}
                        ~ApiRequests() {}
                        QString resetTime;
                        unsigned int resetTimeSeconds;
                        unsigned int remainingHits;
                        unsigned int hourlyLimit;
        };
        //update_profile
        class Profile : public Response
        {
                public:
                        Profile() { userExt = new ExtUserInfoElement; }
                        ~Profile() { if(userExt) delete userExt; }
                        ExtUserInfoElement *userExt;
        };
//==================================================================================================

//Favorite Methods
//==================================================================================================
        class Favorites : public Response
        {
                public:
                        Favorites() {}
                        ~Favorites() {}
                        QLinkedList<StatusElement*> list;
        };
//create
        class AddFavorite : public Response
        {
                public:
                        AddFavorite() { status = new StatusElement; }
                        ~AddFavorite() { if(status) delete status; }
                        StatusElement *status;
        };
//destroy
        class RemoveFavorite : public Response
        {
                public:
                        RemoveFavorite() { status = new StatusElement; }
                        ~RemoveFavorite() { if(status) delete status;}
                        StatusElement *status;
        };
//==================================================================================================

//Notification Methods
//==================================================================================================
//follow
        class EnableNotifications : public Response
        {
                public:
                        EnableNotifications() { user = new BasicUserInfoElement; }
                        ~EnableNotifications() { if(user) delete user; }
                        BasicUserInfoElement *user;
        };
//leave
        class DisableNotifications : public Response
        {
                public:
                        DisableNotifications() { user = new BasicUserInfoElement; }
                        ~DisableNotifications() { if(user) delete user; }
                        BasicUserInfoElement *user;
        };
//==================================================================================================

//Block Methods
//==================================================================================================
//create
//==================================================================================================
        class BlockUser : public Response
        {
                public:
                        BlockUser() { user = new BasicUserInfoElement; }
                        ~BlockUser() { if(user) delete user; }
                        BasicUserInfoElement *user;
        };
//destroy
        class UnBlockUser : public Response
        {
                public:
                        UnBlockUser() { user = new BasicUserInfoElement; }
                        ~UnBlockUser() { if(user) delete user; }
                        BasicUserInfoElement *user;
        };
//==================================================================================================

//Help Methods
//==================================================================================================
//test
	class TwitterUp : public Response
	{
		public:
			TwitterUp() {}
			~TwitterUp() {}
			bool up;
	};
//==================================================================================================

//Not in API
//==================================================================================================
        class FeaturedUsers : public Response
        {
                public:
                        FeaturedUsers() {}
                        ~FeaturedUsers() {}
                        QLinkedList<BasicUserInfoElement*> list;
        };
//==================================================================================================
};


#endif //Returnables_H

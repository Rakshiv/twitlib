#ifndef Core_H
#define Core_H

#include <QtCore/QObject>
#include <QtCore/QBuffer>
#include <QtCore/QEventLoop>
#include <QtCore/QMap>
#include <QtNetwork/QHttp>
#include "Server.h"
#include "Decipher.h"
#include "Returnables.h"

class Core : public QObject
{
	Q_OBJECT;
          
	public:
		Core();
		virtual ~Core();
        
    public:
        void GetPublicTimeline();
        void GetSingleStatus(QString id);
        void GetFeaturedUsers();
        void Logout();
        void Login(QString user, QString passw);
        void IsTwitterUp();
        void GetUsersTimeline(SERVER::Option2 *opt=NULL);
        void GetFavorites(QString user="", unsigned int page=1);
        void GetFriendsTimeline(SERVER::Option1 *opt=NULL);
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
        void AddFriendship(QString user, bool follow=true);
        void RemoveFriendship(QString user);
        void FriendshipExist(QString user_a, QString user_b);
        void VerifyCredentials();
        void UpdateLocation(QString location);
        void UpdateDeliveryDevice(SERVER::DEVICES device);
        void RemainingApiRequests();
        void AddFavorite(QString id);
        void RemoveFavorite(QString id);
		
	public slots:
        void RequestStarted(int id);
		void ReqFinished(int id, bool error);
        void DataReadProgress(int done, int total);
        void Done(bool error);
        
    signals:
		void PublicTimeline(Returnables::PublicTimeline *);
		void FriendsTimeline(Returnables::FriendsTimeline *);
		void SingleStatus(Returnables::SingleStatus *);
		void FeaturedUsers(Returnables::FeaturedUsers *);
		void Login(Returnables::Login *);
		void TwitterUp(Returnables::TwitterUp *);
		void UserTimeline(Returnables::UserTimeline *);
		void Favorites(Returnables::Favorites *);
		void NewStatus(Returnables::NewStatus *);
		void RecentReplies(Returnables::RecentReplies *);
		void RemoveStatus(Returnables::RemoveStatus *);
		void Friends(Returnables::Friends *);
		void Followers(Returnables::Followers *);
		void UserDetails(Returnables::UserDetails *);
		void SentDirectMessages(Returnables::SentDirectMessages *);
		void ReceivedDirectMessages(Returnables::ReceivedDirectMessages *);
		void SendDirectMessage(Returnables::SendDirectMessage *);
		void RemoveDirectMessage(Returnables::RemoveDirectMessage *);
		void AddFriendship(Returnables::AddFriendship *);
		void RemoveFriendship(Returnables::RemoveFriendship *);
		void FriendshipExists(Returnables::FriendshipExist *);
		void UpdateLocation(Returnables::UpdateLocation *);
		void DeliveryDevice(Returnables::DeliveryDevice *);
		void ApiRequests(Returnables::ApiRequests *);
		void AddFavorite(Returnables::AddFavorite *);
		void RemoveFavorite(Returnables::RemoveFavorite *);

        void QueryDone();
        void OnError(QString error);
        void OnMessageReceived(QString message);
        void OnStatusReceived(SERVER::RESP response);

	private:
		enum RequestId { PUBLIC_TIMELINE, FRIENDS_TIMELINE, SINGLE_STATUS, LOGOUT, FEATURED_USERS, VERIFY_CREDENTIALS, \
						 TWITTER_UP, USER_TIMELINE, FAVORITES, NEW_STATUS, RECENT_REPLIES, REMOVE_STATUS, FRIENDS, \
						 FOLLOWERS, USER_DETAILS, SENT_DIRECT_MESSAGES, RECEIVED_DIRECT_MESSAGES, SEND_DIRECT_MESSAGE, \
						 REMOVE_DIRECT_MESSAGE, ADD_FRIENDSHIP, REMOVE_FRIENDSHIP, FRIENDSHIP_EXISTS, UPDATE_LOCATION, \
						 DELIVERY_DEVICE, API_REQUESTS, ADD_FAVORITE, REMOVE_FAVORITE };
		struct Info
		{
			Info() { buffer = NULL; }
			QBuffer *buffer;
			RequestId requestid;
		};

    private:
        void MakeConnections();
		void responseHeaderReceived(const QHttpResponseHeader &resp);
        int MakeGetRequest(QString req,RequestId reqId = LOGOUT);
        int MakePostRequest(QString path,QByteArray req,RequestId reqId = LOGOUT);
               
	private:
        QMap<int,Info> m_buffer;
        QEventLoop  *m_eventLoop;
		QHttp       *m_http;
		
	private:
		static QString TWITTER_HOST;
        static QString VERIFY_CREDENTIALS_URL;
		static QString PUBLIC_TIMELINE_URL;
        static QString GET_SINGLE_STATUS_URL;
        static QString FEATURED_USERS_URL;        
        static QString LOGOUT_URL;
        static QString IS_TWITTER_UP_URL;        
        static QString USERS_TIMELINE_URL;
        static QString GET_FAVORITES_URL;
        static QString FRIENDS_TIMELINE_URL;
        static QString POST_NEW_STATUS_URL;
        static QString GET_REPLIES_URL;
        static QString REMOVE_STATUS_URL;
        static QString GET_FRIENDS_URL;
        static QString GET_FOLLOWERS_URL;
        static QString GET_USER_DETAILS_URL;
        static QString GET_SENT_DIRECT_MESSAGES_URL;
        static QString GET_RECEIVED_DIRECT_MESSAGES_URL;
        static QString SEND_NEW_DIRECT_MESSAGE_URL;
        static QString REMOVE_DIRECT_MESSAGE_URL;        
        static QString CREATE_FRIENDSHIP_URL;
        static QString REMOVE_FRIENDSHIP_URL;
        static QString FRIENDSHIP_EXIST_URL;
        static QString UPDATE_LOCATION_URL;
        static QString UPDATE_DELIVERY_DEVICE_URL;
        static QString REMAINING_API_REQUESTS_URL;
        static QString ADD_FAVORITE_URL;
        static QString REMOVE_FAVORITE_URL;
};

#endif // Core_H




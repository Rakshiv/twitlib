#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <QtCore/QString>
#include "ui_example.h"
#include "QTwitLib.h"

#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>

class Example : public QWidget
{
	Q_OBJECT;
	public:
		Example();
		virtual ~Example();
	
	public:
		void SetupBasicUI();
		QString GetUsername();
		QString GetPassword();	
		
	public slots:
		void TabChanged(int tabIdx);
		void ExecuteClicked();
		void LoginClicked();
        void OnError(QString error); 
        void OnMessageReceived(QString message);
        void OnStatusReceived(SERVER::RESP response);

	public slots:
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

	private:
		void MakeConnections();
	
	private:
		enum TAB { PUBLIC_TIMELINE, FRIENDS_TIMELINE, SINGLE_STATUS, FEATURED_USERS, LOGIN, TWITTER_UP, USER_TIMELINE, FAVORITES, \
		           NEW_STATUS, RECENT_REPLIES, REMOVE_STATUS, FRIENDS, FOLLOWERS, USER_DETAILS, SENT_DIRECT_MESSAGES, \
		           RECEIVED_DIRECT_MESSAGES, SEND_DIRECT_MESSAGE, REMOVE_DIRECT_MESAGE, ADD_FRIENDSHIP, REMOVE_FRIENDSHIP, \
		           FRIENDSHIP_EXISTS, UPDATE_LOCATION, DELIVERY_DEVICE, API_REQUESTS, ADD_FAVORITE, REMOVE_FAVORITE };
		Ui::Form m_gui;
		QTwitLib  *m_twitLib;

	private:
		QPlainTextEdit *m_plainTextEdit;
		QLineEdit *m_lineEditUsername;
		QLineEdit *m_lineEditPassword;
		QLabel *m_labelUsername;
		QLabel *m_labelPassword;
		QPushButton *m_pushButtonLogin;
		QPushButton *m_pushButtonExecute;
};


#endif // EXAMPLE_H


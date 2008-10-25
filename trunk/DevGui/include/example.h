#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <QtCore/QString>
#include "ui_example.h"
#include "QTwitLib.h"

class Example : public QWidget
{
	Q_OBJECT;
	public:
		Example();
		virtual ~Example();
	
	public:
		QString GetUsername();
		QString GetPassword();	
		
	public slots:
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
		Ui::Form m_gui;
		QTwitLib  *m_twitLib;
};


#endif // EXAMPLE_H


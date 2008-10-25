#include <QtGui/QMessageBox>
#include "example.h"

//=====================================================================

//=====================================================================
Example::Example()
{
	m_gui.setupUi(this);
	m_twitLib = new QTwitLib();
	MakeConnections();
}
//=====================================================================
Example::~Example()
{
	if(m_twitLib)
		delete m_twitLib;
}
//=====================================================================
void Example::MakeConnections()
{

}
//=====================================================================
void Example::OnError(QString error) 
{ 
    //m_gui.plainTextEdit->appendPlainText("ERROR "+error); 
}
//=====================================================================
void Example::OnMessageReceived(QString message)
{ 
    //m_gui.plainTextEdit->appendPlainText("MESSAGE "+message); 
}
//=====================================================================
void Example::OnStatusReceived(SERVER::RESP response)
{
    //m_gui.plainTextEdit->appendPlainText("STATUS REC "+QString::number(response)); 
}
//=====================================================================
void Example::PublicTimeline(Returnables::PublicTimeline *) {}
//=====================================================================
void Example::FriendsTimeline(Returnables::FriendsTimeline *) {}
//=====================================================================
void Example::SingleStatus(Returnables::SingleStatus *) {}
//=====================================================================
void Example::FeaturedUsers(Returnables::FeaturedUsers *) {}
//=====================================================================
void Example::Login(Returnables::Login *) {}
//=====================================================================
void Example::TwitterUp(Returnables::TwitterUp *) {}
//=====================================================================
void Example::UserTimeline(Returnables::UserTimeline *) {}
//=====================================================================
void Example::Favorites(Returnables::Favorites *) {}
//=====================================================================
void Example::NewStatus(Returnables::NewStatus *) {}
//=====================================================================
void Example::RecentReplies(Returnables::RecentReplies *) {}
//=====================================================================
void Example::RemoveStatus(Returnables::RemoveStatus *) {}
//=====================================================================
void Example::Friends(Returnables::Friends *) {}
//=====================================================================
void Example::Followers(Returnables::Followers *) {}
//=====================================================================
void Example::UserDetails(Returnables::UserDetails *) {}
//=====================================================================
void Example::SentDirectMessages(Returnables::SentDirectMessages *) {}
//=====================================================================
void Example::ReceivedDirectMessages(Returnables::ReceivedDirectMessages *) {}
//=====================================================================
void Example::SendDirectMessage(Returnables::SendDirectMessage *) {}
//=====================================================================
void Example::RemoveDirectMessage(Returnables::RemoveDirectMessage *) {}
//=====================================================================
void Example::AddFriendship(Returnables::AddFriendship *) {}
//=====================================================================
void Example::RemoveFriendship(Returnables::RemoveFriendship *) {}
//=====================================================================
void Example::FriendshipExists(Returnables::FriendshipExist *) {}
//=====================================================================
void Example::UpdateLocation(Returnables::UpdateLocation *) {}
//=====================================================================
void Example::DeliveryDevice(Returnables::DeliveryDevice *) {}
//=====================================================================
void Example::ApiRequests(Returnables::ApiRequests *) {}
//=====================================================================
void Example::AddFavorite(Returnables::AddFavorite *) {}
//=====================================================================
void Example::RemoveFavorite(Returnables::RemoveFavorite *) {}
//=====================================================================
//=====================================================================
//=====================================================================
//=====================================================================
//=====================================================================
QString Example::GetUsername()
{
	return "";
}
//=====================================================================
QString Example::GetPassword()
{
	return "";
}
//=====================================================================

//=====================================================================
//=====================================================================


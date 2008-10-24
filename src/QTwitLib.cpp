
#include "QTwitLib.h"
#include "Core.h"

//=====================================================================
QTwitLib::QTwitLib()
{}
//=====================================================================
QTwitLib::~QTwitLib()
{}
//=====================================================================
void QTwitLib::GetPublicTimeline()
{
    Core::GetPublicTimeline();
}
//=====================================================================
void QTwitLib::GetSingleStatus(unsigned int id)
{
    Core::GetSingleStatus(QString::number(id));
}
//=====================================================================
void QTwitLib::GetFeaturedUsers()
{
    Core::GetFeaturedUsers();
}
//=====================================================================
void QTwitLib::Logout()
{
    Core::Logout();
}
//=====================================================================
void QTwitLib::Login(QString user, QString password)
{
    Core::Login(user, password);
}
//=====================================================================
void QTwitLib::IsTwitterUp()
{
    Core::IsTwitterUp();
}
//=====================================================================
void QTwitLib::GetUsersTimeline(SERVER::Option2 *opt  /*=NULL*/)
{
    Core::GetUsersTimeline(opt);
}
//=====================================================================
void QTwitLib::GetFavorites(QString user  /*=""*/, unsigned int page  /*=1*/)
{
    Core::GetFavorites(user, page);
}
//=====================================================================
void QTwitLib::GetFriendsTimeline(SERVER::Option1 *opt  /*=NULL*/)
{
    Core::GetFriendsTimeline(opt);
}
//=====================================================================
void QTwitLib::PostNewStatus(QString status)                                                
{
    Core::PostNewStatus(status);
}
//=====================================================================
void QTwitLib::GetRecentReplies(SERVER::Option3 *opt  /*=NULL*/)
{
    Core::GetRecentReplies(opt);
}
//=====================================================================
void QTwitLib::RemoveStatus(unsigned int id)
{
    Core::RemoveStatus(QString::number(id));
}
//=====================================================================
void QTwitLib::GetFriends(SERVER::Option4 *opt  /*=NULL*/)
{
    Core::GetFriends(opt);
}
//=====================================================================
void QTwitLib::GetFollowers(SERVER::Option5 *opt  /*=NULL*/)
{
    Core::GetFollowers(opt);
}
//=====================================================================
void QTwitLib::GetUserDetails(QString user)
{
    Core::GetUserDetails(user);
}
//=====================================================================
void QTwitLib::GetSentDirectMessages(SERVER::Option6 *opt  /*=NULL*/)
{
    Core::GetSentDirectMessages(opt);
}
//=====================================================================
void QTwitLib::GetReceivedDirectMessages(SERVER::Option6 *opt  /*=NULL*/)
{
    Core::GetReceivedDirectMessages(opt);
}
//=====================================================================
void QTwitLib::SendDirectMessage(QString user, QString text)
{
    Core::SendDirectMessage(user, text);
}
//=====================================================================
void QTwitLib::RemoveDirectMessage(unsigned int id)
{
    Core::RemoveDirectMessage(QString::number(id));
}
//=====================================================================
void QTwitLib::AddFriendship(QString user)
{
    Core::AddFriendship(user);
}
//=====================================================================
void QTwitLib::RemoveFriendship(QString user)
{
    Core::RemoveFriendship(user);
}
//=====================================================================
void QTwitLib::FriendshipExist(QString user_a, QString user_b)
{
    Core::FriendshipExist(user_a, user_b);
}
//=====================================================================
void QTwitLib::VerifyCredentials()
{
    Core::VerifyCredentials();
}
//=====================================================================
void QTwitLib::UpdateLocation(QString location)
{
    Core::UpdateLocation(location);
}
//=====================================================================
void QTwitLib::UpdateDeliveryDevice(SERVER::DEVICES device)
{
    Core::UpdateDeliveryDevice(device);
}
//=====================================================================
void QTwitLib::RemainingApiRequests()
{
    Core::RemainingApiRequests();
}
//=====================================================================
void QTwitLib::AddFavorite(unsigned int id)
{
    Core::AddFavorite(QString::number(id));
}
//=====================================================================
void QTwitLib::RemoveFavorite(unsigned int id)
{
    Core::RemoveFavorite(QString::number(id));
}
//=====================================================================
void QTwitLib::StartFollow(QString user)
{
    Core::StartFollow(user);
}
//=====================================================================
void QTwitLib::StopFollow(QString user)
{
    Core::StopFollow(user);
}
//=====================================================================
void QTwitLib::BlockUser(QString user)
{
    Core::BlockUser(user);
}
//=====================================================================
void QTwitLib::UnBlockUser(QString user)
{
    Core::UnBlockUser(user);
}
//=====================================================================


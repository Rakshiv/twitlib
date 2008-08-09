
#include "QTwitLib.h"
#include "Core.h"

//=====================================================================
QTwitLib::QTwitLib(ITwitReply *obj)
{
    m_core = new Core(obj);
}
//=====================================================================
QTwitLib::~QTwitLib()
{
    if(m_core)
    {
        delete m_core;
        m_core = NULL;
    }
}
//=====================================================================
void QTwitLib::GetPublicTimeline()
{
    m_core->GetPublicTimeline();
}
//=====================================================================
void QTwitLib::GetSingleStatus(int id)
{
    m_core->GetSingleStatus(QString::number(id));
}
//=====================================================================
void QTwitLib::GetFeaturedUsers()
{
    m_core->GetFeaturedUsers();
}
//=====================================================================
void QTwitLib::Logout()
{
    m_core->Logout();
}
//=====================================================================
void QTwitLib::Login(std::string user, std::string password)
{
    m_core->Login(QString(user.c_str()),QString(password.c_str()));
}
//=====================================================================
void QTwitLib::GetDowntimeSchedule()
{
    m_core->GetDowntimeSchedule();
}
//=====================================================================
void QTwitLib::IsTwitterUp()
{
    m_core->IsTwitterUp();
}
//=====================================================================
void QTwitLib::GetUsersTimeline(SERVER::Option2 *opt  /*=NULL*/)
{
    m_core->GetUsersTimeline(opt);
}
//=====================================================================
void QTwitLib::GetFavorites(std::string user  /*=""*/, int page  /*=1*/)
{
    m_core->GetFavorites(QString(user.c_str()),page);
}
//=====================================================================
void QTwitLib::GetFriendsTimeline(SERVER::Option1 *opt  /*=NULL*/)
{
    m_core->GetFriendsTimeline(opt);
}
//=====================================================================
void QTwitLib::PostNewStatus(std::string status)                                                
{
    m_core->PostNewStatus(QString(status.c_str()));
}
//=====================================================================
void QTwitLib::GetRecentReplies(SERVER::Option3 *opt  /*=NULL*/)
{
    m_core->GetRecentReplies(opt);
}
//=====================================================================
void QTwitLib::RemoveStatus(int id)
{
    m_core->RemoveStatus(QString::number(id));
}
//=====================================================================
void QTwitLib::GetFriends(SERVER::Option4 *opt  /*=NULL*/)
{
    m_core->GetFriends(opt);
}
//=====================================================================
void QTwitLib::GetFollowers(SERVER::Option5 *opt  /*=NULL*/)
{
    m_core->GetFollowers(opt);
}
//=====================================================================
void QTwitLib::GetUserDetails(std::string user)
{
    m_core->GetUserDetails(QString(user.c_str()));
}
//=====================================================================
void QTwitLib::GetSentDirectMessages(SERVER::Option6 *opt  /*=NULL*/)
{
    m_core->GetSentDirectMessages(opt);
}
//=====================================================================
void QTwitLib::GetReceivedDirectMessages(SERVER::Option6 *opt  /*=NULL*/)
{
    m_core->GetReceivedDirectMessages(opt);
}
//=====================================================================
void QTwitLib::SendDirectMessage(std::string user, std::string text)
{
    m_core->SendDirectMessage(QString(user.c_str()), QString(text.c_str()));
}
//=====================================================================
void QTwitLib::RemoveDirectMessage(int id)
{
    m_core->RemoveDirectMessage(QString::number(id));
}
//=====================================================================
void QTwitLib::AddFriendship(std::string user)
{
    m_core->AddFriendship(QString(user.c_str()));
}
//=====================================================================
void QTwitLib::RemoveFriendship(std::string user)
{
    m_core->RemoveFriendship(QString(user.c_str()));
}
//=====================================================================
void QTwitLib::FriendshipExist(std::string user_a, std::string user_b)
{
    m_core->FriendshipExist(QString(user_a.c_str()), QString(user_b.c_str()));
}
//=====================================================================
void QTwitLib::VerifyCredentials()
{
    m_core->VerifyCredentials();
}
//=====================================================================
void QTwitLib::UpdateLocation(std::string location)
{
    m_core->UpdateLocation(QString(location.c_str()));
}
//=====================================================================
void QTwitLib::UpdateDeliveryDevice(SERVER::DEVICES device)
{
    m_core->UpdateDeliveryDevice(device);
}
//=====================================================================
void QTwitLib::RemainingApiRequests()
{
    m_core->RemainingApiRequests();
}
//=====================================================================
void QTwitLib::AddFavorite(int id)
{
    m_core->AddFavorite(QString::number(id));
}
//=====================================================================
void QTwitLib::RemoveFavorite(int id)
{
    m_core->RemoveFavorite(QString::number(id));
}
//=====================================================================
void QTwitLib::StartFollow(std::string user)
{
    m_core->StartFollow(QString(user.c_str()));
}
//=====================================================================
void QTwitLib::StopFollow(std::string user)
{
    m_core->StopFollow(QString(user.c_str()));
}
//=====================================================================
void QTwitLib::BlockUser(std::string user)
{
    m_core->BlockUser(QString(user.c_str()));
}
//=====================================================================
void QTwitLib::UnBlockUser(std::string user)
{
    m_core->UnBlockUser(QString(user.c_str()));
}
//=====================================================================


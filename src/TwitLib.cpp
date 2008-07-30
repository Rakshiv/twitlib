
#include "TwitLib.h"
#include "Core.h"

//=====================================================================
TwitLib::TwitLib(ITwitReply *obj)
{
    m_core = new Core(obj);
}
//=====================================================================
TwitLib::~TwitLib()
{
    if(m_core)
    {
        delete m_core;
        m_core = NULL;
    }
}
//=====================================================================
void TwitLib::GetPublicTimeline()
{
    m_core->GetPublicTimeline();
}
//=====================================================================
void TwitLib::GetSingleStatus(int id)
{
    m_core->GetSingleStatus(QString::number(id));
}
//=====================================================================
void TwitLib::GetFeaturedUsers()
{
    m_core->GetFeaturedUsers();
}
//=====================================================================
void TwitLib::Logout()
{
    m_core->Logout();
}
//=====================================================================
void TwitLib::Login(std::string user, std::string password)
{
    m_core->Login(QString(user.c_str()),QString(password.c_str()));
}
//=====================================================================
void TwitLib::GetDowntimeSchedule()
{
    m_core->GetDowntimeSchedule();
}
//=====================================================================
void TwitLib::IsTwitterUp()
{
    m_core->IsTwitterUp();
}
//=====================================================================
void TwitLib::GetUsersTimeline(SERVER::Option2 *opt  /*=NULL*/)
{
    m_core->GetUsersTimeline(opt);
}
//=====================================================================
void TwitLib::GetFavorites(std::string user  /*=""*/, int page  /*=1*/)
{
    m_core->GetFavorites(QString(user.c_str()),page);
}
//=====================================================================
void TwitLib::GetFriendsTimeline(SERVER::Option1 *opt  /*=NULL*/)
{
    m_core->GetFriendsTimeline(opt);
}
//=====================================================================
void TwitLib::PostNewStatus(std::string status)                                                
{
    m_core->PostNewStatus(QString(status.c_str()));
}
//=====================================================================
void TwitLib::GetRecentReplies(SERVER::Option3 *opt  /*=NULL*/)
{
    m_core->GetRecentReplies(opt);
}
//=====================================================================
void TwitLib::RemoveStatus(int id)
{
    m_core->RemoveStatus(QString::number(id));
}
//=====================================================================
void TwitLib::GetFriends(SERVER::Option4 *opt  /*=NULL*/)
{
    m_core->GetFriends(opt);
}
//=====================================================================
void TwitLib::GetFollowers(SERVER::Option5 *opt  /*=NULL*/)
{
    m_core->GetFollowers(opt);
}
//=====================================================================
void TwitLib::GetUserDetails(std::string user)
{
    m_core->GetUserDetails(QString(user.c_str()));
}
//=====================================================================
void TwitLib::GetSentDirectMessages(SERVER::Option6 *opt  /*=NULL*/)
{
    m_core->GetSentDirectMessages(opt);
}
//=====================================================================
void TwitLib::GetReceivedDirectMessages(SERVER::Option6 *opt  /*=NULL*/)
{
    m_core->GetReceivedDirectMessages(opt);
}
//=====================================================================
void TwitLib::SendDirectMessage(std::string user, std::string text)
{
    m_core->SendDirectMessage(QString(user.c_str()), QString(text.c_str()));
}
//=====================================================================
void TwitLib::RemoveDirectMessage(int id)
{
    m_core->RemoveDirectMessage(QString::number(id));
}
//=====================================================================
void TwitLib::AddFriendship(std::string user)
{
    m_core->AddFriendship(QString(user.c_str()));
}
//=====================================================================
void TwitLib::RemoveFriendship(std::string user)
{
    m_core->RemoveFriendship(QString(user.c_str()));
}
//=====================================================================
void TwitLib::FriendshipExist(std::string user_a, std::string user_b)
{
    m_core->FriendshipExist(QString(user_a.c_str()), QString(user_b.c_str()));
}
//=====================================================================
void TwitLib::VerifyCredentials()
{
    m_core->VerifyCredentials();
}
//=====================================================================
void TwitLib::UpdateLocation(std::string location)
{
    m_core->UpdateLocation(QString(location.c_str()));
}
//=====================================================================
void TwitLib::UpdateDeliveryDevice(SERVER::DEVICES device)
{
    m_core->UpdateDeliveryDevice(device);
}
//=====================================================================
void TwitLib::RemainingApiRequests()
{
    m_core->RemainingApiRequests();
}
//=====================================================================
void TwitLib::AddFavorite(int id)
{
    m_core->AddFavorite(QString::number(id));
}
//=====================================================================
void TwitLib::RemoveFavorite(int id)
{
    m_core->RemoveFavorite(QString::number(id));
}
//=====================================================================
void TwitLib::StartFollow(std::string user)
{
    m_core->StartFollow(QString(user.c_str()));
}
//=====================================================================
void TwitLib::StopFollow(std::string user)
{
    m_core->StopFollow(QString(user.c_str()));
}
//=====================================================================
void TwitLib::BlockUser(std::string user)
{
    m_core->BlockUser(QString(user.c_str()));
}
//=====================================================================
void TwitLib::UnBlockUser(std::string user)
{
    m_core->UnBlockUser(QString(user.c_str()));
}
//=====================================================================


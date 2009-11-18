/*
    This file is part of QTwitlib.

    QTwitlib is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    QTwitlib is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QTwitlib.  If not, see <http://www.gnu.org/licenses/>.
	
	Original Author: Bradley Lackey
*/

#include <QtGui>
#include "example.h"

//=====================================================================

//=====================================================================
Example::Example()
{
        m_gui.setupUi(this);

        m_twitLib = new QTwitLib();
        m_plainTextEdit = new QPlainTextEdit();
        m_pushButtonExecute = new QPushButton();
        m_pushButtonExecute->setText("Execute");
        m_lineEditUsername = new QLineEdit();
        m_lineEditPassword = new QLineEdit();
        m_lineEditPassword->setEchoMode(QLineEdit::Password);
        m_labelUsername = new QLabel();
        m_labelUsername->setText("Username");
        m_labelPassword = new QLabel();
        m_labelPassword->setText("Password");
        m_pushButtonLogin = new QPushButton();
        m_pushButtonLogin->setText("Login");

        MakeConnections();
        SetupBasicUI();
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
        connect(m_gui.tabWidget,SIGNAL(currentChanged(int)),this,SLOT(TabChanged(int)));
        connect(m_pushButtonExecute,SIGNAL(clicked()),this,SLOT(ExecuteClicked()));
        connect(m_pushButtonLogin,SIGNAL(clicked()),this,SLOT(LoginClicked()));
        connect(m_twitLib,SIGNAL(OnResponseReceived(Returnables::Response *)),this,SLOT(OnResponseReceived(Returnables::Response *)));
}
//=====================================================================
void Example::OnError(QString error)
{
    m_plainTextEdit->appendPlainText("ERROR "+error);
}
//=====================================================================
void Example::OnMessageReceived(QString message)
{
    m_plainTextEdit->appendPlainText("MESSAGE "+message);
}
//=====================================================================
void Example::OnStatusReceived(SERVER::RESP response)
{
    m_plainTextEdit->appendPlainText("STATUS REC "+QString::number(response));
}
//=====================================================================
void Example::DisplayList(QLinkedList<Returnables::StatusElement*> list, QString header)
{
        Returnables::StatusElement *element = NULL;

        m_plainTextEdit->appendPlainText("----------------StatusElement-----------------");
        m_plainTextEdit->appendHtml("<h2>"+header+"</h2>");
        m_plainTextEdit->appendPlainText("");
        QString boolText;

        while(!list.isEmpty())
        {
                element = list.takeFirst();
                m_plainTextEdit->appendPlainText("<status>");
                m_plainTextEdit->appendPlainText("created_at: " + element->status.createdAt);
                m_plainTextEdit->appendPlainText("id: " + QString::number(element->status.id));
                m_plainTextEdit->appendPlainText("text: " + element->status.text);
                m_plainTextEdit->appendPlainText("source: " + element->status.source);
                    boolText = element->user.isProtected ? "true" : "false";
                m_plainTextEdit->appendPlainText("truncated: " + boolText);
                m_plainTextEdit->appendPlainText("in_reply_to_status_id: " + QString::number(element->status.inReplyToStatusId));
                m_plainTextEdit->appendPlainText("in_reply_to_user_id: " + QString::number(element->status.inReplyToUserId));
                    boolText = element->status.favorited ? "true" : "false";
                m_plainTextEdit->appendPlainText("favorited: " + boolText);
                m_plainTextEdit->appendPlainText("<user>");
                m_plainTextEdit->appendPlainText("id: " + QString::number(element->user.id));
                m_plainTextEdit->appendPlainText("name: " + element->user.name);
                m_plainTextEdit->appendPlainText("screen_name: " + element->user.screenName);
                m_plainTextEdit->appendPlainText("description: " + element->user.description);
                m_plainTextEdit->appendPlainText("location: " + element->user.location);
                m_plainTextEdit->appendPlainText("profile_image_url: " + element->user.profileImageUrl);
                m_plainTextEdit->appendPlainText("url: " + element->user.url);
                    boolText = element->user.isProtected ? "true" : "false";
                m_plainTextEdit->appendPlainText("protected: " + boolText);
                m_plainTextEdit->appendPlainText("followers_count: " + QString::number(element->user.followersCount));
                m_plainTextEdit->appendPlainText("");
        }
}
void Example::DisplayList(QLinkedList<Returnables::BasicUserInfoElement*> list, QString header)
{
        Returnables::BasicUserInfoElement *element = NULL;

        m_plainTextEdit->appendPlainText("---------------BasicUserInfoElement------------------");
        m_plainTextEdit->appendHtml("<h2>"+header+"</h2>");
        m_plainTextEdit->appendPlainText("");
        QString boolText;

        while(!list.isEmpty())
        {
                element = list.takeFirst();
                m_plainTextEdit->appendPlainText("<user>");
                m_plainTextEdit->appendPlainText("id: " + QString::number(element->user.id));
                m_plainTextEdit->appendPlainText("name: " + element->user.name);
                m_plainTextEdit->appendPlainText("screen_name: " + element->user.screenName);
                m_plainTextEdit->appendPlainText("location: " + element->user.location);
                m_plainTextEdit->appendPlainText("description: " + element->user.description);
                m_plainTextEdit->appendPlainText("profile_image_url: " + element->user.profileImageUrl);
                m_plainTextEdit->appendPlainText("url: " + element->user.url);
                    boolText = element->user.isProtected ? "true" : "false";
                m_plainTextEdit->appendPlainText("protected: " + boolText);
                m_plainTextEdit->appendPlainText("followers_count: " + QString::number(element->user.followersCount));
                m_plainTextEdit->appendPlainText("<status>");
                m_plainTextEdit->appendPlainText("created_at: " + element->status.createdAt);
                m_plainTextEdit->appendPlainText("id: " + QString::number(element->status.id));
                m_plainTextEdit->appendPlainText("text: " + element->status.text);
                m_plainTextEdit->appendPlainText("source: " + element->status.source);
                    boolText = element->status.truncated ? "true" : "false";
                m_plainTextEdit->appendPlainText("truncated: " + boolText);
                m_plainTextEdit->appendPlainText("in_reply_to_status_id: " + QString::number(element->status.inReplyToStatusId));
                m_plainTextEdit->appendPlainText("in_reply_to_user_id: " + QString::number(element->status.inReplyToUserId));
                    boolText = element->status.favorited ? "true" : "false";
                m_plainTextEdit->appendPlainText("favorited: " + boolText);
                m_plainTextEdit->appendPlainText("in_reply_to_screen_name: " + element->status.inReplyToScreenName);

                m_plainTextEdit->appendPlainText("");

        }
}
//==========================================================================
void Example::DisplayList(QLinkedList<Returnables::ExtUserInfoElement*> list, QString header)
{
        Returnables::ExtUserInfoElement *element = NULL;

        m_plainTextEdit->appendPlainText("----------------ExtUserInfoElement-----------------");
        m_plainTextEdit->appendHtml("<h2>"+header+"</h2>");
        m_plainTextEdit->appendPlainText("");
        QString boolText;

        while(!list.isEmpty())
        {
                element = list.takeFirst();
                m_plainTextEdit->appendPlainText("<user>");
                m_plainTextEdit->appendPlainText("id: " + QString::number(element->user.id));
                m_plainTextEdit->appendPlainText("name: " + element->user.name);
                m_plainTextEdit->appendPlainText("screen_name: " + element->user.screenName);
                m_plainTextEdit->appendPlainText("location: " + element->user.location);
                m_plainTextEdit->appendPlainText("description: " + element->user.description);
                m_plainTextEdit->appendPlainText("profile_image_url: " + element->user.profileImageUrl);
                m_plainTextEdit->appendPlainText("url: " + element->user.url);
                    boolText = element->user.isProtected ? "true" : "false";
                m_plainTextEdit->appendPlainText("protected: " + boolText);
                m_plainTextEdit->appendPlainText("followers_count: " + QString::number(element->user.followersCount));
                m_plainTextEdit->appendPlainText("DETAILS");
                m_plainTextEdit->appendPlainText("profile_background_color: " + element->details.profileBackgroundColor);
                m_plainTextEdit->appendPlainText("profile_text_color: " + element->details.profileTextColor);
                m_plainTextEdit->appendPlainText("profile_link_color: " + element->details.profileLinkColor);
                m_plainTextEdit->appendPlainText("profile_sidebar_fill_color: " + element->details.profileSidebarFillColor);
                m_plainTextEdit->appendPlainText("profile_sidebar_border_color: " + element->details.profileSidebarBorderColor);
                m_plainTextEdit->appendPlainText("friends_count: " + QString::number(element->details.friendsCount));
                m_plainTextEdit->appendPlainText("created_at: " + element->details.createdAt);
                m_plainTextEdit->appendPlainText("favorites_count: " + QString::number(element->details.favoritesCount));
                m_plainTextEdit->appendPlainText("utc_offset: " + QString::number(element->details.utcOffset));
                m_plainTextEdit->appendPlainText("time_zone: " + element->details.timeZone);
                m_plainTextEdit->appendPlainText("profile_background_image_url: " + element->details.profileBackgroundImageUrl);
                    boolText = element->details.profileBackgroundTiled ? "true" : "false";
                m_plainTextEdit->appendPlainText("profile_background_tile: " + boolText);
                    boolText = element->details.following ? "true" : "false";
                m_plainTextEdit->appendPlainText("following: " + boolText);
                     boolText = element->details.notifications ? "true" : "false";
                m_plainTextEdit->appendPlainText("notifications: " + boolText);
                m_plainTextEdit->appendPlainText("statuses_count: " + QString::number(element->details.statusesCount));
                m_plainTextEdit->appendPlainText("<status>");
                m_plainTextEdit->appendPlainText("created_at: " + element->status.createdAt);
                m_plainTextEdit->appendPlainText("id: " + QString::number(element->status.id));
                m_plainTextEdit->appendPlainText("text: " + element->status.text);
                m_plainTextEdit->appendPlainText("source: " + element->status.source);
                    boolText = element->status.truncated ? "true" : "false";
                m_plainTextEdit->appendPlainText("truncated: " + boolText);
                m_plainTextEdit->appendPlainText("in_reply_to_status_id: " + QString::number(element->status.inReplyToStatusId));
                m_plainTextEdit->appendPlainText("in_reply_to_user_id: " + QString::number(element->status.inReplyToUserId));
                    boolText = element->status.favorited ? "true" : "false";
                m_plainTextEdit->appendPlainText("favorited: " + boolText);
                m_plainTextEdit->appendPlainText("in_reply_to_screen_name: " + element->status.inReplyToScreenName);

            m_plainTextEdit->appendPlainText("");
        }
}
//=====================================================================
void Example::DisplayList(QLinkedList<unsigned int> list, QString header)
{
        unsigned int element;

        m_plainTextEdit->appendPlainText("----------------IDs LIST-----------------");
        m_plainTextEdit->appendHtml("<h2>"+header+"</h2>");
        m_plainTextEdit->appendPlainText("");

        while(!list.isEmpty())
        {
                element = list.takeFirst();
                m_plainTextEdit->appendPlainText("id: " + QString::number(element));
        }
}
//=====================================================================
void Example::DisplayList(QLinkedList<Returnables::DirectMessageElement*> list, QString header)
{
        Returnables::DirectMessageElement *directMessage = NULL;

        m_plainTextEdit->appendPlainText("---------------------------------");
        m_plainTextEdit->appendHtml("<h2>"+header+"</h2>");
        m_plainTextEdit->appendPlainText("");

        while(!list.isEmpty())
        {
                directMessage = list.takeFirst();
                m_plainTextEdit->appendPlainText("ID: "+QString::number(directMessage->headerInfo.id));
                m_plainTextEdit->appendPlainText("Sender: "+directMessage->sender.screenName);
                m_plainTextEdit->appendPlainText("Recipient: "+directMessage->recipient.screenName);
                m_plainTextEdit->appendPlainText("Created At: "+directMessage->headerInfo.createdAt);
                m_plainTextEdit->appendPlainText("Text: "+directMessage->headerInfo.text);
                m_plainTextEdit->appendPlainText("");
        }
}
//=====================================================================
void Example::OnResponseReceived(Returnables::Response *resp)
{
        if(resp)
    {
                switch(resp->reqID)
                {
                case Returnables::PUBLIC_TIMELINE:
                        {
                                Returnables::PublicTimeline *pTimeline = static_cast<Returnables::PublicTimeline *>(resp);
                                DisplayList(pTimeline->list, "Public Timeline");
                                delete pTimeline;
                                break;
                        }
                case Returnables::FRIENDS_TIMELINE:
                        {
                                Returnables::FriendsTimeline *fTimeline = static_cast<Returnables::FriendsTimeline *>(resp);
                                DisplayList(fTimeline->list, "Friends Timeline");
                                delete fTimeline;
                                break;
                        }
                case Returnables::SINGLE_STATUS:
                        {
                                Returnables::SingleStatus *singleStatus = static_cast<Returnables::SingleStatus *>(resp);
                                QLinkedList<Returnables::StatusElement *> list;
                                list.append(singleStatus->status);
                                DisplayList(list, "Single Status");
                                delete singleStatus;
                                break;
                        }
                case Returnables::FEATURED_USERS:
                        {
                                Returnables::FeaturedUsers *featuredUsers = static_cast<Returnables::FeaturedUsers *>(resp);
                                DisplayList(featuredUsers->list, "Featured Users");
                                delete featuredUsers;
                                break;
                        }
                case Returnables::TWITTER_UP:
                        {
                                Returnables::TwitterUp *twitterUp = static_cast<Returnables::TwitterUp *>(resp);
                                m_plainTextEdit->appendHtml("<h2>Twitter Up</h2>");
                                m_plainTextEdit->appendPlainText("");
                                QString up = twitterUp->up ? "true" : "false";
                                m_plainTextEdit->appendPlainText("Up: "+up);
                                delete twitterUp;
                                break;
                        }
                case Returnables::USER_TIMELINE:
                        {
                                Returnables::UserTimeline *userTimeline = static_cast<Returnables::UserTimeline *>(resp);
                                DisplayList(userTimeline->list, "Users Timeline");
                                delete userTimeline;
                                break;
                        }
                case Returnables::FAVORITES:
                        {
                                Returnables::Favorites *favorites = static_cast<Returnables::Favorites *>(resp);
                                DisplayList(favorites->list, "Favorites");
                                delete favorites;
                                break;
                        }
                case Returnables::NEW_STATUS:
                        {
                                Returnables::NewStatus *newStatus = static_cast<Returnables::NewStatus *>(resp);
                                QLinkedList<Returnables::StatusElement*> list;
                                list.append(newStatus->status);
                                DisplayList(list, "New Status");
                                delete newStatus;
                                break;
                        }
                case Returnables::RECENT_MENTIONS:
                        {
                                Returnables::RecentMentions *mentions = static_cast<Returnables::RecentMentions *>(resp);
                                DisplayList(mentions->list, "Recent Mentions");
                                delete mentions;
                                break;
                        }
                case Returnables::REMOVE_STATUS:
                        {
                                Returnables::RemoveStatus *removedStatus = static_cast<Returnables::RemoveStatus *>(resp);
                                QLinkedList<Returnables::StatusElement*> list;
                                list.append(removedStatus->status);
                                DisplayList(list, "Remove Status");
                                delete removedStatus;
                                break;
                        }
                case Returnables::FRIENDS:
                        {
                                Returnables::Friends *friends = static_cast<Returnables::Friends *>(resp);
                                DisplayList(friends->list, "Friends");
                                delete friends;
                                break;
                        }
                case Returnables::FOLLOWERS:
                        {
                                Returnables::Followers *followers = static_cast<Returnables::Followers *>(resp);
                                DisplayList(followers->list, "Followers");
                                delete followers;
                                break;
                        }
                case Returnables::USER_DETAILS:
                        {
                                Returnables::UserDetails *userDetails = static_cast<Returnables::UserDetails *>(resp);
                                QLinkedList<Returnables::ExtUserInfoElement*> list;
                                list.append(userDetails->userExt);
                                DisplayList(list, "User Details");
                                delete userDetails;
                                break;
                        }
                case Returnables::VERIFY_CREDENTIALS:
                        {
                                Returnables::VerifyCredentials *verifyCredentials = static_cast<Returnables::VerifyCredentials *>(resp);
                                QLinkedList<Returnables::ExtUserInfoElement *> list;
                                list.append(verifyCredentials->userExt);
                                DisplayList(list, "Verify Credentials");
                                delete verifyCredentials;
                                break;
                        }
                case Returnables::SENT_DIRECT_MESSAGES:
                        {
                                Returnables::SentDirectMessages *sentDirectMessages = static_cast<Returnables::SentDirectMessages *>(resp);
                                DisplayList(sentDirectMessages->list, "Sent Direct Messages");
                                delete sentDirectMessages;
                                break;
                        }
                case Returnables::RECEIVED_DIRECT_MESSAGES:
                        {
                                Returnables::ReceivedDirectMessages *receivedDirectMessages = static_cast<Returnables::ReceivedDirectMessages *>(resp);
                                DisplayList(receivedDirectMessages->list, "Received Direct Messages");
                                delete receivedDirectMessages;
                                break;
                        }
                case Returnables::SEND_DIRECT_MESSAGE:
                        {
                                Returnables::SendDirectMessage *sendDirectMessage = static_cast<Returnables::SendDirectMessage *>(resp);
                                m_plainTextEdit->appendHtml("<h2>Send Direct Messages</h2>");
                                m_plainTextEdit->appendPlainText("");
                                m_plainTextEdit->appendPlainText("ID: "+QString::number(sendDirectMessage->message->headerInfo.id));
                                m_plainTextEdit->appendPlainText("Sender: "+sendDirectMessage->message->sender.screenName);
                                m_plainTextEdit->appendPlainText("Recipient: "+sendDirectMessage->message->recipient.screenName);
                                m_plainTextEdit->appendPlainText("Created At: "+sendDirectMessage->message->headerInfo.createdAt);
                                m_plainTextEdit->appendPlainText("Text: "+sendDirectMessage->message->headerInfo.text);
                                delete sendDirectMessage;
                                break;
                        }
                case Returnables::REMOVE_DIRECT_MESSAGE:
                        {
                                Returnables::RemoveDirectMessage *removeDirectMessage = static_cast<Returnables::RemoveDirectMessage *>(resp);
                                m_plainTextEdit->appendHtml("<h2>Remove Direct Messages</h2>");
                                m_plainTextEdit->appendPlainText("");
                                m_plainTextEdit->appendPlainText("ID: "+QString::number(removeDirectMessage->message->headerInfo.id));
                                m_plainTextEdit->appendPlainText("Sender: "+removeDirectMessage->message->sender.screenName);
                                m_plainTextEdit->appendPlainText("Recipient: "+removeDirectMessage->message->recipient.screenName);
                                m_plainTextEdit->appendPlainText("Created At: "+removeDirectMessage->message->headerInfo.createdAt);
                                m_plainTextEdit->appendPlainText("Text: "+removeDirectMessage->message->headerInfo.text);
                                delete removeDirectMessage;
                                break;
                        }
                case Returnables::ADD_FRIENDSHIP:
                        {
                                Returnables::AddFriendship *addFriendship = static_cast<Returnables::AddFriendship *>(resp);
                                QLinkedList<Returnables::BasicUserInfoElement*> list;
                                list.append(addFriendship->user);
                                DisplayList(list, "Add Friendship");
                                delete addFriendship;
                                break;
                        }
                case Returnables::REMOVE_FRIENDSHIP:
                        {
                                Returnables::RemoveFriendship *removeFriendship = static_cast<Returnables::RemoveFriendship *>(resp);
                                QLinkedList<Returnables::BasicUserInfoElement*> list;
                                list.append(removeFriendship->user);
                                DisplayList(list, "Remove Friendship");
                                delete removeFriendship;
                                break;
                        }
                case Returnables::FRIENDSHIP_EXISTS:
                        {
                                Returnables::FriendshipExist *friendshipExists = static_cast<Returnables::FriendshipExist *>(resp);
                                m_plainTextEdit->appendHtml("<h2>Friendship Exist</h2>");
                                m_plainTextEdit->appendPlainText("");
                                QString friends = friendshipExists->friends ? "true" : "false";
                                m_plainTextEdit->appendPlainText("Are Friends?: "+friends);
                                delete friendshipExists;
                                break;
                        }
                case Returnables::DELIVERY_DEVICE:
                        {
                                Returnables::DeliveryDevice *deliveryDevice = static_cast<Returnables::DeliveryDevice *>(resp);
                                QLinkedList<Returnables::BasicUserInfoElement*> list;
                                list.append(deliveryDevice->user);
                                DisplayList(list, "Update Delivery Device");
                                delete deliveryDevice;
                                break;
                        }
                case Returnables::API_REQUESTS:
                        {
                                Returnables::ApiRequests *apiRequests = static_cast<Returnables::ApiRequests *>(resp);
                                m_plainTextEdit->appendHtml("<h2>Remaining API requests</h2>");
                                m_plainTextEdit->appendPlainText("");
                                m_plainTextEdit->appendPlainText("Hourly Limit: "+QString::number(apiRequests->hourlyLimit));
                                m_plainTextEdit->appendPlainText("Remaining hits: "+QString::number(apiRequests->remainingHits));
                                m_plainTextEdit->appendPlainText("Reset time: "+apiRequests->resetTime);
                                m_plainTextEdit->appendPlainText("Reset time in seconds: "+QString::number(apiRequests->resetTimeSeconds));
                                delete apiRequests;
                                break;
                        }
                case Returnables::ADD_FAVORITE:
                        {
                                Returnables::AddFavorite *addFavorite = static_cast<Returnables::AddFavorite *>(resp);
                                QLinkedList<Returnables::StatusElement*> list;
                                list.append(addFavorite->status);
                                DisplayList(list, "Add Favorite");
                                delete addFavorite;
                                break;
                        }
                case Returnables::REMOVE_FAVORITE:
                        {
                                Returnables::RemoveFavorite *removeFavorite = static_cast<Returnables::RemoveFavorite *>(resp);
                                QLinkedList<Returnables::StatusElement*> list;
                                list.append(removeFavorite->status);
                                DisplayList(list, "Remove Favorite");
                                delete removeFavorite;
                                break;
                        }
                case Returnables::PROFILE_COLORS:
                        {
                                Returnables::ProfileColors *profileColors = static_cast<Returnables::ProfileColors*>(resp);
                                QLinkedList<Returnables::ExtUserInfoElement*> list;
                                list.append(profileColors->userExt);
                                DisplayList(list, "Profile Colors");
                                delete profileColors;
                                break;
                        }
                case Returnables::PROFILE_IMAGE:
                        {
                                Returnables::ProfileImage *profileImage = static_cast<Returnables::ProfileImage*>(resp);
                                QLinkedList<Returnables::ExtUserInfoElement*> list;
                                list.append(profileImage->userExt);
                                DisplayList(list, "Profile Image");
                                delete profileImage;
                                break;
                        }
                case Returnables::PROFILE_BACKGROUND_IMAGE:
                        {
                                Returnables::ProfileBackgroundImage *profileBackgroundImage = static_cast<Returnables::ProfileBackgroundImage*>(resp);
                                QLinkedList<Returnables::ExtUserInfoElement*> list;
                                list.append(profileBackgroundImage->userExt);
                                DisplayList(list, "Profile Background Image");
                                delete profileBackgroundImage;
                                break;
                        }
                case Returnables::PROFILE:
                        {
                                Returnables::Profile *profile = static_cast<Returnables::Profile*>(resp);
                                QLinkedList<Returnables::ExtUserInfoElement*> list;
                                list.append(profile->userExt);
                                DisplayList(list, "Profile");
                                delete profile;
                                break;
                        }
                case Returnables::FRIENDS_IDS:
                        {
                            Returnables::FriendsIDs *friendsIDs = static_cast<Returnables::FriendsIDs*>(resp);
                            DisplayList(friendsIDs->list, "FriendsIDs");
                            delete friendsIDs;
                            break;
                        }
                case Returnables::FOLLOWERS_IDS:
                        {
                            Returnables::FollowersIDs *followersIDs = static_cast<Returnables::FollowersIDs*>(resp);
                            DisplayList(followersIDs->list, "FollowersIDs");
                            delete followersIDs;
                            break;
                        }
                case Returnables::ENABLE_NOTIFICATIONS:
                        {
                            Returnables::EnableNotifications *enableNotifications = static_cast<Returnables::EnableNotifications*>(resp);
                            QLinkedList<Returnables::BasicUserInfoElement*> list;
                            list.append(enableNotifications->user);
                            DisplayList(list, "Enable Notifications");
                            delete enableNotifications;
                            break;
                        }
                case Returnables::DISABLE_NOTIFICATIONS:
                        {
                            Returnables::DisableNotifications *disableNotifications = static_cast<Returnables::DisableNotifications*>(resp);
                            QLinkedList<Returnables::BasicUserInfoElement*>list;
                            list.append(disableNotifications->user);
                            DisplayList(list, "Disable Notifications");
                            delete disableNotifications;
                            break;
                        }
                case Returnables::BLOCK_USER:
                        {
                            Returnables::BlockUser *blockUser = static_cast<Returnables::BlockUser*>(resp);
                            QLinkedList<Returnables::BasicUserInfoElement*> list;
                            list.append(blockUser->user);
                            DisplayList(list, "Block User");
                            delete blockUser;
                            break;
                        }
                case Returnables::UNBLOCK_USER:
                        {
                            Returnables::UnBlockUser *unBlockUser = static_cast<Returnables::UnBlockUser*>(resp);
                            QLinkedList<Returnables::BasicUserInfoElement*> list;
                            list.append(unBlockUser->user);
                            DisplayList(list, "UnBlock User");
                            delete unBlockUser;
                            break;
                        }
                }
                m_plainTextEdit->verticalScrollBar()->setSliderPosition(0);
        }
}
//=====================================================================
QString Example::GetUsername()
{
        return m_lineEditUsername->text();
}
//=====================================================================
QString Example::GetPassword()
{
        return m_lineEditPassword->text();
}
//=====================================================================
void Example::TabChanged(int /*tabIdx*/)
{
        m_plainTextEdit->clear();
        delete leftLayout;
        delete mainLayout;
        SetupBasicUI();
}
//=====================================================================
void Example::LoginClicked()
{
        m_twitLib->Login(GetUsername(),GetPassword());
        //OR
        //m_twitLib->SetLoginInfo(GetUsername(),GetPassword());
        //m_twitLib->VerifyCredentials();
}
//=====================================================================
void Example::ExecuteClicked()
{
        m_plainTextEdit->clear();
        unsigned int num = 0;
        QString text, text2, text3;
        QColor color;

        switch(m_gui.tabWidget->currentIndex())
        {
        case Returnables::PUBLIC_TIMELINE:
                m_twitLib->GetPublicTimeline();
                break;
        case Returnables::FRIENDS_TIMELINE:
                m_twitLib->GetFriendsTimeline();
                break;
        case Returnables::SINGLE_STATUS:
                num = QInputDialog::getText(m_plainTextEdit,"Status ID","Enter status ID").toULongLong();
                if(num != 0)
                        m_twitLib->GetSingleStatus(num);
                break;
        case Returnables::FEATURED_USERS:
                m_twitLib->GetFeaturedUsers();
                break;
        case Returnables::VERIFY_CREDENTIALS:
                m_twitLib->SetLoginInfo(GetUsername(),GetPassword());
                m_twitLib->VerifyCredentials();
                //OR
                //m_twitLib->Login(GetUsername(),GetPassword());
                break;
        case Returnables::TWITTER_UP:
                m_twitLib->IsTwitterUp();
                break;
        case Returnables::USER_TIMELINE:
                m_twitLib->GetUsersTimeline();
                break;
        case Returnables::FAVORITES:
                m_twitLib->GetFavorites();
                break;
        case Returnables::NEW_STATUS:
                text = QInputDialog::getText(m_plainTextEdit,"New Status","Enter new status");
                text2 = QInputDialog::getText(m_plainTextEdit,"in_reply_to_status_id","Enter ID of an existing status that the status to be posted is in reply to.");
                text3 = QInputDialog::getText(m_plainTextEdit,"Source","Enter twitter client name");
                if(!text.isEmpty())
                        m_twitLib->PostNewStatus(text, text2.toULongLong(), text3);
                break;
        case Returnables::RECENT_MENTIONS:
                m_twitLib->GetRecentMentions();
                break;
        case Returnables::REMOVE_STATUS:
                num = QInputDialog::getText(m_plainTextEdit,"Remove Status ID","Enter status ID to remove").toULongLong();
                if(num != 0)
                        m_twitLib->RemoveStatus(num);
                break;
        case Returnables::FRIENDS:
                m_twitLib->GetFriends();
                break;
        case Returnables::FOLLOWERS:
                m_twitLib->GetFollowers();
                break;
        case Returnables::USER_DETAILS:
                text = QInputDialog::getText(m_plainTextEdit,"User Details","Enter ID or screen name of a user.");
                text2 = QInputDialog::getText(m_plainTextEdit,"User Details","Enter ID of the user to return.");
                text3 = QInputDialog::getText(m_plainTextEdit,"User Details","Enter screen name of the user to return.");
                m_twitLib->GetUserDetails(text, text2.toUInt(), text3);
                break;
        case Returnables::SENT_DIRECT_MESSAGES:
                m_twitLib->GetSentDirectMessages();
                break;
        case Returnables::RECEIVED_DIRECT_MESSAGES:
                m_twitLib->GetReceivedDirectMessages();
                break;
        case Returnables::SEND_DIRECT_MESSAGE:
                text = QInputDialog::getText(m_plainTextEdit,"Send Direct Message","Enter username to send to");
                text2 = QInputDialog::getText(m_plainTextEdit,"Send Direct Message","Enter new message");
                if(!text.isEmpty() && !text2.isEmpty())
                        m_twitLib->SendDirectMessage(text,text2);
                break;
        case Returnables::REMOVE_DIRECT_MESSAGE:
                num = QInputDialog::getText(m_plainTextEdit,"Remove Direct Message","Enter status ID to remove").toULongLong();
                if(num != 0)
                        m_twitLib->RemoveDirectMessage(num);
                break;
        case Returnables::ADD_FRIENDSHIP:
                text = QInputDialog::getText(m_plainTextEdit,"Add Friendship","Enter username to befriend");
                if(!text.isEmpty())
                        m_twitLib->AddFriendship(text);
                break;
        case Returnables::REMOVE_FRIENDSHIP:
                text = QInputDialog::getText(m_plainTextEdit,"Remove Friendship","Enter username to remove as a friend");
                if(!text.isEmpty())
                        m_twitLib->RemoveFriendship(text);
                break;
        case Returnables::FRIENDSHIP_EXISTS:
                text = QInputDialog::getText(m_plainTextEdit,"Friendship Exists","Enter first username");
                text2 = QInputDialog::getText(m_plainTextEdit,"Friendship Exists","Enter second username");
                if(!text.isEmpty() && !text2.isEmpty())
                        m_twitLib->FriendshipExist(text,text2);
                break;
        case Returnables::DELIVERY_DEVICE:
                text = QInputDialog::getText(m_plainTextEdit,"Update Delivery Device","Enter new device (SMS, IM, NONE)");
                if(!text.isEmpty())
                {
                        if(text.toLower().contains("sms"))
                                m_twitLib->UpdateDeliveryDevice(SERVER::SMS);
                        else if(text.toLower().contains("im"))
                                m_twitLib->UpdateDeliveryDevice(SERVER::IM);
                        else if(text.toLower().contains("none"))
                                m_twitLib->UpdateDeliveryDevice(SERVER::NONE);
                }
                break;
        case Returnables::API_REQUESTS:
                m_twitLib->RemainingApiRequests();
                break;
        case Returnables::ADD_FAVORITE:
                num = QInputDialog::getText(m_plainTextEdit,"Add Favorite","Enter status ID to favorite").toULongLong();
                if(num != 0)
                        m_twitLib->AddFavorite(num);
                break;
        case Returnables::REMOVE_FAVORITE:
                num = QInputDialog::getText(m_plainTextEdit,"Remove Favorite","Enter status ID to remove as a favorite").toULongLong();
                if(num != 0)
                        m_twitLib->RemoveFavorite(num);
                break;
        case Returnables::PROFILE_COLORS:
            {
                QString background_color="",text_color="",link_color="",sidebar_fill_color="",sidebar_border_color="";

                color = QColorDialog::getColor(Qt::red,m_plainTextEdit,"background_color");
                    if(color.isValid()){ background_color = color.name(); }
                color = QColorDialog::getColor(Qt::red,m_plainTextEdit,"text_color");
                    if(color.isValid()){ text_color = color.name(); }
                color = QColorDialog::getColor(Qt::red,m_plainTextEdit,"link_color");
                    if(color.isValid()){ link_color = color.name(); }
                color = QColorDialog::getColor(Qt::red,m_plainTextEdit,"sidebar_fill_color");
                    if(color.isValid()){ sidebar_fill_color = color.name(); }
                color = QColorDialog::getColor(Qt::red,m_plainTextEdit,"sidebar_border_color");
                    if(color.isValid()){ sidebar_border_color = color.name(); }
                    if(background_color.isEmpty() && text_color.isEmpty() && link_color.isEmpty() \
                       && sidebar_fill_color.isEmpty() && sidebar_border_color.isEmpty())
                    {
                        QMessageBox::warning(m_plainTextEdit, "Update Profile Colors", "You must enter one or more colors");
                    } else {
                        m_twitLib->UpdateProfileColors(background_color,text_color,link_color,sidebar_fill_color,sidebar_border_color);
                    }
                break;
            }
        case Returnables::PROFILE_IMAGE:
                text = QFileDialog::getOpenFileName(this, "Image File", "/", "*.png *.jpg *.gif");
                if(!text.isEmpty())
                {
                    m_twitLib->UpdateProfileImage(text);
                }
                break;
        case Returnables::PROFILE_BACKGROUND_IMAGE:
                text = QFileDialog::getOpenFileName(this, "Image File", "/", "*.png *.jpg *.gif");
                num = QInputDialog::getInt(m_plainTextEdit, "Tile Background", "1 == tiled", 0,0,1);
                if(!text.isEmpty())
                {
                    m_twitLib->UpdateProfileBackgroundImage(text, num);
                }
                break;
        case Returnables::PROFILE:
            {
                QString name = "",email = "",url = "",location = "",description = "";

                name = QInputDialog::getText(m_plainTextEdit, "Account name", "Enter your real name, so people you know can recognize you.");
                email = QInputDialog::getText(m_plainTextEdit,"Account Email", "Enter your email");
                url = QInputDialog::getText(m_plainTextEdit, "Account URL", "Have a homepage or a blog? Put the address here.");
                location = QInputDialog::getText(m_plainTextEdit, "Account Location", "Where in the world are you?");
                description = QInputDialog::getText(m_plainTextEdit, "Account Description", "About yourself in fewer than 160 chars.");
                if(name.isEmpty() && email.isEmpty() && url.isEmpty() && location.isEmpty() && description.isEmpty())
                {
                    QMessageBox::warning(m_plainTextEdit, "Update Profile", "You must enter one or more parameters");
                } else {
                    m_twitLib->UpdateProfile(name,email,url,location,description);
                }
                break;
            }
        case Returnables::FRIENDS_IDS:
                text = QInputDialog::getText(m_plainTextEdit, "ID or Screen Name", "Enter  ID or screen_name of the user to retrieve the friends ID list for.");
                text2 = QInputDialog::getText(m_plainTextEdit, "ID", "Enter ID of the user for whom to return the friends list");
                text3 = QInputDialog::getText(m_plainTextEdit, "Screen Name", "Enter screen name of the user for whom to return the friends list.");
                m_twitLib->GetFriendsIDs(text, text2, text3);
                break;
        case Returnables::FOLLOWERS_IDS:
                text = QInputDialog::getText(m_plainTextEdit, "ID or Screen Name", "Enter ID or screen_name of the user to retrieve the friends ID list for.");
                text2 = QInputDialog::getText(m_plainTextEdit, "ID", "Enter ID of the user for whom to return the followers list.");
                text3 = QInputDialog::getText(m_plainTextEdit, "Screen Name", "Enter screen name of the user for whom to return the followers list.");
                m_twitLib->GetFollowersIDs(text, text2, text3);
                break;
        case Returnables::ENABLE_NOTIFICATIONS:
                text = QInputDialog::getText(m_plainTextEdit, "Notifications", "Enter ID or screen name of the user");
                if(!text.isEmpty())
                    m_twitLib->EnableNotifications(text);
                break;
        case Returnables::DISABLE_NOTIFICATIONS:
                text = QInputDialog::getText(m_plainTextEdit, "Notifications", "Enter ID or screen name of the user");
                if(!text.isEmpty())
                    m_twitLib->DisableNotifications(text);
                break;
        case Returnables::BLOCK_USER:
                text = QInputDialog::getText(m_plainTextEdit, "Block", "Enter ID or screen name of the user");
                if(!text.isEmpty())
                    m_twitLib->BlockUser(text);
                break;
        case Returnables::UNBLOCK_USER:
                text = QInputDialog::getText(m_plainTextEdit, "Block", "Enter ID or screen name of the user");
                if(!text.isEmpty())
                    m_twitLib->UnBlockUser(text);
                break;
        default:
                break;
        }
}
//=====================================================================
void Example::SetupBasicUI()
{
        QWidget *tab = m_gui.tabWidget->currentWidget();

        m_plainTextEdit->setParent(tab);
        m_plainTextEdit->show();

        m_lineEditUsername->setParent(tab);
        m_lineEditUsername->show();

        m_lineEditPassword->setParent(tab);
        m_lineEditPassword->show();

        m_labelUsername->setParent(tab);
        m_labelUsername->show();

        m_labelPassword->setParent(tab);
        m_labelPassword->show();

        m_pushButtonLogin->setParent(tab);
        m_pushButtonLogin->show();

        m_pushButtonExecute->setParent(tab);
        m_pushButtonExecute->show();

        leftLayout = new QVBoxLayout();
            leftLayout->addWidget(m_labelUsername);
            leftLayout->addWidget(m_lineEditUsername);
            leftLayout->addWidget(m_labelPassword);
            leftLayout->addWidget(m_lineEditPassword);
            leftLayout->addWidget(m_pushButtonLogin);
            leftLayout->addWidget(m_pushButtonExecute);
            leftLayout->addStretch(1);

        mainLayout = new QHBoxLayout();
            mainLayout->addLayout(leftLayout);
            mainLayout->addWidget(m_plainTextEdit, 1);

        tab->setLayout(mainLayout);


}

#include <QtGui/QMessageBox>
#include <QtGui/QInputDialog>
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
void Example::OnResponseReceived(Returnables::Response *resp)
{
	if(resp)
    {
		switch(resp->reqID)
		{
		case Returnables::PUBLIC_TIMELINE:
			{
				Returnables::PublicTimeline *pTimeline = static_cast<Returnables::PublicTimeline *>(resp);
				m_plainTextEdit->appendHtml("<h2>Public Timeline</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendPlainText("ID: "+QString::number(pTimeline->list.first()->status.id));
				m_plainTextEdit->appendPlainText("Username: "+pTimeline->list.first()->user.screenName);
				m_plainTextEdit->appendPlainText("Text: "+pTimeline->list.first()->status.text);
				delete pTimeline;
				break;
			}
		case Returnables::FRIENDS_TIMELINE:
			{
				Returnables::FriendsTimeline *fTimeline = static_cast<Returnables::FriendsTimeline *>(resp);
				m_plainTextEdit->appendHtml("<h2>Friends Timeline</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendPlainText("ID: "+QString::number(fTimeline->list.first()->status.id));
				m_plainTextEdit->appendPlainText("Username: "+fTimeline->list.first()->user.screenName);
				m_plainTextEdit->appendPlainText("Text: "+fTimeline->list.first()->status.text);
				delete fTimeline;
				break;
			}
		case Returnables::SINGLE_STATUS:
			{
				Returnables::SingleStatus *singleStatus = static_cast<Returnables::SingleStatus *>(resp);
				m_plainTextEdit->appendHtml("<h2>Single Status</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendPlainText("ID: "+QString::number(singleStatus->status->id));
				m_plainTextEdit->appendPlainText("Username: "+singleStatus->user->screenName);
				m_plainTextEdit->appendPlainText("Text: "+singleStatus->status->text);
				delete singleStatus;
				break;
			}
		case Returnables::FEATURED_USERS:
			{
				Returnables::FeaturedUsers *featuredUsers = static_cast<Returnables::FeaturedUsers *>(resp);
				m_plainTextEdit->appendHtml("<h2>Featured Users</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendPlainText("ID: "+QString::number(featuredUsers->list.first()->status.id));
				m_plainTextEdit->appendPlainText("Username: "+featuredUsers->list.first()->user.screenName);
				m_plainTextEdit->appendPlainText("Text: "+featuredUsers->list.first()->status.text);
				delete featuredUsers;
				break;
			}
		case Returnables::LOGIN:
			{
				Returnables::Login *login = static_cast<Returnables::Login *>(resp);
				m_plainTextEdit->appendHtml("<h2>Login</h2>");
				m_plainTextEdit->appendHtml("<br>");
				QString authorized = login->authorized ? "true" : "false";
				m_plainTextEdit->appendPlainText("Authorized: "+authorized);
				delete login;
				break;
			}
		case Returnables::TWITTER_UP:
			{
				Returnables::TwitterUp *twitterUp = static_cast<Returnables::TwitterUp *>(resp);
				m_plainTextEdit->appendHtml("<h2>Twitter Up</h2>");
				m_plainTextEdit->appendHtml("<br>");
				QString up = twitterUp->up ? "true" : "false";
				m_plainTextEdit->appendPlainText("Up: "+up);
				delete twitterUp;
				break;
			}
		case Returnables::USER_TIMELINE:
			{
				Returnables::UserTimeline *userTimeline = static_cast<Returnables::UserTimeline *>(resp);
				m_plainTextEdit->appendHtml("<h2>Users Timeline</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendPlainText("ID: "+QString::number(userTimeline->list.first()->status.id));
				m_plainTextEdit->appendPlainText("Username: "+userTimeline->list.first()->user.screenName);
				m_plainTextEdit->appendPlainText("Text: "+userTimeline->list.first()->status.text);
				delete userTimeline;
				break;
			}
		case Returnables::FAVORITES:
			{
				Returnables::Favorites *favorites = static_cast<Returnables::Favorites *>(resp);
				m_plainTextEdit->appendHtml("<h2>Favorites</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendPlainText("ID: "+QString::number(favorites->list.first()->status.id));
				m_plainTextEdit->appendPlainText("Username: "+favorites->list.first()->user.screenName);
				m_plainTextEdit->appendPlainText("Text: "+favorites->list.first()->status.text);
				delete favorites;
				break;
			}
		case Returnables::NEW_STATUS:
			{
				Returnables::NewStatus *newStatus = static_cast<Returnables::NewStatus *>(resp);
				m_plainTextEdit->appendHtml("<h2>New Status</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendPlainText("ID: "+QString::number(newStatus->newStatus->id));
				m_plainTextEdit->appendPlainText("Username: "+newStatus->user->screenName);
				m_plainTextEdit->appendPlainText("Text: "+newStatus->newStatus->text);
				delete newStatus;
				break;
			}
		case Returnables::RECENT_REPLIES:
			{
				Returnables::RecentReplies *replies = static_cast<Returnables::RecentReplies *>(resp);
				m_plainTextEdit->appendHtml("<h2>Recent Replies</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendPlainText("ID: "+QString::number(replies->list.first()->status.id));
				m_plainTextEdit->appendPlainText("Username: "+replies->list.first()->user.screenName);
				m_plainTextEdit->appendPlainText("Text: "+replies->list.first()->status.text);
				delete replies;
				break;
			}
		case Returnables::REMOVE_STATUS:
			{
				Returnables::RemoveStatus *removedStatus = static_cast<Returnables::RemoveStatus *>(resp);
				m_plainTextEdit->appendHtml("<h2>Remove Status</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendPlainText("ID: "+QString::number(removedStatus->removedStatus->id));
				m_plainTextEdit->appendPlainText("Username: "+removedStatus->user->screenName);
				m_plainTextEdit->appendPlainText("Text: "+removedStatus->removedStatus->text);
				delete removedStatus;
				break;
			}
		case Returnables::FRIENDS:
			{
				Returnables::Friends *friends = static_cast<Returnables::Friends *>(resp);
				m_plainTextEdit->appendHtml("<h2>Friends</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendPlainText("ID: "+QString::number(friends->list.first()->status.id));
				m_plainTextEdit->appendPlainText("Username: "+friends->list.first()->user.screenName);
				m_plainTextEdit->appendPlainText("Text: "+friends->list.first()->status.text);
				delete friends;
				break;
			}
		case Returnables::FOLLOWERS:
			{
				Returnables::Followers *followers = static_cast<Returnables::Followers *>(resp);
				m_plainTextEdit->appendHtml("<h2>Followers</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendPlainText("ID: "+QString::number(followers->list.first()->status.id));
				m_plainTextEdit->appendPlainText("Username: "+followers->list.first()->user.screenName);
				m_plainTextEdit->appendPlainText("Text: "+followers->list.first()->status.text);
				delete followers;
				break;
			}
		case Returnables::USER_DETAILS:
			{
				Returnables::UserDetails *userDetails = static_cast<Returnables::UserDetails *>(resp);
				m_plainTextEdit->appendHtml("<h2>User Details</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendPlainText("ID: "+QString::number(userDetails->status->id));
				m_plainTextEdit->appendPlainText("Username: "+userDetails->user->screenName);
				m_plainTextEdit->appendPlainText("Friends: "+QString::number(userDetails->details->friendsCount));
				m_plainTextEdit->appendPlainText("Text: "+userDetails->status->text);
				delete userDetails;
				break;
			}
		case Returnables::SENT_DIRECT_MESSAGES:
			{
				Returnables::SentDirectMessages *sentDirectMessages = static_cast<Returnables::SentDirectMessages *>(resp);
				m_plainTextEdit->appendHtml("<h2>Sent Direct Messages</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendPlainText("ID: "+QString::number(sentDirectMessages->list.first()->headerInfo.id));
				m_plainTextEdit->appendPlainText("Sender: "+sentDirectMessages->list.first()->sender.screenName);
				m_plainTextEdit->appendPlainText("Recipient: "+sentDirectMessages->list.first()->recipient.screenName);
				m_plainTextEdit->appendPlainText("Created At: "+sentDirectMessages->list.first()->headerInfo.createdAt);
				m_plainTextEdit->appendPlainText("Text: "+sentDirectMessages->list.first()->headerInfo.text);
				delete sentDirectMessages;
				break;
			}
		case Returnables::RECEIVED_DIRECT_MESSAGES:
			{
				Returnables::ReceivedDirectMessages *receivedDirectMessages = static_cast<Returnables::ReceivedDirectMessages *>(resp);
				m_plainTextEdit->appendHtml("<h2>Received Direct Messages</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendPlainText("ID: "+QString::number(receivedDirectMessages->list.first()->headerInfo.id));
				m_plainTextEdit->appendPlainText("Sender: "+receivedDirectMessages->list.first()->sender.screenName);
				m_plainTextEdit->appendPlainText("Recipient: "+receivedDirectMessages->list.first()->recipient.screenName);
				m_plainTextEdit->appendPlainText("Created At: "+receivedDirectMessages->list.first()->headerInfo.createdAt);
				m_plainTextEdit->appendPlainText("Text: "+receivedDirectMessages->list.first()->headerInfo.text);
				delete receivedDirectMessages;
				break;
			}
		case Returnables::SEND_DIRECT_MESSAGE:
			{	
				Returnables::SendDirectMessage *sendDirectMessage = static_cast<Returnables::SendDirectMessage *>(resp);
				m_plainTextEdit->appendHtml("<h2>Received Direct Messages</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendPlainText("ID: "+QString::number(sendDirectMessage->headerInfo->id));
				m_plainTextEdit->appendPlainText("Sender: "+sendDirectMessage->sender->screenName);
				m_plainTextEdit->appendPlainText("Recipient: "+sendDirectMessage->recipient->screenName);
				m_plainTextEdit->appendPlainText("Created At: "+sendDirectMessage->headerInfo->createdAt);
				m_plainTextEdit->appendPlainText("Text: "+sendDirectMessage->headerInfo->text);
				delete sendDirectMessage;
				break;
			}
		case Returnables::REMOVE_DIRECT_MESSAGE:
			{
				Returnables::RemoveDirectMessage *removeDirectMessage = static_cast<Returnables::RemoveDirectMessage *>(resp);
				m_plainTextEdit->appendHtml("<h2>Remove Direct Messages</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendPlainText("ID: "+QString::number(removeDirectMessage->headerInfo->id));
				m_plainTextEdit->appendPlainText("Sender: "+removeDirectMessage->sender->screenName);
				m_plainTextEdit->appendPlainText("Recipient: "+removeDirectMessage->recipient->screenName);
				m_plainTextEdit->appendPlainText("Created At: "+removeDirectMessage->headerInfo->createdAt);
				m_plainTextEdit->appendPlainText("Text: "+removeDirectMessage->headerInfo->text);
				delete removeDirectMessage;
				break;
			}
		case Returnables::ADD_FRIENDSHIP:
			{
				Returnables::AddFriendship *addFriendship = static_cast<Returnables::AddFriendship *>(resp);
				m_plainTextEdit->appendHtml("<h2>Add Friendship</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendPlainText("ID: "+QString::number(addFriendship->status->id));
				m_plainTextEdit->appendPlainText("Username: "+addFriendship->user->screenName);
				m_plainTextEdit->appendPlainText("Text: "+addFriendship->status->text);
				delete addFriendship;
				break;
			}
		case Returnables::REMOVE_FRIENDSHIP:
			{
				Returnables::RemoveFriendship *removeFriendship = static_cast<Returnables::RemoveFriendship *>(resp);
				m_plainTextEdit->appendHtml("<h2>Remove Friendship</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendPlainText("ID: "+QString::number(removeFriendship->status->id));
				m_plainTextEdit->appendPlainText("Username: "+removeFriendship->user->screenName);
				m_plainTextEdit->appendPlainText("Text: "+removeFriendship->status->text);
				delete removeFriendship;
				break;
			}
		case Returnables::FRIENDSHIP_EXISTS:
			{
				Returnables::FriendshipExist *friendshipExists = static_cast<Returnables::FriendshipExist *>(resp);
				m_plainTextEdit->appendHtml("<h2>Friendship Exist</h2>");
				m_plainTextEdit->appendHtml("<br>");
				QString friends = friendshipExists->friends ? "true" : "false";
				m_plainTextEdit->appendPlainText("Are Friends?: "+friends);
				delete friendshipExists;
				break;
			}
		case Returnables::UPDATE_LOCATION:
			{
				Returnables::UpdateLocation *updateLocation = static_cast<Returnables::UpdateLocation *>(resp);
				m_plainTextEdit->appendHtml("<h2>Update Location</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendPlainText("ID: "+QString::number(updateLocation->status->id));
				m_plainTextEdit->appendPlainText("Username: "+updateLocation->user->screenName);
				m_plainTextEdit->appendPlainText("Location: "+updateLocation->user->location);
				m_plainTextEdit->appendPlainText("Text: "+updateLocation->status->text);
				delete updateLocation;
				break;
			}
		case Returnables::DELIVERY_DEVICE:
			{
				Returnables::DeliveryDevice *deliveryDevice = static_cast<Returnables::DeliveryDevice *>(resp);
				m_plainTextEdit->appendHtml("<h2>Update Delivery Device</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendPlainText("ID: "+QString::number(deliveryDevice->status->id));
				m_plainTextEdit->appendPlainText("Username: "+deliveryDevice->user->screenName);
				m_plainTextEdit->appendPlainText("Text: "+deliveryDevice->status->text);
				delete deliveryDevice;
				break;
			}
		case Returnables::API_REQUESTS:
			{
				Returnables::ApiRequests *apiRequests = static_cast<Returnables::ApiRequests *>(resp);
				m_plainTextEdit->appendHtml("<h2>Remaining API requests</h2>");
				m_plainTextEdit->appendHtml("<br>");
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
				m_plainTextEdit->appendHtml("<h2>Add Favorite</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendPlainText("ID: "+QString::number(addFavorite->status->id));
				m_plainTextEdit->appendPlainText("Username: "+addFavorite->user->screenName);
				m_plainTextEdit->appendPlainText("Text: "+addFavorite->status->text);
				delete addFavorite;
				break;
			}
		case Returnables::REMOVE_FAVORITE:
			{
				Returnables::RemoveFavorite *removeFavorite = static_cast<Returnables::RemoveFavorite *>(resp);
				m_plainTextEdit->appendHtml("<h2>Remove Favorite</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendPlainText("ID: "+QString::number(removeFavorite->status->id));
				m_plainTextEdit->appendPlainText("Username: "+removeFavorite->user->screenName);
				m_plainTextEdit->appendPlainText("Text: "+removeFavorite->status->text);
				delete removeFavorite;
				break;
			}
		}
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
void Example::TabChanged(int tabIdx)
{
	m_plainTextEdit->clear();
	SetupBasicUI();
}
//=====================================================================
void Example::LoginClicked()
{
	m_twitLib->Login(GetUsername(),GetPassword());
}
//=====================================================================
void Example::ExecuteClicked()
{
	m_plainTextEdit->clear();
	unsigned int num = 0;
	QString text, text2;

	switch(m_gui.tabWidget->currentIndex())
	{
	case Returnables::PUBLIC_TIMELINE:
		m_twitLib->GetPublicTimeline();
		break;
	case Returnables::FRIENDS_TIMELINE:
		m_twitLib->GetFriendsTimeline();
		break;
	case Returnables::SINGLE_STATUS:
		num = QInputDialog::getText(m_plainTextEdit,"Status ID","Enter status ID").toUInt();
		if(num != 0)
			m_twitLib->GetSingleStatus(num);
		break;
	case Returnables::FEATURED_USERS:
		m_twitLib->GetFeaturedUsers();
		break;
	case Returnables::LOGIN:
		m_twitLib->Login(GetUsername(),GetPassword());
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
		if(!text.isEmpty())
			m_twitLib->PostNewStatus(text);
		break;
	case Returnables::RECENT_REPLIES:
		m_twitLib->GetRecentReplies();
		break;
	case Returnables::REMOVE_STATUS:
		num = QInputDialog::getText(m_plainTextEdit,"Remove Status ID","Enter status ID to remove").toUInt();
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
		text = QInputDialog::getText(m_plainTextEdit,"User Details","Enter username to query");
		if(!text.isEmpty())
			m_twitLib->GetUserDetails(text);
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
		num = QInputDialog::getText(m_plainTextEdit,"Remove Direct Message","Enter status ID to remove").toUInt();
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
	case Returnables::UPDATE_LOCATION:
		text = QInputDialog::getText(m_plainTextEdit,"Update Location","Enter your new location");
		if(!text.isEmpty())
			m_twitLib->UpdateLocation(text);
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
		num = QInputDialog::getText(m_plainTextEdit,"Add Favorite","Enter status ID to favorite").toUInt();
		if(num != 0)
			m_twitLib->AddFavorite(num);
		break;
	case Returnables::REMOVE_FAVORITE:
		num = QInputDialog::getText(m_plainTextEdit,"Remove Favorite","Enter status ID to remove as a favorite").toUInt();
		if(num != 0)
			m_twitLib->RemoveFavorite(num);
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
	m_plainTextEdit->setGeometry(QRect(150, 30, 511, 391));
	m_plainTextEdit->show();

	m_lineEditUsername->setParent(tab);
	m_lineEditUsername->setGeometry(QRect(10, 30, 113, 20));
	m_lineEditUsername->show();

	m_lineEditPassword->setParent(tab);
	m_lineEditPassword->setGeometry(QRect(10, 80, 113, 20));
	m_lineEditPassword->show();

	m_labelUsername->setParent(tab);
	m_labelUsername->setGeometry(QRect(10, 50, 111, 16));
	m_labelUsername->show();

	m_labelPassword->setParent(tab);
	m_labelPassword->setGeometry(QRect(10, 100, 111, 16));
	m_labelPassword->show();

	m_pushButtonLogin->setParent(tab);
	m_pushButtonLogin->setGeometry(QRect(10, 130, 75, 24));
	m_pushButtonLogin->show();

	m_pushButtonExecute->setParent(tab);
    m_pushButtonExecute->setGeometry(QRect(10, 170, 75, 24));
	m_pushButtonExecute->show();
}

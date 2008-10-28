#include <QtGui/QMessageBox>
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
				m_plainTextEdit->appendHtml("<b>"+pTimeline->list.first()->user.screenName+"</b>");
				m_plainTextEdit->appendPlainText(pTimeline->list.first()->status.text);
				m_plainTextEdit->appendHtml("<b>"+pTimeline->list.last()->user.screenName+"</b>");
				m_plainTextEdit->appendPlainText(pTimeline->list.last()->status.text);
				delete pTimeline;
				break;
			}
		case Returnables::FRIENDS_TIMELINE:
			{
				Returnables::FriendsTimeline *fTimeline = static_cast<Returnables::FriendsTimeline *>(resp);
				m_plainTextEdit->appendHtml("<h2>Friends Timeline</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendHtml("<b>"+fTimeline->list.first()->user.screenName+"</b>");
				m_plainTextEdit->appendPlainText(fTimeline->list.first()->status.text);
				m_plainTextEdit->appendHtml("<b>"+fTimeline->list.last()->user.screenName+"</b>");
				m_plainTextEdit->appendPlainText(fTimeline->list.last()->status.text);
				delete fTimeline;
				break;
			}
		case Returnables::SINGLE_STATUS:
			{
				Returnables::SingleStatus *singleStatus = static_cast<Returnables::SingleStatus *>(resp);
				m_plainTextEdit->appendHtml("<h2>Single Status</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendHtml("<b>"+singleStatus->user->screenName+"</b>");
				m_plainTextEdit->appendPlainText(singleStatus->status->text);
				delete singleStatus;
				break;
			}
		case Returnables::FEATURED_USERS:
			{
				Returnables::FeaturedUsers *featuredUsers = static_cast<Returnables::FeaturedUsers *>(resp);
				m_plainTextEdit->appendHtml("<h2>Featured Users</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendHtml("<b>"+featuredUsers->list.first()->user.screenName+"</b>");
				m_plainTextEdit->appendPlainText(featuredUsers->list.first()->status.text);
				m_plainTextEdit->appendHtml("<b>"+featuredUsers->list.last()->user.screenName+"</b>");
				m_plainTextEdit->appendPlainText(featuredUsers->list.last()->status.text);
				delete featuredUsers;
				break;
			}
		case Returnables::LOGIN:
			{
				Returnables::Login *login = static_cast<Returnables::Login *>(resp);
				m_plainTextEdit->appendHtml("<h2>Login</h2>");
				m_plainTextEdit->appendHtml("<br>");
				QString authorized = login->authorized ? "true" : "false";
				m_plainTextEdit->appendHtml("<b>Authorized: "+authorized+"</b>");
				delete login;
				break;
			}
		case Returnables::TWITTER_UP:
			{
				Returnables::TwitterUp *twitterUp = static_cast<Returnables::TwitterUp *>(resp);
				m_plainTextEdit->appendHtml("<h2>Twitter Up</h2>");
				m_plainTextEdit->appendHtml("<br>");
				QString up = twitterUp->up ? "true" : "false";
				m_plainTextEdit->appendHtml("<b>Up: "+up+"</b>");
				delete twitterUp;
				break;
			}
		case Returnables::USER_TIMELINE:
			{
				Returnables::UserTimeline *userTimeline = static_cast<Returnables::UserTimeline *>(resp);
				m_plainTextEdit->appendHtml("<h2>Users Timeline</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendHtml("<b>"+userTimeline->list.first()->user.screenName+"</b>");
				m_plainTextEdit->appendPlainText(userTimeline->list.first()->status.text);
				m_plainTextEdit->appendHtml("<b>"+userTimeline->list.last()->user.screenName+"</b>");
				m_plainTextEdit->appendPlainText(userTimeline->list.last()->status.text);
				delete userTimeline;
				break;
			}
		case Returnables::FAVORITES:
			{
				Returnables::Favorites *favorites = static_cast<Returnables::Favorites *>(resp);
				m_plainTextEdit->appendHtml("<h2>Favorites</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendHtml("<b>"+favorites->list.first()->user.screenName+"</b>");
				m_plainTextEdit->appendPlainText(favorites->list.first()->status.text);
				m_plainTextEdit->appendHtml("<b>"+favorites->list.last()->user.screenName+"</b>");
				m_plainTextEdit->appendPlainText(favorites->list.last()->status.text);
				delete favorites;
				break;
			}
		case Returnables::NEW_STATUS:
			{
				Returnables::NewStatus *newStatus = static_cast<Returnables::NewStatus *>(resp);
				m_plainTextEdit->appendHtml("<h2>New Status</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendHtml("<b>"+newStatus->user->screenName+"</b>");
				m_plainTextEdit->appendPlainText(newStatus->newStatus->text);
				delete newStatus;
				break;
			}
		case Returnables::RECENT_REPLIES:
			{
				Returnables::RecentReplies *replies = static_cast<Returnables::RecentReplies *>(resp);
				m_plainTextEdit->appendHtml("<h2>Recent Replies</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendHtml("<b>"+replies->list.first()->user.screenName+"</b>");
				m_plainTextEdit->appendPlainText(replies->list.first()->status.text);
				m_plainTextEdit->appendHtml("<b>"+replies->list.last()->user.screenName+"</b>");
				m_plainTextEdit->appendPlainText(replies->list.last()->status.text);
				delete replies;
				break;
			}
		case Returnables::REMOVE_STATUS:
			{
				Returnables::RemoveStatus *removedStatus = static_cast<Returnables::RemoveStatus *>(resp);
				m_plainTextEdit->appendHtml("<h2>Remove Status</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendHtml("<b>"+removedStatus->user->screenName+"</b>");
				m_plainTextEdit->appendPlainText(removedStatus->removedStatus->text);
				delete removedStatus;
				break;
			}
		case Returnables::FRIENDS:
			{
				Returnables::Friends *friends = static_cast<Returnables::Friends *>(resp);
				m_plainTextEdit->appendHtml("<h2>Friends</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendHtml("<b>"+friends->list.first()->user.screenName+"</b>");
				m_plainTextEdit->appendPlainText(friends->list.first()->status.text);
				m_plainTextEdit->appendHtml("<b>"+friends->list.last()->user.screenName+"</b>");
				m_plainTextEdit->appendPlainText(friends->list.last()->status.text);
				delete friends;
				break;
			}
		case Returnables::FOLLOWERS:
			{
				Returnables::Followers *followers = static_cast<Returnables::Followers *>(resp);
				m_plainTextEdit->appendHtml("<h2>Followers</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendHtml("<b>"+followers->list.first()->user.screenName+"</b>");
				m_plainTextEdit->appendPlainText(followers->list.first()->status.text);
				m_plainTextEdit->appendHtml("<b>"+followers->list.last()->user.screenName+"</b>");
				m_plainTextEdit->appendPlainText(followers->list.last()->status.text);
				delete followers;
				break;
			}
		case Returnables::USER_DETAILS:
			{
				Returnables::UserDetails *userDetails = static_cast<Returnables::UserDetails *>(resp);
				m_plainTextEdit->appendHtml("<h2>User Details</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendHtml("<b>"+userDetails->user->screenName+"</b>");
				m_plainTextEdit->appendPlainText("Friends: "+QString::number(userDetails->details->friendsCount));
				m_plainTextEdit->appendPlainText(userDetails->status->text);
				delete userDetails;
				break;
			}
		case Returnables::SENT_DIRECT_MESSAGES:
			{
				Returnables::SentDirectMessages *sentDirectMessages = static_cast<Returnables::SentDirectMessages *>(resp);
				m_plainTextEdit->appendHtml("<h2>Sent Direct Messages</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendHtml("Sender: <b>"+sentDirectMessages->list.first()->sender.screenName+"</b>");
				m_plainTextEdit->appendPlainText("Recipient: "+sentDirectMessages->list.first()->recipient.screenName);
				m_plainTextEdit->appendHtml("Created At: <b>"+sentDirectMessages->list.first()->headerInfo.createdAt+"</b>");
				m_plainTextEdit->appendPlainText(sentDirectMessages->list.first()->headerInfo.text);
				delete sentDirectMessages;
				break;
			}
		case Returnables::RECEIVED_DIRECT_MESSAGES:
			{
				Returnables::ReceivedDirectMessages *receivedDirectMessages = static_cast<Returnables::ReceivedDirectMessages *>(resp);
				m_plainTextEdit->appendHtml("<h2>Received Direct Messages</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendHtml("Sender: <b>"+receivedDirectMessages->list.first()->sender.screenName+"</b>");
				m_plainTextEdit->appendPlainText("Recipient: "+receivedDirectMessages->list.first()->recipient.screenName);
				m_plainTextEdit->appendHtml("Created At: <b>"+receivedDirectMessages->list.first()->headerInfo.createdAt+"</b>");
				m_plainTextEdit->appendPlainText(receivedDirectMessages->list.first()->headerInfo.text);
				delete receivedDirectMessages;
				break;
			}
		case Returnables::SEND_DIRECT_MESSAGE:
			{	
				Returnables::SendDirectMessage *sendDirectMessage = static_cast<Returnables::SendDirectMessage *>(resp);
				m_plainTextEdit->appendHtml("<h2>Received Direct Messages</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendHtml("Sender: <b>"+sendDirectMessage->sender->screenName+"</b>");
				m_plainTextEdit->appendPlainText("Recipient: "+sendDirectMessage->recipient->screenName);
				m_plainTextEdit->appendHtml("Created At: <b>"+sendDirectMessage->headerInfo->createdAt+"</b>");
				m_plainTextEdit->appendPlainText(sendDirectMessage->headerInfo->text);
				delete sendDirectMessage;
				break;
			}
		case Returnables::REMOVE_DIRECT_MESSAGE:
			{
				Returnables::RemoveDirectMessage *removeDirectMessage = static_cast<Returnables::RemoveDirectMessage *>(resp);
				m_plainTextEdit->appendHtml("<h2>Remove Direct Messages</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendHtml("Sender: <b>"+removeDirectMessage->sender->screenName+"</b>");
				m_plainTextEdit->appendPlainText("Recipient: "+removeDirectMessage->recipient->screenName);
				m_plainTextEdit->appendHtml("Created At: <b>"+removeDirectMessage->headerInfo->createdAt+"</b>");
				m_plainTextEdit->appendPlainText(removeDirectMessage->headerInfo->text);
				delete removeDirectMessage;
				break;
			}
		case Returnables::ADD_FRIENDSHIP:
			{
				Returnables::AddFriendship *addFriendship = static_cast<Returnables::AddFriendship *>(resp);
				m_plainTextEdit->appendHtml("<h2>Add Friendship</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendHtml("<b>"+addFriendship->user->screenName+"</b>");
				m_plainTextEdit->appendPlainText(addFriendship->status->text);
				delete addFriendship;
				break;
			}
		case Returnables::REMOVE_FRIENDSHIP:
			{
				Returnables::RemoveFriendship *removeFriendship = static_cast<Returnables::RemoveFriendship *>(resp);
				m_plainTextEdit->appendHtml("<h2>Remove Friendship</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendHtml("<b>"+removeFriendship->user->screenName+"</b>");
				m_plainTextEdit->appendPlainText(removeFriendship->status->text);
				delete removeFriendship;
				break;
			}
		case Returnables::FRIENDSHIP_EXISTS:
			{
				Returnables::FriendshipExist *friendshipExists = static_cast<Returnables::FriendshipExist *>(resp);
				m_plainTextEdit->appendHtml("<h2>Friendship Exist</h2>");
				m_plainTextEdit->appendHtml("<br>");
				QString friends = friendshipExists->friends ? "true" : "false";
				m_plainTextEdit->appendHtml("<b>Are Friends?: "+friends+"</b>");
				delete friendshipExists;
				break;
			}
		case Returnables::UPDATE_LOCATION:
			{
				Returnables::UpdateLocation *updateLocation = static_cast<Returnables::UpdateLocation *>(resp);
				m_plainTextEdit->appendHtml("<h2>Update Location</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendHtml("<b>"+updateLocation->user->screenName+"</b>");
				m_plainTextEdit->appendPlainText(updateLocation->user->location);
				m_plainTextEdit->appendPlainText(updateLocation->status->text);
				delete updateLocation;
				break;
			}
		case Returnables::DELIVERY_DEVICE:
			{
				Returnables::DeliveryDevice *deliveryDevice = static_cast<Returnables::DeliveryDevice *>(resp);
				m_plainTextEdit->appendHtml("<h2>Update Delivery Device</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendHtml("<b>"+deliveryDevice->user->screenName+"</b>");
				m_plainTextEdit->appendPlainText(deliveryDevice->status->text);
				delete deliveryDevice;
				break;
			}
		case Returnables::API_REQUESTS:
			{
				Returnables::ApiRequests *apiRequests = static_cast<Returnables::ApiRequests *>(resp);
				m_plainTextEdit->appendHtml("<h2>Remaining API requests</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendHtml("Hourly Limit: <b>"+QString::number(apiRequests->hourlyLimit)+"</b>");
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
				m_plainTextEdit->appendHtml("<b>"+addFavorite->user->screenName+"</b>");
				m_plainTextEdit->appendPlainText(addFavorite->status->text);
				delete addFavorite;
				break;
			}
		case Returnables::REMOVE_FAVORITE:
			{
				Returnables::RemoveFavorite *removeFavorite = static_cast<Returnables::RemoveFavorite *>(resp);
				m_plainTextEdit->appendHtml("<h2>Remove Favorite</h2>");
				m_plainTextEdit->appendHtml("<br>");
				m_plainTextEdit->appendHtml("<b>"+removeFavorite->user->screenName+"</b>");
				m_plainTextEdit->appendPlainText(removeFavorite->status->text);
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

	switch(m_gui.tabWidget->currentIndex())
	{
	case Returnables::PUBLIC_TIMELINE:
		m_twitLib->GetPublicTimeline();
		break;
	case Returnables::FRIENDS_TIMELINE:
		m_twitLib->GetFriendsTimeline(NULL);
		break;
	case Returnables::SINGLE_STATUS:
		m_twitLib->GetSingleStatus(978353645);
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
		m_twitLib->GetUsersTimeline(NULL);
		break;
	case Returnables::FAVORITES:
		m_twitLib->GetFavorites("",1);
		break;
	case Returnables::NEW_STATUS:
		m_twitLib->PostNewStatus("Everyone ready for some Chuck action!?!!?!");
		break;
	case Returnables::RECENT_REPLIES:
		m_twitLib->GetRecentReplies(NULL);
		break;
	case Returnables::REMOVE_STATUS:
		m_twitLib->RemoveStatus(978251294);
		break;
	case Returnables::FRIENDS:
		m_twitLib->GetFriends(NULL);
		break;
	case Returnables::FOLLOWERS:
		m_twitLib->GetFollowers(NULL);
		break;
	case Returnables::USER_DETAILS:
		m_twitLib->GetUserDetails("blackey02");
		break;
	case Returnables::SENT_DIRECT_MESSAGES:
		m_twitLib->GetSentDirectMessages(NULL);
		break;
	case Returnables::RECEIVED_DIRECT_MESSAGES:
		m_twitLib->GetReceivedDirectMessages(NULL);
		break;
	case Returnables::SEND_DIRECT_MESSAGE:
		m_twitLib->SendDirectMessage("blackey02","New Test Direct Message");
		break;
	case Returnables::REMOVE_DIRECT_MESSAGE:
		m_twitLib->RemoveDirectMessage(39658729);
		break;
	case Returnables::ADD_FRIENDSHIP:
		m_twitLib->AddFriendship("kevinrose",true);
		break;
	case Returnables::REMOVE_FRIENDSHIP:
		m_twitLib->RemoveFriendship("kevinrose");
		break;
	case Returnables::FRIENDSHIP_EXISTS:
		m_twitLib->FriendshipExist("blackey02","kevinrose");
		break;
	case Returnables::UPDATE_LOCATION:
		m_twitLib->UpdateLocation("Pleasanton, CA");
		break;
	case Returnables::DELIVERY_DEVICE:
		m_twitLib->UpdateDeliveryDevice(SERVER::NONE);
		break;
	case Returnables::API_REQUESTS:
		m_twitLib->RemainingApiRequests();
		break;
	case Returnables::ADD_FAVORITE:
		m_twitLib->AddFavorite(978353645);
		break;
	case Returnables::REMOVE_FAVORITE:
		m_twitLib->RemoveFavorite(978353645);
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

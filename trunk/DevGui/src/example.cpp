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
				break;
			}
		case Returnables::FRIENDS_TIMELINE:
			{
				Returnables::FriendsTimeline *fTimeline = static_cast<Returnables::FriendsTimeline *>(resp);
				break;
			}
		case Returnables::SINGLE_STATUS:
			{
				Returnables::SingleStatus *singleStatus = static_cast<Returnables::SingleStatus *>(resp);
				break;
			}
		case Returnables::FEATURED_USERS:
			{
				Returnables::FeaturedUsers *featuredUsers = static_cast<Returnables::FeaturedUsers *>(resp);
				break;
			}
		case Returnables::LOGIN:
			{
				Returnables::Login *login = static_cast<Returnables::Login *>(resp);
				break;
			}
		case Returnables::TWITTER_UP:
			{
				Returnables::TwitterUp *twitterUp = static_cast<Returnables::TwitterUp *>(resp);
				break;
			}
		case Returnables::USER_TIMELINE:
			{
				Returnables::UserTimeline *userTimeline = static_cast<Returnables::UserTimeline *>(resp);
				break;
			}
		case Returnables::FAVORITES:
			{
				Returnables::Favorites *favorites = static_cast<Returnables::Favorites *>(resp);
				break;
			}
		case Returnables::NEW_STATUS:
			{
				Returnables::NewStatus *newStatus = static_cast<Returnables::NewStatus *>(resp);
				break;
			}
		case Returnables::RECENT_REPLIES:
			{
				Returnables::RecentReplies *replies = static_cast<Returnables::RecentReplies *>(resp);
				break;
			}
		case Returnables::REMOVE_STATUS:
			{
				Returnables::RemoveStatus *removedStatus = static_cast<Returnables::RemoveStatus *>(resp);
				break;
			}
		case Returnables::FRIENDS:
			{
				Returnables::Friends *friends = static_cast<Returnables::Friends *>(resp);
				break;
			}
		case Returnables::FOLLOWERS:
			{
				Returnables::Followers *followers = static_cast<Returnables::Followers *>(resp);
				break;
			}
		case Returnables::USER_DETAILS:
			{
				Returnables::UserDetails *userDetails = static_cast<Returnables::UserDetails *>(resp);
				break;
			}
		case Returnables::SENT_DIRECT_MESSAGES:
			{
				Returnables::SentDirectMessages *sentDirectMessages = static_cast<Returnables::SentDirectMessages *>(resp);
				break;
			}
		case Returnables::RECEIVED_DIRECT_MESSAGES:
			{
				Returnables::ReceivedDirectMessages *receivedDirectMessages = static_cast<Returnables::ReceivedDirectMessages *>(resp);
				break;
			}
		case Returnables::SEND_DIRECT_MESSAGE:
			{	
				Returnables::SendDirectMessage *sendDirectMessage = static_cast<Returnables::SendDirectMessage *>(resp);
				break;
			}
		case Returnables::REMOVE_DIRECT_MESSAGE:
			{
				Returnables::RemoveDirectMessage *removeDirectMessage = static_cast<Returnables::RemoveDirectMessage *>(resp);
				break;
			}
		case Returnables::ADD_FRIENDSHIP:
			{
				Returnables::AddFriendship *addFriendship = static_cast<Returnables::AddFriendship *>(resp);
				break;
			}
		case Returnables::REMOVE_FRIENDSHIP:
			{
				Returnables::RemoveFriendship *removeFriendship = static_cast<Returnables::RemoveFriendship *>(resp);
				break;
			}
		case Returnables::FRIENDSHIP_EXISTS:
			{
				Returnables::FriendshipExist *friendshipExists = static_cast<Returnables::FriendshipExist *>(resp);
				break;
			}
		case Returnables::UPDATE_LOCATION:
			{
				Returnables::UpdateLocation *updateLocation = static_cast<Returnables::UpdateLocation *>(resp);
				break;
			}
		case Returnables::DELIVERY_DEVICE:
			{
				Returnables::DeliveryDevice *deliveryDevice = static_cast<Returnables::DeliveryDevice *>(resp);
				break;
			}
		case Returnables::API_REQUESTS:
			{
				Returnables::ApiRequests *apiRequests = static_cast<Returnables::ApiRequests *>(resp);
				break;
			}
		case Returnables::ADD_FAVORITE:
			{
				Returnables::AddFavorite *addFavorite = static_cast<Returnables::AddFavorite *>(resp);
				break;
			}
		case Returnables::REMOVE_FAVORITE:
			{
				Returnables::RemoveFavorite *removeFavorite = static_cast<Returnables::RemoveFavorite *>(resp);
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
	switch(m_gui.tabWidget->currentIndex())
	{
	case Returnables::PUBLIC_TIMELINE:
		m_twitLib->GetPublicTimeline();
		break;
	case Returnables::FRIENDS_TIMELINE:
		m_twitLib->GetFriendsTimeline(NULL);
		break;
	case Returnables::SINGLE_STATUS:
		m_twitLib->GetSingleStatus(123);
		break;
	case Returnables::FEATURED_USERS:
		m_twitLib->GetFeaturedUsers();
		break;
	case Returnables::LOGIN:
		m_twitLib->Login(GetUsername(),GetPassword());
		break;
	case Returnables::LOGOUT:
		break;
	case Returnables::VERIFY_CREDENTIALS:
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
		m_twitLib->PostNewStatus("New Status");
		break;
	case Returnables::RECENT_REPLIES:
		m_twitLib->GetRecentReplies(NULL);
		break;
	case Returnables::REMOVE_STATUS:
		m_twitLib->RemoveStatus(123);
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
		m_twitLib->RemoveDirectMessage(123);
		break;
	case Returnables::ADD_FRIENDSHIP:
		m_twitLib->AddFriendship("blackey02",true);
		break;
	case Returnables::REMOVE_FRIENDSHIP:
		m_twitLib->RemoveFriendship("blackey02");
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
		m_twitLib->AddFavorite(123);
		break;
	case Returnables::REMOVE_FAVORITE:
		m_twitLib->RemoveFavorite(123);
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

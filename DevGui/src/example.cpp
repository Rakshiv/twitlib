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
	connect(m_twitLib,SIGNAL(PublicTimeline(Returnables::PublicTimeline *)),this,SLOT(PublicTimeline(Returnables::PublicTimeline *)));
	connect(m_twitLib,SIGNAL(FriendsTimeline(Returnables::FriendsTimeline *)),this,SLOT(FriendsTimeline(Returnables::FriendsTimeline *)));
	connect(m_twitLib,SIGNAL(SingleStatus(Returnables::SingleStatus *)),this,SLOT(SingleStatus(Returnables::SingleStatus *)));
	connect(m_twitLib,SIGNAL(FeaturedUsers(Returnables::FeaturedUsers *)),this,SLOT(FeaturedUsers(Returnables::FeaturedUsers *)));
	connect(m_twitLib,SIGNAL(Login(Returnables::Login *)),this,SLOT(Login(Returnables::Login *)));
	connect(m_twitLib,SIGNAL(TwitterUp(Returnables::TwitterUp *)),this,SLOT(TwitterUp(Returnables::TwitterUp *)));
	connect(m_twitLib,SIGNAL(UserTimeline(Returnables::UserTimeline *)),this,SLOT(UserTimeline(Returnables::UserTimeline *)));
	connect(m_twitLib,SIGNAL(Favorites(Returnables::Favorites *)),this,SLOT(Favorites(Returnables::Favorites *)));
	connect(m_twitLib,SIGNAL(NewStatus(Returnables::NewStatus *)),this,SLOT(NewStatus(Returnables::NewStatus *)));
	connect(m_twitLib,SIGNAL(RecentReplies(Returnables::RecentReplies *)),this,SLOT(RecentReplies(Returnables::RecentReplies *)));
	connect(m_twitLib,SIGNAL(RemoveStatus(Returnables::RemoveStatus *)),this,SLOT(RemoveStatus(Returnables::RemoveStatus *)));
	connect(m_twitLib,SIGNAL(Friends(Returnables::Friends *)),this,SLOT(Friends(Returnables::Friends *)));
	connect(m_twitLib,SIGNAL(Followers(Returnables::Followers *)),this,SLOT(Followers(Returnables::Followers *)));
	connect(m_twitLib,SIGNAL(UserDetails(Returnables::UserDetails *)),this,SLOT(UserDetails(Returnables::UserDetails *)));
	connect(m_twitLib,SIGNAL(SentDirectMessages(Returnables::SentDirectMessages *)),this,SLOT(SentDirectMessages(Returnables::SentDirectMessages *)));
	connect(m_twitLib,SIGNAL(ReceivedDirectMessages(Returnables::ReceivedDirectMessages *)),this,SLOT(ReceivedDirectMessages(Returnables::ReceivedDirectMessages *)));
	connect(m_twitLib,SIGNAL(SendDirectMessage(Returnables::SendDirectMessage *)),this,SLOT(SendDirectMessage(Returnables::SendDirectMessage *)));
	connect(m_twitLib,SIGNAL(RemoveDirectMessage(Returnables::RemoveDirectMessage *)),this,SLOT(RemoveDirectMessage(Returnables::RemoveDirectMessage *)));
	connect(m_twitLib,SIGNAL(AddFriendship(Returnables::AddFriendship *)),this,SLOT(AddFriendship(Returnables::AddFriendship *)));
	connect(m_twitLib,SIGNAL(RemoveFriendship(Returnables::RemoveFriendship *)),this,SLOT(RemoveFriendship(Returnables::RemoveFriendship *)));
	connect(m_twitLib,SIGNAL(FriendshipExists(Returnables::FriendshipExist *)),this,SLOT(FriendshipExists(Returnables::FriendshipExist *)));
	connect(m_twitLib,SIGNAL(UpdateLocation(Returnables::UpdateLocation *)),this,SLOT(UpdateLocation(Returnables::UpdateLocation *)));
	connect(m_twitLib,SIGNAL(DeliveryDevice(Returnables::DeliveryDevice *)),this,SLOT(DeliveryDevice(Returnables::DeliveryDevice *)));
	connect(m_twitLib,SIGNAL(ApiRequests(Returnables::ApiRequests *)),this,SLOT(ApiRequests(Returnables::ApiRequests *)));
	connect(m_twitLib,SIGNAL(AddFavorite(Returnables::AddFavorite *)),this,SLOT(AddFavorite(Returnables::AddFavorite *)));
	connect(m_twitLib,SIGNAL(RemoveFavorite(Returnables::RemoveFavorite *)),this,SLOT(RemoveFavorite(Returnables::RemoveFavorite *)));
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
void Example::PublicTimeline(Returnables::PublicTimeline *publicTimeline) {}
//=====================================================================
void Example::FriendsTimeline(Returnables::FriendsTimeline *friendsTimeline) {}
//=====================================================================
void Example::SingleStatus(Returnables::SingleStatus *singleStatus) {}
//=====================================================================
void Example::FeaturedUsers(Returnables::FeaturedUsers *featuredUsers) {}
//=====================================================================
void Example::Login(Returnables::Login *login) {}
//=====================================================================
void Example::TwitterUp(Returnables::TwitterUp *isTwitterUp) {}
//=====================================================================
void Example::UserTimeline(Returnables::UserTimeline *userTimeline) {}
//=====================================================================
void Example::Favorites(Returnables::Favorites *favorites) {}
//=====================================================================
void Example::NewStatus(Returnables::NewStatus *newStatus) {}
//=====================================================================
void Example::RecentReplies(Returnables::RecentReplies *recentReplies) {}
//=====================================================================
void Example::RemoveStatus(Returnables::RemoveStatus *removeStatus) {}
//=====================================================================
void Example::Friends(Returnables::Friends *friends) {}
//=====================================================================
void Example::Followers(Returnables::Followers *followers) {}
//=====================================================================
void Example::UserDetails(Returnables::UserDetails *userDetails) {}
//=====================================================================
void Example::SentDirectMessages(Returnables::SentDirectMessages *sentDirectMessages) {}
//=====================================================================
void Example::ReceivedDirectMessages(Returnables::ReceivedDirectMessages *receivedDirectMessages) {}
//=====================================================================
void Example::SendDirectMessage(Returnables::SendDirectMessage *sendDirectMesssage) {}
//=====================================================================
void Example::RemoveDirectMessage(Returnables::RemoveDirectMessage *removeDirectMessage) {}
//=====================================================================
void Example::AddFriendship(Returnables::AddFriendship *addFriendship) {}
//=====================================================================
void Example::RemoveFriendship(Returnables::RemoveFriendship *removeFriendship) {}
//=====================================================================
void Example::FriendshipExists(Returnables::FriendshipExist *friendshipExists) {}
//=====================================================================
void Example::UpdateLocation(Returnables::UpdateLocation *updateLocation) {}
//=====================================================================
void Example::DeliveryDevice(Returnables::DeliveryDevice *deliveryDevice) {}
//=====================================================================
void Example::ApiRequests(Returnables::ApiRequests *apiRequests) {}
//=====================================================================
void Example::AddFavorite(Returnables::AddFavorite *addFavorite) {}
//=====================================================================
void Example::RemoveFavorite(Returnables::RemoveFavorite *removeFavorite) {}
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
	case PUBLIC_TIMELINE:
		m_twitLib->GetPublicTimeline();
		break;
	case FRIENDS_TIMELINE:
		m_twitLib->GetFriendsTimeline(NULL);
		break;
	case SINGLE_STATUS:
		m_twitLib->GetSingleStatus(123);
		break;
	case FEATURED_USERS:
		m_twitLib->GetFeaturedUsers();
		break;
	case LOGIN:
		m_twitLib->Login(GetUsername(),GetPassword());
		break;
	case TWITTER_UP:
		m_twitLib->IsTwitterUp();
		break;
	case USER_TIMELINE:
		m_twitLib->GetUsersTimeline(NULL);
		break;
	case FAVORITES:
		m_twitLib->GetFavorites("",1);
		break;
	case NEW_STATUS:
		m_twitLib->PostNewStatus("New Status");
		break;
	case RECENT_REPLIES:
		m_twitLib->GetRecentReplies(NULL);
		break;
	case REMOVE_STATUS:
		m_twitLib->RemoveStatus(123);
		break;
	case FRIENDS:
		m_twitLib->GetFriends(NULL);
		break;
	case FOLLOWERS:
		m_twitLib->GetFollowers(NULL);
		break;
	case USER_DETAILS:
		m_twitLib->GetUserDetails("blackey02");
		break;
	case SENT_DIRECT_MESSAGES:
		m_twitLib->GetSentDirectMessages(NULL);
		break;
	case RECEIVED_DIRECT_MESSAGES:
		m_twitLib->GetReceivedDirectMessages(NULL);
		break;
	case SEND_DIRECT_MESSAGE:
		m_twitLib->SendDirectMessage("blackey02","New Test Direct Message");
		break;
	case REMOVE_DIRECT_MESAGE:
		m_twitLib->RemoveDirectMessage(123);
		break;
	case ADD_FRIENDSHIP:
		m_twitLib->AddFriendship("blackey02",true);
		break;
	case REMOVE_FRIENDSHIP:
		m_twitLib->RemoveFriendship("blackey02");
		break;
	case FRIENDSHIP_EXISTS:
		m_twitLib->FriendshipExist("blackey02","kevinrose");
		break;
	case UPDATE_LOCATION:
		m_twitLib->UpdateLocation("Pleasanton, CA");
		break;
	case DELIVERY_DEVICE:
		m_twitLib->UpdateDeliveryDevice(SERVER::NONE);
		break;
	case API_REQUESTS:
		m_twitLib->RemainingApiRequests();
		break;
	case ADD_FAVORITE:
		m_twitLib->AddFavorite(123);
		break;
	case REMOVE_FAVORITE:
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

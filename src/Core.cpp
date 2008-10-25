#include "Core.h"

#include <QtXml/QDomDocument>
#include <QtGui/QMessageBox>
#include <QtCore/QUrl>
#include <QtCore/QFile>

//=====================================================================
QString Core::TWITTER_HOST = "twitter.com";
QString Core::VERIFY_CREDENTIALS_URL = "/account/verify_credentials.xml";
QString Core::PUBLIC_TIMELINE_URL = "/statuses/public_timeline.xml";
QString Core::GET_SINGLE_STATUS_URL = "/statuses/show/[req-id].xml";
QString Core::FEATURED_USERS_URL = "/statuses/featured.xml";
QString Core::LOGOUT_URL = "/account/end_session";
QString Core::IS_TWITTER_UP_URL = "/help/test.xml";
QString Core::USERS_TIMELINE_URL = "/statuses/user_timeline[/opt-user].xml";
QString Core::GET_FAVORITES_URL = "/favorites[/opt-user].xml";
QString Core::FRIENDS_TIMELINE_URL = "/statuses/friends_timeline.xml";
QString Core::POST_NEW_STATUS_URL = "/statuses/update.xml";
QString Core::GET_REPLIES_URL = "/statuses/replies.xml";
QString Core::REMOVE_STATUS_URL = "/statuses/destroy/[req-id].xml";
QString Core::GET_FRIENDS_URL = "/statuses/friends[/opt-user].xml";
QString Core::GET_FOLLOWERS_URL = "/statuses/followers[/opt-user].xml";
QString Core::GET_USER_DETAILS_URL = "/users/show/[req-user].xml";
QString Core::GET_SENT_DIRECT_MESSAGES_URL = "/direct_messages/sent.xml";
QString Core::GET_RECEIVED_DIRECT_MESSAGES_URL = "/direct_messages.xml";
QString Core::SEND_NEW_DIRECT_MESSAGE_URL = "/direct_messages/new.xml";
QString Core::REMOVE_DIRECT_MESSAGE_URL = "/direct_messages/destroy/[req-id].xml";
QString Core::CREATE_FRIENDSHIP_URL = "/friendships/create/[req-user].xml";
QString Core::REMOVE_FRIENDSHIP_URL = "/friendships/destroy/[req-user].xml";
QString Core::FRIENDSHIP_EXIST_URL = "http://twitter.com/friendships/exists.xml";
QString Core::UPDATE_LOCATION_URL = "/account/update_location.xml";
QString Core::UPDATE_DELIVERY_DEVICE_URL = "/account/update_delivery_device.xml";
QString Core::REMAINING_API_REQUESTS_URL = "/account/rate_limit_status.xml";
QString Core::ADD_FAVORITE_URL = "/favorites/create/[req-id].xml";
QString Core::REMOVE_FAVORITE_URL = "/favorites/destroy/[req-id].xml";
QString Core::START_FOLLOW_URL = "/notifications/follow/[req-user].xml";
QString Core::STOP_FOLLOW_URL = "/notifications/leave/[req-user].xml";
QString Core::START_BLOCK_URL = "/blocks/create/[req-user].xml";
QString Core::STOP_BLOCK_URL = "/blocks/destroy/[req-user].xml";

//=====================================================================
Core::Core()
{
    m_eventLoop = new QEventLoop(this);
	m_http = new QHttp(TWITTER_HOST);

	MakeConnections();
}
//=====================================================================
Core::~Core()
{
    if(m_eventLoop)
        delete m_eventLoop;
    if(m_http)
        delete m_http;
}
//=====================================================================
void Core::MakeConnections()   
{
    connect(m_http, SIGNAL(dataReadProgress(int, int)), this, SLOT(DataReadProgress(int, int)));   
    connect(m_http, SIGNAL(requestStarted(int)), this, SLOT(RequestStarted(int)));
    connect(m_http, SIGNAL(requestFinished(int,bool)), this, SLOT(ReqFinished(int, bool)));
    connect(m_http, SIGNAL(done(bool)), this, SLOT(Done(bool)));
    connect(this, SIGNAL(QueryDone()), m_eventLoop, SLOT(quit()));
}
//=====================================================================
void Core::Done ( bool /*error*/ )
{
    emit QueryDone();
}
//=====================================================================
void Core::DataReadProgress ( int /*done*/, int /*total*/ )
{
    //emit OnMessageReceived(QString::number(done).toStdString()+" / "+QString::number(total).toStdString());
}
//=====================================================================
int Core::MakeGetRequest(QString req,RequestId reqId)
{
    int id;
    QBuffer *tempBuffer = new QBuffer;
    tempBuffer->open(QIODevice::ReadWrite);
    id = m_http->get(req,tempBuffer);
	m_buffer[id].buffer = tempBuffer;
	m_buffer[id].requestid = reqId;
	return id;
}
//=====================================================================
int Core::MakePostRequest(QString path,QByteArray req,RequestId reqId)
{
    int id;
    QBuffer *tempBuffer = new QBuffer;
    tempBuffer->open(QIODevice::ReadWrite);
    id = m_http->post(path,req,tempBuffer);
	m_buffer[id].buffer = tempBuffer;
	m_buffer[id].requestid = reqId;
	return id;
}
//=====================================================================
void Core::RequestStarted(int /*id*/)
{}
//=====================================================================
void Core::ReqFinished(int id, bool error)
{
    QString response;
    QHttpResponseHeader head;

	if(error)
	{
		emit OnError(m_http->errorString());
	}
    
	head = m_http->lastResponse(); 
    if(head.isValid())
        responseHeaderReceived(head);
     
	if(m_buffer[id].buffer)
		response = QString(m_buffer[id].buffer->data());
	else
		response = QString::null;
     
	if(!response.isNull())
    {
		switch(m_buffer[id].requestid)
		{
		case PUBLIC_TIMELINE:
			Returnables::PublicTimeline *pTimeline;
			pTimeline = Decipher::PublicTimeline(response);
			emit PublicTimeline(pTimeline);
			break;
		case FRIENDS_TIMELINE:
			Returnables::FriendsTimeline *fTimeline;
			fTimeline = Decipher::FriendsTimeline(response);
			emit FriendsTimeline(fTimeline);
			break;
		case SINGLE_STATUS:
			Returnables::SingleStatus *singleStatus;
			singleStatus = Decipher::SingleStatus(response);
			emit SingleStatus(singleStatus);
			break;
		case FEATURED_USERS:
			Returnables::FeaturedUsers *featuredUsers;
			featuredUsers = Decipher::FeaturedUsers(response);
			emit FeaturedUsers(featuredUsers);
			break;
		case VERIFY_CREDENTIALS:
			Returnables::Login *login;
			login = Decipher::Login(response);
			emit Login(login);
			break;
		case TWITTER_UP:
			Returnables::TwitterUp *twitterUp;
			twitterUp = Decipher::TwitterUp(response);
			emit TwitterUp(twitterUp);
			break;
		case USER_TIMELINE:
			Returnables::UserTimeline *userTimeline;
			userTimeline = Decipher::UserTimeline(response);
			emit UserTimeline(userTimeline);
			break;
		case FAVORITES:
			Returnables::Favorites *favorites;
			favorites = Decipher::Favorites(response);
			emit Favorites(favorites);
			break;
		case NEW_STATUS:
			Returnables::NewStatus *newStatus;
			newStatus = Decipher::NewStatus(response);
			emit NewStatus(newStatus);
			break;
		case RECENT_REPLIES:
			Returnables::RecentReplies *replies;
			replies = Decipher::RecentReplies(response);
			emit RecentReplies(replies);
			break;
		case REMOVE_STATUS:
			Returnables::RemoveStatus *removedStatus;
			removedStatus = Decipher::RemoveStatus(response);
			emit RemoveStatus(removedStatus);
			break;
		case FRIENDS:
			Returnables::Friends *friends;
			friends = Decipher::Friends(response);
			emit Friends(friends);
			break;
		case FOLLOWERS:
			Returnables::Followers *followers;
			followers = Decipher::Followers(response);
			emit Followers(followers);
			break;
		case USER_DETAILS:
			Returnables::UserDetails *userDetails;
			userDetails = Decipher::UserDetails(response);
			emit UserDetails(userDetails);
			break;
		case SENT_DIRECT_MESSAGES:
			Returnables::SentDirectMessages *sentDirectMessages;
			sentDirectMessages = Decipher::SentDirectMessages(response);
			emit SentDirectMessages(sentDirectMessages);
			break;
		case RECEIVED_DIRECT_MESSAGES:
			Returnables::ReceivedDirectMessages *receivedDirectMessages;
			receivedDirectMessages = Decipher::ReceivedDirectMessages(response);
			emit ReceivedDirectMessages(receivedDirectMessages);
			break;
		case SEND_DIRECT_MESSAGE:
			Returnables::SendDirectMessage *sendDirectMessage;
			sendDirectMessage = Decipher::SendDirectMessage(response);
			emit SendDirectMessage(sendDirectMessage);
			break;
		case REMOVE_DIRECT_MESSAGE:
			Returnables::RemoveDirectMessage *removeDirectMessage;
			removeDirectMessage = Decipher::RemoveDirectMessage(response);
			emit RemoveDirectMessage(removeDirectMessage);
			break;
		case ADD_FRIENDSHIP:
			Returnables::AddFriendship *addFriendship;
			addFriendship = Decipher::AddFriendShip(response);
			emit AddFriendship(addFriendship);
			break;
		case REMOVE_FRIENDSHIP:
			Returnables::RemoveFriendship *removeFriendship;
			removeFriendship = Decipher::RemoveFriendship(response);
			emit RemoveFriendship(removeFriendship);
			break;
		case FRIENDSHIP_EXISTS:
			Returnables::FriendshipExist *friendshipExists;
			friendshipExists = Decipher::FriendshipExist(response);
			emit FriendshipExists(friendshipExists);
			break;
		case UPDATE_LOCATION:
			Returnables::UpdateLocation *updateLocation;
			updateLocation = Decipher::UpdateLocation(response);
			emit UpdateLocation(updateLocation);
			break;
		case DELIVERY_DEVICE:
			Returnables::DeliveryDevice *deliveryDevice;
			deliveryDevice = Decipher::DeliveryDevice(response);
			emit DeliveryDevice(deliveryDevice);
			break;
		case API_REQUESTS:
			Returnables::ApiRequests *apiRequests;
			apiRequests = Decipher::ApiRequests(response);
			emit ApiRequests(apiRequests);
			break;
		case ADD_FAVORITE:
			Returnables::AddFavorite *addFavorite;
			addFavorite = Decipher::AddFavorite(response);
			emit AddFavorite(addFavorite);
			break;
		case REMOVE_FAVORITE:
			Returnables::RemoveFavorite *removeFavorite;
			removeFavorite = Decipher::RemoveFavorite(response);
			emit RemoveFavorite(removeFavorite);
			break;
		default:
			emit OnMessageReceived(response);
		}
	}

	if(m_buffer[id].buffer)
    {
		m_buffer[id].buffer->close();
		delete m_buffer[id].buffer;
		m_buffer[id].buffer = NULL;
    }
}
//=====================================================================
void Core::responseHeaderReceived(const QHttpResponseHeader &resp)
{
	switch(resp.statusCode())
	{
		case SERVER::OK:
            emit OnStatusReceived(SERVER::OK);
			break;
		case SERVER::NOT_MODIFIED:
            emit OnStatusReceived(SERVER::NOT_MODIFIED);
			break;
		case SERVER::BAD_REQUEST:
            emit OnStatusReceived(SERVER::BAD_REQUEST);
			break;
		case SERVER::NOT_AUTHORIZED:
            emit OnStatusReceived(SERVER::NOT_AUTHORIZED);
			break;
		case SERVER::FORBIDDEN:
            emit OnStatusReceived(SERVER::FORBIDDEN);
			break;
		case SERVER::NOT_FOUND:
            emit OnStatusReceived(SERVER::NOT_FOUND);
			break;
		case SERVER::INTERNAL_SERVER_ERROR:
            emit OnStatusReceived(SERVER::INTERNAL_SERVER_ERROR);
			break;
		case SERVER::BAD_GATEWAY:
            emit OnStatusReceived(SERVER::BAD_GATEWAY);
			break;
		case SERVER::SERVICE_UNAVAILABLE:
            emit OnStatusReceived(SERVER::SERVICE_UNAVAILABLE);
			break;
		default:
            emit OnStatusReceived(SERVER::UNKNOWN);
			break;
	}
}
//=====================================================================
void Core::GetPublicTimeline()
{
    MakeGetRequest(PUBLIC_TIMELINE_URL,PUBLIC_TIMELINE);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::GetSingleStatus(QString id)
{
    QString req;
    req = GET_SINGLE_STATUS_URL;
    req.replace("[req-id]",id);
    MakeGetRequest(req,SINGLE_STATUS);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::GetFeaturedUsers()
{
    MakeGetRequest(FEATURED_USERS_URL, FEATURED_USERS);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::Logout()
{
    m_http->setUser("","");
	MakePostRequest(LOGOUT_URL,"",LOGOUT);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::Login(QString user, QString passw)
{
    m_http->setUser(user, passw);
    MakeGetRequest(VERIFY_CREDENTIALS_URL,VERIFY_CREDENTIALS);
}
//=====================================================================
void Core::IsTwitterUp()
{
    MakeGetRequest(IS_TWITTER_UP_URL,TWITTER_UP);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::GetUsersTimeline(SERVER::Option2 *opt  /*=NULL*/)
{
    QString buildUrl = USERS_TIMELINE_URL;
    
    if(opt)
    {
        QString user        = opt->user.c_str();
        QString count      = QString::number(opt->count);
        QString since       = opt->since.c_str();
        QString sinceId    = QString::number(opt->sinceId);
        QString page       = QString::number(opt->page);
        
        if(!user.isEmpty())
            buildUrl.replace("[/opt-user]","/"+user);
        else
            buildUrl.replace("[/opt-user]","");
        
        buildUrl += "?count="+count;
        buildUrl += "&since="+since;
        buildUrl += "&since_id="+sinceId;
        buildUrl += "&page="+page;
    }
    else
    {
        buildUrl.replace("[/opt-user]","");
    }

    MakeGetRequest(buildUrl,USER_TIMELINE);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::GetFavorites(QString user  /*=""*/, unsigned int page  /*=1*/)
{
    QString buildUrl  = GET_FAVORITES_URL;
    
    if(!user.isEmpty())
        buildUrl.replace("[/opt-user]","/"+user);
    else
        buildUrl.replace("[/opt-user]","");
    
	buildUrl += "?page="+QString::number(page);

    MakeGetRequest(buildUrl,FAVORITES);    
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::GetFriendsTimeline(SERVER::Option1 *opt  /*=NULL*/)
{
    QString buildUrl = FRIENDS_TIMELINE_URL;
    
    if(opt)
    {       
        QString since       = opt->since.c_str();
        QString sinceId    = QString::number(opt->sinceId);
        QString count      = QString::number(opt->count);
        QString page       = QString::number(opt->page);
        
        buildUrl += "?since="+since;
        buildUrl += "&since_id="+sinceId;
        buildUrl += "&count="+count;
        buildUrl += "&page="+page;
    }

    MakeGetRequest(buildUrl,FRIENDS_TIMELINE);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::PostNewStatus(QString status)
{
    QByteArray encodedUrl, req;
    encodedUrl = QUrl::toPercentEncoding(status);
    
    req = "status=";
    req += encodedUrl;
    
    MakePostRequest(POST_NEW_STATUS_URL,req,NEW_STATUS);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::GetRecentReplies(SERVER::Option3 *opt  /*=NULL*/)
{
    QString buildUrl = GET_REPLIES_URL;
    
    if(opt)
    {       
        QString page       = QString::number(opt->page);
        QString since       = opt->since.c_str();
        QString sinceId    = QString::number(opt->sinceId);
        
        buildUrl += "?page="+page;
        buildUrl += "&since="+since;
        buildUrl += "&sinceId="+sinceId;
    }

    MakeGetRequest(buildUrl,RECENT_REPLIES);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::RemoveStatus(QString id)
{
	QString buildUrl = REMOVE_STATUS_URL;
	buildUrl = buildUrl.replace("[req-id]",id);
    
	MakePostRequest(buildUrl,"",REMOVE_STATUS);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::GetFriends(SERVER::Option4 *opt  /*=NULL*/)
{
    QString buildUrl = GET_FRIENDS_URL;
    
    if(opt)
    {
        QString user        = opt->user.c_str();
        QString page       = QString::number(opt->page);
        QString lite          = opt->lite ? "true" : "false";
        QString since       = opt->since.c_str();
        
        if(!user.isEmpty())
            buildUrl.replace("[/opt-user]","/"+user);
        else
            buildUrl.replace("[/opt-user]","");
        
        buildUrl += "?page="+page;
        buildUrl += "&lite="+lite;
        buildUrl += "&since="+since;       
    }
    else
    {
        buildUrl.replace("[/opt-user]","");
    }

    MakeGetRequest(buildUrl,FRIENDS);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::GetFollowers(SERVER::Option5 *opt  /*=NULL*/)
{
    QString buildUrl = GET_FOLLOWERS_URL;
    
    if(opt)
    {
        QString user        = opt->user.c_str();
        QString page       = QString::number(opt->page);
        QString lite          = opt->lite ? "true" : "false";
        
        if(!user.isEmpty())
            buildUrl.replace("[/opt-user]","/"+user);
        else
            buildUrl.replace("[/opt-user]","");
        
        buildUrl += "?page="+page;
        buildUrl += "&lite="+lite;
    }
    else
    {
        buildUrl.replace("[/opt-user]","");
    }

    MakeGetRequest(buildUrl,FOLLOWERS);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::GetUserDetails(QString user)
{
    QString buildUrl = GET_USER_DETAILS_URL;
    
    buildUrl = buildUrl.replace("[req-user]",user);
    
    MakeGetRequest(buildUrl,USER_DETAILS);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::GetSentDirectMessages(SERVER::Option6 *opt  /*=NULL*/)
{
    QString buildUrl = GET_SENT_DIRECT_MESSAGES_URL;
    
    if(opt)
    {       
        QString since       = opt->since.c_str();
        QString sinceId    = QString::number(opt->sinceId);
        QString page       = QString::number(opt->page);
        
        buildUrl += "?since="+since;
        buildUrl += "&sinceId="+sinceId;
        buildUrl += "&page="+page;
    }

    MakeGetRequest(buildUrl,SENT_DIRECT_MESSAGES);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::GetReceivedDirectMessages(SERVER::Option6 *opt  /*=NULL*/)
{
    QString buildUrl = GET_RECEIVED_DIRECT_MESSAGES_URL;
    
    if(opt)
    {       
        QString since       = opt->since.c_str();
        QString sinceId    = QString::number(opt->sinceId);
        QString page       = QString::number(opt->page);
        
        buildUrl += "?since="+since;
        buildUrl += "&sinceId="+sinceId;
        buildUrl += "&page="+page;
    }

    MakeGetRequest(buildUrl,RECEIVED_DIRECT_MESSAGES);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::SendDirectMessage(QString user, QString text)
{
    QByteArray encodedText, req;
    encodedText = QUrl::toPercentEncoding(text);
    
    req = "user=";
    req += user.toAscii();
    req += "&";
    req += "text=";
    req += encodedText;
    
    MakePostRequest(SEND_NEW_DIRECT_MESSAGE_URL,req,SEND_DIRECT_MESSAGE);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=================================================================================================================
void Core::RemoveDirectMessage(QString id)
{
    QString buildUrl = REMOVE_DIRECT_MESSAGE_URL;
    
    buildUrl = buildUrl.replace("[req-id]",id);

	MakePostRequest(buildUrl,"",REMOVE_DIRECT_MESSAGE);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::AddFriendship(QString user, bool follow)
{
    QByteArray req;
	QString buildUrl;

	buildUrl = CREATE_FRIENDSHIP_URL;
	buildUrl = buildUrl.replace("[req-user]",user);
  
    req = "follow=";
	req += follow ? "true" : "false";
      
	MakePostRequest(buildUrl,req,ADD_FRIENDSHIP);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::RemoveFriendship(QString user)
{
    QString buildUrl = REMOVE_FRIENDSHIP_URL;
    
    buildUrl = buildUrl.replace("[req-user]",user);
    
	MakePostRequest(buildUrl,"",REMOVE_FRIENDSHIP);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::FriendshipExist(QString user_a, QString user_b)
{
    QString buildUrl = FRIENDSHIP_EXIST_URL;
    
    buildUrl += "?user_a="+user_a;
    buildUrl += "&user_b="+user_b;
    
    MakeGetRequest(buildUrl,FRIENDSHIP_EXISTS);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::VerifyCredentials()
{
    MakeGetRequest(VERIFY_CREDENTIALS_URL);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::UpdateLocation(QString location)
{
    QByteArray req, encodedText;
    encodedText = QUrl::toPercentEncoding(location);
  
    req = "location=";
    req += encodedText;
    
    MakePostRequest(UPDATE_LOCATION_URL,req,UPDATE_LOCATION);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::UpdateDeliveryDevice(SERVER::DEVICES device)
{
	QByteArray req;

	switch(device)
    {
        case SERVER::SMS:
            req = "device=sms";
            break;
        case SERVER::IM:
            req = "device=im";
           break;
        case SERVER::NONE:
            req = "device=none";
            break;
    }
    
	MakePostRequest(UPDATE_DELIVERY_DEVICE_URL,req,DELIVERY_DEVICE);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::RemainingApiRequests()
{
    MakeGetRequest(REMAINING_API_REQUESTS_URL,API_REQUESTS);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::AddFavorite(QString id)
{
    QString buildUrl = ADD_FAVORITE_URL;
    
    buildUrl = buildUrl.replace("[req-id]",id);
    
	MakePostRequest(buildUrl,"",ADD_FAVORITE);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::RemoveFavorite(QString id)
{
    QString buildUrl = REMOVE_FAVORITE_URL;
    
    buildUrl = buildUrl.replace("[req-id]",id);
    
	MakePostRequest(buildUrl,"",REMOVE_FAVORITE);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::StartFollow(QString user)
{
    QString buildUrl = START_FOLLOW_URL;
    
    buildUrl = buildUrl.replace("[req-user]",user);
    
    MakeGetRequest(buildUrl);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::StopFollow(QString user)
{
    QString buildUrl = STOP_FOLLOW_URL;
    
    buildUrl = buildUrl.replace("[req-user]",user);
    
    MakeGetRequest(buildUrl);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::BlockUser(QString user)
{
    QString buildUrl = START_BLOCK_URL;
    
    buildUrl = buildUrl.replace("[req-user]",user);
    
    MakeGetRequest(buildUrl);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::UnBlockUser(QString user)
{
    QString buildUrl = STOP_BLOCK_URL;
    
    buildUrl = buildUrl.replace("[req-user]",user);
    
    MakeGetRequest(buildUrl);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================









#include "Core.h"

#include <QtXml/QDomDocument>
#include <QtGui/QMessageBox>
#include <QtCore/QUrl>

//=====================================================================
QString Core::TWITTER_HOST = "twitter.com";
QString Core::VERIFY_CREDENTIALS_URL = "/account/verify_credentials.xml";
QString Core::PUBLIC_TIMELINE_URL = "/statuses/public_timeline.xml";
QString Core::GET_SINGLE_STATUS_URL = "/statuses/show/[req-id].xml";
QString Core::FEATURED_USERS_URL = "/statuses/featured.xml";
QString Core::LOGOUT_URL = "/account/end_session";
QString Core::DOWNTIME_SCH_URL = "/downtime_schedule.xml";
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
QString Core::UPDATE_DELIVERY_DEVICE = "/account/update_delivery_device.xml";
QString Core::REMAINING_API_REQUESTS = "/account/rate_limit_status.xml";
QString Core::ADD_FAVORITE_URL = "/favorites/create/[req-id].xml";
QString Core::REMOVE_FAVORITE_URL = "/favorites/destroy/[req-id].xml";
QString Core::START_FOLLOW_URL = "/notifications/follow/[req-user].xml";
QString Core::STOP_FOLLOW_URL = "/notifications/leave/[req-user].xml";
QString Core::START_BLOCK_URL = "/blocks/create/[req-user].xml";
QString Core::STOP_BLOCK_URL = "/blocks/destroy/[req-user].xml";

//=====================================================================
Core::Core(ITwitReply *obj)
{
    m_subscriber = obj;
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
void Core::Done ( bool error )
{
    emit QueryDone();
}
//=====================================================================
void Core::DataReadProgress ( int done, int total )
{
    //m_subscriber->OnMessageReceived(QString::number(done).toStdString()+" / "+QString::number(total).toStdString());
}
//=====================================================================
int Core::MakeGetRequest(QString req)
{
    int reqId;
    QBuffer *tempBuffer = new QBuffer;
    tempBuffer->open(QIODevice::ReadWrite);
    reqId = m_http->get(req,tempBuffer);
    m_buffer[reqId] = tempBuffer;
	return reqId;
}
//=====================================================================
int Core::MakePostRequest(QString path,QByteArray req)
{
    int reqId;
    QBuffer *tempBuffer = new QBuffer;
    tempBuffer->open(QIODevice::ReadWrite);
    reqId = m_http->post(path,req,tempBuffer);
    m_buffer[reqId] = tempBuffer;
	return reqId;
}
//=====================================================================
void Core::RequestStarted(int id)
{}
//=====================================================================
void Core::ReqFinished(int id, bool error)
{
    QByteArray resp;
    QHttpResponseHeader head;
    
    head = m_http->lastResponse();
    if(head.isValid())
        responseHeaderReceived(head);
     
    if(m_buffer[id])
        resp = m_buffer[id]->data();
     
    if(error)
    {
        m_subscriber->OnError(m_http->errorString().toStdString());
    }
    else if(id == m_loginId)
    {      
        m_credentialsId = MakeGetRequest(VERIFY_CREDENTIALS_URL);
    }
    else if(id == m_credentialsId)
    {
        QString buffer = QString(resp);
        if(buffer.contains("true"))
            m_subscriber->OnLoginStatus(true);
        else
            m_subscriber->OnLoginStatus(false);
    }
    else
    {
        m_subscriber->OnMessageReceived(QString(resp).toStdString());
    }
    
    if(m_buffer[id])
    {
        m_buffer[id]->close();
        delete m_buffer[id];
        m_buffer[id] = NULL;
    }
}
//=====================================================================
void Core::responseHeaderReceived(const QHttpResponseHeader &resp)
{
	switch(resp.statusCode())
	{
		case SERVER::OK:
            m_subscriber->OnStatusReceived(SERVER::OK);
			break;
		case SERVER::NOT_MODIFIED:
            m_subscriber->OnStatusReceived(SERVER::NOT_MODIFIED);
			break;
		case SERVER::BAD_REQUEST:
            m_subscriber->OnStatusReceived(SERVER::BAD_REQUEST);
			break;
		case SERVER::NOT_AUTHORIZED:
            m_subscriber->OnLoginStatus(false);
            m_subscriber->OnStatusReceived(SERVER::NOT_AUTHORIZED);
			break;
		case SERVER::FORBIDDEN:
            m_subscriber->OnStatusReceived(SERVER::FORBIDDEN);
			break;
		case SERVER::NOT_FOUND:
            m_subscriber->OnStatusReceived(SERVER::NOT_FOUND);
			break;
		case SERVER::INTERNAL_SERVER_ERROR:
            m_subscriber->OnStatusReceived(SERVER::INTERNAL_SERVER_ERROR);
			break;
		case SERVER::BAD_GATEWAY:
            m_subscriber->OnStatusReceived(SERVER::BAD_GATEWAY);
			break;
		case SERVER::SERVICE_UNAVAILABLE:
            m_subscriber->OnStatusReceived(SERVER::SERVICE_UNAVAILABLE);
			break;
		default:
            m_subscriber->OnStatusReceived(SERVER::UNKNOWN);
			break;
	}
}
//=====================================================================
void Core::GetPublicTimeline()
{
    MakeGetRequest(PUBLIC_TIMELINE_URL);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::GetSingleStatus(QString id)
{
    QString req;
    req = GET_SINGLE_STATUS_URL;
    req.replace("[req-id]",id);
    MakeGetRequest(req);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::GetFeaturedUsers()
{
    MakeGetRequest(FEATURED_USERS_URL);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::Logout()
{
    MakeGetRequest(LOGOUT_URL);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::Login(QString user, QString passw)
{
    m_loginId = m_http->setUser(user, passw);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::GetDowntimeSchedule()
{
    MakeGetRequest(DOWNTIME_SCH_URL);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::IsTwitterUp()
{
    MakeGetRequest(IS_TWITTER_UP_URL);
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

    MakeGetRequest(buildUrl);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::GetFavorites(QString user  /*=""*/, int page  /*=1*/)
{
    QString buildUrl  = GET_FAVORITES_URL;
    
    if(!user.isEmpty())
        buildUrl.replace("[/opt-user]","/"+user);
    else
        buildUrl.replace("[/opt-user]","");
    
    buildUrl += "?page="+page;
    
    MakeGetRequest(buildUrl);    
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

    MakeGetRequest(buildUrl);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::PostNewStatus(QString status)
{
    QByteArray encodedUrl, req;
    encodedUrl = QUrl::toPercentEncoding(status);
    
    req = "status=";
    req += encodedUrl;
    
    MakePostRequest(POST_NEW_STATUS_URL,req);
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

    MakeGetRequest(buildUrl);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::RemoveStatus(QString id)
{
    QString buildUrl = REMOVE_STATUS_URL;
    
    buildUrl = buildUrl.replace("[req-id]",id);
    
    MakeGetRequest(buildUrl);
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

    MakeGetRequest(buildUrl);
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

    MakeGetRequest(buildUrl);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::GetUserDetails(QString user)
{
    QString buildUrl = GET_USER_DETAILS_URL;
    
    buildUrl = buildUrl.replace("[req-user]",user);
    
    MakeGetRequest(buildUrl);
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

    MakeGetRequest(buildUrl);
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

    MakeGetRequest(buildUrl);
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
    
    MakePostRequest(SEND_NEW_DIRECT_MESSAGE_URL,req);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=================================================================================================================
void Core::RemoveDirectMessage(QString id)
{
    QString buildUrl = REMOVE_DIRECT_MESSAGE_URL;
    
    buildUrl = buildUrl.replace("[req-id]",id);
    
    MakeGetRequest(buildUrl);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::AddFriendship(QString user)
{
    QString buildUrl = CREATE_FRIENDSHIP_URL;
    
    buildUrl = buildUrl.replace("[req-user]",user);
    
    MakeGetRequest(buildUrl);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::RemoveFriendship(QString user)
{
    QString buildUrl = REMOVE_FRIENDSHIP_URL;
    
    buildUrl = buildUrl.replace("[req-user]",user);
    
    MakeGetRequest(buildUrl);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::FriendshipExist(QString user_a, QString user_b)
{
    QString buildUrl = FRIENDSHIP_EXIST_URL;
    
    buildUrl += "?user_a="+user_a;
    buildUrl += "&user_b="+user_b;
    
    MakeGetRequest(buildUrl);
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
    
    MakePostRequest(UPDATE_LOCATION_URL,req);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::UpdateDeliveryDevice(SERVER::DEVICES device)
{
    QString buildUrl = UPDATE_DELIVERY_DEVICE;

    switch(device)
    {
        case SERVER::SMS:
            buildUrl += "?device=sms";
            break;
        case SERVER::IM:
            buildUrl += "?device=im";
           break;
        case SERVER::NONE:
            buildUrl += "?device=none";
            break;
    }
    
    MakeGetRequest(buildUrl);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::RemainingApiRequests()
{
    MakeGetRequest(REMAINING_API_REQUESTS);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::AddFavorite(QString id)
{
    QString buildUrl = ADD_FAVORITE_URL;
    
    buildUrl = buildUrl.replace("[req-id]",id);
    
    MakeGetRequest(buildUrl);
    m_eventLoop->exec(QEventLoop::AllEvents);
}
//=====================================================================
void Core::RemoveFavorite(QString id)
{
    QString buildUrl = REMOVE_FAVORITE_URL;
    
    buildUrl = buildUrl.replace("[req-id]",id);
    
    MakeGetRequest(buildUrl);
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









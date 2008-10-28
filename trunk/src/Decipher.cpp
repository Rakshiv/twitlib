#include "Decipher.h"
#include <QtXML/QDomDocument>
#include <QtXML/QDomNodeList>
#include <QtCore/QTextStream>


//=====================================================================
QString Decipher::nStatus = "status";
QString Decipher::nCreatedAt = "created_at";
QString Decipher::nId = "id";
QString Decipher::nText = "text";
QString Decipher::nSource = "source";
QString Decipher::nTruncated = "truncated";
QString Decipher::nInReplyToStatusId = "in_reply_to_status_id";
QString Decipher::nInReplyToUserId = "in_reply_to_user_id";
QString Decipher::nFavorited = "favorited";
QString Decipher::nUser = "user";
QString Decipher::nName = "name";
QString Decipher::nScreenName = "screen_name";
QString Decipher::nDescription = "description";
QString Decipher::nLocation = "location";
QString Decipher::nProfileImageUrl = "profile_image_url";
QString Decipher::nUrl = "url";
QString Decipher::nProtected = "protected";
QString Decipher::nFollowersCount = "followers_count";
QString Decipher::nAuthorized = "authorized";
QString Decipher::nOk = "ok";
QString Decipher::nProfileBackgroundColor = "profile_background_color";
QString Decipher::nProfileTextColor = "profile_text_color";
QString Decipher::nProfileLinkColor = "profile_link_color";
QString Decipher::nProfileSidebarFillColor = "profile_sidebar_fill_color";
QString Decipher::nProfileSidebarBorderColor = "profile_sidebar_border_color";
QString Decipher::nFriendsCount = "friends_count";
QString Decipher::nFavoritesCount = "favourites_count";
QString Decipher::nUtcOffset = "utc_offset";
QString Decipher::nTimeZone = "time_zone";
QString Decipher::nProfileBackgroundImageUrl = "profile_background_image_url";
QString Decipher::nProfileBackgroundTiled = "profile_background_tile";
QString Decipher::nStatusesCount = "statuses_count";
QString Decipher::nDirectMessage = "direct_message";
QString Decipher::nSenderId = "sender_id";
QString Decipher::nRecipientId = "recipient_id";
QString Decipher::nSenderScreenName = "sender_screen_name";
QString Decipher::nRecipientScreenName = "recipient_screen_name";
QString Decipher::nSender = "sender";
QString Decipher::nRecipient = "recipient";
QString Decipher::nFriends = "friends";
QString Decipher::nHash = "hash";
QString Decipher::nResetTime = "reset-time";
QString Decipher::nResetTimeSeconds = "reset-time-in-seconds";
QString Decipher::nRemainingHits = "remaining-hits";
QString Decipher::nHourlyLimit = "hourly-limit";
//=====================================================================
Decipher::Decipher()
{}
//=====================================================================
Decipher::~Decipher()
{}
//=====================================================================
QLinkedList<Returnables::StatusUser*> Decipher::GetStatusUserList(const QString &xml, Parent parent)
{
	QDomDocument doc;
	QDomNodeList nodeList;
	QLinkedList<Returnables::StatusUser*> statusUserList;

	doc.setContent(xml);

	switch(parent)
	{
	case STATUS:
		nodeList = doc.elementsByTagName(nStatus);
		break;
	case USER:
		nodeList = doc.elementsByTagName(nUser);
		break;
	}

	for(int i=0; i<nodeList.count(); i++)
	{
		Returnables::StatusUser *item = new Returnables::StatusUser();
		QDomElement node;
		node = nodeList.at(i).toElement();

		switch(parent)
		{
		case STATUS:
			{
				PopulateStatus(item->status,node);
				node = node.namedItem(nUser).toElement();
				PopulateUser(item->user,node);
				break;
			}
		case USER:
			{
				PopulateUser(item->user,node);
				node = node.namedItem(nStatus).toElement();
				PopulateStatus(item->status,node);
				break;
			}
		}
		statusUserList.append(item);
	}

	return statusUserList;
}
//=====================================================================
QLinkedList<Returnables::DirectMessage*> Decipher::GetDirectMessageList(const QString &xml)
{
	QDomDocument doc;
	QDomNodeList nodeList;
	QLinkedList<Returnables::DirectMessage*> directMessageList;

	doc.setContent(xml);
	nodeList = doc.elementsByTagName(nDirectMessage);

	for(int i=0; i<nodeList.count(); i++)
	{
		Returnables::DirectMessage *directMessage = new Returnables::DirectMessage();
		QDomElement nodeSender, nodeRecipient;
		QDomElement node;

		node = nodeList.at(i).toElement();	
		PopulateDirectHeader(directMessage->headerInfo,node);
		nodeSender = node.namedItem(nSender).toElement();
		PopulateUser(directMessage->sender,nodeSender);
		nodeRecipient = node.namedItem(nRecipient).toElement();
		PopulateUser(directMessage->recipient,nodeRecipient);

		directMessageList.append(directMessage);
	}

	return directMessageList;
}
//=====================================================================
void Decipher::PopulateStatus(Returnables::Status &status, const QDomElement &node)
{
	status.createdAt = node.namedItem(nCreatedAt).toElement().text();
	status.id = node.namedItem(nId).toElement().text().toUInt();
	status.text = node.namedItem(nText).toElement().text();
	status.source = node.namedItem(nSource).toElement().text();
	status.truncated = (node.namedItem(nTruncated).toElement().text().toLower() == "true") ? true : false;
	status.inReplyToStatusId = node.namedItem(nInReplyToStatusId).toElement().text().toUInt();
	status.inReplyToUserId = node.namedItem(nInReplyToUserId).toElement().text().toUInt();
	status.favorited = (node.namedItem(nFavorited).toElement().text().toLower() == "true") ? true : false;
}
//=====================================================================
void Decipher::PopulateUser(Returnables::User &user, const QDomElement &node)
{
	user.id = node.namedItem(nId).toElement().text().toUInt();
	user.name = node.namedItem(nName).toElement().text();
	user.screenName = node.namedItem(nScreenName).toElement().text();
	user.description = node.namedItem(nDescription).toElement().text();
	user.location = node.namedItem(nLocation).toElement().text();
	user.profileImageUrl = node.namedItem(nProfileImageUrl).toElement().text();
	user.url = node.namedItem(nUrl).toElement().text();
	user.isProtected = (node.namedItem(nProtected).toElement().text().toLower() == "true") ? true : false;
	user.followersCount = node.namedItem(nFollowersCount).toElement().text().toUInt();
}
//=====================================================================
void Decipher::PopulateDetails(Returnables::Details &details, const QDomElement &node)
{
	details.createdAt = node.namedItem(nCreatedAt).toElement().text();
	details.favoritesCount = node.namedItem(nFavoritesCount).toElement().text().toUInt();
	details.friendsCount = node.namedItem(nFriendsCount).toElement().text().toUInt();
	details.profileBackgroundColor = node.namedItem(nProfileBackgroundColor).toElement().text();
	details.profileBackgroundImageUrl = node.namedItem(nProfileBackgroundImageUrl).toElement().text();
	details.profileBackgroundTiled = (node.namedItem(nProfileBackgroundTiled).toElement().text().toLower() == "true") ? true : false;
	details.profileLinkColor = node.namedItem(nProfileLinkColor).toElement().text();
	details.profileSidebarBorderColor = node.namedItem(nProfileSidebarBorderColor).toElement().text();
	details.profileSidebarFillColor = node.namedItem(nProfileSidebarFillColor).toElement().text();
	details.profileTextColor = node.namedItem(nProfileTextColor).toElement().text();
	details.statusesCount = node.namedItem(nStatusesCount).toElement().text().toUInt();
	details.timeZone = node.namedItem(nTimeZone).toElement().text();
	details.utcOffset = node.namedItem(nUtcOffset).toElement().text().toInt();
}
//=====================================================================
void Decipher::PopulateDirectHeader(Returnables::DirectHeader &header, const QDomElement &node)
{
	header.createdAt = node.namedItem(nCreatedAt).toElement().text();
	header.id = node.namedItem(nId).toElement().text().toUInt();
	header.recipientId = node.namedItem(nRecipientId).toElement().text().toUInt();
	header.recipientScreenName = node.namedItem(nRecipientScreenName).toElement().text();
	header.senderId = node.namedItem(nSenderId).toElement().text().toUInt();
	header.senderScreenName = node.namedItem(nSenderScreenName).toElement().text();
	header.text = node.namedItem(nText).toElement().text();
}
//=====================================================================
void Decipher::PopulateApiRequests(Returnables::ApiRequests &apiRequests, const QDomElement &node)
{
	apiRequests.hourlyLimit = node.namedItem(nHourlyLimit).toElement().text().toUInt();
	apiRequests.remainingHits = node.namedItem(nRemainingHits).toElement().text().toUInt();
	apiRequests.resetTime = node.namedItem(nResetTime).toElement().text();
	apiRequests.resetTimeSeconds = node.namedItem(nResetTimeSeconds).toElement().text().toUInt();
}
//=====================================================================
Returnables::PublicTimeline* Decipher::PublicTimeline(const QString &xml)
{
	Returnables::PublicTimeline *publicTimeline = NULL;
	QLinkedList<Returnables::StatusUser*> list = GetStatusUserList(xml);

	if(!list.isEmpty())
	{		
		publicTimeline = new Returnables::PublicTimeline();
		publicTimeline->list = list;
		publicTimeline->reqID = Returnables::PUBLIC_TIMELINE;
	}

	return publicTimeline;
}
//=====================================================================
Returnables::FriendsTimeline* Decipher::FriendsTimeline(const QString &xml)
{
	Returnables::FriendsTimeline *friendsTimeline = NULL;
	QLinkedList<Returnables::StatusUser*> list = GetStatusUserList(xml);

	if(!list.isEmpty())
	{	
		friendsTimeline = new Returnables::FriendsTimeline();
		friendsTimeline->list = list;
		friendsTimeline->reqID = Returnables::FRIENDS_TIMELINE;
	}

	return friendsTimeline;
}
//=====================================================================
Returnables::SingleStatus* Decipher::SingleStatus(const QString &xml)
{
	Returnables::SingleStatus *singleStatus = NULL;
	QLinkedList<Returnables::StatusUser*> list = GetStatusUserList(xml);

	if(!list.isEmpty())
	{
		singleStatus = new Returnables::SingleStatus();
		*singleStatus->status = list.first()->status;
		*singleStatus->user = list.first()->user;
		singleStatus->reqID = Returnables::SINGLE_STATUS;
	}

	return singleStatus;
}
//=====================================================================
Returnables::FeaturedUsers* Decipher::FeaturedUsers(const QString &xml)
{
	Returnables::FeaturedUsers *featuredUsers = NULL;
	QLinkedList<Returnables::StatusUser*> list = GetStatusUserList(xml,USER);

	if(!list.isEmpty())
	{
		featuredUsers = new Returnables::FeaturedUsers();
		featuredUsers->list = list;
		featuredUsers->reqID = Returnables::FEATURED_USERS;
	}

	return featuredUsers;
}
//=====================================================================
Returnables::Login* Decipher::Login(const QString &xml)
{
	Returnables::Login *login = NULL;
	QDomDocument doc;
	QDomElement elem;

	doc.setContent(xml);
	elem = doc.namedItem(nAuthorized).toElement();

	if(!elem.isNull())
	{
		login = new Returnables::Login();
		login->authorized = (elem.text().toLower().contains("true")) ? true : false;
		login->reqID = Returnables::LOGIN;
	}

	return login;
}
//=====================================================================
Returnables::TwitterUp* Decipher::TwitterUp(const QString &xml)
{
	Returnables::TwitterUp *twitterUp = NULL;
	QDomDocument doc;
	QDomElement elem;

	doc.setContent(xml);
	elem = doc.namedItem(nOk).toElement();

	if(!elem.isNull())
	{
		twitterUp = new Returnables::TwitterUp();
		twitterUp->up = (elem.text().toLower().contains("true")) ? true : false;
		twitterUp->reqID = Returnables::TWITTER_UP;
	}

	return twitterUp;
}
//=====================================================================
Returnables::UserTimeline* Decipher::UserTimeline(const QString &xml)
{
	Returnables::UserTimeline *userTimeline = NULL;
	QLinkedList<Returnables::StatusUser*> list = GetStatusUserList(xml);

	if(!list.isEmpty())
	{	
		userTimeline = new Returnables::UserTimeline();
		userTimeline->list = list;
		userTimeline->reqID = Returnables::USER_TIMELINE;
	}

	return userTimeline;
}
//=====================================================================
Returnables::Favorites* Decipher::Favorites(const QString &xml)
{
	Returnables::Favorites *favorites = NULL;
	QLinkedList<Returnables::StatusUser*> list = GetStatusUserList(xml);

	if(!list.isEmpty())
	{	
		favorites = new Returnables::Favorites();
		favorites->list = list;
		favorites->reqID = Returnables::FAVORITES;
	}

	return favorites;
}
//=====================================================================
Returnables::NewStatus* Decipher::NewStatus(const QString &xml)
{
	Returnables::NewStatus *newStatus = NULL;
	QLinkedList<Returnables::StatusUser*> list = GetStatusUserList(xml);

	if(!list.isEmpty())
	{
		newStatus = new Returnables::NewStatus();
		*newStatus->newStatus = list.first()->status;
		*newStatus->user = list.first()->user;
		newStatus->reqID = Returnables::NEW_STATUS;
	}

	return newStatus;
}
//=====================================================================
Returnables::RecentReplies* Decipher::RecentReplies(const QString &xml)
{
	Returnables::RecentReplies *replies = NULL;
	QLinkedList<Returnables::StatusUser*> list = GetStatusUserList(xml);

	if(!list.isEmpty())
	{	
		replies = new Returnables::RecentReplies();
		replies->list = list;
		replies->reqID = Returnables::RECENT_REPLIES;
	}

	return replies;
}
//=====================================================================
Returnables::RemoveStatus* Decipher::RemoveStatus(const QString &xml)
{
	Returnables::RemoveStatus *removedStatus = NULL;
	QLinkedList<Returnables::StatusUser*> list = GetStatusUserList(xml);

	if(!list.isEmpty())
	{
		removedStatus = new Returnables::RemoveStatus();
		*removedStatus->removedStatus = list.first()->status;
		*removedStatus->user = list.first()->user;
		removedStatus->reqID = Returnables::REMOVE_STATUS;
	}

	return removedStatus;
}

//=====================================================================
Returnables::Friends* Decipher::Friends(const QString &xml)
{
	Returnables::Friends *friends = NULL;
	QLinkedList<Returnables::StatusUser*> list = GetStatusUserList(xml,USER);

	if(!list.isEmpty())
	{
		friends = new Returnables::Friends();
		friends->list = list;
		friends->reqID = Returnables::FRIENDS;
	}

	return friends;
}
//=====================================================================
Returnables::Followers* Decipher::Followers(const QString &xml)
{
	Returnables::Followers *followers = NULL;
	QLinkedList<Returnables::StatusUser*> list = GetStatusUserList(xml,USER);

	if(!list.isEmpty())
	{
		followers = new Returnables::Followers();
		followers->list = list;
		followers->reqID = Returnables::FOLLOWERS;
	}

	return followers;
}
//=====================================================================
Returnables::UserDetails* Decipher::UserDetails(const QString &xml)
{
	Returnables::UserDetails *userDetails = new Returnables::UserDetails();
	QDomDocument doc;
	QDomElement elem;
	bool success;

	doc.setContent(xml);
	elem = doc.firstChildElement(nUser);
	success = !elem.isNull() ? true : false;
	PopulateUser(*userDetails->user,elem);
	PopulateDetails(*userDetails->details,elem);
	elem = elem.firstChildElement(nStatus);
	success = (success && !elem.isNull()) ? true : false;
	PopulateStatus(*userDetails->status,elem);
	userDetails->reqID = Returnables::USER_DETAILS;

	if(!success)
	{
		delete userDetails;
		userDetails = NULL;
	}

	return userDetails;
}
//=====================================================================
Returnables::SentDirectMessages* Decipher::SentDirectMessages(const QString &xml)
{
	Returnables::SentDirectMessages *sentDirectMessage = NULL;
	QLinkedList<Returnables::DirectMessage*> list = GetDirectMessageList(xml);

	if(!list.isEmpty())
	{
		sentDirectMessage = new Returnables::SentDirectMessages();
		sentDirectMessage->list = list;
		sentDirectMessage->reqID = Returnables::SENT_DIRECT_MESSAGES;
	}

	return sentDirectMessage;
}
//=====================================================================
Returnables::ReceivedDirectMessages* Decipher::ReceivedDirectMessages(const QString &xml)
{
	Returnables::ReceivedDirectMessages *receivedDirectMessages = NULL;
	QLinkedList<Returnables::DirectMessage*> list = GetDirectMessageList(xml);

	if(!list.isEmpty())
	{
		receivedDirectMessages = new Returnables::ReceivedDirectMessages();
		receivedDirectMessages->list = list;
		receivedDirectMessages->reqID = Returnables::RECEIVED_DIRECT_MESSAGES;
	}

	return receivedDirectMessages;
}
//=====================================================================
Returnables::SendDirectMessage* Decipher::SendDirectMessage(const QString &xml)
{
	Returnables::SendDirectMessage *sendDirectMessage = NULL;
	QLinkedList<Returnables::DirectMessage*> list = GetDirectMessageList(xml);

	if(!list.isEmpty())
	{
		sendDirectMessage = new Returnables::SendDirectMessage();
		*sendDirectMessage->headerInfo = list.first()->headerInfo;
		*sendDirectMessage->recipient = list.first()->recipient;
		*sendDirectMessage->sender = list.first()->sender;
		sendDirectMessage->reqID = Returnables::SEND_DIRECT_MESSAGE;
	}

	return sendDirectMessage;
}
//=====================================================================
Returnables::RemoveDirectMessage* Decipher::RemoveDirectMessage(const QString &xml)
{
	Returnables::RemoveDirectMessage *removeDirectMessage = NULL;
	QLinkedList<Returnables::DirectMessage*> list = GetDirectMessageList(xml);

	if(!list.isEmpty())
	{
		removeDirectMessage = new Returnables::RemoveDirectMessage();
		*removeDirectMessage->headerInfo = list.first()->headerInfo;
		*removeDirectMessage->recipient = list.first()->recipient;
		*removeDirectMessage->sender = list.first()->sender;
		removeDirectMessage->reqID = Returnables::REMOVE_DIRECT_MESSAGE;
	}

	return removeDirectMessage;	
}
//=====================================================================
Returnables::AddFriendship* Decipher::AddFriendShip(const QString &xml)
{
	Returnables::AddFriendship *addFriendship = NULL;
	QLinkedList<Returnables::StatusUser*> list = GetStatusUserList(xml,USER);

	if(!list.isEmpty())
	{	
		addFriendship = new Returnables::AddFriendship();
		*addFriendship->status = list.first()->status;
		*addFriendship->user = list.first()->user;
		addFriendship->reqID = Returnables::ADD_FRIENDSHIP;
	}

	return addFriendship;	
}
//=====================================================================
Returnables::RemoveFriendship* Decipher::RemoveFriendship(const QString &xml)
{
	Returnables::RemoveFriendship *removeFriendship = NULL;
	QLinkedList<Returnables::StatusUser*> list = GetStatusUserList(xml,USER);

	if(!list.isEmpty())
	{	
		removeFriendship = new Returnables::RemoveFriendship();
		*removeFriendship->status = list.first()->status;
		*removeFriendship->user = list.first()->user;
		removeFriendship->reqID = Returnables::REMOVE_FRIENDSHIP;
	}

	return removeFriendship;
}
//=====================================================================
Returnables::FriendshipExist* Decipher::FriendshipExist(const QString &xml)
{
	Returnables::FriendshipExist* friendshipExists = NULL;
	QDomDocument doc;
	QDomElement elem;

	doc.setContent(xml);
	elem = doc.namedItem(nFriends).toElement();

	if(!elem.isNull())
	{
		friendshipExists = new Returnables::FriendshipExist();
		friendshipExists->friends = (elem.text().toLower().contains("true")) ? true : false;
		friendshipExists->reqID = Returnables::FRIENDSHIP_EXISTS;
	}

	return friendshipExists;
}
//=====================================================================
Returnables::UpdateLocation* Decipher::UpdateLocation(const QString &xml)
{
	Returnables::UpdateLocation *updateLocation = NULL;
	QLinkedList<Returnables::StatusUser*> list = GetStatusUserList(xml,USER);

	if(!list.isEmpty())
	{	
		updateLocation = new Returnables::UpdateLocation();
		*updateLocation->status = list.first()->status;
		*updateLocation->user = list.first()->user;
		updateLocation->reqID = Returnables::UPDATE_LOCATION;
	}

	return updateLocation;
}
//=====================================================================
Returnables::DeliveryDevice* Decipher::DeliveryDevice(const QString &xml)
{
	Returnables::DeliveryDevice *deliveryDevice = NULL;
	QLinkedList<Returnables::StatusUser*> list = GetStatusUserList(xml,USER);

	if(!list.isEmpty())
	{	
		deliveryDevice = new Returnables::DeliveryDevice();
		*deliveryDevice->status = list.first()->status;
		*deliveryDevice->user = list.first()->user;
		deliveryDevice->reqID = Returnables::DELIVERY_DEVICE;
	}

	return deliveryDevice;
}
//=====================================================================
Returnables::ApiRequests* Decipher::ApiRequests(const QString &xml)
{
	Returnables::ApiRequests* apiRequests = NULL;
	QDomDocument doc;
	QDomElement elem;

	doc.setContent(xml);
	elem = doc.namedItem(nHash).toElement();

	if(!elem.isNull())
	{
		apiRequests = new Returnables::ApiRequests();
		PopulateApiRequests(*apiRequests,elem);
		apiRequests->reqID = Returnables::API_REQUESTS;
	}

	return apiRequests;
}
//=====================================================================
Returnables::AddFavorite* Decipher::AddFavorite(const QString &xml)
{
	Returnables::AddFavorite *addFavorite = NULL;
	QLinkedList<Returnables::StatusUser*> list = GetStatusUserList(xml);

	if(!list.isEmpty())
	{	
		addFavorite = new Returnables::AddFavorite();
		*addFavorite->status = list.first()->status;
		*addFavorite->user = list.first()->user;
		addFavorite->reqID = Returnables::ADD_FAVORITE;
	}

	return addFavorite;
}
//=====================================================================
Returnables::RemoveFavorite* Decipher::RemoveFavorite(const QString &xml)
{
	Returnables::RemoveFavorite *removeFavorite = NULL;
	QLinkedList<Returnables::StatusUser*> list = GetStatusUserList(xml);

	if(!list.isEmpty())
	{	
		removeFavorite = new Returnables::RemoveFavorite();
		*removeFavorite->status = list.first()->status;
		*removeFavorite->user = list.first()->user;
		removeFavorite->reqID = Returnables::REMOVE_FAVORITE;
	}

	return removeFavorite;
}
//=====================================================================

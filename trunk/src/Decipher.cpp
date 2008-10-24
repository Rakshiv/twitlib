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
Returnables::PublicTimeline* Decipher::PublicTimeline(const QString &xml)
{
	Returnables::PublicTimeline *publicTimeline = new Returnables::PublicTimeline();
	publicTimeline->list = GetStatusUserList(xml);
	return publicTimeline;
}
//=====================================================================
Returnables::FriendsTimeline* Decipher::FriendsTimeline(const QString &xml)
{
	Returnables::FriendsTimeline *friendsTimeline = new Returnables::FriendsTimeline();
	friendsTimeline->list = GetStatusUserList(xml);
	return friendsTimeline;
}
//=====================================================================
Returnables::SingleStatus* Decipher::SingleStatus(const QString &xml)
{
	Returnables::SingleStatus *singleStatus = new Returnables::SingleStatus();
	QDomDocument doc;
	QDomElement elem;

	doc.setContent(xml);
	elem = doc.firstChildElement(nStatus);
	PopulateStatus(*singleStatus->status,elem);
	elem = elem.firstChildElement(nUser);
	PopulateUser(*singleStatus->user,elem);

	return singleStatus;
}
//=====================================================================
Returnables::FeaturedUsers* Decipher::FeaturedUsers(const QString &xml)
{
	Returnables::FeaturedUsers *featuredUsers = new Returnables::FeaturedUsers();
	featuredUsers->list = GetStatusUserList(xml,USER);
	return featuredUsers;
}
//=====================================================================
Returnables::Login* Decipher::Login(const QString &xml)
{
	Returnables::Login *login = new Returnables::Login();
	QDomDocument doc;
	QDomElement elem;

	doc.setContent(xml);
	elem = doc.namedItem(nAuthorized).toElement();
	login->authorized = (elem.text().toLower().contains("true")) ? true : false;
	return login;
}
//=====================================================================
Returnables::TwitterUp* Decipher::TwitterUp(const QString &xml)
{
	Returnables::TwitterUp *twitterUp = new Returnables::TwitterUp();
	QDomDocument doc;
	QDomElement elem;

	doc.setContent(xml);
	elem = doc.namedItem(nOk).toElement();
	twitterUp->up = (elem.text().toLower().contains("true")) ? true : false;
	return twitterUp;
}
//=====================================================================
Returnables::UserTimeline* Decipher::UserTimeline(const QString &xml)
{
	Returnables::UserTimeline *userTimeline = new Returnables::UserTimeline();
	userTimeline->list = GetStatusUserList(xml);
	return userTimeline;
}
//=====================================================================
Returnables::Favorites* Decipher::Favorites(const QString &xml)
{
	Returnables::Favorites *favorites = new Returnables::Favorites();
	favorites->list = GetStatusUserList(xml);
	return favorites;
}
//=====================================================================
Returnables::NewStatus* Decipher::NewStatus(const QString &xml)
{
	Returnables::NewStatus *newStatus = new Returnables::NewStatus();
	QDomDocument doc;
	QDomElement elem;

	doc.setContent(xml);
	elem = doc.firstChildElement(nStatus);
	PopulateStatus(*newStatus->newStatus,elem);
	elem = elem.firstChildElement(nUser);
	PopulateUser(*newStatus->user,elem);

	return newStatus;
}
//=====================================================================
Returnables::RecentReplies* Decipher::RecentReplies(const QString &xml)
{
	Returnables::RecentReplies *replies = new Returnables::RecentReplies();
	replies->list = GetStatusUserList(xml);
	return replies;
}
//=====================================================================
Returnables::RemoveStatus* Decipher::RemoveStatus(const QString &xml)
{
	Returnables::RemoveStatus *removedStatus = new Returnables::RemoveStatus();
	QDomDocument doc;
	QDomElement elem;

	doc.setContent(xml);
	elem = doc.firstChildElement(nStatus);
	PopulateStatus(*removedStatus->removedStatus,elem);
	elem = elem.firstChildElement(nUser);
	PopulateUser(*removedStatus->user,elem);

	return removedStatus;
}

//=====================================================================
Returnables::Friends* Decipher::Friends(const QString &xml)
{
	Returnables::Friends *friends = new Returnables::Friends();
	friends->list = GetStatusUserList(xml,USER);
	return friends;
}
//=====================================================================
Returnables::Followers* Decipher::Followers(const QString &xml)
{
	Returnables::Followers *followers = new Returnables::Followers();
	followers->list = GetStatusUserList(xml,USER);
	return followers;
}
//=====================================================================
Returnables::UserDetails* Decipher::UserDetails(const QString &xml)
{
	Returnables::UserDetails *userDetails = new Returnables::UserDetails();
	QDomDocument doc;
	QDomElement elem;

	doc.setContent(xml);
	elem = doc.firstChildElement(nUser);
	PopulateUser(*userDetails->user,elem);
	PopulateDetails(*userDetails->details,elem);
	elem = elem.firstChildElement(nStatus);
	PopulateStatus(*userDetails->status,elem);

	return userDetails;
}
//=====================================================================
Returnables::SentDirectMessages* Decipher::SentDirectMessages(const QString &xml)
{
	Returnables::SentDirectMessages *sentDirectMessage = new Returnables::SentDirectMessages();
	sentDirectMessage->list = GetDirectMessageList(xml);
	return sentDirectMessage;
}
//=====================================================================
Returnables::ReceivedDirectMessages* Decipher::ReceivedDirectMessages(const QString &xml)
{
	Returnables::ReceivedDirectMessages *receivedDirectMessages = new Returnables::ReceivedDirectMessages();
	receivedDirectMessages->list = GetDirectMessageList(xml);
	return receivedDirectMessages;
}
//=====================================================================

//=====================================================================
//=====================================================================
//=====================================================================
//=====================================================================
//=====================================================================
//=====================================================================
//=====================================================================
//=====================================================================
//=====================================================================
//=====================================================================

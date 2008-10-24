#include "Decipher.h"
#include <QtXML/QDomDocument>
#include <QtXML/QDomNodeList>
#include <QtCore/QTextStream>


//=====================================================================
QString Decipher::nStatus = "status";
QString Decipher::nStatusCreatedAt = "created_at";
QString Decipher::nStatusId = "id";
QString Decipher::nStatusText = "text";
QString Decipher::nStatusSource = "source";
QString Decipher::nStatusTruncated = "truncated";
QString Decipher::nStatusInReplyToStatusId = "in_reply_to_status_id";
QString Decipher::nStatusInReplyToUserId = "in_reply_to_user_id";
QString Decipher::nStatusFavorited = "favorited";
QString Decipher::nUser = "user";
QString Decipher::nUserId = "id";
QString Decipher::nUserName = "name";
QString Decipher::nUserScreenName = "screen_name";
QString Decipher::nUserDescription = "description";
QString Decipher::nUserLocation = "location";
QString Decipher::nUserProfileImageUrl = "profile_image_url";
QString Decipher::nUserUrl = "url";
QString Decipher::nUserProtected = "protected";
QString Decipher::nUserFollowersCount = "followers_count";
QString Decipher::nAuthorized = "authorized";
QString Decipher::nOk = "ok";
//=====================================================================
Decipher::Decipher()
{}
//=====================================================================
Decipher::~Decipher()
{}
//=====================================================================
QLinkedList<Returnables::StatusUser*> Decipher::GetStatuses(const QString &xml, Parent parent)
{
	QDomDocument doc;
	QDomNodeList nodeList;

	QLinkedList<Returnables::StatusUser*> list;

	doc.setContent(xml);

	nodeList = (parent == STATUS) ? doc.elementsByTagName(nStatus) : doc.elementsByTagName(nUser);
	
	for(int i=0; i<nodeList.count(); i++)
	{
		Returnables::StatusUser *item = new Returnables::StatusUser();
		Returnables::Status status;
		Returnables::User user;
		QDomElement node;

		node = nodeList.at(i).toElement();

		switch(parent)
		{
		case STATUS:
			PopulateStatus(status,node);
			node = node.namedItem(nUser).toElement();
			PopulateUser(user,node);
			item->status = status;
			item->user = user;
			break;
		case USER:
			PopulateUser(user,node);
			node = node.namedItem(nStatus).toElement();
			PopulateStatus(status,node);
			item->status = status;
			item->user = user;
			break;
		}
	
		list.append(item);
	}

	return list;
}
//=====================================================================
void Decipher::PopulateStatus(Returnables::Status &status, QDomElement node)
{
	status.createdAt = node.namedItem(nStatusCreatedAt).toElement().text();
	status.id = node.namedItem(nStatusId).toElement().text().toUInt();
	status.text = node.namedItem(nStatusText).toElement().text();
	status.source = node.namedItem(nStatusSource).toElement().text();
	status.truncated = (node.namedItem(nStatusTruncated).toElement().text() == "true") ? true : false;
	status.inReplyToStatusId = node.namedItem(nStatusInReplyToStatusId).toElement().text().toUInt();
	status.inReplyToUserId = node.namedItem(nStatusInReplyToUserId).toElement().text().toUInt();
	status.favorited = (node.namedItem(nStatusFavorited).toElement().text() == "true") ? true : false;
}
//=====================================================================
void Decipher::PopulateUser(Returnables::User &user, QDomElement node)
{
	user.id = node.namedItem(nUserId).toElement().text().toUInt();
	user.name = node.namedItem(nUserName).toElement().text();
	user.screenName = node.namedItem(nUserScreenName).toElement().text();
	user.description = node.namedItem(nUserDescription).toElement().text();
	user.location = node.namedItem(nUserLocation).toElement().text();
	user.profileImageUrl = node.namedItem(nUserProfileImageUrl).toElement().text();
	user.url = node.namedItem(nUserUrl).toElement().text();
	user.isProtected = (node.namedItem(nUserProtected).toElement().text() == "true") ? true : false;
	user.followersCount = node.namedItem(nUserFollowersCount).toElement().text().toUInt();
}
//=====================================================================
Returnables::PublicTimeline* Decipher::PublicTimeline(const QString &xml)
{
	Returnables::PublicTimeline *publicTimeline = new Returnables::PublicTimeline();
	publicTimeline->statuses = GetStatuses(xml);
	return publicTimeline;
}
//=====================================================================
Returnables::FriendsTimeline* Decipher::FriendsTimeline(const QString &xml)
{
	Returnables::FriendsTimeline *friendsTimeline = new Returnables::FriendsTimeline();
	friendsTimeline->statuses = GetStatuses(xml);
	return friendsTimeline;
}
//=====================================================================
Returnables::SingleStatus* Decipher::SingleStatus(const QString &xml)
{
	Returnables::SingleStatus *singleStatus = new Returnables::SingleStatus();
	QLinkedList<Returnables::StatusUser*> list = GetStatuses(xml);
	singleStatus->status = (list.isEmpty()) ? NULL : list.first();
	return singleStatus;
}
//=====================================================================
Returnables::FeaturedUsers* Decipher::FeaturedUsers(const QString &xml)
{
	Returnables::FeaturedUsers *featuredUsers = new Returnables::FeaturedUsers();
	featuredUsers->users = GetStatuses(xml,USER);
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
	userTimeline->statuses = GetStatuses(xml);
	return userTimeline;
}
//=====================================================================
Returnables::Favorites* Decipher::Favorites(const QString &xml)
{
	Returnables::Favorites *favorites = new Returnables::Favorites();
	favorites->statuses = GetStatuses(xml);
	return favorites;
}
//=====================================================================
Returnables::NewStatus* Decipher::NewStatus(const QString &xml)
{
	Returnables::NewStatus *newStatus = new Returnables::NewStatus();
	QLinkedList<Returnables::StatusUser*> list = GetStatuses(xml);
	newStatus->status = (list.isEmpty()) ? NULL : list.first();
	return newStatus;
}


//=====================================================================
//=====================================================================
//=====================================================================
//=====================================================================
//=====================================================================
//=====================================================================
//=====================================================================
#include "Decipher.h"
#include <QtXML/QDomDocument>
#include <QtXML/QDomNodeList>
#include <QtCore/QTextStream>


//=====================================================================
Decipher::Decipher()
{}
//=====================================================================
Decipher::~Decipher()
{}
//=====================================================================
Returnables::PublicTimeline* Decipher::PublicTimeline(const QString &xml)
{
	Returnables::PublicTimeline *publicTimeline = new Returnables::PublicTimeline();

	QDomDocument doc;
	QDomNodeList nodeList;
	QLinkedList<Returnables::Status*> list;
	// Nodes
	const QString status = "status";
	const QString statusCreatedAt = "created_at";
	const QString statusId = "id";
	const QString statusText = "text";
	const QString statusSource = "source";
	const QString statusTruncated = "truncated";
	const QString statusInReplyToStatusId = "in_reply_to_status_id";
	const QString statusInReplyToUserId = "in_reply_to_user_id";
	const QString statusFavorited = "favorited";
	const QString user = "user";
	const QString userId = "id";
	const QString userName = "name";
	const QString userScreenName = "screen_name";
	const QString userDescription = "description";
	const QString userLocation = "location";
	const QString userProfileImageUrl = "profile_image_url";
	const QString userUrl = "url";
	const QString userProtected = "protected";
	const QString userFollowersCount = "followers_count";

	doc.setContent(xml);

	nodeList = doc.elementsByTagName(status);
	
	for(int i=0; i<nodeList.count(); i++)
	{
		Returnables::Status *status = new Returnables::Status();
		QDomElement node;

		node = nodeList.at(i).toElement();

		status->createdAt = node.namedItem(statusCreatedAt).toElement().text();
		status->id = node.namedItem(statusId).toElement().text().toUInt();
		status->text = node.namedItem(statusText).toElement().text();
		status->source = node.namedItem(statusSource).toElement().text();
		status->truncated = (node.namedItem(statusTruncated).toElement().text() == "true") ? true : false;
		status->inReplyToStatusId = node.namedItem(statusInReplyToStatusId).toElement().text().toUInt();
		status->inReplyToUserId = node.namedItem(statusInReplyToUserId).toElement().text().toUInt();
		status->favorited = (node.namedItem(statusFavorited).toElement().text() == "true") ? true : false;

		node = node.namedItem(user).toElement();

		status->userInfo.id = node.namedItem(userId).toElement().text().toUInt();
		status->userInfo.name = node.namedItem(userName).toElement().text();
		status->userInfo.screenName = node.namedItem(userScreenName).toElement().text();
		status->userInfo.description = node.namedItem(userDescription).toElement().text();
		status->userInfo.location = node.namedItem(userLocation).toElement().text();
		status->userInfo.profileImageUrl = node.namedItem(userProfileImageUrl).toElement().text();
		status->userInfo.url = node.namedItem(userUrl).toElement().text();
		status->userInfo.isProtected = (node.namedItem(userProtected).toElement().text() == "true") ? true : false;
		status->userInfo.followersCount = node.namedItem(userFollowersCount).toElement().text().toUInt();
		
		list.append(status);
	}

	publicTimeline->statuses = list;

	return publicTimeline;
}
//=====================================================================
Returnables::FriendsTimeline* Decipher::FriendsTimeline(const QString &xml)
{
	Returnables::FriendsTimeline *friendsTimeline = new Returnables::FriendsTimeline();
	friendsTimeline->statuses = PublicTimeline(xml)->statuses;
	return friendsTimeline;
}
//=====================================================================
//=====================================================================
//=====================================================================
//=====================================================================
//=====================================================================


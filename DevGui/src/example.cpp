#include <QtGui/QMessageBox>
#include "example.h"
#include "Decipher.h"

//=====================================================================

//=====================================================================
Example::Example()
{
	m_gui.setupUi(this);
	m_twitLib = new QTwitLib();
	MakeConnections();
	
	m_gui.pushButton->setText("Public Timeline");
	m_gui.pushButton_2->setText("Login");
	m_gui.pushButton_3->setText("Friends Timeline");
	m_gui.pushButton_4->setText("Clear Text Area");
    m_gui.pushButton_5->setText("Logout");
	m_gui.pushButton_6->setText("Test Event");
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
	connect(m_twitLib, SIGNAL(ReceivedDirectMessages(Returnables::ReceivedDirectMessages *)), this, SLOT(TestReturn(Returnables::ReceivedDirectMessages *)));

    connect(m_twitLib, SIGNAL(OnError(QString)), this, SLOT(OnError(QString)));
    connect(m_twitLib, SIGNAL(OnMessageReceived(QString)), this, SLOT(OnMessageReceived(QString)));
    connect(m_twitLib, SIGNAL(OnStatusReceived(SERVER::RESP)), this, SLOT(OnStatusReceived(SERVER::RESP)));
    connect(m_gui.pushButton, SIGNAL(clicked()), this, SLOT(Button1Event()));
	connect(m_gui.pushButton_2, SIGNAL(clicked()), this, SLOT(Button2Event()));
	connect(m_gui.pushButton_3, SIGNAL(clicked()), this, SLOT(Button3Event()));
	connect(m_gui.pushButton_4, SIGNAL(clicked()), this, SLOT(Button4Event()));	  
    connect(m_gui.pushButton_5, SIGNAL(clicked()), this, SLOT(Button5Event()));
	connect(m_gui.pushButton_6, SIGNAL(clicked()), this, SLOT(Button6Event()));	
}
//=====================================================================
QString Example::GetUsername()
{
	return m_gui.lineEdit->text();
}
//=====================================================================
QString Example::GetPassword()
{
	return m_gui.lineEdit_2->text();
}
//=====================================================================
// Display public timeline
void Example::Button1Event()
{
	m_twitLib->GetPublicTimeline();
}
//=====================================================================
// Login with supplied username / password
void Example::Button2Event()
{	
	m_twitLib->Login(GetUsername(),GetPassword());
}
//=====================================================================
// Get Friends Timeline
void Example::Button3Event()
{	
	m_twitLib->GetFriendsTimeline();
}
//=====================================================================
// Clear Text area
void Example::Button4Event()
{	
	m_gui.plainTextEdit->setPlainText("");
}
//=====================================================================
// Logout
void Example::Button5Event()
{	
	m_gui.plainTextEdit->setPlainText("");
	m_twitLib->Logout();
}
//=====================================================================
// Extra Event
void Example::Button6Event()
{	
	m_twitLib->RemoveFavorite(974728991);
	//m_twitLib->AddFavorite(974728991);
}
//=====================================================================
void Example::TestReturn(Returnables::ReceivedDirectMessages *direct)
{
	QString message = "";

	if(!direct->list.isEmpty())
	//if(!followers->list.isEmpty())
	{
		//message += "Name: "+removed->removedStatus->user.name+"\n";
		//message += "Message: "+removed->removedStatus->status.text;

		message += "sender name: "+direct->list.first()->headerInfo.senderScreenName+"\n";
		message += "recipient name: "+direct->list.first()->recipient.screenName+"\n";

		delete direct;
	}

	//if(twitUp->up)
	//	message = "Twitter's working!!";
	//else
	//	message = "Twitter's down!";

	m_gui.plainTextEdit->appendPlainText("Message "+message);
}
//=====================================================================
void Example::OnError(QString error) 
{ 
    m_gui.plainTextEdit->appendPlainText("ERROR "+error); 
}
//=====================================================================
void Example::OnMessageReceived(QString message)
{ 
    m_gui.plainTextEdit->appendPlainText("MESSAGE "+message); 
}
//=====================================================================
void Example::OnStatusReceived(SERVER::RESP response)
{
    m_gui.plainTextEdit->appendPlainText("STATUS REC "+QString::number(response)); 
}
//=====================================================================

//=====================================================================

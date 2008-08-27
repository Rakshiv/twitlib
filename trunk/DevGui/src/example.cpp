#include <QtGui/QMessageBox>
#include "example.h"


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
    connect(m_twitLib, SIGNAL(OnError(QString)), this, SLOT(OnError(QString)));
    connect(m_twitLib, SIGNAL(OnMessageReceived(QString)), this, SLOT(OnMessageReceived(QString)));
    connect(m_twitLib, SIGNAL(OnStatusReceived(SERVER::RESP)), this, SLOT(OnStatusReceived(SERVER::RESP)));
    connect(m_twitLib, SIGNAL(OnLoginStatus(bool)), this, SLOT(OnLoginStatus(bool)));
    connect(m_gui.pushButton, SIGNAL(clicked()), this, SLOT(Button1Event()));
	connect(m_gui.pushButton_2, SIGNAL(clicked()), this, SLOT(Button2Event()));
	connect(m_gui.pushButton_3, SIGNAL(clicked()), this, SLOT(Button3Event()));
	connect(m_gui.pushButton_4, SIGNAL(clicked()), this, SLOT(Button4Event()));	  
    connect(m_gui.pushButton_5, SIGNAL(clicked()), this, SLOT(Button5Event()));	
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
void Example::OnLoginStatus(bool isLoggedIn)
{ 
    if(isLoggedIn)
        m_gui.plainTextEdit->appendPlainText("LOGIN STATUS GOOD"); 
    else
        m_gui.plainTextEdit->appendPlainText("LOGIN STATUS BAD"); 
}
//=====================================================================

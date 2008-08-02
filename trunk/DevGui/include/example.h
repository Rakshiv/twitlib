#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <QtGui/QMessageBox>
#include "ui_example.h"
#include "TwitLib.h"
#include "Server.h"
#include "ITwitReply.h"


class Example : public QWidget,
				public ITwitReply

{
	Q_OBJECT;
	public:
		Example();
		virtual ~Example();
	
	public:
		void MakeConnections();
		QString GetUsername();
		QString GetPassword();
		
	public: //callback from libTwit
        void OnError(std::string error); 
        void OnMessageReceived(std::string message); 
        void OnStatusReceived(SERVER::RESP response); 
        void OnLoginStatus(bool isLoggedIn); 
		
	public slots:
		void Button1Event();
		void Button2Event();
		void Button3Event();
		void Button4Event();
	
	private:
		Ui::Form m_gui;
		TwitLib  *m_twitLib;
		
};

#endif // EXAMPLE_H


#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <QtCore/QString>
#include "ui_example.h"
#include "QTwitLib.h"
#include "Server.h"
#include "Returnables.h"


class Example : public QWidget
{
	Q_OBJECT;
	public:
		Example();
		virtual ~Example();
	
	public:
		void MakeConnections();
		QString GetUsername();
		QString GetPassword();
		
	public slots:
		void Button1Event();
		void Button2Event();
		void Button3Event();
		void Button4Event();
        void Button5Event();
		void Button6Event();
        void OnError(QString error); 
        void OnMessageReceived(QString message);
        void OnStatusReceived(SERVER::RESP response);

		void TestReturn(Returnables::ReceivedDirectMessages *);
	
	private:
		Ui::Form m_gui;
		QTwitLib  *m_twitLib;
};


#endif // EXAMPLE_H


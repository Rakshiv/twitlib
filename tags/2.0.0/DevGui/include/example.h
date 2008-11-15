#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <QtCore/QString>
#include "ui_example.h"
#include "QTwitLib.h"

#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>

class Example : public QWidget
{
	Q_OBJECT;
	public:
		Example();
		virtual ~Example();
	
	public:
		void SetupBasicUI();
		QString GetUsername();
		QString GetPassword();	
		
	public slots:
		void TabChanged(int tabIdx);
		void ExecuteClicked();
		void LoginClicked();
        void OnError(QString error); 
        void OnMessageReceived(QString message);
        void OnStatusReceived(SERVER::RESP response);
		void OnResponseReceived(Returnables::Response *);

	private:
		void MakeConnections();
		void DisplayList(QLinkedList<Returnables::StatusUser*> list, QString header);
		void DisplayList(QLinkedList<Returnables::DirectMessage*> list, QString header);
	
	private:
		Ui::Form m_gui;
		QTwitLib  *m_twitLib;

	private:
		QPlainTextEdit *m_plainTextEdit;
		QLineEdit *m_lineEditUsername;
		QLineEdit *m_lineEditPassword;
		QLabel *m_labelUsername;
		QLabel *m_labelPassword;
		QPushButton *m_pushButtonLogin;
		QPushButton *m_pushButtonExecute;
};


#endif // EXAMPLE_H


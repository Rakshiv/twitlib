#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <QtCore/QString>
#include "ui_example.h"
#include "QTwitLib.h"

#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>

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
                void DisplayList(QLinkedList<Returnables::StatusElement*> list, QString header);
                void DisplayList(QLinkedList<Returnables::BasicUserInfoElement*> list, QString header);
                void DisplayList(QLinkedList<Returnables::ExtUserInfoElement*> list, QString header);
                void DisplayList(QLinkedList<Returnables::DirectMessageElement*> list, QString header);
                void DisplayList(QLinkedList<unsigned int> list, QString header);
	
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

                QVBoxLayout *leftLayout;
                QHBoxLayout *mainLayout;
};


#endif // EXAMPLE_H


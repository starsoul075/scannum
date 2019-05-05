#pragma once

#include <QThread>

class QTimer;
class QNetworkAccessManager;
class QNetworkReply;
class QFile;

class RequestHandler : public QThread
{
	Q_OBJECT
public:
	RequestHandler(QString fileName, QObject *parent = Q_NULLPTR);
	~RequestHandler();

	void SetUrl(QString url);
	void SetVal(int val);

protected:
	void run() override;

signals:
	void SendRequest();

private slots:
	void HandlerResponse(QNetworkReply *);
	void HandlerSendRequest();

private:
	QString m_requestUrl;
	int m_reqSecVal;
	QString m_saveName;
	QTimer *m_timer;
	bool m_bStop;
	QFile *file;
	QNetworkAccessManager *manager;
};

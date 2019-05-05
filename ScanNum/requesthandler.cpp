#include "requesthandler.h"

#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>

RequestHandler::RequestHandler(QString fielName, QObject *parent)
	: QThread(parent), m_saveName(fielName)
{
	m_requestUrl = "http://m.10010.com/NumApp/NumberCenter/qryNum?callback=jsonp_queryMoreNums&provinceCode=81&cityCode=823&monthFeeLimit=0&groupKey=41250010&searchCategory=3&net=01&amounts=200&codeTypeCode=&searchValue=&qryType=02&goodsNet=4&_=1556009494184";
	m_reqSecVal = 100;
	manager = new QNetworkAccessManager(this);
	connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(HandlerResponse(QNetworkReply *)));
	connect(this, SIGNAL(SendRequest()), this, SLOT(HandlerSendRequest()));

	m_bStop = false;
	file = new QFile(m_saveName);
	file->open(QIODevice::WriteOnly);
}

RequestHandler::~RequestHandler()
{
}

void RequestHandler::SetUrl(QString url)
{
	m_requestUrl = url;
}

void RequestHandler::SetVal(int val)
{
	m_reqSecVal = val;
}

void RequestHandler::run()
{
	while (!m_bStop)
	{
		emit SendRequest();
		QThread::msleep(m_reqSecVal);
	}
}

void RequestHandler::HandlerSendRequest()
{
	manager->get(QNetworkRequest(QUrl(m_requestUrl)));
}

void RequestHandler::HandlerResponse(QNetworkReply *reply)
{
	if (reply->error() != QNetworkReply::NoError)
	{
		return;
	}

	QByteArray data = reply->readAll();
	QByteArray json = data.mid(20, data.length() - 21);
	QJsonParseError err;
	double tmp = 0;
	QJsonDocument doc = QJsonDocument::fromJson(json, &err);
	if (err.error == QJsonParseError::NoError)
	{
		if (doc.isObject())
		{
			QJsonObject obj = doc.object();
			if (obj.contains("numArray"))
			{
				QByteArray array;
				QJsonArray nums = obj.value("numArray").toArray();
				for (int i = 0; i < nums.size(); ++i)
				{
					tmp = nums.at(i).toDouble();
					if (tmp > 100)
					{
						array.append(QString::number(tmp, 'f', 0));
						array.append('\n');
					}
				}
				file->write(array);
				file->flush();
			}
		}
		
	}
}


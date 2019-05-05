#include "json.h"
#include <QJsonDocument>
#include <QJsonParseError>

json::json(QObject *parent)
	: QObject(parent)
{
}

json::~json()
{
}

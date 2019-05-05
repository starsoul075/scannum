#pragma once

#include <QObject>

class json : public QObject
{
	Q_OBJECT

public:
	json(QObject *parent);
	~json();
};

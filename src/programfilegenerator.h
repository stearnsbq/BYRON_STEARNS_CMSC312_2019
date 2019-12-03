#ifndef PROGRAMFILEGENERATOR_H
#define PROGRAMFILEGENERATOR_H
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>


class programfilegenerator
{
public:
programfilegenerator();
QJsonDocument generate(int count = 0);
private:
};

#endif // PROGRAMFILEGENERATOR_H

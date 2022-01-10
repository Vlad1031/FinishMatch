#include "match3model.h"
#include <random>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>

Match3model::Match3model(QObject *parent) : QAbstractListModel(parent)
{
    QFile file;
    file.setFileName(":size.json");
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "Not JSON file";
    }

    QTextStream file_text(&file);
    QString jString;
    jString = file_text.readAll();
    file.close();
    QByteArray jByte = jString.toLocal8Bit();

    auto jDocument = QJsonDocument::fromJson(jByte);

    if(jDocument.isNull()){
        qDebug() << "Failed to create JSON doc";
    }

    if(!jDocument.isObject()){
        qDebug() << "JSON is not an object";
    }

    QJsonObject jObject = jDocument.object();

    if(jObject.isEmpty()){
        qDebug() << "JSON object is empty";
    }

    QJsonArray colors = jObject.value("colors").toArray();
    QJsonValue columns = jObject.value("columns");
    QJsonValue rows = jObject.value("rows");

    qDebug() << colors;
    qDebug() << columns;
    qDebug() << rows;

    for(int i = 0; i < columns.toInt(); i++){
        for(int j = 0; j < rows.toInt(); j++){
            m_board.push_back(j);
        }
    }
}

Match3model::~Match3model() { }

int Match3model::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_board.count();
}

QVariant Match3model::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() > m_board.count()){
        return QVariant();
    }

    switch (role) {
        case Qt::DisplayRole:
        return m_board.value(index.row());
    }
    return QVariant();
}

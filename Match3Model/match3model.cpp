#include "match3model.h"
#include <random>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>

Match3model::Match3model(QObject *parent) : QAbstractListModel(parent)
{
    m_roleNames[ColorRole] = "color";

    for(int i = 0; i < myColumns() * myRows(); i++){
        mBoard mb;
        mb.m_index = i;
        mb.m_color = QColor(myColors()[rand() % myColors().size()]);
        m_board.append(mb);
    }
    shaffle();
}

Match3model::~Match3model() { }

void Match3model::shaffle(){
    auto seed = chrono::system_clock::now().time_since_epoch().count();
    static mt19937 generator(seed);

    do{
        shuffle(m_board.begin(), m_board.end(), generator);
        emit dataChanged(createIndex(0, 0), createIndex(myColumns() * myRows(), 0));
    }while(!boardValid());
}

int Match3model::myRows(){
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

    QJsonObject jObject = jDocument.object();
    QJsonValue rows = jObject.value("rows");

    return rows.toInt();
}

int Match3model::myColumns(){
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

    QJsonObject jObject = jDocument.object();
    QJsonValue columns = jObject.value("columns");

    return columns.toInt();
}
QList<QString> Match3model::myColors(){
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
    QJsonObject jObject = jDocument.object();

    QJsonArray colors = jObject.value("colors").toArray();
    QList<QString> myColor;

    foreach(QJsonValue allColors, colors){
        myColor.append(allColors.toString());
    }
    return myColor;
}

bool Match3model::neighboring(int from, int to){
    if(from % myColumns() < myColumns() - 1 && from + 1 == to)
        return true;
    if(from % myColumns() > 0 && from - 1 == to)
        return true;
    if(from < (myColumns() * myRows() - myColumns()) && from + myColumns() == to)
        return true;
    if(from >= myColumns() && from - myColumns() == to)
        return true;
    return false;
}

void Match3model::move(int from, int to){
    if(neighboring(from, to)){
        m_board.move(from, to);
        if(from > to){
            beginMoveRows(QModelIndex(), from, from, QModelIndex(), to);
            endMoveRows();
            if(to < from && to < from - 1){
                beginMoveRows(QModelIndex(), to + 1, to + 1, QModelIndex(), from + 1);
                endMoveRows();
            }
            m_board.move(to + 1, from);
        }

        else{
            beginMoveRows(QModelIndex(), from, from, QModelIndex(), to + 1);
            endMoveRows();
            if(to > from && to > from + 1){
                beginMoveRows(QModelIndex(), to - 1, to - 1, QModelIndex(), from);
                endMoveRows();
            }
            m_board.move(to - 1, from);
        }
    }
}

bool Match3model::boardValid(){
    if(!combinations().empty()){
        return false;
    }
    return true;
}

//bool Match3model::gameOver(){
//    bool m_gameOver = true;

//    return m_gameOver;
//}

QSet<int> Match3model::combinations(){
    QSet<int> listIndex;
    for(int i = 0; i < m_board.size(); i++){

        if(m_board.value(i).m_index < m_board.size() - 2){
            if(i % myColumns() < myColumns() - 2){
                if(m_board.value(i).m_color == m_board.value(i + 1).m_color &&
                        m_board.value(i).m_color == m_board.value(i + 2).m_color){
                    listIndex.insert(i);
                }
            }

            if(i % myRows() < myRows() + 2){
                if(m_board.value(i).m_color == m_board.value(i + myRows()).m_color &&
                        m_board.value(i).m_color == m_board.value(i + myRows() * 2).m_color){
                    listIndex.insert(i);
                    listIndex.insert(i + myRows());
                    listIndex.insert(i + myRows() * 2);
                }
            }
        }
    }
    qDebug() << listIndex;
    return listIndex;
}

bool Match3model::remove(){
    combinations();

    //для видалення горезонталі
    beginRemoveRows(QModelIndex(), *combinations().begin(), *combinations().begin() + 2);
    for(int i = *combinations().begin(); i < *combinations().end(); i++){
        m_board.removeAt(i);
    }
    endRemoveRows();

    //для видалення вертикалі
    foreach(int a, combinations()){
        beginRemoveRows(QModelIndex(), a, a);
        m_board.removeAt(a);
        endRemoveRows();
    }

    return true;
}

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
    case ColorRole:
        return m_board.value(index.row()).m_color;
    }
    return QVariant();
}

QHash<int, QByteArray> Match3model::roleNames() const{
    return m_roleNames;
}

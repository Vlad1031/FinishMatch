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
        mb.m_color = myColors()[rand() % myColors().size()];
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
    }while(!removeIndex.isEmpty());
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

bool Match3model::combinations(){
    for(int i = 0; i < myRows(); i++){
        for(int j = 0; j < myColumns() - 2; j++){
            if(m_board.at(j + 2 + myColumns() * i).m_color == m_board.at(j + myColumns() * i).m_color &&
                    m_board.at(j + myColumns() * i).m_color == m_board.at(j + 1 + myColumns() * i).m_color){
                for(int n = 0; n < 3; n++){
                    if(find(removeIndex.begin(), removeIndex.end(), j + n + myColumns() * i) == removeIndex.end()){
                        removeIndex.push_back(j + n + myColumns() * i);
                    }
                }
            }
        }
    }

    for(int i = 0; i < myColumns(); i++){
        for(int j = 0; j < myRows() - 2; j++){
            if(m_board.at(myColumns() * (j + 2) + i).m_color == m_board.at(myColumns() * j + i).m_color &&
                    m_board.at(myColumns() * j + i).m_color == m_board.at(myColumns() * (j + 1) + i).m_color){
                for(int n = 0; n < 3; n++){
                    if(find(removeIndex.begin(), removeIndex.end(), myColumns() * (j + n) + i) == removeIndex.end()){
                        removeIndex.push_back(myColumns() * (j + n) + i);
                    }
                }
            }
        }
    }
    qDebug() << removeIndex;
    return !removeIndex.empty();
}

int Match3model::score(){
    scoreCount += removeIndex.size();
    qDebug() << "score =" << scoreCount;
    return scoreCount;
}

void Match3model::remove(){
    score();
    while(!removeIndex.isEmpty()){
        beginRemoveRows(QModelIndex(), removeIndex[0], removeIndex[0]);
        m_board.removeAt(removeIndex[0]);
        endRemoveRows();

        beginInsertRows(QModelIndex(), removeIndex[0], removeIndex[0]);
        m_board.insert(removeIndex[0], mBoard(myColors()[rand() % myColors().size()]));
        endInsertRows();

        for(int i = 0; i < removeIndex[0] / myColumns(); i++){
            move(removeIndex[0] - i * myColumns(), removeIndex[0] - (i + 1) * myColumns());
        }

        removeIndex.pop_front();
    }
}

bool Match3model::gameOver(){
    for(int i = 0; i < myRows(); i++){
        for(int j = 0; j < myColumns(); j++){

            if(i > 1){
                if(myColumns() - j > 1 &&
                        m_board.at(i * myColumns() + j).m_color == m_board.at((i - 1) * myColumns() + j).m_color &&
                        m_board.at((i - 1) * myColumns() + j).m_color == m_board.at((i - 2) * myColumns() + j + 1).m_color){
                    return false;
                }

                if(j > 0 &&
                        m_board.at(i * myColumns() + j).m_color == m_board.at((i - 1) * myColumns() + j).m_color &&
                        m_board.at((i - 1) * myColumns() + j).m_color == m_board.at((i - 2) * myColumns() + j - 1).m_color){
                    return false;
                }

                if(i > 2 &&
                        m_board.at(i * myColumns() + j).m_color == m_board.at((i - 1) * myColumns() + j).m_color &&
                        m_board.at((i - 1) * myColumns() + j).m_color == m_board.at((i - 3) * myColumns() + j).m_color){
                    return false;
                }
            }

            if(myRows() - i > 2){
                if(myColumns() - j > 1 &&
                        m_board.at(i * myColumns() + j).m_color == m_board.at((i + 1) * myColumns() + j).m_color &&
                        m_board.at((i + 1) * myColumns() + j).m_color == m_board.at((i + 2) * myColumns() + j + 1).m_color){
                    return false;
                }

                if(myColumns() - j > 1 &&
                        m_board.at(i * myColumns() + j).m_color == m_board.at((i + 1) * myColumns() + j + 1).m_color &&
                        m_board.at((i + 1) * myColumns() + j + 1).m_color == m_board.at((i + 2) * myColumns()).m_color){
                    return false;
                }

                if(myRows() - i > 3 &&
                        m_board.at(i * myColumns() + j).m_color == m_board.at((i + 1) * myColumns() + j).m_color &&
                        m_board.at((i + 1) * myColumns() + j).m_color == m_board.at((i + 3) * myColumns() + j).m_color){
                    return false;
                }

                if(j > 0 &&
                        m_board.at(i * myColumns() + j).m_color == m_board.at((i + 2) * myColumns() + j).m_color &&
                        m_board.at((i + 2) * myColumns() + j).m_color == m_board.at((i + 1) * myColumns() + j + 1).m_color){
                    return false;
                }

                if(j > 0 &&
                        m_board.at(i * myColumns() + j).m_color == m_board.at((i + 1) * myColumns() + j).m_color &&
                        m_board.at((i + 1) * myColumns() + j).m_color == m_board.at((i + 2) * myColumns() + j - 1).m_color){
                    return false;
                }
            }

            if(j > 1){
                if(myRows() - i > 1 &&
                        m_board.at(i * myColumns() + j).m_color == m_board.at(i * myColumns() + j - 1).m_color &&
                        m_board.at(i * myColumns() + j - 1).m_color == m_board.at((i + 1) * myColumns() + j - 2).m_color){
                    return false;
                }

                if(i > 0 &&
                        m_board.at(i * myColumns() + j).m_color == m_board.at(i * myColumns() + j - 1).m_color &&
                        m_board.at(i * myColumns() + j - 1).m_color == m_board.at((i - 1) * myColumns() + j - 2).m_color){
                    return false;
                }

                if(j > 2 &&
                        m_board.at(i * myColumns() + j).m_color == m_board.at(i * myColumns() + j - 1).m_color &&
                        m_board.at(i * myColumns() + j - 1).m_color == m_board.at(i * myColumns() + j - 3).m_color){
                    return false;
                }
            }

            if(myColumns() - j > 2){
                if(myRows() - i > 1 &&
                        m_board.at(i * myColumns() + j).m_color == m_board.at(i * myColumns() + j + 2).m_color &&
                        m_board.at(i * myColumns() + j + 2).m_color == m_board.at((i + 1) * myColumns() + j + 1).m_color){
                    return false;
                }

                if(myRows() - i > 1 &&
                        m_board.at(i * myColumns() + j).m_color == m_board.at(i * myColumns() + j + 1).m_color &&
                        m_board.at(i * myColumns() + j + 1).m_color == m_board.at((i + 1) * myColumns() + j + 2).m_color){
                    return false;
                }

                if(myColumns() - j > 3 &&
                        m_board.at(i * myColumns() + j).m_color == m_board.at(i * myColumns() + j + 1).m_color &&
                        m_board.at(i * myColumns() + j + 1).m_color == m_board.at(i * myColumns() + j + 3).m_color){
                    return false;
                }

                if(i > 0 &&
                        m_board.at(i * myColumns() + j).m_color == m_board.at(i * myColumns() + j + 2).m_color &&
                        m_board.at(i * myColumns() + j + 2).m_color == m_board.at((i - 1) * myColumns() + j + 1).m_color){
                    return false;
                }

                if(i > 0 &&
                        m_board.at(i * myColumns() + j).m_color == m_board.at(i * myColumns() + j + 1).m_color &&
                        m_board.at(i * myColumns() + j + 1).m_color == m_board.at((i - 1) * myColumns() + j + 2).m_color){
                    return false;
                }
            }
        }
    }
    return true;
}

int Match3model::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return m_board.count();
}

QVariant Match3model::data(const QModelIndex &index, int role) const{
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

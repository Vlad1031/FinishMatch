#include "match3model.h"

Match3model::Match3model(QObject *parent) : QAbstractListModel(parent)
{
    for(int i = 1; i <= 16; i++){
        m_board.push_back(i);
    }
}

Match3model::~Match3model()
{
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
        case Qt::DisplayRole:
        return m_board.value(index.row());
    }
    return QVariant();
}

#ifndef MATCH3MODEL_H
#define MATCH3MODEL_H

#include <QAbstractListModel>
#include <QList>

class Match3model : public QAbstractListModel
{
    Q_OBJECT
    Q_DISABLE_COPY(Match3model)

public:
    explicit Match3model(QObject *parent = nullptr);
    ~Match3model() override;

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

private:
    QList <int> m_board;
};

#endif // MATCH3MODEL_H
#ifndef MATCH3MODEL_H
#define MATCH3MODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QColor>
#include <QString>
#include <QVariant>
#include <QFile>
#include <QByteArray>
using namespace std;

class Match3model : public QAbstractListModel
{
    Q_OBJECT
    Q_DISABLE_COPY(Match3model)

public:

    enum roleNames{
        ColorRole = Qt::UserRole
    };
    virtual QHash<int, QByteArray> roleNames() const override;

    explicit Match3model(QObject *parent = nullptr);
    ~Match3model() override;

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    Q_INVOKABLE bool neighboring(int from, int to);
    Q_INVOKABLE void move(int from, int to);

    Q_INVOKABLE void boardValid();
    Q_INVOKABLE bool gameOver();
    Q_INVOKABLE void remove(int index);

    Q_INVOKABLE int myRows();
    Q_INVOKABLE int myColumns();
    Q_INVOKABLE QList<QString> myColors();

private:
    struct mBoard{
        int m_index;
        QColor m_color;
    };
    QList <mBoard> m_board;
    QHash<int, QByteArray> m_roleNames;
};

#endif // MATCH3MODEL_H

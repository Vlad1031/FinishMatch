#ifndef MATCH3MODEL_H
#define MATCH3MODEL_H

#include <QQuickItem>

class Match3Model : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(Match3Model)

public:
    explicit Match3Model(QQuickItem *parent = nullptr);
    ~Match3Model() override;
};

#endif // MATCH3MODEL_H

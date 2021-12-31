#ifndef MATCH3MODEL_PLUGIN_H
#define MATCH3MODEL_PLUGIN_H

#include <QQmlExtensionPlugin>

class Match3ModelPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override;
};

#endif // MATCH3MODEL_PLUGIN_H

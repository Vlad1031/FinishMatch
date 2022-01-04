#include "match3model_plugin.h"

#include "match3model.h"

#include <qqml.h>

void Match3ModelPlugin::registerTypes(const char *uri)
{
    // @uri Match3model
    qmlRegisterType<Match3model>(uri, 1, 0, "Match3model");
}


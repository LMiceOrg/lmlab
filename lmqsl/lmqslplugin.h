#pragma once

#include "lmqsl_global.h"

#include <extensionsystem/iplugin.h>

namespace LMQSL {
namespace Internal {

class LMQSLPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "LMQSL.json")

public:
    LMQSLPlugin();
    ~LMQSLPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

private:
    void triggerAction();
};

} // namespace Internal
} // namespace LMQSL

#ifndef _OSGEARTH_MEMORY_QTQML_
#define _OSGEARTH_MEMORY_QTQML_ 1

#include "../export.hpp"
#include <QJSEngine>
#include <QObject>
#include <QQmlEngine>
#include <osgEarth/Memory>

namespace osgEarth {
class OSGQTQML_EXPORT MemoryQtQml : public QObject {
    Q_OBJECT
public:
    MemoryQtQml(QObject* parent = 0)
        : QObject(parent)
    {
    }

    Q_INVOKABLE double bytes2kb(unsigned int bytes)
    {
        double d = 1.0 / 1024.0;
        return static_cast<double>(bytes) * d;
    }
    Q_INVOKABLE double bytes2mb(unsigned int bytes)
    {
        double d = 1.0 / (1024.0 * 1024.0);
        return static_cast<double>(bytes) * d;
    }
    Q_INVOKABLE unsigned int getProcessPhysicalUsage()
    {
        return osgEarth::Memory::getProcessPhysicalUsage();
    }
    Q_INVOKABLE unsigned getProcessPeakPhysicalUsage()
    {
        return osgEarth::Memory::getProcessPeakPhysicalUsage();
    }
    Q_INVOKABLE unsigned getProcessPrivateUsage()
    {
        return osgEarth::Memory::getProcessPrivateUsage();
    }
    Q_INVOKABLE unsigned getProcessPeakPrivateUsage()
    {
        return osgEarth::Memory::getProcessPeakPrivateUsage();
    }
};

static QObject* memoryQObjectSingletonTypeProvider(QQmlEngine* engine, QJSEngine* scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    MemoryQtQml* mem = new MemoryQtQml();
    return mem;
}
}

#endif

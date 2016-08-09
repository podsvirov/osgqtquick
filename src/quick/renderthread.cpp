#include "renderthread.hpp"
#include "window.hpp"

#include <iostream>
#include <QDebug>

namespace osgQtQuick {

RenderThread::RenderThread(Window *window)
    : window(window)
    , started(false)
    , surface(0)
    , context(0)
{
    _latestEndFrameTime = QDateTime::currentDateTime().addMSecs(-window->minFrameTime());
    _shutDown = false;
}

void RenderThread::renderNext()
{
    std::cout << "          Render\n"; std::cout.flush();

    if(_shutDown) return;

    context->makeCurrent(surface);

    window->frame();

    QDateTime endFrameTime = QDateTime::currentDateTime();
    unsigned long frameTime = static_cast<unsigned long>(_latestEndFrameTime.msecsTo(endFrameTime));
    _latestEndFrameTime = endFrameTime;
    unsigned long minFrameTime = static_cast<unsigned long>(window->minFrameTime());

    //qDebug() << "[osgQtQuick] RenderThread frameTime:" << frameTime << "/" << minFrameTime;
    if(frameTime < minFrameTime)
        QThread::msleep(minFrameTime - frameTime);

    //std::cout << "          Render Done\n"; std::cout.flush();

    emit renderNextDone();
}

void RenderThread::shutDown()
{
    qDebug() << "[osgQtQuick] RenderThread::shutDown";

    _shutDown = true;

    context->makeCurrent(surface);

    window->deleteFbos();

    context->doneCurrent();

    delete context;
    context = 0;

    // schedule this to be deleted only after we're done cleaning up
    surface->deleteLater();

    // Stop event processing, move the thread to GUI and make sure it is deleted.
    exit();
    moveToThread(QGuiApplication::instance()->thread());
}

}

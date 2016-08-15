#include "renderthread.hpp"
#include "window.hpp"
#include "osgviewer/viewindex.hpp"

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
    if(_shutDown) return;

    context->makeCurrent(surface);

    window->frame();

    QDateTime endFrameTime = QDateTime::currentDateTime();
    unsigned long frameTime = static_cast<unsigned long>(_latestEndFrameTime.msecsTo(endFrameTime));
    _latestEndFrameTime = endFrameTime;
    unsigned long minFrameTime = static_cast<unsigned long>(window->minFrameTime());

    if(frameTime < minFrameTime)
        QThread::msleep(minFrameTime - frameTime);

    emit textureReady();
}

void RenderThread::shutDown()
{
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

void RenderThread::acceptNewSize(osgViewer::ViewQtQuick::Index *view, QSize size)
{
    view->render.size = size;
    view->render.update = view->render.update % 2 + 2;
}

}

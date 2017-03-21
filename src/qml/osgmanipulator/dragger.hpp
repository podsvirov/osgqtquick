#ifndef _OSGMANIPULATOR_DRAGGER_QTQML_
#define _OSGMANIPULATOR_DRAGGER_QTQML_ 1

#include <osg/MatrixTransformQtQml>

#include <QtGui/QMatrix4x4>

namespace osgManipulator {

class Dragger;

class OSGQTQML_EXPORT DraggerQtQml : public osg::MatrixTransformQtQml
{
  Q_OBJECT

  Q_PROPERTY(bool handleEvents READ getHandleEvents WRITE setHandleEvents NOTIFY handleEventsChanged)
  Q_PROPERTY(bool draggerActive READ getDraggerActive WRITE setDraggerActive NOTIFY draggerActiveChanged)

public:
  class Index;

  DraggerQtQml(QObject *parent = 0);
  DraggerQtQml(Index *, QObject *parent = 0);

  void classBegin();

  Q_INVOKABLE bool getHandleEvents() const;
  Q_INVOKABLE void setHandleEvents(bool handleEvents);

  Q_INVOKABLE void addTransformUpdating(osg::MatrixTransformQtQml *transform /*,
                                        int handleCommandMask=DraggerTransformCallback::HANDLE_ALL*/);

  Q_INVOKABLE void removeTransformUpdating(osg::MatrixTransformQtQml *transform);

  Q_INVOKABLE bool getDraggerActive() const;
  Q_INVOKABLE void setDraggerActive(bool draggerActive);

  Q_INVOKABLE void setupDefaultGeometry();

  Dragger* asDragger();

  static DraggerQtQml* fromDragger(Dragger *dragger, QObject *parent = 0);

Q_SIGNALS:
  void handleEventsChanged(bool handleEvents) const;
  void draggerActiveChanged(bool draggerActive) const;
};

}

#endif // _OSGMANIPULATOR_DRAGGER_QTQML_

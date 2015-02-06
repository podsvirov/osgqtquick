#ifndef _OSG_BOX_QTQML_
#define _OSG_BOX_QTQML_ 1

#include <osg/ShapeQtQml>
#include <QVector3D>

namespace osg {

class Box;

class OSGQTQML_EXPORT BoxQtQml : public ShapeQtQml
{
  Q_OBJECT

  Q_PROPERTY(QVector3D halfLengths READ getHalfLengths WRITE setHalfLengths NOTIFY halfLengthsChanged)

public:
  class Index;

  BoxQtQml(QObject *parent = 0);
  BoxQtQml(Index *, QObject *parent = 0);

  void classBegin();

  Q_INVOKABLE QVector3D getHalfLengths() const;
  Q_INVOKABLE void setHalfLengths(const QVector3D &halfLengths);

  Box* box();

  static BoxQtQml* fromBox(Box *box, QObject *parent = 0);

signals:
  void halfLengthsChanged(const QVector3D &halfLengths) const;
};

}

#endif // _OSG_SHAPEDRAWABLE_QTQML_

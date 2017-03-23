#ifndef _OSGTEXT_STYLE_QTQML_
#define _OSGTEXT_STYLE_QTQML_ 1

#include <osg/DrawableQtQml>

#include <osg/ShapeQtQml>

#include <QtGui/QColor>

namespace osgText {

class Style;

class OSGQTQML_EXPORT StyleQtQml : public osg::ObjectQtQml
{
  Q_OBJECT

  //Q_PROPERTY(osgText::StyleQtQml* style READ getStyle WRITE setStyle NOTIFY styleChanged)

  Q_PROPERTY(qreal widthRatio READ getWidthRatio WRITE setWidthRatio NOTIFY widthRatioChanged)

public:
  class Index;

  StyleQtQml(QObject *parent = 0);
  StyleQtQml(Index *, QObject *parent = 0);

  void classBegin();

  //Q_INVOKABLE StyleQtQml *getStyle() const;
  //Q_INVOKABLE void setStyle(StyleQtQml *style);

  Q_INVOKABLE qreal getWidthRatio() const;
  Q_INVOKABLE void setWidthRatio(qreal widthRatio);

  Style* style();

  static StyleQtQml* fromStyle(Style *style, QObject *parent = 0);

Q_SIGNALS:
  //void shapeChanged(ShapeQtQml *shape) const;
  void widthRatioChanged(qreal widthRatio) const;
};

}

#endif // _OSGTEXT_STYLE_QTQML_

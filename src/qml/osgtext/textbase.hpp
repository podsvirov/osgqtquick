#ifndef _OSGTEXT_TEXTBASE_QTQML_
#define _OSGTEXT_TEXTBASE_QTQML_ 1

#include <osg/DrawableQtQml>

#include <osgText/StyleQtQml>

#include <QColor>

namespace osgText {

class TextBase;

class OSGQTQML_EXPORT TextBaseQtQml : public osg::DrawableQtQml
{
  Q_OBJECT

  Q_PROPERTY(osgText::StyleQtQml* style READ getStyle WRITE setStyle NOTIFY styleChanged)
  Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged)
  Q_PROPERTY(QString text READ getText WRITE setText NOTIFY textChanged)
  Q_PROPERTY(qreal characterSize READ getCharacterSize WRITE setCharacterSize NOTIFY characterSizeChanged)
  Q_PROPERTY(AxisAlignment axisAlignment READ getAxisAlignment WRITE setAxisAlignment NOTIFY axisAlignmentChanged)
  Q_PROPERTY(DrawModeMasks drawMode READ getDrawMode WRITE setDrawMode NOTIFY drawModeChanged)

public:
  enum AxisAlignment
  {
      XY_PLANE,
      REVERSED_XY_PLANE,
      XZ_PLANE,
      REVERSED_XZ_PLANE,
      YZ_PLANE,
      REVERSED_YZ_PLANE,
      SCREEN,
      USER_DEFINED_ROTATION
  };

  Q_ENUMS(AxisAlignment)

  enum DrawModeMask
  {
      TEXT              = 1,
      BOUNDINGBOX       = 2,
      FILLEDBOUNDINGBOX = 4,
      ALIGNMENT         = 8
  };

  Q_DECLARE_FLAGS(DrawModeMasks, DrawModeMask)
  Q_FLAGS(DrawModeMasks)
  Q_ENUMS(DrawModeMask)

public:
  class Index;

  TextBaseQtQml(QObject *parent = 0);
  TextBaseQtQml(Index *, QObject *parent = 0);

  void classBegin();

  Q_INVOKABLE StyleQtQml *getStyle() const;
  Q_INVOKABLE void setStyle(StyleQtQml *style);

  Q_INVOKABLE QColor getColor() const;
  Q_INVOKABLE void setColor(const QColor &color);

  Q_INVOKABLE QString getText() const;
  Q_INVOKABLE void setText(const QString &text);

  Q_INVOKABLE qreal getCharacterSize() const;
  Q_INVOKABLE void setCharacterSize(qreal size);

  Q_INVOKABLE AxisAlignment getAxisAlignment() const;
  Q_INVOKABLE void setAxisAlignment(AxisAlignment axisAlignment);

  Q_INVOKABLE DrawModeMasks getDrawMode() const;
  Q_INVOKABLE void setDrawMode(DrawModeMasks drawMode);

  TextBase* textBase();

  static TextBaseQtQml* fromTextBase(TextBase *textBase, QObject *parent = 0);

signals:
  void styleChanged(StyleQtQml *shape) const;
  void colorChanged(const QColor &color) const;
  void textChanged(const QString &text) const;
  void characterSizeChanged(qreal size) const;
  void axisAlignmentChanged(AxisAlignment axisAlignment) const;
  void drawModeChanged(DrawModeMasks drawMode) const;
};

}

Q_DECLARE_OPERATORS_FOR_FLAGS(osgText::TextBaseQtQml::DrawModeMasks)

#endif // _OSGTEXT_TEXTBASE_QTQML_

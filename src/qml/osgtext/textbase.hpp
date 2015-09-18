#ifndef _OSGTEXT_TEXTBASE_QTQML_
#define _OSGTEXT_TEXTBASE_QTQML_ 1

#include <osg/DrawableQtQml>

#include <osg/ShapeQtQml>

#include <QColor>

namespace osgText {

class TextBase;

class OSGQTQML_EXPORT TextBaseQtQml : public osg::DrawableQtQml
{
  Q_OBJECT

  //Q_PROPERTY(osgText::StyleQtQml* style READ getStyle WRITE setStyle NOTIFY styleChanged)
  Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged)
  Q_PROPERTY(QString text READ getText WRITE setText NOTIFY textChanged)
  Q_PROPERTY(qreal characterSize READ getCharacterSize WRITE setCharacterSize NOTIFY characterSizeChanged)

public:
  class Index;

  TextBaseQtQml(QObject *parent = 0);
  TextBaseQtQml(Index *, QObject *parent = 0);

  void classBegin();

  //Q_INVOKABLE StyleQtQml *getStyle() const;
  //Q_INVOKABLE void setStyle(StyleQtQml *style);

  Q_INVOKABLE QColor getColor() const;
  Q_INVOKABLE void setColor(const QColor &color);

  Q_INVOKABLE QString getText() const;
  Q_INVOKABLE void setText(const QString &text);

  Q_INVOKABLE qreal getCharacterSize() const;
  Q_INVOKABLE void setCharacterSize(qreal size);

  TextBase* textBase();

  static TextBaseQtQml* fromTextBase(TextBase *textBase, QObject *parent = 0);

signals:
  //void shapeChanged(ShapeQtQml *shape) const;
  void colorChanged(const QColor &color) const;
  void textChanged(const QString &text) const;
  void characterSizeChanged(qreal size) const;
};

}

#endif // _OSGTEXT_TEXTBASE_QTQML_

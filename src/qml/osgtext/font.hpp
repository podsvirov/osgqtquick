#ifndef _OSGTEXT_FONT_QTQML_
#define _OSGTEXT_FONT_QTQML_ 1

#include <osg/ObjectQtQml>

#include <osgText/FontImplementationQtQml>

namespace osgText {

class Font;

class OSGQTQML_EXPORT FontQtQml: public osg::ObjectQtQml
{
  Q_OBJECT

  Q_PROPERTY(osgText::FontImplementationQtQml* implementation READ getImplementation WRITE setImplementation NOTIFY implementationChanged)
  Q_PROPERTY(qreal glyphImageMarginRatio READ getGlyphImageMarginRatio WRITE setGlyphImageMarginRatio NOTIFY glyphImageMarginRatioChanged)

public:
  class Index;

  FontQtQml(QObject *parent = 0);
  FontQtQml(Index *, QObject *parent = 0);

  void classBegin();

  Q_INVOKABLE FontImplementationQtQml *getImplementation() const;
  Q_INVOKABLE void setImplementation(FontImplementationQtQml *implementation);

  Q_INVOKABLE qreal getGlyphImageMarginRatio() const;
  Q_INVOKABLE void setGlyphImageMarginRatio(qreal widthRatio);

  Font* font();

  static FontQtQml* fromFont(Font *font, QObject *parent = 0);

signals:
  void implementationChanged(FontImplementationQtQml *implementation) const;
  void glyphImageMarginRatioChanged(qreal widthRatio) const;
};

}

#endif // _OSGTEXT_FONT_QTQML_

#ifndef _OSGTEXT_FONT_QTQML_
#define _OSGTEXT_FONT_QTQML_ 1

#include <osg/Version>

#include <osg/ObjectQtQml>

#include <osgText/FontImplementationQtQml>

namespace osgText {

class Font;

class OSGQTQML_EXPORT FontQtQml: public osg::ObjectQtQml
{
  Q_OBJECT

  Q_PROPERTY(osgText::FontImplementationQtQml* implementation READ getImplementation WRITE setImplementation NOTIFY implementationChanged)
#if OSG_VERSION_LESS_THAN(3, 6, 0)
  Q_PROPERTY(qreal glyphImageMarginRatio READ getGlyphImageMarginRatio WRITE setGlyphImageMarginRatio NOTIFY glyphImageMarginRatioChanged)
#endif // OSG_VERSION_LESS_THAN(3, 6, 0)

public:
  class Index;

  FontQtQml(QObject *parent = 0);
  FontQtQml(Index *, QObject *parent = 0);

  void classBegin();

  Q_INVOKABLE FontImplementationQtQml *getImplementation();
  Q_INVOKABLE void setImplementation(FontImplementationQtQml *implementation);

#if OSG_VERSION_LESS_THAN(3, 6, 0)
  Q_INVOKABLE qreal getGlyphImageMarginRatio() const;
  Q_INVOKABLE void setGlyphImageMarginRatio(qreal widthRatio);
#endif // OSG_VERSION_LESS_THAN(3, 6, 0)

  Font* font();

  static FontQtQml* fromFont(Font *font, QObject *parent = 0);

Q_SIGNALS:
  void implementationChanged(FontImplementationQtQml *implementation) const;
#if OSG_VERSION_LESS_THAN(3, 6, 0)
  void glyphImageMarginRatioChanged(qreal widthRatio) const;
#endif // OSG_VERSION_LESS_THAN(3, 6, 0)
};

}

#endif // _OSGTEXT_FONT_QTQML_

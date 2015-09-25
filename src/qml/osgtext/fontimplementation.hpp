#ifndef _OSGTEXT_FONTIMPLEMENTATION_QTQML_
#define _OSGTEXT_FONTIMPLEMENTATION_QTQML_ 1

#include <osgQtQml/Object>

#include <osgText/Font>

namespace osgText {

class OSGQTQML_EXPORT FontImplementationQtQml: public osgQtQml::Object
{
  Q_OBJECT

public:
  class Index;

  FontImplementationQtQml(QObject *parent = 0);
  FontImplementationQtQml(Index *, QObject *parent = 0);

  void classBegin();

  Font::FontImplementation* fontImplementation();

  static FontImplementationQtQml* fromFontImplementation(Font::FontImplementation *implementation, QObject *parent = 0);
};

}

#endif // _OSGTEXT_FONTIMPLEMENTATION_QTQML_

#ifndef _OSGQT_QFONTIMPLEMENTATION_QTQML_
#define _OSGQT_QFONTIMPLEMENTATION_QTQML_ 1

#include <osgText/FontImplementationQtQml>

#include <QtGui/QFont>

namespace osgQt {

class QFontImplementation;

class OSGQTQML_EXPORT QFontImplementationQtQml: public osgText::FontImplementationQtQml
{
  Q_OBJECT

  Q_PROPERTY(QFont font READ getFont WRITE setFont NOTIFY fontChanged)

public:
  class Index;

  QFontImplementationQtQml(QObject *parent = 0);
  QFontImplementationQtQml(Index *, QObject *parent = 0);

  void classBegin();

  Q_INVOKABLE QFont getFont() const;
  Q_INVOKABLE void setFont(const QFont &font);

  QFontImplementation* qFontImplementation();

  static QFontImplementationQtQml* fromQFontImplementation(QFontImplementation *implementation, QObject *parent = 0);

Q_SIGNALS:
  void fontChanged(const QFont &font) const;
};

}

#endif // _OSGQT_QFONTIMPLEMENTATION_QTQML_

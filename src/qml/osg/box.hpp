#ifndef _OSG_BOX_QTQML_
#define _OSG_BOX_QTQML_ 1

#include <osg/ShapeQtQml>

namespace osg {

class Box;

class OSGQTQML_EXPORT BoxQtQml : public ShapeQtQml
{
  Q_OBJECT

public:
  class Index;

  BoxQtQml(QObject *parent = 0);
  BoxQtQml(Index *, QObject *parent = 0);

  void classBegin();

  Box* box();

  static BoxQtQml* fromBox(Box *box, QObject *parent = 0);
};

}

#endif // _OSG_SHAPEDRAWABLE_QTQML_

#ifndef _OSG_GRAPHICSCONTEXT_QTQML_
#define _OSG_GRAPHICSCONTEXT_QTQML_ 1

#include <osg/ObjectQtQml>

namespace osg {

class GraphicsContext;

class OSGQTQML_EXPORT GraphicsContextQtQml : public osg::ObjectQtQml
{
  Q_OBJECT

public:
  class Index;

  GraphicsContextQtQml(QObject *parent = 0);
  GraphicsContextQtQml(Index *index, QObject *parent = 0);

  void classBegin();

  GraphicsContext* graphicsContext();

  static GraphicsContextQtQml* fromGraphicsContext(GraphicsContext *graphicsContext, QObject *parent = 0);
};

}

#endif // _OSG_GRAPHICSCONTEXT_QTQML_

#ifndef _OSGVIEWER_COMPOSITEVIEWER_QTQML_
#define _OSGVIEWER_COMPOSITEVIEWER_QTQML_ 1

#include <osg/ObjectQtQml>

namespace osgViewer {

class CompositeViewer;

class OSGQTQML_EXPORT CompositeViewerQtQml : public osg::ObjectQtQml
{
  Q_OBJECT

public:
  class Index;

  CompositeViewerQtQml(QObject *parent = 0);
  CompositeViewerQtQml(Index *index, QObject *parent = 0);

  void classBegin();

  CompositeViewer* compositeViewer();

  static CompositeViewerQtQml* fromCompositeViewer(CompositeViewer *compositeViewer, QObject *parent = 0);
};

}

#endif // _OSGVIEWER_COMPOSITEVIEWER_QTQML_

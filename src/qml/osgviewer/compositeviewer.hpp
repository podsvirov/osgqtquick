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

protected:
  template<typename T>
  typename T::Index::OType* o(T *p);

  template<typename T>
  const typename T::Index::OType* o(const T *p) const;
};

template<typename T>
inline typename T::Index::OType* CompositeViewerQtQml::o(T *p)
{
    return static_cast<typename T::Index::OType*>(i(p)->o_ptr);
}

template<typename T>
inline const typename T::Index::OType* CompositeViewerQtQml::o(const T *p) const
{
    return static_cast<typename T::Index::OType*>(i(p)->o_ptr);
}

}

#endif // _OSGVIEWER_COMPOSITEVIEWER_QTQML_

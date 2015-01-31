#ifndef _OSG_TRANSFORM_QTQML_
#define _OSG_TRANSFORM_QTQML_ 1

#include <osg/GroupQtQml>

namespace osg {

class Transform;

class OSGQTQML_EXPORT TransformQtQml : public GroupQtQml
{
  Q_OBJECT

public:
  class Index;

  TransformQtQml(QObject *parent = 0);
  TransformQtQml(Index *, QObject *parent = 0);

  void classBegin();

  Transform* transform();

  static TransformQtQml* fromTransform(Transform *transform, QObject *parent = 0);
};

}

#endif // _OSG_TRANSFORM_QTQML_

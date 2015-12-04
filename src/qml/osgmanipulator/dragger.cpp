#include "dragger.hpp"
#include "draggerindex.hpp"

#include <osgManipulator/Dragger>

#include <QDebug>

/*!
   \qmltype Dragger
   \inherits osg::MatrixTransform
   \inqmlmodule osgManipulator
   \brief Base type for draggers
 */

namespace osgManipulator {

DraggerQtQml::Index::Index(Dragger *dragger) :
    MatrixTransformQtQml::Index(dragger)
{
}

DraggerQtQml::DraggerQtQml(QObject *parent) :
  MatrixTransformQtQml(parent)
{
}

DraggerQtQml::DraggerQtQml(DraggerQtQml::Index *index, QObject *parent) :
  MatrixTransformQtQml(index, parent)
{
}

void DraggerQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    MatrixTransformQtQml::classBegin();
}

/*!
   \qmlproperty bool osgManipulator::Dragger::draggerActive

   Dragger active
 */

bool DraggerQtQml::getDraggerActive() const
{
    return o(this)->getDraggerActive();
}

void DraggerQtQml::setDraggerActive(bool draggerActive)
{
    if(draggerActive == getDraggerActive()) return;

    o(this)->setDraggerActive(draggerActive);

    emit draggerActiveChanged(draggerActive);
}

void DraggerQtQml::setupDefaultGeometry()
{
    o(this)->setupDefaultGeometry();
}

Dragger *DraggerQtQml::asDragger()
{
    return o(this);
}

DraggerQtQml *DraggerQtQml::fromDragger(Dragger *dragger, QObject *parent)
{
    if(!dragger) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(dragger))
    {
        return static_cast<DraggerQtQml*>(index->qtObject());
    }

    DraggerQtQml *result = new DraggerQtQml(new Index(dragger), parent);
    result->classBegin();
    result->componentComplete();
    return result;
}

}

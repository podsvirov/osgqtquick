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
   \qmlproperty bool osgManipulator::Dragger::handleEvents

   Handle events
 */

bool DraggerQtQml::getHandleEvents() const
{
    return o(this)->getHandleEvents();
}

void DraggerQtQml::setHandleEvents(bool handleEvents)
{
    if(handleEvents == getHandleEvents()) return;

    o(this)->setHandleEvents(handleEvents);

    emit handleEventsChanged(handleEvents);
}

/*!
   \qmlmethod void osgManipulator::Dragger::addTransformUpdating(osg::MatrixTransform transform)

   Add \a transform updating
 */

void DraggerQtQml::addTransformUpdating(osg::MatrixTransformQtQml *transform)
{
    o(this)->addTransformUpdating(transform->asMatrixTransform());
}

/*!
   \qmlmethod void osgManipulator::Dragger::removeTransformUpdating(osg::MatrixTransform transform)

   Remove \a transform updating
 */

void DraggerQtQml::removeTransformUpdating(osg::MatrixTransformQtQml *transform)
{
    o(this)->removeTransformUpdating(transform->asMatrixTransform());
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

/*!
   \qmlmethod void osgManipulator::Dragger::setupDefaultGeometry()

   Setup default geometry for dragger
 */

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

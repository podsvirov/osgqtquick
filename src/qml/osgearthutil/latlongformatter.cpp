#include "latlongformatter.hpp"

#include "../index.hpp"
#include <osgEarth/SpatialReference>

using namespace osgEarth::Util;

LatLongFormatterQtQml::LatLongFormatterQtQml(QObject* parent)
    : QObject(parent)
    , _llf(LatLongFormatter::FORMAT_DEGREES_MINUTES_SECONDS_TERSE, LatLongFormatter::USE_COLONS | LatLongFormatter::USE_PREFIXES)
{
}

QString LatLongFormatterQtQml::format(QGeoCoordinate pos)
{
    return QString::fromStdString(_llf.format(GeoPoint(SpatialReference::get("wgs84"), osgQt::vec3d(pos))));
}

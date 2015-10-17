#ifndef _OSGQTQML_INDEX_
#define _OSGQTQML_INDEX_ 1

#include <osgQtQml/Export>

#include <osg/Object>
#include <osg/Vec4>
#include <osg/Vec3d>
#include <osg/Quat>
#include <osgText/String>

#include <QObject>
#include <QPointer>
#include <QColor>
#include <QVector3D>
#include <QQuaternion>

#include <list>
#include <set>

namespace osgQt {

inline osg::Vec4 swapColor(const QColor& color)
{
    return osg::Vec4(color.redF(),
                     color.greenF(),
                     color.blueF(),
                     color.alphaF());
}

inline QColor swapColor(const osg::Vec4& color)
{
    return QColor::fromRgbF(color.r(),
                            color.g(),
                            color.b(),
                            color.a());
}

inline osg::Vec3d vec3d(const QVector3D& v)
{
    return osg::Vec3d(static_cast<osg::Vec3d::value_type>(v.x()),
                      static_cast<osg::Vec3d::value_type>(v.y()),
                      static_cast<osg::Vec3d::value_type>(v.z()));
}

inline QVector3D qVector3D(const osg::Vec3d& v)
{
    return QVector3D(static_cast<float>(v.x()),
                     static_cast<float>(v.y()),
                     static_cast<float>(v.z()));
}

inline osg::Quat quat(const QQuaternion& q)
{
    return osg::Quat(static_cast<osg::Quat::value_type>(q.x()),
                     static_cast<osg::Quat::value_type>(q.y()),
                     static_cast<osg::Quat::value_type>(q.z()),
                     static_cast<osg::Quat::value_type>(q.scalar()));
}

inline QQuaternion qQuaternion(const osg::Quat& q)
{
    return QQuaternion(static_cast<float>(q.w()),
                       static_cast<float>(q.x()),
                       static_cast<float>(q.y()),
                       static_cast<float>(q.z()));
}

inline osgText::String swapString(const QString& string)
{
    return osgText::String(string.toStdString(),
                           osgText::String::ENCODING_UTF8);
}

inline QString swapString(const osgText::String& string)
{
    return QString::fromStdString(string.createUTF8EncodedString());
}

}

namespace osgQtQuick {

class Object;

}

namespace osgQtQml {

class Index;
class Object;

typedef Index* (*qtMakeIndex) (QObject*);
typedef Index* (*osgMakeIndex)  (osg::Object*);

struct OSGQTQML_EXPORT Storage {
    std::set<qtMakeIndex> qtMakers;
    std::set<osgMakeIndex> osgMakers;
    std::map<QObject*, Index*> qtIndexes;
    std::map<osg::Referenced*, Index*> osgIndexes;
};

class OSGQTQML_EXPORT Index
{
public:
    typedef osg::Referenced OType;
    typedef QObject QType;

public:
    Index(osg::Referenced *o_ptr = 0);
    virtual ~Index();

public: // methods
    QObject *qtObject();
    osg::Referenced *osgReferenced();

    bool isBegin() const;
    bool isComplete() const;

    virtual void classBegin();
    virtual void componentComplete();

public: // static methods
    static Index *checkIndex(osg::Referenced *o_ptr);
    static Index *checkIndex(QObject *o_ptr);

    static Index *fromObject(osg::Object *o_ptr);
    static Index *fromObject(QObject *o_ptr);

    static bool insertMake(osgMakeIndex make);
    static bool eraseMake(osgMakeIndex make);

    static bool insertMake(qtMakeIndex make);
    static bool eraseMake(qtMakeIndex make);

protected:
    template<typename T>
    typename T::OType* o(T *p);

    template<typename T>
    typename T::QType* q(T *p);

    void setQ(QObject *q);
    void setO(osg::Referenced *o);

private:
    friend class ::osgQtQml::Object;
    friend class ::osgQtQuick::Object;

    bool is_begin;
    bool is_complete;

    osg::ref_ptr<osg::Referenced> o_ptr;
    QPointer<QObject> q_ptr;

    static Storage storage;
};

inline QObject *Index::qtObject()
{
    return q_ptr.data();
}

inline osg::Referenced *Index::osgReferenced()
{
    return o_ptr.get();
}

inline bool Index::isBegin() const
{
    return is_begin;
}

inline bool Index::isComplete() const
{
    return is_complete;
}

template<typename T>
inline typename T::OType* Index::o(T *p)
{
    return static_cast<typename T::OType*>(p->o_ptr.get());
}

template<typename T>
inline typename T::QType* Index::q(T *p)
{
    return static_cast<typename T::QType*>(p->q_ptr.data());
}

inline void Index::setQ(QObject *q)
{
    q_ptr = q;
}

inline void Index::setO(osg::Referenced *o)
{
    o_ptr = o;
}

}

#endif // _OSGQTQML_INDEX_

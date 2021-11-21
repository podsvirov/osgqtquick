# osgQtQuick - OpenSceneGraph QML Modules

[![msys2](https://github.com/podsvirov/osgqtquick/workflows/msys2/badge.svg?branch=develop)](https://github.com/podsvirov/osgqtquick/actions?query=workflow%3Amsys2+branch%3Adevelop)

![Hello from osgQtQuick 2.0!](https://github.com/podsvirov/osgqtquick/blob/gh-repos/images/text3d.png)

Intergation [OpenSceneGraph](http://openscenegraph.org) to [Qt Quick](http://doc.qt.io/qt-5/qtquick-index.html).

## Reference Documentation

Please visit documentation [pages](https://podsvirov.github.io/osgqtquick).
 
## Source Code

Actual development code avaliable in [develop](https://github.com/podsvirov/osgqtquick/tree/develop) branch.

## Prebuilt Binaries

#### MSYS2 Project

Now it's distributed as [package](https://packages.msys2.org/base/mingw-w64-osgQtQuick-git)
of [MSYS2](https://www.msys2.org) distro.
Type in the appropriate shell:

    pacman -S mingw-w64-i686-osgQtQuick

or

    pacman -S mingw-w64-x86_64-osgQtQuick
    
or

    pacman -S mingw-w64-ucrt-x86_64-osgQtQuick

## Dependencies

* Qt >= 5.0.0
* OpenSceneGraph >= 3.3.2

## Threaded Rendering

The osgQtQuick is now support all QtQuick render loop types.
But if your application has problems on startup or resize the window,
try to set a environment variable "QSG_RENDER_LOOP" to the value of "basic", "windows" or "threaded".

## Related Links

* The wiki [pages](https://github.com/podsvirov/osgqtquick/wiki/osgQtQuick-2.0).
* The library [page](http://inqlude.org/libraries/osgqtquick.html) at [inqlude](http://inqlude.org/) project.
* The discussion [thread](http://forum.qt.io/topic/58737) at Qt [forum](http://forum.qt.io).

## Similar Projects

* [qmlosg](https://github.com/rickyviking/qmlosg) - Integration test of osg and qt quick + qml framework
* [QtQuick2OSGItem](https://bitbucket.org/leon_manukyan/qtquick2osgitem) - small package allowing to embed OpenSceneGraph scenes as visual items in Qt Quick 2 applications

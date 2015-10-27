#include "index.hpp"

#include <osgGA/GUIEventAdapter>

namespace osgQt {

// For more info see ${OSG_ROOT}/src/osgQt/GraphicsWindowQt.cpp
std::map<unsigned int, int> keyMap = {
    { Qt::Key_Escape        , osgGA::GUIEventAdapter::KEY_Escape      },
    { Qt::Key_Delete        , osgGA::GUIEventAdapter::KEY_Delete      },
    { Qt::Key_Home          , osgGA::GUIEventAdapter::KEY_Home        },
    { Qt::Key_Enter         , osgGA::GUIEventAdapter::KEY_KP_Enter    },
    { Qt::Key_End           , osgGA::GUIEventAdapter::KEY_End         },
    { Qt::Key_Return        , osgGA::GUIEventAdapter::KEY_Return      },
    { Qt::Key_PageUp        , osgGA::GUIEventAdapter::KEY_Page_Up     },
    { Qt::Key_PageDown      , osgGA::GUIEventAdapter::KEY_Page_Down   },
    { Qt::Key_Left          , osgGA::GUIEventAdapter::KEY_Left        },
    { Qt::Key_Right         , osgGA::GUIEventAdapter::KEY_Right       },
    { Qt::Key_Up            , osgGA::GUIEventAdapter::KEY_Up          },
    { Qt::Key_Down          , osgGA::GUIEventAdapter::KEY_Down        },
    { Qt::Key_Backspace     , osgGA::GUIEventAdapter::KEY_BackSpace   },
    { Qt::Key_Tab           , osgGA::GUIEventAdapter::KEY_Tab         },
    { Qt::Key_Space         , osgGA::GUIEventAdapter::KEY_Space       },
    { Qt::Key_Delete        , osgGA::GUIEventAdapter::KEY_Delete      },
    { Qt::Key_Alt           , osgGA::GUIEventAdapter::KEY_Alt_L       },
    { Qt::Key_Shift         , osgGA::GUIEventAdapter::KEY_Shift_L     },
    { Qt::Key_Control       , osgGA::GUIEventAdapter::KEY_Control_L   },
    { Qt::Key_Meta          , osgGA::GUIEventAdapter::KEY_Meta_L      },

    { Qt::Key_F1            , osgGA::GUIEventAdapter::KEY_F1          },
    { Qt::Key_F2            , osgGA::GUIEventAdapter::KEY_F2          },
    { Qt::Key_F3            , osgGA::GUIEventAdapter::KEY_F3          },
    { Qt::Key_F4            , osgGA::GUIEventAdapter::KEY_F4          },
    { Qt::Key_F5            , osgGA::GUIEventAdapter::KEY_F5          },
    { Qt::Key_F6            , osgGA::GUIEventAdapter::KEY_F6          },
    { Qt::Key_F7            , osgGA::GUIEventAdapter::KEY_F7          },
    { Qt::Key_F8            , osgGA::GUIEventAdapter::KEY_F8          },
    { Qt::Key_F9            , osgGA::GUIEventAdapter::KEY_F9          },
    { Qt::Key_F10           , osgGA::GUIEventAdapter::KEY_F10         },
    { Qt::Key_F11           , osgGA::GUIEventAdapter::KEY_F11         },
    { Qt::Key_F12           , osgGA::GUIEventAdapter::KEY_F12         },
    { Qt::Key_F13           , osgGA::GUIEventAdapter::KEY_F13         },
    { Qt::Key_F14           , osgGA::GUIEventAdapter::KEY_F14         },
    { Qt::Key_F15           , osgGA::GUIEventAdapter::KEY_F15         },
    { Qt::Key_F16           , osgGA::GUIEventAdapter::KEY_F16         },
    { Qt::Key_F17           , osgGA::GUIEventAdapter::KEY_F17         },
    { Qt::Key_F18           , osgGA::GUIEventAdapter::KEY_F18         },
    { Qt::Key_F19           , osgGA::GUIEventAdapter::KEY_F19         },
    { Qt::Key_F20           , osgGA::GUIEventAdapter::KEY_F20         },

    { Qt::Key_hyphen        , '-'                                     },
    { Qt::Key_Equal         , '='                                     },

    { Qt::Key_division      , osgGA::GUIEventAdapter::KEY_KP_Divide   },
    { Qt::Key_multiply      , osgGA::GUIEventAdapter::KEY_KP_Multiply },
    { Qt::Key_Minus         , '-'                                     },
    { Qt::Key_Plus          , '+'                                     },
    //{ Qt::Key_H             , osgGA::GUIEventAdapter::KEY_KP_Home     },
    //{ Qt::Key_              , osgGA::GUIEventAdapter::KEY_KP_Up       },
    //{ 92                    , osgGA::GUIEventAdapter::KEY_KP_Page_Up  },
    //{ 86                    , osgGA::GUIEventAdapter::KEY_KP_Left     },
    //{ 87                    , osgGA::GUIEventAdapter::KEY_KP_Begin    },
    //{ 88                    , osgGA::GUIEventAdapter::KEY_KP_Right    },
    //{ 83                    , osgGA::GUIEventAdapter::KEY_KP_End      },
    //{ 84                    , osgGA::GUIEventAdapter::KEY_KP_Down     },
    //{ 85                    , osgGA::GUIEventAdapter::KEY_KP_Page_Down},
    { Qt::Key_Insert        , osgGA::GUIEventAdapter::KEY_KP_Insert   }
    //{ Qt::Key_Delete        , osgGA::GUIEventAdapter::KEY_KP_Delete   }
};

}

namespace osgQtQuick {

Storage Index::storage = Storage();

Index::Index(osg::Object *object) :
    osgQtQml::Index(object),
    o_ptr(0)
{
}

Index::~Index()
{

}

void Index::classBegin()
{
    osgQtQml::Index::classBegin();
}

} // namespace osgQtQuick


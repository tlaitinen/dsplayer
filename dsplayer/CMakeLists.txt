FIND_PACKAGE(Qt5Widgets)
FIND_PACKAGE(Qt5WebKitWidgets)
include_directories(${libdsinterface_include} ${libutil_include})
SET(dsplayer_SOURCES src/main.cpp src/mainwindow.cpp)
SET(dsplayer_HEADERS src/mainwindow.h)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC ON)
ADD_EXECUTABLE(dsplayer ${dsplayer_SOURCES} 
              ${dsplayer_HEADERS_MOC})
qt5_use_modules(dsplayer WebKit Widgets WebKitWidgets)
TARGET_LINK_LIBRARIES(dsplayer ${Qt5Widgets_LIBRARIES} dsinterface util-ar)
install(TARGETS dsplayer ${INSTALL_OPTS})    


QT +=  webkitwidgets 
LIBS +=  -ldsinterface  -lprotobuf -lrt

TEMPLATE = app
TARGET = 
DEPENDPATH += .

# Input
HEADERS += mainwindow.h  
SOURCES += main.cpp mainwindow.cpp 


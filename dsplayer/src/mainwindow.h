/*
Copyright (C) 2013 Tero Laitinen

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/
 #ifndef MAINWINDOW_H
 #define MAINWINDOW_H

 #include <QMainWindow>
 #include <QtWebKitWidgets/QWebView>
 #include <QtWebKitWidgets/QWebFrame>


#include <QTimer>
#include <vector>
#include "util.hpp"
#include "dsserver.hpp"
class QAction;
 class QMenu;

class JSInterface : public QObject {
     Q_OBJECT

    bool readyFlag;
public:
    JSInterface() : readyFlag(false) {}
    Q_INVOKABLE void log(QString s) {
    std::cerr << s.toUtf8().constData() << std::endl;

    }
    Q_INVOKABLE void ready() {
        std::cerr << "ready!" << std::endl;
        readyFlag = true;
    }
    bool isReady() const {
        return readyFlag;
    }


};
 class MyWebView : public QWebView {
     Q_OBJECT
        
         
     void keyPressEvent (QKeyEvent *);
     
     JSInterface jsInterface;
 public:
     MyWebView() : QWebView(), defsUpdated(0) {
     }
     time_t defsUpdated;
     bool isReady() const {
         return jsInterface.isReady();
     }
     void loadContent() {
          load(QString::fromStdString("http://localhost/ds/"));
          //webView->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
          page()->mainFrame()->setScrollBarPolicy( Qt::Vertical, Qt::ScrollBarAlwaysOff );
          page()->mainFrame()->setScrollBarPolicy( Qt::Horizontal, Qt::ScrollBarAlwaysOff );
          page()->mainFrame()->addToJavaScriptWindowObject("dsplayer", &jsInterface);
     }
 };

 class MainWindow : public QMainWindow
 {
     Q_OBJECT

 public:
     MainWindow();

 private:
     ds::Server server;
     std::vector<MyWebView*> webViews;
     QTimer* timer;
    
 private slots:
     void timerCb();
 };

 #endif

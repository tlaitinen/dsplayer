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
#include <QtWidgets>
#include <iostream>
#include <QtWebKit/QWebElement>
#include <qfile.h>
#include <qtextstream.h>
#include "mainwindow.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
static QString loadFile(const QString& path) {
     QFile file(path);
     if (!file.open(QIODevice::ReadOnly))
         return "";
     QTextStream stream(&file);
     QString string = stream.readAll();;
     file.close();
     return string;
}
 MainWindow::MainWindow()

     {
        setContentsMargins(0,0,0,0);
     layout()->setContentsMargins(0,0,0,0);
    
      showFullScreen();
      QApplication::setOverrideCursor(QCursor(Qt::BlankCursor));

      for (int i = 0; i < QApplication::desktop()->screenCount(); i++) {
          QRect res = QApplication::desktop()->screenGeometry(i);

          MyWebView* webView = new MyWebView();
          webView->move(QPoint(res.x(), res.y()));
          webView->resize(res.width(), res.height());
          webView->loadContent();
          webView->showFullScreen();
          webViews.push_back(webView);
          std::cerr << "Webview on screen " << i << std::endl;
      }
    //setCentralWidget(webView);
 //layout()->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
// layout()->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerCb()));
    timer->start(100);
 }

void MyWebView::keyPressEvent (QKeyEvent *e) {
    switch(e->key())  {
            case Qt::Key_Escape:
                close();
            break;
    }
}
void MainWindow::timerCb() {
    bool closed = false;
    for (size_t i = 0; i < webViews.size(); i++) {
        if (webViews[i]->isVisible() == false) {
            closed = true;
            break;
        }
        std::string path = "/mnt/hd/ds/screen" + util::toString(i) + ".js";
        struct stat buf;
        stat(path.c_str(), &buf);
        if (buf.st_mtime != webViews[i]->defsUpdated && webViews[i]->isReady()) {
            webViews[i]->defsUpdated = buf.st_mtime;
            try {
                std::cerr << "Running JS on screen " << i << " : " << path << std::endl;
                std::string js = util::readFile(path);
                webViews[i]->page()->mainFrame()->evaluateJavaScript(QString::fromStdString(js));
            } catch (util::Except e) {
                std::cerr << "Could not load file " << path << std::endl;
            }
        }

    }
    if (closed) {
        for (size_t i = 0; i < webViews.size(); i++) {
            webViews[i]->close();
        }
        close();
    }

    server.check();
    if (server.hasRequest()) {
        ds::Request req;
        server.getRequest(req);
        if (req.has_set_template()) {
            const ds::SetTemplate& st = req.set_template();
            if (st.screen() >= 0 && st.screen() < webViews.size()) {
                webViews[st.screen()]->setHtml(loadFile(st.path().c_str()));
            }
        } else if (req.has_update_screen()) {
            const ds::UpdateScreen& us= req.update_screen();

        if (us.screen() >= 0 && us.screen() < webViews.size()) {
	        std::cerr << "Updating element " << us.container() << " with " << us.path() << std::endl;		

            QWebElement e = webViews[us.screen()]->page()->mainFrame()->findFirstElement(us.container().c_str());

            std::cerr << "isNull() : " << e.isNull() << std::endl;
            QString content = loadFile(us.path().c_str());
            e.setInnerXml(content);
        }


        } else if (req.has_evaluate()) {
            const ds::Evaluate& e = req.evaluate();
            if (e.screen() >= 0 && e.screen() < webViews.size()) {
                std::cerr << "Evaluating: " << e.js() << std::endl;

                webViews[e.screen()]->settings()->clearMemoryCaches();
                webViews[e.screen()]->page()->mainFrame()->evaluateJavaScript(QString::fromStdString(e.js()));
            }
        }
    }
}

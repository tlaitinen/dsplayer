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
 #include "mainwindow.h"

 int main(int argc, char * argv[])
 {
     QApplication app(argc, argv);
     QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);
     MainWindow mainWindow;
     mainWindow.setFocus();
     mainWindow.show();

     return app.exec();
 }

#The MIT License (MIT)

#Copyright © 2021-2022 Antonio Dias

#Permission is hereby granted, free of charge, to any person obtaining a copy
#of this software and associated documentation files (the "Software"), to deal
#in the Software without restriction, including without limitation the rights
#to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#copies of the Software, and to permit persons to whom the Software is
#furnished to do so, subject to the following conditions:

#The above copyright notice and this permission notice shall be included in all
#copies or substantial portions of the Software.

#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#SOFTWARE.

QT += core gui widgets serialport

CONFIG += c++11

#CONFIG += no_qgoodwindow #This flag disable QGoodWindow

include($$PWD/../../QGoodWindow/QGoodWindow.pri)

include($$PWD/../../QGoodCentralWidget/QGoodCentralWidget.pri)

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    msg_processer.cpp

HEADERS += \
    mainwindow.h \
    msg_processer.h

FORMS += \
    centralwidget.ui

RC_ICONS=kj_logo.ico

RESOURCES += \
    images.qrc

TRANSLATIONS = translations/en_US.ts translations/zh_CN.ts


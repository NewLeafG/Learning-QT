/*
The MIT License (MIT)

Copyright © 2022 Antonio Dias

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef QGOODCENTRALWIDGET_H
#define QGOODCENTRALWIDGET_H

#include <QGoodWindow>

#ifdef QGOODWINDOW
#include "titlebar.h"
#endif

/** **QGoodCentralWidget** class contains the public API's to control the behavior of **QGoodWindow**. */
class QGoodCentralWidget : public QWidget
{
    Q_OBJECT
public:
    /** Constructor of *QGoodCentralWidget*, is mandatory pass a valid instance of the parent *QGoodWindow*. */
    explicit QGoodCentralWidget(QGoodWindow *gw);
    /** Destructor of *QGoodCentralWidget*. */
    ~QGoodCentralWidget();


    /** Utility for showing a modal *QDialog* with customized title bar and borders.
        Pass the *QDialog* and the parent *QGoodWindow* and optionally a *QGoodCentralWidget* for mimic
        it's colors on the new window. Optionally pass a left title bar widget,
        a right title bar widget and set the visibility
        of title and icon on the new window. */
    static int execDialogWithWindow(QDialog *dialog, QGoodWindow *parent_gw,
                                    QGoodCentralWidget *base_gcw = nullptr,
                                    QWidget *left_title_bar_widget = nullptr,
                                    QWidget *right_title_bar_widget = nullptr,
                                    bool title_visible = true, bool icon_visible = true);

public slots:
    /** Set the left title bar widget and returns the previous widget or nullptr if none, delete this widget as needed.
        If the widget is transparent for mouse, but not it's children's set \e transparent_for_mouse to true. */
    QWidget *setLeftTitleBarWidget(QWidget *widget, bool transparent_for_mouse = false);

    /** Set the right title bar widget and returns the previous widget or nullptr if none, delete this widget as needed.
        If the widget is transparent for mouse, but not it's children's set \e transparent_for_mouse to true. */
    QWidget *setRightTitleBarWidget(QWidget *widget, bool transparent_for_mouse = false);

    /** Set the central widget of *QGoodCentralWidget*. */
    void setCentralWidget(QWidget *widget);

    /** Set the color of *QGoodCentralWidget* title bar. */
    void setTitleBarColor(const QColor &color);

    /** Set the color of *QGoodCentralWidget* border. */
    void setActiveBorderColor(const QColor &color);

    /** Change the visibility of *QGoodCentralWidget* title bar. */
    void setTitleBarVisible(bool visible);

    /** Change the visibility of *QGoodCentralWidget* title bar title. */
    void setTitleVisible(bool visible);

    /** Change the visibility of *QGoodCentralWidget* title bar icon. */
    void setIconVisible(bool visible);

    /** Change the title bar height to \e height multiplied to current pixel ratio. */
    void setTitleBarHeight(int height);

    /** Change the caption button width to \e width multiplied to current pixel ratio. */
    void setCaptionButtonWidth(int width);

    /** Returns the left *QGoodCentralWidget* title bar widget or nullptr if none is set. */
    QWidget *leftTitleBarWidget() const;

    /** Returns the right *QGoodCentralWidget* title bar widget or nullptr if none is set. */
    QWidget *rightTitleBarWidget() const;

    /** Returns the *QGoodCentralWidget* central widget or nullptr if none is set. */
    QWidget *centralWidget() const;

    /** Returns the *QGoodCentralWidget* title bar color. */
    QColor titleBarColor() const;

    /** Returns the *QGoodCentralWidget* border color. */
    QColor activeBorderColor() const;

    /** Returns if the *QGoodCentralWidget* title bar is visible or not. */
    bool isTitleBarVisible() const;

    /** Returns if the *QGoodCentralWidget* title bar title is visible or not. */
    bool isTitleVisible() const;

    /** Returns if the *QGoodCentralWidget* title bar icon is visible or not. */
    bool isIconVisible() const;

    /** Returns the *QGoodCentralWidget* title bar height. */
    int titleBarHeight() const;

    /** Returns the *QGoodCentralWidget* title bar caption button width. */
    int captionButtonWidth() const;

    /** Update the *QGoodCentralWidget* state, it's called internally
        and must be called if changing *QGoodCentralWidget* metrics
        like hide or show a title bar widget. */
    void updateWindow();

private:
    //\cond HIDDEN_SYMBOLS
    //Functions
    bool eventFilter(QObject *watched, QEvent *event);

    //Variables
    QPointer<QGoodWindow> m_gw;
    QPointer<QWidget> m_central_widget_place_holder;
    QPointer<QWidget> m_central_widget;
#ifdef QGOODWINDOW
    bool m_left_widget_transparent_for_mouse;
    bool m_right_widget_transparent_for_mouse;
    int m_caption_button_width;
    bool m_draw_borders;
    QFrame *m_frame;
    QString m_frame_style;
    TitleBar *m_title_bar;
    QPointer<QWidget> m_title_bar_left_widget;
    QPointer<QWidget> m_title_bar_right_widget;
    QColor m_title_bar_color;
    QColor m_active_border_color;
    bool m_title_bar_visible;
    bool m_title_visible;
    bool m_icon_visible;
#endif
    //\endcond
};

#endif // QGOODCENTRALWIDGET_H

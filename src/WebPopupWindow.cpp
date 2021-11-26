/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "WebPage.h"
#include "WebPopupWindow.h"
#include "WebView.h"
#include <QAction>
#include <QIcon>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QWindow>

/*****************************************************************************/
/**
 * @brief WebPopupWindow::WebPopupWindow
 * @param profile
 */
WebPopupWindow::WebPopupWindow(QWebEngineProfile *profile) : myUrlLineEdit(new QLineEdit(this)), myFavAction(new QAction(this)), myView(new WebView(this))
{
    setAttribute(Qt::WA_DeleteOnClose);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
    layout->addWidget(myUrlLineEdit);
    layout->addWidget(myView);

    myView->setPage(new WebPage(profile, myView));
    myView->setFocus();

    myUrlLineEdit->setReadOnly(true);
    myUrlLineEdit->addAction(myFavAction, QLineEdit::LeadingPosition);

    connect(myView, &WebView::titleChanged, this, &QWidget::setWindowTitle);
    connect(myView, &WebView::urlChanged, [this](const QUrl &url) { myUrlLineEdit->setText(url.toDisplayString()); });
    connect(myView, &WebView::favIconChanged, myFavAction, &QAction::setIcon);
    connect(myView->page(), &WebPage::geometryChangeRequested, this, &WebPopupWindow::handleGeometryChangeRequested);
    connect(myView->page(), &WebPage::windowCloseRequested, this, &QWidget::close);
}
/*****************************************************************************/
/**
 * @brief WebPopupWindow::view
 * @return
 */
WebView *WebPopupWindow::view() const
{
    return myView;
}
/*****************************************************************************/
/**
 * @brief WebPopupWindow::handleGeometryChangeRequested
 * @param newGeometry
 */
void WebPopupWindow::handleGeometryChangeRequested(const QRect &newGeometry)
{
    if (QWindow *window = windowHandle()) { setGeometry(newGeometry.marginsRemoved(window->frameMargins())); }
    show();
    myView->setFocus();
}
/******************************* End of File *********************************/

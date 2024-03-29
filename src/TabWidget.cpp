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
#include "TabWidget.h"

/*****************************************************************************/
/**
 * @brief TabWidget::TabWidget
 * @param thisMenuWidget
 * @param profile
 * @param parent
 */
TabWidget::TabWidget(QMenu *thisMenuWidget, QWebEngineProfile *profile, QWidget *parent) : QTabWidget(parent), myMenuWidget(thisMenuWidget), myProfile(profile)
{
    // Manage Bookmarks Menu
    myMenuWidget->addAction(tr("Manage Bookmarks"), this, &TabWidget::createBookmarkTab);
    //
    QTabBar *tabBar = this->tabBar();
    tabBar->setTabsClosable(true);
    tabBar->setSelectionBehaviorOnRemove(QTabBar::SelectPreviousTab);
    tabBar->setMovable(true);
    tabBar->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(tabBar, &QTabBar::customContextMenuRequested, this, &TabWidget::handleContextMenuRequested);
    connect(tabBar, &QTabBar::tabCloseRequested, this, &TabWidget::closeTab);
    connect(tabBar, &QTabBar::tabBarDoubleClicked, [this](int index) { if (index == -1) { createTab(); }});

    setDocumentMode(true);
    setElideMode(Qt::ElideRight);

    connect(this, &QTabWidget::currentChanged, this, &TabWidget::handleCurrentChanged);

    if (profile->isOffTheRecord())
    {
        QLabel *icon = new QLabel(this);
        QPixmap pixmap(QStringLiteral(":ninja.png"));
        icon->setPixmap(pixmap.scaledToHeight(tabBar->height()));
        setStyleSheet(QStringLiteral("QTabWidget::tab-bar { left: %1px; }").arg(icon->width()));
    }
    addFeatureTabs();
}
/*****************************************************************************/
/**
 * @brief TabWidget::handleCurrentChanged
 * @param index
 */
void TabWidget::handleCurrentChanged(int index)
{
    if (index != -1)
    {
        WebView *view = webView(index);
        if (view)
        {
            if (!view->url().isEmpty()) { view->setFocus(); }
            emit titleChanged(view->title());
            emit loadProgress(view->loadProgress());
            emit urlChanged(view->url());
            emit favIconChanged(view->favIcon());
            emit webActionEnabledChanged(QWebEnginePage::Back,    view->isWebActionEnabled(QWebEnginePage::Back));
            emit webActionEnabledChanged(QWebEnginePage::Forward, view->isWebActionEnabled(QWebEnginePage::Forward));
            emit webActionEnabledChanged(QWebEnginePage::Stop,    view->isWebActionEnabled(QWebEnginePage::Stop));
            emit webActionEnabledChanged(QWebEnginePage::Reload,  view->isWebActionEnabled(QWebEnginePage::Reload));
        }
    }
    else
    {
        emit titleChanged(QString());
        emit loadProgress(0);
        emit urlChanged(QUrl());
        emit favIconChanged(QIcon());
        emit webActionEnabledChanged(QWebEnginePage::Back, false);
        emit webActionEnabledChanged(QWebEnginePage::Forward, false);
        emit webActionEnabledChanged(QWebEnginePage::Stop, false);
        emit webActionEnabledChanged(QWebEnginePage::Reload, true);
    }
}
/*****************************************************************************/
/**
 * @brief TabWidget::handleContextMenuRequested
 * @param pos
 */
void TabWidget::handleContextMenuRequested(const QPoint &pos)
{
    QMenu menu;
    menu.addAction(tr("New &Tab"), this, &TabWidget::createTab, QKeySequence::AddTab);
    int index = tabBar()->tabAt(pos);
    if (index != -1)
    {
        QAction *action = menu.addAction(tr("Clone Tab"));
        connect(action, &QAction::triggered, this, [this,index]() { cloneTab(index); });
        menu.addSeparator();
        action = menu.addAction(tr("&Close Tab"));
        action->setShortcut(QKeySequence::Close);
        connect(action, &QAction::triggered, this, [this,index]() { closeTab(index); });
        action = menu.addAction(tr("Close &Other Tabs"));
        connect(action, &QAction::triggered, this, [this,index]() { closeOtherTabs(index); });
        menu.addSeparator();
        action = menu.addAction(tr("Reload Tab"));
        action->setShortcut(QKeySequence::Refresh);
        connect(action, &QAction::triggered, this, [this,index]() { reloadTab(index); });
    }
    else
    {
        menu.addSeparator();
    }
    menu.addAction(tr("Reload All Tabs"), this, &TabWidget::reloadAllTabs);
    menu.exec(QCursor::pos());
}
/*****************************************************************************/
/**
 * @brief TabWidget::currentWebView
 * @return
 */
WebView *TabWidget::currentWebView() const
{
    return webView(currentIndex());
}
/*****************************************************************************/
/**
 * @brief TabWidget::webView
 * @param index
 * @return
 */
WebView *TabWidget::webView(int index) const
{
    return qobject_cast<WebView*>(widget(index));
}
/*****************************************************************************/
/**
 * @brief TabWidget::setupView
 * @param webView
 */
void TabWidget::setupView(WebView *webView)
{
    QWebEnginePage *webPage = webView->page();

    connect(webView, &QWebEngineView::titleChanged, [this, webView](const QString &title)
    {
        int index = indexOf(webView);
        if (index != -1)
        {
            setTabText(index, title);
            setTabToolTip(index, title);
        }
        if (currentIndex() == index) { emit titleChanged(title); }
    });
    connect(webView, &QWebEngineView::urlChanged, [this, webView](const QUrl &url)
    {
        int index = indexOf(webView);
        if (index != -1)             { tabBar()->setTabData(index, url); }
        if (currentIndex() == index) { emit urlChanged(url); }
    });
    connect(webView, &QWebEngineView::loadProgress, [this, webView](int progress) { if (currentIndex() == indexOf(webView)) { emit loadProgress(progress); } });
    connect(webPage, &QWebEnginePage::linkHovered, [this, webView](const QString &url) { if (currentIndex() == indexOf(webView)) { emit linkHovered(url); } });
    connect(webView, &WebView::favIconChanged, [this, webView](const QIcon &icon)
    {
        int index = indexOf(webView);
        if (index != -1)             { setTabIcon(index, icon); }
        if (currentIndex() == index) { emit favIconChanged(icon); }
    });
    connect(webView, &WebView::webActionEnabledChanged, [this, webView](QWebEnginePage::WebAction action, bool enabled) { if (currentIndex() ==  indexOf(webView)) { emit webActionEnabledChanged(action,enabled); } });
    connect(webPage, &QWebEnginePage::windowCloseRequested, [this, webView]()
    {
        int index = indexOf(webView);
        if (index >= 0) { closeTab(index); }
    });
    connect(webView, &WebView::devToolsRequested, this, &TabWidget::devToolsRequested);
    #if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    connect(webPage, &QWebEnginePage::findTextFinished, [this, webView](const QWebEngineFindTextResult &result) { if (currentIndex() == indexOf(webView)) { emit findTextFinished(result); } });
    #endif
}
/*****************************************************************************/
/**
 * @brief TabWidget::getBookmarkTab
 * @return
 */
int TabWidget::getBookmarkTab()
{
    return myBookmarkTab;
}
/*****************************************************************************/
/**
 * @brief TabWidget::getBookmarkView
 * @return
 */
BookmarkView *TabWidget::getBookmarkView()
{
    return myBookmarkView;
}
/*****************************************************************************/
/**
 * @brief TabWidget::getHelpTab
 * @return
 */
int TabWidget::getHelpTab()
{
    return myHelpTab;
}
/*****************************************************************************/
/**
 * @brief TabWidget::getHelpView
 * @return
 */
HelpView *TabWidget::getHelpView()
{
    return myHelpView;
}
/*****************************************************************************/
/**
 * @brief TabWidget::getDownloadTab
 * @return
 */
int TabWidget::getDownloadTab()
{
    return myDownloadTab;
}
/*****************************************************************************/
/**
 * @brief TabWidget::setDownloadTab
 * @param thisDownloadTab
 */
void TabWidget::setDownloadTab(int thisDownloadTab)
{
    if (myDownloadTab != thisDownloadTab)
    {
        myDownloadTab = thisDownloadTab;
    }
}
/*****************************************************************************/
/**
 * @brief TabWidget::addFeatureTabs
 */
void TabWidget::addFeatureTabs()
{
    myHelpView = createBackgroundHelpTab();
    myBookmarkView = createBackgroundBookmarkTab();
}
/*****************************************************************************/
/**
 * @brief TabWidget::createHelpTab
 * @param thisSource
 */
void TabWidget::createHelpTab(const QString &thisSource)
{
    if (myHelpTab == -1)
    {
        myHelpView = createBackgroundHelpTab();
        if (!thisSource.isEmpty()) { myHelpView->setPageSource(thisSource); }
        //setCurrentWidget(myHelpView);
    }
    else
    {
        if (!thisSource.isEmpty()) { myHelpView->setPageSource(thisSource); }
        if (!isTabVisible(getHelpTab()))
        {
            setTabVisible(getHelpTab(), true);
        }
        setCurrentIndex(getHelpTab());
    }
}
/*****************************************************************************/
/**
 * @brief TabWidget::createBackgroundHelpTab
 * @return
 */
HelpView *TabWidget::createBackgroundHelpTab()
{
    HelpView *myHelpView = new HelpView(this);
    if (myHelpView->getPageSource().isEmpty())
    {
        myHelpView->setPageSource("qrc:Help_en.md");
    }
    setUpdatesEnabled(false);
    myHelpTab = addTab(myHelpView, tr("Help"));
    setTabVisible(getHelpTab(), false);
    setTabIcon(myHelpTab, myHelpView->favIcon());
    // Workaround for QTBUG-61770
    myHelpView->resize(currentWidget()->size());
    //myHelpView->show();
    setUpdatesEnabled(true);
    return myHelpView;
}
/*****************************************************************************/
/**
 * @brief TabWidget::createDownloadTab
 * @param thisDownloadManagerWidget
 */
void TabWidget::createDownloadTab(QPointer<DownloadManagerWidget> thisDownloadManagerWidget)
{
    if (myDownloadTab == -1)
    {
        setUpdatesEnabled(false);
        setDownloadTab(addTab(thisDownloadManagerWidget.data(), tr("Downloads")));
        setTabVisible(getDownloadTab(), false);
        setTabIcon(getDownloadTab(), thisDownloadManagerWidget->favIcon());
        // Workaround for QTBUG-61770
        thisDownloadManagerWidget->resize(currentWidget()->size());
        //setCurrentWidget(myDownloadManagerWidget);
        setUpdatesEnabled(true);
    }
    else
    {
        if (!isTabVisible(getDownloadTab()))
        {
            setTabVisible(getDownloadTab(), true);
        }
        setCurrentIndex(getHelpTab());
    }
}
/*****************************************************************************/
/**
 * @brief TabWidget::createBookmarkTab
 * @return
 */
void TabWidget::createBookmarkTab()
{
    createBookmarkTabAdd("");
}
/*****************************************************************************/
/**
 * @brief TabWidget::createBookmarkTabAdd
 * @param thisLink
 * @return
 */
void TabWidget::createBookmarkTabAdd(const QString &thisLink)
{
    if (myBookmarkTab == -1)
    {
        myBookmarkView = createBackgroundBookmarkTab();
        if (!thisLink.isEmpty()) { myBookmarkView->setUrl(thisLink); }
        //setCurrentWidget(myBookmarkView);
    }
    else
    {
        if (!isTabVisible(getBookmarkTab()))
        {
            setTabVisible(getBookmarkTab(), true);
        }
        setCurrentIndex(getBookmarkTab());
    }
}
/*****************************************************************************/
/**
 * @brief TabWidget::createBackgroundBookmarkTab
 * @return
 */
BookmarkView *TabWidget::createBackgroundBookmarkTab()
{
    BookmarkView *myBookmarkView = new BookmarkView(this);
    setUpdatesEnabled(false);
    myBookmarkTab = addTab(myBookmarkView, tr("Bookmarks"));
    setTabVisible(getBookmarkTab(), false);
    setTabIcon(myBookmarkTab, myBookmarkView->favIcon());
    // Workaround for QTBUG-61770
    myBookmarkView->resize(currentWidget()->size());
    //myBookmarkView->show();
    setUpdatesEnabled(true);
    return myBookmarkView;
}
/*****************************************************************************/
/**
 * @brief TabWidget::createTab
 * @return
 */
WebView *TabWidget::createTab()
{
    WebView *webView = createBackgroundTab();
    setCurrentWidget(webView);
    return webView;
}
/*****************************************************************************/
/**
 * @brief TabWidget::createBackgroundTab
 * @return
 */
WebView *TabWidget::createBackgroundTab()
{
    WebView *webView = new WebView;
    WebPage *webPage = new WebPage(myProfile, webView);
    webView->setPage(webPage);
    setupView(webView);
    int index = addTab(webView, tr("(Untitled)"));
    setTabIcon(index, webView->favIcon());
    // Workaround for QTBUG-61770
    webView->resize(currentWidget()->size());
    webView->show();
    return webView;
}
/*****************************************************************************/
/**
 * @brief TabWidget::reloadAllTabs
 */
void TabWidget::reloadAllTabs()
{
    for (int i = 0; i < count(); ++i) { webView(i)->reload(); }
}
/*****************************************************************************/
/**
 * @brief TabWidget::closeOtherTabs
 * @param index
 */
void TabWidget::closeOtherTabs(int index)
{
    for (int i = count() - 1; i > index; --i) { closeTab(i); }
    for (int i = index - 1; i >= 0; --i)      { closeTab(i); }
}
/*****************************************************************************/
/**
 * @brief TabWidget::closeAllTabs
 */
void TabWidget::closeAllTabs()
{
    setCurrentIndex(getDownloadTab());
    setTabIcon(getDownloadTab(), QIcon());
    setCurrentWidget(nullptr);
    for (int i = 0; i < count(); ++i)
    {
        removeTab(i);
    }
    delete myBookmarkView;
    delete myHelpView;
}
/*****************************************************************************/
/**
 * @brief TabWidget::closeTab
 * @param thisIndex must be greater then -1
 */
void TabWidget::closeTab(int thisIndex)
{
    if (myBookmarkTab == thisIndex) { setTabVisible(thisIndex, false); return; }
    if (myHelpTab     == thisIndex) { setTabVisible(thisIndex, false); return; }
    if (myDownloadTab == thisIndex) { setTabVisible(thisIndex, false); return; }

    if (WebView *view = webView(thisIndex))
    {
        bool hasFocus = view->hasFocus();
        removeTab(thisIndex);
        if (hasFocus && count() > 0) { currentWebView()->setFocus(); }
        if (count() == 0)            { createTab(); }
        view->deleteLater();
    }
}
/*****************************************************************************/
/**
 * @brief TabWidget::cloneTab
 * @param index
 */
void TabWidget::cloneTab(int index)
{
    if (WebView *view = webView(index))
    {
        WebView *tab = createTab();
        tab->setUrl(view->url());
    }
}
/*****************************************************************************/
/**
 * @brief TabWidget::setUrl
 * @param url
 */
void TabWidget::setUrl(const QUrl &url)
{
    if (!currentWebView()) { return; }
    if (WebView *view = currentWebView())
    {
        view->setUrl(url);
        view->setFocus();
    }
}
/*****************************************************************************/
/**
 * @brief TabWidget::triggerWebPageAction
 * @param action
 */
void TabWidget::triggerWebPageAction(QWebEnginePage::WebAction action)
{
    if (WebView *webView = currentWebView())
    {
        webView->triggerPageAction(action);
        webView->setFocus();
    }
}
/*****************************************************************************/
/**
 * @brief TabWidget::nextTab
 */
void TabWidget::nextTab()
{
    int next = currentIndex() + 1;
    if (next == count()) { next = 0; }
    setCurrentIndex(next);
}
/*****************************************************************************/
/**
 * @brief TabWidget::previousTab
 */
void TabWidget::previousTab()
{
    int next = currentIndex() - 1;
    if (next < 0) { next = count() - 1; }
    setCurrentIndex(next);
}
/*****************************************************************************/
/**
 * @brief TabWidget::reloadTab
 * @param index
 */
void TabWidget::reloadTab(int index)
{
    if (WebView *view = webView(index)) { view->reload(); }
}
/******************************* End of File *********************************/

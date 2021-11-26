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
#include "BrowserWindow.h"

/*****************************************************************************/
/**
 * @brief BrowserWindow::BrowserWindow
 * @param browser
 * @param profile
 * @param forDevTools
 */
BrowserWindow::BrowserWindow(QMenu *thisMenuWidget, Browser *browser, QWebEngineProfile *profile, bool forDevTools) : myMenuWidget(thisMenuWidget), myBrowser(browser), myProfile(profile), myTabWidget(new TabWidget(myMenuWidget, profile, this)), myProgressBar(nullptr), myTreeWidget(nullptr), myHistoryBackAction(nullptr), myHistoryForwardAction(nullptr), myStopAction(nullptr), myReloadAction(nullptr), myStopReloadAction(nullptr), myFavAction(nullptr), myUrlLineEdit(nullptr)
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    setFocusPolicy(Qt::ClickFocus);

    myBookmarkMenuWidgetView = new BookmarkMenu(myMenuWidget);
    // From bookmark menu
    QObject::connect(myBookmarkMenuWidgetView, &BookmarkMenu::handleOpenBookmark, myTabWidget, &TabWidget::setUrl);
    //
    if (!forDevTools)
    {
        myProgressBar = new QProgressBar(this);

        QToolBar *toolbar = createToolBar();
        addToolBar(toolbar);
        menuBar()->addMenu(createFileMenu(myTabWidget));
        menuBar()->addMenu(createEditMenu());
        menuBar()->addMenu(createViewMenu(toolbar));
        menuBar()->addMenu(myMenuWidget);
        menuBar()->addMenu(createWindowMenu(myTabWidget));
        menuBar()->addMenu(createHelpMenu());
    }

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    if (!forDevTools)
    {
        addToolBarBreak();

        myProgressBar->setMaximumHeight(1);
        myProgressBar->setTextVisible(false);
        myProgressBar->setStyleSheet(QStringLiteral("QProgressBar {border: 0px} QProgressBar::chunk {background-color: #da4453}"));

        layout->addWidget(myProgressBar);
    }

    layout->addWidget(myTabWidget);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(myTabWidget, &TabWidget::titleChanged, this, &BrowserWindow::handleWebViewTitleChanged);
    if (!forDevTools)
    {
        connect(myTabWidget, &TabWidget::linkHovered, [this](const QString& url) { statusBar()->showMessage(url); });
        connect(myTabWidget, &TabWidget::loadProgress, this, &BrowserWindow::handleWebViewLoadProgress);
        connect(myTabWidget, &TabWidget::webActionEnabledChanged, this, &BrowserWindow::handleWebActionEnabledChanged);
        connect(myTabWidget, &TabWidget::urlChanged, [this](const QUrl &url) { myUrlLineEdit->setText(url.toDisplayString()); });
        connect(myTabWidget, &TabWidget::favIconChanged, myFavAction, &QAction::setIcon);
        connect(myTabWidget, &TabWidget::devToolsRequested, this, &BrowserWindow::handleDevToolsRequested);
        connect(myUrlLineEdit, &QLineEdit::returnPressed, [this]() { myTabWidget->setUrl(QUrl::fromUserInput(myUrlLineEdit->text())); });
        #if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
        connect(myTabWidget, &TabWidget::findTextFinished, this, &BrowserWindow::handleFindTextFinished);
        #endif

        QAction *focusUrlLineEditAction = new QAction(this);
        addAction(focusUrlLineEditAction);
        focusUrlLineEditAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_L));
        connect(focusUrlLineEditAction, &QAction::triggered, this, [this] () { myUrlLineEdit->setFocus(Qt::ShortcutFocusReason); });
    }

    handleWebViewTitleChanged(QString());
    myTabWidget->createTab();
}
/*****************************************************************************/
/**
 * @brief BrowserWindow::~BrowserWindow
 */
BrowserWindow::~BrowserWindow()
{
}
/*****************************************************************************/
/**
 * @brief BrowserWindow::closeEvent
 * @param event
 */
void BrowserWindow::closeEvent(QCloseEvent *event)
{
    if (myTabWidget->count() > 1)
    {
        int theOpenFeatureTabs = 0;
        if (myTabWidget->getBookmarkTab() != -1)
        {
            theOpenFeatureTabs++;
        }
        if (myTabWidget->getHelpTab() != -1)
        {
            theOpenFeatureTabs++;
        }
        if (myTabWidget->getDownloadTab() != -1)
        {
            theOpenFeatureTabs++;
        }
        theOpenFeatureTabs = theOpenFeatureTabs - myTabWidget->count();
        if (theOpenFeatureTabs > 1)
        {
            int ret = QMessageBox::warning(this, tr("Confirm close"), tr("Are you sure you want to close the window ?\nThere are %1 tabs open.").arg(myTabWidget->count()), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
            if (ret == QMessageBox::No) { event->ignore(); return; }
        }
    }
    event->accept();
    deleteLater();
}
/*****************************************************************************/
/**
 * @brief BrowserWindow::sizeHint
 * @return
 */
QSize BrowserWindow::sizeHint() const
{
    QRect desktopRect = QApplication::primaryScreen()->geometry();
    QSize size = desktopRect.size() * qreal(0.9);
    return size;
}
/*****************************************************************************/
/**
 * @brief BrowserWindow::createFileMenu
 * @param tabWidget
 * @return
 */
QMenu *BrowserWindow::createFileMenu(TabWidget *tabWidget)
{
    QMenu *fileMenu = new QMenu(tr("&File"));
    fileMenu->addAction(tr("&New Window"), this, &BrowserWindow::handleNewWindowTriggered, QKeySequence::New);
    fileMenu->addAction(tr("New &Incognito Window"), this, &BrowserWindow::handleNewIncognitoWindowTriggered);

    QAction *newTabAction = new QAction(tr("New &Tab"), this);
    newTabAction->setShortcuts(QKeySequence::AddTab);
    connect(newTabAction, &QAction::triggered, this, [this]()
    {
        myTabWidget->createTab();
        myUrlLineEdit->setFocus();
    });
    fileMenu->addAction(newTabAction);

    fileMenu->addAction(tr("&Open File..."), this, &BrowserWindow::handleFileOpenTriggered, QKeySequence::Open);
    fileMenu->addSeparator();

    QAction *closeTabAction = new QAction(tr("&Close Tab"), this);
    closeTabAction->setShortcuts(QKeySequence::Close);
    connect(closeTabAction, &QAction::triggered, [tabWidget]() { tabWidget->closeTab(tabWidget->currentIndex()); });
    fileMenu->addAction(closeTabAction);

    QAction *closeAction = new QAction(tr("&Quit"),this);
    closeAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q));
    connect(closeAction, &QAction::triggered, this, &QWidget::close);
    fileMenu->addAction(closeAction);

    connect(fileMenu, &QMenu::aboutToShow, [this, closeAction]()
    {
        if (myBrowser->windows().count() == 1) { closeAction->setText(tr("&Quit")); }
        else                                   { closeAction->setText(tr("&Close Window")); }
    });
    return fileMenu;
}
#if !defined(QT_NO_CONTEXTMENU) && !defined(QT_NO_CLIPBOARD)
/*****************************************************************************/
/**
 * @brief BrowserWindow::onCustomContextMenuRequested
 * @param pos
 */
void BrowserWindow::onCustomContextMenuRequested(const QPoint &pos)
{
    const QTreeWidgetItem *item = myTreeWidget->itemAt(pos);
    if (!item) { return; }
    const QString url = item->text(1);
    QMenu contextMenu;
    //QAction *copyAction = contextMenu.addAction(QObject::tr("Copy Link to Clipboard"));
    QAction *openAction = contextMenu.addAction(QObject::tr("Open"));
    QAction *addAction = contextMenu.addAction(QObject::tr("Add"));
    QAction *action = contextMenu.exec(myTreeWidget->viewport()->mapToGlobal(pos));
    // FIXME clipboard
    //if (action == copyAction) { QGuiApplication::clipboard()->setText(url); }
    if (action == openAction)
        { QDesktopServices::openUrl(QUrl(url)); }
    else if (action == addAction)
        { myTreeWidget->addBookmark(); }
}
#endif // !QT_NO_CONTEXTMENU && !QT_NO_CLIPBOARD
/*****************************************************************************/
/**
 * @brief BrowserWindow::createEditMenu
 * @return
 */
QMenu *BrowserWindow::createEditMenu()
{
    QMenu *editMenu = new QMenu(tr("&Edit"));
    //
    QAction *findAction = editMenu->addAction(tr("&Find"));
    findAction->setShortcuts(QKeySequence::Find);
    connect(findAction, &QAction::triggered, this, &BrowserWindow::handleFindActionTriggered);
    QAction *findNextAction = editMenu->addAction(tr("Find &Next"));
    findNextAction->setShortcut(QKeySequence::FindNext);
    connect(findNextAction, &QAction::triggered, [this]()
    {
        if (!currentTab() || myLastSearch.isEmpty()) { return; }
        currentTab()->findText(myLastSearch);
    });

    QAction *findPreviousAction = editMenu->addAction(tr("Find &Previous"));
    findPreviousAction->setShortcut(QKeySequence::FindPrevious);
    connect(findPreviousAction, &QAction::triggered, [this]()
    {
        if (!currentTab() || myLastSearch.isEmpty()) { return; }
        currentTab()->findText(myLastSearch, QWebEnginePage::FindBackward);
    });

    return editMenu;
}
/*****************************************************************************/
/**
 * @brief BrowserWindow::createViewMenu
 * @param toolbar
 * @return
 */
QMenu *BrowserWindow::createViewMenu(QToolBar *toolbar)
{
    QMenu *viewMenu = new QMenu(tr("&View"));
    myStopAction = viewMenu->addAction(tr("&Stop"));
    QList<QKeySequence> shortcuts;
    shortcuts.append(QKeySequence(Qt::CTRL | Qt::Key_Period));
    shortcuts.append(Qt::Key_Escape);
    myStopAction->setShortcuts(shortcuts);
    connect(myStopAction, &QAction::triggered, [this]() { myTabWidget->triggerWebPageAction(QWebEnginePage::Stop); });

    myReloadAction = viewMenu->addAction(tr("Reload Page"));
    myReloadAction->setShortcuts(QKeySequence::Refresh);
    connect(myReloadAction, &QAction::triggered, [this]() { myTabWidget->triggerWebPageAction(QWebEnginePage::Reload); });

    QAction *zoomIn = viewMenu->addAction(tr("Zoom &In"));
    zoomIn->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Plus));
    connect(zoomIn, &QAction::triggered, [this]() { if (currentTab()) { currentTab()->setZoomFactor(currentTab()->zoomFactor() + 0.1); } });

    QAction *zoomOut = viewMenu->addAction(tr("Zoom &Out"));
    zoomOut->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Minus));
    connect(zoomOut, &QAction::triggered, [this]() { if (currentTab()) { currentTab()->setZoomFactor(currentTab()->zoomFactor() - 0.1); } });

    QAction *resetZoom = viewMenu->addAction(tr("Reset &Zoom"));
    resetZoom->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_0));
    connect(resetZoom, &QAction::triggered, [this]() { if (currentTab()) { currentTab()->setZoomFactor(1.0); } });


    viewMenu->addSeparator();
    QAction *viewToolbarAction = new QAction(tr("Hide Toolbar"),this);
    viewToolbarAction->setShortcut(tr("Ctrl+|"));
    connect(viewToolbarAction, &QAction::triggered, [toolbar,viewToolbarAction]()
    {
        if (toolbar->isVisible())
        {
            viewToolbarAction->setText(tr("Show Toolbar"));
            toolbar->close();
        }
        else
        {
            viewToolbarAction->setText(tr("Hide Toolbar"));
            toolbar->show();
        }
    });
    viewMenu->addAction(viewToolbarAction);

    QAction *viewStatusbarAction = new QAction(tr("Hide Status Bar"), this);
    viewStatusbarAction->setShortcut(tr("Ctrl+/"));
    connect(viewStatusbarAction, &QAction::triggered, [this, viewStatusbarAction]()
    {
        if (statusBar()->isVisible())
        {
            viewStatusbarAction->setText(tr("Show Status Bar"));
            statusBar()->close();
        }
        else
        {
            viewStatusbarAction->setText(tr("Hide Status Bar"));
            statusBar()->show();
        }
    });
    viewMenu->addAction(viewStatusbarAction);
    return viewMenu;
}
/*****************************************************************************/
/**
 * @brief BrowserWindow::createWindowMenu
 * @param tabWidget
 * @return
 */
QMenu *BrowserWindow::createWindowMenu(TabWidget *tabWidget)
{
    QMenu *menu = new QMenu(tr("&Window"));

    QAction *nextTabAction = new QAction(tr("Show Next Tab"), this);
    QList<QKeySequence> shortcuts;
    shortcuts.append(QKeySequence(Qt::CTRL | Qt::Key_BraceRight));
    shortcuts.append(QKeySequence(Qt::CTRL | Qt::Key_PageDown));
    shortcuts.append(QKeySequence(Qt::CTRL | Qt::Key_BracketRight));
    shortcuts.append(QKeySequence(Qt::CTRL | Qt::Key_Less));
    nextTabAction->setShortcuts(shortcuts);
    connect(nextTabAction, &QAction::triggered, tabWidget, &TabWidget::nextTab);

    QAction *previousTabAction = new QAction(tr("Show Previous Tab"), this);
    shortcuts.clear();
    shortcuts.append(QKeySequence(Qt::CTRL | Qt::Key_BraceLeft));
    shortcuts.append(QKeySequence(Qt::CTRL | Qt::Key_PageUp));
    shortcuts.append(QKeySequence(Qt::CTRL | Qt::Key_BracketLeft));
    shortcuts.append(QKeySequence(Qt::CTRL | Qt::Key_Greater));
    previousTabAction->setShortcuts(shortcuts);
    connect(previousTabAction, &QAction::triggered, tabWidget, &TabWidget::previousTab);

    connect(menu, &QMenu::aboutToShow, [this, menu, nextTabAction, previousTabAction]()
    {
        menu->clear();
        menu->addAction(nextTabAction);
        menu->addAction(previousTabAction);
        menu->addSeparator();
        QVector<BrowserWindow*> windows = myBrowser->windows();
        int index(-1);
        for (auto window : windows)
        {
            QAction *action = menu->addAction(window->windowTitle(), this, &BrowserWindow::handleShowWindowTriggered);
            action->setData(++index);
            action->setCheckable(true);
            if (window == this) { action->setChecked(true); }
        }
    });
    return menu;
}
/*****************************************************************************/
/**
 * @brief BrowserWindow::createHelpMenu
 * @return
 */
QMenu *BrowserWindow::createHelpMenu()
{
    QMenu *helpMenu = new QMenu(tr("&Help"));
    helpMenu->addAction(tr("About &Qt"), this, &BrowserWindow::onSetHelpTab);
    return helpMenu;
}
/*****************************************************************************/
/**
 * @brief BrowserWindow::createToolBar
 * @return
 */
QToolBar *BrowserWindow::createToolBar()
{
    QToolBar *navigationBar = new QToolBar(tr("Navigation"));
    navigationBar->setMovable(false);
    navigationBar->toggleViewAction()->setEnabled(false);

    myHistoryBackAction = new QAction(this);
    QList<QKeySequence> backShortcuts = QKeySequence::keyBindings(QKeySequence::Back);
    for (auto it = backShortcuts.begin(); it != backShortcuts.end();)
    {
        // Chromium already handles navigate on backspace when appropriate.
        if ((*it)[0] == Qt::Key_Backspace)
            { it = backShortcuts.erase(it); }
        else
            { ++it; }
    }
    // For some reason Qt doesn't bind the dedicated Back key to Back.
    backShortcuts.append(QKeySequence(Qt::Key_Back));
    myHistoryBackAction->setShortcuts(backShortcuts);
    myHistoryBackAction->setIconVisibleInMenu(false);
    myHistoryBackAction->setIcon(QIcon(QStringLiteral(":go-previous.png")));
    myHistoryBackAction->setToolTip(tr("Go back in history"));
    connect(myHistoryBackAction, &QAction::triggered, [this]() { myTabWidget->triggerWebPageAction(QWebEnginePage::Back); });
    navigationBar->addAction(myHistoryBackAction);

    myHistoryForwardAction = new QAction(this);
    QList<QKeySequence> fwdShortcuts = QKeySequence::keyBindings(QKeySequence::Forward);
    for (auto it = fwdShortcuts.begin(); it != fwdShortcuts.end();)
    {
        if (((*it)[0] & Qt::Key_unknown) == Qt::Key_Backspace)
            { it = fwdShortcuts.erase(it); }
        else
            { ++it; }
    }
    fwdShortcuts.append(QKeySequence(Qt::Key_Forward));
    myHistoryForwardAction->setShortcuts(fwdShortcuts);
    myHistoryForwardAction->setIconVisibleInMenu(false);
    myHistoryForwardAction->setIcon(QIcon(QStringLiteral(":go-next.png")));
    myHistoryForwardAction->setToolTip(tr("Go forward in history"));
    connect(myHistoryForwardAction, &QAction::triggered, [this]() { myTabWidget->triggerWebPageAction(QWebEnginePage::Forward); });
    navigationBar->addAction(myHistoryForwardAction);

    myStopReloadAction = new QAction(this);
    connect(myStopReloadAction, &QAction::triggered, [this]() { myTabWidget->triggerWebPageAction(QWebEnginePage::WebAction(myStopReloadAction->data().toInt())); });
    navigationBar->addAction(myStopReloadAction);

    myUrlLineEdit = new QLineEdit(this);
    myFavAction = new QAction(this);
    myUrlLineEdit->addAction(myFavAction, QLineEdit::LeadingPosition);
    myUrlLineEdit->setClearButtonEnabled(true);
    navigationBar->addWidget(myUrlLineEdit);
    //
    auto bookmarkerAction = new QAction(this);
    bookmarkerAction->setIcon(QIcon(QStringLiteral(":addressbook.png")));
    bookmarkerAction->setToolTip(tr("Bookmark"));
    navigationBar->addAction(bookmarkerAction);
    connect(bookmarkerAction, &QAction::triggered, this, &BrowserWindow::onBookmarkUrl);
    // Show Downloads
    auto downloadsAction = new QAction(this);
    downloadsAction->setIcon(QIcon(QStringLiteral(":go-bottom.png")));
    downloadsAction->setToolTip(tr("Show downloads"));
    navigationBar->addAction(downloadsAction);
    //connect(downloadsAction, &QAction::triggered, [this]() { myBrowser->downloadManagerWidget().show(); });
    connect(downloadsAction, &QAction::triggered, this, &BrowserWindow::onDownloadTab);
    //
    return navigationBar;
}
/*****************************************************************************/
/**
 * @brief BrowserWindow::handleWebActionEnabledChanged
 * @param action
 * @param enabled
 */
void BrowserWindow::handleWebActionEnabledChanged(QWebEnginePage::WebAction action, bool enabled)
{
    switch (action)
    {
        case QWebEnginePage::Back:
            myHistoryBackAction->setEnabled(enabled);
            break;
        case QWebEnginePage::Forward:
            myHistoryForwardAction->setEnabled(enabled);
            break;
        case QWebEnginePage::Reload:
            myReloadAction->setEnabled(enabled);
            break;
        case QWebEnginePage::Stop:
            myStopAction->setEnabled(enabled);
            break;
        default:
            qWarning("Unhandled webActionChanged signal");
    }
}
/*****************************************************************************/
/**
 * @brief BrowserWindow::handleWebViewTitleChanged
 * @param title
 */
void BrowserWindow::handleWebViewTitleChanged(const QString &title)
{
    QString suffix = myProfile->isOffTheRecord() ? tr("Qt Simple Browser (Incognito)") : tr("Qt Simple Browser");
    if (title.isEmpty())
        { setWindowTitle(suffix); }
    else
        { setWindowTitle(title + " - " + suffix); }
}
/*****************************************************************************/
/**
 * @brief BrowserWindow::handleNewWindowTriggered
 */
void BrowserWindow::handleNewWindowTriggered()
{
    BrowserWindow *window = myBrowser->createWindow();
    window->myUrlLineEdit->setFocus();
}
/*****************************************************************************/
/**
 * @brief BrowserWindow::handleNewIncognitoWindowTriggered
 */
void BrowserWindow::handleNewIncognitoWindowTriggered()
{
    BrowserWindow *window = myBrowser->createWindow(/* offTheRecord: */ true);
    window->myUrlLineEdit->setFocus();
}
/*****************************************************************************/
/**
 * @brief BrowserWindow::handleFileOpenTriggered
 */
void BrowserWindow::handleFileOpenTriggered()
{
    QUrl url = QFileDialog::getOpenFileUrl(this, tr("Open Web Resource"), QString(), tr("Web Resources (*.html *.htm *.svg *.png *.gif *.svgz);;All files (*.*)"));
    if (url.isEmpty()) { return; }
    currentTab()->setUrl(url);
}
/*****************************************************************************/
/**
 * @brief BrowserWindow::handleFindActionTriggered
 */
void BrowserWindow::handleFindActionTriggered()
{
    if (!currentTab()) { return; }
    bool ok = false;
    QString search = QInputDialog::getText(this, tr("Find"), tr("Find:"), QLineEdit::Normal, myLastSearch, &ok);
    if (ok && !search.isEmpty())
    {
        myLastSearch = search;
        #if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
        currentTab()->findText(myLastSearch);
        #else
        currentTab()->findText(myLastSearch, 0, [this](bool found) { if (!found) { statusBar()->showMessage(tr("\"%1\" not found.").arg(myLastSearch)); } });
        #endif
    }
}
/*****************************************************************************/
/**
 * @brief BrowserWindow::tabWidget
 * @return
 */
TabWidget *BrowserWindow::tabWidget() const
{
    return myTabWidget;
}
/*****************************************************************************/
/**
 * @brief BrowserWindow::currentTab
 * @return
 */
WebView *BrowserWindow::currentTab() const
{
    return myTabWidget->currentWebView();
}
/*****************************************************************************/
/**
 * @brief BrowserWindow::handleWebViewLoadProgress
 * @param progress
 */
void BrowserWindow::handleWebViewLoadProgress(int progress)
{
    static QIcon stopIcon(QStringLiteral(":process-stop.png"));
    static QIcon reloadIcon(QStringLiteral(":view-refresh.png"));

    if (0 < progress && progress < 100)
    {
        myStopReloadAction->setData(QWebEnginePage::Stop);
        myStopReloadAction->setIcon(stopIcon);
        myStopReloadAction->setToolTip(tr("Stop loading the current page"));
        myProgressBar->setValue(progress);
    }
    else
    {
        myStopReloadAction->setData(QWebEnginePage::Reload);
        myStopReloadAction->setIcon(reloadIcon);
        myStopReloadAction->setToolTip(tr("Reload the current page"));
        myProgressBar->setValue(0);
    }
}
/*****************************************************************************/
/**
 * @brief BrowserWindow::handleShowWindowTriggered
 */
void BrowserWindow::handleShowWindowTriggered()
{
    if (QAction *action = qobject_cast<QAction*>(sender()))
    {
        int offset = action->data().toInt();
        QVector<BrowserWindow*> windows = myBrowser->windows();
        windows.at(offset)->activateWindow();
        windows.at(offset)->currentTab()->setFocus();
    }
}
/*****************************************************************************/
/**
 * @brief BrowserWindow::handleDevToolsRequested
 * @param source
 */
void BrowserWindow::handleDevToolsRequested(QWebEnginePage *source)
{
    source->setDevToolsPage(myBrowser->createDevToolsWindow()->currentTab()->page());
    source->triggerAction(QWebEnginePage::InspectElement);
}
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
/*****************************************************************************/
/**
 * @brief BrowserWindow::handleFindTextFinished
 * @param result
 */
void BrowserWindow::handleFindTextFinished(const QWebEngineFindTextResult &result)
{
    if (result.numberOfMatches() == 0)
        { statusBar()->showMessage(tr("\"%1\" not found.").arg(myLastSearch)); }
    else
        { statusBar()->showMessage(tr("\"%1\" found: %2/%3").arg(myLastSearch, QString::number(result.activeMatch()), QString::number(result.numberOfMatches()))); }
}
#endif
/*****************************************************************************/
/**
 * @brief BrowserWindow::onBookmarkUrl
 */
void BrowserWindow::onBookmarkUrl()
{
    if (!myUrlLineEdit->text().isEmpty())
    {
        if (myTabWidget->getBookmarkTab() == -1)
        {
            myTabWidget->createBookmarkTabAdd(myUrlLineEdit->text());
        }
        else
        {
            myTabWidget->getBookmarkView()->setUrl(myUrlLineEdit->text());
            myTabWidget->setCurrentIndex(myTabWidget->getBookmarkTab());
            if (!myTabWidget->isTabVisible(myTabWidget->getBookmarkTab()))
            {
                myTabWidget->setTabVisible(myTabWidget->getBookmarkTab(), true);
                myTabWidget->setCurrentIndex(myTabWidget->getBookmarkTab());
            }
        }
    }
}
/*****************************************************************************/
/**
 * @brief BrowserWindow::onSetHelpTab
 */
void BrowserWindow::onSetHelpTab()
{
    if (myTabWidget->getHelpTab() == -1)
    {
        myTabWidget->createHelpTab("qrc:Help_en.md");
    }
    else
    {
        myTabWidget->getHelpView()->setPageSource("qrc:Help_en.md");
        myTabWidget->setCurrentIndex(myTabWidget->getHelpTab());
        if (!myTabWidget->isTabVisible(myTabWidget->getHelpTab()))
        {
            myTabWidget->setTabVisible(myTabWidget->getHelpTab(), true);
        }
    }
}
/*****************************************************************************/
/**
 * @brief BrowserWindow::onDownloadTab
 */
void BrowserWindow::onDownloadTab()
{
    if (myTabWidget->getDownloadTab() == -1)
    {
        myDownloadManagerWidget = &myBrowser->downloadManagerWidget();
        int index = myTabWidget->addTab(myDownloadManagerWidget, tr("Downloads"));
        myTabWidget->setTabIcon(index, myBrowser->downloadManagerWidget().favIcon());
        myTabWidget->setDownloadTab(index);
        // Workaround for QTBUG-61770
        myBrowser->downloadManagerWidget().resize(myTabWidget->currentWidget()->size());
        myBrowser->downloadManagerWidget().show();
        myTabWidget->setCurrentWidget(myDownloadManagerWidget);
    }
    else
    {
        myTabWidget->setCurrentIndex(myTabWidget->getDownloadTab());
        if (!myTabWidget->isTabVisible(myTabWidget->getDownloadTab()))
        {
            myTabWidget->setTabVisible(myTabWidget->getDownloadTab(), true);
        }
    }
}
/******************************* End of File *********************************/

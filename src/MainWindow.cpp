/******************************************************************************
** WeBook: Pronounced Web-Book, is a Book Content Management System  (BCMS)   *
*******************************************************************************/
#include "MainWindow.h"
/******************************************************************************
** MainWindow Constructor                                                     *
** I use CamelCase and Qt uses no_camel_case; even thu these is an option.    *
** This means that Automatic Signal to Slot Connects will not be made.        *
** The reason I do not want this auto handler of events, is simple, typos.    *
** A typo will not get caught at compile time, CamelCase enforces this.       *
** So all connects are manual.                                                *
**  *
**  *
** The Method to my Maddness starts with Text only data and not SQL databases *
** SQL is more complex doing searches for data stored in Text files pointless *
** The WeBook Manager is a Single Name with No Spaces, and a new entery       *
** Is Name will be the Folder all the data is in, and why no spaces           *
**  *
**  *
*******************************************************************************/
/*!
   \class MainWindow
   \title WeBook Client Main Windows
   \brief WeBook is Pronounced Web Book, it is a Web Content Book Manager.
   \inmodule WeBookClient
   \inherits QMainWindow
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    qLoggerCommon = new QLogger::QLoggerCommon(true);

    // Set up UI and set defaults just so we know all the ui conttrols we are working with
    ui->setupUi(this);

    // Connect Signals to Slots
    connect(this, &MainWindow::handelStatusMessage,      this, &MainWindow::onStatusMessage);


    #ifdef Q_OS_OSX
        setUnifiedTitleAndToolBarOnMac(true);
    #endif
    setWindowTitle(QApplication::applicationName());

    connect(ui->textEdit,                                       &QTextEdit::currentCharFormatChanged, this,           &MainWindow::onCurrentCharFormatChanged);
    connect(ui->textEdit,                                       &QTextEdit::cursorPositionChanged,    this,           &MainWindow::onCursorPositionChanged);

    setToolButtonStyle(Qt::ToolButtonFollowStyle);

    setupTextActions();

    QFont textFont("Helvetica");
    textFont.setStyleHint(QFont::SansSerif);
    ui->textEdit->setFont(textFont);
    fontChanged(ui->textEdit->font());
    colorChanged(ui->textEdit->textColor());
    alignmentChanged(ui->textEdit->alignment());

    connect(ui->textEdit->document(),                           &QTextDocument::modificationChanged,  ui->actionSave, &QAction::setEnabled);
    connect(ui->textEdit->document(),                           &QTextDocument::modificationChanged,  this,           &QWidget::setWindowModified);
    connect(ui->textEdit->document(),                           &QTextDocument::undoAvailable,        ui->actionUndo, &QAction::setEnabled);
    connect(ui->textEdit->document(),                           &QTextDocument::redoAvailable,        ui->actionRedo, &QAction::setEnabled);

    setWindowModified(ui->textEdit->document()->isModified());
    ui->actionSave->setEnabled(ui->textEdit->document()->isModified());
    ui->actionUndo->setEnabled(ui->textEdit->document()->isUndoAvailable());
    ui->actionRedo->setEnabled(ui->textEdit->document()->isRedoAvailable());

    ui->actionCut->setEnabled(false);
    ui->actionCopy->setEnabled(false);

#ifndef QT_NO_CLIPBOARD
    connect(ui->textEdit,              &QTextEdit::copyAvailable, ui->actionCut,  &QAction::setEnabled);
    connect(ui->textEdit,              &QTextEdit::copyAvailable, ui->actionCopy, &QAction::setEnabled);
    connect(QApplication::clipboard(), &QClipboard::dataChanged,  this,           &MainWindow::onClipboardDataChanged);
#endif
    //


#ifdef Q_OS_MACOS
    // Use dark text on light background on macOS, also in dark mode.
    QPalette pal = ui->textEdit->palette();
    pal.setColor(QPalette::Base, QColor(Qt::white));
    pal.setColor(QPalette::Text, QColor(Qt::black));
    ui->textEdit->setPalette(pal);
#endif
    //
    setWeBookModel();
    //    Settings
    ui->editSettingsIniFileName->setText(qLoggerCommon->getSetting(QLogger::ConstSettingsIniFileName, qLoggerCommon->combinePathFileName(qLoggerCommon->getFilelPath(), qLoggerCommon->getIniFileName())).toString());
    ui->editSettingsApplicationName->setText(qLoggerCommon->getSetting(QLogger::ConstSettingsApplicationName, qLoggerCommon->getAppName()).toString());
    ui->editSettingsOrgName->setText(qLoggerCommon->getSetting(QLogger::ConstSettingsOrgName, qLoggerCommon->getOrgName()).toString());
    ui->editSettingsOrgDomain->setText(qLoggerCommon->getSetting(QLogger::ConstSettingsOrgDomain, qLoggerCommon->getOrgDomain()).toString());
    //    Database
    //    spinBoxDbPort               Spinbox

    //    WeBookMan
    //    spinBoxWeBookManYear        Spinbox
    //    spinBoxWeBookManRating      Spinbox
    ui->editWeBookManTitle->setText(qLoggerCommon->getSetting("WeBookManTitle", "").toString());
    // Connect Signals to Slots
    // external
    connect(ui->actionQt,                   &QAction::triggered,            qApp,           &QApplication::aboutQt);
    // internal
    connect(ui->actionQuit,                 &QAction::triggered,            this,           &MainWindow::quitNow);
    connect(ui->widgetTab,                  &QTabWidget::currentChanged,    this,           &MainWindow::onTabChanged);
    connect(ui->pushButtonWeBookManAdd,     &QPushButton::clicked,          this,           &MainWindow::onAddBook);
    connect(ui->pushButtonWeBookManDelete,  &QPushButton::clicked,          this,           &MainWindow::onDeleteBook);
    connect(ui->pushButtonSgSave,           &QPushButton::clicked,          this,           &MainWindow::onSaveApplicationSettings);
    connect(ui->actionAbout,                &QAction::triggered,            this,           &MainWindow::onAbout);
    connect(ui->actionTextBold,             &QAction::triggered,            this,           &MainWindow::onTextBold);
    connect(ui->actionTextUnderline,        &QAction::triggered,            this,           &MainWindow::onTextUnderline);
    connect(ui->actionToggleCheckState,     &QAction::triggered,            this,           &MainWindow::onSetChecked);
    connect(ui->actionTextItalic,           &QAction::triggered,            this,           &MainWindow::onTextItalic);
    connect(ui->actionTextColor,            &QAction::triggered,            this,           &MainWindow::onTextColor);
    connect(ui->actionNew,                  &QAction::triggered,            this,           &MainWindow::onFileNew);
    connect(ui->actionPDF,                  &QAction::triggered,            this,           &MainWindow::onFilePrintPdf);
    connect(ui->actionPrint,                &QAction::triggered,            this,           &MainWindow::onFilePrint);
    connect(ui->actionSave,                 &QAction::triggered,            this,           &MainWindow::onFileSave);
    connect(ui->actionIndentMore,           &QAction::triggered,            this,           &MainWindow::onIndent);
    connect(ui->actionIndentLess,           &QAction::triggered,            this,           &MainWindow::onUnindent);
    // There is a way to pass the function in, but I could not find it, and it still requires all 4 connects, so what is the point
    connect(ui->actionAlignLeft,            &QAction::triggered,            this, [this]() { MainWindow::onTextAlign(ui->actionAlignLeft); });
    connect(ui->actionAlignCenter,          &QAction::triggered,            this, [this]() { MainWindow::onTextAlign(ui->actionAlignCenter); });
    connect(ui->actionAlignRight,           &QAction::triggered,            this, [this]() { MainWindow::onTextAlign(ui->actionAlignRight); });
    connect(ui->actionAlignJustify,         &QAction::triggered,            this, [this]() { MainWindow::onTextAlign(ui->actionAlignJustify); });
    //
    //
    connect(ui->actionCut,                  &QAction::triggered,            ui->textEdit,   &QTextEdit::cut);
    connect(ui->actionCopy,                 &QAction::triggered,            ui->textEdit,   &QTextEdit::copy);
    connect(ui->actionRedo,                 &QAction::triggered,            ui->textEdit,   &QTextEdit::redo);
    connect(ui->actionUndo,                 &QAction::triggered,            ui->textEdit,   &QTextEdit::undo);
    connect(ui->actionPaste,                &QAction::triggered,            ui->textEdit,   &QTextEdit::paste);
    //
    // connectSlotsByName
    // void on_<object name>_<signal name>(<signal parameters>);
    //
    setTocTreeViewModel("");
    // TOC Change Document in Editor
    connect(ui->treeViewTocView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::onTocUpdateActions);
    connect(ui->menuTOC,                           &QMenu::aboutToShow, this, &MainWindow::onTocUpdateActions);
    connect(ui->actionTocInsertRowAction,          &QAction::triggered, this, &MainWindow::onTocInsertRow);
    connect(ui->actionTocInsertColumnAction,       &QAction::triggered, this, &MainWindow::onTocInsertColumn);
    connect(ui->actionTocRemoveRowAction,          &QAction::triggered, this, &MainWindow::onTocRemoveRow);
    connect(ui->actionTocRemoveColumnAction,       &QAction::triggered, this, &MainWindow::onTocRemoveColumn);
    connect(ui->actionTocInsertChildAction,        &QAction::triggered, this, &MainWindow::onTocInsertChild);
    // The WeBook Change TOC
    connect(ui->listViewWeBookMan->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::loadTOC);
    //
    // Alphanumber . - _
    QRegExp rx("^[a-zA-Z0-9_.-]*$");
    QValidator* validator = new QRegExpValidator( rx, 0 );
    ui->editWeBookManTitle->setValidator(validator);

/*
 *
    connect(spinboxObject, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int newValue) { });
 */

    ui->textEdit->setFocus();

    emit handelStatusMessage(tr("Ready")); // onStatusMessage
} // end MainWindow
/******************************************************************************
** ~MainWindow Deconstructor                                                  *
*******************************************************************************/
MainWindow::~MainWindow()
{
    if (isDebugMessage) qDebug() << "Deconstructor: writeSettings then delete ui";
    delete ui;
} // end ~MainWindow
/******************************************************************************
** closeEvent                                                                 *
*******************************************************************************/
void MainWindow::closeEvent(QCloseEvent *e)
{
    if (isDebugMessage) qDebug() << "closeEvent";
    if (maybeSave()) e->accept();
    else             e->ignore();
    if (!isCloseCalled)
    {
        isCloseCalled = true; // to prevent reentering this call
        quitNow();
    }
} // end closeEvent
/******************************************************************************
** quitNow                                                                    *
*******************************************************************************/
void MainWindow::quitNow()
{
    if (isDebugMessage) qDebug() << "quitNow";
    writeSettings();
    if (!isCloseCalled)
    {
        isCloseCalled = true; // to prevent reentering this call
        emit handleEventAction(0); // FIXME Enum
        close();
    }
} // end quitNow
/******************************************************************************
** setTreeViewModel                                                           *
** This uses a String Model, internally all the records are strings
** A record is a row in a StringList
** Looking a this from the stand point of the Text, each row is a record
** The string is a ID Tab Title format using 2 spaces to specify a child of the above
**  |  1 2  3
** 1|Top    Top
** 2|  Item1 Item 1
** 3|  Item2 Item 2
** 4|  Item3 Item 3
** 5|    Item3.1 Item 3.1
** 6|       Item3.1.1 Item 3.1.1
** 7|  Item4 Item 4
** 8|  Item5 Item 5
**
** TOC is a File named after the WeBook Managers books: WeBook,MyBook, .toc   *
*******************************************************************************/
void MainWindow::setTocTreeViewModel(QString modelName)
{
    if (isDebugMessage) qDebug() << "Set Toc TreeView Model";
    //
    QString myTocPath;
    if (modelName.isEmpty())
    {
        // Current Book
        modelName = myCurrentBook = qLoggerCommon->getSetting(constCurrentWeBook, QLogger::ConstDefaultAppFolder).toString(); // Defaults to the same as the default folder name
        myTocPath = QString("%1%2%3.toc").arg(qLoggerCommon->getFilelPath(), QDir::separator(), modelName);
    }
    else
    {
        myTocPath = modelName;
    }
    if (!myTocPath.contains(QDir::separator()))
    {
        myTocPath = QString("%1%2%3.toc").arg(qLoggerCommon->getFilelPath(), QDir::separator(), modelName);
    }
    QFile booksResourceFile(myTocPath);
    if (booksResourceFile.exists())
    {
        if (!openWeBookTOC(myTocPath))
        {
            qDebug() << "Error could not open file for reading: " << booksResourceFile.fileName() << " Error = " << booksResourceFile.errorString();
        }
    }
    else
    {
        if (booksResourceFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        {
            QTextStream out(&booksResourceFile);
            out << constDefaultTOC;  // "Home\tHome Page\n"
            booksResourceFile.close();
            if (!openWeBookTOC(myTocPath))
            {
                qDebug() << "Error could not open file for reading: " << booksResourceFile.fileName() << " Error = " << booksResourceFile.errorString();
            }
        }
        else
        {
            qDebug() << "Error could not open file for reading: " << booksResourceFile.fileName() << " Error = " << booksResourceFile.errorString();
        }
    }
} // end setTocTreeViewModel
/******************************************************************************
** openWeBookTOC(QString thisFullPathFileName)                                *
*******************************************************************************/
bool MainWindow::openWeBookTOC(QString thisFullPathFileName)
{
    if (isDebugMessage) qDebug() << "open WeBook TOC";
    QFile booksResourceFile(thisFullPathFileName);
    if (booksResourceFile.exists())
    {
        if (booksResourceFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            dragDropTocModel = new TreeViewDragDropModel(booksResourceFile.readAll(), this);
            ui->treeViewTocView->setModel(dragDropTocModel);

            for (int column = 0; column < dragDropTocModel->columnCount(); ++column) ui->treeViewTocView->resizeColumnToContents(column);

            connect(ui->treeViewTocView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::onTocUpdateActions);

            booksResourceFile.close();
            return true;
        }
        else
        {
            qDebug() << "Error could not open books.txt for reading: " << booksResourceFile.fileName() << " Error = " << booksResourceFile.errorString();
        }
    }
    return false;
} // end openWeBookTOC
/******************************************************************************
** setWeBookModel                                                             *
** WeBook Manager Model
*******************************************************************************/
void MainWindow::setWeBookModel()
{
    if (isDebugMessage) qDebug() << "Set WeBook Model";
    //
    WeBooksCatFileFullPath = QString("%1%2%3").arg(qLoggerCommon->getFilelPath(), QDir::separator(), QLogger::ConstDefaultWeBookCatName);
    QFile WeBooksCatFile(WeBooksCatFileFullPath);
    if (WeBooksCatFile.exists())
    {
        openWeBookCat(WeBooksCatFileFullPath);
    }
    else
    {
        if (WeBooksCatFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        {
            QTextStream out(&WeBooksCatFile);
            out << constDefaultWeBook; // "WeBook\n"
            WeBooksCatFile.close();
            openWeBookCat(WeBooksCatFileFullPath);
        }
        else
        {
            qDebug() << "Error could not open file for reading: " << WeBooksCatFile.fileName() << " Error = " << WeBooksCatFile.errorString();
        }
    }
} // end setWeBookModel
/******************************************************************************
** openWeBookCat(QString thisFullPathFileName)                                *
*******************************************************************************/
bool MainWindow::openWeBookCat(QString thisFullPathFileName)
{
    QFile WeBooksCatFile(thisFullPathFileName);
    if (WeBooksCatFile.exists())
    {
        if (WeBooksCatFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QStringList stringList;
            QTextStream textStream(&WeBooksCatFile);
            while (true)
            {
                QString line = textStream.readLine();
                if (line.isNull() || line.isEmpty()) break;
                else stringList.append(line);
            }
            weBookMan = new WeBookMan(stringList);
            ui->listViewWeBookMan->setModel(weBookMan);
            WeBooksCatFile.close();
            return true;
        }
        else
        {
            qDebug() << "Error could not open file for reading: " << WeBooksCatFile.fileName() << " Error = " << WeBooksCatFile.errorString();
        }
    }
    return false;
} // end openWeBookCat
/******************************************************************************
** saveTabStates(int tabNumber)                                               *
** saveTabStates(TabFileMan)                                                  *
** Define all actions for specific tabs here                                  *
**                                                                            *
** 0 tabSettings                                                              *
** 1 tabConnectionMan                                                         *
** 2 tabWeBookMan                                                             *
** 3 tabTOC                                                                   *
** 4 tabEditor                                                                *
** 5 tabContacts                                                              *
** 6 tabFileMan                                                               *
** 7 tabCalendarMan                                                           *
** 8 tabCalculator                                                            *
*******************************************************************************/
void MainWindow::saveTabStates(int tabNumber)
{
    if (isDebugMessage) qDebug() << "saveTabStates";
    switch (tabNumber)
    {
        case TabSettings:       // 0
            break;
        case TabConnectionMan:  // 1
            break;
        case TabWeBookMan:      // 2
            break;
        case TabTOC:            // 3
            break;
        case TabEditor:         // 4
            myTabStates[tabNumber].stateOfAlignLeft = ui->actionAlignLeft->isEnabled();
            myTabStates[tabNumber].stateOfAlignRight = ui->actionAlignRight->isEnabled();
            myTabStates[tabNumber].stateOfAlignCenter = ui->actionAlignCenter->isEnabled();
            myTabStates[tabNumber].stateOfAlignJustify = ui->actionAlignJustify->isEnabled();
            myTabStates[tabNumber].stateOfCopy = ui->actionCopy->isEnabled();
            myTabStates[tabNumber].stateOfCut = ui->actionCut->isEnabled();
            myTabStates[tabNumber].stateOfIndentLess = ui->actionIndentLess->isEnabled();
            myTabStates[tabNumber].stateOfIndentMore = ui->actionIndentMore->isEnabled();
            myTabStates[tabNumber].stateOfNew = ui->actionNew->isEnabled();
            myTabStates[tabNumber].stateOfPaste = ui->actionPaste->isEnabled();
            myTabStates[tabNumber].stateOfPDF = ui->actionPDF->isEnabled();
            myTabStates[tabNumber].stateOfPrint = ui->actionPrint->isEnabled();
            myTabStates[tabNumber].stateOfRedo = ui->actionRedo->isEnabled();
            myTabStates[tabNumber].stateOfSave = ui->actionSave->isEnabled();
            myTabStates[tabNumber].stateOfTextBold = ui->actionTextBold->isEnabled();
            myTabStates[tabNumber].stateOfTextColor = ui->actionTextColor->isEnabled();
            myTabStates[tabNumber].stateOfTextItalic = ui->actionTextItalic->isEnabled();
            myTabStates[tabNumber].stateOfTextUnderline = ui->actionTextUnderline->isEnabled();
            myTabStates[tabNumber].stateOfToggleCheckState = ui->actionToggleCheckState->isEnabled();
            myTabStates[tabNumber].stateOfUndo = ui->actionUndo->isEnabled();
            break;
        case TabContacts:         // 5
            break;
        case TabFileMan:          // 6
            break;
        case TabCalendarMan:      // 7
            break;
        case TabCalculator:       // 8
            break;
    }
} // end saveTabStates
/******************************************************************************
** restoreTabStates(int tabNumber)                                            *
** restoreTabStates(TabFileMan)                                               *
**                                                                            *
** 0 tabSettings                                                              *
** 1 tabConnectionMan                                                         *
** 2 tabWeBookMan                                                             *
** 3 tabTOC                                                                   *
** 4 tabEditor                                                                *
** 5 tabContacts                                                              *
** 6 tabFileMan                                                               *
** 7 tabCalendarMan                                                           *
** 8 tabCalculator                                                            *
*******************************************************************************/
void MainWindow::restoreTabStates(int tabNumber)
{
    if (isDebugMessage) qDebug() << "restoreTabStates";
    switch (tabNumber)
    {
        case TabSettings:        // 0
            break;
        case TabConnectionMan:   // 1
            break;
        case TabWeBookMan:       // 2
            break;
        case TabTOC:             // 3
            break;
        case TabEditor:          // 4
            ui->actionAlignLeft->setEnabled(myTabStates[tabNumber].stateOfAlignLeft);
            ui->actionAlignRight->setEnabled(myTabStates[tabNumber].stateOfAlignRight);
            ui->actionAlignCenter->setEnabled(myTabStates[tabNumber].stateOfAlignCenter);
            ui->actionAlignJustify->setEnabled(myTabStates[tabNumber].stateOfAlignJustify);
            ui->actionCopy->setEnabled(myTabStates[tabNumber].stateOfCopy);
            ui->actionCut->setEnabled(myTabStates[tabNumber].stateOfCut);
            ui->actionIndentLess->setEnabled(myTabStates[tabNumber].stateOfIndentLess);
            ui->actionIndentMore->setEnabled(myTabStates[tabNumber].stateOfIndentMore);
            ui->actionNew->setEnabled(myTabStates[tabNumber].stateOfNew);
            ui->actionPaste->setEnabled(myTabStates[tabNumber].stateOfPaste);
            ui->actionPDF->setEnabled(myTabStates[tabNumber].stateOfPDF);
            ui->actionPrint->setEnabled(myTabStates[tabNumber].stateOfPrint);
            ui->actionRedo->setEnabled(myTabStates[tabNumber].stateOfRedo);
            ui->actionSave->setEnabled(myTabStates[tabNumber].stateOfSave);
            ui->actionTextBold->setEnabled(myTabStates[tabNumber].stateOfTextBold);
            ui->actionTextColor->setEnabled(myTabStates[tabNumber].stateOfTextColor);
            ui->actionTextItalic->setEnabled(myTabStates[tabNumber].stateOfTextItalic);
            ui->actionTextUnderline->setEnabled(myTabStates[tabNumber].stateOfTextUnderline);
            ui->actionToggleCheckState->setEnabled(myTabStates[tabNumber].stateOfToggleCheckState);
            ui->actionUndo->setEnabled(myTabStates[tabNumber].stateOfUndo);
            /*
            ui->actionCut->setEnabled(true);
            ui->actionNew->setEnabled(true);
            ui->actionPDF->setEnabled(true);
            ui->actionCopy->setEnabled(true);
            ui->actionRedo->setEnabled(true);
            ui->actionSave->setEnabled(true);
            ui->actionUndo->setEnabled(true);
            ui->actionPaste->setEnabled(true);
            ui->actionPrint->setEnabled(true);
            ui->actionTextBold->setEnabled(true);
            ui->actionAlignLeft->setEnabled(true);
            ui->actionDbConnect->setEnabled(true);
            ui->actionTextColor->setEnabled(true);
            ui->actionAlignRight->setEnabled(true);
            ui->actionIndentLess->setEnabled(true);
            ui->actionIndentMore->setEnabled(true);
            ui->actionTextItalic->setEnabled(true);
            ui->actionAlignCenter->setEnabled(true);
            ui->actionAlignJustify->setEnabled(true);
            ui->actionTextUnderline->setEnabled(true);
            ui->actionToggleCheckState->setEnabled(true);
            */
            comboStyle->setEnabled(true);
            comboFont->setEnabled(true);
            comboSize->setEnabled(true);
            break;
        case TabContacts:     // 5
            break;
        case TabFileMan:      // 6
            break;
        case TabCalendarMan:  // 7
            break;
        case TabCalculator:     // 8
            break;
    }
} // end restoreTabStates
/******************************************************************************
** onTabChanged for ui->tabWidget                                             *
** Define all actions for specific tabs here                                  *
**                                                                            *
** 0 tabSettings                                                              *
** 1 tabConnectionMan                                                         *
** 2 tabWeBookMan                                                             *
** 3 tabTOC                                                                   *
** 4 tabEditor                                                                *
** 5 tabContacts                                                              *
** 6 tabFileMan                                                               *
** 7 tabCalendarMan                                                           *
** 8 tabCalculator                                                            *
*******************************************************************************/
void MainWindow::onTabChanged(int tab)
{
    if (isDebugMessage) qDebug() << "onTabChanged=" << tab;
    disableAllMenuToolbarActions(tab);

    switch (tab)
    {
        case TabSettings:       // 0
            break;
        case TabConnectionMan:  // 1
            break;
        case TabWeBookMan:      // 2
            break;
        case TabTOC:            // 3
            break;
        case TabEditor:         // 4 not all of these should be enabled
            break;
        case TabContacts:       // 5
            break;
        case TabFileMan:        // 6
            break;
        case TabCalendarMan:    // 7
            break;
        case TabCalculator:     // 8
            break;
    } // end switch on tab
} // end onTabChanged
/******************************************************************************
** disableAllMenuToolbarActions                                               *
** Define all actions for all tabs here                                       *
*******************************************************************************/
void MainWindow::disableAllMenuToolbarActions(int tabNumber)
{
    if (isDebugMessage) qDebug() << "disableAllMenuToolbarActions";
    saveTabStates(lastTab);
    ui->actionAlignLeft->setEnabled(false);
    ui->actionAlignRight->setEnabled(false);
    ui->actionTextItalic->setEnabled(false);
    ui->actionAlignCenter->setEnabled(false);
    ui->actionAlignJustify->setEnabled(false);
    ui->actionCopy->setEnabled(false);
    ui->actionCut->setEnabled(false);
    ui->actionIndentLess->setEnabled(false);
    ui->actionIndentMore->setEnabled(false);
    ui->actionNew->setEnabled(false);
    ui->actionPaste->setEnabled(false);
    ui->actionPDF->setEnabled(false);
    ui->actionPrint->setEnabled(false);
    ui->actionRedo->setEnabled(false);
    ui->actionSave->setEnabled(false);
    ui->actionTextBold->setEnabled(false);
    ui->actionTextColor->setEnabled(false);
    ui->actionTextUnderline->setEnabled(false);
    ui->actionToggleCheckState->setEnabled(false);
    ui->actionUndo->setEnabled(false);
    comboStyle->setEnabled(false);
    comboFont->setEnabled(false);
    comboSize->setEnabled(false);
    lastTab = tabNumber;
    restoreTabStates(tabNumber);
} // end disableAllMenuToolbarActions
/******************************************************************************
** onSaveApplicationSettings                                                  *
*******************************************************************************/
void MainWindow::onSaveApplicationSettings()
{
    if (isDebugMessage) qDebug() << "onSaveApplicationSettings";

} // end onSaveApplicationSettings
/******************************************************************************
** setupTextActions                                                           *
*******************************************************************************/
void MainWindow::setupTextActions()
{
    if (isDebugMessage) qDebug() << "setupTextActions";

    ui->toolBar->addSeparator();
    QToolBar *tb = addToolBar(tr("Format Actions"));
    tb->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    addToolBarBreak(Qt::TopToolBarArea);
    addToolBar(tb);
    comboStyle = new QComboBox(tb);
    tb->addWidget(comboStyle);
    comboStyle->addItem("Standard");
    comboStyle->addItem("Bullet List (Disc)");
    comboStyle->addItem("Bullet List (Circle)");
    comboStyle->addItem("Bullet List (Square)");
    comboStyle->addItem("Task List (Unchecked)");
    comboStyle->addItem("Task List (Checked)");
    comboStyle->addItem("Ordered List (Decimal)");
    comboStyle->addItem("Ordered List (Alpha lower)");
    comboStyle->addItem("Ordered List (Alpha upper)");
    comboStyle->addItem("Ordered List (Roman lower)");
    comboStyle->addItem("Ordered List (Roman upper)");
    comboStyle->addItem("Heading 1");
    comboStyle->addItem("Heading 2");
    comboStyle->addItem("Heading 3");
    comboStyle->addItem("Heading 4");
    comboStyle->addItem("Heading 5");
    comboStyle->addItem("Heading 6");

    connect(comboStyle, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::onTextStyle);

    comboFont = new QFontComboBox(tb);
    tb->addWidget(comboFont);
    connect(comboFont, &QComboBox::textActivated, this, &MainWindow::onTextFamily);

    comboSize = new QComboBox(tb);
    comboSize->setObjectName("comboSize");
    tb->addWidget(comboSize);
    comboSize->setEditable(true);

    const QList<int> standardSizes = QFontDatabase::standardSizes();
    for (int size : standardSizes)   comboSize->addItem(QString::number(size));
    comboSize->setCurrentIndex(standardSizes.indexOf(QApplication::font().pointSize()));

    connect(comboSize, &QComboBox::textActivated, this, &MainWindow::onTextSize);
} // end setupTextActions
/******************************************************************************
** load                                                                       *
*******************************************************************************/
bool MainWindow::load(const QString &f)
{
    if (isDebugMessage) qDebug() << "load";

    if (!QFile::exists(f))           return false;
    QFile file(f);
    if (!file.open(QFile::ReadOnly)) return false;

    QByteArray data = file.readAll();
    QTextCodec *codec = Qt::codecForHtml(data);
    QString str = codec->toUnicode(data);
    if (Qt::mightBeRichText(str))
    {
        QUrl baseUrl = (f.front() == QLatin1Char(':') ? QUrl(f) : QUrl::fromLocalFile(f)).adjusted(QUrl::RemoveFilename);
        ui->textEdit->document()->setBaseUrl(baseUrl);
        ui->textEdit->setHtml(str);
    }
    else
    {
        // mimetypeapplication/vnd.oasis.opendocument.textPK
    #if QT_CONFIG(textmarkdownreader)
        QMimeDatabase db;
        if (db.mimeTypeForFileNameAndData(f, data).name() == QLatin1String("text/markdown"))
            ui->textEdit->setMarkdown(QString::fromUtf8(data));
        else
    #endif
            ui->textEdit->setPlainText(QString::fromUtf8(data));
    }

    setCurrentFileName(f);
    return true;
} // end load
/******************************************************************************
** setCurrentFileName                                                         *
*******************************************************************************/
void MainWindow::setCurrentFileName(const QString &thisFileName)
{
    if (isDebugMessage) qDebug() << "Set Current File Name=" << thisFileName;

    this->fullPathFileNameExt = thisFileName;
    ui->textEdit->document()->setModified(false);

    QString shownName;
    if (thisFileName.isEmpty()) shownName = getSetFullPathFileNameExt(thisFileName);
    else                        shownName = QFileInfo(thisFileName).fileName();

    setWindowTitle(tr("%1[*] - %2").arg(shownName, QApplication::applicationName()));
    setWindowModified(false);
} // end setCurrentFileName
/******************************************************************************
** maybeSave                                                                  *
*******************************************************************************/
bool MainWindow::maybeSave()
{
    if (isDebugMessage) qDebug() << "maybe Save is now just Save it Automatically";
    if (! ui->textEdit->document()->isModified())  return true;
    return onFileSave();
} // end maybeSave
/******************************************************************************
** getSetFullPathFileNameExt                                                  *
** Full Path to file
*******************************************************************************/
QString MainWindow::getSetFullPathFileNameExt(QString thisFileName)
{
    if (isDebugMessage) qDebug() << "Getter Setter fullPathFileNameExt";
    if (thisFileName.isNull() || thisFileName.isEmpty()) { thisFileName = myCurrentChapter; }
    if (thisFileName != myCurrentChapter)
    {
        if (isDebugMessage) qDebug() << "Getter Setter fullPathFileNameExt(myFileName=" << thisFileName << ") and myCurrentChapter=" << myCurrentChapter;
    }

    if (myCurrentBook.isEmpty())  getSetCurrentBook();
    if (myCurrentChapter.isEmpty()) getSetCurrentChapter();
    if (!myCurrentChapter.isEmpty()) thisFileName = myCurrentChapter;

    if (thisFileName.isEmpty())
    {
        if (isDebugMessage) qDebug() << "thisFileName and myCurrentChapter are empty";
    }
    // Setter
    fullPathFileNameExt = QString("%1%2%3%4%5.%6").arg(qLoggerCommon->getFilelPath(), QDir::separator(), myCurrentBook, QDir::separator(), thisFileName, constWeBookEditorExt);
    // Make Sure File and Path exist
    QFile booksResourceFile(fullPathFileNameExt);
    if (!booksResourceFile.exists())
    {
        QString myFolderName = QString("%1%2%3").arg(qLoggerCommon->getFilelPath(), QDir::separator(), myCurrentBook);
        if (!QDir(myFolderName).exists()) { QDir().mkdir(myFolderName); }
        if (booksResourceFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        {
            QTextStream out(&booksResourceFile);
            out << "\n";
            booksResourceFile.close();
        }
        else
        {
            qDebug() << "Error could not open file for writing: " << booksResourceFile.fileName() << " Error = " << booksResourceFile.errorString();
        }
    }
    // Getter
    return fullPathFileNameExt;
} // end getSetFullPathFileNameExt
/******************************************************************************
** onFileNew                                                                  *
*******************************************************************************/
void MainWindow::onFileNew()
{
    if (isDebugMessage) qDebug() << "onFileNew";
    if (maybeSave())
    {
        ui->textEdit->clear();
        setCurrentFileName(QString());
    }
} // end onFileNew
/******************************************************************************
** onFileOpen FIXME maybe import it                                           *
*******************************************************************************/
void MainWindow::onFileOpen()
{
    if (isDebugMessage) qDebug() << "onFileOpen";
    QFileDialog fileDialog(this, tr("Open File..."));
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setMimeTypeFilters(QStringList()
                              #if QT_CONFIG(texthtmlparser)
                                  << "text/html"
                              #endif
                              #if QT_CONFIG(textmarkdownreader)
                                  << "text/markdown"
                              #endif
                                  << "text/plain");
    if (fileDialog.exec() != QDialog::Accepted) return;
    const QString fn = fileDialog.selectedFiles().first();
    if (load(fn)) statusBar()->showMessage(tr("Opened \"%1\"").arg(QDir::toNativeSeparators(fn)));
    else          statusBar()->showMessage(tr("Could not open \"%1\"").arg(QDir::toNativeSeparators(fn)));
} // end onFileOpen
/******************************************************************************
** onFileSave                                                                 *
*******************************************************************************/
bool MainWindow::onFileSave()
{
    if (isDebugMessage) qDebug() << "on File Save";

    if (fullPathFileNameExt.isEmpty())  { getSetFullPathFileNameExt(""); }
    if (fullPathFileNameExt.startsWith(QStringLiteral(":/"))) { getSetFullPathFileNameExt(""); };

    QTextDocumentWriter writer(fullPathFileNameExt);
    /*
        Format	Description
        plaintext	Plain text
        HTML	HyperText Markup Language
        ODF	OpenDocument Format
        writer.setFormat("odf"); // same as ODF
        writer.setFormat("ODF"); // same as odf both fail
        writer.setFormat("plaintext"); // Did not try, its plaintext
    */
    writer.setFormat("HTML"); // Works, odf and ODF fails

    bool success = writer.write(ui->textEdit->document());
    if (success)
    {
        ui->textEdit->document()->setModified(false);
        statusBar()->showMessage(tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(fullPathFileNameExt)));
    }
    else
    {
        statusBar()->showMessage(tr("Could not write to file \"%1\"").arg(QDir::toNativeSeparators(fullPathFileNameExt)));
    }
    return success;
} // end onFileSave
/******************************************************************************
** onFileSaveAs                                                               *
*******************************************************************************/
bool MainWindow::onFileSaveAs()
{
    if (isDebugMessage) qDebug() << "onFileSaveAs";

    QFileDialog fileDialog(this, tr("Save as..."));
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    QStringList mimeTypes;
    mimeTypes << "text/plain"
             #if QT_CONFIG(textodfwriter)
              << "application/vnd.oasis.opendocument.text"
             #endif
             #if QT_CONFIG(textmarkdownwriter)
              << "text/markdown"
             #endif
              << "text/html";
    fileDialog.setMimeTypeFilters(mimeTypes);
    #if QT_CONFIG(textodfwriter)
        fileDialog.setDefaultSuffix("odt");
    #endif
    if (fileDialog.exec() != QDialog::Accepted)
        return false;
    const QString fn = fileDialog.selectedFiles().first();
    setCurrentFileName(fn);
    return onFileSave();
} // end onFileSaveAs
/******************************************************************************
** onFilePrint                                                                *
*******************************************************************************/
void MainWindow::onFilePrint()
{
    if (isDebugMessage) qDebug() << "onFilePrint";
    #if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printdialog)
        QPrinter printer(QPrinter::HighResolution);
        QPrintDialog *dlg = new QPrintDialog(&printer, this);
        if (ui->textEdit->textCursor().hasSelection()) dlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);
        dlg->setWindowTitle(tr("Print Document"));
        if (dlg->exec() == QDialog::Accepted) ui->textEdit->print(&printer);
        delete dlg;
    #endif
} // end onFilePrint
/******************************************************************************
** onFilePrintPreview                                                         *
*******************************************************************************/
void MainWindow::onFilePrintPreview()
{
    if (isDebugMessage) qDebug() << "onFilePrintPreview";
    #if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printpreviewdialog)
        QPrinter printer(QPrinter::HighResolution);
        QPrintPreviewDialog preview(&printer, this);
        connect(&preview, &QPrintPreviewDialog::paintRequested, this, &MainWindow::onPrintPreview);
        preview.exec();
    #endif
} // end onFilePrintPreview
/******************************************************************************
** onPrintPreview FIXME see below                                             *
*******************************************************************************/
void MainWindow::onPrintPreview(QPrinter *printer)
{
    if (isDebugMessage) qDebug() << "onPrintPreview";
    #if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
        ui->textEdit->print(printer);
    #else
        Q_UNUSED(printer)
    #endif
} // end onPrintPreview
/******************************************************************************
** onFilePrintPdf FIXME this only works on current page, add option to tree   *
*******************************************************************************/
void MainWindow::onFilePrintPdf()
{
    if (isDebugMessage) qDebug() << "onFilePrintPdf";
    #if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
        QFileDialog fileDialog(this, tr("Export PDF"));
        fileDialog.setAcceptMode(QFileDialog::AcceptSave);
        fileDialog.setMimeTypeFilters(QStringList("application/pdf"));
        fileDialog.setDefaultSuffix("pdf");
        if (fileDialog.exec() != QDialog::Accepted) return;
        QString fileName = fileDialog.selectedFiles().first();
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        ui->textEdit->document()->print(&printer);
        statusBar()->showMessage(tr("Exported \"%1\"").arg(QDir::toNativeSeparators(fileName)));
    #endif
} // end onFilePrintPdf
/******************************************************************************
** onTextBold                                                                 *
*******************************************************************************/
void MainWindow::onTextBold()
{
    if (isDebugMessage) qDebug() << "onTextBold";
    QTextCharFormat fmt;
    fmt.setFontWeight(ui->actionTextBold->isChecked() ? QFont::Bold : QFont::Normal);
    mergeFormatOnWordOrSelection(fmt);
} // end onTextBold
/******************************************************************************
** onTextUnderline                                                            *
*******************************************************************************/
void MainWindow::onTextUnderline()
{
    if (isDebugMessage) qDebug() << "onTextUnderline";
    QTextCharFormat fmt;
    fmt.setFontUnderline(ui->actionTextUnderline->isChecked());
    mergeFormatOnWordOrSelection(fmt);
} // end onTextUnderline
/******************************************************************************
** onTextItalic                                                               *
*******************************************************************************/
void MainWindow::onTextItalic()
{
    if (isDebugMessage) qDebug() << "onTextItalic";
    QTextCharFormat fmt;
    fmt.setFontItalic(ui->actionTextItalic->isChecked());
    mergeFormatOnWordOrSelection(fmt);
} // end onTextItalic
/******************************************************************************
** onTextFamily                                                               *
*******************************************************************************/
void MainWindow::onTextFamily(const QString &f)
{
    if (isDebugMessage) qDebug() << "onTextFamily=" << f;
    QTextCharFormat fmt;
    fmt.setFontFamily(f);
    mergeFormatOnWordOrSelection(fmt);
} // end onTextFamily
/******************************************************************************
** onTextSize                                                                 *
*******************************************************************************/
void MainWindow::onTextSize(const QString &p)
{
    if (isDebugMessage) qDebug() << "onTextSize=" << p;
    qreal pointSize = p.toFloat();
    if (p.toFloat() > 0)
    {
        QTextCharFormat fmt;
        fmt.setFontPointSize(pointSize);
        mergeFormatOnWordOrSelection(fmt);
    }
} // end onTextSize
/******************************************************************************
** onTextStyle                                                                *
*******************************************************************************/
void MainWindow::onTextStyle(int styleIndex)
{
    if (isDebugMessage) qDebug() << "onTextStyle=" << styleIndex;
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextListFormat::Style style = QTextListFormat::ListStyleUndefined;
    QTextBlockFormat::MarkerType marker = QTextBlockFormat::MarkerType::NoMarker;

    switch (styleIndex)
    {
        case 1:
            style = QTextListFormat::ListDisc;
            break;
        case 2:
            style = QTextListFormat::ListCircle;
            break;
        case 3:
            style = QTextListFormat::ListSquare;
            break;
        case 4:
            if (cursor.currentList()) style = cursor.currentList()->format().style();
            else                      style = QTextListFormat::ListDisc;
            marker = QTextBlockFormat::MarkerType::Unchecked;
            break;
        case 5:
            if (cursor.currentList()) style = cursor.currentList()->format().style();
            else                      style = QTextListFormat::ListDisc;
            marker = QTextBlockFormat::MarkerType::Checked;
            break;
        case 6:
            style = QTextListFormat::ListDecimal;
            break;
        case 7:
            style = QTextListFormat::ListLowerAlpha;
            break;
        case 8:
            style = QTextListFormat::ListUpperAlpha;
            break;
        case 9:
            style = QTextListFormat::ListLowerRoman;
            break;
        case 10:
            style = QTextListFormat::ListUpperRoman;
            break;
        default:
            break;
    }

    cursor.beginEditBlock();

    QTextBlockFormat blockFmt = cursor.blockFormat();

    if (style == QTextListFormat::ListStyleUndefined)
    {
        blockFmt.setObjectIndex(-1);
        int headingLevel = styleIndex >= 11 ? styleIndex - 11 + 1 : 0; // H1 to H6, or Standard
        blockFmt.setHeadingLevel(headingLevel);
        cursor.setBlockFormat(blockFmt);

        int sizeAdjustment = headingLevel ? 4 - headingLevel : 0; // H1 to H6: +3 to -2
        QTextCharFormat fmt;
        fmt.setFontWeight(headingLevel ? QFont::Bold : QFont::Normal);
        fmt.setProperty(QTextFormat::FontSizeAdjustment, sizeAdjustment);
        cursor.select(QTextCursor::LineUnderCursor);
        cursor.mergeCharFormat(fmt);
        ui->textEdit->mergeCurrentCharFormat(fmt);
    }
    else
    {
        blockFmt.setMarker(marker);
        cursor.setBlockFormat(blockFmt);
        QTextListFormat listFmt;
        if (cursor.currentList())
        {
            listFmt = cursor.currentList()->format();
        }
        else
        {
            listFmt.setIndent(blockFmt.indent() + 1);
            blockFmt.setIndent(0);
            cursor.setBlockFormat(blockFmt);
        }
        listFmt.setStyle(style);
        cursor.createList(listFmt);
    }

    cursor.endEditBlock();
} // end onTextStyle
/******************************************************************************
** onTextColor                                                                *
*******************************************************************************/
void MainWindow::onTextColor()
{
    if (isDebugMessage) qDebug() << "onTextColor";
    QColor col = QColorDialog::getColor(ui->textEdit->textColor(), this);
    if (!col.isValid()) return;
    QTextCharFormat fmt;
    fmt.setForeground(col);
    mergeFormatOnWordOrSelection(fmt);
    colorChanged(col);
} // end onTextColor
/******************************************************************************
** onTextAlign                                                                *
*******************************************************************************/
void MainWindow::onTextAlign(QAction *a)
{
    if (isDebugMessage) qDebug() << "onTextAlign=" << a;
    if (a == ui->actionAlignLeft)         ui->textEdit->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    else if (a == ui->actionAlignCenter)  ui->textEdit->setAlignment(Qt::AlignHCenter);
    else if (a == ui->actionAlignRight)   ui->textEdit->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
    else if (a == ui->actionAlignJustify) ui->textEdit->setAlignment(Qt::AlignJustify);
} // end onTextAlign
/******************************************************************************
** onSetChecked                                                               *
*******************************************************************************/
void MainWindow::onSetChecked(bool checked)
{
    if (isDebugMessage) qDebug() << "onSetChecked=" << checked;
    onTextStyle(checked ? 5 : 4);
} // end onSetChecked
/******************************************************************************
** onIndent                                                                   *
*******************************************************************************/
void MainWindow::onIndent()
{
    if (isDebugMessage) qDebug() << "onIndent";
    modifyIndentation(1);
} // end onIndent
/******************************************************************************
** onUnindent                                                                 *
*******************************************************************************/
void MainWindow::onUnindent()
{
    if (isDebugMessage) qDebug() << "onUnindent";
    modifyIndentation(-1);
} // end onUnindent
/******************************************************************************
** modifyIndentation                                                          *
*******************************************************************************/
void MainWindow::modifyIndentation(int amount)
{
    if (isDebugMessage) qDebug() << "modifyIndentation=" << amount;
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.beginEditBlock();
    if (cursor.currentList())
    {
        QTextListFormat listFmt = cursor.currentList()->format();
        // See whether the line above is the list we want to move this item into,
        // or whether we need a new list.
        QTextCursor above(cursor);
        above.movePosition(QTextCursor::Up);
        if (above.currentList() && listFmt.indent() + amount == above.currentList()->format().indent())
        {
            above.currentList()->add(cursor.block());
        }
        else
        {
            listFmt.setIndent(listFmt.indent() + amount);
            cursor.createList(listFmt);
        }
    }
    else
    {
        QTextBlockFormat blockFmt = cursor.blockFormat();
        blockFmt.setIndent(blockFmt.indent() + amount);
        cursor.setBlockFormat(blockFmt);
    }
    cursor.endEditBlock();
} // end modifyIndentation
/******************************************************************************
** currentCharFormatChanged                                                   *
*******************************************************************************/
void MainWindow::onCurrentCharFormatChanged(const QTextCharFormat &format)
{
    if (isDebugMessage) qDebug() << "currentCharFormatChanged=" << format;
    fontChanged(format.font());
    colorChanged(format.foreground().color());
} // end onCurrentCharFormatChanged
/******************************************************************************
** onCursorPositionChanged                                                    *
*******************************************************************************/
void MainWindow::onCursorPositionChanged()
{
    if (isDebugMessage) qDebug() << "onCursorPositionChanged";
    alignmentChanged(ui->textEdit->alignment());
    QTextList *list = ui->textEdit->textCursor().currentList();
    if (list)
    {
        switch (list->format().style())
        {
            case QTextListFormat::ListDisc:
                comboStyle->setCurrentIndex(1);
                break;
            case QTextListFormat::ListCircle:
                comboStyle->setCurrentIndex(2);
                break;
            case QTextListFormat::ListSquare:
                comboStyle->setCurrentIndex(3);
                break;
            case QTextListFormat::ListDecimal:
                comboStyle->setCurrentIndex(6);
                break;
            case QTextListFormat::ListLowerAlpha:
                comboStyle->setCurrentIndex(7);
                break;
            case QTextListFormat::ListUpperAlpha:
                comboStyle->setCurrentIndex(8);
                break;
            case QTextListFormat::ListLowerRoman:
                comboStyle->setCurrentIndex(9);
                break;
            case QTextListFormat::ListUpperRoman:
                comboStyle->setCurrentIndex(10);
                break;
            default:
                comboStyle->setCurrentIndex(-1);
                break;
        }
        switch (ui->textEdit->textCursor().block().blockFormat().marker())
        {
            case QTextBlockFormat::MarkerType::NoMarker:
                ui->actionToggleCheckState->setChecked(false);
                break;
            case QTextBlockFormat::MarkerType::Unchecked:
                comboStyle->setCurrentIndex(4);
                ui->actionToggleCheckState->setChecked(false);
                break;
            case QTextBlockFormat::MarkerType::Checked:
                comboStyle->setCurrentIndex(5);
                ui->actionToggleCheckState->setChecked(true);
                break;
        }
    }
    else
    {
        int headingLevel = ui->textEdit->textCursor().blockFormat().headingLevel();
        comboStyle->setCurrentIndex(headingLevel ? headingLevel + 10 : 0);
    }
} // end onCursorPositionChanged
/******************************************************************************
** onClipboardDataChanged                                                     *
*******************************************************************************/
void MainWindow::onClipboardDataChanged()
{
    if (isDebugMessage) qDebug() << "onClipboardDataChanged";
#ifndef QT_NO_CLIPBOARD
    if (const QMimeData *md = QApplication::clipboard()->mimeData()) ui->actionPaste->setEnabled(md->hasText());
#endif
} // end onClipboardDataChanged
/******************************************************************************
** mergeFormatOnWordOrSelection                                               *
*******************************************************************************/
void MainWindow::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    if (isDebugMessage) qDebug() << "mergeFormatOnWordOrSelection";
    QTextCursor cursor = ui->textEdit->textCursor();
    if (!cursor.hasSelection()) cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    ui->textEdit->mergeCurrentCharFormat(format);
} // end mergeFormatOnWordOrSelection
/******************************************************************************
** fontChanged                                                                *
*******************************************************************************/
void MainWindow::fontChanged(const QFont &f)
{
    if (isDebugMessage) qDebug() << "fontChanged=" << f;
    comboFont->setCurrentIndex(comboFont->findText(QFontInfo(f).family()));
    comboSize->setCurrentIndex(comboSize->findText(QString::number(f.pointSize())));
    ui->actionTextBold->setChecked(f.bold());
    ui->actionTextItalic->setChecked(f.italic());
    ui->actionTextUnderline->setChecked(f.underline());
} // end fontChanged
/******************************************************************************
** colorChanged                                                               *
*******************************************************************************/
void MainWindow::colorChanged(const QColor &c)
{
    if (isDebugMessage) qDebug() << "colorChanged=" << c;
    QPixmap pix(16, 16);
    pix.fill(c);
    ui->actionTextColor->setIcon(pix);
} // end colorChanged
/******************************************************************************
** alignmentChanged                                                           *
*******************************************************************************/
void MainWindow::alignmentChanged(Qt::Alignment a)
{
    if (isDebugMessage) qDebug() << "alignmentChanged=" << a;
    if (a & Qt::AlignLeft)         ui->actionAlignLeft->setChecked(true);
    else if (a & Qt::AlignHCenter) ui->actionAlignCenter->setChecked(true);
    else if (a & Qt::AlignRight)   ui->actionAlignRight->setChecked(true);
    else if (a & Qt::AlignJustify) ui->actionAlignJustify->setChecked(true);
} // end alignmentChanged
/******************************************************************************
** onAbout                                                                    *
*******************************************************************************/
void MainWindow::onAbout()
{
    if (isDebugMessage) qDebug() << "onAbout";
    AboutDialog *myAbout = new AboutDialog();
    myAbout->show();
} // end onAbout
/******************************************************************************
** onAddBook for ui->pushButtonWeBookManAdd                                   *
*******************************************************************************/
void MainWindow::onAddBook()
{
    if (isDebugMessage) qDebug() << "onAddBook";
    if (ui->editWeBookManTitle->text().isEmpty())
    {
        onStatusMessage("Title cannot be blank");
    }
    else
    {

        QModelIndex index = ui->listViewWeBookMan->selectionModel()->currentIndex();
        if (!ui->listViewWeBookMan->model()->insertRow(index.row()+1, index.parent())) return;
        const QModelIndex child = ui->listViewWeBookMan->model()->index(index.row() + 1, 0, index.parent());
        ui->listViewWeBookMan->model()->setData(child, QVariant(ui->editWeBookManTitle->text()), Qt::EditRole);
    }
} // end onAddBook
/******************************************************************************
** onDeleteBook for ui->pushButtonWeBookManDelete                             *
*******************************************************************************/
void MainWindow::onDeleteBook()
{
    if (isDebugMessage) qDebug() << "onDeleteBook";
    const QModelIndex index = ui->listViewWeBookMan->selectionModel()->currentIndex();
    QAbstractItemModel *model = ui->listViewWeBookMan->model();
    if (model->removeRow(index.row(), index.parent())) ui->listViewWeBookMan->repaint();
} // end onDeleteBook
/******************************************************************************
** onTocInsertChild                                                           *
*******************************************************************************/
void MainWindow::onTocInsertChild()
{
    const QModelIndex index = ui->treeViewTocView->selectionModel()->currentIndex();
    QAbstractItemModel *model = ui->treeViewTocView->model();

    if (model->columnCount(index) == 0)
    {
        if (!model->insertColumn(0, index)) return;
    }

    if (!model->insertRow(0, index)) return;

    for (int column = 0; column < model->columnCount(index); ++column)
    {
        const QModelIndex child = model->index(0, column, index);
        model->setData(child, QVariant(tr("[No data]")), Qt::EditRole);
        if (!model->headerData(column, Qt::Horizontal).isValid()) model->setHeaderData(column, Qt::Horizontal, QVariant(tr("[No header]")), Qt::EditRole);
    }

    ui->treeViewTocView->selectionModel()->setCurrentIndex(model->index(0, 0, index), QItemSelectionModel::ClearAndSelect);
    onTocUpdateActions();
} // end onTocInsertChild
/******************************************************************************
** onTocInsertColumn                                                          *
*******************************************************************************/
bool MainWindow::onTocInsertColumn()
{
    QAbstractItemModel *model = ui->treeViewTocView->model();
    int column = ui->treeViewTocView->selectionModel()->currentIndex().column();

    // Insert a column in the parent item.
    bool changed = model->insertColumn(column + 1);
    if (changed) model->setHeaderData(column + 1, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);

    onTocUpdateActions();

    return changed;
} // end onTocInsertColumn
/******************************************************************************
** onTocInsertRow                                                             *
*******************************************************************************/
void MainWindow::onTocInsertRow()
{
    const QModelIndex index = ui->treeViewTocView->selectionModel()->currentIndex();
    QAbstractItemModel *model = ui->treeViewTocView->model();

    if (!model->insertRow(index.row()+1, index.parent())) return;

    onTocUpdateActions();

    for (int column = 0; column < model->columnCount(index.parent()); ++column)
    {
        const QModelIndex child = model->index(index.row() + 1, column, index.parent());
        model->setData(child, QVariant(tr("[No data]")), Qt::EditRole);
    }
} // end onTocInsertRow
/******************************************************************************
** onTocRemoveColumn                                                          *
*******************************************************************************/
bool MainWindow::onTocRemoveColumn()
{
    QAbstractItemModel *model = ui->treeViewTocView->model();
    const int column = ui->treeViewTocView->selectionModel()->currentIndex().column();

    // Insert columns in each child of the parent item.
    const bool changed = model->removeColumn(column);
    if (changed) onTocUpdateActions();

    return changed;
} // end
/******************************************************************************
** onTocRemoveRow                                                             *
*******************************************************************************/
void MainWindow::onTocRemoveRow()
{
    const QModelIndex index = ui->treeViewTocView->selectionModel()->currentIndex();
    QAbstractItemModel *model = ui->treeViewTocView->model();
    if (model->removeRow(index.row(), index.parent())) onTocUpdateActions();
} // end onTocRemoveRow
/******************************************************************************
** onTocUpdateActions                                                         *
** If the Book changes so does the TOC                                        *
** If the Index changes, so does the Document                                 *
*******************************************************************************/
void MainWindow::onTocUpdateActions()
{
    const bool hasSelection = !ui->treeViewTocView->selectionModel()->selection().isEmpty();
    ui->actionTocRemoveRowAction->setEnabled(hasSelection);
    ui->actionTocRemoveColumnAction->setEnabled(hasSelection);

    const bool hasCurrent = ui->treeViewTocView->selectionModel()->currentIndex().isValid();
    ui->actionTocInsertRowAction->setEnabled(hasCurrent);
    ui->actionTocInsertColumnAction->setEnabled(hasCurrent);

    if (hasCurrent)
    {
        ui->treeViewTocView->closePersistentEditor(ui->treeViewTocView->selectionModel()->currentIndex());

        const int row = ui->treeViewTocView->selectionModel()->currentIndex().row();
        const int column = ui->treeViewTocView->selectionModel()->currentIndex().column();
        if (ui->treeViewTocView->selectionModel()->currentIndex().parent().isValid())
        { statusBar()->showMessage(tr("Position: (%1,%2)").arg(row, column)); }
        else
        { statusBar()->showMessage(tr("Position: (%1,%2) in top level").arg(row, column)); }
        loadDoc(getSetCurrentChapter());
    }
} // end onTocUpdateActions
/******************************************************************************
** loadDoc                                                                    *
*******************************************************************************/
void MainWindow::loadDoc(QString thisFileName)
{
    if (isDebugMessage) qDebug() << "load(" << thisFileName << ")";
    //
    if (!this->fullPathFileNameExt.isEmpty()) { onFileSave(); fullPathFileNameExt.clear(); }
    QString myFileName = QString("%1%2%3%4%5.%6").arg(qLoggerCommon->getFilelPath(), QDir::separator(), myCurrentBook, QDir::separator(), thisFileName, constWeBookEditorExt);
    QFile booksResourceFile(myFileName);
    if (!booksResourceFile.exists())
    {
        QString myFolderName = QString("%1%2%3").arg(qLoggerCommon->getFilelPath(), QDir::separator(), myCurrentBook);
        if (!QDir(myFolderName).exists()) { QDir().mkdir(myFolderName); }
        if (booksResourceFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        {
            QTextStream out(&booksResourceFile);
            out << "\n";
            booksResourceFile.close();
        }
        else
        {
            qDebug() << "Error could not open file for writing: " << booksResourceFile.fileName() << " Error = " << booksResourceFile.errorString();
        }
    }
    //
    load(myFileName); // Sets fileName
} // end loadDoc
/******************************************************************************
** getSetCurrentBook                                                          *
*******************************************************************************/
QString MainWindow::getSetCurrentBook()
{
    if (isDebugMessage) qDebug() << "getSetCurrentBook";
    myCurrentBook = ui->listViewWeBookMan->model()->data(ui->listViewWeBookMan->currentIndex(), Qt::DisplayRole).toString();
    return ui->listViewWeBookMan->model()->data(ui->listViewWeBookMan->currentIndex(), Qt::DisplayRole).toString();
} // end getSetCurrentBook
/******************************************************************************
** getSetCurrentChapter                                                       *
*******************************************************************************/
QString MainWindow::getSetCurrentChapter()
{
    if (isDebugMessage) qDebug() << "getSetCurrentChapter";
    myCurrentChapter = ui->treeViewTocView->model()->data(ui->treeViewTocView->currentIndex(), Qt::DisplayRole).toString();
    return myCurrentChapter;
} // end getSetCurrentChapter
/******************************************************************************
** loadTOC                                                                    *
*******************************************************************************/
void MainWindow::loadTOC()
{
    if (isDebugMessage) qDebug() << "load TOC";

    if (ui->listViewWeBookMan->selectionModel()->selection().isEmpty()) return;


    const bool hasCurrent = ui->listViewWeBookMan->selectionModel()->currentIndex().isValid();

    if (hasCurrent)
    {

        const int row = ui->listViewWeBookMan->selectionModel()->currentIndex().row();
        const int column = ui->listViewWeBookMan->selectionModel()->currentIndex().column();
        if (ui->listViewWeBookMan->selectionModel()->currentIndex().parent().isValid())
        { statusBar()->showMessage(tr("Position: (%1,%2)").arg(row, column));  }
        else
        { statusBar()->showMessage(tr("Position: (%1,%2) in top level").arg(row, column)); }
        QString myFileName = QString("%1%2%3.toc").arg(qLoggerCommon->getFilelPath(), QDir::separator(), getSetCurrentBook());
        setTocTreeViewModel(myFileName);
    }
} // end loadTOC
/******************************************************************************
** writeSettings                                                              *
** 1. Current Tab                                                             *
** 2. Current Book                                                            *
** 3. Current Chapter                                                         *
*******************************************************************************/
void MainWindow::writeSettings()
{
    if (isDebugMessage) qDebug() << "writeSettings";
    // Current Tab
    qLoggerCommon->setSetting(constCurrentTab, lastTab);
    // Current Book
    qLoggerCommon->setSetting(constCurrentWeBook, getSetCurrentBook());
    // Current Chapter
    qLoggerCommon->setSetting(constCurrentWeChapter, getSetCurrentChapter());
    // Geometry
    qLoggerCommon->setGeometry(pos(), size(), isMaximized(), isMinimized());
    //
    qLoggerCommon->setSetting(QLogger::ConstSettingsIniFileName, ui->editSettingsIniFileName->text());
    qLoggerCommon->setSetting(QLogger::ConstSettingsApplicationName, ui->editSettingsApplicationName->text());
    qLoggerCommon->setSetting(QLogger::ConstSettingsOrgName, ui->editSettingsOrgName->text());
    qLoggerCommon->setSetting(QLogger::ConstSettingsOrgDomain, ui->editSettingsOrgDomain->text());

    bookListItemsReturned = weBookMan->getData(); // Returns a String
    QFile booksResourceFile(WeBooksCatFileFullPath);
    if (booksResourceFile.exists())
    {
        if (isDebugMessage) qDebug() << "booksResourceFile.exists for writing: " << booksResourceFile.fileName();
        if (booksResourceFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        {
            if (isDebugMessage) qDebug() << "booksResourceFile.open for writing: " << booksResourceFile.fileName();
            QTextStream out(&booksResourceFile);
            out << bookListItemsReturned;
            booksResourceFile.close();
        }
        else
        {
            if (isDebugMessage) qDebug() << "Error could not write to file: " << booksResourceFile.fileName() << " Error = " << booksResourceFile.errorString();
        }
    }
    else
    {
        if (isDebugMessage) qDebug() << "Error books.txt file missing: " << booksResourceFile.fileName();
    }
    bookListItems = weBookMan->getStringList();
    for (int i = 0; i < bookListItems.count(); i++)
    {
        saveTOC(QString("%1%2%3.%4").arg(qLoggerCommon->getFilelPath(), QDir::separator(), bookListItems[i], "toc"));
    }
} // end writeSettings
/******************************************************************************
** readSettings                                                               *
** Do not use Setters, we do not want any events generated                    *
** Set all Variables used here                                                *
** 1. Current Tab                                                             *
** 2. Current Book                                                            *
** 3. Current Chapter                                                         *
**
*******************************************************************************/
void MainWindow::readSettings()
{
    if (isDebugMessage) qDebug() << "readSettings";
    // Current Tab
    currentTab = qLoggerCommon->getSetting(constCurrentTab, TabSettings).toInt();  // Defaults to Settings Tab
    // Current Book
    myCurrentBook = qLoggerCommon->getSetting(constCurrentWeBook, QLogger::ConstDefaultAppFolder).toString(); // Defaults to the same as the default folder name
    // Current Chapter
    myCurrentChapter = qLoggerCommon->getSetting(constCurrentWeChapter, myCurrentChapter).toString();
    // Geometry
    QSize mySize = qLoggerCommon->getGeometrySize(QLogger::ConstDefaultGeometrySize);
    QPoint myPos = qLoggerCommon->getGeometryPos(QLogger::ConstDefaultGeometryPos);
    resize(mySize);
    move(myPos);
    //
    if (isUiSet)
    {
        if(qLoggerCommon->getGeometryMax(isMaximized())) setWindowState(windowState() | Qt::WindowMaximized);
        if(qLoggerCommon->getGeometryMin(isMinimized())) setWindowState(windowState() | Qt::WindowMinimized);
    }
    //
    // Set Book Active
    bookListItems = weBookMan->getStringList();
    for (int i = 0; i < bookListItems.count(); i++)
    {
        if (bookListItems[i] == myCurrentBook)
        {
           ui->listViewWeBookMan->setCurrentIndex(ui->listViewWeBookMan->model()->index(i, 0, QModelIndex()));
           break;
        }
    }

    setTocTreeViewModel(myCurrentBook);
    // Set TOC Active
    ui->treeViewTocView->setCurrentIndex(dragDropTocModel->setActive(myCurrentChapter, QModelIndex()));
    // Switch to Edit Tab to set the states to save
    lastTab = TabEditor;
    ui->widgetTab->setCurrentIndex(TabEditor);
    saveTabStates(TabEditor);
    // if the Editor was not the last tab, switch now
    if (currentTab != TabEditor)
    {
        ui->widgetTab->setCurrentIndex(currentTab);
    }

} // end readSettings
/******************************************************************************
** saveTOC                                                                    *
*******************************************************************************/
void MainWindow::saveTOC(QString bookName)
{
    if (isDebugMessage) qDebug() << "saveTOC(" << bookName << ")";
    // Get Data from model
    treeListItemsReturned = dragDropTocModel->getData();
    // Create a new file since we will overwrite it
    qDebug() << "Current dir:" << QDir::currentPath();

    QFile booksResourceFile(bookName);
    if (booksResourceFile.exists())
    {
        qDebug() << "booksResourceFile.exists for writing: " << booksResourceFile.fileName();
        if (booksResourceFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) // Create File
        {
            qDebug() << "booksResourceFile.open for writing: " << booksResourceFile.fileName();
            QTextStream out(&booksResourceFile);
            out << treeListItemsReturned;
            qDebug() << "out = " << treeListItemsReturned;
            booksResourceFile.close();
        }
        else
        {
            qDebug() << "Error could not write to file: " << booksResourceFile.fileName() << " Error = " << booksResourceFile.errorString();
        }
    }
    else
    {
        qDebug() << "Error books.txt file missing: " << booksResourceFile.fileName();
    }
} // end saveTOC
/******************************************************************************
** onStatusMessage for handelStatusMessage                                    *
*******************************************************************************/
void MainWindow::onStatusMessage(const QString &message)
{
    if (isDebugMessage) qDebug() << "onStatusMessage=" << message;
    ui->statusbar->showMessage(tr(message.toUtf8()));
    if (isRunOnce)
    {
        isRunOnce = false;     // Makes this a Run Once
        isUiSet = true;        // Set to true since the UI is Set at this point
        // I wait to read Settings till after the UI is fully loaded
        readSettings();
        onTocUpdateActions();
    }
} // end onStatusMessage
/* ***************************** End of File ******************************* */

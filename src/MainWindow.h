/******************************************************************************
** WeBook: Pronounced Web Book, is a Book Content Management System  (BCMS)   *
*******************************************************************************/
#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QScreen>
#include <QMainWindow>
#include <QMap>
#include <QPointer>
#include <QToolBar>
#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QColorDialog>
#include <QComboBox>
#include <QCloseEvent>
#include <QDataWidgetMapper>
#include <QDir>
#include <QFontComboBox>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFontDatabase>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QMimeData>
#include <QMimeDatabase>
#include <QObject>
#include <QSettings>
#include <QStandardPaths>
#include <QStatusBar>
#include <QTextCodec>
#include <QTextEdit>
#include <QToolBar>
#include <QTextCursor>
#include <QTextDocumentWriter>
#include <QTextList>
#include <QWidget>
#include <QtWidgets>

#if defined(QT_PRINTSUPPORT_LIB)
    #include <QtPrintSupport/qtprintsupportglobal.h>
    #if QT_CONFIG(printer)
        #if QT_CONFIG(printdialog)
            #include <QPrintDialog>
        #endif
        #include <QPrinter>
        #if QT_CONFIG(printpreviewdialog)
            #include <QPrintPreviewDialog>
        #endif
    #endif
#endif

#include "QLogger/QLoggerCommon.h"
#include "QLogger/QLoggerCrypto.h"

#ifdef Q_OS_MAC
    const QString rsrcPath = ":/images/mac";
#else
    const QString rsrcPath = ":/images/win";
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QAction;
class QComboBox;
class QFontComboBox;
class QTextEdit;
class QTextCharFormat;
class QMenu;
class QPrinter;
class QToolButton;
QT_END_NAMESPACE


class ConnectionWidget;
QT_FORWARD_DECLARE_CLASS(QTableView)
QT_FORWARD_DECLARE_CLASS(QPushButton)
QT_FORWARD_DECLARE_CLASS(QTextEdit)
QT_FORWARD_DECLARE_CLASS(QSqlError)

#include "WeBookMan.h"
#include "TreeModel.h"
#include "TreeViewDragDropModel.h"
#include "AboutDialog.h"

// This file gets created at Build time
#include "ui_MainWindow.h"
/******************************************************************************
** MainWindow                                                                 *
*******************************************************************************/
class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
        // Tabs must be forced to be int 0 based indexes that match the actual ui for widgetTab, this enforces compile-time checks
        enum MainTabs             { TabSettings=0, TabConnectionMan=1, TabWeBookMan=2, TabTOC=3, TabEditor=4, TabContacts=5, TabFileMan=6, TabCalendarMan=7, TabCalculator=8};

        Q_ENUM(MainTabs)               // I enumerate the Tabs to make it easier to travers and save/restore setting
        // Track State Changes using these Constants using Settings
        const QString constCurrentTab            = "CurrentTab";       // Current Tab Number
        const QString constCurrentWeBook         = "CurrentWeBook";    // Name of WeBook Category file for default WeBook
        const QString constCurrentWeChapter      = "CurrentWeChapter"; // Name of WeBook Chapter file for default WeBook
        const QString constWeBookEditorExt       = "html";             // I do not like to hard code things, hoping for rtf, got odf, so HTML works
        //
        const QString constDefaultTOC            = "Home\tHome Page\n";//
        const QString constDefaultWeBook         = "WeBook\n";         //
        int defaultGeometryWidth     = 866;                                                 // Set from size of Form
        int defaultGeometryHeight    = 666;                                                 // Set from size of Form
        int defaultGeometryPositionX = 200;                                                 // Set X Postion
        int defaultGeometryPositionY = 200;                                                 // Set Y Postion
        // Public Functions

        bool load(const QString &f);                                                        // load HTML Document

    signals:
        void handelStatusMessage(const QString &message);                                   // onStatusMessage
        // Events that change QSettings trigger
        void handleEventAction(int eventValue);

    public slots:
        void onStatusMessage(const QString &message);                                       // handelStatusMessage

        void onTabChanged(int tab);                                                         // ui->tabWidget
        void onSaveApplicationSettings();                                                   // ui->pushButtonSgSave

        void onAddBook();                                                                   // ui->pushButtonWeBookManAdd
        void onDeleteBook();                                                                // ui->pushButtonWeBookManDelete
        void onFileNew();                                                                   // on File New
        //
        void onTocUpdateActions();

    protected:
        void closeEvent(QCloseEvent *e) override;                                           // close Event

    private slots:
        void onAbout();                                                                     // ui->actionAbout

        void onFileOpen();                                                                  // on File Open
        bool onFileSave();                                                                  // ui->actionSave
        bool onFileSaveAs();                                                                // on File SaveAs
        void onFilePrint();                                                                 // ui->actionPrint
        void onFilePrintPreview();                                                          // on File Print Preview
        void onFilePrintPdf();                                                              // on File Print Pdf

        void onTextBold();                                                                  // actionTextBold
        void onTextUnderline();                                                             // actionTextUnderline
        void onTextItalic();                                                                // actionTextItalic
        void onTextFamily(const QString &f);                                                // comboFont
        void onTextSize(const QString &p);                                                  // comboSize
        void onTextStyle(int styleIndex);                                                   // comboStyle
        void onTextColor();                                                                 // actionTextColor
        void onTextAlign(QAction *a);                                                       // actionAlignRight

        void onSetChecked(bool checked);                                                    // actionToggleCheckState

        void onIndent();                                                                    // on Indent
        void onUnindent();                                                                  // on Unindent

        void onCurrentCharFormatChanged(const QTextCharFormat &format);                     // on Current Char Format Changed
        void onCursorPositionChanged();                                                     // on Cursor Position Changed
        void onClipboardDataChanged();                                                      // on Clipboard Data Changed
        void onPrintPreview(QPrinter *);                                                    // on Print Preview
        //
        void onTocInsertChild();                                                            //
        bool onTocInsertColumn();                                                           //
        void onTocInsertRow();                                                              //
        bool onTocRemoveColumn();                                                           //
        void onTocRemoveRow();                                                              //

    private:
        // Track all Tab State Changes using this struct, for each bool is an action with its pattern name: actionCut = stateOfCut, action vs stateOf(action), I hate using the same name, confusing
        // The Edit Tab controls most of its own enbalbed states, but I like to save and restore them for a reason, the UI updates faster when it does not need to make changes
        typedef struct TabStates
        {
                bool stateOfCut;
                bool stateOfNew;
                bool stateOfPDF;
                bool stateOfCopy;
                bool stateOfRedo;
                bool stateOfSave;
                bool stateOfUndo;
                bool stateOfPaste;
                bool stateOfPrint;
                bool stateOfTextBold;
                bool stateOfAlignLeft;
                bool stateOfDbConnect;
                bool stateOfTextColor;
                bool stateOfAlignRight;
                bool stateOfIndentLess;
                bool stateOfIndentMore;
                bool stateOfTextItalic;
                bool stateOfAlignCenter;
                bool stateOfAlignJustify;
                bool stateOfTextUnderline;
                bool stateOfToggleCheckState;
        } TabStates;
        Ui::MainWindow          *ui                 = nullptr;                              // Pointer to mainwindow.ui
        WeBookMan               *weBookMan          = nullptr;                              // WeBookMan is a StringList Model
        TreeViewDragDropModel   *dragDropTocModel   = nullptr;                              // TOC Model
        QLogger::QLoggerCrypto  *weBookCrypto       = nullptr;                              // Crypto
        QLogger::QLoggerCommon  *qLoggerCommon      = nullptr;                              // Logging and QtSettings


        void setTocTreeViewModel(QString modelName);                                        //

        void setupTextActions();                                                            // setup Text Actions
        bool maybeSave();                                                                   // maybe Save, yes/no/cancel type of maybe
        void setCurrentFileName(const QString &thisFileName);                               // set Current FileName FIXME
        void modifyIndentation(int amount);                                                 // modify Indentation

        void mergeFormatOnWordOrSelection(const QTextCharFormat &format);                   // merge Format On Word Or Selection is used by many function to alter the text
        void fontChanged(const QFont &f);                                                   // font Changed
        void colorChanged(const QColor &c);                                                 // color Changed
        void alignmentChanged(Qt::Alignment a);                                             // alignment Changed
        void quitNow();                                                                     // quitNow not sure we need this FIXME
        void writeSettings();                                                               // Write Setting on Exit
        void readSettings();                                                                // Read Setting on Startup
        void saveTabStates(int tabNumber);                                                  // save    Tab States struct TabStates
        void restoreTabStates(int tabNumber);                                               // restore Tab States struct TabStates
        void disableAllMenuToolbarActions(int tabNumber);                                   // disable All Menu Toolbar Actions

        void setWeBookModel();
        //
        QComboBox               *comboStyle;                                                // Under Toolbar
        QFontComboBox           *comboFont;                                                 // Under Toolbar
        QComboBox               *comboSize;                                                 // Under Toolbar
        //
        QString                 fullPathFileNameExt = "";                                   // Full Path File Name.ext
        QString getSetFullPathFileNameExt(QString thisFileName);                            // Getter Setter fullPathFileNameExt
        bool                    isCloseCalled       = false;                                // Set on Quit
        bool                    isDebugMessage      = true;                                 // Set to true to show debug messages
        bool                    isDebugAllMessages  = true;                                 // Set to true to show debug messages
        bool                    isRunOnce           = true;                                 // is SQL Require Running is just one instance of its useage
        bool                    isUiSet             = false;                                // used during start up, when I need to use features that normal access the ui, that may not be available
        TabStates               myTabStates[7];                                             // used to track tab states
        int                     lastTab;                                                    // Keeps track of last tab
        int                     currentTab;                                                 // Keeps track of current tab
        QString                 myCurrentBook       = "";                                   // Current WeBook
        QString                 myCurrentChapter    = "";                                   // Current WeBook Chapter
        QString                 myUrlDownloadDataFile;                                      // Url Download Data File
        QString                 myDownloadDataPath;                                         // Download Data Path
        QStringList             bookListItems;                                              // weBookMan->getStringList();
        QString                 bookListItemsReturned;                                      // used to weBookMan->getData()
        QString                 treeListItemsReturned;                                      // treeListItemsReturned = dragDropModel->getData();
        QString                 WeBooksCatFileFullPath;                                     // Full Path to WeBooks.cat File constWeBookCatName
        void saveTOC(QString bookName);                                                     //
        void loadDoc(QString thisFileName);                                                 //
        void loadTOC();                                                                     //
        QString getSetCurrentBook();                                                        // Get the Current Book from WeBook Manager
        QString getSetCurrentChapter();                                                     // Get the Current File from TOC
        bool openWeBookCat(QString thisFullPathFileName);                                   // Open File and Read into Model
        bool openWeBookTOC(QString thisFullPathFileName);                                   // Open File and Read into Model
}; // end class MainWindow
#endif // MAINWINDOW_H
/* ***************************** End of File ******************************* */

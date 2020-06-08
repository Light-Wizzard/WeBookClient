/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionSave;
    QAction *actionPrint;
    QAction *actionPDF;
    QAction *actionQuit;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionTextBold;
    QAction *actionTextItalic;
    QAction *actionTextUnderline;
    QAction *actionAlignLeft;
    QAction *actionAlignCenter;
    QAction *actionAlignRight;
    QAction *actionAlignJustify;
    QAction *actionIndentMore;
    QAction *actionIndentLess;
    QAction *actionAbout;
    QAction *actionQt;
    QAction *actionToggleCheckState;
    QAction *actionTextColor;
    QAction *actionTocInsertRowAction;
    QAction *actionTocRemoveRowAction;
    QAction *actionTocInsertColumnAction;
    QAction *actionTocRemoveColumnAction;
    QAction *actionTocInsertChildAction;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *widgetTab;
    QWidget *tabSettings;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBoxSettingsGlobals;
    QVBoxLayout *verticalLayout_4;
    QFormLayout *formLayoutSg;
    QLabel *labelSettingsIniFileName;
    QLineEdit *editSettingsIniFileName;
    QLabel *labelSettingsApplicationName;
    QLineEdit *editSettingsApplicationName;
    QLabel *labelSettingsOrgName;
    QLineEdit *editSettingsOrgName;
    QLabel *labelSettingsOrgDomain;
    QLineEdit *editSettingsOrgDomain;
    QLabel *labelSettingsTravisURL;
    QLineEdit *editSettingsTravisURL;
    QLabel *labelSettingsAppVeyorURL;
    QLineEdit *editSettingsAppVeyorURL;
    QPushButton *pushButtonSgSave;
    QWidget *tabConnectionMan;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBoxConnectionManLocal;
    QFormLayout *formLayout_2;
    QPushButton *pushButtonConnectionManLocalPath;
    QLineEdit *editConnectionManLocalPath;
    QGroupBox *groupBoxConnectionManVPS;
    QFormLayout *formLayout;
    QLabel *labelConnectionManVpsIP;
    QLineEdit *editConnectionManVpsIP;
    QLabel *labelConnectionManVpsPort;
    QSpinBox *spinBoxConnectionManVpsPort;
    QLabel *labelConnectionManVpsUsername;
    QLineEdit *editConnectionManVpsUsername;
    QLabel *labelConnectionManVpsPassword;
    QLineEdit *editConnectionManVpsPassword;
    QLabel *labelConnectionManVpsDomainNameList;
    QLineEdit *editConnectionManVpsDomainNameList;
    QGroupBox *groupBoxConnectionManDC;
    QFormLayout *formLayout_3;
    QLabel *labelConnectionManDcIP;
    QLineEdit *editConnectionManDcIP;
    QLabel *labelConnectionManDcPort;
    QSpinBox *spinBoxConnectionManDcPort;
    QLabel *labelConnectionManDcUsername;
    QLineEdit *editConnectionNameDcUsername;
    QLabel *labelConnectionManDcPassword;
    QLineEdit *editConnectionManDcPassword;
    QLabel *labelConnectionManDcDomainNameList;
    QLineEdit *editConnectionManDcDomainNameList;
    QCheckBox *checkBoxConnectionManDC;
    QCheckBox *checkBoxConnectionManVPS;
    QWidget *tabWeBookMan;
    QGridLayout *gridLayout_8;
    QGridLayout *gridLayoutWeBookMan;
    QGroupBox *groupBoxWeBook;
    QVBoxLayout *groupBoxWeBookLayout;
    QListView *listViewWeBookMan;
    QGroupBox *groupBoxWeDetails;
    QFormLayout *_6;
    QLabel *labelWeBookManTitle;
    QLineEdit *editWeBookManTitle;
    QGroupBox *groupBoxControls;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonWeBookManAdd;
    QPushButton *pushButtonWeBookManDelete;
    QWidget *tabTOC;
    QGridLayout *gridLayout_9;
    QTreeView *treeViewTocView;
    QWidget *tabEditor;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *textEdit;
    QWidget *tabContacts;
    QVBoxLayout *verticalLayout_5;
    QWidget *tabFileMan;
    QGridLayout *gridLayout_2;
    QWidget *tabCalendarMan;
    QGridLayout *gridLayout_7;
    QCalendarWidget *calendarWidget;
    QWidget *tabCalculator;
    QMenuBar *menubar;
    QMenu *menuChapter;
    QMenu *menuEdit;
    QMenu *menuFormat;
    QMenu *menuHelp;
    QMenu *menuInsert;
    QMenu *menuTOC;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(866, 734);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("document-new");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8(":/images/win/filenew.png"), QSize(), QIcon::Normal, QIcon::On);
        }
        actionNew->setIcon(icon);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave->setEnabled(false);
        QIcon icon1;
        iconThemeName = QString::fromUtf8("document-save");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QString::fromUtf8(":/images/win/filesave.png"), QSize(), QIcon::Normal, QIcon::On);
        }
        actionSave->setIcon(icon1);
        actionPrint = new QAction(MainWindow);
        actionPrint->setObjectName(QString::fromUtf8("actionPrint"));
        QIcon icon2;
        iconThemeName = QString::fromUtf8("document-print");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QString::fromUtf8(":/images/win/fileprint.png"), QSize(), QIcon::Normal, QIcon::On);
        }
        actionPrint->setIcon(icon2);
        actionPDF = new QAction(MainWindow);
        actionPDF->setObjectName(QString::fromUtf8("actionPDF"));
        QIcon icon3;
        iconThemeName = QString::fromUtf8("exportpdf");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon3 = QIcon::fromTheme(iconThemeName);
        } else {
            icon3.addFile(QString::fromUtf8(":/images/win/exportpdf.png"), QSize(), QIcon::Normal, QIcon::On);
        }
        actionPDF->setIcon(icon3);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        QIcon icon4;
        iconThemeName = QString::fromUtf8("application-exit");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon4 = QIcon::fromTheme(iconThemeName);
        } else {
            icon4.addFile(QString::fromUtf8(":/images/win/exit.png"), QSize(), QIcon::Normal, QIcon::On);
        }
        actionQuit->setIcon(icon4);
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        QIcon icon5;
        iconThemeName = QString::fromUtf8("edit-undo");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon5 = QIcon::fromTheme(iconThemeName);
        } else {
            icon5.addFile(QString::fromUtf8(":/images/win/editundo.png"), QSize(), QIcon::Normal, QIcon::On);
        }
        actionUndo->setIcon(icon5);
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        QIcon icon6;
        iconThemeName = QString::fromUtf8("edit-redo");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon6 = QIcon::fromTheme(iconThemeName);
        } else {
            icon6.addFile(QString::fromUtf8(":/images/win/editredo.png"), QSize(), QIcon::Normal, QIcon::On);
        }
        actionRedo->setIcon(icon6);
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName(QString::fromUtf8("actionCut"));
        QIcon icon7;
        iconThemeName = QString::fromUtf8("edit-cut");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon7 = QIcon::fromTheme(iconThemeName);
        } else {
            icon7.addFile(QString::fromUtf8(":/images/win/editcut.png"), QSize(), QIcon::Normal, QIcon::On);
        }
        actionCut->setIcon(icon7);
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        QIcon icon8;
        iconThemeName = QString::fromUtf8("edit-copy");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon8 = QIcon::fromTheme(iconThemeName);
        } else {
            icon8.addFile(QString::fromUtf8(":/images/win/editcopy.png"), QSize(), QIcon::Normal, QIcon::On);
        }
        actionCopy->setIcon(icon8);
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        QIcon icon9;
        iconThemeName = QString::fromUtf8("edit-paste");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon9 = QIcon::fromTheme(iconThemeName);
        } else {
            icon9.addFile(QString::fromUtf8(":/images/win/editpaste.png"), QSize(), QIcon::Normal, QIcon::On);
        }
        actionPaste->setIcon(icon9);
        actionTextBold = new QAction(MainWindow);
        actionTextBold->setObjectName(QString::fromUtf8("actionTextBold"));
        actionTextBold->setCheckable(true);
        QIcon icon10;
        iconThemeName = QString::fromUtf8("format-text-bold");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon10 = QIcon::fromTheme(iconThemeName);
        } else {
            icon10.addFile(QString::fromUtf8(":/images/win/textbold.png"), QSize(), QIcon::Normal, QIcon::On);
        }
        actionTextBold->setIcon(icon10);
        actionTextItalic = new QAction(MainWindow);
        actionTextItalic->setObjectName(QString::fromUtf8("actionTextItalic"));
        actionTextItalic->setCheckable(true);
        QIcon icon11;
        iconThemeName = QString::fromUtf8("format-text-italic");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon11 = QIcon::fromTheme(iconThemeName);
        } else {
            icon11.addFile(QString::fromUtf8(":/images/win/textitalic.png"), QSize(), QIcon::Normal, QIcon::On);
        }
        actionTextItalic->setIcon(icon11);
        actionTextUnderline = new QAction(MainWindow);
        actionTextUnderline->setObjectName(QString::fromUtf8("actionTextUnderline"));
        actionTextUnderline->setCheckable(true);
        QIcon icon12;
        iconThemeName = QString::fromUtf8("format-text-underline");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon12 = QIcon::fromTheme(iconThemeName);
        } else {
            icon12.addFile(QString::fromUtf8(":/images/win/textunder.png"), QSize(), QIcon::Normal, QIcon::On);
        }
        actionTextUnderline->setIcon(icon12);
        actionAlignLeft = new QAction(MainWindow);
        actionAlignLeft->setObjectName(QString::fromUtf8("actionAlignLeft"));
        QIcon icon13;
        iconThemeName = QString::fromUtf8("format-justify-left");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon13 = QIcon::fromTheme(iconThemeName);
        } else {
            icon13.addFile(QString::fromUtf8(":/images/win/textleft.png"), QSize(), QIcon::Normal, QIcon::On);
        }
        actionAlignLeft->setIcon(icon13);
        actionAlignCenter = new QAction(MainWindow);
        actionAlignCenter->setObjectName(QString::fromUtf8("actionAlignCenter"));
        QIcon icon14;
        iconThemeName = QString::fromUtf8("format-justify-center");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon14 = QIcon::fromTheme(iconThemeName);
        } else {
            icon14.addFile(QString::fromUtf8(":/images/win/textcenter.png"), QSize(), QIcon::Normal, QIcon::On);
        }
        actionAlignCenter->setIcon(icon14);
        actionAlignRight = new QAction(MainWindow);
        actionAlignRight->setObjectName(QString::fromUtf8("actionAlignRight"));
        QIcon icon15;
        iconThemeName = QString::fromUtf8("format-justify-right");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon15 = QIcon::fromTheme(iconThemeName);
        } else {
            icon15.addFile(QString::fromUtf8(":/images/win/textright.png"), QSize(), QIcon::Normal, QIcon::On);
        }
        actionAlignRight->setIcon(icon15);
        actionAlignJustify = new QAction(MainWindow);
        actionAlignJustify->setObjectName(QString::fromUtf8("actionAlignJustify"));
        QIcon icon16;
        iconThemeName = QString::fromUtf8("format-justify-fill");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon16 = QIcon::fromTheme(iconThemeName);
        } else {
            icon16.addFile(QString::fromUtf8(":/images/win/textjustify.png"), QSize(), QIcon::Normal, QIcon::On);
        }
        actionAlignJustify->setIcon(icon16);
        actionIndentMore = new QAction(MainWindow);
        actionIndentMore->setObjectName(QString::fromUtf8("actionIndentMore"));
        QIcon icon17;
        iconThemeName = QString::fromUtf8("format-indent-more");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon17 = QIcon::fromTheme(iconThemeName);
        } else {
            icon17.addFile(QString::fromUtf8(":/images/win/format-indent-more.png"), QSize(), QIcon::Normal, QIcon::On);
        }
        actionIndentMore->setIcon(icon17);
        actionIndentLess = new QAction(MainWindow);
        actionIndentLess->setObjectName(QString::fromUtf8("actionIndentLess"));
        QIcon icon18;
        iconThemeName = QString::fromUtf8("format-indent-less");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon18 = QIcon::fromTheme(iconThemeName);
        } else {
            icon18.addFile(QString::fromUtf8(":/images/win/format-indent-less.png"), QSize(), QIcon::Normal, QIcon::On);
        }
        actionIndentLess->setIcon(icon18);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        QIcon icon19;
        iconThemeName = QString::fromUtf8("help-about");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon19 = QIcon::fromTheme(iconThemeName);
        } else {
            icon19.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionAbout->setIcon(icon19);
        actionQt = new QAction(MainWindow);
        actionQt->setObjectName(QString::fromUtf8("actionQt"));
        QIcon icon20;
        iconThemeName = QString::fromUtf8("help-contents");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon20 = QIcon::fromTheme(iconThemeName);
        } else {
            icon20.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionQt->setIcon(icon20);
        actionToggleCheckState = new QAction(MainWindow);
        actionToggleCheckState->setObjectName(QString::fromUtf8("actionToggleCheckState"));
        actionToggleCheckState->setCheckable(true);
        QIcon icon21;
        iconThemeName = QString::fromUtf8("status-checkbox-checked");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon21 = QIcon::fromTheme(iconThemeName);
        } else {
            icon21.addFile(QString::fromUtf8(":/images/win/checkbox-checked.png"), QSize(), QIcon::Normal, QIcon::On);
        }
        actionToggleCheckState->setIcon(icon21);
        actionTextColor = new QAction(MainWindow);
        actionTextColor->setObjectName(QString::fromUtf8("actionTextColor"));
        QIcon icon22;
        icon22.addFile(QString::fromUtf8(":/images/win/colorwheel.png"), QSize(), QIcon::Normal, QIcon::On);
        actionTextColor->setIcon(icon22);
        actionTocInsertRowAction = new QAction(MainWindow);
        actionTocInsertRowAction->setObjectName(QString::fromUtf8("actionTocInsertRowAction"));
        QIcon icon23;
        icon23.addFile(QString::fromUtf8(":/images/win/filenew.png"), QSize(), QIcon::Normal, QIcon::On);
        actionTocInsertRowAction->setIcon(icon23);
        actionTocRemoveRowAction = new QAction(MainWindow);
        actionTocRemoveRowAction->setObjectName(QString::fromUtf8("actionTocRemoveRowAction"));
        QIcon icon24;
        icon24.addFile(QString::fromUtf8(":/images/win/remove_from_basket.png"), QSize(), QIcon::Normal, QIcon::On);
        actionTocRemoveRowAction->setIcon(icon24);
        actionTocInsertColumnAction = new QAction(MainWindow);
        actionTocInsertColumnAction->setObjectName(QString::fromUtf8("actionTocInsertColumnAction"));
        QIcon icon25;
        icon25.addFile(QString::fromUtf8(":/images/win/lists.png"), QSize(), QIcon::Normal, QIcon::On);
        actionTocInsertColumnAction->setIcon(icon25);
        actionTocRemoveColumnAction = new QAction(MainWindow);
        actionTocRemoveColumnAction->setObjectName(QString::fromUtf8("actionTocRemoveColumnAction"));
        QIcon icon26;
        icon26.addFile(QString::fromUtf8(":/images/win/disconnect.png"), QSize(), QIcon::Normal, QIcon::On);
        actionTocRemoveColumnAction->setIcon(icon26);
        actionTocInsertChildAction = new QAction(MainWindow);
        actionTocInsertChildAction->setObjectName(QString::fromUtf8("actionTocInsertChildAction"));
        QIcon icon27;
        icon27.addFile(QString::fromUtf8(":/images/win/hierarchy.png"), QSize(), QIcon::Normal, QIcon::On);
        actionTocInsertChildAction->setIcon(icon27);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widgetTab = new QTabWidget(centralwidget);
        widgetTab->setObjectName(QString::fromUtf8("widgetTab"));
        tabSettings = new QWidget();
        tabSettings->setObjectName(QString::fromUtf8("tabSettings"));
        verticalLayout_3 = new QVBoxLayout(tabSettings);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBoxSettingsGlobals = new QGroupBox(tabSettings);
        groupBoxSettingsGlobals->setObjectName(QString::fromUtf8("groupBoxSettingsGlobals"));
        groupBoxSettingsGlobals->setEnabled(true);
        verticalLayout_4 = new QVBoxLayout(groupBoxSettingsGlobals);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        formLayoutSg = new QFormLayout();
        formLayoutSg->setObjectName(QString::fromUtf8("formLayoutSg"));
        formLayoutSg->setSizeConstraint(QLayout::SetNoConstraint);
        labelSettingsIniFileName = new QLabel(groupBoxSettingsGlobals);
        labelSettingsIniFileName->setObjectName(QString::fromUtf8("labelSettingsIniFileName"));

        formLayoutSg->setWidget(0, QFormLayout::LabelRole, labelSettingsIniFileName);

        editSettingsIniFileName = new QLineEdit(groupBoxSettingsGlobals);
        editSettingsIniFileName->setObjectName(QString::fromUtf8("editSettingsIniFileName"));

        formLayoutSg->setWidget(0, QFormLayout::FieldRole, editSettingsIniFileName);

        labelSettingsApplicationName = new QLabel(groupBoxSettingsGlobals);
        labelSettingsApplicationName->setObjectName(QString::fromUtf8("labelSettingsApplicationName"));

        formLayoutSg->setWidget(1, QFormLayout::LabelRole, labelSettingsApplicationName);

        editSettingsApplicationName = new QLineEdit(groupBoxSettingsGlobals);
        editSettingsApplicationName->setObjectName(QString::fromUtf8("editSettingsApplicationName"));

        formLayoutSg->setWidget(1, QFormLayout::FieldRole, editSettingsApplicationName);

        labelSettingsOrgName = new QLabel(groupBoxSettingsGlobals);
        labelSettingsOrgName->setObjectName(QString::fromUtf8("labelSettingsOrgName"));

        formLayoutSg->setWidget(2, QFormLayout::LabelRole, labelSettingsOrgName);

        editSettingsOrgName = new QLineEdit(groupBoxSettingsGlobals);
        editSettingsOrgName->setObjectName(QString::fromUtf8("editSettingsOrgName"));

        formLayoutSg->setWidget(2, QFormLayout::FieldRole, editSettingsOrgName);

        labelSettingsOrgDomain = new QLabel(groupBoxSettingsGlobals);
        labelSettingsOrgDomain->setObjectName(QString::fromUtf8("labelSettingsOrgDomain"));

        formLayoutSg->setWidget(3, QFormLayout::LabelRole, labelSettingsOrgDomain);

        editSettingsOrgDomain = new QLineEdit(groupBoxSettingsGlobals);
        editSettingsOrgDomain->setObjectName(QString::fromUtf8("editSettingsOrgDomain"));

        formLayoutSg->setWidget(3, QFormLayout::FieldRole, editSettingsOrgDomain);

        labelSettingsTravisURL = new QLabel(groupBoxSettingsGlobals);
        labelSettingsTravisURL->setObjectName(QString::fromUtf8("labelSettingsTravisURL"));

        formLayoutSg->setWidget(4, QFormLayout::LabelRole, labelSettingsTravisURL);

        editSettingsTravisURL = new QLineEdit(groupBoxSettingsGlobals);
        editSettingsTravisURL->setObjectName(QString::fromUtf8("editSettingsTravisURL"));

        formLayoutSg->setWidget(4, QFormLayout::FieldRole, editSettingsTravisURL);

        labelSettingsAppVeyorURL = new QLabel(groupBoxSettingsGlobals);
        labelSettingsAppVeyorURL->setObjectName(QString::fromUtf8("labelSettingsAppVeyorURL"));

        formLayoutSg->setWidget(5, QFormLayout::LabelRole, labelSettingsAppVeyorURL);

        editSettingsAppVeyorURL = new QLineEdit(groupBoxSettingsGlobals);
        editSettingsAppVeyorURL->setObjectName(QString::fromUtf8("editSettingsAppVeyorURL"));

        formLayoutSg->setWidget(5, QFormLayout::FieldRole, editSettingsAppVeyorURL);


        verticalLayout_4->addLayout(formLayoutSg);

        pushButtonSgSave = new QPushButton(groupBoxSettingsGlobals);
        pushButtonSgSave->setObjectName(QString::fromUtf8("pushButtonSgSave"));

        verticalLayout_4->addWidget(pushButtonSgSave);


        verticalLayout_3->addWidget(groupBoxSettingsGlobals);

        widgetTab->addTab(tabSettings, QString());
        tabConnectionMan = new QWidget();
        tabConnectionMan->setObjectName(QString::fromUtf8("tabConnectionMan"));
        verticalLayout_6 = new QVBoxLayout(tabConnectionMan);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        groupBoxConnectionManLocal = new QGroupBox(tabConnectionMan);
        groupBoxConnectionManLocal->setObjectName(QString::fromUtf8("groupBoxConnectionManLocal"));
        formLayout_2 = new QFormLayout(groupBoxConnectionManLocal);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        pushButtonConnectionManLocalPath = new QPushButton(groupBoxConnectionManLocal);
        pushButtonConnectionManLocalPath->setObjectName(QString::fromUtf8("pushButtonConnectionManLocalPath"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, pushButtonConnectionManLocalPath);

        editConnectionManLocalPath = new QLineEdit(groupBoxConnectionManLocal);
        editConnectionManLocalPath->setObjectName(QString::fromUtf8("editConnectionManLocalPath"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, editConnectionManLocalPath);


        verticalLayout_6->addWidget(groupBoxConnectionManLocal);

        groupBoxConnectionManVPS = new QGroupBox(tabConnectionMan);
        groupBoxConnectionManVPS->setObjectName(QString::fromUtf8("groupBoxConnectionManVPS"));
        formLayout = new QFormLayout(groupBoxConnectionManVPS);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setHorizontalSpacing(6);
        formLayout->setVerticalSpacing(6);
        formLayout->setContentsMargins(8, 8, 8, 8);
        labelConnectionManVpsIP = new QLabel(groupBoxConnectionManVPS);
        labelConnectionManVpsIP->setObjectName(QString::fromUtf8("labelConnectionManVpsIP"));

        formLayout->setWidget(0, QFormLayout::LabelRole, labelConnectionManVpsIP);

        editConnectionManVpsIP = new QLineEdit(groupBoxConnectionManVPS);
        editConnectionManVpsIP->setObjectName(QString::fromUtf8("editConnectionManVpsIP"));

        formLayout->setWidget(0, QFormLayout::FieldRole, editConnectionManVpsIP);

        labelConnectionManVpsPort = new QLabel(groupBoxConnectionManVPS);
        labelConnectionManVpsPort->setObjectName(QString::fromUtf8("labelConnectionManVpsPort"));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelConnectionManVpsPort);

        spinBoxConnectionManVpsPort = new QSpinBox(groupBoxConnectionManVPS);
        spinBoxConnectionManVpsPort->setObjectName(QString::fromUtf8("spinBoxConnectionManVpsPort"));

        formLayout->setWidget(1, QFormLayout::FieldRole, spinBoxConnectionManVpsPort);

        labelConnectionManVpsUsername = new QLabel(groupBoxConnectionManVPS);
        labelConnectionManVpsUsername->setObjectName(QString::fromUtf8("labelConnectionManVpsUsername"));

        formLayout->setWidget(2, QFormLayout::LabelRole, labelConnectionManVpsUsername);

        editConnectionManVpsUsername = new QLineEdit(groupBoxConnectionManVPS);
        editConnectionManVpsUsername->setObjectName(QString::fromUtf8("editConnectionManVpsUsername"));

        formLayout->setWidget(2, QFormLayout::FieldRole, editConnectionManVpsUsername);

        labelConnectionManVpsPassword = new QLabel(groupBoxConnectionManVPS);
        labelConnectionManVpsPassword->setObjectName(QString::fromUtf8("labelConnectionManVpsPassword"));

        formLayout->setWidget(3, QFormLayout::LabelRole, labelConnectionManVpsPassword);

        editConnectionManVpsPassword = new QLineEdit(groupBoxConnectionManVPS);
        editConnectionManVpsPassword->setObjectName(QString::fromUtf8("editConnectionManVpsPassword"));
        editConnectionManVpsPassword->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(3, QFormLayout::FieldRole, editConnectionManVpsPassword);

        labelConnectionManVpsDomainNameList = new QLabel(groupBoxConnectionManVPS);
        labelConnectionManVpsDomainNameList->setObjectName(QString::fromUtf8("labelConnectionManVpsDomainNameList"));

        formLayout->setWidget(4, QFormLayout::LabelRole, labelConnectionManVpsDomainNameList);

        editConnectionManVpsDomainNameList = new QLineEdit(groupBoxConnectionManVPS);
        editConnectionManVpsDomainNameList->setObjectName(QString::fromUtf8("editConnectionManVpsDomainNameList"));

        formLayout->setWidget(4, QFormLayout::FieldRole, editConnectionManVpsDomainNameList);


        verticalLayout_6->addWidget(groupBoxConnectionManVPS);

        groupBoxConnectionManDC = new QGroupBox(tabConnectionMan);
        groupBoxConnectionManDC->setObjectName(QString::fromUtf8("groupBoxConnectionManDC"));
        formLayout_3 = new QFormLayout(groupBoxConnectionManDC);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        labelConnectionManDcIP = new QLabel(groupBoxConnectionManDC);
        labelConnectionManDcIP->setObjectName(QString::fromUtf8("labelConnectionManDcIP"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, labelConnectionManDcIP);

        editConnectionManDcIP = new QLineEdit(groupBoxConnectionManDC);
        editConnectionManDcIP->setObjectName(QString::fromUtf8("editConnectionManDcIP"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, editConnectionManDcIP);

        labelConnectionManDcPort = new QLabel(groupBoxConnectionManDC);
        labelConnectionManDcPort->setObjectName(QString::fromUtf8("labelConnectionManDcPort"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, labelConnectionManDcPort);

        spinBoxConnectionManDcPort = new QSpinBox(groupBoxConnectionManDC);
        spinBoxConnectionManDcPort->setObjectName(QString::fromUtf8("spinBoxConnectionManDcPort"));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, spinBoxConnectionManDcPort);

        labelConnectionManDcUsername = new QLabel(groupBoxConnectionManDC);
        labelConnectionManDcUsername->setObjectName(QString::fromUtf8("labelConnectionManDcUsername"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, labelConnectionManDcUsername);

        editConnectionNameDcUsername = new QLineEdit(groupBoxConnectionManDC);
        editConnectionNameDcUsername->setObjectName(QString::fromUtf8("editConnectionNameDcUsername"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, editConnectionNameDcUsername);

        labelConnectionManDcPassword = new QLabel(groupBoxConnectionManDC);
        labelConnectionManDcPassword->setObjectName(QString::fromUtf8("labelConnectionManDcPassword"));

        formLayout_3->setWidget(3, QFormLayout::LabelRole, labelConnectionManDcPassword);

        editConnectionManDcPassword = new QLineEdit(groupBoxConnectionManDC);
        editConnectionManDcPassword->setObjectName(QString::fromUtf8("editConnectionManDcPassword"));
        editConnectionManDcPassword->setEchoMode(QLineEdit::Password);

        formLayout_3->setWidget(3, QFormLayout::FieldRole, editConnectionManDcPassword);

        labelConnectionManDcDomainNameList = new QLabel(groupBoxConnectionManDC);
        labelConnectionManDcDomainNameList->setObjectName(QString::fromUtf8("labelConnectionManDcDomainNameList"));

        formLayout_3->setWidget(4, QFormLayout::LabelRole, labelConnectionManDcDomainNameList);

        editConnectionManDcDomainNameList = new QLineEdit(groupBoxConnectionManDC);
        editConnectionManDcDomainNameList->setObjectName(QString::fromUtf8("editConnectionManDcDomainNameList"));

        formLayout_3->setWidget(4, QFormLayout::FieldRole, editConnectionManDcDomainNameList);


        verticalLayout_6->addWidget(groupBoxConnectionManDC);

        checkBoxConnectionManDC = new QCheckBox(tabConnectionMan);
        checkBoxConnectionManDC->setObjectName(QString::fromUtf8("checkBoxConnectionManDC"));

        verticalLayout_6->addWidget(checkBoxConnectionManDC);

        checkBoxConnectionManVPS = new QCheckBox(tabConnectionMan);
        checkBoxConnectionManVPS->setObjectName(QString::fromUtf8("checkBoxConnectionManVPS"));

        verticalLayout_6->addWidget(checkBoxConnectionManVPS);

        widgetTab->addTab(tabConnectionMan, QString());
        tabWeBookMan = new QWidget();
        tabWeBookMan->setObjectName(QString::fromUtf8("tabWeBookMan"));
        gridLayout_8 = new QGridLayout(tabWeBookMan);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayoutWeBookMan = new QGridLayout();
        gridLayoutWeBookMan->setObjectName(QString::fromUtf8("gridLayoutWeBookMan"));
        gridLayoutWeBookMan->setContentsMargins(9, 9, 9, 9);
        groupBoxWeBook = new QGroupBox(tabWeBookMan);
        groupBoxWeBook->setObjectName(QString::fromUtf8("groupBoxWeBook"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBoxWeBook->sizePolicy().hasHeightForWidth());
        groupBoxWeBook->setSizePolicy(sizePolicy);
        groupBoxWeBook->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        groupBoxWeBookLayout = new QVBoxLayout(groupBoxWeBook);
        groupBoxWeBookLayout->setSpacing(6);
        groupBoxWeBookLayout->setObjectName(QString::fromUtf8("groupBoxWeBookLayout"));
        groupBoxWeBookLayout->setContentsMargins(9, 9, 9, 9);
        listViewWeBookMan = new QListView(groupBoxWeBook);
        listViewWeBookMan->setObjectName(QString::fromUtf8("listViewWeBookMan"));

        groupBoxWeBookLayout->addWidget(listViewWeBookMan);

        groupBoxWeDetails = new QGroupBox(groupBoxWeBook);
        groupBoxWeDetails->setObjectName(QString::fromUtf8("groupBoxWeDetails"));
        _6 = new QFormLayout(groupBoxWeDetails);
        _6->setObjectName(QString::fromUtf8("_6"));
        labelWeBookManTitle = new QLabel(groupBoxWeDetails);
        labelWeBookManTitle->setObjectName(QString::fromUtf8("labelWeBookManTitle"));

        _6->setWidget(0, QFormLayout::LabelRole, labelWeBookManTitle);

        editWeBookManTitle = new QLineEdit(groupBoxWeDetails);
        editWeBookManTitle->setObjectName(QString::fromUtf8("editWeBookManTitle"));
        editWeBookManTitle->setEnabled(true);

        _6->setWidget(0, QFormLayout::FieldRole, editWeBookManTitle);


        groupBoxWeBookLayout->addWidget(groupBoxWeDetails);

        groupBoxControls = new QGroupBox(groupBoxWeBook);
        groupBoxControls->setObjectName(QString::fromUtf8("groupBoxControls"));
        horizontalLayout = new QHBoxLayout(groupBoxControls);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButtonWeBookManAdd = new QPushButton(groupBoxControls);
        pushButtonWeBookManAdd->setObjectName(QString::fromUtf8("pushButtonWeBookManAdd"));

        horizontalLayout->addWidget(pushButtonWeBookManAdd);

        pushButtonWeBookManDelete = new QPushButton(groupBoxControls);
        pushButtonWeBookManDelete->setObjectName(QString::fromUtf8("pushButtonWeBookManDelete"));

        horizontalLayout->addWidget(pushButtonWeBookManDelete);


        groupBoxWeBookLayout->addWidget(groupBoxControls);


        gridLayoutWeBookMan->addWidget(groupBoxWeBook, 0, 0, 1, 1);


        gridLayout_8->addLayout(gridLayoutWeBookMan, 0, 0, 1, 1);

        widgetTab->addTab(tabWeBookMan, QString());
        tabTOC = new QWidget();
        tabTOC->setObjectName(QString::fromUtf8("tabTOC"));
        gridLayout_9 = new QGridLayout(tabTOC);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        treeViewTocView = new QTreeView(tabTOC);
        treeViewTocView->setObjectName(QString::fromUtf8("treeViewTocView"));
        treeViewTocView->setAlternatingRowColors(true);
        treeViewTocView->setSelectionBehavior(QAbstractItemView::SelectItems);
        treeViewTocView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        treeViewTocView->setAnimated(false);
        treeViewTocView->setAllColumnsShowFocus(true);

        gridLayout_9->addWidget(treeViewTocView, 0, 0, 1, 1);

        widgetTab->addTab(tabTOC, QString());
        tabEditor = new QWidget();
        tabEditor->setObjectName(QString::fromUtf8("tabEditor"));
        verticalLayout_2 = new QVBoxLayout(tabEditor);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        textEdit = new QTextEdit(tabEditor);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        verticalLayout_2->addWidget(textEdit);

        widgetTab->addTab(tabEditor, QString());
        tabContacts = new QWidget();
        tabContacts->setObjectName(QString::fromUtf8("tabContacts"));
        verticalLayout_5 = new QVBoxLayout(tabContacts);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        widgetTab->addTab(tabContacts, QString());
        tabFileMan = new QWidget();
        tabFileMan->setObjectName(QString::fromUtf8("tabFileMan"));
        gridLayout_2 = new QGridLayout(tabFileMan);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        widgetTab->addTab(tabFileMan, QString());
        tabCalendarMan = new QWidget();
        tabCalendarMan->setObjectName(QString::fromUtf8("tabCalendarMan"));
        gridLayout_7 = new QGridLayout(tabCalendarMan);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        calendarWidget = new QCalendarWidget(tabCalendarMan);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));

        gridLayout_7->addWidget(calendarWidget, 0, 0, 1, 1);

        widgetTab->addTab(tabCalendarMan, QString());
        tabCalculator = new QWidget();
        tabCalculator->setObjectName(QString::fromUtf8("tabCalculator"));
        widgetTab->addTab(tabCalculator, QString());

        verticalLayout->addWidget(widgetTab);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 866, 25));
        menuChapter = new QMenu(menubar);
        menuChapter->setObjectName(QString::fromUtf8("menuChapter"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuFormat = new QMenu(menubar);
        menuFormat->setObjectName(QString::fromUtf8("menuFormat"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuInsert = new QMenu(menubar);
        menuInsert->setObjectName(QString::fromUtf8("menuInsert"));
        menuTOC = new QMenu(menubar);
        menuTOC->setObjectName(QString::fromUtf8("menuTOC"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
#if QT_CONFIG(shortcut)
        labelConnectionManVpsUsername->setBuddy(editConnectionManVpsUsername);
        labelConnectionManVpsPassword->setBuddy(editConnectionManVpsPassword);
        labelConnectionManVpsDomainNameList->setBuddy(editConnectionManVpsDomainNameList);
        labelConnectionManDcUsername->setBuddy(editConnectionManVpsUsername);
        labelConnectionManDcPassword->setBuddy(editConnectionManVpsPassword);
        labelConnectionManDcDomainNameList->setBuddy(editConnectionManVpsDomainNameList);
#endif // QT_CONFIG(shortcut)

        menubar->addAction(menuChapter->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuFormat->menuAction());
        menubar->addAction(menuInsert->menuAction());
        menubar->addAction(menuTOC->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuChapter->addAction(actionNew);
        menuChapter->addSeparator();
        menuChapter->addAction(actionSave);
        menuChapter->addSeparator();
        menuChapter->addAction(actionPrint);
        menuChapter->addSeparator();
        menuChapter->addAction(actionPDF);
        menuChapter->addSeparator();
        menuChapter->addAction(actionQuit);
        menuEdit->addAction(actionRedo);
        menuEdit->addAction(actionUndo);
        menuEdit->addSeparator();
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuFormat->addAction(actionTextBold);
        menuFormat->addAction(actionTextItalic);
        menuFormat->addAction(actionTextUnderline);
        menuFormat->addSeparator();
        menuFormat->addAction(actionAlignLeft);
        menuFormat->addAction(actionAlignCenter);
        menuFormat->addAction(actionAlignRight);
        menuFormat->addAction(actionAlignJustify);
        menuFormat->addSeparator();
        menuFormat->addAction(actionIndentMore);
        menuFormat->addAction(actionIndentLess);
        menuFormat->addSeparator();
        menuFormat->addAction(actionTextColor);
        menuHelp->addAction(actionAbout);
        menuHelp->addAction(actionQt);
        menuInsert->addAction(actionToggleCheckState);
        menuTOC->addAction(actionTocInsertRowAction);
        menuTOC->addAction(actionTocRemoveRowAction);
        menuTOC->addAction(actionTocInsertColumnAction);
        menuTOC->addAction(actionTocRemoveColumnAction);
        menuTOC->addAction(actionTocInsertChildAction);
        toolBar->addAction(actionNew);
        toolBar->addSeparator();
        toolBar->addAction(actionSave);
        toolBar->addSeparator();
        toolBar->addAction(actionPrint);
        toolBar->addSeparator();
        toolBar->addAction(actionPDF);
        toolBar->addSeparator();
        toolBar->addAction(actionRedo);
        toolBar->addAction(actionUndo);
        toolBar->addSeparator();
        toolBar->addAction(actionCut);
        toolBar->addAction(actionCopy);
        toolBar->addAction(actionPaste);
        toolBar->addSeparator();
        toolBar->addAction(actionTextBold);
        toolBar->addAction(actionTextItalic);
        toolBar->addAction(actionTextUnderline);
        toolBar->addSeparator();
        toolBar->addAction(actionAlignLeft);
        toolBar->addAction(actionAlignCenter);
        toolBar->addAction(actionAlignRight);
        toolBar->addAction(actionAlignJustify);
        toolBar->addSeparator();
        toolBar->addAction(actionIndentLess);
        toolBar->addAction(actionIndentMore);
        toolBar->addSeparator();
        toolBar->addAction(actionToggleCheckState);
        toolBar->addSeparator();
        toolBar->addAction(actionTextColor);
        toolBar->addSeparator();
        toolBar->addAction(actionQuit);

        retranslateUi(MainWindow);

        widgetTab->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNew->setText(QCoreApplication::translate("MainWindow", "&New", nullptr));
#if QT_CONFIG(tooltip)
        actionNew->setToolTip(QCoreApplication::translate("MainWindow", "New Chapter", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionNew->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave->setText(QCoreApplication::translate("MainWindow", "&Save", nullptr));
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionPrint->setText(QCoreApplication::translate("MainWindow", "&Print", nullptr));
#if QT_CONFIG(tooltip)
        actionPrint->setToolTip(QCoreApplication::translate("MainWindow", "Print", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionPrint->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+P", nullptr));
#endif // QT_CONFIG(shortcut)
        actionPDF->setText(QCoreApplication::translate("MainWindow", "PDF", nullptr));
#if QT_CONFIG(tooltip)
        actionPDF->setToolTip(QCoreApplication::translate("MainWindow", "Create PDF", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionPDF->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+P", nullptr));
#endif // QT_CONFIG(shortcut)
        actionQuit->setText(QCoreApplication::translate("MainWindow", "&Quit", nullptr));
#if QT_CONFIG(tooltip)
        actionQuit->setToolTip(QCoreApplication::translate("MainWindow", "Quit", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionQuit->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionUndo->setText(QCoreApplication::translate("MainWindow", "&Undo", nullptr));
#if QT_CONFIG(tooltip)
        actionUndo->setToolTip(QCoreApplication::translate("MainWindow", "Undo", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionUndo->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Z", nullptr));
#endif // QT_CONFIG(shortcut)
        actionRedo->setText(QCoreApplication::translate("MainWindow", "&Redo", nullptr));
#if QT_CONFIG(tooltip)
        actionRedo->setToolTip(QCoreApplication::translate("MainWindow", "Redo", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionRedo->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+Z", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCut->setText(QCoreApplication::translate("MainWindow", "Cut", nullptr));
#if QT_CONFIG(tooltip)
        actionCut->setToolTip(QCoreApplication::translate("MainWindow", "Cut", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionCut->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+X", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCopy->setText(QCoreApplication::translate("MainWindow", "&Copy", nullptr));
#if QT_CONFIG(tooltip)
        actionCopy->setToolTip(QCoreApplication::translate("MainWindow", "Copy", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionCopy->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        actionPaste->setText(QCoreApplication::translate("MainWindow", "Paste", nullptr));
#if QT_CONFIG(tooltip)
        actionPaste->setToolTip(QCoreApplication::translate("MainWindow", "Paste", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionPaste->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+V", nullptr));
#endif // QT_CONFIG(shortcut)
        actionTextBold->setText(QCoreApplication::translate("MainWindow", "&Bold", nullptr));
#if QT_CONFIG(tooltip)
        actionTextBold->setToolTip(QCoreApplication::translate("MainWindow", "Bold", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionTextBold->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+B", nullptr));
#endif // QT_CONFIG(shortcut)
        actionTextItalic->setText(QCoreApplication::translate("MainWindow", "&Italic", nullptr));
#if QT_CONFIG(tooltip)
        actionTextItalic->setToolTip(QCoreApplication::translate("MainWindow", "Italic", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionTextItalic->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+I", nullptr));
#endif // QT_CONFIG(shortcut)
        actionTextUnderline->setText(QCoreApplication::translate("MainWindow", "&Underline", nullptr));
#if QT_CONFIG(tooltip)
        actionTextUnderline->setToolTip(QCoreApplication::translate("MainWindow", "Underline", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionTextUnderline->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+U", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAlignLeft->setText(QCoreApplication::translate("MainWindow", "Align &Left", nullptr));
#if QT_CONFIG(tooltip)
        actionAlignLeft->setToolTip(QCoreApplication::translate("MainWindow", "Justify Left", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionAlignLeft->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+L", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAlignCenter->setText(QCoreApplication::translate("MainWindow", "Align C&enter", nullptr));
#if QT_CONFIG(tooltip)
        actionAlignCenter->setToolTip(QCoreApplication::translate("MainWindow", "Justify Center", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionAlignCenter->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+E", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAlignRight->setText(QCoreApplication::translate("MainWindow", "Align &Right", nullptr));
#if QT_CONFIG(tooltip)
        actionAlignRight->setToolTip(QCoreApplication::translate("MainWindow", "Justify Right", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionAlignRight->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+R", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAlignJustify->setText(QCoreApplication::translate("MainWindow", "Justify", nullptr));
#if QT_CONFIG(tooltip)
        actionAlignJustify->setToolTip(QCoreApplication::translate("MainWindow", "Justify Fill", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionAlignJustify->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+J", nullptr));
#endif // QT_CONFIG(shortcut)
        actionIndentMore->setText(QCoreApplication::translate("MainWindow", "Indent More", nullptr));
#if QT_CONFIG(tooltip)
        actionIndentMore->setToolTip(QCoreApplication::translate("MainWindow", "Indent More", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionIndentMore->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+]", nullptr));
#endif // QT_CONFIG(shortcut)
        actionIndentLess->setText(QCoreApplication::translate("MainWindow", "Indent Less", nullptr));
#if QT_CONFIG(tooltip)
        actionIndentLess->setToolTip(QCoreApplication::translate("MainWindow", "Indent Less", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionIndentLess->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+[", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
#if QT_CONFIG(tooltip)
        actionAbout->setToolTip(QCoreApplication::translate("MainWindow", "About", nullptr));
#endif // QT_CONFIG(tooltip)
        actionQt->setText(QCoreApplication::translate("MainWindow", "Qt", nullptr));
#if QT_CONFIG(tooltip)
        actionQt->setToolTip(QCoreApplication::translate("MainWindow", "About Qt", nullptr));
#endif // QT_CONFIG(tooltip)
        actionToggleCheckState->setText(QCoreApplication::translate("MainWindow", "Chech Box Chec&ked", nullptr));
#if QT_CONFIG(tooltip)
        actionToggleCheckState->setToolTip(QCoreApplication::translate("MainWindow", "Chech Box Checked", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionToggleCheckState->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+K", nullptr));
#endif // QT_CONFIG(shortcut)
        actionTextColor->setText(QCoreApplication::translate("MainWindow", "Text Color", nullptr));
#if QT_CONFIG(tooltip)
        actionTextColor->setToolTip(QCoreApplication::translate("MainWindow", "Text Color", nullptr));
#endif // QT_CONFIG(tooltip)
        actionTocInsertRowAction->setText(QCoreApplication::translate("MainWindow", "Insert Row", nullptr));
#if QT_CONFIG(shortcut)
        actionTocInsertRowAction->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+I, R", nullptr));
#endif // QT_CONFIG(shortcut)
        actionTocRemoveRowAction->setText(QCoreApplication::translate("MainWindow", "Remove Row", nullptr));
#if QT_CONFIG(shortcut)
        actionTocRemoveRowAction->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+R, R", nullptr));
#endif // QT_CONFIG(shortcut)
        actionTocInsertColumnAction->setText(QCoreApplication::translate("MainWindow", "Insert Column", nullptr));
#if QT_CONFIG(shortcut)
        actionTocInsertColumnAction->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+I, C", nullptr));
#endif // QT_CONFIG(shortcut)
        actionTocRemoveColumnAction->setText(QCoreApplication::translate("MainWindow", "Remove Column", nullptr));
#if QT_CONFIG(shortcut)
        actionTocRemoveColumnAction->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+R, C", nullptr));
#endif // QT_CONFIG(shortcut)
        actionTocInsertChildAction->setText(QCoreApplication::translate("MainWindow", "Insert Child", nullptr));
#if QT_CONFIG(shortcut)
        actionTocInsertChildAction->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        groupBoxSettingsGlobals->setTitle(QCoreApplication::translate("MainWindow", "Globals", nullptr));
        labelSettingsIniFileName->setText(QCoreApplication::translate("MainWindow", "Ini File Name", nullptr));
        labelSettingsApplicationName->setText(QCoreApplication::translate("MainWindow", "Application Name", nullptr));
        labelSettingsOrgName->setText(QCoreApplication::translate("MainWindow", "Organization Name", nullptr));
        labelSettingsOrgDomain->setText(QCoreApplication::translate("MainWindow", "Oranization Domain", nullptr));
        labelSettingsTravisURL->setText(QCoreApplication::translate("MainWindow", "Travis URL", nullptr));
        labelSettingsAppVeyorURL->setText(QCoreApplication::translate("MainWindow", "AppVeyor URL", nullptr));
        pushButtonSgSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        widgetTab->setTabText(widgetTab->indexOf(tabSettings), QCoreApplication::translate("MainWindow", "Settings", nullptr));
        groupBoxConnectionManLocal->setTitle(QCoreApplication::translate("MainWindow", "Local", nullptr));
        pushButtonConnectionManLocalPath->setText(QCoreApplication::translate("MainWindow", "Local Path...", nullptr));
        groupBoxConnectionManVPS->setTitle(QCoreApplication::translate("MainWindow", "VPS", nullptr));
        labelConnectionManVpsIP->setText(QCoreApplication::translate("MainWindow", "IP Address", nullptr));
        labelConnectionManVpsPort->setText(QCoreApplication::translate("MainWindow", "Port", nullptr));
        labelConnectionManVpsUsername->setText(QCoreApplication::translate("MainWindow", "&Username:", nullptr));
        labelConnectionManVpsPassword->setText(QCoreApplication::translate("MainWindow", "&Password:", nullptr));
        labelConnectionManVpsDomainNameList->setText(QCoreApplication::translate("MainWindow", "Domain Name List", nullptr));
        groupBoxConnectionManDC->setTitle(QCoreApplication::translate("MainWindow", "Domain Controller (DC)", nullptr));
        labelConnectionManDcIP->setText(QCoreApplication::translate("MainWindow", "IP Address", nullptr));
        labelConnectionManDcPort->setText(QCoreApplication::translate("MainWindow", "Port", nullptr));
        labelConnectionManDcUsername->setText(QCoreApplication::translate("MainWindow", "&Username:", nullptr));
        labelConnectionManDcPassword->setText(QCoreApplication::translate("MainWindow", "&Password:", nullptr));
        labelConnectionManDcDomainNameList->setText(QCoreApplication::translate("MainWindow", "Domain Name List", nullptr));
        checkBoxConnectionManDC->setText(QCoreApplication::translate("MainWindow", "Domain Controller (DC)", nullptr));
        checkBoxConnectionManVPS->setText(QCoreApplication::translate("MainWindow", "VPS", nullptr));
        widgetTab->setTabText(widgetTab->indexOf(tabConnectionMan), QCoreApplication::translate("MainWindow", "Connect", nullptr));
        groupBoxWeBook->setTitle(QCoreApplication::translate("MainWindow", "WeBook Manager", nullptr));
        groupBoxWeDetails->setTitle(QCoreApplication::translate("MainWindow", "Details", nullptr));
        labelWeBookManTitle->setText(QCoreApplication::translate("MainWindow", "<b>Title:</b>", nullptr));
        groupBoxControls->setTitle(QCoreApplication::translate("MainWindow", "Controls", nullptr));
        pushButtonWeBookManAdd->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        pushButtonWeBookManDelete->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        widgetTab->setTabText(widgetTab->indexOf(tabWeBookMan), QCoreApplication::translate("MainWindow", "Books", nullptr));
        widgetTab->setTabText(widgetTab->indexOf(tabTOC), QCoreApplication::translate("MainWindow", "TOC", nullptr));
        widgetTab->setTabText(widgetTab->indexOf(tabEditor), QCoreApplication::translate("MainWindow", "Editor", nullptr));
        widgetTab->setTabText(widgetTab->indexOf(tabContacts), QCoreApplication::translate("MainWindow", "Contacts", nullptr));
        widgetTab->setTabText(widgetTab->indexOf(tabFileMan), QCoreApplication::translate("MainWindow", "Files", nullptr));
        widgetTab->setTabText(widgetTab->indexOf(tabCalendarMan), QCoreApplication::translate("MainWindow", "Calendar", nullptr));
        widgetTab->setTabText(widgetTab->indexOf(tabCalculator), QCoreApplication::translate("MainWindow", "Calculator", nullptr));
#if QT_CONFIG(tooltip)
        menuChapter->setToolTip(QCoreApplication::translate("MainWindow", "Chapter", nullptr));
#endif // QT_CONFIG(tooltip)
        menuChapter->setTitle(QCoreApplication::translate("MainWindow", "&Chapter", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "&Edit", nullptr));
        menuFormat->setTitle(QCoreApplication::translate("MainWindow", "&Format", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
        menuInsert->setTitle(QCoreApplication::translate("MainWindow", "Insert", nullptr));
        menuTOC->setTitle(QCoreApplication::translate("MainWindow", "TOC", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "WeBook Tabs", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

/******************************************************************************
** WeBook: Pronounced Web Book, is a Book Content Management System  (BCMS)   *
*******************************************************************************/
#pragma once
#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include "ui_AboutDialog.h"

namespace Ui { class AboutDialog; }
/******************************************************************************
** class AboutDialog : public QDialog                                         *
*******************************************************************************/
class AboutDialog : public QDialog
{
        Q_OBJECT

    public:
        explicit AboutDialog(QWidget *parent = nullptr);
        ~AboutDialog();

    private:
        Ui::AboutDialog *ui;
};

#endif // ABOUTDIALOG_H
/* ***************************** End of File ******************************* */

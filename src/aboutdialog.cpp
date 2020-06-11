#include "aboutdialog.h"
/******************************************************************************
** AboutDialog Constructor                                                    *
*******************************************************************************/
AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    connect(ui->pushButtonCloseAbout, &QPushButton::clicked,  this, &QDialog::close);
}
/******************************************************************************
** AboutDialog Destructor                                                     *
*******************************************************************************/
AboutDialog::~AboutDialog()
{
    delete ui;
}
/* ***************************** End of File ******************************* */

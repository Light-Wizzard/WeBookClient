#include "Bookmarks.h"
#include "ui_Bookmarks.h"

/*****************************************************************************/
/**
 * @brief Bookmarks::Bookmarks
 * @param parent
 */
Bookmarks::Bookmarks(QWidget *parent) : QWidget(parent), ui(new Ui::Bookmarks)
{
    ui->setupUi(this);
}
/*****************************************************************************/
/**
 * @brief Bookmarks::~Bookmarks
 */
Bookmarks::~Bookmarks()
{
    delete ui;
}
/******************************* End of File *********************************/

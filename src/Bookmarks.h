#ifndef BOOKMARKS_H
#define BOOKMARKS_H

#include <QWidget>

namespace Ui { class Bookmarks; }

/*****************************************************************************/
/**
 * @brief The Bookmarks class
 */
class Bookmarks : public QWidget
{
        Q_OBJECT

    public:
        explicit Bookmarks(QWidget *parent = nullptr);
        ~Bookmarks();

    private:
        Ui::Bookmarks *ui;
}; // end class Bookmarks
#endif // BOOKMARKS_H
/******************************* End of File *********************************/

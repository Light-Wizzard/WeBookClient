#include <QCoreApplication>
#include <QTest>
#include "unit_test/aestest.h"
/******************************************************************************
** maintest                                                                   *
** QAESEncryption                                                             *
*******************************************************************************/
int maintest(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    AesTest test1;
    QTest::qExec(&test1);
    return 0;
}
/* ***************************** End of File ******************************* */


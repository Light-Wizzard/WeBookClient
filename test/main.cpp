#include <QtTest>
#include "testmathtokenizer.h"
#include "testmathparser.h"

int main(int argc, char** argv) 
{
    QApplication app(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    TestMathTokenizer testTokenizer;
    TestMathParser testParser;
    // multiple test suites can be ran like this
    return QTest::qExec(&testTokenizer, argc, argv) | QTest::qExec(&testParser, argc, argv);
}


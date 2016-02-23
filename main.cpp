#include <QCoreApplication>
#include "linkslooker.h"
int main(int argc, char *argv[])
{
   QCoreApplication a(argc, argv);


    linkslooker ll(a.thread());

   return a.exec();
}

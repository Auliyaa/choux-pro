#include <QtWidgets/QApplication>
#include "choux_window.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  choux_window window;
  window.show();

  return app.exec();
}

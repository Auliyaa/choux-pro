#pragma once

#include <QtWidgets/QMainWindow>

namespace Ui
{
class choux_window;
}

class choux_window: public QMainWindow
{
  Q_OBJECT

  Ui::choux_window* _ui;

public slots:
  void input_changed();
  void reset();
  void setResults(int base, int top, int steps, int count, int leftover);

public:
  choux_window();
  virtual ~choux_window();
};

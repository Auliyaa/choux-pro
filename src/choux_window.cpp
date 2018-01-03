#include "choux_window.h"

#include <QtCore/QDir>
#include <QtCore/QDebug>
#include <QtCore/QTime>

#include "ui_choux_window.h"

choux_window::choux_window()
  : QMainWindow(),
    _ui(new Ui::choux_window)
{
  _ui->setupUi(this);

  // Add some background magic
  QDir bg_dir(":/bg");
  qsrand(QTime::currentTime().msec());
  QString bg = bg_dir.entryList()[qrand()%bg_dir.entryInfoList().size()];
  _ui->centralwidget->setStyleSheet("#centralwidget { border-image: url(:/bg/" + bg + ") 0 0 0 0 stretch stretch; }");
}

choux_window::~choux_window()
{
  delete _ui;
}

void choux_window::input_changed()
{
  _ui->results->setText("");

  int base  = _ui->base->value();
  int total = _ui->total->value();
  int last  = _ui->last->value();

  _ui->total->setEnabled(!(base != 0 && last  != 0));
  _ui->base->setEnabled( !(last != 0 && total != 0));
  _ui->last->setEnabled( !(base != 0 && total != 0));

  if (last != 0 && total != 0)
  {
    // Compute number of steps and base size
    int current_count = last;
    int current_total = total-current_count;
    int steps=1;

    while (current_total >= current_count)
    {
      ++current_count;
      ++steps;
      current_total -= current_count;
    }

    setResults(current_count, last, steps, total-current_total, current_total);
  }

  else if (base != 0 && total != 0)
  {
    // Compute number of steps and top size
    int current_count = base;
    int current_total = total-current_count;
    int steps=1;

    while (current_count-1 >= 3 && current_total >= current_count-1)
    {
      ++steps;
      --current_count;
      current_total -= current_count;
    }

    setResults(base, current_count, steps, total-current_total, current_total);
  }

  else if (base != 0 && last != 0)
  {
    // Compute number of steps and total
    int current_count = last;
    int steps=1;
    int total=current_count;

    while (current_count < base)
    {
      ++steps;
      ++current_count;
      total+=current_count;
    }

    setResults(base, last, steps, total, 0);
  }
}

void choux_window::reset()
{
  _ui->base->setValue(0);
  _ui->total->setValue(0);
  _ui->last->setValue(0);
}

void choux_window::setResults(int base, int top, int steps, int count, int leftover)
{
  QString result = "Cette <b>splendide</b> pièce montée comprend les éléments suivants:<br/><br/>";
  result += "<ul>";
  result += "<li><b>Etage du haut  :</b> " + QString::number(top)      + "</li>";
  result += "<li><b>Etage du bas   :</b> " + QString::number(base)     + "</li>";
  result += "<li><b>Nombre d'étages:</b> " + QString::number(steps)    + "</li>";
  result += "<li><b>Nombre de choux:</b> " + QString::number(count)    + "</li>";
  result += "<li><b>Reste en choux :</b> " + QString::number(leftover) + "</li>";
  result += "</ul>";
  _ui->results->setText(result);
}

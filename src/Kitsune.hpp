#ifndef KITSUNE_H
#define KITSUNE_H

#include <QMainWindow>

namespace Ui
{
    class KitsuneUi;
}

class Kitsune : public QMainWindow
{
    Q_OBJECT

public:
    explicit Kitsune(QWidget *parent = 0);
    ~Kitsune();

private:
    Ui::KitsuneUi *ui;
};

#endif /* KITSUNE_H */

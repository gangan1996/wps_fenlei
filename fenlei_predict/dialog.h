#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <vector>
#include <string>

using namespace  std;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public:
    void sendData(vector<string>v1,vector<string>v2,vector<int>v3);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H

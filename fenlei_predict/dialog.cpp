#include "dialog.h"
#include "ui_dialog.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::sendData(vector<string> v1, vector<string> v2, vector<int> v3)
{
    ui->listWidget->setFixedWidth(700);
    //设置item图标大小
    ui->listWidget->setIconSize(QSize(20,20));

    if(v1.size()==v2.size()&&v2.size()==v3.size())
    {
        for(int a=0;a<v1.size();a++)
        {
            QListWidgetItem *add_item = new QListWidgetItem(ui->listWidget);
            if(v3[a]==1)
            {
                add_item->setIcon(QIcon(":/image1/bg/icon.png"));
            }else{
                add_item->setIcon(QIcon(":/image1/bg/icon2.png"));
            }

            add_item->setText(QString::fromStdString("\""+v1[a]+"\""+"判别类型为:"+v2[a]));
        }

    }else{

        cout<<"v1v2v3 is not same!!"<<endl;
    }

}

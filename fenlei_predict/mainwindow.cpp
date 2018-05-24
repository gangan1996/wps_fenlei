#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"

#include <QFileDialog>
#include <iostream>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <dirent.h>
#include <algorithm>
#include <map>

using namespace std;

float he=0.85,lun=0.85,jian=0.85,gong=0.85;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dialog=new Dialog(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
vector<string> listFiles(string cate_dir)
{
    vector<string> files;//存放文件名

    DIR *dir;
    struct dirent *ptr;
    char base[1000];

    if ((dir=opendir(cate_dir.c_str())) == NULL)
    {
        perror("Open dir error...");
        cout<<cate_dir;
                exit(1);
    }
    while ((ptr=readdir(dir)) != NULL)
    {
        if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0)
        {
            files.push_back(ptr->d_name);
         }


    }
    closedir(dir);

    //排序，按从小到大排序
    sort(files.begin(), files.end());
    return files;
}

//从文件中读取
void readfile(const vector<string> vec,vector<string> & vec_content,string dir)
{
    for(int i = 0; i<vec.size();i++)
    {
        string filename = dir+vec[i];
        cout<<filename<<endl;
        ifstream in(filename.c_str());
        if(!in.is_open()) {
            cout << "Error: Cannot Open " << filename << endl;
            exit(1);
        }
        string str="";
        string temp;
        while(getline(in,temp)) {
            str+=temp;
        }
        in.close();
        vec_content.push_back(str);

    }
}

void setlabel(vector<string> v,int i,vector<pair<string,int>>& m)
{
    for(int a=0;a<v.size();a++)
    m.push_back(pair<string,int>(v[a],i));
}

void MainWindow::on_pushButton_clicked()
{
    QFileDialog dialog;

    if(dialog.exec()){

    QString file = dialog.selectedFiles().at(0);

    QFileInfo info(file);

    ui->label->setText(info.path());


    }
}

void MainWindow::on_pushButton_2_clicked()
{

    vector<string> test_text,test_title,test_label,test_catagory;
    vector<string> title1,title2,title3,title4;
    vector<pair<string,int>> test;

    string testdir=ui->label->text().toStdString();

    title1 = listFiles(testdir+"/gongwen/");
    readfile(title1,test_text,testdir+"/gongwen/");
    setlabel(title1,0,test);

    title2 = listFiles(testdir+"/lunwen/");
    readfile(title2,test_text,testdir+"/lunwen/");
    setlabel(title2,1,test);

    title3 = listFiles(testdir+"/jianli/");
    readfile(title3,test_text,testdir+"/jianli/");
    setlabel(title3,2,test);

    title4 = listFiles(testdir+"/hetong/");
    readfile(title4,test_text,testdir+"/hetong/");
    setlabel(title4,3,test);

    test_title.insert(test_title.end(),title1.begin(),title1.end());
    test_title.insert(test_title.end(),title2.begin(),title2.end());
    test_title.insert(test_title.end(),title3.begin(),title3.end());
    test_title.insert(test_title.end(),title4.begin(),title4.end());




    for(int i=0;i<test_text.size();i++)
    {
        test_label.push_back("0");

    }

    string model_name="model2";
    string out_name="out2";

    ifstream model_file(model_name,ios::in);
    ofstream output_file(out_name,ios::out);

    if(!model_file.is_open()) {
        printf("Cannot open %s\n","model1");
        exit(1);
    }
    if(!output_file.is_open()) {
        printf("Cannot open %s\n","out");
        exit(1);
    }
    cout << "Now Starting Parsing " << testdir << endl;

    model_file.close();
    output_file.close();
    char *error;
    void *handle = dlopen("../build-demo-Desktop_Qt_5_10_0_GCC_64bit-Debug/libdemo.so",RTLD_NOW);
    //void *handle = dlopen("../../myproject/build-untitled3-Desktop_Qt_5_10_0_GCC_64bit-Debug/libuntitled3.so",RTLD_NOW);
    void (*predict)(vector<string> &,vector<string> &,vector<string> &,const char *,const char *);
    if(!handle) {
        fprintf(stderr,"%s\n",dlerror());
        exit(1);
    }
    *(void **)(&predict) = dlsym(handle,"predict");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    predict(test_text,test_label,test_title,model_name.c_str(),out_name.c_str());
    dlclose(handle);
    vector <int> catagory;
    string str;
    ifstream i(out_name);
    if(i.is_open())
    {
        while (i>>str) {
            catagory.push_back(stoi(str));
        }
    }else{
        cout<<"can't open out"<<endl;
    }
    for(int a=0;a<catagory.size();a++)
    {
        switch (catagory[a])
        {
        case 0:test_catagory.push_back("公文");
            break;
        case 1:test_catagory.push_back("论文");
            break;
        case 2:test_catagory.push_back("简历");
            break;
        case 3:test_catagory.push_back("合同");
            break;
        default:
            break;
        }
    }
    if(test_title.size()==test_catagory.size())
    {
        for(int a=0;a<test_title.size();a++)
        {
            cout<<"\""<<test_title[a]<<"\""<<"的文本属性为:"<<test_catagory[a]<<endl;
        }

     }else{

               cout<<"test_title.size()!=test_catagory.size()"<<endl;
        }

    int gong_z=0,lun_z=0,jian_z=0,he_z=0;
    int gong_y=0,lun_y=0,jian_y=0,he_y=0;
    vector<int> zhunquelv;
    if(test.size()==catagory.size())
    {
        for(int a=0;a<test.size();a++)
        {
           if(test[a].second==0)
           {
               gong_z++;
               if(catagory[a]==0)
               {
                   gong_y++;
                   zhunquelv.push_back(1);
               }else{
                   zhunquelv.push_back(0);
               }
           }else if(test[a].second==1)
           {
               lun_z++;
               if(catagory[a]==1)
               {
                   lun_y++;
                   zhunquelv.push_back(1);
               }else{
                   zhunquelv.push_back(0);
               }
           }else if(test[a].second==2)
           {
               jian_z++;
               if(catagory[a]==2)
               {
                   jian_y++;
                   zhunquelv.push_back(1);
               }else{
                   zhunquelv.push_back(0);
               }
           }else if(test[a].second==3)
           {
               he_z++;
               if(catagory[a]==3)
               {
                   he_y++;
                   zhunquelv.push_back(1);
               }else{
                   zhunquelv.push_back(0);
               }
           }
        }
    }else{
        cout<<"test_title,test,test_catagory size is not same"<<endl;
        cout<<"test_title size is:"<<test_title.size()<<endl;
        cout<<"test size is:"<<test.size()<<endl;
        cout<<"catagory size is:"<<catagory.size()<<endl;
    }
    dialog->sendData(test_title,test_catagory,zhunquelv);

    he=(float)he_y/he_z;
    lun=(float)lun_y/lun_z;
    jian=(float)jian_y/jian_z;
    gong=(float)gong_y/gong_z;
    ui->label_6->setText(QString::fromStdString(to_string(he)));
    ui->label_7->setText(QString::fromStdString(to_string(lun)));
    ui->label_8->setText(QString::fromStdString(to_string(jian)));
    ui->label_9->setText(QString::fromStdString(to_string(gong)));
    update();
    return;
}
void MainWindow::paintEvent(QPaintEvent *)
{


     QPainter painter(this);
     painter.drawPixmap(0,0,width(),height(),QPixmap(":/image1/bg/bg2.png"));
     painter.setRenderHint(QPainter::Antialiasing, true);

     int radius = 50;
     int arcHeight = 30;
     int begin,zhuan;
     // >> 1（右移1位）相当于width() / 2
     painter.translate(width()/4, height()/2);

     /**
      * 参数二：半径
      * 参数三：开始的角度
      * 参数四：指扫取的角度-顺时针（360度 / 8 = 45度）
      * 参数五：圆环的高度
      * 参数六：填充色
     **/

     begin=he*360;
     zhuan=360-begin;
     gradientArc(&painter, radius, 0,  begin, arcHeight, qRgb(144, 238, 144),he);
     gradientArc(&painter, radius, begin, zhuan, arcHeight, qRgb(255, 255, 255),0.0);


     begin=lun*360;
     zhuan=360-begin;
      painter.translate(width()/6, 0);
      gradientArc(&painter, radius, 0,  begin, arcHeight, qRgb(240, 230, 140),lun);
      gradientArc(&painter, radius, begin, zhuan, arcHeight, qRgb(255, 255, 255),0.0);

      begin=jian*360;
      zhuan=360-begin;
      painter.translate(width()/6, 0);
      gradientArc(&painter, radius, 0,  begin, arcHeight, qRgb(255, 182, 193),jian);
      gradientArc(&painter, radius, begin, zhuan, arcHeight, qRgb(255, 255, 255),0.0);

      begin=gong*360;
      zhuan=360-begin;
      painter.translate(width()/6, 0);
      gradientArc(&painter, radius, 0,  begin, arcHeight, qRgb(135, 206, 250),gong);
      gradientArc(&painter, radius, begin, zhuan, arcHeight, qRgb(255, 255, 255),0.0);



}

void MainWindow::gradientArc(QPainter *painter, int radius, int startAngle, int angleLength, int arcHeight, QRgb color,float baifenbi)
{
    // 渐变色
    QRadialGradient gradient(0, 0, radius);
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1.0, color);
    painter->setBrush(gradient);

    // << 1（左移1位）相当于radius*2 即：150*2=300
    //QRectF(-150, -150, 300, 300)
    QRectF rect(-radius, -radius, radius << 1, radius << 1);
    QPainterPath path;
    path.arcTo(rect, startAngle, angleLength);

    QFont font;
        font.setFamily("Microsoft YaHei");
        font.setPointSize(14);

    painter->setPen(Qt::NoPen);

    painter->drawPath(path);
}

void MainWindow::on_pushButton_3_clicked()
{


    dialog->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    dialog2=new Dialog2(this);
    dialog2->show();
}

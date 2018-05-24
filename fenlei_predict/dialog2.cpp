#include "dialog2.h"
#include "ui_dialog2.h"
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

float ti=0.85,cai=0.85,yu=0.85,fang=0.85,jiao=0.85,
ke=0.85,shishang=0.85,shizheng=0.85,you=0.85,jia=0.85;
vector<string> test_title,test_catagory;
vector<int> zhunquelv;

Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{
    ui->setupUi(this);
}

Dialog2::~Dialog2()
{
    delete ui;
}

vector<string> listFiles1(string cate_dir)
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
void readfile1(const vector<string> vec,vector<string> & vec_content,string dir)
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

void setlabel1(vector<string> v,int i,vector<pair<string,int>>& m)
{
    for(int a=0;a<v.size();a++)
        m.push_back(pair<string,int>(v[a],i));
}

void Dialog2::on_pushButton_clicked()
{
    QFileDialog dialog;

    if(dialog.exec()){

        QString file = dialog.selectedFiles().at(0);

        QFileInfo info(file);

        ui->label->setText(info.path());


    }
}

void Dialog2::on_pushButton_2_clicked()
{
    vector<string> test_text,test_label;
    vector<string> title1,title2,title3,title4,title5,title6,
            title7,title8,title9,title10;
    vector<pair<string,int>> test;

    string testdir=ui->label->text().toStdString();

    title1 = listFiles1(testdir+"/tiyu/");
    readfile1(title1,test_text,testdir+"/tiyu/");
    setlabel1(title1,0,test);

    title2 = listFiles1(testdir+"/caijing/");
    readfile1(title2,test_text,testdir+"/caijing/");
    setlabel1(title2,1,test);

    title3 = listFiles1(testdir+"/yule/");
    readfile1(title3,test_text,testdir+"/yule/");
    setlabel1(title3,2,test);

    title4 = listFiles1(testdir+"/fangchan/");
    readfile1(title4,test_text,testdir+"/fangchan/");
    setlabel1(title4,3,test);

    title5 = listFiles1(testdir+"/jiaoyu/");
    readfile1(title5,test_text,testdir+"/jiaoyu/");
    setlabel1(title5,4,test);

    title6 = listFiles1(testdir+"/keji/");
    readfile1(title6,test_text,testdir+"/keji/");
    setlabel1(title6,5,test);

    title7 = listFiles1(testdir+"/shishang/");
    readfile1(title7,test_text,testdir+"/shishang/");
    setlabel1(title7,6,test);

    title8 = listFiles1(testdir+"/shizheng/");
    readfile1(title8,test_text,testdir+"/shizheng/");
    setlabel1(title8,7,test);

    title9 = listFiles1(testdir+"/youxi/");
    readfile1(title9,test_text,testdir+"/youxi/");
    setlabel1(title9,8,test);

    title10 = listFiles1(testdir+"/jiaju/");
    readfile1(title10,test_text,testdir+"/jiaju/");
    setlabel1(title10,9,test);

    test_title.insert(test_title.end(),title1.begin(),title1.end());
    test_title.insert(test_title.end(),title2.begin(),title2.end());
    test_title.insert(test_title.end(),title3.begin(),title3.end());
    test_title.insert(test_title.end(),title4.begin(),title4.end());
    test_title.insert(test_title.end(),title5.begin(),title5.end());
    test_title.insert(test_title.end(),title6.begin(),title6.end());
    test_title.insert(test_title.end(),title7.begin(),title7.end());
    test_title.insert(test_title.end(),title8.begin(),title8.end());
    test_title.insert(test_title.end(),title9.begin(),title9.end());
    test_title.insert(test_title.end(),title10.begin(),title10.end());




    for(int i=0;i<test_text.size();i++)
    {
        test_label.push_back("0");

    }

    string model_name="model10";
    string out_name="out10";

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
        case 0:test_catagory.push_back("体育");
            break;
        case 1:test_catagory.push_back("财经");
            break;
        case 2:test_catagory.push_back("娱乐");
            break;
        case 3:test_catagory.push_back("房产");
            break;
        case 4:test_catagory.push_back("教育");
            break;
        case 5:test_catagory.push_back("科技");
            break;
        case 6:test_catagory.push_back("时尚");
            break;
        case 7:test_catagory.push_back("时政");
            break;
        case 8:test_catagory.push_back("游戏");
            break;
        case 9:test_catagory.push_back("家居");
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

    int ti_z=0,cai_z=0,yu_z=0,fang_z=0,jiao_z=0,
            ke_z=0,shishang_z=0,shizheng_z=0,you_z=0,jia_z=0;
    int ti_y=0,cai_y=0,yu_y=0,fang_y=0,jiao_y=0,
            ke_y=0,shishang_y=0,shizheng_y=0,you_y=0,jia_y=0;

    if(test.size()==catagory.size())
    {
        for(int a=0;a<test.size();a++)
        {
            if(test[a].second==0)
            {
                ti_z++;
                if(catagory[a]==0)
                {
                    ti_y++;
                    zhunquelv.push_back(1);
                }else{
                    zhunquelv.push_back(0);
                }
            }else if(test[a].second==1)
            {
                cai_z++;
                if(catagory[a]==1)
                {
                    cai_y++;
                    zhunquelv.push_back(1);
                }else{
                    zhunquelv.push_back(0);
                }
            }else if(test[a].second==2)
            {
                yu_z++;
                if(catagory[a]==2)
                {
                    yu_y++;
                    zhunquelv.push_back(1);
                }else{
                    zhunquelv.push_back(0);
                }
            }else if(test[a].second==3)
            {
                fang_z++;
                if(catagory[a]==3)
                {
                    fang_y++;
                    zhunquelv.push_back(1);
                }else{
                    zhunquelv.push_back(0);
                }
            }else if(test[a].second==4)
            {
                jiao_z++;
                if(catagory[a]==4)
                {
                    jiao_y++;
                    zhunquelv.push_back(1);
                }else{
                    zhunquelv.push_back(0);
                }
            }else if(test[a].second==5)
            {
                ke_z++;
                if(catagory[a]==5)
                {
                    ke_y++;
                    zhunquelv.push_back(1);
                }else{
                    zhunquelv.push_back(0);
                }
            }else if(test[a].second==6)
            {
                shishang_z++;
                if(catagory[a]==6)
                {
                    shishang_y++;
                    zhunquelv.push_back(1);
                }else{
                    zhunquelv.push_back(0);
                }
            }else if(test[a].second==7)
            {
                shizheng_z++;
                if(catagory[a]==7)
                {
                    shizheng_y++;
                    zhunquelv.push_back(1);
                }else{
                    zhunquelv.push_back(0);
                }
            }else if(test[a].second==8)
            {
                you_z++;
                if(catagory[a]==8)
                {
                    you_y++;
                    zhunquelv.push_back(1);
                }else{
                    zhunquelv.push_back(0);
                }
            }else if(test[a].second==9)
            {
                jia_z++;
                if(catagory[a]==9)
                {
                    jia_y++;
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
    //dialog->sendData(test_title,test_catagory,zhunquelv);

    ti=(float)ti_y/ti_z;
    cai=(float)cai_y/cai_z;
    yu=(float)yu_y/yu_z;
    fang=(float)fang_y/fang_z;
    jiao=(float)jiao_y/jiao_z;
    ke=(float)ke_y/ke_z;
    shishang=(float)shishang_y/shishang_z;
    shizheng=(float)shizheng_y/shizheng_z;
    you=(float)you_y/you_z;
    jia=(float)jia_y/jia_z;

    update();
    //return;
}

void Dialog2::paintEvent(QPaintEvent *)
{

    ui->label_2->setText(QString::fromStdString(to_string(ti)));
    ui->label_3->setText(QString::fromStdString(to_string(cai)));
    ui->label_4->setText(QString::fromStdString(to_string(yu)));
    ui->label_5->setText(QString::fromStdString(to_string(fang)));
    ui->label_6->setText(QString::fromStdString(to_string(jiao)));
    ui->label_7->setText(QString::fromStdString(to_string(ke)));
    ui->label_8->setText(QString::fromStdString(to_string(shishang)));
    ui->label_9->setText(QString::fromStdString(to_string(shizheng)));
    ui->label_10->setText(QString::fromStdString(to_string(you)));
    ui->label_11->setText(QString::fromStdString(to_string(jia)));
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":/image1/bg/bg3.png"));
    painter.setRenderHint(QPainter::Antialiasing, true);

    int radius = 50;
    int arcHeight = 30;
    int begin,zhuan;
    // >> 1（右移1位）相当于width() / 2
    painter.translate(width()/7, height()/4);


    // 参数二：半径
    // 参数三：开始的角度
    // 参数四：指扫取的角度-顺时针（360度 / 8 = 45度）
    // 参数五：圆环的高度
    // 参数六：填充色


    begin=ti*360;
    zhuan=360-begin;
    gradientArc(&painter, radius, 0,  begin, arcHeight, qRgb(144, 238, 144));
    gradientArc(&painter, radius, begin, zhuan, arcHeight, qRgb(255, 255, 255));


    begin=cai*360;
    zhuan=360-begin;
    painter.translate(width()/6, 0);
    gradientArc(&painter, radius, 0,  begin, arcHeight, qRgb(144, 238, 144));
    gradientArc(&painter, radius, begin, zhuan, arcHeight, qRgb(255, 255, 255));

    begin=yu*360;
    zhuan=360-begin;
    painter.translate(width()/6, 0);
    gradientArc(&painter, radius, 0,  begin, arcHeight, qRgb(144, 238, 144));
    gradientArc(&painter, radius, begin, zhuan, arcHeight, qRgb(255, 255, 255));

    begin=fang*360;
    zhuan=360-begin;
    painter.translate(width()/6, 0);
    gradientArc(&painter, radius, 0,  begin, arcHeight, qRgb(144, 238, 144));
    gradientArc(&painter, radius, begin, zhuan, arcHeight, qRgb(255, 255, 255));


    begin=jiao*360;
    zhuan=360-begin;
    painter.translate(width()/6, 0);
    gradientArc(&painter, radius, 0,  begin, arcHeight, qRgb(144, 238, 144));
    gradientArc(&painter, radius, begin, zhuan, arcHeight, qRgb(255, 255, 255));

    begin=ke*360;
    zhuan=360-begin;
    painter.translate(0, height()/5);
    gradientArc(&painter, radius, 0,  begin, arcHeight, qRgb(144, 238, 144));
    gradientArc(&painter, radius, begin, zhuan, arcHeight, qRgb(255, 255, 255));

    begin=shishang*360;
    zhuan=360-begin;
    painter.translate(-width()/6, 0);
    gradientArc(&painter, radius, 0,  begin, arcHeight, qRgb(144, 238, 144));
    gradientArc(&painter, radius, begin, zhuan, arcHeight, qRgb(255, 255, 255));

    begin=shizheng*360;
    zhuan=360-begin;
    painter.translate(-width()/6, 0);
    gradientArc(&painter, radius, 0,  begin, arcHeight, qRgb(144, 238, 144));
    gradientArc(&painter, radius, begin, zhuan, arcHeight, qRgb(255, 255, 255));

    begin=you*360;
    zhuan=360-begin;
    painter.translate(-width()/6, 0);
    gradientArc(&painter, radius, 0,  begin, arcHeight, qRgb(144, 238, 144));
    gradientArc(&painter, radius, begin, zhuan, arcHeight, qRgb(255, 255, 255));

    begin=jia*360;
    zhuan=360-begin;
    painter.translate(-width()/6, 0);
    gradientArc(&painter, radius, 0,  begin, arcHeight, qRgb(144, 238, 144));
    gradientArc(&painter, radius, begin, zhuan, arcHeight, qRgb(255, 255, 255));

}

void Dialog2::gradientArc(QPainter *painter, int radius, int startAngle, int angleLength, int arcHeight, QRgb color)
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

void Dialog2::on_pushButton_3_clicked()
{
    if(test_title.size()==test_catagory.size()&&test_catagory.size()==zhunquelv.size())
    {
        for(int a=0;a<test_title.size();a++)
        {
            QListWidgetItem *add_item = new QListWidgetItem(ui->listWidget);
            if(zhunquelv[a]==1)
            {
                add_item->setIcon(QIcon(":/image1/bg/icon.png"));
            }else{
                add_item->setIcon(QIcon(":/image1/bg/icon2.png"));
            }

            add_item->setText(QString::fromStdString("\""+test_title[a]+"\""+"判别类型为:"+test_catagory[a]));
        }

    }else{

        cout<<"v1v2v3 is not same!!"<<endl;
    }
}

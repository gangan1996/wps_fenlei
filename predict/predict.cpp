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
using namespace std;


void printUsage() {
    printf(
    "***This is just a demo version for predict***\n"
    "Usage:predict data_file model_file output_file\n"
    );
    exit(1);
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

int main(int argc, char** argv) {
    if(argc != 4) {
        printUsage();
    }
    vector<string> test_text,test_label,test_title,test_catagory;

    string content;
    string testdir="./";


    test_title = listFiles(testdir+argv[1]+"/");
    readfile(test_title,test_text,testdir+argv[1]+"/");

    for(int i=0;i<test_text.size();i++)
    {
        test_label.push_back("0");

    }


    ifstream model_file(argv[2],ios::in);
    ofstream output_file(argv[3],ios::out);

    if(!model_file.is_open()) {
        printf("Cannot open %s\n",argv[2]);
        exit(1);
    }
    if(!output_file.is_open()) {
        printf("Cannot open %s\n",argv[3]);
        exit(1);
    }
    cout << "Now Starting Parsing " << argv[1] << endl;

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
    predict(test_text,test_label,test_title,argv[2],argv[3]);
    dlclose(handle);
    vector <int> catagory;
    string str;
    ifstream i("out");
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

}

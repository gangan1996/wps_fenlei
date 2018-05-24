#include <iostream>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
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
 	
            files.push_back(ptr->d_name); 

	 
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
	vector<string> test_text,test_label,test_title;

	string content;

	test_title = listFiles("./"+argv[1]);
	readfile(test_title,test_text,"./"+argv[1]);

	for(int i=0;i<test_text.size();i++)
	{
		test_label.push_back("0");

	}

	
	ifstream model_file(argv[2],ios::in);
	ofstream output_file(argv[3],ios::out);
	if(!test_file.is_open()) {
		printf("Cannot open %s\n",argv[1]);
		exit(1);
	}
	if(!model_file.is_open()) {
		printf("Cannot open %s\n",argv[2]);
		exit(1);
	}
	if(!output_file.is_open()) {
		printf("Cannot open %s\n",argv[3]);
		exit(1);
	}
	cout << "Now Starting Parsing " << argv[1] << endl;  
	test_file.close();
	model_file.close();
	output_file.close();
	char *error;
    void *handle = dlopen("../build-demo-Desktop_Qt_5_10_1_GCC_64bit-Debug/libdemo.so",RTLD_NOW);
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
}

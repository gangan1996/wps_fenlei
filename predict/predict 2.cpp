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


int main(int argc, char** argv) {
	if(argc != 4) {
		printUsage();
	}	
	vector<string> test_text,test_label,test_title;
	ifstream test_file(argv[1],ios::in);
	string content;
	while(!test_file.eof())
	{
		char *tmp=new char[4096];
		test_file.getline(tmp,4096);
		content+=tmp;
		delete tmp; 
        cout<<"while";
	}
	test_text.push_back(content);
	test_label.push_back("0");
	test_title.push_back(argv[1]);
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

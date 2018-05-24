#include <iostream>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cstring>
#include <dirent.h>
#include <vector>
using namespace std;

int readTxtData(string path,vector<string> &text,vector<string> &labels,vector<string> &titles) {
    DIR *dir,*sub_dir;
    struct dirent *ptr,*sub_ptr;
    string p;
    string label;
    if ((dir = opendir(path.c_str())) != NULL) {
        while ((ptr = readdir(dir)) != NULL) {
            if (ptr->d_type == 4) {
                if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0) {
					label = p.assign(ptr->d_name);
					if(!label.compare("offical")) {
						label = "0";
					} else if (!label.compare("article")) {
						label = "1";
					} else if (!label.compare("resume")) {
						label = "2";
					} else if (!label.compare("contract")) {
						label = "3";
					} else {
						cout << "Error Foler: " << label << " does not belong to 4 legal categorys" << endl;
						return 0;
					}
					string new_path= p.assign(path).append("/").append(ptr->d_name);
					sub_dir = opendir(new_path.c_str());
					while((sub_ptr = readdir(sub_dir)) != NULL) {
						if (sub_ptr->d_type != 4) {
							titles.push_back(p.assign(sub_ptr->d_name));
							labels.push_back(label);
							string txtPath = p.assign(new_path).append("/").append(sub_ptr->d_name);
							ifstream ifs(txtPath.c_str(),ios::in);
							if(!ifs.is_open()) {
								cout << "Cannot open"  << txtPath << endl;
								exit(1);
							}
							std::istreambuf_iterator<char> begin(ifs);
							std::istreambuf_iterator<char> end;
							string content(begin, end);
							ifs.close();
							text.push_back(content);
						}
					}
					closedir(sub_dir);
            	} 
        	}
        }
        closedir(dir);
	} else {
		cout << "Path does not exists" << endl;
		return 0;
	}
	return 1;
}

int readTxtData2(string path,vector<string> &text,vector<string> &labels,vector<string> &titles) {
    DIR *dir,*sub_dir;
    struct dirent *ptr,*sub_ptr;
    string p;
    string label;
    if ((dir = opendir(path.c_str())) != NULL) {
        while ((ptr = readdir(dir)) != NULL) {
            if (ptr->d_type == 4) {
                if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0) {
                    label = p.assign(ptr->d_name);
                    if(!label.compare("tiyu")) {
                        label = "0";
                    } else if (!label.compare("caijing")) {
                        label = "1";
                    } else if (!label.compare("yule")) {
                        label = "2";
                    } else if (!label.compare("fangchan")) {
                        label = "3";
                    } else if (!label.compare("jiaoyu")) {
                        label = "4";
                    } else if (!label.compare("keji")) {
                        label = "5";
                    } else if (!label.compare("shishang")) {
                        label = "6";
                    } else if (!label.compare("shizheng")) {
                        label = "7";
                    } else if (!label.compare("youxi")) {
                        label = "8";
                    } else if (!label.compare("jiaju")) {
                        label = "9";
                    } else {
                        cout << "Error Foler: " << label << " does not belong to 4 legal categorys" << endl;
                        return 0;
                    }
                    string new_path= p.assign(path).append("/").append(ptr->d_name);
                    sub_dir = opendir(new_path.c_str());
                    while((sub_ptr = readdir(sub_dir)) != NULL) {
                        if (sub_ptr->d_type != 4) {
                            titles.push_back(p.assign(sub_ptr->d_name));
                            labels.push_back(label);
                            string txtPath = p.assign(new_path).append("/").append(sub_ptr->d_name);
                            ifstream ifs(txtPath.c_str(),ios::in);
                            if(!ifs.is_open()) {
                                cout << "Cannot open"  << txtPath << endl;
                                exit(1);
                            }
                            std::istreambuf_iterator<char> begin(ifs);
                            std::istreambuf_iterator<char> end;
                            string content(begin, end);
                            ifs.close();
                            text.push_back(content);
                        }
                    }
                    closedir(sub_dir);
                }
            }
        }
        closedir(dir);
    } else {
        cout << "Path does not exists" << endl;
        return 0;
    }
    return 1;
}

void printUsage() {
	printf(
	"***This is just a demo version for train***\n"
	"Usage: demo [options] train_directory model_file\n"
	"options:\n"
	"-t type for classification,0 for traditional model,1 for neural networks model,default is 0\n"
	);
	exit(1);
}


int main(int argc, char** argv) {
	int mode = 0;
	int i;
	for(i = 1;i < argc;i++) {
		if(argv[i][0] != '-')
			break;
		i++;
		switch(argv[i-1][1]) {
			case 't':
				mode = atoi(argv[i]);
				if(mode != 0 && mode != 1) {
					cout << "Error: Unknown Mode" << endl;
					printUsage();
				}
				break;
			default:
				cout << "Error: Unknown Option" << endl;
				printUsage();
		}
	}
	if(i != argc - 2) {
		printUsage();
	}	
	vector<string> train_text,train_label,train_title;
	string train_directory(argv[i]);
	ofstream model_file(argv[i+1],ios::out);
	if(!model_file.is_open()) {
		printf("Cannot open %s\n",argv[i+2]);
		exit(1);
	}
	cout << "Now Starting Collecting " << argv[i] << endl; 
    int ok = readTxtData2(train_directory,train_text,train_label,train_title);
	if(ok == 0) {
		cout << "Parsing Error in " << argv[i] << endl;
		exit(1);
	}
	model_file.close();
	char *error;
    void *handle = dlopen("../build-demo-Desktop_Qt_5_10_0_GCC_64bit-Debug/libdemo.so",RTLD_NOW);
	void (*train1)(vector<string> &,vector<string> &,char *);
	void (*train2)(vector<string> &,vector<string> &,vector<string> &,char *);
	if(!handle) {
		fprintf(stderr,"%s\n",dlerror());
        std::cout<<"123";
		exit(1);
	}
	*(void **)(&train1) = dlsym(handle,"train1");
	if ((error = dlerror()) != NULL)  {
		fprintf (stderr, "%s\n", error);
		exit(1);
	}
	*(void **)(&train2) = dlsym(handle,"train2");
	if ((error = dlerror()) != NULL)  {
		fprintf (stderr, "%s\n", error);
		exit(1);
	}
	if(mode == 0)
		train1(train_text,train_label,argv[i+1]);
	else 
		train2(train_text,train_label,train_title,argv[i+1]);
	dlclose(handle);
}

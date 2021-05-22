#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
using namespace std;

void readfromfile(string filename, int* &p, int* &q, int& size);

void* sum(void* param) {
	int *new_ptr = *(int**) param;
	int *a=new int;
	*a=new_ptr[0]+new_ptr[1];
	pthread_exit( (void*) a);
}

int main() {
  	int size = 0;
	int* p;
	int* q;
	ofstream fout("result");
	readfromfile("input.txt",p,q,size);
	int *arr1 = new int[size]; 
	int *arr = new int[2];
	pthread_t id[size];
	for (int i=0; i < size; i++) {
		arr[0]=p[i];
		arr[1]=q[i];
		if (pthread_create(&id[i], NULL, &sum, &arr)==-1) {
			cout<<"Thread Creation Failed!"<<endl;
			return 1;
		}
		int *ptr;
		pthread_join(id[0], (void**) &ptr);
		arr1[i]=*ptr;
	}
	for (int i=0;i<size;i++)
	{
		fout<<arr1[i];
		fout<<"\n";
	}
	delete []arr1;
	delete []arr;
	delete p;
	delete q;
}

void readfromfile(string filename,int* &p, int* &q, int& size) {
	int a[100];
	int b[100];
	int i = 0;
	ifstream fin(filename);
	if (fin.is_open()) {
		while (!fin.eof()) {
			fin >> a[i];
			fin >> b[i];
			i++;
		}
	}
	size = i-1;
	p = new int[size];
	q = new int[size];
	for (int i = 0; i < size; i++) {
		p[i] = a[i];
		q[i] = b[i];
	}
}

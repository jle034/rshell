#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <cstdlib>
#include "Timer.h"

using namespace std;

void io_stream(char* input,char* output);
void rwchar(char* input,char* output);
void rwbuff(char* input,char* output);

int main(int argc, char** argv)
{
	if(argc < 3 || argc > 4)
	{
		cerr << "Error: invalid number of arguments\n";
		return -1; //function didn't finish without errors
	}

	char* input_file = argv[1];
	char* output_file = argv[2];
	struct stat buf;
	//if input file doesn't exist, give error message
	if(stat(input_file,&buf)!=0)
	{
		perror("stat");
		//cerr << "File does not exist\n";
		exit(1);
	}
	//if output file already exists, give error message
	if(stat(output_file, &buf)==0)
	{
		perror("stat");
		//cerr << "Output file should not already exist\n";
		exit(1);
	}
	//if input file is directory, give error
	if(buf.st_mode & S_IFDIR)
	{
		cerr << "Input file should not be a directory\n";
		exit(1);
	}

	if(argc==4)
	{
		Timer uno;
		double wTime,uTime,sTime;
		uno.start();
		io_stream(input_file, output_file);	
		uno.elapsedTime(wTime,uTime,sTime);
		cout << wTime<< "---"  << uTime << "---"  << sTime << endl; 
		
		
		Timer dos;
		double w2Time,u2Time,s2Time;
		dos.start();
		rwchar(input_file, output_file);
		dos.elapsedTime(w2Time,u2Time,s2Time);
		cout << w2Time<< "---"  << u2Time << "---"  << s2Time << endl; 
		
		Timer tres;
		double w3Time,u3Time,s3Time;
		tres.start();
		rwbuff(input_file, output_file);
		tres.elapsedTime(w3Time,u3Time,s3Time);
		cout << w3Time<< "---"  << u3Time << "---"  << s3Time << endl; 

	}
	if(argc==3)
	{
		rwbuff(input_file,output_file);
	}

	return 0;
}

void io_stream(char* input,char* output)
{
	ifstream fin(input);
	ofstream fout(output);
	char c;
	while(fin.get(c))
	{
		fout << c;
	}
	fin.close();
	fout.close();

	return;
}
void rwchar(char* input,char* output)
{
	int fdin,fdout;
	char c;
	if(-1==(fdout=open(output,O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR)))
	{
		perror("open");
		return ;	
	}
	if(-1==(fdin=open(input,O_RDONLY)))
	{
		perror("open");
		return ;	
	}
	size_t buf_size=1;
	int size;
	int size2;
	while(((size) = (read(fdin,&c,buf_size))))
	{
		if(size == -1)
		{
			perror("read");
			exit(1);
		}
		(size2)=(write(fdout,&c,size));
		if(size2==-1)
		{
			perror("write");
			exit(1);
		}
	}
	
	if(-1==close(fdin))
	{
		perror("close");
		exit(1);
	}
	if(-1==close(fdout))
	{
		perror("close");
		exit(1);
	}

	return;
}
void rwbuff(char* input,char* output)
{
	int fdin,fdout;
	char c[BUFSIZ];
	if(-1==(fdout=open(output,O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR)))
	{
		perror("open");
		return ;	
	}
	if(-1==(fdin=open(input,O_RDONLY)))
	{
		perror("open");
		return ;	
	}
	int size;
	int size2;
	while(((size) = (read(fdin,&c,sizeof(c)))))
	{
		if(size == -1)
		{
			perror("read");
			exit(1);
		}
		(size2)=(write(fdout,&c,size));
		if(size2==-1)
		{
			perror("write");
			exit(1);
		}
	}
	
	if(-1==close(fdin))
	{
		perror("close");
		exit(1);
	}
	if(-1==close(fdout))
	{
		perror("close");
		exit(1);
	}

	return;
}

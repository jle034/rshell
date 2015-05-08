#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <vector>

using namespace std;

void recursiveRemove(char* directory)	{
	DIR* dir;
	dir = opendir(directory);
	if(NULL == dir)	{
		perror("cannot open directory");
		return;
	}
	
	struct dirent* directoryEntries;
	while((directoryEntries = readdir(dir)) != NULL)	{
		char* subDirectory = new char[strlen(directory) + strlen(directoryEntries->d_name) + 2];
		strcpy(subDirectory, directory);
		strcat(subDirectory, "/");
		strcat(subDirectory, directoryEntries->d_name);
		if(directoryEntries->d_type & DT_DIR)	{
			if(strcmp(directoryEntries->d_name, ".") == 0 || strcmp(directoryEntries->d_name, "..") == 0)	{
				continue;
			}
			recursiveRemove(subDirectory);
		}
		else	{
			unlink(subDirectory);
		}
		delete [] subDirectory;
	}
	if(directoryEntries == NULL)
		perror("error in readdir");
	
	if (closedir(dir) == -1)	{
		perror("error in closing directory");
	}
	if (rmdir(directory) == -1)	{
		perror("error in removing directory");
	}
}

int main(int argc, char ** argv)	{
	vector<char*> names;
	for(int i = 1; i < argc; i++)	{
		names.push_back(argv[i]);	
	}
	
	//char* rFlg = "-r"; 
	bool rFound = false;
	for(vector<char*>::iterator it = names.begin(); it !=  names.end(); it++)	{
		//int loc = names.at(i).find(rFlg);
		//if (loc >= 0)	{
		if(strncmp(*it, "-r", 9999) == 0)	{
			names.erase(it);
			rFound = true;
			break;
		}
	}

	for(int i = 0; i < names.size(); i++)	{
		struct stat temp;
		int x = stat(names.at(i), &temp);
		if(x <= -1)	{
			perror("error in stat");
		}
		if(S_ISDIR(temp.st_mode) && !(rFound))	{
			perror("Is a directory");		
		}
		else	{
			if(S_ISDIR(temp.st_mode))	{
				int success = rmdir(names.at(i));
				if (success <= -1)	{
					recursiveRemove(names.at(i));
				}
			}

			else	{
				unlink(names.at(i));
			}
		}
	}














}

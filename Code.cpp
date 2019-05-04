#include <iostream>
#include <string>
#include <string.h>
using namespace std;
const int Num_Blocks=100;
const int Size_Blocks=50;
static char *List_Arr[Num_Blocks];
int Free_Bool_Arr[Num_Blocks],File_Bool_Arr[Num_Blocks];
//int dread (int addr,char*buff);
void InitialSetter();
int fseek(int fileid, int rootlen);
int dwrite(int addr,char *storage);
int fmkdir(char *name);
int FDsearcher(char*name);
int fopen (char*name);
int fwrite (int fileid,char *storage,int length);
int cd(char *name);
int fls();
int fclose(int fileid);
int fread (int fileid,char *storage,int length);
int check=0,fault=0,nofault=1,counter=0,counter2=0, tracker=0,tracker2=0,File_Tracker=0,flag=0,flag1=0,File_Flag=0,File_Read=0,rootblocks=1,current =0;

int main (){
	InitialSetter();
	int z=0,fd=-1;
	char c[6],storage[16]="My name is Khan",buff[200];
	cout<<"Enter name of Directory (size 6)"<<endl;
	cin>>c;
	int i=0;
	while(i<10)
	{
		fmkdir(c);
		i++;
	}
	fd=fopen(c);
	fwrite(fd,storage,strlen(storage));
	fread(fd,buff,strlen(storage));
	fclose(fd);
	cd (c);
	fls();
	return 0;
}


int fls(){
	if(check==1){
		cout<<"Listing All Data"<<endl<<endl;
		int root=0;
		for(;List_Arr[root][Size_Blocks-1]!='\0';)
		{
			cout<<List_Arr[root]<<endl;
			root=List_Arr[root][Size_Blocks-1];   //used as 1 level of indexing
		}
		cout<<List_Arr[root]<<endl;
		return 0;
	}
	else
		cout<<"Data has not been Initialized"<<endl;
	return 0;
}
//int dread (int addr,char*buff)
//{
//	char * storageptr;
//	int i;
//	if (addr<Num_Blocks)
//	{
//	if (List_Arr[addr]!='\0')
//	{
//		storageptr=List_Arr[addr];
//		for(i=0;i<Size_Blocks-1;i++)
//			buff[i]=*storageptr++;
//	}
//	else 
//	{
//		for(i=0;i<Size_Blocks-1;i++)
//			buff[i]=0;
//	}
//	return nofault;
//	}
//		return fault;
//}

void InitialSetter(){
	if(Num_Blocks>=Size_Blocks+Size_Blocks)
	{
		for (int i=0;i<Num_Blocks;i++)
		{
			File_Bool_Arr[i]=0;
			Free_Bool_Arr[i]=0;
			List_Arr[i]=new char[Size_Blocks];
			for(int ii=0;ii<Size_Blocks;ii++)
				List_Arr[i][ii]='\0';
		}
		Free_Bool_Arr[0]=1;
		check=1;
	}
	else
		cout<<"Kindly increase Number of Blocks"<<endl;
}

int fseek(int fileid, int rootlen){
	int x=strlen( List_Arr[fileid]);
	return x;
}

int fclose(int fileid){
	if(File_Bool_Arr[fileid]!=0)
		File_Bool_Arr[fileid]=0;
	else
		cout<<"File is already close"<<endl;
	return 0;
}
int dwrite(int addr,char *storage){
	flag=0,tracker=addr;
	int i, rootlen=0,bsize=0;
	char * storageptr;
	if(List_Arr[addr]!='\0')
		rootlen=fseek(addr, 0);
	int storagelen=strlen(storage);
	bsize=Size_Blocks-rootlen;
	if (addr>=Num_Blocks)
		return fault;
	if (storagelen<=bsize-1)
	{
		storageptr=List_Arr[addr];
		for(i=rootlen;i<Size_Blocks-1;i++)
			storageptr[i]=*storage++;
		flag=1;
	}
	else if (List_Arr[tracker][Size_Blocks-1]!='\0')
	{
		int k=0;
		while (k!=counter)
		{
			tracker=List_Arr[tracker][Size_Blocks-1];
			storageptr=List_Arr[tracker];
			rootlen=strlen(List_Arr[tracker]);
			storagelen=strlen(storage);
			bsize=Size_Blocks-rootlen;
			if (storagelen<=bsize-1)
			{
				storageptr=List_Arr[tracker];
				int m=0;
				for(i=rootlen;i<Size_Blocks-1;i++)
				{
					List_Arr[tracker][i]=storage[m];
					m++;
				}
				flag=1;
				return nofault;
			}
			k++;
		}

	}
	if(flag==0)
	{
		int x=-1;
		for ( int m=0;m!=Num_Blocks-1;m++)
		{
			if (Free_Bool_Arr[m]==0)
			{
				x=m;
				break;
			}
		}
		if (x==-1)
		{
			cout<<"Disk is Full"<<endl;
			return fault;
		}
		else {
			Free_Bool_Arr[x]=1;
			List_Arr[tracker][Size_Blocks-1]=x;
			counter++;
			storageptr=List_Arr[x];
			for(i=0;i<Size_Blocks-1;i++)
			{
				storageptr[i]=*storage++;
				storageptr[i++]='\0';
			}
		}
	}
	return nofault;
}


int fmkdir(char *name){
	File_Flag=0;
	char temporary[50];
	if(File_Flag==1)
	{temporary[0]='%';temporary[1]='F';temporary[2]='I';temporary[3]='L';temporary[4]='%';}
	else
	{temporary[0]='%';temporary[1]='F';temporary[2]='O';temporary[3]='L';temporary[4]='%';}
	int destination=-1,i=0;
	for ( i=0;i<Num_Blocks;i++)
	{
		if (Free_Bool_Arr[i]==0){
			destination=i;
			break;
		}
	}
	if (destination==-1){
		cout<<"Disk is Full"<<endl;
		return -1;
	}
	else{
		temporary[5]=destination+'0';
		Free_Bool_Arr[i]=1;
		temporary[6]='%';
		int d= strlen(name);
		for (int j=0;j<d;j++){
			temporary[j+7]=name[j];
			temporary[j+8]='@';
			temporary[j+9]='\0';
		}
		dwrite(current,temporary);
	}
	return 0;
}

int FDsearcher(char*name){
	int index=0,x=strlen(name), j=0, count=0;
	for(;count<=counter+1;count++)
	{
		for (int i=0;i<Size_Blocks;i++)
		{
			if (List_Arr[index][i]==name[j])
			{
				j++;
				if ((j==x) && (List_Arr[index][i+1]=='@') )
					return List_Arr[index][i-x-1];
			}
			else 
				j=0;
		}
		if (List_Arr[Size_Blocks-1]!='\0')
			index=List_Arr[index][Size_Blocks-1];
	}
	return -1;
}

int fopen (char*name)
{
	int fd=FDsearcher(name);
	if (fd!=-1){
		File_Bool_Arr[fd]=1;
		return fd;
	}
	File_Flag=1;
	fmkdir(name);
	int fd1=FDsearcher(name);
	File_Bool_Arr[fd]=1;
	return fd1;
}

int fwrite (int fileid,char *storage,int length)
{
	if (File_Bool_Arr[fileid]!=1)
		cout<<"File is Not open"<<endl;
	else
	{
		int reading=0,writelength=length,i=0, Head_Length=0, B_size=0;
		if (fileid>Num_Blocks)
			return -1;
		File_Tracker=fileid;
		char * storageptr;
		if(List_Arr[fileid]!='\0')
			B_size=Size_Blocks-Head_Length;
		storageptr=List_Arr[fileid];
		for(i=0;i<Size_Blocks-1 && length>0;i++)
		{
			if (flag1==1){
				storage[reading++]=storageptr[i];
				storage[reading+1]='\0';
				length--;
			}
			else{
				storageptr[i]=*storage++;
				length--;
			}
		}
		while(length>0)
		{
			if (List_Arr[File_Tracker][Size_Blocks-1]!='\0')
			{
				for(int k=0;k!=counter2;k++)
				{
					File_Tracker=List_Arr[File_Tracker][Size_Blocks-1];
					storageptr=List_Arr[File_Tracker];
					storageptr=List_Arr[File_Tracker];
					int m=0;
					for(i=strlen(storageptr);i<Size_Blocks-1&&length>0;i++){
						if (flag1==1){
							storage[reading++]=storageptr[i];
							storage[reading+1]='\0';
							length--;
						}
						else{
							List_Arr[File_Tracker][i]=storage[m];
							m++;
							length--;
						}
					}
					if(length==0)
						return length;
				}
			}
			if(length>0)
			{
				int x=-1;
				for ( x=0;x!=Num_Blocks-1;x++)
				{
					if (Free_Bool_Arr[x]==0)
						break;
				}
				if (x==-1)
				{
					writelength=writelength-length;
					return writelength;
				}
				else 
				{
					Free_Bool_Arr[x]=1;
					List_Arr[File_Tracker][Size_Blocks-1]=x;
					counter2++;
					storageptr=List_Arr[x];
					for(i=0;i<Size_Blocks-11&&length>0;i++)
					{
						if (flag1==1)
						{
							storage[reading++]=storageptr[i];
							storage[reading+1]='\0';
							length--;
						}
						else
						{
							storageptr[i]=*storage++;
							length--;
						}
					}
					if (length==0)
						return length;
				}
			}
		}
		return length;
	}
	return fault;
}

int fread (int fileid,char *storage,int length)
{
	flag1=1;
	int x= fwrite(fileid,storage,length);
	cout<<storage<<endl;
	flag1=0;
	return x;
}

int cd(char *name)
{
	int fd=FDsearcher(name);
	if (fd==-1)
	{
		cout<<"No Folder Found"<<endl;
		return -1;
	}
	else
	{
		current=fd;
		return 0;
	}
}
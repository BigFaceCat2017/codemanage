
//dll ��Ҫһ��ʱ���ʼ�������Կ�ʼ������ʱ����е���������

#include <iostream>
#include <Windows.h>
#include <wininet.h> 
#pragma comment(lib, "wininet.lib ") 

int main()
{
	HINSTANCE hInst = LoadLibraryA("Sunday.dll");
	if (!hInst)
	{
		std::cout<<"�޷����� Sunday.dll!";
		getchar();
		return 0;
	}
	std::cout<<"dll ��ʼ����ɣ�"<<"\n";
    std::cout<<"�����ֿ⣡��ֻ��Ҫ�ڳ���ͷ����һ�μ��ɣ�"<<"\n";
	typedef int (CALLBACK* LPLoadLib)(char[],char[]);
	LPLoadLib LoadLibFromFile = (LPLoadLib)GetProcAddress(hInst, "LoadLibFromFile");
	
	
	
	int index = LoadLibFromFile ("12306.lib","123");
	
	if (index == -1)
	{
		std::cout<<"����ʶ������";
		getchar();
		return 0;
	}

	std::cout<<"����ʶ�����ɡ�"<<"\n";

	std::cout<<"����ͼƬ�С�����"<<"\n";


/*
	typedef bool (CALLBACK* LPGetCode)(int,char[],char[]);
	LPGetCode GetCodeFromFile = (LPGetCode)GetProcAddress(hInst, "GetCodeFromFile");
*/
	typedef bool (CALLBACK* LPGetCodeFromBuffer)(int,char*,int,char[]);
	LPGetCodeFromBuffer GetCodeFromBuffer = (LPGetCodeFromBuffer)GetProcAddress(hInst, "GetCodeFromBuffer");

	char result[16];

	
	HANDLE pfile = CreateFile("6.png",GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);

	if(pfile == INVALID_HANDLE_VALUE){
		std::cout<<"�ļ���ʧ�ܣ�";
		CloseHandle(pfile);
		return 0;
	}

	unsigned long filesize = GetFileSize (pfile, NULL);
	char* buffer = new char[filesize]; 
	unsigned long readsize;
	ReadFile(pfile,buffer,filesize,&readsize,NULL);
	CloseHandle(pfile);

	long nCount;
	nCount=GetTickCount();

	if (GetCodeFromBuffer(index,buffer,filesize,result))
		std::cout<<"ʶ����� ��"<<result<<" ,ʶ����ʱ�� "<<GetTickCount()-nCount;
	else
		std::cout<<"ʶ��ʧ�ܣ�";
	getchar();
	return 0;
}


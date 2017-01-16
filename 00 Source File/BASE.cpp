#include "BASE.h"
char g_szRootPath[1124]={0};

//
//
//
void InitDirectory(char* root)
{
	strcpy(g_szRootPath,root);
}

//
//
//
void SetRootDirectory()
{
	SetCurrentDirectory(g_szRootPath);
}
//
//
//
void SetSoundDirectory()
{
	char tmp[512]={0};
	strcpy(tmp,g_szRootPath);
	strcat(tmp,"\\04 Sound File");
	SetCurrentDirectory(tmp);
}
//
//
//
void SetDataDirectory()
{
	char tmp[512]={0};
	strcpy(tmp,g_szRootPath);
	strcat(tmp,"\\01 Data File");
	SetCurrentDirectory(tmp);
}
//
//
//
void SetVisualDirectory()
{
	char tmp[512]={0};
	strcpy(tmp,g_szRootPath);
	strcat(tmp,"\\02 Visual File");
	SetCurrentDirectory(tmp);
}
//
//
//
void SetShaderDirectory()
{
	char tmp[512]={0};
	strcpy(tmp,g_szRootPath);
	strcat(tmp,"\\03 Shader File");
	SetCurrentDirectory(tmp);
}

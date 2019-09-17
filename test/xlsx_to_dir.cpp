#include "xlsx_to_dir.h"
#include <direct.h>
#include <cerrno>
#include <ShlDisp.h>
#include <stdio.h>
#include <atlstr.h>
#include <ShellAPI.h>
#pragma comment (lib, "shell32.lib")

void XlsxToDir::Unpacking(const std::string &output_file_name_zip, const std::string &output_directory, const std::string &input_file_name) {
  _mkdir(output_directory.c_str()); 
  if (errno == ENOENT)
    throw "error create directory for content xlsx file!";
  std::rename(input_file_name.c_str(), output_file_name_zip.c_str());
  UnzipFile(output_file_name_zip, output_directory);
  std::rename(output_file_name_zip.c_str(), input_file_name.c_str());
}

void XlsxToDir::UnzipFile(const std::string &file_name, const std::string &directory_name)
{
  CString strSrc(file_name.c_str());
  CString strDest(directory_name.c_str());
  BSTR lpZipFile = strSrc.AllocSysString();
  BSTR lpFolder = strDest.AllocSysString();
  IShellDispatch *pISD;
  Folder  *pZippedFile = 0L;
  Folder  *pDestination = 0L;
  long FilesCount = 0;
  IDispatch* pItem = 0L;
  FolderItems *pFilesInside = 0L;
  VARIANT Options, OutFolder, InZipFile, Item;
  CoInitialize( NULL);
  if (CoCreateInstance(CLSID_Shell, NULL, CLSCTX_INPROC_SERVER, IID_IShellDispatch, (void **)&pISD) != S_OK)
    throw "error create shell object!";
  InZipFile.vt = VT_BSTR;
  InZipFile.bstrVal = lpZipFile;
  pISD->NameSpace( InZipFile, &pZippedFile);
  if (!pZippedFile) {
	pISD->Release();
	throw "error getting pointer zip archive!";
  }
  OutFolder.vt = VT_BSTR;
  OutFolder.bstrVal = lpFolder;
  pISD->NameSpace( OutFolder, &pDestination);
  if(!pDestination)
  {
    pZippedFile->Release();
    pISD->Release();
	throw "error getting pointer destination folder!";
  }
  pZippedFile->Items(&pFilesInside);
  if(!pFilesInside) {
    pDestination->Release();
    pZippedFile->Release();
    pISD->Release();
	throw "error reading files in archive!";
  }	    
  pFilesInside->get_Count( &FilesCount);
  if( FilesCount < 1) {
    pFilesInside->Release();
    pDestination->Release();
    pZippedFile->Release();
    pISD->Release();
	throw "archive is empty!";
  }
  pFilesInside->QueryInterface(IID_IDispatch,(void**)&pItem);
  Item.vt = VT_DISPATCH;
  Item.pdispVal = pItem;
  Options.vt = VT_I4;
  Options.lVal = 1024 | 512 | 16 | 4;//http://msdn.microsoft.com/en-us/library/bb787866(VS.85).aspx
  bool retval = pDestination->CopyHere( Item, Options) == S_OK;
  pItem->Release();
  pItem = 0L;
  pFilesInside->Release();
  pFilesInside = 0L;
  pDestination->Release();
  pDestination = 0L;
  pZippedFile->Release();
  pZippedFile = 0L;
  pISD->Release();
  pISD = 0L;
  if (!retval)
	  throw "error copying files from archive!";
};
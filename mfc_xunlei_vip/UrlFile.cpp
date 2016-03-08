#include "stdafx.h"
#include "UrlFile.h"
/*
* �����Linux�¿�����C������Ҫͷ�ļ�unistd.h����VC��û�и�ͷ�ļ���
* ������VC�������Ǳ�������������ݱ���Ϊunistd.h�����Խ��������⡣
*/
#ifdef _WIN32
#include <io.h>
#include <process.h>
#else
#include<unistd.h>
#endif

#include <./curl/curl.h>
#pragma comment(lib, "./lib/libcurl")  //���curl��̬��
#pragma  warning(disable:4996)
UrlFile::UrlFile()
{
}


UrlFile::~UrlFile()
{
}

size_t UrlFile::write_data(void* ptr, size_t size, size_t nmemb, void* stream)
{
	size_t written = fwrite(ptr, size, nmemb, (FILE*)stream);
	return written;
}

// ����URL�ļ����ݵ��ļ�
bool UrlFile::url2file(const char* web_url, const char* savefile)
{
	CURL* curl_handle;
	const char* pagefilename = savefile;
	FILE* pagefile;


	curl_global_init(CURL_GLOBAL_ALL);

	/// init the curl session  ��ʼ��cURLЭ��
	curl_handle = curl_easy_init();

	/// set URL to get here   ����URL������
	curl_easy_setopt(curl_handle, CURLOPT_URL, web_url);

	/// Switch on full protocol/debug output while testing  ����ʱ����������Э��/�������
	curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 0L);

	/// disable progress meter, set to 0L to enable and disable debug output   ���ý��ȱ�����Ϊ0L���úͽ��õ������
	curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);

	/// send all data to this function  �������ݷ��͸��������
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, UrlFile::write_data);

	/// open the file   д�ļ�������ļ�
	pagefile = fopen(pagefilename, "wb");
	if (pagefile) {

		/// write the page body to this file handle  дҳ���ļ��������ļ����
		curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, pagefile);

		/* get it! */
		curl_easy_perform(curl_handle);

		/* close the header file */
		fclose(pagefile);
	}

	/* cleanup curl stuff */
	curl_easy_cleanup(curl_handle);

	return true;
}

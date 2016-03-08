#include "stdafx.h"
#include "UrlFile.h"
/*
* 许多在Linux下开发的C程序都需要头文件unistd.h，但VC中没有个头文件，
* 所以用VC编译总是报错。把下面的内容保存为unistd.h，可以解决这个问题。
*/
#ifdef _WIN32
#include <io.h>
#include <process.h>
#else
#include<unistd.h>
#endif

#include <./curl/curl.h>
#pragma comment(lib, "./lib/libcurl")  //添加curl静态库
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

// 保存URL文件内容到文件
bool UrlFile::url2file(const char* web_url, const char* savefile)
{
	CURL* curl_handle;
	const char* pagefilename = savefile;
	FILE* pagefile;


	curl_global_init(CURL_GLOBAL_ALL);

	/// init the curl session  初始化cURL协议
	curl_handle = curl_easy_init();

	/// set URL to get here   设置URL到这里
	curl_easy_setopt(curl_handle, CURLOPT_URL, web_url);

	/// Switch on full protocol/debug output while testing  测试时开启完整的协议/调试输出
	curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 0L);

	/// disable progress meter, set to 0L to enable and disable debug output   禁用进度表，设置为0L启用和禁用调试输出
	curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);

	/// send all data to this function  所有数据发送给这个函数
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, UrlFile::write_data);

	/// open the file   写文件到结果文件
	pagefile = fopen(pagefilename, "wb");
	if (pagefile) {

		/// write the page body to this file handle  写页面文件到保存文件句柄
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

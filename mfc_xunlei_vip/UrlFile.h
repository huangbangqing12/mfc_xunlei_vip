#pragma once
class UrlFile
{
public:
	UrlFile();
	virtual ~UrlFile();
	//   使用curl保存url文件的回调函数
	static size_t write_data(void* ptr, size_t size, size_t nmemb, void* stream);
	// 将url指向的文件保存
	bool url2file(const char* web_url, const char* savefile);
};


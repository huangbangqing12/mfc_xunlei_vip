#pragma once
class UrlFile
{
public:
	UrlFile();
	virtual ~UrlFile();
	//   ʹ��curl����url�ļ��Ļص�����
	static size_t write_data(void* ptr, size_t size, size_t nmemb, void* stream);
	// ��urlָ����ļ�����
	bool url2file(const char* web_url, const char* savefile);
};


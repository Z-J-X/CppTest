#if 0
#include <iostream>
#include <filesystem>
using namespace std;
using namespace std::filesystem;
int main()
{
	path str("C:\\Windows");
	if (!exists(str))		//�����ȼ��Ŀ¼�Ƿ���ڲ���ʹ���ļ����.
		return 1;
	directory_entry entry(str);		//�ļ����
	if (entry.status().type() == file_type::directory)	//��������C++11��ǿö������
		cout << "��·����һ��Ŀ¼" << endl;
	directory_iterator list(str);	        //�ļ��������
	for (auto& it : list)
		cout << it.path().filename() << endl;	//ͨ���ļ���ڣ�it����ȡpath�����ٵõ�path������ļ�������֮���
	return 0;
}
#endif
#include<iostream>
#include<sstream>

void toStr()
{
	std::stringstream ss;
	ss << "hello world" << 2020 << 3.1415926;
	std::string str;
	ss >> str;
	ss >> str;
	ss >> str;
	//or :
	//str = ss.str();
	std::cout << str << std::endl;
}

void toNumber()
{
	std::stringstream ss;
	ss << "3.1415";
	float data;
	ss >> data;
	std::cout << data << std::endl;
}

class Demo
{
public:
	Demo()
	{
		//throw std::invalid_argument("--- Virtual interface name too long.");
	}
	~Demo()
	{
		std::cout << "hello" << std::endl;
	}
};

unsigned short checksum(unsigned short* buffer, int size)
{
	unsigned long cksum = 0;
	while (size > 1)
	{
		cksum += *buffer++;
		size -= sizeof(unsigned short);
	}
	if (size)
	{
		cksum += *(unsigned short*)buffer;
	}
	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >> 16);
	return (unsigned short)(~cksum);
}

int main()
{
	unsigned char data[] = { 0x45,0x00,0x00,0x21,0xCB,0xBA,0x40,0x00,0x40,0x11,0,0,0xC0,0xA8,0x64,0x05,0xC0,0xA8,0x0A,0x05 };
	unsigned char tmp[20] = { 0 };
	for (int i = 0; i < 20; i++)
	{
		tmp[i] = data[19 - i];
	}
	unsigned short* sdata = (unsigned short*)tmp;
	std::cout <<std::hex <<sdata[9] << std::endl;
	std::cout << checksum(sdata, 20);
	return 0;
}

#include<iostream>
#include <iomanip>

bool addr_to_sys_title(const std::string& addr, std::string& strSysTitle)
{
    unsigned char buf1[16], buf2[8], * dev_name_str;
    unsigned int idx, cnt, dev_name_len, high, low;
    unsigned long long serial_no;

    memset(buf1, 0, sizeof(buf1));
    dev_name_len = addr.size();
    dev_name_str = (unsigned char*)addr.c_str();
    buf2[0] = 'K';
    buf2[1] = 'F';
    buf2[2] = 'M';
    for (idx = 0; idx < dev_name_len; idx++) {
        if ((dev_name_str[idx] >= '0' && dev_name_str[idx] <= '9'))
            break;
        if (idx < 3)
            buf2[idx] = dev_name_str[idx];
    }
    if (idx < dev_name_len) {
        cnt = dev_name_len - idx;
        while (cnt > 12) {
            idx++;
            cnt--;
        }
        memcpy(buf1, dev_name_str + idx, cnt);
    }
    serial_no = atoll((char*)buf1);
    high = serial_no >> 32;
    low = serial_no;
    buf2[3] = high;
    buf2[4] = (low >> 24);
    buf2[5] = (low >> 16);
    buf2[6] = (low >> 8);
    buf2[7] = (low >> 0);
    strSysTitle.clear();
    strSysTitle.append((char*)buf2, 8);
    return true;
}

int main2()
{

    std::string str = "KFC9190300000",des;
    addr_to_sys_title(str, des);
    for (int a : des)
    {
        unsigned int i =(unsigned int) a&0xff ;
        std::cout << std::setiosflags(std::ios::uppercase) << std::hex << std::setw(2) << std::setfill('0') << i << " "<<std::endl;
    }
    std::cout << des << std::endl;
    return 0;
}
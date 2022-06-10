#include"PqxxHandle.h"

#if 1
int main()
{
	PqxxHandle Test;
	Test.Init("postgresql://ami:ami@10.32.233.138:5432/ami_empower");
	Test.GetDevInfo("0000000bdfd63e01");
}
#endif
#include <iostream>
#include <ctime>

#include "encryption.h"
#include "decryption.h"

using std::cin;
using std::cout;
using std::endl;

int main()
{

	cout << "请输入要进行的步骤：" << endl;
	cout << "加密图片请按1，解密图片请按2：";
	char a;
	cin >> a;

	time_t begin, end;
	bool flag;
	double ret;
	begin = clock();

	if ('1' == a)
	{
		cout << "图片加密中，请稍候..." << endl;

		flag = encryption("lena.bmp", "lena1.bmp", 0.3);
		//flag = encryption("2.tif", "2T.tif", 0.3);
		//flag = encryption("4.tif", "4T.tif", 0.3);
		//flag = encryption("7.tif", "7T.tif", 0.3);
		//flag = encryption("10.tif", "10T.tif", 0.3);
		//flag = encryption("s4.img", "s4T.img", 0.3);
		//flag = encryption("s41.img", "s41T.img", 0.3);

		end = clock();
		ret = double(end - begin) / CLOCKS_PER_SEC;
		if (flag)
		{
			cout << "图片加密成功！" << endl;
			cout << "运行时间:" << ret << endl;
		}
		else
		{
			cout << "图片加密失败！" << endl;
		}
	}
	if ('2' == a)
	{
		cout << "图片解密中，请稍候..." << endl;

		flag = decryption("lena1.bmp", "lena2.bmp", 0.3);
		//flag = decryption("2T.tif", "22.tif", 0.3);
		//flag = decryption("4T.tif", "4.tif", 0.3);
		//flag = decryption("7T.tif", "7.tif", 0.3);
		//flag = decryption("10T.tif", "10.tif", 0.3);
		//flag = decryption("s4T.img", "s4.img", 0.3);
		//flag = decryption("s41T.img", "s41.img", 0.3);

		end = clock();
		ret = double(end - begin) / CLOCKS_PER_SEC;
		if (flag)
		{
			cout << "图片解密成功！" << endl;
			cout << "运行时间:" << ret << endl;
		}
		else
		{
			cout << "图片解密失败！" << endl;
		}
	}
}

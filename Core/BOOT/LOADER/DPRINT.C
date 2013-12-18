#include "video.h"
#include "varg.h"

void DPrint(char *fmt, ...)
{
	va_list ap;
	char *p = fmt;
	int data;

	va_start(ap, fmt);
	while (*p != '\0')
	{
		if (*p != '%')
		{
			if (*p == '\n') // 换行符需要被解释为回车+换行
			{
				*p = '\0';
				Print(fmt);
				Print("\r\n");
				fmt = p + 1;
			}
			p++;
			continue; // 为了减少缩进, 用continue取代了else
		}

		// 遇到了%, 先打印出[fmt,p)这一段字符串
		*p = '\0';
		if (fmt != p)
			Print(fmt);

		// 然后对%之后跟的格式符做switch-case判断
		++p;
		switch (*p)
		{
			case 'c':
				data = va_arg(ap, int);
				*p = (char)data; // 覆盖，下一次来打印
				fmt = p; // 新的开始
				p++; //下一次要测试的位置
				break;
			case 'u':
				data = va_arg(ap, int);
				ShowDecU(*(UINT*)(&data));
				p++;
				fmt = p;
				break;
			case 'd':
				data = va_arg(ap, int);
				ShowDec(data);
				p++;
				fmt = p;
				break;
			case 'x': case 'X':// 都显示为大写
				data = va_arg(ap, int);
				ShowHexU(*(UINT*)(&data));
				p++;
				fmt = p;
				break;
			case 's':
				data = va_arg(ap, int);
				Print((char *)data);
				p++;
				fmt = p;
				break;
			case '%':
				fmt = p;
				p++;
				break;
			case '\0': //最后一个字符是%, 我们要把它打印出来
				fmt = p - 1;
				*fmt = '%';//刚刚我们"不小心"把%置0了,现在恢复过来
				break;
			default:// %后跟了一个我们不解释的字符, %和这个字符都打印出来
				fmt = p - 1;
				*fmt = '%';
				p++;
		}
	}
	if (fmt != p)
		Print(fmt);
	va_end(ap);
}

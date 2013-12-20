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
			if (*p == '\n') // ���з���Ҫ������Ϊ�س�+����
			{
				*p = '\0';
				Print(fmt);
				Print("\r\n");
				fmt = p + 1;
			}
			p++;
			continue; // Ϊ�˼�������, ��continueȡ����else
		}

		// ������%, �ȴ�ӡ��[fmt,p)��һ���ַ���
		*p = '\0';
		if (fmt != p)
			Print(fmt);

		// Ȼ���%֮����ĸ�ʽ����switch-case�ж�
		++p;
		switch (*p)
		{
			case 'c':
				data = va_arg(ap, int);
				*p = (char)data; // ���ǣ���һ������ӡ
				fmt = p; // �µĿ�ʼ
				p++; //��һ��Ҫ���Ե�λ��
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
			case 'x': case 'X':// ����ʾΪ��д
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
			case '\0': //���һ���ַ���%, ����Ҫ������ӡ����
				fmt = p - 1;
				*fmt = '%';//�ո�����"��С��"��%��0��,���ڻָ�����
				break;
			default:// %�����һ�����ǲ����͵��ַ�, %������ַ�����ӡ����
				fmt = p - 1;
				*fmt = '%';
				p++;
		}
	}
	if (fmt != p)
		Print(fmt);
	va_end(ap);
}
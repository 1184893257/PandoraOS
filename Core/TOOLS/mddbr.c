#include <stdio.h>

#define BYTES 512

int main(int argc, char **argv)
{
	FILE *in, *out;
	char buf[BYTES];

	if (argc != 3)
	{
		fprintf(stderr, "��Ҫ��������:Pandora DBR�ļ���ԭDBR�ļ�");
		return 1;
	}

	in = fopen(argv[1], "rb");
	fread(buf, 1, BYTES, in);
	fclose(in);

	// ��ȡԭDBR�д� [11, 90) ֮�������
	out = fopen(argv[2], "rb");
	fseek(out, 11, SEEK_SET);
	fread(&buf[11], 1, 90 - 11, out);
	fclose(out);

	out = fopen(argv[2], "wb");
	fwrite(buf, 1, BYTES, out);
	fclose(out);

	return 0;
}

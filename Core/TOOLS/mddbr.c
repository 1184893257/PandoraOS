#include <stdio.h>

#define BYTES 512

int main(int argc, char **argv)
{
	FILE *in, *out;
	char buf[BYTES];

	if (argc != 3)
	{
		fprintf(stderr, "需要两个参数:Pandora DBR文件、原DBR文件");
		return 1;
	}

	in = fopen(argv[1], "rb");
	fread(buf, 1, BYTES, in);
	fclose(in);

	// 读取原DBR中从 [11, 90) 之间的数据
	out = fopen(argv[2], "rb");
	fseek(out, 11, SEEK_SET);
	fread(&buf[11], 1, 90 - 11, out);
	fclose(out);

	out = fopen(argv[2], "wb");
	fwrite(buf, 1, BYTES, out);
	fclose(out);

	return 0;
}

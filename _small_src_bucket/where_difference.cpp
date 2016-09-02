#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

#define BYTE unsigned char

void read(const wchar_t *szFileName, std::vector<BYTE> &file)
{
  std::ifstream is( szFileName, std::ifstream::binary );
	if ( !is || is.fail() )
	{
		assert( !"Can't open file!" );
		return;
	}
		is.seekg( 0, std::ios::end );
	unsigned int file_size = is.tellg();
	is.seekg( 0, std::ios::beg );

	file.resize(file_size);
	is.read( (char*)file.data(), file_size );
}

int main()
{
	std::vector<BYTE> file1;
  std::vector<BYTE> file2;

	read(LR"(d:\1_code\Temp\Crypto\cathash2\data.txt)", file1);
	read(LR"(c:\Users\All Users\Agnitum\Security Suite\log\data.txt)", file2);

  for (int i = 0, j = 0; i < file1.size(); ++i, ++j)
	{
			if ( file1[i] != file2[j])
			{
				++j;
				if ( file1[i] != file2[j])
				{
					std::cout << i << "\n" << file1[i] << "\n" << file2[j];
					break;
				}
			}
	}

		return 0;
}

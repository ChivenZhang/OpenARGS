# OpenARGS
GNU-Style Command Line Parser

# Example
```cpp
#include <iostream>
#include <OpenARGS/OpenARGS.h>

int main(int argc, char** argv)
{
	auto text = R"(gcc -Wp,-MD,usr/.gen_init_cpio.d -Wall Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -o "usr/gen_init_cpio" usr/gen_init_cpio.c -U="F oo" --Unused=Foo)";
	OpenARGS args(text);
	//OpenARGS args(argc, argv);

	std::cout << std::endl << ">> PARSE <<" << std::endl;
	std::cout << args.string() << std::endl << std::endl;
	auto items = args.array();
	for (size_t i = 0; i < items.size(); ++i)
		std::cout << i << ": " << items[i] << std::endl;


	std::cout << std::endl << ">> TEST  <<" << std::endl;
	std::cout << "level " << args.exist("O2") << std::endl;
	std::cout << "warn? " << args.exist("Wall") << std::endl;
	std::cout << "find? " << args.value("Unused") << std::endl;


	size_t index;
	if (args.index("o", index))
	{
		std::cout << "output to " << args.item(index + 1).Value << std::endl;
		std::cout << "output to " << args.item(index + 2).Value << std::endl;
	}

	return 0;
}
```

```cmd
>> PARSE <<
gcc --Wp,-MD,usr/.gen_init_cpio.d --Wall Wmissing-prototypes --Wstrict-prototypes --O2 --fomit-frame-pointer -o usr/gen_init_cpio usr/gen_init_cpio.c -U="F oo" --Unused=Foo

0: gcc
1: --Wp,-MD,usr/.gen_init_cpio.d
2: --Wall
3: Wmissing-prototypes
4: --Wstrict-prototypes
5: --O2
6: --fomit-frame-pointer
7: -o
8: usr/gen_init_cpio
9: usr/gen_init_cpio.c
10: -U="F oo"
11: --Unused=Foo

>> TEST  <<
level 1
warn? 1
find? Foo
output to usr/gen_init_cpio
output to usr/gen_init_cpio.c
```

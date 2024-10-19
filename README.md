# OpenARG
Command Line Parser

# Example
```cpp
#include <iostream>
#include <OpenARG/OpenARG.h>

int main(int argc, char** argv)
{
	auto text = R"(gcc -Wp,-MD,usr/.gen_init_cpio.d -"Unused"="Foo" -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -o "usr/gen_init_cpio" usr/gen_init_cpio.c)";
	std::cout << text << std::endl;

	OpenARG args(text);
	//OpenARG args(argc, argv);

	std::cout << std::endl << ">> PARSE <<" << std::endl;
	auto items = args.items();
	for (size_t i = 0; i < items.size(); ++i)
	{
		auto& e = items[i];
		std::cout << i << ": ";
		if (e.Name.size() && e.Value.size()) std::cout << e.Name << "=" << e.Value << std::endl;
		else if (e.Name.size()) std::cout << e.Name << std::endl;
		else if (e.Value.size()) std::cout << e.Value << std::endl;
	}

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
gcc -Wp,-MD,usr/.gen_init_cpio.d -"Unused"="Foo" -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -o "usr/gen_init_cpio" usr/gen_init_cpio.c

>> PARSE <<
0: gcc
1: Wp,-MD,usr/.gen_init_cpio.d
2: Unused=Foo
3: Wall
4: Wmissing-prototypes
5: Wstrict-prototypes
6: O2
7: fomit-frame-pointer
8: o
9: usr/gen_init_cpio
10: usr/gen_init_cpio.c

>> TEST  <<
level 1
warn? 1
find? Foo
output to usr/gen_init_cpio
output to usr/gen_init_cpio.c
```

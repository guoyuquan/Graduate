#include <stdio.h>
#include <sys/utsname.h>

int main()
{
    struct utsname un;
    uname(&un);
    printf("name of OS: %s\nname of this node: %s\ncurrent realease of OS: %s\ncurrent version of release%s\nname of hardware type: %s\n", un.sysname, un.nodename, un.release, un.version, un.machine);
    return 0;
}
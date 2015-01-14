#include <pwd.h>
#include <stddef.h>
#include <stdio.h>

int main()
{
    struct passwd *ptr;
    
    setpwent();  //rewind the passwd file;
    while((ptr = getpwent())!=NULL)
    {
        printf("%s\n%s\n%d\n%d\n%s\n%s\n%s\n%s\n", ptr->pw_name, ptr->pw_passwd, ptr->pw_uid, ptr->pw_gid, ptr->pw_gecos, ptr->pw_dir, ptr->pw_shell,ptr->pw_class);
    }
    endpwent();
    return 0;
}
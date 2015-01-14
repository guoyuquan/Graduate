#include <grp.h>
#include <stdio.h>

int main()
{
    struct group *grp;
    setgrent(); //rewind the file
    while ((grp=getgrent())!=NULL)
    {
        printf("%s\n%s\n%d\n", grp->gr_name, grp->gr_passwd, grp->gr_gid);
        for(int i=0; grp->gr_mem[i]!=NULL; i++)
        {
            printf("%s\n", grp->gr_mem[i]);
        }
    }
    endgrent();
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

typedef int Myfunc(const char *, const struct stat *, int);

static Myfunc myfunc;
static int myftw(char *, Myfunc *);
static int dopath(Myfunc *);

static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int main(int argc, char *argv[])
{
    int ret;
    if(argc != 2)
    {
        fprintf(stderr, "usage: ftw <starting-pathname> \n");
        exit(0);
    }
    ret=myftw(argv[1], myfunc);
    ntot=nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
    if(ntot==0)
        ntot = 1;
    printf("regular files = %7ld, %5.2f %%\n", nreg, nreg*100.0/ntot);
    printf("directories   = %7ld, %5.2f %%\n", ndir, ndir*100.0/ntot);
    printf("block special = %7ld, %5.2f %%\n", nblk, nblk*100.0/ntot);
    printf("char special  = %7ld, %5.2f %%\n", nchr, nchr*100.0/ntot);
    printf("FIFOs         = %7ld, %5.2f %%\n", nfifo, nfifo*100.0/ntot);
    printf("symbolic link = %7ld, %5.2f %%\n", nslink, nslink*100.0/ntot);
    printf("sockets       = %7ld, %5.2f %%\n", nsock, nsock*100.0/ntot);
    exit(ret);
}

/*
 * Descend through the hierarchy, starting at "pathname".
 * The caller's func() is called for every file.
 */

#define FTW_F   1 /* file other than directory */
#define FTW_D   2 /* directory */
#define FTW_DNR 3 /* directory that can't be read */
#define FTW_NS  4 /* file we can't stat */

#ifdef  PATH_MAX
static int  pathmax = PATH_MAX;
#else
static int  pathmax = 0;
#endif

#define SUSV3   200112L

static long posix_version = 0;

/* If PATH_MAX is indeterminate, no guarantee this is adequate */
#define PATH_MAX_GUESS  1024

char *
path_alloc(int *sizep) /* also return allocated size, if nonnull */
{
    char    *ptr;
    int size;
    
    if (posix_version == 0)
        posix_version = sysconf(_SC_VERSION);
    
    if (pathmax == 0) {     /* first time through */
        errno = 0;
        if ((pathmax = pathconf("/", _PC_PATH_MAX)) < 0) {
            if (errno == 0)
                pathmax = PATH_MAX_GUESS; /* it's indeterminate */
            else
            {
                fprintf(stderr, "pathconf error for _PC_PATH_MAX\n");
            }
        } else {
            pathmax++;      /* add one since it's relative to root */
        }
    }
    if (posix_version < SUSV3)
        size = pathmax + 1;
    else
        size = pathmax;
    
    if ((ptr = malloc(size)) == NULL)
    {
        fprintf(stderr,"malloc error for pathname\n");
    }
    
    if (sizep != NULL)
        *sizep = size;
    return(ptr);
}

static char *fullpath; /* contains full pathname for every file */

static int myftw(char *pathname, Myfunc *func)
{
    int len;
    fullpath = path_alloc(&len);
    strncpy(fullpath, pathname, len);
    fullpath[len-1] =0;
    return (dopath(func));
}
/*
 * Descend through the hierarchy, starting at "fullpath".
 * If "fullpath" is anything other than a directory, we lstat() it,
 * call func(), and return. For a directory, we call ourself
 * recursively for each name in the directory.
 */

static int dopath(Myfunc * func)
{
    struct stat statbuf;
    struct dirent *dirp;
    DIR *dp;
    int ret;
    char *ptr;
    if(lstat(fullpath, &statbuf)<0)
        return func(fullpath, &statbuf, FTW_NS);
    if(S_ISDIR(statbuf.st_mode)==0) /*not a directory*/
        return (func(fullpath, &statbuf, FTW_F));
    /*
     * It's a directory. First call func() for the directory,
     * then process each filename in the directory.
     */
    if((ret=func(fullpath, & statbuf, FTW_D))!=0)
        return ret;
    ptr=fullpath+strlen(fullpath);
    *ptr++='/';
    *ptr=0;
    if((dp=opendir(fullpath))==NULL)
        return(func(fullpath, &statbuf, FTW_DNR));
    while ((dirp=readdir(dp))!=NULL)
    {
        if(strcmp(dirp->d_name, ".")==0||strcmp(dirp->d_name, "..")==0)
            continue;
        strcpy(ptr, dirp->d_name);
        if((ret=dopath(func))!=0)
            break;
    }
    ptr[-1]=0;
    if(closedir(dp)<0)
    {
        fprintf(stderr, "error: close directory %s\n" , fullpath);
    }
    return ret;
}

static int myfunc(const char *pathname, const struct stat * statptr, int type)
{
    switch (type)
    {
        case FTW_F :
            switch (statptr->st_mode &S_IFMT)
            {
                case S_IFREG : nreg++; break;
                case S_IFBLK : nblk++; break;
                case S_IFCHR : nchr++; break;
                case S_IFIFO : nfifo++; break;
                case S_IFLNK : nslink++; break;
                case S_IFSOCK : nsock++; break;
                case S_IFDIR : 
                    fprintf(stderr, "error: %s\n", pathname);
            }
            break;
        case FTW_D:
            ndir++;
            break;
        case FTW_DNR:
            fprintf(stderr, "error: can't read directory %s\n", pathname);
            break;
        case FTW_NS:
            fprintf(stderr, "error: stat error for %s\n", pathname);
            break;
        default:
            fprintf(stderr, "error: unknown type %d for pathname %s\n", type, pathname);
            break;
    }
    return 0;
}
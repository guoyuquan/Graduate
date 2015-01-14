#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * functions to lock or unlock a regio of a file
 */
int
lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
    struct flock lock;
    
    lock.l_type = type;     /* F_RDLCK, F_WRLCK, F_UNLCK */
    lock.l_start = offset;  /* byte offset, relative to l_whence */
    lock.l_whence = whence; /* SEEK_SET, SEEK_CUR, SEEK_END */
    lock.l_len = len;       /* #bytes (0 means to EOF) */
    
    return (fcntl(fd, cmd, &lock));
}

#define read_lock(fd, offset, whence, len) \
            lock_reg((fd), F_SETLK, F_RDLCK, (offset), (whence), (len))
#define readw_lock(fd, offset, whence, len) \
lock_reg((fd), F_SETLKW, F_RDLCK, (offset), (whence), (len))
#define write_lock(fd, offset, whence, len) \
lock_reg((fd), F_SETLK, F_WRLCK, (offset), (whence), (len))
#define writew_lock(fd, offset, whence, len) \
lock_reg((fd), F_SETLKW, F_WRLCK, (offset), (whence), (len))
#define un_lock(fd, offset, whence, len) \
lock_reg((fd), F_SETLK, F_UNLCK, (offset), (whence), (len))

/*
 * testing for a lock
 */

pid_t
lock_test(int fd, int type, off_t offset, int whence, off_t len)
{
    struct flock lock;
    lock.l_type = type;     /* F_RDLCK or F_WRLCK */
    lock.l_start = offset;  /* byte offset, relative to l_whence */
    lock.l_whence = whence; /* SEEK_SET, SEEK_CUR, SEEK_END */
    lock.l_len = len;       /* #bytes (0 means to EOF) */
    if(fcntl(fd, F_GETLK, &lock)<0)
    {
        fprintf(stderr,"error: fcntl\n");
        exit(0);
    }
    if(lock.l_type==F_UNLCK)
        return(0); /*false, the region is not locked by another proc*/
    return (lock.l_pid); /*true, return pid*/
}

#define is_read_lockable(fd, offset, whence, len) \
(lock_test((fd), F_RDLCK, (offset), (whence), (len)) == 0)
#define is_write_lockable(fd, offset, whence, len) \
(lock_test((fd), F_WRLCK, (offset), (whence), (len)) == 0)

static void
lockabyte(const char *name, int fd, off_t offset)
{
    if(writew_lock(fd, offset, SEEK_SET, 1)<0)
    {
        fprintf(stderr, "error: writew_lock for %s\n", name);
        exit(0);
    }
    printf("%s: got the lock, byte %lld\n", name, offset);
}

int main()
{
    int fd;
    pid_t pid;
    /*
     * create a file and wirte two bytes to it;
     */
    if((fd=creat("templock", FILESEC_MODE))<0)
    {
        fprintf(stderr, "error: creat\n");
        exit(0);
    }
    if(write(fd, "ab", 2)!=2)
    {
        fprintf(stderr, "write error\n");
        exit(0);
    }
    if ((pid = fork()) < 0) {
        fprintf(stderr, "error: ford\n");
    } else if (pid == 0) {         /* child */
        lockabyte("child", fd, 0);
        //TELL_PARENT(getppid());
        //WAIT_PARENT();
        lockabyte("child", fd, 1);
    } else {                       /* parent */
        lockabyte("parent", fd, 1);
        //TELL_CHILD(pid);
        //WAIT_CHILD();
        lockabyte("parent", fd, 0);
    }
    exit(0);
}
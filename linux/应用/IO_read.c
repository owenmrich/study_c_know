open
read
write
close
fstat
stat
lstat
//struct stat xxx
//以下为stat的linux下的定义
struct stat
{
__dev_t st_dev;                     /* Device.  */
unsigned short int __pad1;
__ino_t st_ino;                     /* File serial number.  */
__mode_t st_mode;                   /* File mode.  */
__nlink_t st_nlink;                 /* Link count.  */
__uid_t st_uid;                     /* User ID of the file’s owner. */
__gid_t st_gid;                     /* Group ID of the file’s group.*/
__dev_t st_rdev;                    /* Device number, if device.  */
unsigned short int __pad2;
__off_t st_size;                    /* Size of file, in bytes.  */
__blksize_t st_blksize;             /* Optimal block size for I/O.  */
__blkcnt_t st_blocks;               /* Number 512-byte blocks allocated. */
struct timespec st_atim;            /* Time of last access.  */
struct timespec st_mtim;            /* Time of last modification.  */
struct timespec st_ctim;            /* Time of last status change.  */
unsigned long int __unused4;
unsigned long int __unused5;
};
//
int fstat(int filedes, struct stat *buf);
int stat(const char *path, struct stat *buf);
int lstat(const char *path, struct stat *buf);

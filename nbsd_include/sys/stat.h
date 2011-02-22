#ifndef _SYS_STAT_H_
#define	_SYS_STAT_H_

#include <sys/featuretest.h>
#include <sys/types.h>		/* XXX */

#if defined(_NETBSD_SOURCE)
#include <sys/time.h>
#endif

#define __MINIX_EMULATE_NETBSD_STAT

/* 
 * __MINIX_EMULATE_NETBSD_STAT
 *
 * Userspace flag to emulate netbsd stat structure. Please note that
 * this might be dangerous, and should be enabled only when we're sure
 * that the program doesn't use the emulated information for doing
 * something harmful.
 * It is meant to be temporary, until we add a new syscall.
 */
#ifdef __MINIX_EMULATE_NETBSD_STAT
#define __netbsd_stat stat
#else
#define __minix_stat stat
#endif

struct __minix_stat {
	dev_t st_dev;			/* major/minor device number */
	ino_t st_ino;			/* i-node number */
	mode_t st_mode;		/* file mode, protection bits, etc. */
	nlink_t st_nlink;		/* # links; */
	uid_t st_uid;			/* uid of the file's owner */ 
	gid_t st_gid;		/* gid */
	dev_t st_rdev;
	off_t st_size;		/* file size */
	time_t st_atime;		/* time of last access */
	time_t st_mtime;		/* time of last data modification */
	time_t st_ctime;		/* time of last file status change */
};

struct __netbsd_stat {
	dev_t st_dev;			/* major/minor device number */
	ino_t st_ino;			/* i-node number */
	mode_t st_mode;		/* file mode, protection bits, etc. */
	nlink_t st_nlink;		/* # links; */
	uid_t st_uid;			/* uid of the file's owner */ 
	gid_t st_gid;		/* gid */
	dev_t st_rdev;
	off_t st_size;		/* file size */
	time_t st_atime;		/* time of last access */
	time_t st_mtime;		/* time of last data modification */
	time_t st_ctime;		/* time of last file status change */

	/* XXX: Currently not supported by Minix, and here are just emulated. */
	struct	  timespec st_atimespec;/* time of last access */
	struct	  timespec st_mtimespec;/* time of last data modification */
	struct	  timespec st_ctimespec;/* time of last file status change */
	struct 	  timespec st_birthtimespec; /* time of creation */
	blkcnt_t  st_blocks;		/* blocks allocated for file */
	blksize_t st_blksize;		/* optimal blocksize for I/O */
	uint32_t  st_flags;		/* user defined flags for file */
	uint32_t  st_gen;		/* file generation number */
	uint32_t  st_spare[2];
};

#ifdef __MINIX_EMULATE_NETBSD_STAT
#define	st_atimensec		st_atimespec.tv_nsec
#define	st_mtimensec		st_mtimespec.tv_nsec
#define	st_ctimensec		st_ctimespec.tv_nsec
#define st_birthtime		st_birthtimespec.tv_sec
#define st_birthtimensec	st_birthtimespec.tv_nsec
#endif 

#define	S_ISUID	0004000			/* set user id on execution */
#define	S_ISGID	0002000			/* set group id on execution */
#if defined(_NETBSD_SOURCE)
#define	S_ISTXT	0001000			/* sticky bit */
#endif

#define	S_IRWXU	0000700			/* RWX mask for owner */
#define	S_IRUSR	0000400			/* R for owner */
#define	S_IWUSR	0000200			/* W for owner */
#define	S_IXUSR	0000100			/* X for owner */

#if defined(_NETBSD_SOURCE)
#define	S_IREAD		S_IRUSR
#define	S_IWRITE	S_IWUSR
#define	S_IEXEC		S_IXUSR
#endif

#define	S_IRWXG	0000070			/* RWX mask for group */
#define	S_IRGRP	0000040			/* R for group */
#define	S_IWGRP	0000020			/* W for group */
#define	S_IXGRP	0000010			/* X for group */

#define	S_IRWXO	0000007			/* RWX mask for other */
#define	S_IROTH	0000004			/* R for other */
#define	S_IWOTH	0000002			/* W for other */
#define	S_IXOTH	0000001			/* X for other */

#define	_S_IFMT	  0170000		/* type of file mask */
#define	_S_IFIFO  0010000		/* named pipe (fifo) */
#define	_S_IFCHR  0020000		/* character special */
#define	_S_IFDIR  0040000		/* directory */
#define	_S_IFBLK  0060000		/* block special */
#define	_S_IFREG  0100000		/* regular */
#define	_S_IFLNK  0120000		/* symbolic link */
#define	_S_IFSOCK 0140000		/* socket */
#define	_S_ISVTX  0001000		/* save swapped text even after use */

#if defined(_XOPEN_SOURCE) || defined(_NETBSD_SOURCE)
#define	S_IFMT	 _S_IFMT
#define	S_IFIFO	 _S_IFIFO
#define	S_IFCHR	 _S_IFCHR
#define	S_IFDIR	 _S_IFDIR
#define	S_IFBLK	 _S_IFBLK
#define	S_IFREG	 _S_IFREG
#define	S_IFLNK	 _S_IFLNK
#define	S_ISVTX	 _S_ISVTX
#endif
#if ((_XOPEN_SOURCE - 0) >= 600) || defined(_NETBSD_SOURCE)
#define	S_IFSOCK _S_IFSOCK
#endif

#define	S_ISDIR(m)	(((m) & _S_IFMT) == _S_IFDIR)	/* directory */
#define	S_ISCHR(m)	(((m) & _S_IFMT) == _S_IFCHR)	/* char special */
#define	S_ISBLK(m)	(((m) & _S_IFMT) == _S_IFBLK)	/* block special */
#define	S_ISREG(m)	(((m) & _S_IFMT) == _S_IFREG)	/* regular file */
#define	S_ISFIFO(m)	(((m) & _S_IFMT) == _S_IFIFO)	/* fifo */
#if ((_POSIX_C_SOURCE - 0) >= 200112L) || defined(_XOPEN_SOURCE) || \
    defined(_NETBSD_SOURCE)
#define	S_ISLNK(m)	(((m) & _S_IFMT) == _S_IFLNK)	/* symbolic link */
#endif
#if ((_POSIX_C_SOURCE - 0) >= 200112L) || ((_XOPEN_SOURCE - 0) >= 600) || \
    defined(_NETBSD_SOURCE)
#define	S_ISSOCK(m)	(((m) & _S_IFMT) == _S_IFSOCK)	/* socket */
#endif

#if defined(_NETBSD_SOURCE)
#define	ACCESSPERMS	(S_IRWXU|S_IRWXG|S_IRWXO)	/* 0777 */
							/* 7777 */
#define	ALLPERMS	(S_ISUID|S_ISGID|S_ISTXT|S_IRWXU|S_IRWXG|S_IRWXO)
							/* 0666 */
#define	DEFFILEMODE	(S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

#define S_BLKSIZE	512		/* block size used in the stat struct */

#endif /* _NETBSD_SOURCE */

#if defined(__minix)
#include <machine/vmparam.h>
/* Convenient constant to use when st_blocksize field is required. */
#define MINIX_ST_BLKSIZE PAGE_SIZE
#endif

#if !defined(_KERNEL) && !defined(_STANDALONE)
#include <sys/cdefs.h>

__BEGIN_DECLS
int	chmod(const char *, mode_t);
int	mkdir(const char *, mode_t);
int	mkfifo(const char *, mode_t);
#ifndef __LIBC12_SOURCE__
int	stat(const char *, struct stat *);
int	fstat(int, struct stat *);
#endif
mode_t	umask(mode_t);
#if defined(_XOPEN_SOURCE) || defined(_NETBSD_SOURCE)
int	fchmod(int, mode_t);
#ifndef __LIBC12_SOURCE__
int	lstat(const char *, struct stat *);
int	mknod(const char *, mode_t, dev_t) __RENAME(__mknod50);
#endif
#endif /* defined(_XOPEN_SOURCE) || defined(_NETBSD_SOURCE) */
__END_DECLS

#endif /* !_KERNEL && !_STANDALONE */
#endif /* !_SYS_STAT_H_ */
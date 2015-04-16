/*TODO:
 * Get below 1 directory level working
 * Make math functions.
 * Make math functions work.
 * Make write up
 * Think of more things to do.
 */


/*
  FUSE: Filesystem in Userspace
  Copyright (C) 2001-2007  Miklos Szeredi <miklos@szeredi.hu>

  This program can be distributed under the terms of the GNU GPL.
  See the file COPYING.

  gcc -Wall mathfs.c `pkg-config fuse --cflags --libs` -o mathfs
*/

#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

//Directory path names and some test text.
static const char *mathfs_str = "You've done something right!\nI think...\n";
static const char *mathfs_path = "/mathfs";
const char* add_path= "/add";
const char* sub_path = "/sub";
const char* mul_path = "/mul";
const char* div_path = "/div";
const char* exp_path = "/exp";
const char* fib_path = "/fib";
const char* fac_path = "/factor";


/*
 *Set file properties in this function.
 *Compares the input path (path) and then sets file permissions and stuff.
 *Use this to make files and directories exist, but not necessarily visible.
 * stbuff->st_mode = S_IFDIR | 0755 to make a directory.
 * stbuff->st_mode = S_IFDIR | 0444 to make a file.
 *
 * Currently, each of our directories are hard coded in.
 */
static int mathfs_getattr(const char *path, struct stat *stbuf)
{
	int res = 0;

	printf("getattr(\"%s\")\n",path);

	memset(stbuf, 0, sizeof(struct stat));
	if (strcmp(path, "/") == 0) {
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
	} 
	 else if (strcmp(path, mathfs_path) == 0) {
		stbuf->st_mode = S_IFREG | 0444;
		stbuf->st_nlink = 1;
		stbuf->st_size = strlen(mathfs_str);
	} 
	 else if (strcmp(path, add_path) == 0) {
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 1;
		stbuf->st_size = strlen(mathfs_str);
	} 
	 else if (strcmp(path, sub_path) == 0) {
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 1;
		stbuf->st_size = strlen(mathfs_str);
	} 
	 else if (strcmp(path, mul_path) == 0) {
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 1;
		stbuf->st_size = strlen(mathfs_str);
	} 
	 else if (strcmp(path, div_path) == 0) {
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 1;
		stbuf->st_size = strlen(mathfs_str);
	} 
	 else if (strcmp(path, exp_path) == 0) {
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 1;
		stbuf->st_size = strlen(mathfs_str);
	} 
	 else if (strcmp(path, fib_path) == 0) {
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 1;
		stbuf->st_size = strlen(mathfs_str);
	} 
	 else if (strcmp(path, fac_path) == 0) {
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 1;
		stbuf->st_size = strlen(mathfs_str);
	} 
	 else
		res = -ENOENT;

	return res;
}

/*
 *This function add files to a directory.
 *Use this to make things visible to ls command.
 *
 *
 */
static int mathfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
			 off_t offset, struct fuse_file_info *fi)
{
	(void) offset;
	(void) fi;
	printf("readdir(\"%s\")\n",path);

	if (strcmp(path, "/") != 0)
		return -ENOENT;

	filler(buf, ".", NULL, 0);
	filler(buf, "..", NULL, 0);
	filler(buf, mathfs_path + 1, NULL, 0);
	filler(buf, add_path + 1, NULL, 0);
	filler(buf, sub_path + 1, NULL, 0);
	filler(buf, mul_path + 1, NULL, 0);
	filler(buf, div_path + 1, NULL, 0);
	filler(buf, exp_path + 1, NULL, 0);
	filler(buf, fib_path + 1, NULL, 0);
	filler(buf, fac_path + 1, NULL, 0);

	return 0;
}

/*
 *This function to open stuff.
 *Compares string length and then does stuff.
 *
 */
static int mathfs_open(const char *path, struct fuse_file_info *fi)
{
	printf("open(\"%s\")\n",path);
	
	int bad_open = 1;

	if(strcmp(path, mathfs_path) == 0)
		bad_open = 0;
  	if(strcmp(path, add_path) == 0)
		bad_open = 0;
	if(strcmp(path, sub_path) == 0)
		bad_open = 0;
	if(strcmp(path, mul_path) == 0)
		bad_open = 0;
	if(strcmp(path, div_path) == 0)
		bad_open = 0;
	if(strcmp(path, exp_path) == 0)
		bad_open = 0;
	if(strcmp(path, fib_path) == 0)
		bad_open = 0;
	if(strcmp(path, exp_path) == 0)
		bad_open = 0;
	
	if(bad_open == 1)
		return -ENOENT;

	if ((fi->flags & 3) != O_RDONLY)
		return -EACCES;

	return 0;
}

static int mathfs_read(const char *path, char *buf, size_t size, off_t offset,
		      struct fuse_file_info *fi)
{
	printf("read(\"%s\")\n",path);
	size_t len;
	(void) fi;

	int bad_read = 1;

	if(strcmp(path, mathfs_path) == 0)
		bad_read = 0;
	if(strcmp(path, add_path) == 0)
		bad_read = 0;
	if(strcmp(path, sub_path) == 0)
		bad_read = 0;
	if(strcmp(path, mul_path) == 0)
		bad_read = 0;
	if(strcmp(path, div_path) == 0)
		bad_read = 0;
	if(strcmp(path, exp_path) == 0)
		bad_read = 0;
	if(strcmp(path, fib_path) == 0)
		bad_read = 0;
	if(strcmp(path, exp_path) == 0)
		bad_read = 0;
	
	if(bad_read == 1)
		return -ENOENT;

	len = strlen(mathfs_str);
	if (offset < len) {
		if (offset + size > len)
			size = len - offset;
		memcpy(buf, mathfs_str + offset, size);
	} else
		size = 0;

	return size;
}

static struct fuse_operations mathfs_oper = {
	.getattr	= mathfs_getattr,
	.readdir	= mathfs_readdir,
	.open		= mathfs_open,
	.read		= mathfs_read,
};

int main(int argc, char *argv[])
{
	return fuse_main(argc, argv, &mathfs_oper, NULL);
}

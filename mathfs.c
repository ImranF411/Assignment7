/*TODO:
 * Add math functions to mathfs.
 * Make math functions work.
 * Make write up
 * Create doc entries in math folders.
 * Remove mathfs file.
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
#include <stdlib.h>
#include <string.h>
#include "functions.h"

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
const char* add_doc_path= "/add/doc";
const char* sub_doc_path = "/sub/doc";
const char* mul_doc_path = "/mul/doc";
const char* div_doc_path = "/div/doc";
const char* exp_doc_path = "/exp/doc";
const char* fib_doc_path = "/fib/doc";
const char* fac_doc_path = "/factor/doc";
/*Doc file strings go here*/
char* result_ptr;
/*Descriptions of each function*/
char* fac_msg = "Compute the prime factors of a number.\n";
char* fib_msg = "Compute the first n fibonacci numbers.\n";
char* add_msg = "Add two numbers.\n";
char* sub_msg = "Subtract two numbers.\n";
char* mul_msg = "Multiply two numbers.\n";
char* div_msg = "Divide two numbers.\n";
char* exp_msg = "Raises a number to a given exponent.\n";



void make_dir(struct stat *stbuf){

	stbuf->st_mode = S_IFDIR | 0755;
	stbuf->st_nlink = 3;
	stbuf->st_size = 0;
	return;
}

void make_file(struct stat *stbuf, char* result_string){

	stbuf->st_mode = S_IFREG | 0444;
	stbuf->st_nlink = 1;
	stbuf->st_size = strlen(result_string);
	return;
}

int valid_path(const char *path, struct stat *stbuf)
{
	char *path_copy = (char*) calloc(strlen(path)+1,sizeof(char));
	strcpy(path_copy,path);

	int case_switch = 0, ret = 9;
	char * path_arg = strtok(path_copy,"/");
	char * arg1;
	char * arg2;


	//If accessing add/sub/mul/div/exp
	if(strcmp(path_arg,"add") == 0 || strcmp(path_arg,"sub")== 0 ||
	   strcmp(path_arg,"mul") == 0 || strcmp(path_arg,"div")== 0 ||
	   strcmp(path_arg,"exp") == 0)
		case_switch = 1;
	//If accessing fib/factor
	else if(strcmp(path_arg,"fib") == 0 || strcmp(path_arg,"factor") == 0)
		case_switch = 2;

	switch (case_switch){
	 case 1://Expect 2 "arguments"
		arg1 = strtok(NULL,"/");	//Get first folder
		if (arg1 == NULL){		//If not there, make a directory
			make_dir(stbuf);
			ret = 0;
			break;
		}
		
		arg2 = strtok(NULL,"/");	//Get second folder
		if (arg2 == NULL) {		//If not there, make a directory
			make_dir(stbuf);
			ret = 0;
			break;
		}
		break;
	 case 2://Expect 1 "argument"
		arg1 = strtok(NULL,"/");	//Get first folder
		if (arg1 == NULL){		//If not there, make a directory
			make_dir(stbuf);
			ret = 0;
			break;
		}
		break;
	default:
		ret = -ENOENT;
		break;
	}

	if(ret == 9){
		//Have necessary folders, do operation.
		if(strcmp(path_arg,"add") == 0)
			result_ptr = add(arg1,arg2);
		if(strcmp(path_arg,"sub") == 0)
			result_ptr = subtract(arg1,arg2);
		if(strcmp(path_arg,"mul") == 0)
			result_ptr = multiply(arg1,arg2);
		if(strcmp(path_arg,"div") == 0)
			result_ptr = divide(arg1,arg2);
		if(strcmp(path_arg,"exp") == 0)
			result_ptr = exponent(arg1,arg2);
		if(strcmp(path_arg,"fib") == 0)
			result_ptr = fibonacci(arg1);
		if(strcmp(path_arg,"factor") == 0)
			result_ptr = factor(arg1);
		make_file(stbuf,result_ptr);
		ret = 0;
	}
	
	free(path_copy);
	return ret;
}

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
	 else if (strcmp(path, add_doc_path) == 0) {
		//Set result_ptr here to appropriate doc string
		result_ptr = add_msg;
		stbuf->st_mode = S_IFREG | 0444;
		stbuf->st_nlink = 1;
		//Change strlen(mathfs_str) to strlen(result_ptr);
		stbuf->st_size = strlen(result_ptr);
	} 
	 else if (strcmp(path, sub_doc_path) == 0) {
		result_ptr = sub_msg;
		stbuf->st_mode = S_IFREG | 0444;
		stbuf->st_nlink = 1;
		stbuf->st_size = strlen(result_ptr);
	} 
	 else if (strcmp(path, mul_doc_path) == 0) {
		result_ptr = mul_msg;
		stbuf->st_mode = S_IFREG | 0444;
		stbuf->st_nlink = 1;
		stbuf->st_size = strlen(result_ptr);
	} 
	 else if (strcmp(path, div_doc_path) == 0) {
		result_ptr = div_msg;
		stbuf->st_mode = S_IFREG | 0444;
		stbuf->st_nlink = 1;
		stbuf->st_size = strlen(result_ptr);
	} 
	 else if (strcmp(path, exp_doc_path) == 0) {
		result_ptr = exp_msg;
		stbuf->st_mode = S_IFREG | 0444;
		stbuf->st_nlink = 1;
		stbuf->st_size = strlen(result_ptr);
	} 
	 else if (strcmp(path, fib_doc_path) == 0) {
		result_ptr = fib_msg;
		stbuf->st_mode = S_IFREG | 0444;
		stbuf->st_nlink = 1;
		stbuf->st_size = strlen(result_ptr);
	} 
	 else if (strcmp(path, fac_doc_path) == 0) {
		result_ptr = fac_msg;
		stbuf->st_mode = S_IFREG | 0444;
		stbuf->st_nlink = 1;
		stbuf->st_size = strlen(result_ptr);
	}
	 else
		res = valid_path(path,stbuf);

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

//	if (strcmp(path, "/") != 0)
//		return -ENOENT;
	if (strcmp(path,"/") == 0){
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
	}else if(strcmp(path,add_path) == 0){
		filler(buf, ".", NULL, 0);
		filler(buf, "..", NULL, 0);
		filler(buf, "/doc" + 1, NULL, 0);
	}else if(strcmp(path,sub_path) == 0){
		filler(buf, ".", NULL, 0);
		filler(buf, "..", NULL, 0);
		filler(buf, "/doc" + 1, NULL, 0);
	}else if(strcmp(path,mul_path) == 0){
		filler(buf, ".", NULL, 0);
		filler(buf, "..", NULL, 0);
		filler(buf, "/doc" + 1, NULL, 0);
	}else if(strcmp(path,div_path) == 0){
		filler(buf, ".", NULL, 0);
		filler(buf, "..", NULL, 0);
		filler(buf, "/doc" + 1, NULL, 0);
	}else if(strcmp(path,exp_path) == 0){
		filler(buf, ".", NULL, 0);
		filler(buf, "..", NULL, 0);
		filler(buf, "/doc" + 1, NULL, 0);
	}else if(strcmp(path,fib_path) == 0){
		filler(buf, ".", NULL, 0);
		filler(buf, "..", NULL, 0);
		filler(buf, "/doc" + 1, NULL, 0);
	}else if(strcmp(path,fac_path) == 0){
		filler(buf, ".", NULL, 0);
		filler(buf, "..", NULL, 0);
		filler(buf, "/doc" + 1, NULL, 0);
	}else
		return -ENOENT;
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
  	if(strcmp(path, add_doc_path) == 0)
		bad_open = 0;
	if(strcmp(path, sub_doc_path) == 0)
		bad_open = 0;
	if(strcmp(path, mul_doc_path) == 0)
		bad_open = 0;
	if(strcmp(path, div_doc_path) == 0)
		bad_open = 0;
	if(strcmp(path, exp_doc_path) == 0)
		bad_open = 0;
	if(strcmp(path, fib_doc_path) == 0)
		bad_open = 0;
	if(strcmp(path, fac_doc_path) == 0)
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
	if(strcmp(path, add_doc_path) == 0)
		bad_read = 0;
	if(strcmp(path, sub_doc_path) == 0)
		bad_read = 0;
	if(strcmp(path, mul_doc_path) == 0)
		bad_read = 0;
	if(strcmp(path, div_doc_path) == 0)
		bad_read = 0;
	if(strcmp(path, exp_doc_path) == 0)
		bad_read = 0;
	if(strcmp(path, fib_doc_path) == 0)
		bad_read = 0;
	if(strcmp(path, fac_doc_path) == 0)
		bad_read = 0;
	
	if(bad_read == 1)
		return -ENOENT;
	
	//In below lines, replace mathfs_str to result_ptr
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

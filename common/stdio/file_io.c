#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "file_io.h"

/**
 * @brief   open_file  open a file
 *
 * @param   int     fd      I/O, file descriptor
 * @param   char *  path    INPUT, file path
 * @param   int     mode    INPUT, file open mode
 *
 * @return  return 0 if success, and return fd; else return -1
 */
int open_file(int *fd, const char *path, int mode)
{
    int ret = -1;

    ret = open(path, mode);
    if(ret < 0 )
    {
        return ret;
    }

    *fd = ret;
    return ret;
}

/**
 * @brief   lseek_file  Offset ofs bytes from the beginning of the file
 *
 * @param   int     fd      INTPUT, file descriptor
 * @param   int     ofs     INPUT, offset bytes
 *
 * @return  returns the resulting offset location as measured in bytes from the beginning of the file.
 *          On error, the value (int) -1 is returned and errno is set to indicate the error.
 */
int lseek_file(int *fd, int ofs)
{
    return lseek(*fd, ofs, SEEK_SET);
}

/**
 * @brief   read_bytes  attempts to read up to count bytes from file descriptor fd into the buffer starting at buff.
 *
 * @param   int             fd      I, file descriptor
 * @param   void *          buff    O, Store the read byte content
 * @param   unsigned int    count   I, number of bytes to read
 *
 * @return  On success, the number of bytes read is returned (zero indicates end of file),
 *          and the file position is advanced by this number.
 *          On error, -1 is returned, and errno is set appropriately.
 *          In this case, it is left unspecified whether the file position (if any) changes.
 */
int read_bytes(int fd, void *buff, unsigned int count)
{
    unsigned int byte_left = 0;
    int          byte_read = 0;
    char         *ptr = NULL;

    ptr = buff;
    byte_left = count;

    while(byte_left > 0)
    {
        byte_read = read(fd, ptr, count);
        if(byte_read < 0)
        {
            if(errno == EINTR)
                byte_read = 0;
            else
                return -1;
        }
        else if (byte_read == 0)
        {
            break;
        }

        byte_left -= byte_read;
        ptr += byte_read;
    }

    return (count - byte_left);
}

/**
 * @brief   write_bytes  writes up to count bytes from the buffer starting at buf to the file referred to by the file descriptor fd.
 *
 * @param   int             fd      I, file descriptor
 * @param   void *          buff    I, Stores what will be written to the file
 * @param   unsigned int    count   I, number of bytes to be written
 *
 * @return  On success, the number of bytes written is returned (zero indicates nothing was written).
 *          It is not an error if this number is smaller than the number of bytes requested;
 *          this may happen for example because the disk device was filled.
 *
 *          On error, -1 is returned, and errno is set appropriately.
 *
 *          If  count  is  zero  and  fd  refers to a regular file, then write() may return a failure status if one of the errors below is detected.
 *          If no errors are detected, or error detection is not performed, 0 will be returned without causing any other effect.
 *          If count is zero and fd refers to a file other than a regular file, the results are not specified.
 */
int write_bytes(int *fd, const void *buff, unsigned int count)
{
	unsigned int      byte_left;
	int       byte_written;
	const char	  *ptr;

	ptr = buff;
	byte_left = count;
    while (byte_left > 0)
    {
        byte_written = write(fd, ptr, byte_left);
    	if(byte_written <= 0)
        {
    		if (byte_written < 0 && errno == EINTR)
    			byte_written = 0;		/* and call write() again */
    		else
    			return -1;			/* error */
    	}

    	byte_left   -= byte_written;
    	ptr         += byte_written;
    }
    
    return count - byte_left;
}

/**
 * @brief   close_file  closes a file descriptor, so that it no longer refers to any file and may be reused.
 *
 * @param   int  fd     I, file descriptor
 *
 * @return  returns zero on success.  On error, -1 is returned, and errno is set appropriately.
 */
int close_file(int fd)
{
    return close(fd);
}

int fread_bytes(FILE* fp, void *buff, u_int count)
{
    if(NULL == fp || NULL == buff)
    {
        return -1;
    }

	unsigned int byte_left;
	int     	 byte_read;
	char	     *ptr;

	ptr = buff;
	byte_left = count;
    while (byte_left > 0)
    {
        byte_read = fread(ptr, 1, byte_left, fp);
    	if (byte_read <= 0)
        {
    		if (!ferror(fp))
    			break;
    		else
    			return(-1);
    	}

    	byte_left -= byte_read;
    	ptr       += byte_read;
    }

	return (count - byte_left);		/* return >= 0 */
}

int fread_xbytes(FILE* fp, void *buff, u_int n, u_int x)
{
    if(NULL == fp || NULL == buff)
        return -1;

	unsigned int num = x < n ? x:n;
	return fread_bytes(fp, buff, num);
}

int fwrite_bytes(FILE *fp, const void *buff, unsigned int count)
{
    if(NULL == fp || NULL == buff)
        return -1;

	unsigned int bytes_left;
	int 		 bytes_written;
	const char	*ptr;

	ptr = buff;
	bytes_left = count;
	while (bytes_left > 0)
  {
		if ( (bytes_written = fwrite(ptr, 1, bytes_left, fp)) <= 0)
    {
				return(-1);			/* error */
		}

		bytes_left  -= bytes_written;
		ptr         += bytes_written;
	}

	return count - bytes_left;
}

int fwrite_xbytes(FILE *fp, const void *buff, u_int n, u_int x)
{
    if(NULL == fp || NULL == buff)
        return -1;

	unsigned int num = x < n?x :n;
	return fwrite_bytes(fp, buff, num);
}

int read_file(const char * fpath, char * buff, u_int *count)
{
    if(NULL == fpath || NULL == buff || NULL == count)
        return -1;

    FILE * fh;
    int ret;

    if( (fh = fopen(fpath,"rb") ) == NULL)
        return -1;

    ret = fread_bytes(fh, buff, *count);
    if(ret < 0)
    {
        fclose(fh);
        return -1;
    }

    *count = ret;
    fclose(fh);

    return 0;
}

int write_file(const char * fpath, bool_t is_app, char * buff, u_int *count)
{
    if(NULL == fpath || NULL == buff || NULL == count)
        return -1;

    FILE * fp;
    int ret;
    char * mode;

    mode = is_app?"ab":"wb";
    if( (fp = fopen(fpath, mode) ) == NULL)
        return -1;

    ret = fwrite_bytes(fp, buff, *count);
    if(ret < 0)
    {
        fclose(fp);
        return -1;
    }

    *count = ret;
    fclose(fp);

    return 0;
}

char *get_file_dirname(const char *s)
{
	if (NULL == s)
  {
        return NULL;
    }

	char *aux = f_strdup(s);
    if(NULL == aux)
    {
        return NULL;
    }

	char *s2  = f_strdup(dirname(aux));
    if(NULL == s2)
    {
        return NULL;
    }
    
	free(aux);
	return s2;
}

/**
 * @brief   f_open
 *
 * @param   string  fd
 * @param   string  path
 * @param   string  mode
 *
 * @return
 */
int set_nonblocking(int fd)
{

    int flags = fcntl(fd, F_GETFL);
    if (flags == -1)
    {
        debug_err("fcntl error");
        return -1;
    }

    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
    {
        debug_err("fcntl error");
        return -1;
    }

    return 0;
}

file_type_enumt get_file_type(const char *file)
{
    if(NULL == file)
    {
        debug_err("no file input.");
        return FILE_TYPE_UNKOWN;
    }

    if ((strstr(file, ".s19") != NULL) || (NULL != strstr(file, ".mot")))
    {
        debug_info("file is S19\n");
        return FILE_TYPE_S19;
    }

    if (strstr(file, ".bin") != NULL)
    {
        debug_info("file is BIN\n");
        return FILE_TYPE_BIN;
    }

    if (strstr(file, ".hex") != NULL)
    {
        debug_info("file is HEX\n");
        return FILE_TYPE_HEX;
    }

    return FILE_TYPE_UNKOWN;
}

int get_file_size(FILE *file)
{
    if(NULL == file)
    {
        debug_err("no file input.");
        return -1;
    }

    int fsize = -1;
    struct stat statb;
    if(stat(file, &statb) == 0 && S_ISREG(statb.st_mode))
    {
       fsize = (int)statb.st_size;
    }

    return fsize;
}

u_int get_file_total_line(FILE *fp, u_int per_line_bytes)
{
    if(NULL == fp)
    {
        debug_err("no file input.");
        return -1;
    }

    unsigned int total_line = 0;
    fseek(fp, 0L, SEEK_SET);
    while(1)
    {
        char buf[per_line_bytes] = {0};
        fgets(buf, per_line_bytes, fp);
        if(feof(fp))
        {
            debug_warn("end of file.");
            break;
        }

        if(!ferror(fp))
        {
            total_line++;
        }
        else
        {
            debug_err("get file line error.\n");
            return -1;
        }
    }

    fseek(fp, 0L, SEEK_SET);
    return total_line;
}



/**============================= printf function family ============================== */
char *f_asprintf(char *fmt, ...)
{

    char *ret = NULL;
    va_list ap;

    va_start(ap, fmt);
    int rc = 0;
#ifdef _GNU_SOURCE
    rc = vasprintf(&ret, fmt, ap);
#else
    rc = vsprintf(ret, fmt, ap);
#endif
    va_end(ap);

    if (rc < 0)
    {
        debug_err("vasprintf error");
        return NULL;
    }

    return ret;
}


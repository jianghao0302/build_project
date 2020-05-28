#ifndef __FILE_IO_H__
#define __FILE_IO_H__

typedef enum FILE_TYPE {
    FILE_TYPE_S19,
    FILE_TYPE_BIN,
    FILE_TYPE_HEX,
    FILE_TYPE_UNKOWN
}file_type_enumt;


/**
 * @brief   open_file  open a file
 *
 * @param   int     fd      I/O, file descriptor
 * @param   char *      path    INPUT, file path
 * @param   int     mode    INPUT, file open mode
 *
 * @return  return 0 if success, and return fd; else return -1
 */
int open_file(int *fd, const char *path, int mode);

/**
 * @brief   lseek_file  Offset ofs bytes from the beginning of the file
 *
 * @param   int     fd      INTPUT, file descriptor
 * @param   int     ofs     INPUT, offset bytes
 *
 * @return  returns the resulting offset location as measured in bytes from the beginning of the file.  
 *          On error, the value (int) -1 is returned and errno is set to indicate the error.
 */
int lseek_file(int *fd, int ofs);

/**
 * @brief   read_bytes  attempts to read up to count bytes from file descriptor fd into the buffer starting at buff.
 *
 * @param   int     fd      I, file descriptor
 * @param   void *      buff    O, Store the read byte content
 * @param   unsigned int    count   I, number of bytes to read
 *
 * @return  On success, the number of bytes read is returned (zero indicates end of file), 
 *          and the file position is advanced by this number.
 *          On error, -1 is returned, and errno is set appropriately.  
 *          In this case, it is left unspecified whether the file position (if any) changes.
 */
int read_bytes(int fd, void *buff, unsigned int count);

/**
 * @brief   write_bytes  writes up to count bytes from the buffer starting at buf to the file referred to by the file descriptor fd.
 *
 * @param   int         fd      I, file descriptor
 * @param   void *          buff    I, Stores what will be written to the file
 * @param   unsigned int        count   I, number of bytes to be written
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
int write_bytes(int *fd, const void *buff, unsigned int count);

/**
 * @brief   close_file  closes a file descriptor, so that it no longer refers to any file and may be reused.
 *
 * @param   int  fd     I, file descriptor
 *
 * @return  returns zero on success.  On error, -1 is returned, and errno is set appropriately.
 */
int close_file(int fd);

int fread_bytes(FILE* fp, void *buff, unsigned int count);
int fread_xbytes(FILE* fp, void *buff, unsigned int n, unsigned int x);
int fwrite_bytes(FILE *fp, const void *buff, unsigned int count);
int fwrite_xbytes(FILE *fp, const void *buff, unsigned int n, unsigned int x);
int read_file(const char * fpath, char * buff, unsigned int *count);
int write_file(const char * fpath, bool_t is_app, char * buff, unsigned int *count);
int get_file_size(const char * path);
int get_file_size(FILE *file);
unsigned int get_file_total_line(FILE *fp, unsigned int per_line_bytes);
int set_nonblocking(int fd);


char *f_asprintf(char *fmt, ...);


#endif

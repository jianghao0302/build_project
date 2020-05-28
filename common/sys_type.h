/**
 * @script    sys_type.h
 * @brief  
 * @version  1.0.0
 * @modify  2019-11-27
 */

#ifndef __SYS_TYPE_H__
#define __SYS_TYPE_H__

#define UNUSED(A)   (void *)(A)


#ifndef FALSE
#      define  FALSE   (0)
#endif

#ifndef TRUE
#      define  TRUE    (1)
#endif

#ifndef NULL
#      define  NULL 0
#endif


enum bool_t { TRUE = 1, FALSE = 0};
typedef enum bool_t bool_t;

typedef signed char	        int8_t;
typedef unsigned char	      uint8_t;
typedef short		            int16_t;
typedef unsigned short	    uint16_t;
typedef int		              int32_t;
typedef unsigned int	      uint32_t;

typedef unsigned long       u_long;
typedef unsigned int        u_int;
typedef unsigned short      u_short;
typedef unsigned char       u_char;

#endif

multiline_comment|/*&n; *  drivers/s390/char/sclp_tty.h&n; *    interface to the SCLP-read/write driver&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Peschke &lt;mpeschke@de.ibm.com&gt;&n; *&t;&t; Martin Schwidefsky &lt;schwidefsky@de.ibm.com&gt;&n; */
macro_line|#ifndef __SCLP_TTY_H__
DECL|macro|__SCLP_TTY_H__
mdefine_line|#define __SCLP_TTY_H__
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/termios.h&gt;
macro_line|#include &lt;linux/tty_driver.h&gt;
multiline_comment|/* This is the type of data structures storing sclp ioctl setting. */
DECL|struct|sclp_ioctls
r_struct
id|sclp_ioctls
(brace
DECL|member|htab
r_int
r_int
id|htab
suffix:semicolon
DECL|member|echo
r_int
r_char
id|echo
suffix:semicolon
DECL|member|columns
r_int
r_int
id|columns
suffix:semicolon
DECL|member|final_nl
r_int
r_char
id|final_nl
suffix:semicolon
DECL|member|max_sccb
r_int
r_int
id|max_sccb
suffix:semicolon
DECL|member|kmem_sccb
r_int
r_int
id|kmem_sccb
suffix:semicolon
multiline_comment|/* can&squot;t be modified at run time */
DECL|member|tolower
r_int
r_char
id|tolower
suffix:semicolon
DECL|member|delim
r_int
r_char
id|delim
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* must be unique, FIXME: must be added in Documentation/ioctl_number.txt */
DECL|macro|SCLP_IOCTL_LETTER
mdefine_line|#define SCLP_IOCTL_LETTER &squot;B&squot;
multiline_comment|/* set width of horizontal tabulator */
DECL|macro|TIOCSCLPSHTAB
mdefine_line|#define TIOCSCLPSHTAB&t;_IOW(SCLP_IOCTL_LETTER, 0, unsigned short)
multiline_comment|/* enable/disable echo of input (independent from line discipline) */
DECL|macro|TIOCSCLPSECHO
mdefine_line|#define TIOCSCLPSECHO&t;_IOW(SCLP_IOCTL_LETTER, 1, unsigned char)
multiline_comment|/* set number of colums for output */
DECL|macro|TIOCSCLPSCOLS
mdefine_line|#define TIOCSCLPSCOLS&t;_IOW(SCLP_IOCTL_LETTER, 2, unsigned short)
multiline_comment|/* enable/disable writing without final new line character */
DECL|macro|TIOCSCLPSNL
mdefine_line|#define TIOCSCLPSNL&t;_IOW(SCLP_IOCTL_LETTER, 4, signed char)
multiline_comment|/* set the maximum buffers size for output, rounded up to next 4kB boundary */
DECL|macro|TIOCSCLPSOBUF
mdefine_line|#define TIOCSCLPSOBUF&t;_IOW(SCLP_IOCTL_LETTER, 5, unsigned short)
multiline_comment|/* set initial (default) sclp ioctls */
DECL|macro|TIOCSCLPSINIT
mdefine_line|#define TIOCSCLPSINIT&t;_IO(SCLP_IOCTL_LETTER, 6)
multiline_comment|/* enable/disable conversion from upper to lower case of input */
DECL|macro|TIOCSCLPSCASE
mdefine_line|#define TIOCSCLPSCASE&t;_IOW(SCLP_IOCTL_LETTER, 7, unsigned char)
multiline_comment|/* set special character used for separating upper and lower case, */
multiline_comment|/* 0x00 disables this feature */
DECL|macro|TIOCSCLPSDELIM
mdefine_line|#define TIOCSCLPSDELIM&t;_IOW(SCLP_IOCTL_LETTER, 9, unsigned char)
multiline_comment|/* get width of horizontal tabulator */
DECL|macro|TIOCSCLPGHTAB
mdefine_line|#define TIOCSCLPGHTAB&t;_IOR(SCLP_IOCTL_LETTER, 10, unsigned short)
multiline_comment|/* Is echo of input enabled ? (independent from line discipline) */
DECL|macro|TIOCSCLPGECHO
mdefine_line|#define TIOCSCLPGECHO&t;_IOR(SCLP_IOCTL_LETTER, 11, unsigned char)
multiline_comment|/* get number of colums for output */
DECL|macro|TIOCSCLPGCOLS
mdefine_line|#define TIOCSCLPGCOLS&t;_IOR(SCLP_IOCTL_LETTER, 12, unsigned short)
multiline_comment|/* Is writing without final new line character enabled ? */
DECL|macro|TIOCSCLPGNL
mdefine_line|#define TIOCSCLPGNL&t;_IOR(SCLP_IOCTL_LETTER, 14, signed char)
multiline_comment|/* get the maximum buffers size for output */
DECL|macro|TIOCSCLPGOBUF
mdefine_line|#define TIOCSCLPGOBUF&t;_IOR(SCLP_IOCTL_LETTER, 15, unsigned short)
multiline_comment|/* Is conversion from upper to lower case of input enabled ? */
DECL|macro|TIOCSCLPGCASE
mdefine_line|#define TIOCSCLPGCASE&t;_IOR(SCLP_IOCTL_LETTER, 17, unsigned char)
multiline_comment|/* get special character used for separating upper and lower case, */
multiline_comment|/* 0x00 disables this feature */
DECL|macro|TIOCSCLPGDELIM
mdefine_line|#define TIOCSCLPGDELIM&t;_IOR(SCLP_IOCTL_LETTER, 19, unsigned char)
multiline_comment|/* get the number of buffers/pages got from kernel at startup */
DECL|macro|TIOCSCLPGKBUF
mdefine_line|#define TIOCSCLPGKBUF&t;_IOR(SCLP_IOCTL_LETTER, 20, unsigned short)
r_extern
r_struct
id|tty_driver
op_star
id|sclp_tty_driver
suffix:semicolon
macro_line|#endif&t;/* __SCLP_TTY_H__ */
eof

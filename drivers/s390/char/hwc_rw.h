multiline_comment|/*&n; *  drivers/s390/char/hwc_rw.h&n; *    interface to the HWC-read/write driver &n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Peschke &lt;peschke@fh-brandenburg.de&gt;&n; */
macro_line|#ifndef __HWC_RW_H__
DECL|macro|__HWC_RW_H__
mdefine_line|#define __HWC_RW_H__
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#ifndef __HWC_RW_C__
r_extern
r_int
id|hwc_init
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|hwc_write
(paren
r_int
id|from_user
comma
r_const
r_int
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|hwc_chars_in_buffer
(paren
r_int
r_char
)paren
suffix:semicolon
r_extern
r_int
r_int
id|hwc_write_room
(paren
r_int
r_char
)paren
suffix:semicolon
r_extern
r_void
id|hwc_flush_buffer
(paren
r_int
r_char
)paren
suffix:semicolon
r_extern
r_int
r_int
id|hwc_ioctl
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|do_hwc_interrupt
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|hwc_printk
(paren
r_const
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
macro_line|#else
r_extern
r_void
id|store_hwc_input
(paren
r_int
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|wake_up_hwc_tty
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|IN_HWCB
mdefine_line|#define IN_HWCB      1
DECL|macro|IN_WRITE_BUF
mdefine_line|#define IN_WRITE_BUF 2
DECL|macro|IN_BUFS_TOTAL
mdefine_line|#define IN_BUFS_TOTAL        (IN_HWCB | IN_WRITE_BUF)
DECL|typedef|ioctl_htab_t
r_typedef
r_int
r_int
r_int
id|ioctl_htab_t
suffix:semicolon
DECL|typedef|ioctl_echo_t
r_typedef
r_int
r_char
id|ioctl_echo_t
suffix:semicolon
DECL|typedef|ioctl_cols_t
r_typedef
r_int
r_int
r_int
id|ioctl_cols_t
suffix:semicolon
DECL|typedef|ioctl_code_t
r_typedef
r_int
r_char
id|ioctl_code_t
suffix:semicolon
DECL|typedef|ioctl_nl_t
r_typedef
r_int
r_char
id|ioctl_nl_t
suffix:semicolon
DECL|typedef|ioctl_obuf_t
r_typedef
r_int
r_int
r_int
id|ioctl_obuf_t
suffix:semicolon
DECL|typedef|ioctl_case_t
r_typedef
r_int
r_char
id|ioctl_case_t
suffix:semicolon
DECL|typedef|ioctl_delim_t
r_typedef
r_int
r_char
id|ioctl_delim_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|width_htab
id|ioctl_htab_t
id|width_htab
suffix:semicolon
DECL|member|echo
id|ioctl_echo_t
id|echo
suffix:semicolon
DECL|member|columns
id|ioctl_cols_t
id|columns
suffix:semicolon
DECL|member|code
id|ioctl_code_t
id|code
suffix:semicolon
DECL|member|final_nl
id|ioctl_nl_t
id|final_nl
suffix:semicolon
DECL|member|max_hwcb
id|ioctl_obuf_t
id|max_hwcb
suffix:semicolon
DECL|member|kmem_hwcb
id|ioctl_obuf_t
id|kmem_hwcb
suffix:semicolon
DECL|member|tolower
id|ioctl_case_t
id|tolower
suffix:semicolon
DECL|member|delim
id|ioctl_delim_t
id|delim
suffix:semicolon
DECL|typedef|hwc_ioctls_t
)brace
id|hwc_ioctls_t
suffix:semicolon
DECL|variable|_hwc_ioctls
r_static
id|hwc_ioctls_t
id|_hwc_ioctls
suffix:semicolon
DECL|macro|HWC_IOCTL_LETTER
mdefine_line|#define HWC_IOCTL_LETTER &squot;B&squot;
DECL|macro|TIOCHWCSHTAB
mdefine_line|#define TIOCHWCSHTAB&t;_IOW(HWC_IOCTL_LETTER, 0, _hwc_ioctls.width_htab)
DECL|macro|TIOCHWCSECHO
mdefine_line|#define TIOCHWCSECHO&t;_IOW(HWC_IOCTL_LETTER, 1, _hwc_ioctls.echo)
DECL|macro|TIOCHWCSCOLS
mdefine_line|#define TIOCHWCSCOLS&t;_IOW(HWC_IOCTL_LETTER, 2, _hwc_ioctls.columns)
DECL|macro|TIOCHWCSCODE
mdefine_line|#define TIOCHWCSCODE&t;_IOW(HWC_IOCTL_LETTER, 3, _hwc_ioctls.code)
DECL|macro|TIOCHWCSNL
mdefine_line|#define TIOCHWCSNL&t;_IOW(HWC_IOCTL_LETTER, 4, _hwc_ioctls.final_nl)
DECL|macro|TIOCHWCSOBUF
mdefine_line|#define TIOCHWCSOBUF&t;_IOW(HWC_IOCTL_LETTER, 5, _hwc_ioctls.max_hwcb)
DECL|macro|TIOCHWCSINIT
mdefine_line|#define TIOCHWCSINIT&t;_IO(HWC_IOCTL_LETTER, 6)
DECL|macro|TIOCHWCSCASE
mdefine_line|#define TIOCHWCSCASE&t;_IOW(HWC_IOCTL_LETTER, 7, _hwc_ioctls.tolower)
DECL|macro|TIOCHWCSDELIM
mdefine_line|#define TIOCHWCSDELIM&t;_IOW(HWC_IOCTL_LETTER, 9, _hwc_ioctls.delim)
DECL|macro|TIOCHWCGHTAB
mdefine_line|#define TIOCHWCGHTAB&t;_IOR(HWC_IOCTL_LETTER, 10, _hwc_ioctls.width_htab)
DECL|macro|TIOCHWCGECHO
mdefine_line|#define TIOCHWCGECHO&t;_IOR(HWC_IOCTL_LETTER, 11, _hwc_ioctls.echo)
DECL|macro|TIOCHWCGCOLS
mdefine_line|#define TIOCHWCGCOLS&t;_IOR(HWC_IOCTL_LETTER, 12, _hwc_ioctls.columns)
DECL|macro|TIOCHWCGCODE
mdefine_line|#define TIOCHWCGCODE&t;_IOR(HWC_IOCTL_LETTER, 13, _hwc_ioctls.code)
DECL|macro|TIOCHWCGNL
mdefine_line|#define TIOCHWCGNL&t;_IOR(HWC_IOCTL_LETTER, 14, _hwc_ioctls.final_nl)
DECL|macro|TIOCHWCGOBUF
mdefine_line|#define TIOCHWCGOBUF&t;_IOR(HWC_IOCTL_LETTER, 15, _hwc_ioctls.max_hwcb)
DECL|macro|TIOCHWCGINIT
mdefine_line|#define TIOCHWCGINIT&t;_IOR(HWC_IOCTL_LETTER, 16, _hwc_ioctls)
DECL|macro|TIOCHWCGCASE
mdefine_line|#define TIOCHWCGCASE&t;_IOR(HWC_IOCTL_LETTER, 17, _hwc_ioctls.tolower)
DECL|macro|TIOCHWCGDELIM
mdefine_line|#define TIOCHWCGDELIM&t;_IOR(HWC_IOCTL_LETTER, 19, _hwc_ioctls.delim)
DECL|macro|TIOCHWCGKBUF
mdefine_line|#define TIOCHWCGKBUF&t;_IOR(HWC_IOCTL_LETTER, 20, _hwc_ioctls.max_hwcb)
DECL|macro|TIOCHWCGCURR
mdefine_line|#define TIOCHWCGCURR&t;_IOR(HWC_IOCTL_LETTER, 21, _hwc_ioctls)
DECL|macro|CODE_ASCII
mdefine_line|#define CODE_ASCII              0x0
DECL|macro|CODE_EBCDIC
mdefine_line|#define CODE_EBCDIC             0x1
macro_line|#endif
eof

multiline_comment|/* bootstd.h:  Bootloader system call interface&n; *&n; * (c) 1999, Rt-Control, Inc.&n; */
macro_line|#ifndef __BOOTSTD_H__
DECL|macro|__BOOTSTD_H__
mdefine_line|#define __BOOTSTD_H__
DECL|macro|NR_BSC
mdefine_line|#define NR_BSC 21            /* last used bootloader system call */
DECL|macro|__BN_reset
mdefine_line|#define __BN_reset        0  /* reset and start the bootloader */
DECL|macro|__BN_test
mdefine_line|#define __BN_test         1  /* tests the system call interface */
DECL|macro|__BN_exec
mdefine_line|#define __BN_exec         2  /* executes a bootloader image */
DECL|macro|__BN_exit
mdefine_line|#define __BN_exit         3  /* terminates a bootloader image */
DECL|macro|__BN_program
mdefine_line|#define __BN_program      4  /* program FLASH from a chain */
DECL|macro|__BN_erase
mdefine_line|#define __BN_erase        5  /* erase sector(s) of FLASH */
DECL|macro|__BN_open
mdefine_line|#define __BN_open         6
DECL|macro|__BN_write
mdefine_line|#define __BN_write        7
DECL|macro|__BN_read
mdefine_line|#define __BN_read         8
DECL|macro|__BN_close
mdefine_line|#define __BN_close        9
DECL|macro|__BN_mmap
mdefine_line|#define __BN_mmap         10 /* map a file descriptor into memory */
DECL|macro|__BN_munmap
mdefine_line|#define __BN_munmap       11 /* remove a file to memory mapping */
DECL|macro|__BN_gethwaddr
mdefine_line|#define __BN_gethwaddr    12 /* get the hardware address of my interfaces */
DECL|macro|__BN_getserialnum
mdefine_line|#define __BN_getserialnum 13 /* get the serial number of this board */
DECL|macro|__BN_getbenv
mdefine_line|#define __BN_getbenv      14 /* get a bootloader envvar */
DECL|macro|__BN_setbenv
mdefine_line|#define __BN_setbenv      15 /* get a bootloader envvar */
DECL|macro|__BN_setpmask
mdefine_line|#define __BN_setpmask     16 /* set the protection mask */
DECL|macro|__BN_readenv
mdefine_line|#define __BN_readenv      17 /* read environment variables */
DECL|macro|__BN_flash_chattr_range
mdefine_line|#define __BN_flash_chattr_range&t;&t;18
DECL|macro|__BN_flash_erase_range
mdefine_line|#define __BN_flash_erase_range&t;&t;19
DECL|macro|__BN_flash_write_range
mdefine_line|#define __BN_flash_write_range&t;&t;20
multiline_comment|/* Calling conventions compatible to (uC)linux/68k&n; * We use simmilar macros to call into the bootloader as for uClinux&n; */
DECL|macro|__bsc_return
mdefine_line|#define __bsc_return(type, res) &bslash;&n;do { &bslash;&n;   if ((unsigned long)(res) &gt;= (unsigned long)(-64)) { &bslash;&n;      /* let errno be a function, preserve res in %d0 */ &bslash;&n;      int __err = -(res); &bslash;&n;      errno = __err; &bslash;&n;      res = -1; &bslash;&n;   } &bslash;&n;   return (type)(res); &bslash;&n;} while (0)
DECL|macro|_bsc0
mdefine_line|#define _bsc0(type,name) &bslash;&n;type name(void) &bslash;&n;{ &bslash;&n;   register long __res __asm__ (&quot;%d0&quot;) = __BN_##name; &bslash;&n;   __asm__ __volatile__ (&quot;trap #2&quot; &bslash;&n;                         : &quot;=g&quot; (__res) &bslash;&n;                         : &quot;0&quot; (__res) &bslash;&n;                         : &quot;%d0&quot;); &bslash;&n;   __bsc_return(type,__res); &bslash;&n;}
DECL|macro|_bsc1
mdefine_line|#define _bsc1(type,name,atype,a) &bslash;&n;type name(atype a) &bslash;&n;{ &bslash;&n;   register long __res __asm__ (&quot;%d0&quot;) = __BN_##name; &bslash;&n;   register long __a __asm__ (&quot;%d1&quot;) = (long)a; &bslash;&n;   __asm__ __volatile__ (&quot;trap #2&quot; &bslash;&n;                         : &quot;=g&quot; (__res) &bslash;&n;                         : &quot;0&quot; (__res), &quot;d&quot; (__a) &bslash;&n;                         : &quot;%d0&quot;); &bslash;&n;   __bsc_return(type,__res); &bslash;&n;}
DECL|macro|_bsc2
mdefine_line|#define _bsc2(type,name,atype,a,btype,b) &bslash;&n;type name(atype a, btype b) &bslash;&n;{ &bslash;&n;   register long __res __asm__ (&quot;%d0&quot;) = __BN_##name; &bslash;&n;   register long __a __asm__ (&quot;%d1&quot;) = (long)a; &bslash;&n;   register long __b __asm__ (&quot;%d2&quot;) = (long)b; &bslash;&n;   __asm__ __volatile__ (&quot;trap #2&quot; &bslash;&n;                         : &quot;=g&quot; (__res) &bslash;&n;                         : &quot;0&quot; (__res), &quot;d&quot; (__a), &quot;d&quot; (__b) &bslash;&n;                         : &quot;%d0&quot;); &bslash;&n;   __bsc_return(type,__res); &bslash;&n;}
DECL|macro|_bsc3
mdefine_line|#define _bsc3(type,name,atype,a,btype,b,ctype,c) &bslash;&n;type name(atype a, btype b, ctype c) &bslash;&n;{ &bslash;&n;   register long __res __asm__ (&quot;%d0&quot;) = __BN_##name; &bslash;&n;   register long __a __asm__ (&quot;%d1&quot;) = (long)a; &bslash;&n;   register long __b __asm__ (&quot;%d2&quot;) = (long)b; &bslash;&n;   register long __c __asm__ (&quot;%d3&quot;) = (long)c; &bslash;&n;   __asm__ __volatile__ (&quot;trap #2&quot; &bslash;&n;                         : &quot;=g&quot; (__res) &bslash;&n;                         : &quot;0&quot; (__res), &quot;d&quot; (__a), &quot;d&quot; (__b), &bslash;&n;                           &quot;d&quot; (__c) &bslash;&n;                         : &quot;%d0&quot;); &bslash;&n;   __bsc_return(type,__res); &bslash;&n;}
DECL|macro|_bsc4
mdefine_line|#define _bsc4(type,name,atype,a,btype,b,ctype,c,dtype,d) &bslash;&n;type name(atype a, btype b, ctype c, dtype d) &bslash;&n;{ &bslash;&n;   register long __res __asm__ (&quot;%d0&quot;) = __BN_##name; &bslash;&n;   register long __a __asm__ (&quot;%d1&quot;) = (long)a; &bslash;&n;   register long __b __asm__ (&quot;%d2&quot;) = (long)b; &bslash;&n;   register long __c __asm__ (&quot;%d3&quot;) = (long)c; &bslash;&n;   register long __d __asm__ (&quot;%d4&quot;) = (long)d; &bslash;&n;   __asm__ __volatile__ (&quot;trap #2&quot; &bslash;&n;                         : &quot;=g&quot; (__res) &bslash;&n;                         : &quot;0&quot; (__res), &quot;d&quot; (__a), &quot;d&quot; (__b), &bslash;&n;                           &quot;d&quot; (__c), &quot;d&quot; (__d) &bslash;&n;                         : &quot;%d0&quot;); &bslash;&n;   __bsc_return(type,__res); &bslash;&n;}
DECL|macro|_bsc5
mdefine_line|#define _bsc5(type,name,atype,a,btype,b,ctype,c,dtype,d,etype,e) &bslash;&n;type name(atype a, btype b, ctype c, dtype d, etype e) &bslash;&n;{ &bslash;&n;   register long __res __asm__ (&quot;%d0&quot;) = __BN_##name; &bslash;&n;   register long __a __asm__ (&quot;%d1&quot;) = (long)a; &bslash;&n;   register long __b __asm__ (&quot;%d2&quot;) = (long)b; &bslash;&n;   register long __c __asm__ (&quot;%d3&quot;) = (long)c; &bslash;&n;   register long __d __asm__ (&quot;%d4&quot;) = (long)d; &bslash;&n;   register long __e __asm__ (&quot;%d5&quot;) = (long)e; &bslash;&n;   __asm__ __volatile__ (&quot;trap #2&quot; &bslash;&n;                         : &quot;=g&quot; (__res) &bslash;&n;                         : &quot;0&quot; (__res), &quot;d&quot; (__a), &quot;d&quot; (__b), &bslash;&n;                           &quot;d&quot; (__c), &quot;d&quot; (__d), &quot;d&quot; (__e) &bslash;&n;                         : &quot;%d0&quot;); &bslash;&n;   __bsc_return(type,__res); &bslash;&n;}
macro_line|#endif /* __BOOTSTD_H__ */
eof

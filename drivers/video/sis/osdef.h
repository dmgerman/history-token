multiline_comment|/* #define WINCE_HEADER */
multiline_comment|/* #define WIN2000 */
multiline_comment|/* #define TC */
DECL|macro|LINUX_KERNEL
mdefine_line|#define LINUX_KERNEL&t;   /* Kernel framebuffer */
multiline_comment|/* #define LINUX_XF86 */
multiline_comment|/* XFree86 */
multiline_comment|/**********************************************************************/
macro_line|#ifdef LINUX_KERNEL
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#ifdef CONFIG_FB_SIS_300
DECL|macro|SIS300
mdefine_line|#define SIS300
macro_line|#endif
macro_line|#ifdef CONFIG_FB_SIS_315
DECL|macro|SIS315H
mdefine_line|#define SIS315H
macro_line|#endif
macro_line|#if 1
DECL|macro|SISFBACCEL
mdefine_line|#define SISFBACCEL&t;/* Include 2D acceleration */
macro_line|#endif
macro_line|#if 1
DECL|macro|SISFB_PAN
mdefine_line|#define SISFB_PAN&t;/* Include Y-Panning code */
macro_line|#endif
macro_line|#else
multiline_comment|/*&t;#define SIS300*/
DECL|macro|SIS315H
mdefine_line|#define SIS315H
macro_line|#endif
macro_line|#ifdef LINUX_XF86
DECL|macro|SIS300
mdefine_line|#define SIS300
multiline_comment|/* #define SIS315H */
multiline_comment|/* TW: done above */
macro_line|#endif
multiline_comment|/**********************************************************************/
macro_line|#ifdef TC
macro_line|#endif
macro_line|#ifdef WIN2000
macro_line|#endif
macro_line|#ifdef WINCE_HEADER
macro_line|#endif
macro_line|#ifdef LINUX_XF86
macro_line|#endif
macro_line|#ifdef LINUX_KERNEL
macro_line|#endif
multiline_comment|/**********************************************************************/
macro_line|#ifdef TC
DECL|macro|SiS_SetMemory
mdefine_line|#define SiS_SetMemory(MemoryAddress,MemorySize,value) memset(MemoryAddress, value, MemorySize);
macro_line|#endif
macro_line|#ifdef WIN2000
DECL|macro|SiS_SetMemory
mdefine_line|#define SiS_SetMemory(MemoryAddress,MemorySize,value) MemFill((PVOID) MemoryAddress,(ULONG) MemorySize,(UCHAR) value);
macro_line|#endif
macro_line|#ifdef WINCE_HEADER
DECL|macro|SiS_SetMemory
mdefine_line|#define SiS_SetMemory(MemoryAddress,MemorySize,value) memset(MemoryAddress, value, MemorySize);
macro_line|#endif
macro_line|#ifdef LINUX_XF86
DECL|macro|SiS_SetMemory
mdefine_line|#define SiS_SetMemory(MemoryAddress,MemorySize,value) memset(MemoryAddress, value, MemorySize)
macro_line|#endif
macro_line|#ifdef LINUX_KERNEL
DECL|macro|SiS_SetMemory
mdefine_line|#define SiS_SetMemory(MemoryAddress,MemorySize,value) memset(MemoryAddress, value, MemorySize)
macro_line|#endif
multiline_comment|/**********************************************************************/
multiline_comment|/**********************************************************************/
macro_line|#ifdef TC
DECL|macro|SiS_MemoryCopy
mdefine_line|#define SiS_MemoryCopy(Destination,Soruce,Length) memmove(Destination, Soruce, Length);
macro_line|#endif
macro_line|#ifdef WIN2000
DECL|macro|SiS_MemoryCopy
mdefine_line|#define SiS_MemoryCopy(Destination,Soruce,Length)  /*VideoPortMoveMemory((PUCHAR)Destination , Soruce,length);*/
macro_line|#endif
macro_line|#ifdef WINCE_HEADER
DECL|macro|SiS_MemoryCopy
mdefine_line|#define SiS_MemoryCopy(Destination,Soruce,Length) memmove(Destination, Soruce, Length);
macro_line|#endif
macro_line|#ifdef LINUX_XF86
DECL|macro|SiS_MemoryCopy
mdefine_line|#define SiS_MemoryCopy(Destination,Soruce,Length) memcpy(Destination,Soruce,Length)
macro_line|#endif
macro_line|#ifdef LINUX_KERNEL
DECL|macro|SiS_MemoryCopy
mdefine_line|#define SiS_MemoryCopy(Destination,Soruce,Length) memcpy(Destination,Soruce,Length)
macro_line|#endif
multiline_comment|/**********************************************************************/
macro_line|#ifdef OutPortByte
DECL|macro|OutPortByte
macro_line|#undef OutPortByte
macro_line|#endif /* OutPortByte */
macro_line|#ifdef OutPortWord
DECL|macro|OutPortWord
macro_line|#undef OutPortWord
macro_line|#endif /* OutPortWord */
macro_line|#ifdef OutPortLong
DECL|macro|OutPortLong
macro_line|#undef OutPortLong
macro_line|#endif /* OutPortLong */
macro_line|#ifdef InPortByte
DECL|macro|InPortByte
macro_line|#undef InPortByte
macro_line|#endif /* InPortByte */
macro_line|#ifdef InPortWord
DECL|macro|InPortWord
macro_line|#undef InPortWord
macro_line|#endif /* InPortWord */
macro_line|#ifdef InPortLong
DECL|macro|InPortLong
macro_line|#undef InPortLong
macro_line|#endif /* InPortLong */
multiline_comment|/**********************************************************************/
multiline_comment|/*  TC                                                                */
multiline_comment|/**********************************************************************/
macro_line|#ifdef TC
DECL|macro|OutPortByte
mdefine_line|#define OutPortByte(p,v) outp((unsigned short)(p),(unsigned char)(v))
DECL|macro|OutPortWord
mdefine_line|#define OutPortWord(p,v) outp((unsigned short)(p),(unsigned short)(v))
DECL|macro|OutPortLong
mdefine_line|#define OutPortLong(p,v) outp((unsigned short)(p),(unsigned long)(v))
DECL|macro|InPortByte
mdefine_line|#define InPortByte(p)    inp((unsigned short)(p))
DECL|macro|InPortWord
mdefine_line|#define InPortWord(p)    inp((unsigned short)(p))
DECL|macro|InPortLong
mdefine_line|#define InPortLong(p)    ((inp((unsigned short)(p+2))&lt;&lt;16) | inp((unsigned short)(p)))
macro_line|#endif
multiline_comment|/**********************************************************************/
multiline_comment|/*  LINUX XF86                                                        */
multiline_comment|/**********************************************************************/
macro_line|#ifdef LINUX_XF86
DECL|macro|OutPortByte
mdefine_line|#define OutPortByte(p,v) outb((CARD16)(p),(CARD8)(v))
DECL|macro|OutPortWord
mdefine_line|#define OutPortWord(p,v) outw((CARD16)(p),(CARD16)(v))
DECL|macro|OutPortLong
mdefine_line|#define OutPortLong(p,v) outl((CARD16)(p),(CARD32)(v))
DECL|macro|InPortByte
mdefine_line|#define InPortByte(p)    inb((CARD16)(p))
DECL|macro|InPortWord
mdefine_line|#define InPortWord(p)    inw((CARD16)(p))
DECL|macro|InPortLong
mdefine_line|#define InPortLong(p)    inl((CARD16)(p))
macro_line|#endif
multiline_comment|/**********************************************************************/
multiline_comment|/*  LINUX KERNEL                                                      */
multiline_comment|/**********************************************************************/
macro_line|#ifdef LINUX_KERNEL
DECL|macro|OutPortByte
mdefine_line|#define OutPortByte(p,v) outb((u8)(v),(u16)(p))
DECL|macro|OutPortWord
mdefine_line|#define OutPortWord(p,v) outw((u16)(v),(u16)(p))
DECL|macro|OutPortLong
mdefine_line|#define OutPortLong(p,v) outl((u32)(v),(u16)(p))
DECL|macro|InPortByte
mdefine_line|#define InPortByte(p)    inb((u16)(p))
DECL|macro|InPortWord
mdefine_line|#define InPortWord(p)    inw((u16)(p))
DECL|macro|InPortLong
mdefine_line|#define InPortLong(p)    inl((u16)(p))
macro_line|#endif
multiline_comment|/**********************************************************************/
multiline_comment|/*  WIN 2000                                                          */
multiline_comment|/**********************************************************************/
macro_line|#ifdef WIN2000
DECL|macro|OutPortByte
mdefine_line|#define OutPortByte(p,v) VideoPortWritePortUchar ((PUCHAR) (p), (UCHAR) (v))
DECL|macro|OutPortWord
mdefine_line|#define OutPortWord(p,v) VideoPortWritePortUshort((PUSHORT) (p), (USHORT) (v))
DECL|macro|OutPortLong
mdefine_line|#define OutPortLong(p,v) VideoPortWritePortUlong ((PULONG) (p), (ULONG) (v))
DECL|macro|InPortByte
mdefine_line|#define InPortByte(p)    VideoPortReadPortUchar  ((PUCHAR) (p))
DECL|macro|InPortWord
mdefine_line|#define InPortWord(p)    VideoPortReadPortUshort ((PUSHORT) (p))
DECL|macro|InPortLong
mdefine_line|#define InPortLong(p)    VideoPortReadPortUlong  ((PULONG) (p))
macro_line|#endif
multiline_comment|/**********************************************************************/
multiline_comment|/*  WIN CE                                                            */
multiline_comment|/**********************************************************************/
macro_line|#ifdef WINCE_HEADER
DECL|macro|OutPortByte
mdefine_line|#define OutPortByte(p,v) WRITE_PORT_UCHAR ((PUCHAR) (p), (UCHAR) (v))
DECL|macro|OutPortWord
mdefine_line|#define OutPortWord(p,v) WRITE_PORT_USHORT((PUSHORT) (p), (USHORT) (v))
DECL|macro|OutPortLong
mdefine_line|#define OutPortLong(p,v) WRITE_PORT_ULONG ((PULONG) (p), (ULONG) (v))
DECL|macro|InPortByte
mdefine_line|#define InPortByte(p)    READ_PORT_UCHAR  ((PUCHAR) (p))
DECL|macro|InPortWord
mdefine_line|#define InPortWord(p)    READ_PORT_USHORT ((PUSHORT) (p))
DECL|macro|InPortLong
mdefine_line|#define InPortLong(p)    READ_PORT_ULONG  ((PULONG) (p))
macro_line|#endif
eof

DECL|macro|LINUX_KERNEL
mdefine_line|#define LINUX_KERNEL
DECL|macro|SiS_SetMemory
mdefine_line|#define SiS_SetMemory(MemoryAddress,MemorySize,value) memset(MemoryAddress, value, MemorySize)
DECL|macro|SiS_MemoryCopy
mdefine_line|#define SiS_MemoryCopy(Destination,Soruce,Length) memcpy(Destination,Soruce,Length)
multiline_comment|/**********************************************************************/
macro_line|#ifdef OutPortByte
DECL|macro|OutPortByte
macro_line|#undef OutPortByte
macro_line|#endif&t;&t;&t;&t;/* OutPortByte */
macro_line|#ifdef OutPortWord
DECL|macro|OutPortWord
macro_line|#undef OutPortWord
macro_line|#endif&t;&t;&t;&t;/* OutPortWord */
macro_line|#ifdef OutPortLong
DECL|macro|OutPortLong
macro_line|#undef OutPortLong
macro_line|#endif&t;&t;&t;&t;/* OutPortLong */
macro_line|#ifdef InPortByte
DECL|macro|InPortByte
macro_line|#undef InPortByte
macro_line|#endif&t;&t;&t;&t;/* InPortByte */
macro_line|#ifdef InPortWord
DECL|macro|InPortWord
macro_line|#undef InPortWord
macro_line|#endif&t;&t;&t;&t;/* InPortWord */
macro_line|#ifdef InPortLong
DECL|macro|InPortLong
macro_line|#undef InPortLong
macro_line|#endif&t;&t;&t;&t;/* InPortLong */
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
eof

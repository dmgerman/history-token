multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;anchor.h -- Anchor CO-MEM Lite PCI host bridge part.&n; *&n; *&t;(C) Copyright 2000, Moreton Bay (www.moreton.com.au)&n; */
multiline_comment|/****************************************************************************/
macro_line|#ifndef&t;anchor_h
DECL|macro|anchor_h
mdefine_line|#define&t;anchor_h
multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;Define basic addressing info.&n; */
macro_line|#if defined(CONFIG_MOTOROLA) &amp;&amp; defined(CONFIG_M5407)
DECL|macro|COMEM_BASE
mdefine_line|#define&t;COMEM_BASE&t;0xFFFF0000&t;/* Base of CO-MEM address space */
DECL|macro|COMEM_IRQ
mdefine_line|#define&t;COMEM_IRQ&t;25&t;&t;/* IRQ of anchor part */
macro_line|#else
DECL|macro|COMEM_BASE
mdefine_line|#define&t;COMEM_BASE&t;0x80000000&t;/* Base of CO-MEM address space */
DECL|macro|COMEM_IRQ
mdefine_line|#define&t;COMEM_IRQ&t;25&t;&t;/* IRQ of anchor part */
macro_line|#endif
multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;4-byte registers of CO-MEM, so adjust register addresses for&n; *&t;easy access. Handy macro for word access too.&n; */
DECL|macro|LREG
mdefine_line|#define&t;LREG(a)&t;&t;((a) &gt;&gt; 2)
DECL|macro|WREG
mdefine_line|#define&t;WREG(a)&t;&t;((a) &gt;&gt; 1)
multiline_comment|/*&n; *&t;Define base addresses within CO-MEM Lite register address space.&n; */
DECL|macro|COMEM_I2O
mdefine_line|#define&t;COMEM_I2O&t;0x0000&t;&t;/* I2O registers */
DECL|macro|COMEM_OPREGS
mdefine_line|#define&t;COMEM_OPREGS&t;0x0400&t;&t;/* Operation registers */
DECL|macro|COMEM_PCIBUS
mdefine_line|#define&t;COMEM_PCIBUS&t;0x2000&t;&t;/* Direct access to PCI bus */
DECL|macro|COMEM_SHMEM
mdefine_line|#define&t;COMEM_SHMEM&t;0x4000&t;&t;/* Shared memory region */
DECL|macro|COMEM_SHMEMSIZE
mdefine_line|#define&t;COMEM_SHMEMSIZE&t;0x4000&t;&t;/* Size of shared memory */
multiline_comment|/*&n; *&t;Define CO-MEM Registers.&n; */
DECL|macro|COMEM_I2OHISR
mdefine_line|#define&t;COMEM_I2OHISR&t;0x0030&t;&t;/* I2O host interrupt status */
DECL|macro|COMEM_I2OHIMR
mdefine_line|#define&t;COMEM_I2OHIMR&t;0x0034&t;&t;/* I2O host interrupt mask */
DECL|macro|COMEM_I2OLISR
mdefine_line|#define&t;COMEM_I2OLISR&t;0x0038&t;&t;/* I2O local interrupt status */
DECL|macro|COMEM_I2OLIMR
mdefine_line|#define&t;COMEM_I2OLIMR&t;0x003c&t;&t;/* I2O local interrupt mask */
DECL|macro|COMEM_IBFPFIFO
mdefine_line|#define&t;COMEM_IBFPFIFO&t;0x0040&t;&t;/* I2O inbound free/post FIFO */
DECL|macro|COMEM_OBPFFIFO
mdefine_line|#define&t;COMEM_OBPFFIFO&t;0x0044&t;&t;/* I2O outbound post/free FIFO */
DECL|macro|COMEM_IBPFFIFO
mdefine_line|#define&t;COMEM_IBPFFIFO&t;0x0048&t;&t;/* I2O inbound post/free FIFO */
DECL|macro|COMEM_OBFPFIFO
mdefine_line|#define&t;COMEM_OBFPFIFO&t;0x004c&t;&t;/* I2O outbound free/post FIFO */
DECL|macro|COMEM_DAHBASE
mdefine_line|#define&t;COMEM_DAHBASE&t;0x0460&t;&t;/* Direct access base address */
DECL|macro|COMEM_NVCMD
mdefine_line|#define&t;COMEM_NVCMD&t;0x04a0&t;&t;/* I2C serial command */
DECL|macro|COMEM_NVREAD
mdefine_line|#define&t;COMEM_NVREAD&t;0x04a4&t;&t;/* I2C serial read */
DECL|macro|COMEM_NVSTAT
mdefine_line|#define&t;COMEM_NVSTAT&t;0x04a8&t;&t;/* I2C status */
DECL|macro|COMEM_DMALBASE
mdefine_line|#define&t;COMEM_DMALBASE&t;0x04b0&t;&t;/* DMA local base address */
DECL|macro|COMEM_DMAHBASE
mdefine_line|#define&t;COMEM_DMAHBASE&t;0x04b4&t;&t;/* DMA host base address */
DECL|macro|COMEM_DMASIZE
mdefine_line|#define&t;COMEM_DMASIZE&t;0x04b8&t;&t;/* DMA size */
DECL|macro|COMEM_DMACTL
mdefine_line|#define&t;COMEM_DMACTL&t;0x04bc&t;&t;/* DMA control */
DECL|macro|COMEM_HCTL
mdefine_line|#define&t;COMEM_HCTL&t;0x04e0&t;&t;/* Host control */
DECL|macro|COMEM_HINT
mdefine_line|#define&t;COMEM_HINT&t;0x04e4&t;&t;/* Host interrupt control/status */
DECL|macro|COMEM_HLDATA
mdefine_line|#define&t;COMEM_HLDATA&t;0x04e8&t;&t;/* Host to local data mailbox */
DECL|macro|COMEM_LINT
mdefine_line|#define&t;COMEM_LINT&t;0x04f4&t;&t;/* Local interrupt contole status */
DECL|macro|COMEM_LHDATA
mdefine_line|#define&t;COMEM_LHDATA&t;0x04f8&t;&t;/* Local to host data mailbox */
DECL|macro|COMEM_LBUSCFG
mdefine_line|#define&t;COMEM_LBUSCFG&t;0x04fc&t;&t;/* Local bus configuration */
multiline_comment|/*&n; *&t;Commands and flags for use with Direct Access Register.&n; */
DECL|macro|COMEM_DA_IACK
mdefine_line|#define&t;COMEM_DA_IACK&t;0x00000000&t;/* Interrupt acknowledge (read) */
DECL|macro|COMEM_DA_SPCL
mdefine_line|#define&t;COMEM_DA_SPCL&t;0x00000010&t;/* Special cycle (write) */
DECL|macro|COMEM_DA_MEMRD
mdefine_line|#define&t;COMEM_DA_MEMRD&t;0x00000004&t;/* Memory read cycle */
DECL|macro|COMEM_DA_MEMWR
mdefine_line|#define&t;COMEM_DA_MEMWR&t;0x00000004&t;/* Memory write cycle */
DECL|macro|COMEM_DA_IORD
mdefine_line|#define&t;COMEM_DA_IORD&t;0x00000002&t;/* I/O read cycle */
DECL|macro|COMEM_DA_IOWR
mdefine_line|#define&t;COMEM_DA_IOWR&t;0x00000002&t;/* I/O write cycle */
DECL|macro|COMEM_DA_CFGRD
mdefine_line|#define&t;COMEM_DA_CFGRD&t;0x00000006&t;/* Configuration read cycle */
DECL|macro|COMEM_DA_CFGWR
mdefine_line|#define&t;COMEM_DA_CFGWR&t;0x00000006&t;/* Configuration write cycle */
DECL|macro|COMEM_DA_ADDR
mdefine_line|#define&t;COMEM_DA_ADDR(a)&t;((a) &amp; 0xffffe000)
DECL|macro|COMEM_DA_OFFSET
mdefine_line|#define&t;COMEM_DA_OFFSET(a)&t;((a) &amp; 0x00001fff)
multiline_comment|/*&n; *&t;The PCI bus will be limited in what slots will actually be used.&n; *&t;Define valid device numbers for different boards.&n; */
macro_line|#if defined(CONFIG_MOTOROLA) &amp;&amp; defined(CONFIG_M5407)
DECL|macro|COMEM_MINDEV
mdefine_line|#define&t;COMEM_MINDEV&t;14&t;&t;/* Minimum valid DEVICE */
DECL|macro|COMEM_MAXDEV
mdefine_line|#define&t;COMEM_MAXDEV&t;14&t;&t;/* Maximum valid DEVICE */
DECL|macro|COMEM_BRIDGEDEV
mdefine_line|#define&t;COMEM_BRIDGEDEV&t;15&t;&t;/* Slot bridge is in */
macro_line|#else
DECL|macro|COMEM_MINDEV
mdefine_line|#define&t;COMEM_MINDEV&t;0&t;&t;/* Minimum valid DEVICE */
DECL|macro|COMEM_MAXDEV
mdefine_line|#define&t;COMEM_MAXDEV&t;3&t;&t;/* Maximum valid DEVICE */
macro_line|#endif
DECL|macro|COMEM_MAXPCI
mdefine_line|#define&t;COMEM_MAXPCI&t;(COMEM_MAXDEV+1)&t;/* Maximum PCI devices */
multiline_comment|/****************************************************************************/
macro_line|#endif&t;/* anchor_h */
eof

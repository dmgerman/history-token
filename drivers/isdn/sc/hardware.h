multiline_comment|/*&n; * Hardware specific macros, defines and structures&n; */
macro_line|#ifndef HARDWARE_H
DECL|macro|HARDWARE_H
mdefine_line|#define HARDWARE_H
macro_line|#include &lt;asm/param.h&gt;&t;&t;&t;/* For HZ */
multiline_comment|/*&n; * General hardware parameters common to all ISA adapters&n; */
DECL|macro|MAX_CARDS
mdefine_line|#define MAX_CARDS&t;4&t;&t;/* The maximum number of cards to&n;&t;&t;&t;&t;&t;   control or probe for. If you change&n;&t;&t;&t;&t;&t;   this, you must also change the number&n;&t;&t;&t;&t;&t;   of elements in io, irq, and ram to&n;&t;&t;&t;&t;&t;   match. Initialized in init.c */
multiline_comment|/*&n;extern unsigned int io[];&n;extern unsigned char irq[];&n;extern unsigned long ram[];&n;*/
DECL|macro|SIGNATURE
mdefine_line|#define SIGNATURE&t;0x87654321&t;/* Board reset signature */
DECL|macro|SIG_OFFSET
mdefine_line|#define SIG_OFFSET&t;0x1004&t;&t;/* Where to find signature in shared RAM */
DECL|macro|TRACE_OFFSET
mdefine_line|#define TRACE_OFFSET&t;0x1008&t;&t;/* Trace enable word offset in shared RAM */
DECL|macro|BUFFER_OFFSET
mdefine_line|#define BUFFER_OFFSET&t;0x1800&t;&t;/* Beginning of buffers */
multiline_comment|/* I/O Port parameters */
DECL|macro|IOBASE_MIN
mdefine_line|#define IOBASE_MIN&t;0x180&t;&t;/* Lowest I/O port address */
DECL|macro|IOBASE_MAX
mdefine_line|#define IOBASE_MAX&t;0x3C0&t;&t;/* Highest I/O port address */
DECL|macro|IOBASE_OFFSET
mdefine_line|#define IOBASE_OFFSET&t;0x20&t;&t;/* Inter-board I/O port gap used during&n;&t;&t;&t;&t;&t;   probing */
DECL|macro|FIFORD_OFFSET
mdefine_line|#define FIFORD_OFFSET&t;0x0
DECL|macro|FIFOWR_OFFSET
mdefine_line|#define FIFOWR_OFFSET&t;0x400
DECL|macro|FIFOSTAT_OFFSET
mdefine_line|#define FIFOSTAT_OFFSET&t;0x1000
DECL|macro|RESET_OFFSET
mdefine_line|#define RESET_OFFSET&t;0x2800
DECL|macro|PG0_OFFSET
mdefine_line|#define PG0_OFFSET&t;0x3000&t;&t;/* Offset from I/O Base for Page 0 register */
DECL|macro|PG1_OFFSET
mdefine_line|#define PG1_OFFSET&t;0x3400&t;&t;/* Offset from I/O Base for Page 1 register */
DECL|macro|PG2_OFFSET
mdefine_line|#define PG2_OFFSET&t;0x3800&t;&t;/* Offset from I/O Base for Page 2 register */
DECL|macro|PG3_OFFSET
mdefine_line|#define PG3_OFFSET&t;0x3C00&t;&t;/* Offset from I/O Base for Page 3 register */
DECL|macro|FIFO_READ
mdefine_line|#define FIFO_READ&t;0&t;&t;/* FIFO Read register */
DECL|macro|FIFO_WRITE
mdefine_line|#define FIFO_WRITE&t;1&t;&t;/* FIFO Write rgister */
DECL|macro|LO_ADDR_PTR
mdefine_line|#define LO_ADDR_PTR&t;2&t;&t;/* Extended RAM Low Addr Pointer */
DECL|macro|HI_ADDR_PTR
mdefine_line|#define HI_ADDR_PTR&t;3&t;&t;/* Extended RAM High Addr Pointer */
DECL|macro|NOT_USED_1
mdefine_line|#define NOT_USED_1&t;4
DECL|macro|FIFO_STATUS
mdefine_line|#define FIFO_STATUS&t;5&t;&t;/* FIFO Status Register */
DECL|macro|NOT_USED_2
mdefine_line|#define NOT_USED_2&t;6
DECL|macro|MEM_OFFSET
mdefine_line|#define MEM_OFFSET&t;7
DECL|macro|SFT_RESET
mdefine_line|#define SFT_RESET&t;10&t;&t;/* Reset Register */
DECL|macro|EXP_BASE
mdefine_line|#define EXP_BASE&t;11&t;&t;/* Shared RAM Base address */
DECL|macro|EXP_PAGE0
mdefine_line|#define EXP_PAGE0&t;12&t;&t;/* Shared RAM Page0 register */
DECL|macro|EXP_PAGE1
mdefine_line|#define EXP_PAGE1&t;13&t;&t;/* Shared RAM Page1 register */
DECL|macro|EXP_PAGE2
mdefine_line|#define EXP_PAGE2&t;14&t;&t;/* Shared RAM Page2 register */
DECL|macro|EXP_PAGE3
mdefine_line|#define EXP_PAGE3&t;15&t;&t;/* Shared RAM Page3 register */
DECL|macro|IRQ_SELECT
mdefine_line|#define IRQ_SELECT&t;16&t;&t;/* IRQ selection register */
DECL|macro|MAX_IO_REGS
mdefine_line|#define MAX_IO_REGS&t;17&t;&t;/* Total number of I/O ports */
multiline_comment|/* FIFO register values */
DECL|macro|RF_HAS_DATA
mdefine_line|#define RF_HAS_DATA&t;0x01&t;&t;/* fifo has data */
DECL|macro|RF_QUART_FULL
mdefine_line|#define RF_QUART_FULL&t;0x02&t;&t;/* fifo quarter full */
DECL|macro|RF_HALF_FULL
mdefine_line|#define RF_HALF_FULL&t;0x04&t;&t;/* fifo half full */
DECL|macro|RF_NOT_FULL
mdefine_line|#define RF_NOT_FULL&t;0x08&t;&t;/* fifo not full */
DECL|macro|WF_HAS_DATA
mdefine_line|#define WF_HAS_DATA&t;0x10&t;&t;/* fifo has data */
DECL|macro|WF_QUART_FULL
mdefine_line|#define WF_QUART_FULL&t;0x20&t;&t;/* fifo quarter full */
DECL|macro|WF_HALF_FULL
mdefine_line|#define WF_HALF_FULL&t;0x40&t;&t;/* fifo half full */
DECL|macro|WF_NOT_FULL
mdefine_line|#define WF_NOT_FULL&t;0x80&t;&t;/* fifo not full */
multiline_comment|/* Shared RAM parameters */
DECL|macro|SRAM_MIN
mdefine_line|#define SRAM_MIN&t;0xC0000         /* Lowest host shared RAM address */
DECL|macro|SRAM_MAX
mdefine_line|#define SRAM_MAX&t;0xEFFFF         /* Highest host shared RAM address */
DECL|macro|SRAM_PAGESIZE
mdefine_line|#define SRAM_PAGESIZE&t;0x4000&t;&t;/* Size of one RAM page (16K) */
multiline_comment|/* Shared RAM buffer parameters */
DECL|macro|BUFFER_SIZE
mdefine_line|#define BUFFER_SIZE&t;0x800&t;&t;/* The size of a buffer in bytes */
DECL|macro|BUFFER_BASE
mdefine_line|#define BUFFER_BASE&t;BUFFER_OFFSET&t;/* Offset from start of shared RAM&n;&t;&t;&t;&t;&t;   where buffer start */
DECL|macro|BUFFERS_MAX
mdefine_line|#define BUFFERS_MAX&t;16&t;&t;/* Maximum number of send/receive&n;&t;&t;&t;&t;&t;   buffers per channel */
DECL|macro|HDLC_PROTO
mdefine_line|#define HDLC_PROTO&t;0x01&t;&t;/* Frame Format for Layer 2 */
DECL|macro|BRI_BOARD
mdefine_line|#define BRI_BOARD&t;0
DECL|macro|POTS_BOARD
mdefine_line|#define POTS_BOARD&t;1
DECL|macro|PRI_BOARD
mdefine_line|#define PRI_BOARD&t;2
multiline_comment|/*&n; * Specific hardware parameters for the DataCommute/BRI&n; */
DECL|macro|BRI_CHANNELS
mdefine_line|#define BRI_CHANNELS&t;2&t;&t;/* Number of B channels */
DECL|macro|BRI_BASEPG_VAL
mdefine_line|#define BRI_BASEPG_VAL&t;0x98
DECL|macro|BRI_MAGIC
mdefine_line|#define BRI_MAGIC&t;0x60000&t;&t;/* Magic Number */
DECL|macro|BRI_MEMSIZE
mdefine_line|#define BRI_MEMSIZE&t;0x10000&t;&t;/* Ammount of RAM (64K) */
DECL|macro|BRI_PARTNO
mdefine_line|#define BRI_PARTNO&t;&quot;72-029&quot;
DECL|macro|BRI_FEATURES
mdefine_line|#define BRI_FEATURES&t;ISDN_FEATURE_L2_HDLC | ISDN_FEATURE_L3_TRANS;
multiline_comment|/*&n; * Specific hardware parameters for the DataCommute/PRI&n; */
DECL|macro|PRI_CHANNELS
mdefine_line|#define PRI_CHANNELS&t;23&t;&t;/* Number of B channels */
DECL|macro|PRI_BASEPG_VAL
mdefine_line|#define PRI_BASEPG_VAL&t;0x88
DECL|macro|PRI_MAGIC
mdefine_line|#define PRI_MAGIC&t;0x20000&t;&t;/* Magic Number */
DECL|macro|PRI_MEMSIZE
mdefine_line|#define PRI_MEMSIZE&t;0x100000&t;/* Amount of RAM (1M) */
DECL|macro|PRI_PARTNO
mdefine_line|#define PRI_PARTNO&t;&quot;72-030&quot;
DECL|macro|PRI_FEATURES
mdefine_line|#define PRI_FEATURES&t;ISDN_FEATURE_L2_HDLC | ISDN_FEATURE_L3_TRANS;
multiline_comment|/*&n; * Some handy macros&n; */
multiline_comment|/* Return the number of jiffies in a given number of msecs */
DECL|macro|milliseconds
mdefine_line|#define milliseconds(x)&t;(x/(1000/HZ))
multiline_comment|/* Determine if a channel number is valid for the adapter */
DECL|macro|IS_VALID_CHANNEL
mdefine_line|#define IS_VALID_CHANNEL(y,x)&t;((x&gt;0) &amp;&amp; (x &lt;= adapter[y]-&gt;channels))
macro_line|#endif
eof

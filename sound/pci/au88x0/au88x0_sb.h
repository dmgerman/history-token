multiline_comment|/***************************************************************************&n; *            au88x0_sb.h&n; *&n; *  Wed Oct 29 22:10:42 2003&n; *  &n; ****************************************************************************/
macro_line|#ifdef CHIP_AU8820
multiline_comment|/* AU8820 starting @ 64KiB offset */
DECL|macro|SBEMU_BASE
mdefine_line|#define SBEMU_BASE 0x10000
macro_line|#else
multiline_comment|/* AU8810? and AU8830 starting @ 164KiB offset */
DECL|macro|SBEMU_BASE
mdefine_line|#define SBEMU_BASE 0x29000
macro_line|#endif
DECL|macro|FM_A_STATUS
mdefine_line|#define FM_A_STATUS&t;&t;&t;(SBEMU_BASE + 0x00)&t;/* read */
DECL|macro|FM_A_ADDRESS
mdefine_line|#define FM_A_ADDRESS&t;&t;(SBEMU_BASE + 0x00)&t;/* write */
DECL|macro|FM_A_DATA
mdefine_line|#define FM_A_DATA&t;&t;&t;(SBEMU_BASE + 0x04)
DECL|macro|FM_B_STATUS
mdefine_line|#define FM_B_STATUS&t;&t;&t;(SBEMU_BASE + 0x08)
DECL|macro|FM_B_ADDRESS
mdefine_line|#define FM_B_ADDRESS&t;&t;(SBEMU_BASE + 0x08)
DECL|macro|FM_B_DATA
mdefine_line|#define FM_B_DATA&t;&t;&t;(SBEMU_BASE + 0x0C)
DECL|macro|SB_MIXER_ADDR
mdefine_line|#define SB_MIXER_ADDR&t;&t;(SBEMU_BASE + 0x10)
DECL|macro|SB_MIXER_DATA
mdefine_line|#define SB_MIXER_DATA&t;&t;(SBEMU_BASE + 0x14)
DECL|macro|SB_RESET
mdefine_line|#define SB_RESET&t;&t;&t;(SBEMU_BASE + 0x18)
DECL|macro|SB_RESET_ALIAS
mdefine_line|#define SB_RESET_ALIAS&t;&t;(SBEMU_BASE + 0x1C)
DECL|macro|FM_STATUS2
mdefine_line|#define FM_STATUS2&t;&t;&t;(SBEMU_BASE + 0x20)
DECL|macro|FM_ADDR2
mdefine_line|#define FM_ADDR2&t;&t;&t;(SBEMU_BASE + 0x20)
DECL|macro|FM_DATA2
mdefine_line|#define FM_DATA2&t;&t;&t;(SBEMU_BASE + 0x24)
DECL|macro|SB_DSP_READ
mdefine_line|#define SB_DSP_READ&t;&t;&t;(SBEMU_BASE + 0x28)
DECL|macro|SB_DSP_WRITE
mdefine_line|#define SB_DSP_WRITE&t;&t;(SBEMU_BASE + 0x30)
DECL|macro|SB_DSP_WRITE_STATUS
mdefine_line|#define SB_DSP_WRITE_STATUS&t;(SBEMU_BASE + 0x30)&t;/* bit 7 */
DECL|macro|SB_DSP_READ_STATUS
mdefine_line|#define SB_DSP_READ_STATUS&t;(SBEMU_BASE + 0x38)&t;/* bit 7 */
DECL|macro|SB_LACR
mdefine_line|#define SB_LACR&t;&t;&t;&t;(SBEMU_BASE + 0x40)&t;/* ? */
DECL|macro|SB_LADCR
mdefine_line|#define SB_LADCR&t;&t;&t;(SBEMU_BASE + 0x44)&t;/* ? */
DECL|macro|SB_LAMR
mdefine_line|#define SB_LAMR&t;&t;&t;&t;(SBEMU_BASE + 0x48)&t;/* ? */
DECL|macro|SB_LARR
mdefine_line|#define SB_LARR&t;&t;&t;&t;(SBEMU_BASE + 0x4C)&t;/* ? */
DECL|macro|SB_VERSION
mdefine_line|#define SB_VERSION&t;&t;&t;(SBEMU_BASE + 0x50)
DECL|macro|SB_CTRLSTAT
mdefine_line|#define SB_CTRLSTAT&t;&t;&t;(SBEMU_BASE + 0x54)
DECL|macro|SB_TIMERSTAT
mdefine_line|#define SB_TIMERSTAT&t;&t;(SBEMU_BASE + 0x58)
DECL|macro|FM_RAM
mdefine_line|#define FM_RAM&t;&t;&t;&t;(SBEMU_BASE + 0x100)&t;/* 0x40 ULONG */
eof

multiline_comment|/*&n; * sun4prom.h -- interface to sun4 PROM monitor.  We don&squot;t use most of this,&n; *               so most of these are just placeholders.&n; */
macro_line|#ifndef _SUN4PROM_H_
DECL|macro|_SUN4PROM_H_
mdefine_line|#define _SUN4PROM_H_
multiline_comment|/*&n; * Although this looks similar to an romvec for a OpenProm machine, it is &n; * actually closer to what was used in the Sun2 and Sun3.&n; *&n; * V2 entries exist only in version 2 PROMs and later, V3 in version 3 and later.&n; * &n; * Many of the function prototypes are guesses.  Some are certainly wrong.&n; * Use with care.&n; */
r_typedef
r_struct
(brace
DECL|member|initSP
r_char
op_star
id|initSP
suffix:semicolon
multiline_comment|/* Initial system stack ptr */
DECL|member|startmon
r_void
(paren
op_star
id|startmon
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Initial PC for hardware */
DECL|member|diagberr
r_int
op_star
id|diagberr
suffix:semicolon
multiline_comment|/* Bus err handler for diags */
DECL|member|bootParam
r_struct
id|linux_arguments_v0
op_star
op_star
id|bootParam
suffix:semicolon
multiline_comment|/* Info for bootstrapped pgm */
DECL|member|memorysize
r_int
r_int
op_star
id|memorysize
suffix:semicolon
multiline_comment|/* Usable memory in bytes */
DECL|member|getchar
r_int
r_char
(paren
op_star
id|getchar
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Get char from input device */
DECL|member|putchar
r_void
(paren
op_star
id|putchar
)paren
(paren
r_char
)paren
suffix:semicolon
multiline_comment|/* Put char to output device */
DECL|member|mayget
r_int
(paren
op_star
id|mayget
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Maybe get char, or -1 */
DECL|member|mayput
r_int
(paren
op_star
id|mayput
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Maybe put char, or -1 */
DECL|member|echo
r_int
r_char
op_star
id|echo
suffix:semicolon
multiline_comment|/* Should getchar echo? */
DECL|member|insource
r_int
r_char
op_star
id|insource
suffix:semicolon
multiline_comment|/* Input source selector */
DECL|member|outsink
r_int
r_char
op_star
id|outsink
suffix:semicolon
multiline_comment|/* Output sink selector */
DECL|member|getkey
r_int
(paren
op_star
id|getkey
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Get next key if one exists */
DECL|member|initgetkey
r_void
(paren
op_star
id|initgetkey
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Initialize get key */
DECL|member|translation
r_int
r_int
op_star
id|translation
suffix:semicolon
multiline_comment|/* Kbd translation selector */
DECL|member|keybid
r_int
r_char
op_star
id|keybid
suffix:semicolon
multiline_comment|/* Keyboard ID byte */
DECL|member|screen_x
r_int
op_star
id|screen_x
suffix:semicolon
multiline_comment|/* V2: Screen x pos (r/o) */
DECL|member|screen_y
r_int
op_star
id|screen_y
suffix:semicolon
multiline_comment|/* V2: Screen y pos (r/o) */
DECL|member|keybuf
r_struct
id|keybuf
op_star
id|keybuf
suffix:semicolon
multiline_comment|/* Up/down keycode buffer */
DECL|member|monid
r_char
op_star
id|monid
suffix:semicolon
multiline_comment|/* Monitor version ID */
DECL|member|fbwritechar
r_void
(paren
op_star
id|fbwritechar
)paren
(paren
r_char
)paren
suffix:semicolon
multiline_comment|/* Write a character to FB */
DECL|member|fbAddr
r_int
op_star
id|fbAddr
suffix:semicolon
multiline_comment|/* Address of frame buffer */
DECL|member|font
r_char
op_star
op_star
id|font
suffix:semicolon
multiline_comment|/* Font table for FB */
DECL|member|fbwritestr
r_void
(paren
op_star
id|fbwritestr
)paren
(paren
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/* Write string to FB */
DECL|member|reboot
r_void
(paren
op_star
id|reboot
)paren
(paren
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/* e.g. reboot(&quot;sd()vmlinux&quot;) */
DECL|member|linebuf
r_int
r_char
op_star
id|linebuf
suffix:semicolon
multiline_comment|/* The line input buffer */
DECL|member|lineptr
r_int
r_char
op_star
op_star
id|lineptr
suffix:semicolon
multiline_comment|/* Cur pointer into linebuf */
DECL|member|linesize
r_int
op_star
id|linesize
suffix:semicolon
multiline_comment|/* length of line in linebuf */
DECL|member|getline
r_void
(paren
op_star
id|getline
)paren
(paren
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/* Get line from user */
DECL|member|getnextchar
r_int
r_char
(paren
op_star
id|getnextchar
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Get next char from linebuf */
DECL|member|peeknextchar
r_int
r_char
(paren
op_star
id|peeknextchar
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Peek at next char */
DECL|member|fbthere
r_int
op_star
id|fbthere
suffix:semicolon
multiline_comment|/* =1 if frame buffer there */
DECL|member|getnum
r_int
(paren
op_star
id|getnum
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Grab hex num from line */
DECL|member|printf
r_int
(paren
op_star
id|printf
)paren
(paren
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
multiline_comment|/* See prom_printf() instead */
DECL|member|printhex
r_void
(paren
op_star
id|printhex
)paren
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/* Format N digits in hex */
DECL|member|leds
r_int
r_char
op_star
id|leds
suffix:semicolon
multiline_comment|/* RAM copy of LED register */
DECL|member|setLEDs
r_void
(paren
op_star
id|setLEDs
)paren
(paren
r_int
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/* Sets LED&squot;s and RAM copy */
DECL|member|NMIaddr
r_void
(paren
op_star
id|NMIaddr
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/* Addr for level 7 vector */
DECL|member|abortentry
r_void
(paren
op_star
id|abortentry
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Entry for keyboard abort */
DECL|member|nmiclock
r_int
op_star
id|nmiclock
suffix:semicolon
multiline_comment|/* Counts up in msec */
DECL|member|FBtype
r_int
op_star
id|FBtype
suffix:semicolon
multiline_comment|/* Frame buffer type */
DECL|member|romvecversion
r_int
r_int
id|romvecversion
suffix:semicolon
multiline_comment|/* Version number for this romvec */
DECL|member|globram
r_struct
id|globram
op_star
id|globram
suffix:semicolon
multiline_comment|/* monitor global variables ??? */
DECL|member|kbdaddr
r_void
op_star
id|kbdaddr
suffix:semicolon
multiline_comment|/* Addr of keyboard in use */
DECL|member|keyrinit
r_int
op_star
id|keyrinit
suffix:semicolon
multiline_comment|/* ms before kbd repeat */
DECL|member|keyrtick
r_int
r_char
op_star
id|keyrtick
suffix:semicolon
multiline_comment|/* ms between repetitions */
DECL|member|memoryavail
r_int
r_int
op_star
id|memoryavail
suffix:semicolon
multiline_comment|/* V1: Main mem usable size */
DECL|member|resetaddr
r_int
op_star
id|resetaddr
suffix:semicolon
multiline_comment|/* where to jump on a reset */
DECL|member|resetmap
r_int
op_star
id|resetmap
suffix:semicolon
multiline_comment|/* pgmap entry for resetaddr */
DECL|member|exittomon
r_void
(paren
op_star
id|exittomon
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Exit from user program */
DECL|member|memorybitmap
r_int
r_char
op_star
op_star
id|memorybitmap
suffix:semicolon
multiline_comment|/* V1: &amp;{0 or &amp;bits} */
DECL|member|setcxsegmap
r_void
(paren
op_star
id|setcxsegmap
)paren
(paren
r_int
id|ctxt
comma
r_char
op_star
id|va
comma
r_int
id|pmeg
)paren
suffix:semicolon
multiline_comment|/* Set seg in any context */
DECL|member|vector_cmd
r_void
(paren
op_star
op_star
id|vector_cmd
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/* V2: Handler for &squot;v&squot; cmd */
DECL|member|expectedtrapsig
r_int
r_int
op_star
id|expectedtrapsig
suffix:semicolon
multiline_comment|/* V3: Location of the expected trap signal */
DECL|member|trapvectorbasetable
r_int
r_int
op_star
id|trapvectorbasetable
suffix:semicolon
multiline_comment|/* V3: Address of the trap vector table */
DECL|member|unused1
r_int
id|unused1
suffix:semicolon
DECL|member|unused2
r_int
id|unused2
suffix:semicolon
DECL|member|unused3
r_int
id|unused3
suffix:semicolon
DECL|member|unused4
r_int
id|unused4
suffix:semicolon
DECL|typedef|linux_sun4_romvec
)brace
id|linux_sun4_romvec
suffix:semicolon
r_extern
id|linux_sun4_romvec
op_star
id|sun4_romvec
suffix:semicolon
macro_line|#endif /* _SUN4PROM_H_ */
eof

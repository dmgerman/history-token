multiline_comment|/*&n; *  dialog.h -- common declarations for all dialog modules&n; *&n; *  AUTHOR: Savio Lam (lam836@cs.cuhk.hk)&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version 2&n; *  of the License, or (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;ctype.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include CURSES_LOC
multiline_comment|/*&n; * Colors in ncurses 1.9.9e do not work properly since foreground and&n; * background colors are OR&squot;d rather than separately masked.  This version&n; * of dialog was hacked to work with ncurses 1.9.9e, making it incompatible&n; * with standard curses.  The simplest fix (to make this work with standard&n; * curses) uses the wbkgdset() function, not used in the original hack.&n; * Turn it off if we&squot;re building with 1.9.9e, since it just confuses things.&n; */
macro_line|#if defined(NCURSES_VERSION) &amp;&amp; defined(_NEED_WRAP) &amp;&amp; !defined(GCC_PRINTFLIKE)
DECL|macro|OLD_NCURSES
mdefine_line|#define OLD_NCURSES 1
DECL|macro|wbkgdset
macro_line|#undef  wbkgdset
DECL|macro|wbkgdset
mdefine_line|#define wbkgdset(w,p) /*nothing*/
macro_line|#else
DECL|macro|OLD_NCURSES
mdefine_line|#define OLD_NCURSES 0
macro_line|#endif
DECL|macro|TR
mdefine_line|#define TR(params) _tracef params
DECL|macro|ESC
mdefine_line|#define ESC 27
DECL|macro|TAB
mdefine_line|#define TAB 9
DECL|macro|MAX_LEN
mdefine_line|#define MAX_LEN 2048
DECL|macro|BUF_SIZE
mdefine_line|#define BUF_SIZE (10*1024)
DECL|macro|MIN
mdefine_line|#define MIN(x,y) (x &lt; y ? x : y)
DECL|macro|MAX
mdefine_line|#define MAX(x,y) (x &gt; y ? x : y)
macro_line|#ifndef ACS_ULCORNER
DECL|macro|ACS_ULCORNER
mdefine_line|#define ACS_ULCORNER &squot;+&squot;
macro_line|#endif
macro_line|#ifndef ACS_LLCORNER
DECL|macro|ACS_LLCORNER
mdefine_line|#define ACS_LLCORNER &squot;+&squot;
macro_line|#endif
macro_line|#ifndef ACS_URCORNER
DECL|macro|ACS_URCORNER
mdefine_line|#define ACS_URCORNER &squot;+&squot;
macro_line|#endif
macro_line|#ifndef ACS_LRCORNER
DECL|macro|ACS_LRCORNER
mdefine_line|#define ACS_LRCORNER &squot;+&squot;
macro_line|#endif
macro_line|#ifndef ACS_HLINE
DECL|macro|ACS_HLINE
mdefine_line|#define ACS_HLINE &squot;-&squot;
macro_line|#endif
macro_line|#ifndef ACS_VLINE
DECL|macro|ACS_VLINE
mdefine_line|#define ACS_VLINE &squot;|&squot;
macro_line|#endif
macro_line|#ifndef ACS_LTEE
DECL|macro|ACS_LTEE
mdefine_line|#define ACS_LTEE &squot;+&squot;
macro_line|#endif
macro_line|#ifndef ACS_RTEE
DECL|macro|ACS_RTEE
mdefine_line|#define ACS_RTEE &squot;+&squot;
macro_line|#endif
macro_line|#ifndef ACS_UARROW
DECL|macro|ACS_UARROW
mdefine_line|#define ACS_UARROW &squot;^&squot;
macro_line|#endif
macro_line|#ifndef ACS_DARROW
DECL|macro|ACS_DARROW
mdefine_line|#define ACS_DARROW &squot;v&squot;
macro_line|#endif
multiline_comment|/* &n; * Attribute names&n; */
DECL|macro|screen_attr
mdefine_line|#define screen_attr                   attributes[0]
DECL|macro|shadow_attr
mdefine_line|#define shadow_attr                   attributes[1]
DECL|macro|dialog_attr
mdefine_line|#define dialog_attr                   attributes[2]
DECL|macro|title_attr
mdefine_line|#define title_attr                    attributes[3]
DECL|macro|border_attr
mdefine_line|#define border_attr                   attributes[4]
DECL|macro|button_active_attr
mdefine_line|#define button_active_attr            attributes[5]
DECL|macro|button_inactive_attr
mdefine_line|#define button_inactive_attr          attributes[6]
DECL|macro|button_key_active_attr
mdefine_line|#define button_key_active_attr        attributes[7]
DECL|macro|button_key_inactive_attr
mdefine_line|#define button_key_inactive_attr      attributes[8]
DECL|macro|button_label_active_attr
mdefine_line|#define button_label_active_attr      attributes[9]
DECL|macro|button_label_inactive_attr
mdefine_line|#define button_label_inactive_attr    attributes[10]
DECL|macro|inputbox_attr
mdefine_line|#define inputbox_attr                 attributes[11]
DECL|macro|inputbox_border_attr
mdefine_line|#define inputbox_border_attr          attributes[12]
DECL|macro|searchbox_attr
mdefine_line|#define searchbox_attr                attributes[13]
DECL|macro|searchbox_title_attr
mdefine_line|#define searchbox_title_attr          attributes[14]
DECL|macro|searchbox_border_attr
mdefine_line|#define searchbox_border_attr         attributes[15]
DECL|macro|position_indicator_attr
mdefine_line|#define position_indicator_attr       attributes[16]
DECL|macro|menubox_attr
mdefine_line|#define menubox_attr                  attributes[17]
DECL|macro|menubox_border_attr
mdefine_line|#define menubox_border_attr           attributes[18]
DECL|macro|item_attr
mdefine_line|#define item_attr                     attributes[19]
DECL|macro|item_selected_attr
mdefine_line|#define item_selected_attr            attributes[20]
DECL|macro|tag_attr
mdefine_line|#define tag_attr                      attributes[21]
DECL|macro|tag_selected_attr
mdefine_line|#define tag_selected_attr             attributes[22]
DECL|macro|tag_key_attr
mdefine_line|#define tag_key_attr                  attributes[23]
DECL|macro|tag_key_selected_attr
mdefine_line|#define tag_key_selected_attr         attributes[24]
DECL|macro|check_attr
mdefine_line|#define check_attr                    attributes[25]
DECL|macro|check_selected_attr
mdefine_line|#define check_selected_attr           attributes[26]
DECL|macro|uarrow_attr
mdefine_line|#define uarrow_attr                   attributes[27]
DECL|macro|darrow_attr
mdefine_line|#define darrow_attr                   attributes[28]
multiline_comment|/* number of attributes */
DECL|macro|ATTRIBUTE_COUNT
mdefine_line|#define ATTRIBUTE_COUNT               29
multiline_comment|/*&n; * Global variables&n; */
r_extern
r_bool
id|use_colors
suffix:semicolon
r_extern
r_bool
id|use_shadow
suffix:semicolon
r_extern
id|chtype
id|attributes
(braket
)braket
suffix:semicolon
r_extern
r_const
r_char
op_star
id|backtitle
suffix:semicolon
multiline_comment|/*&n; * Function prototypes&n; */
r_extern
r_void
id|create_rc
(paren
r_const
r_char
op_star
id|filename
)paren
suffix:semicolon
r_extern
r_int
id|parse_rc
(paren
r_void
)paren
suffix:semicolon
r_void
id|init_dialog
(paren
r_void
)paren
suffix:semicolon
r_void
id|end_dialog
(paren
r_void
)paren
suffix:semicolon
r_void
id|attr_clear
(paren
id|WINDOW
op_star
id|win
comma
r_int
id|height
comma
r_int
id|width
comma
id|chtype
id|attr
)paren
suffix:semicolon
r_void
id|dialog_clear
(paren
r_void
)paren
suffix:semicolon
r_void
id|color_setup
(paren
r_void
)paren
suffix:semicolon
r_void
id|print_autowrap
(paren
id|WINDOW
op_star
id|win
comma
r_const
r_char
op_star
id|prompt
comma
r_int
id|width
comma
r_int
id|y
comma
r_int
id|x
)paren
suffix:semicolon
r_void
id|print_button
(paren
id|WINDOW
op_star
id|win
comma
r_const
r_char
op_star
id|label
comma
r_int
id|y
comma
r_int
id|x
comma
r_int
id|selected
)paren
suffix:semicolon
r_void
id|draw_box
(paren
id|WINDOW
op_star
id|win
comma
r_int
id|y
comma
r_int
id|x
comma
r_int
id|height
comma
r_int
id|width
comma
id|chtype
id|box
comma
id|chtype
id|border
)paren
suffix:semicolon
r_void
id|draw_shadow
(paren
id|WINDOW
op_star
id|win
comma
r_int
id|y
comma
r_int
id|x
comma
r_int
id|height
comma
r_int
id|width
)paren
suffix:semicolon
r_int
id|first_alpha
(paren
r_const
r_char
op_star
id|string
comma
r_const
r_char
op_star
id|exempt
)paren
suffix:semicolon
r_int
id|dialog_yesno
(paren
r_const
r_char
op_star
id|title
comma
r_const
r_char
op_star
id|prompt
comma
r_int
id|height
comma
r_int
id|width
)paren
suffix:semicolon
r_int
id|dialog_msgbox
(paren
r_const
r_char
op_star
id|title
comma
r_const
r_char
op_star
id|prompt
comma
r_int
id|height
comma
r_int
id|width
comma
r_int
id|pause
)paren
suffix:semicolon
r_int
id|dialog_textbox
(paren
r_const
r_char
op_star
id|title
comma
r_const
r_char
op_star
id|file
comma
r_int
id|height
comma
r_int
id|width
)paren
suffix:semicolon
r_int
id|dialog_menu
(paren
r_const
r_char
op_star
id|title
comma
r_const
r_char
op_star
id|prompt
comma
r_int
id|height
comma
r_int
id|width
comma
r_int
id|menu_height
comma
r_const
r_char
op_star
id|choice
comma
r_int
id|item_no
comma
r_const
r_char
op_star
r_const
op_star
id|items
)paren
suffix:semicolon
r_int
id|dialog_checklist
(paren
r_const
r_char
op_star
id|title
comma
r_const
r_char
op_star
id|prompt
comma
r_int
id|height
comma
r_int
id|width
comma
r_int
id|list_height
comma
r_int
id|item_no
comma
r_const
r_char
op_star
r_const
op_star
id|items
comma
r_int
id|flag
)paren
suffix:semicolon
r_extern
r_int
r_char
id|dialog_input_result
(braket
)braket
suffix:semicolon
r_int
id|dialog_inputbox
(paren
r_const
r_char
op_star
id|title
comma
r_const
r_char
op_star
id|prompt
comma
r_int
id|height
comma
r_int
id|width
comma
r_const
r_char
op_star
id|init
)paren
suffix:semicolon
multiline_comment|/*&n; * This is the base for fictitious keys, which activate&n; * the buttons.&n; *&n; * Mouse-generated keys are the following:&n; *   -- the first 32 are used as numbers, in addition to &squot;0&squot;-&squot;9&squot;&n; *   -- the lowercase are used to signal mouse-enter events (M_EVENT + &squot;o&squot;)&n; *   -- uppercase chars are used to invoke the button (M_EVENT + &squot;O&squot;)&n; */
DECL|macro|M_EVENT
mdefine_line|#define M_EVENT (KEY_MAX+1)
multiline_comment|/*&n; * The `flag&squot; parameter in checklist is used to select between&n; * radiolist and checklist&n; */
DECL|macro|FLAG_CHECK
mdefine_line|#define FLAG_CHECK 1
DECL|macro|FLAG_RADIO
mdefine_line|#define FLAG_RADIO 0
eof

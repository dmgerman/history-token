multiline_comment|/*&n; *  checklist.c -- implements the checklist box&n; *&n; *  ORIGINAL AUTHOR: Savio Lam (lam836@cs.cuhk.hk)&n; *     Stuart Herbert - S.Herbert@sheffield.ac.uk: radiolist extension&n; *     Alessandro Rubini - rubini@ipvvis.unipv.it: merged the two&n; *  MODIFIED FOR LINUX KERNEL CONFIG BY: William Roadcap (roadcap@cfw.com)&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version 2&n; *  of the License, or (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &quot;dialog.h&quot;
DECL|variable|list_width
DECL|variable|check_x
DECL|variable|item_x
DECL|variable|checkflag
r_static
r_int
id|list_width
comma
id|check_x
comma
id|item_x
comma
id|checkflag
suffix:semicolon
multiline_comment|/*&n; * Print list item&n; */
r_static
r_void
DECL|function|print_item
id|print_item
(paren
id|WINDOW
op_star
id|win
comma
r_const
r_char
op_star
id|item
comma
r_int
id|status
comma
r_int
id|choice
comma
r_int
id|selected
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Clear &squot;residue&squot; of last item */
id|wattrset
(paren
id|win
comma
id|menubox_attr
)paren
suffix:semicolon
id|wmove
(paren
id|win
comma
id|choice
comma
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|list_width
suffix:semicolon
id|i
op_increment
)paren
id|waddch
(paren
id|win
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
id|wmove
(paren
id|win
comma
id|choice
comma
id|check_x
)paren
suffix:semicolon
id|wattrset
(paren
id|win
comma
id|selected
ques
c_cond
id|check_selected_attr
suffix:colon
id|check_attr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|checkflag
op_eq
id|FLAG_CHECK
)paren
id|wprintw
(paren
id|win
comma
l_string|&quot;[%c]&quot;
comma
id|status
ques
c_cond
l_char|&squot;X&squot;
suffix:colon
l_char|&squot; &squot;
)paren
suffix:semicolon
r_else
id|wprintw
(paren
id|win
comma
l_string|&quot;(%c)&quot;
comma
id|status
ques
c_cond
l_char|&squot;X&squot;
suffix:colon
l_char|&squot; &squot;
)paren
suffix:semicolon
id|wattrset
(paren
id|win
comma
id|selected
ques
c_cond
id|tag_selected_attr
suffix:colon
id|tag_attr
)paren
suffix:semicolon
id|mvwaddch
c_func
(paren
id|win
comma
id|choice
comma
id|item_x
comma
id|item
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|wattrset
(paren
id|win
comma
id|selected
ques
c_cond
id|item_selected_attr
suffix:colon
id|item_attr
)paren
suffix:semicolon
id|waddstr
(paren
id|win
comma
(paren
r_char
op_star
)paren
id|item
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|selected
)paren
(brace
id|wmove
(paren
id|win
comma
id|choice
comma
id|check_x
op_plus
l_int|1
)paren
suffix:semicolon
id|wrefresh
(paren
id|win
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Print the scroll indicators.&n; */
r_static
r_void
DECL|function|print_arrows
id|print_arrows
(paren
id|WINDOW
op_star
id|win
comma
r_int
id|choice
comma
r_int
id|item_no
comma
r_int
id|scroll
comma
r_int
id|y
comma
r_int
id|x
comma
r_int
id|height
)paren
(brace
id|wmove
c_func
(paren
id|win
comma
id|y
comma
id|x
)paren
suffix:semicolon
r_if
c_cond
(paren
id|scroll
OG
l_int|0
)paren
(brace
id|wattrset
(paren
id|win
comma
id|uarrow_attr
)paren
suffix:semicolon
id|waddch
(paren
id|win
comma
id|ACS_UARROW
)paren
suffix:semicolon
id|waddstr
(paren
id|win
comma
l_string|&quot;(-)&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|wattrset
(paren
id|win
comma
id|menubox_attr
)paren
suffix:semicolon
id|waddch
(paren
id|win
comma
id|ACS_HLINE
)paren
suffix:semicolon
id|waddch
(paren
id|win
comma
id|ACS_HLINE
)paren
suffix:semicolon
id|waddch
(paren
id|win
comma
id|ACS_HLINE
)paren
suffix:semicolon
id|waddch
(paren
id|win
comma
id|ACS_HLINE
)paren
suffix:semicolon
)brace
id|y
op_assign
id|y
op_plus
id|height
op_plus
l_int|1
suffix:semicolon
id|wmove
c_func
(paren
id|win
comma
id|y
comma
id|x
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|height
OL
id|item_no
)paren
op_logical_and
(paren
id|scroll
op_plus
id|choice
OL
id|item_no
op_minus
l_int|1
)paren
)paren
(brace
id|wattrset
(paren
id|win
comma
id|darrow_attr
)paren
suffix:semicolon
id|waddch
(paren
id|win
comma
id|ACS_DARROW
)paren
suffix:semicolon
id|waddstr
(paren
id|win
comma
l_string|&quot;(+)&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|wattrset
(paren
id|win
comma
id|menubox_border_attr
)paren
suffix:semicolon
id|waddch
(paren
id|win
comma
id|ACS_HLINE
)paren
suffix:semicolon
id|waddch
(paren
id|win
comma
id|ACS_HLINE
)paren
suffix:semicolon
id|waddch
(paren
id|win
comma
id|ACS_HLINE
)paren
suffix:semicolon
id|waddch
(paren
id|win
comma
id|ACS_HLINE
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *  Display the termination buttons&n; */
r_static
r_void
DECL|function|print_buttons
id|print_buttons
c_func
(paren
id|WINDOW
op_star
id|dialog
comma
r_int
id|height
comma
r_int
id|width
comma
r_int
id|selected
)paren
(brace
r_int
id|x
op_assign
id|width
op_div
l_int|2
op_minus
l_int|11
suffix:semicolon
r_int
id|y
op_assign
id|height
op_minus
l_int|2
suffix:semicolon
id|print_button
(paren
id|dialog
comma
l_string|&quot;Select&quot;
comma
id|y
comma
id|x
comma
id|selected
op_eq
l_int|0
)paren
suffix:semicolon
id|print_button
(paren
id|dialog
comma
l_string|&quot; Help &quot;
comma
id|y
comma
id|x
op_plus
l_int|14
comma
id|selected
op_eq
l_int|1
)paren
suffix:semicolon
id|wmove
c_func
(paren
id|dialog
comma
id|y
comma
id|x
op_plus
l_int|1
op_plus
l_int|14
op_star
id|selected
)paren
suffix:semicolon
id|wrefresh
(paren
id|dialog
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Display a dialog box with a list of options that can be turned on or off&n; * The `flag&squot; parameter is used to select between radiolist and checklist.&n; */
r_int
DECL|function|dialog_checklist
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
(brace
r_int
id|i
comma
id|x
comma
id|y
comma
id|box_x
comma
id|box_y
suffix:semicolon
r_int
id|key
op_assign
l_int|0
comma
id|button
op_assign
l_int|0
comma
id|choice
op_assign
l_int|0
comma
id|scroll
op_assign
l_int|0
comma
id|max_choice
comma
op_star
id|status
suffix:semicolon
id|WINDOW
op_star
id|dialog
comma
op_star
id|list
suffix:semicolon
id|checkflag
op_assign
id|flag
suffix:semicolon
multiline_comment|/* Allocate space for storing item on/off status */
r_if
c_cond
(paren
(paren
id|status
op_assign
id|malloc
(paren
r_sizeof
(paren
r_int
)paren
op_star
id|item_no
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|endwin
(paren
)paren
suffix:semicolon
id|fprintf
(paren
id|stderr
comma
l_string|&quot;&bslash;nCan&squot;t allocate memory in dialog_checklist().&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Initializes status */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|item_no
suffix:semicolon
id|i
op_increment
)paren
(brace
id|status
(braket
id|i
)braket
op_assign
op_logical_neg
id|strcasecmp
(paren
id|items
(braket
id|i
op_star
l_int|3
op_plus
l_int|2
)braket
comma
l_string|&quot;on&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|choice
op_logical_and
id|status
(braket
id|i
)braket
)paren
op_logical_or
op_logical_neg
id|strcasecmp
(paren
id|items
(braket
id|i
op_star
l_int|3
op_plus
l_int|2
)braket
comma
l_string|&quot;selected&quot;
)paren
)paren
id|choice
op_assign
id|i
op_plus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|choice
)paren
id|choice
op_decrement
suffix:semicolon
id|max_choice
op_assign
id|MIN
(paren
id|list_height
comma
id|item_no
)paren
suffix:semicolon
multiline_comment|/* center dialog box on screen */
id|x
op_assign
(paren
id|COLS
op_minus
id|width
)paren
op_div
l_int|2
suffix:semicolon
id|y
op_assign
(paren
id|LINES
op_minus
id|height
)paren
op_div
l_int|2
suffix:semicolon
id|draw_shadow
(paren
id|stdscr
comma
id|y
comma
id|x
comma
id|height
comma
id|width
)paren
suffix:semicolon
id|dialog
op_assign
id|newwin
(paren
id|height
comma
id|width
comma
id|y
comma
id|x
)paren
suffix:semicolon
id|keypad
(paren
id|dialog
comma
id|TRUE
)paren
suffix:semicolon
id|draw_box
(paren
id|dialog
comma
l_int|0
comma
l_int|0
comma
id|height
comma
id|width
comma
id|dialog_attr
comma
id|border_attr
)paren
suffix:semicolon
id|wattrset
(paren
id|dialog
comma
id|border_attr
)paren
suffix:semicolon
id|mvwaddch
(paren
id|dialog
comma
id|height
op_minus
l_int|3
comma
l_int|0
comma
id|ACS_LTEE
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|width
op_minus
l_int|2
suffix:semicolon
id|i
op_increment
)paren
id|waddch
(paren
id|dialog
comma
id|ACS_HLINE
)paren
suffix:semicolon
id|wattrset
(paren
id|dialog
comma
id|dialog_attr
)paren
suffix:semicolon
id|waddch
(paren
id|dialog
comma
id|ACS_RTEE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|title
op_ne
l_int|NULL
op_logical_and
id|strlen
c_func
(paren
id|title
)paren
op_ge
id|width
op_minus
l_int|2
)paren
(brace
multiline_comment|/* truncate long title -- mec */
r_char
op_star
id|title2
op_assign
id|malloc
c_func
(paren
id|width
op_minus
l_int|2
op_plus
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|title2
comma
id|title
comma
id|width
op_minus
l_int|2
)paren
suffix:semicolon
id|title2
(braket
id|width
op_minus
l_int|2
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|title
op_assign
id|title2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|title
op_ne
l_int|NULL
)paren
(brace
id|wattrset
(paren
id|dialog
comma
id|title_attr
)paren
suffix:semicolon
id|mvwaddch
(paren
id|dialog
comma
l_int|0
comma
(paren
id|width
op_minus
id|strlen
c_func
(paren
id|title
)paren
)paren
op_div
l_int|2
op_minus
l_int|1
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
id|waddstr
(paren
id|dialog
comma
(paren
r_char
op_star
)paren
id|title
)paren
suffix:semicolon
id|waddch
(paren
id|dialog
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
)brace
id|wattrset
(paren
id|dialog
comma
id|dialog_attr
)paren
suffix:semicolon
id|print_autowrap
(paren
id|dialog
comma
id|prompt
comma
id|width
op_minus
l_int|2
comma
l_int|1
comma
l_int|3
)paren
suffix:semicolon
id|list_width
op_assign
id|width
op_minus
l_int|6
suffix:semicolon
id|box_y
op_assign
id|height
op_minus
id|list_height
op_minus
l_int|5
suffix:semicolon
id|box_x
op_assign
(paren
id|width
op_minus
id|list_width
)paren
op_div
l_int|2
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* create new window for the list */
id|list
op_assign
id|subwin
(paren
id|dialog
comma
id|list_height
comma
id|list_width
comma
id|y
op_plus
id|box_y
op_plus
l_int|1
comma
id|x
op_plus
id|box_x
op_plus
l_int|1
)paren
suffix:semicolon
id|keypad
(paren
id|list
comma
id|TRUE
)paren
suffix:semicolon
multiline_comment|/* draw a box around the list items */
id|draw_box
(paren
id|dialog
comma
id|box_y
comma
id|box_x
comma
id|list_height
op_plus
l_int|2
comma
id|list_width
op_plus
l_int|2
comma
id|menubox_border_attr
comma
id|menubox_attr
)paren
suffix:semicolon
multiline_comment|/* Find length of longest item in order to center checklist */
id|check_x
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|item_no
suffix:semicolon
id|i
op_increment
)paren
id|check_x
op_assign
id|MAX
(paren
id|check_x
comma
op_plus
id|strlen
(paren
id|items
(braket
id|i
op_star
l_int|3
op_plus
l_int|1
)braket
)paren
op_plus
l_int|4
)paren
suffix:semicolon
id|check_x
op_assign
(paren
id|list_width
op_minus
id|check_x
)paren
op_div
l_int|2
suffix:semicolon
id|item_x
op_assign
id|check_x
op_plus
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|choice
op_ge
id|list_height
)paren
(brace
id|scroll
op_assign
id|choice
op_minus
id|list_height
op_plus
l_int|1
suffix:semicolon
id|choice
op_sub_assign
id|scroll
suffix:semicolon
)brace
multiline_comment|/* Print the list */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|max_choice
suffix:semicolon
id|i
op_increment
)paren
(brace
id|print_item
(paren
id|list
comma
id|items
(braket
(paren
id|scroll
op_plus
id|i
)paren
op_star
l_int|3
op_plus
l_int|1
)braket
comma
id|status
(braket
id|i
op_plus
id|scroll
)braket
comma
id|i
comma
id|i
op_eq
id|choice
)paren
suffix:semicolon
)brace
id|print_arrows
c_func
(paren
id|dialog
comma
id|choice
comma
id|item_no
comma
id|scroll
comma
id|box_y
comma
id|box_x
op_plus
id|check_x
op_plus
l_int|5
comma
id|list_height
)paren
suffix:semicolon
id|print_buttons
c_func
(paren
id|dialog
comma
id|height
comma
id|width
comma
l_int|0
)paren
suffix:semicolon
id|wnoutrefresh
(paren
id|list
)paren
suffix:semicolon
id|wnoutrefresh
(paren
id|dialog
)paren
suffix:semicolon
id|doupdate
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|key
op_ne
id|ESC
)paren
(brace
id|key
op_assign
id|wgetch
(paren
id|dialog
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|max_choice
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|toupper
c_func
(paren
id|key
)paren
op_eq
id|toupper
c_func
(paren
id|items
(braket
(paren
id|scroll
op_plus
id|i
)paren
op_star
l_int|3
op_plus
l_int|1
)braket
(braket
l_int|0
)braket
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|max_choice
op_logical_or
id|key
op_eq
id|KEY_UP
op_logical_or
id|key
op_eq
id|KEY_DOWN
op_logical_or
id|key
op_eq
l_char|&squot;+&squot;
op_logical_or
id|key
op_eq
l_char|&squot;-&squot;
)paren
(brace
r_if
c_cond
(paren
id|key
op_eq
id|KEY_UP
op_logical_or
id|key
op_eq
l_char|&squot;-&squot;
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|choice
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|scroll
)paren
r_continue
suffix:semicolon
multiline_comment|/* Scroll list down */
r_if
c_cond
(paren
id|list_height
OG
l_int|1
)paren
(brace
multiline_comment|/* De-highlight current first item */
id|print_item
(paren
id|list
comma
id|items
(braket
id|scroll
op_star
l_int|3
op_plus
l_int|1
)braket
comma
id|status
(braket
id|scroll
)braket
comma
l_int|0
comma
id|FALSE
)paren
suffix:semicolon
id|scrollok
(paren
id|list
comma
id|TRUE
)paren
suffix:semicolon
id|wscrl
(paren
id|list
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|scrollok
(paren
id|list
comma
id|FALSE
)paren
suffix:semicolon
)brace
id|scroll
op_decrement
suffix:semicolon
id|print_item
(paren
id|list
comma
id|items
(braket
id|scroll
op_star
l_int|3
op_plus
l_int|1
)braket
comma
id|status
(braket
id|scroll
)braket
comma
l_int|0
comma
id|TRUE
)paren
suffix:semicolon
id|wnoutrefresh
(paren
id|list
)paren
suffix:semicolon
id|print_arrows
c_func
(paren
id|dialog
comma
id|choice
comma
id|item_no
comma
id|scroll
comma
id|box_y
comma
id|box_x
op_plus
id|check_x
op_plus
l_int|5
comma
id|list_height
)paren
suffix:semicolon
id|wrefresh
(paren
id|dialog
)paren
suffix:semicolon
r_continue
suffix:semicolon
multiline_comment|/* wait for another key press */
)brace
r_else
id|i
op_assign
id|choice
op_minus
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|key
op_eq
id|KEY_DOWN
op_logical_or
id|key
op_eq
l_char|&squot;+&squot;
)paren
(brace
r_if
c_cond
(paren
id|choice
op_eq
id|max_choice
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|scroll
op_plus
id|choice
op_ge
id|item_no
op_minus
l_int|1
)paren
r_continue
suffix:semicolon
multiline_comment|/* Scroll list up */
r_if
c_cond
(paren
id|list_height
OG
l_int|1
)paren
(brace
multiline_comment|/* De-highlight current last item before scrolling up */
id|print_item
(paren
id|list
comma
id|items
(braket
(paren
id|scroll
op_plus
id|max_choice
op_minus
l_int|1
)paren
op_star
l_int|3
op_plus
l_int|1
)braket
comma
id|status
(braket
id|scroll
op_plus
id|max_choice
op_minus
l_int|1
)braket
comma
id|max_choice
op_minus
l_int|1
comma
id|FALSE
)paren
suffix:semicolon
id|scrollok
(paren
id|list
comma
id|TRUE
)paren
suffix:semicolon
id|wscrl
(paren
id|list
comma
l_int|1
)paren
suffix:semicolon
id|scrollok
(paren
id|list
comma
id|FALSE
)paren
suffix:semicolon
)brace
id|scroll
op_increment
suffix:semicolon
id|print_item
(paren
id|list
comma
id|items
(braket
(paren
id|scroll
op_plus
id|max_choice
op_minus
l_int|1
)paren
op_star
l_int|3
op_plus
l_int|1
)braket
comma
id|status
(braket
id|scroll
op_plus
id|max_choice
op_minus
l_int|1
)braket
comma
id|max_choice
op_minus
l_int|1
comma
id|TRUE
)paren
suffix:semicolon
id|wnoutrefresh
(paren
id|list
)paren
suffix:semicolon
id|print_arrows
c_func
(paren
id|dialog
comma
id|choice
comma
id|item_no
comma
id|scroll
comma
id|box_y
comma
id|box_x
op_plus
id|check_x
op_plus
l_int|5
comma
id|list_height
)paren
suffix:semicolon
id|wrefresh
(paren
id|dialog
)paren
suffix:semicolon
r_continue
suffix:semicolon
multiline_comment|/* wait for another key press */
)brace
r_else
id|i
op_assign
id|choice
op_plus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_ne
id|choice
)paren
(brace
multiline_comment|/* De-highlight current item */
id|print_item
(paren
id|list
comma
id|items
(braket
(paren
id|scroll
op_plus
id|choice
)paren
op_star
l_int|3
op_plus
l_int|1
)braket
comma
id|status
(braket
id|scroll
op_plus
id|choice
)braket
comma
id|choice
comma
id|FALSE
)paren
suffix:semicolon
multiline_comment|/* Highlight new item */
id|choice
op_assign
id|i
suffix:semicolon
id|print_item
(paren
id|list
comma
id|items
(braket
(paren
id|scroll
op_plus
id|choice
)paren
op_star
l_int|3
op_plus
l_int|1
)braket
comma
id|status
(braket
id|scroll
op_plus
id|choice
)braket
comma
id|choice
comma
id|TRUE
)paren
suffix:semicolon
id|wnoutrefresh
(paren
id|list
)paren
suffix:semicolon
id|wrefresh
(paren
id|dialog
)paren
suffix:semicolon
)brace
r_continue
suffix:semicolon
multiline_comment|/* wait for another key press */
)brace
r_switch
c_cond
(paren
id|key
)paren
(brace
r_case
l_char|&squot;H&squot;
suffix:colon
r_case
l_char|&squot;h&squot;
suffix:colon
r_case
l_char|&squot;?&squot;
suffix:colon
id|fprintf
(paren
id|stderr
comma
l_string|&quot;%s&quot;
comma
id|items
(braket
(paren
id|scroll
op_plus
id|choice
)paren
op_star
l_int|3
)braket
)paren
suffix:semicolon
id|delwin
(paren
id|dialog
)paren
suffix:semicolon
id|free
(paren
id|status
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
r_case
id|TAB
suffix:colon
r_case
id|KEY_LEFT
suffix:colon
r_case
id|KEY_RIGHT
suffix:colon
id|button
op_assign
(paren
(paren
id|key
op_eq
id|KEY_LEFT
ques
c_cond
op_decrement
id|button
suffix:colon
op_increment
id|button
)paren
OL
l_int|0
)paren
ques
c_cond
l_int|1
suffix:colon
(paren
id|button
OG
l_int|1
ques
c_cond
l_int|0
suffix:colon
id|button
)paren
suffix:semicolon
id|print_buttons
c_func
(paren
id|dialog
comma
id|height
comma
id|width
comma
id|button
)paren
suffix:semicolon
id|wrefresh
(paren
id|dialog
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;S&squot;
suffix:colon
r_case
l_char|&squot;s&squot;
suffix:colon
r_case
l_char|&squot; &squot;
suffix:colon
r_case
l_char|&squot;&bslash;n&squot;
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|button
)paren
(brace
r_if
c_cond
(paren
id|flag
op_eq
id|FLAG_CHECK
)paren
(brace
id|status
(braket
id|scroll
op_plus
id|choice
)braket
op_assign
op_logical_neg
id|status
(braket
id|scroll
op_plus
id|choice
)braket
suffix:semicolon
id|wmove
(paren
id|list
comma
id|choice
comma
id|check_x
)paren
suffix:semicolon
id|wattrset
(paren
id|list
comma
id|check_selected_attr
)paren
suffix:semicolon
id|wprintw
(paren
id|list
comma
l_string|&quot;[%c]&quot;
comma
id|status
(braket
id|scroll
op_plus
id|choice
)braket
ques
c_cond
l_char|&squot;X&squot;
suffix:colon
l_char|&squot; &squot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|status
(braket
id|scroll
op_plus
id|choice
)braket
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|item_no
suffix:semicolon
id|i
op_increment
)paren
id|status
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|status
(braket
id|scroll
op_plus
id|choice
)braket
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|max_choice
suffix:semicolon
id|i
op_increment
)paren
id|print_item
(paren
id|list
comma
id|items
(braket
(paren
id|scroll
op_plus
id|i
)paren
op_star
l_int|3
op_plus
l_int|1
)braket
comma
id|status
(braket
id|scroll
op_plus
id|i
)braket
comma
id|i
comma
id|i
op_eq
id|choice
)paren
suffix:semicolon
)brace
)brace
id|wnoutrefresh
(paren
id|list
)paren
suffix:semicolon
id|wrefresh
(paren
id|dialog
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|item_no
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|status
(braket
id|i
)braket
)paren
(brace
r_if
c_cond
(paren
id|flag
op_eq
id|FLAG_CHECK
)paren
(brace
id|fprintf
(paren
id|stderr
comma
l_string|&quot;&bslash;&quot;%s&bslash;&quot; &quot;
comma
id|items
(braket
id|i
op_star
l_int|3
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
id|fprintf
(paren
id|stderr
comma
l_string|&quot;%s&quot;
comma
id|items
(braket
id|i
op_star
l_int|3
)braket
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
r_else
id|fprintf
(paren
id|stderr
comma
l_string|&quot;%s&quot;
comma
id|items
(braket
(paren
id|scroll
op_plus
id|choice
)paren
op_star
l_int|3
)braket
)paren
suffix:semicolon
id|delwin
(paren
id|dialog
)paren
suffix:semicolon
id|free
(paren
id|status
)paren
suffix:semicolon
r_return
id|button
suffix:semicolon
r_case
l_char|&squot;X&squot;
suffix:colon
r_case
l_char|&squot;x&squot;
suffix:colon
id|key
op_assign
id|ESC
suffix:semicolon
r_case
id|ESC
suffix:colon
r_break
suffix:semicolon
)brace
multiline_comment|/* Now, update everything... */
id|doupdate
(paren
)paren
suffix:semicolon
)brace
id|delwin
(paren
id|dialog
)paren
suffix:semicolon
id|free
(paren
id|status
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* ESC pressed */
)brace
eof

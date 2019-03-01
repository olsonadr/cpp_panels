/*
 *  Console class. It is a Component that has variable pos, and is primary
 *  container used to get user input and output in one area. Not meant to
 *  have any elements added to it. It has a list of strings that represents
 *  the history of inputs and responses.
 */

#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#define MAX_INPUT_SIZE 100

#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <termios.h>
#include "Element.hpp"

class Console : public Element
{
    protected:
        //Fields
        struct int_duple dim;	    /* Dimensions of the container */
        char * merged_arr;	    /* The merged array returned by merge() */
        char ** history;	    /* The history of inputs and outputs */
        int history_num;	    /* The number of strings in history */
        int history_len;	    /* The maximum length of the history */
        struct int_duple input_pos; /* The global position of the input cursor */
        const char * input_prefix;  /* The string preceding the input field */
        int input_prefix_len;	    /* The length of the input prefix */
        char bg_char;		    /* The character to be put in empty space */
        struct termios term_info;   /* The termios allowing for echo manip, etc */
        bool display_input_line;    /* Whether the input area should be displayed */

        // Functions
        void move_input();	    /* Moves cursor to the input pos */
        void move_home();	    /* Moves cursor back home */


    public:
        // Constructors, Operators, and Destructors
        Console(int pos_x, int pos_y, int width, int height,
                int max_history, bool is_dynamic,
                const char * name = "Console");

        Console(const Console & old_console,
                bool is_dynamic = STATIC_ELEMENT);

        void operator=(const Console & old_console);

        ~Console();

        // Accessors
        int_duple get_dim() { return this->dim; }
        char get_bg_char() { return this->bg_char; }

        // Mutators
        void setup_input(struct int_duple g_console_pos);
        void set_input_prefix(const char * input_prefix);
        void set_display_input_line(bool new_val);
        void set_bg_char(char new_bg_char);
        void reset_merged();
        char * merge();

        // I/O
        void input(char * input_buff, int input_buff_size = MAX_INPUT_SIZE);
        void output(const char * line);
        void clear();

        // Misc
        void pause_and_flush();

	// Reasonably Public Terminal Controls
        void cursor_visible();	    /* Makes the cursor visible */
        void cursor_invisible();    /* Makes the cursor invisible */
        void enable_echo();	    /* Enables echo in console */
        void disable_echo();	    /* Disables echo in console */
        void enable_wrap();	    /* Enables line-wrapping in terminal */
        void disable_wrap();	    /* Disables line-wrapping in terminal */
	void enable_buffer();	    /* Enables buffering of input in terminal */
	void disable_buffer();	    /* Disables buffering of input in terminal */

        // Debug
        bool get_display_input() { return this->display_input_line; }
};

#endif

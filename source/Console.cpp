/*
 *  Console class. It is a Component that has variable pos, and is primary
 *  container used to get user input and output in one area. Not meant to
 *  have any elements added to it. It has a list of strings that represents
 *  the history of inputs and responses.
 */

#include "Console.hpp"

// Constructors, Operator Overrides, Destructors

/*
 * Parameterized (and primary) constructor
 */
Console::Console(int pos_x, int pos_y,
                 int width, int height,
                 int history_max, bool is_dynamic,
                 const char * name)
    : Element(pos_x, pos_y, is_dynamic, "Console", name),
      history_len(history_max), history_num(0),
      history(new char * [history_max]),
      input_prefix_len(3),
      input_prefix(">> "),
      bg_char(' '),
      display_input_line(true)
{
    // Contents + ends of lines
    this->merged_arr = new char[(width + 1) * height];

    this->dim =
    {
        .x = width,
        .y = height
    };

    this->input_pos =
    {
        .x = 0,
        .y = 0
    };
}


/*
 * Copy Constructor
 */
Console::Console(const Console & old_console, bool is_dynamic)
    : Element(old_console, is_dynamic),
      history_num(old_console.history_num),
      history_len(old_console.history_len),
      input_pos(old_console.input_pos),
      dim(old_console.dim),
      input_prefix(old_console.input_prefix),
      input_prefix_len(old_console.input_prefix_len),
      bg_char(old_console.bg_char),
      display_input_line(old_console.display_input_line)
{
    // Merged array
    this->merged_arr = new char[old_console.dim.y * old_console.dim.x];

    for (int row = 0; row < old_console.dim.y; row++)
    {
        for (int col = 0; col < old_console.dim.x; col++)
        {
            /* Copy contents of merged_arr */

            this->merged_arr[(row * old_console.dim.x) + col] =
                old_console.merged_arr[(row * old_console.dim.x) + col];
        }
    }

    // History array
    this->history = new char * [old_console.history_len];

    for (int i = 0; i < old_console.history_num; i++)
    {
        this->history[i] = old_console.history[i];
    }

    // Input position
    this->input_pos =
    {
        .x = old_console.input_pos.x,
        .y = old_console.input_pos.y
    };
}


/*
 * Overriden assignment operator
 */
void Console::operator=(const Console & old_console)
{
    Element::operator=(static_cast<Element>(old_console));

    // Merged array
    bool needs_realloc = this->dim.x != old_console.dim.x ||
                         this->dim.y != old_console.dim.y;

    if (needs_realloc)
    {
        /* Delete and start re-allocating (different dimensions) */

        delete[] this->merged_arr;
        this->merged_arr = new char[old_console.dim.y * old_console.dim.x];
    }

    for (int row = 0; row < old_console.dim.y; row++)
    {
        for (int col = 0; col < old_console.dim.x; col++)
        {
            /* Copy contents of merged_arr */

            this->merged_arr[(row * old_console.dim.x) + col] =
                old_console.merged_arr[(row * old_console.dim.x) + col];
        }
    }

    // End merged array

    // Replace history if it's a different length
    if (old_console.history_len != this->history_len)
    {
        delete[] this->history;
        this->history = new char * [old_console.history_len];

        for (int i = 0; i < old_console.history_num; i++)
        {
            this->history[i] = old_console.history[i];
        }
    }

    // Misc Fields
    this->dim = old_console.dim;
    this->history_num = old_console.history_num;
    this->input_pos = old_console.input_pos;
    this->input_prefix = old_console.input_prefix;
    this->input_prefix_len = old_console.input_prefix_len;
    this->bg_char = old_console.bg_char;
    this->display_input_line = old_console.display_input_line;
}


/*
 * Destructor
 */
Console::~Console()
{
    for (int i = 0; i < this->history_num; i++)
    {
        free(this->history[i]);
    }

    delete[] this->history;
    delete[] this->merged_arr;
}




// Public Terminal-Control Functions

/*
 * Moves the terminal cursor to the input_pos coord. Setup input first!
 * Uses ANSI escape sequence to do this.
 */
void Console::move_input()
{
    // Set cursor to input position
    printf("\e[%d;%dH", this->input_pos.y, this->input_pos.x);
}


/*
 * Moves the terminal cursor to the home pos (top-left). Uses an ANSI escape
 * sequence to do this.
 */
void Console::move_home()
{
    printf("\e[H"); // Set cursor to top-left corner
}


/*
 * Makes the cursor visible in the terminal using an ANSI escape sequence.
 */
void Console::cursor_visible()
{
    printf("\e[?25h"); // Make cursor visible
}


/*
 * Makes the cursor invisible in the terminal using an ANSI escape sequence.
 */
void Console::cursor_invisible()
{
    printf("\e[?25l"); // ANSI sequence, makes cursor invisible
}


/*
 * Enables ECHOing in the terminal, such that keystrokes of the user are immediately
 * displayed at the current cursor position in the terminal, using termios. This is
 * standard terminal behaviour. Used for getting input.
 */
void Console::enable_echo()
{
    // Restore Echo
    tcgetattr(0, &this->term_info);
    this->term_info.c_lflag |= ECHO; /* Turn on ECHO */
    tcsetattr(0, TCSANOW, &this->term_info);
}


/*
 * Disables ECHOing in the terminal, such that keystrokes of the user are not automa-
 * tically displayed at the current cursor position in the terminal, using termios.
 * This is usual password entry terminal behaviour, for example.
 */
void Console::disable_echo()
{
    // Disable Echo
    tcgetattr(0, &this->term_info);
    this->term_info.c_lflag &= ~ECHO; /* Turn off ECHO */
    tcsetattr(0, TCSANOW, &this->term_info);
}


/*
 * Enables line-wrapping in the terminal, such that lines that are too long for the
 * current terminal size are wrapped down onto the next line. Used for input.
 */
void Console::enable_wrap()
{
    printf("\e[?7h"); // ANSI sequence, enables line-wrapping
}


/*
 * Disables line-wrapping in the terminal, such that lines that are too long for the
 * current terminal size are NOT wrapped down onto the next line. Used for input.
 */
void Console::disable_wrap()
{
    printf("\e[?7l"); // ANSI sequence, disables line-wrapping
}

/*
 * Disables buffering of input in terminal such that getchar() will be taken without
 * waiting for an <enter> press to take it.
 */
void Console::enable_buffer()
{
    tcgetattr(STDIN_FILENO, &t);	    // Get current terminal info
    t.c_lflag |= ICANON;		    // Manipulate flag bits
    tcsetattr(STDIN_FILENO, TCSANOW, &t);   // Apply new settings
}

/*
 * Disables buffering of input in terminal such that getchar() will only be taken
 * after waiting for an <enter> press.
 */
void Console::disable_buffer()
{
    tcgetattr(STDIN_FILENO, &t);	    // Get current terminal info
    t.c_lflag &= ~ICANON;		    // Manipulate flag bits
    tcsetattr(STDIN_FILENO, TCSANOW, &t);   // Apply new settings
}



// Public Functions

/*
 * Sets the input position to the bottom left corner of the console
 * (after the prefix) by taking the global position of the console.
 */
void Console::setup_input(struct int_duple g_console_pos)
{
    this->input_pos =
    {
        .x = g_console_pos.x + int(strlen(this->input_prefix)) + 1,
        .y = g_console_pos.y + this->dim.y - 1 + 1
    };
}


/*
 * Sets the input prefix (what characters immediately precede where the
 * user will input when input() is called.
 */
void Console::set_input_prefix(const char * input_prefix)
{
    this->input_prefix = input_prefix;
    this->input_prefix_len = strlen(input_prefix);
    this->has_changed = true;
}


/*
 * Sets whether the input line will be displayed when merged.
 */
void Console::set_display_input_line(bool new_val)
{
    this->display_input_line = new_val;
    this->has_changed = true;
}


/*
 * Waits for and gets characters from stdin until it finds a return, thus stopping
 * a single of input of multiple characters ("ynyny<enter>") from being pushed through
 * to later getchar() calls. Not used in the library, but is an option.
 */
void Console::pause_and_flush()
{
    while (getchar() != '\n');
}


/*
 * Gets user input at the correct input position, adding the user's input
 * to the history list using output(), taking the first n chars as designated
 * by the second (optional parameter). If you do not set this to the length of
 * the buffer you pass to take input into, it will take the first 100.
 */
void Console::input(char * input_buff,
                    int input_buff_size)
{
    // Setup
    move_input();
    enable_echo();
    cursor_visible();
    disable_wrap();

    // Get Input and Replace \n with \0
    fgets(input_buff, input_buff_size, stdin);
    size_t ln = strlen(input_buff) - 1;

    if (input_buff[ln] == '\n')
    {
        input_buff[ln] = '\0';
    }

    // Cleanup
    enable_wrap();
    cursor_invisible();
    disable_echo();
    move_home();

    // Push to History and Return
    char * output_buff = new char[input_buff_size + input_prefix_len];
    strcat(output_buff, input_prefix);
    strcat(output_buff, input_buff);
    output(output_buff);
    delete output_buff;
}


/*
 * Adds the passed string to the history array, pushing everything back
 * and incrementing history_num if it is less than history_len, changes
 * has_changed to true.
 */
void Console::output(const char * line)
{
    if (this->history_len > 0)
    {
        if (this->history_num < this->history_len)
        {
            this->history_num++;
        }

        for (int i = this->history_num - 1; i > 0; i--)
        {
            this->history[i] = this->history[i - 1];
        }

        this->history[0] = strdup(line);
    }

    this->has_changed = true;
}


/*
 * Clears the history array (like clearing a console) by setting history num to 0.
 */
void Console::clear()
{
    this->history_num = 0;
    this->has_changed = true;
}


/*
 * Sets the background character that is treated as empty space (that displays
 * the stuff behind it) when seen by merge.
 */
void Console::set_bg_char(char new_bg_char)
{
    this->bg_char = new_bg_char;
    this->has_changed = true;
}


/*
 * Resets the merged buffer back to 'empty' state full of spaces with \n chars
 * at the end of each line (using bg_char to fill terminal).
 */
void Console::reset_merged()
{
    for (int row = 0; row < this->dim.y; row++)
    {
        for (int col = 0; col < this->dim.x; col++)
        {
            this->merged_arr[(row * this->dim.x) + col] = this->bg_char;
        }

        if (row < this->dim.y - 1)
        {
            /* For all but the last rows (which has a \0 instead). */

            this->merged_arr[(row * this->dim.x) + this->dim.x] = '\n';
        }
    }

    // The last chararcter of the buffer
    this->merged_arr[((this->dim.y - 1) * this->dim.x) + this->dim.x] = '\0';
}


/*
 * Merges the history into one character buffer (in merged_arr), but
 * only if the Console has been updated. Returns merged_arr.
 */
char * Console::merge()
{
    bool must_update = this->has_changed;

    if (must_update)
    {
        reset_merged();

        int row = this->dim.y - 1;

        // Input line
        if (this->display_input_line == true)
        {
            /* The input line should be rendered */

            for (int col = 0; col < strlen(this->input_prefix); col++)
            {
                this->merged_arr[(row * this->dim.x) + col] = this->input_prefix[col];
            }
        }
        else
        {
            /* The input line is invisible, move row down to account for this */

            row++;
        }

        int col = 0;

        // Rest of lines
        for (int i = 0; i < this->history_num; i++)
        {
            // Check num lines due to current history element
            int num_lines = 1;
            int curr_line_start = 0;

            for (int j = 0; j < strlen(this->history[i]); j++)
            {
                if (this->history[i][j] == '\n' ||
                        j - curr_line_start >= this->dim.x)
                {
                    /* If you hit new line or line would be to edge */

                    num_lines++;
                    curr_line_start = j;
                }
            }

            // Merge History
            col = 0;
            row -= num_lines;

            for (int j = 0; j < strlen(this->history[i]); j++)
            {
                if (this->history[i][j] == '\n')
                {
                    /* '\n' at current j, reset to left and skip to next char */

                    row++;
                    col = 0;
                    continue;
                }

                if (col >= this->dim.x)
                {
                    /* Would hit edge, wrap back to left */

                    row++;
                    col = 0;
                }

                // Sets the appropriate char in buffer
                if (row >= 0 && row < this->dim.y &&
                        col >= 0 && col < this->dim.x)
                {
                    /* Is in bounds at index */

                    if (this->history[i][j] != '`')
                    {
                        /* Is not transparent char at index */

                        this->merged_arr[(row * this->dim.x) + col] =
                            this->history[i][j];
                    }
                }

                // Move cursor to next char position
                col++;
            }

            // Move cursor to next string position
            row -= num_lines - 1;
        }
    }

    this->has_changed = false;
    return this->merged_arr;
}

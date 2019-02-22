/*
 *  Element class, which is inherited by Containers and Components
 *  for some sick curses-esque rendering.
 */

#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#define DYNAMIC_ELEMENT true
#define STATIC_ELEMENT false

struct int_duple
{
    int x;
    int y;
};

class Element
{
    protected:
        struct int_duple pos;
        bool has_changed;
        bool is_visible;
        bool is_dynamic;
        const char * name;
        const char * type;

    public:
        // Constructors + Operator Overload
        Element(int pos_x, int pos_y, bool is_dynamic,
                const char * type = "Element",
                const char * name = "Element");

        Element(const Element & old_element, bool is_dynamic = STATIC_ELEMENT);

        void operator=(const Element & old_element);

        // Accessors
        int_duple get_pos() { return this->pos; }
        const char * get_name() { return this->name; }
        bool get_is_visible() { return this->is_visible; }
        virtual bool get_has_changed() { return this->has_changed; }
        bool get_is_dynamic() { return this->is_dynamic; }
        const char * get_type() { return this->type; }

        // Mutators
        void set_pos(int x, int y);
        void set_pos(struct int_duple m_pos);
	virtual void mark_has_changed();
        virtual void reset_has_changed();
        void make_visible();
        void make_invisible();
        void toggle_visible();
};

#endif

#include "splashkit.h"

class Tile
{
    private:
        bitmap image;
        point_2d position;
        int value  = 0;
        drawing_options opts;
        rectangle border;
        int tile_num;


    public:
        Tile (bitmap image, point_2d position, int tile_num)
        {
            this->image = image;
            this->position = position;
            this->border = rectangle_from(this->position, 64, 64);
            this->tile_num = tile_num;
            this->opts = option_defaults();
            this->opts.draw_cell = 0;
        };

        void draw_tile()
        {
            if(this->value > 0)
                draw_bitmap(image, position.x, position.y, opts);
            
            draw_rectangle(COLOR_GREEN, border);
        };

        void check_input(int tile_selected)
        {
            point_2d pt = mouse_position();

            if(mouse_down(LEFT_BUTTON))
            {
                if(point_in_rectangle(pt, this->border))
                {
                    value = tile_selected;
                    opts.draw_cell = tile_selected - 1;
                }
            }

            if(mouse_down(RIGHT_BUTTON))
            {
                if(point_in_rectangle(pt, this->border))
                {
                    opts.draw_cell = 0;
                    value = 0; 
                }
            }
        };

        int get_value()
        {
            return this->value;
        };
};
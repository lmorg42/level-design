#include "splashkit.h"

enum selection
{
    DARK_BLOCK,
    LIGHT_BLOCK,
    LADDER,
    WATER1,
    WATER2,
    TOXIC,
    NONE
};

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

        void check_input(selection tile_selected)
        {
            point_2d pt = mouse_position();

            if(mouse_down(LEFT_BUTTON))
            {
                if(point_in_rectangle(pt, this->border))
                {
                    switch (tile_selected)
                    {
                        case DARK_BLOCK:
                            opts.draw_cell = 0;
                            value = 1;
                            break;
                        
                        case LIGHT_BLOCK:
                            opts.draw_cell = 1;
                            value = 2;
                            break;

                        case LADDER:
                            opts.draw_cell = 2;
                            value = 3;
                            break;

                        case WATER1:
                            opts.draw_cell = 3;
                            value = 4;
                            break;

                        case WATER2:
                            opts.draw_cell = 4;
                            value = 5;
                            break;

                        case TOXIC:
                            opts.draw_cell = 5;
                            value = 6;
                            break;

                        default:
                            opts.draw_cell = 0;
                            value = 0;
                            break;
                    }
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
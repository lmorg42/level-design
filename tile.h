#include "splashkit.h"

class Tile
{
    private:
        bitmap blocks;
        bitmap pipes;
        bitmap current_bitmap;
        string type;
        point_2d position;
        int value  = 0;
        drawing_options opts_block;
        drawing_options opts_pipe;
        drawing_options current_opts;
        rectangle border;
        int tile_size;

    public:
        Tile (bitmap initial_bitmap, point_2d position, int tile_size)
        {
            //this->blocks = blocks;
            //this->pipes = pipes;
            //this->type = "block";
            this->position = position;
            this->tile_size = tile_size;
            this->border = rectangle_from(this->position, this->tile_size, this->tile_size);
            //this->opts_block = option_defaults();
            //this->opts_block.draw_cell = 0;
            //this->opts_pipe = option_defaults();
            //this->opts_pipe.draw_cell = 0;
            this->current_bitmap = initial_bitmap;
            this->current_opts = option_defaults();
        };

        void draw_tile()
        {
            // if(this->value > 0 && this->type == "block")
            //     draw_bitmap(blocks, position.x, position.y, opts_block);
            // else if(this->value > 0 && this->type == "pipe")
            //     draw_bitmap(pipes, position.x, position.y, opts_pipe);

            if(this->value > 0)
                draw_bitmap(current_bitmap, position.x, position.y, current_opts);
            
            draw_rectangle(COLOR_GREEN, border);
        };

        void check_input(int tile_selected, bitmap current_bitmap, int offset)
        {
            
            point_2d pt = mouse_position();
            point_2d camera = camera_position();
            // drawing_options opts;
            int multiplier = 0;

            pt.x = pt.x + camera.x;
            pt.y = pt.y + camera.y;

            // if(type == "block")
            //     opts = this->opts_block;
            // else if(type == "pipe")
            // {
            //     opts = this->opts_pipe;
            //     multiplier = bitmap_cell_count(blocks);
            // }

            update_tile(pt, tile_selected, offset, type, current_bitmap);

            // if(type == "block")
            //     this->opts_block = opts;
            // else if(type == "pipe")
            //     this->opts_pipe = opts;
        };

        void update_tile(point_2d mouse_position, int tile_selected, int offset, string type, bitmap current_bitmap)
        {
            if(mouse_down(LEFT_BUTTON))
            {
                if(point_in_rectangle(mouse_position, this->border))
                {
                    this->current_bitmap = current_bitmap;
                    this->type = type;
                    this->value = tile_selected + offset;
                    this->current_opts.draw_cell = tile_selected - 1;
                    //this->current_opts.draw_cell = tile_selected - 1;
                }
            }
            
            if(mouse_down(RIGHT_BUTTON))
            {
                if(point_in_rectangle(mouse_position, this->border))
                {
                    //this->type = type;
                    this->current_opts.draw_cell = 0;
                    value = 0; 
                }
            }

            //return opts;
        };

        int get_value()
        {
            return this->value;
        };

        void set_type(string type)
        {
            this->type = type;
        }
};
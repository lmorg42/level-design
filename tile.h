#include "splashkit.h"

class Tile
{
    private:
        bitmap blocks;
        bitmap pipes;
        string type;
        point_2d position;
        int value  = 0;
        drawing_options opts_block;
        drawing_options opts_pipe;
        rectangle border;
        int tile_size;

    public:
        Tile (bitmap blocks, bitmap pipes, point_2d position, int tile_size)
        {
            this->blocks = blocks;
            this->pipes = pipes;
            this->type = "block";
            this->position = position;
            this->tile_size = tile_size;
            this->border = rectangle_from(this->position, this->tile_size, this->tile_size);
            this->opts_block = option_defaults();
            this->opts_block.draw_cell = 0;
            this->opts_pipe = option_defaults();
            this->opts_pipe.draw_cell = 0;
        };

        void draw_tile()
        {
            if(this->value > 0 && this->type == "block")
                draw_bitmap(blocks, position.x, position.y, opts_block);
            else if(this->value > 0 && this->type == "pipe")
                draw_bitmap(pipes, position.x, position.y, opts_pipe);
            
            draw_rectangle(COLOR_GREEN, border);
        };

        void check_input(int tile_selected, string type)
        {
            point_2d pt = mouse_position();
            drawing_options opts;
            int multiplier = 1;

            if(type == "block")
                opts = this->opts_block;
            else if(type == "pipe")
            {
                opts = this->opts_pipe;
                multiplier = bitmap_cell_count(blocks);
            }

            opts = update_tile(opts, pt, tile_selected, multiplier, type);

            if(type == "block")
                this->opts_block = opts;
            else if(type == "pipe")
                this->opts_pipe = opts;
        };

        drawing_options update_tile(drawing_options opts, point_2d mouse_position, int tile_selected, int addition, string type)
        {
            if(mouse_down(LEFT_BUTTON))
            {
                if(point_in_rectangle(mouse_position, this->border))
                {
                    this->type = type;
                    this->value = tile_selected + addition;
                    opts.draw_cell = tile_selected - 1;
                }
            }
            
            if(mouse_down(RIGHT_BUTTON))
            {
                if(point_in_rectangle(mouse_position, this->border))
                {
                    this->type = type;
                    opts.draw_cell = 0;
                    value = 0; 
                }
            }

            return opts;
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
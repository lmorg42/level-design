#include "splashkit.h"
#include "tile.h"
#include <fstream>
#include <vector>

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 896

//Make these divisible by (16/32/64) depending on tile size used
//Gives extra size to the screen, for use with non-static camera
#define SCREEN_WIDTH_EXTRA 512 * 10
#define SCREEN_HEIGHT_EXTRA 512

void write_out_level_to_file(string file, vector<vector<Tile>> tiles)
{
    std::ofstream level;
    level.open(file);

    for(int i = 0; i < tiles.size(); i++)
    {
        for(int j = 0; j < tiles[i].size(); j ++)
            level << tiles[i][j].get_value() << " ";
        level << "\n";
    }
    level.close();
}

void update_camera(vector_2d mouse_coordinates)
{
    if (key_down(LEFT_ALT_KEY))
    {
        move_camera_by(mouse_coordinates.x * -1, mouse_coordinates.y * -1);
    }  
}

int main()
{
    load_resource_bundle("game_resources", "gameresources.txt");
    open_window("Level Design", SCREEN_WIDTH, SCREEN_HEIGHT);

    bitmap blocks = bitmap_named("SewerBlocks");
    string type = "block";
    //bitmap image = bitmap_named("16TestBlocks");
    //bitmap image = bitmap_named("32TestBlocks");
    bitmap pipes = bitmap_named("pipeTiles");
    bitmap current_selection = blocks;
    bool draw_pipes = false;

    point_2d origin;
    origin.x = 0;
    origin.y = 0;

    int tile_size = 64;
    int tile_selection = 1;

    drawing_options opts = option_defaults();
    opts.draw_cell = 0;
    opts.camera = DRAW_TO_SCREEN;

    vector<vector<Tile>> tiles;
    for(int j = 0; j < (SCREEN_HEIGHT + SCREEN_HEIGHT_EXTRA)/tile_size; j++)
    {
        vector<Tile> row;
        for(int i = 0; i < (SCREEN_WIDTH + SCREEN_WIDTH_EXTRA)/tile_size; i++)
        {
            origin.x = 0 + (i * tile_size);
            origin.y = 0 + (j * tile_size);
            Tile test(blocks, pipes, origin, tile_size);
            row.push_back(test);
        }

        tiles.push_back(row);
    }

    while(!key_typed(ESCAPE_KEY))
    {
        clear_screen(COLOR_BLACK);
        
        for(int i = 0; i < tiles.size(); i++)
        {
            for(int j = 0; j < tiles[i].size(); j++)
            {
                tiles[i][j].draw_tile();
                tiles[i][j].check_input(tile_selection, type);
            }
        }

        if(key_typed(A_KEY))
        {
            write_out_level_to_file("file.txt", tiles);
        }

        if(key_typed(P_KEY))
        {
            write_line("Switching tiles");
            if(!draw_pipes)
            {
                write_line("Draw Pipes");
                type = "pipe";
                draw_pipes = true;
                tile_selection = 1;
                current_selection = pipes;
                opts.draw_cell = 0;
            }
            else
            {
                write_line("Draw Blocks");
                type = "block";
                draw_pipes = false;
                tile_selection = 1;
                current_selection = blocks;
                opts.draw_cell = 0;
            }
        }

        if(key_typed(UP_KEY))
        {
            tile_selection += 1;
            opts.draw_cell += 1;

            if(tile_selection == 1)
            {
                opts.draw_cell = 0;
            }

            if(tile_selection > bitmap_cell_count(current_selection))
            {
                tile_selection = bitmap_cell_count(current_selection);
                opts.draw_cell = bitmap_cell_count(current_selection) - 1;
            }
        }

        if(key_typed(DOWN_KEY))
        {
            tile_selection -= 1;
            opts.draw_cell -= 1;

            if(tile_selection < 0)
            {
                tile_selection = 0;
                opts.draw_cell = 0;
            }
        }

        point_2d current_mouse_position = mouse_position();
        
        update_camera(mouse_movement());

        if(tile_selection > 0)
            draw_bitmap(current_selection, current_mouse_position.x, current_mouse_position.y, opts);


        
        process_events();
        refresh_screen(60);
    }

    free_resource_bundle("game_resources");

    return 0;
}
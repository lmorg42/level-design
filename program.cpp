#include "splashkit.h"
#include "tile.h"
#include <fstream>
#include <vector>

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 896

//Gives extra size to the screen, for use with non-static camera
//Multiply by tile size of the map
#define SCREEN_WIDTH_EXTRA 64 * 0
#define SCREEN_HEIGHT_EXTRA 64 * 0

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

vector<vector<Tile>> make_layer(int tile_size, bitmap blocks, bitmap pipes)
{
    vector<vector<Tile>> tiles;
    point_2d origin;
    origin.x = 0;
    origin.y = 0;

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

    return tiles;
}

void draw_tiles(vector<vector<Tile>> tiles)
{
    for(int i = 0; i < tiles.size(); i++)
    {
        for(int j = 0; j < tiles[i].size(); j++)
            tiles[i][j].draw_tile();
    }
}

vector<vector<Tile>> check_tile_input(vector<vector<Tile>> tiles, int tile_selection, string type)
{
    for(int i = 0; i < tiles.size(); i++)
    {
        for(int j = 0; j < tiles[i].size(); j++)
                tiles[i][j].check_input(tile_selection, type);
    }

    return tiles;
}

int main()
{
    load_resource_bundle("game_resources", "gameresources.txt");
    open_window("Level Design", SCREEN_WIDTH, SCREEN_HEIGHT);

    bitmap blocks = bitmap_named("SewerBlocks");
    string type = "block";
    bitmap pipes = bitmap_named("pipeTiles");
    bitmap current_selection = blocks;

    int layers = 2;
    int current_layer = 1;

    int tile_size = 64;
    int tile_selection = 1;

    drawing_options opts = option_defaults();
    opts.draw_cell = 0;
    opts.camera = DRAW_TO_SCREEN;

    vector<vector<Tile>> tiles = make_layer(tile_size, blocks, pipes);
    vector<vector<Tile>> tiles_2;

    if(layers == 2)
        tiles_2 = make_layer(tile_size, blocks, pipes);

    while(!key_typed(ESCAPE_KEY))
    {
        clear_screen(COLOR_BLACK);

        draw_tiles(tiles);

        if(layers == 2)
            draw_tiles(tiles_2);
        

        if(current_layer == 1)
            tiles = check_tile_input(tiles, tile_selection, type);
        else
            tiles_2 = check_tile_input(tiles_2, tile_selection, type);

        if(layers == 2)
        {
            if(key_typed(L_KEY))
            {
                if(current_layer == 1)
                    current_layer = 2;
                else
                    current_layer = 1;
            }
        }

        if(key_typed(A_KEY))
        {
            write_out_level_to_file("file.txt", tiles);

            if(layers == 2)
                write_out_level_to_file("file2.txt", tiles_2);
        }

        if(key_typed(P_KEY))
        {
            if(type == "block")
            {
                type = "pipe";
                tile_selection = 1;
                current_selection = pipes;
                opts.draw_cell = 0;
            }
            else
            {
                type = "block";
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
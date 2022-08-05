#include "splashkit.h"
#include "tile.h"
#include <fstream>
#include <vector>

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 896

//Make these divisible by (16/32/64) depending on tile size used
#define SCREEN_WIDTH_EXTRA 0
#define SCREEN_HEIGHT_EXTRA 0

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

int main()
{
    load_resource_bundle("game_resources", "gameresources.txt");
    open_window("Level Design", SCREEN_WIDTH + SCREEN_WIDTH_EXTRA, SCREEN_HEIGHT + SCREEN_HEIGHT_EXTRA);

    bitmap image = bitmap_named("SewerBlocks");
    vector<vector<Tile>> tiles;
    point_2d origin;
    origin.x = 0;
    origin.y = 0;
    int tile_size = 64;
    int tile_selection = 1;

    //selection current_selection = DARK_BLOCK;

    for(int j = 0; j < (SCREEN_HEIGHT + SCREEN_HEIGHT_EXTRA)/tile_size; j++)
    {
        vector<Tile> row;
        for(int i = 0; i < (SCREEN_WIDTH + SCREEN_WIDTH_EXTRA)/tile_size; i++)
        {
            origin.x = 0 + (i * tile_size);
            origin.y = 0 + (j * tile_size);
            Tile test(image, origin, tile_size);
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
                tiles[i][j].check_input(tile_selection);
            }
        }

        if(key_typed(A_KEY))
        {
            write_out_level_to_file("file.txt", tiles);
        }

        if(key_typed(UP_KEY))
        {
            tile_selection += 1;

            if(tile_selection > bitmap_cell_count(image))
                tile_selection = 6;
        }

        if(key_typed(DOWN_KEY))
        {
            tile_selection -= 1;

            if(tile_selection < 0)
                tile_selection = 0;
        }
        
        process_events();
        refresh_screen(60);
    }

    free_resource_bundle("game_resources");

    return 0;
}
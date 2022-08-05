#include "splashkit.h"
#include "tile.h"
#include <fstream>
#include <vector>

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
    color background = COLOR_BLACK;
    load_resource_bundle("game_resources", "gameresources.txt");
    open_window("Level Design", 1600, 896);
    bitmap image = bitmap_named("SewerBlocks");
    vector<vector<Tile>> tiles;
    point_2d origin;
    origin.x = 0;
    origin.y = 0;

    int tile_selection = 0;

    selection current_selection = DARK_BLOCK;

    for(int j = 0; j < 14; j++)
    {
        vector<Tile> row;
        for(int i = 0; i < 25; i++)
        {
            origin.x = 0 + (i * 64);
            origin.y = 0 + (j * 64);
            Tile test(image, origin, i);
            row.push_back(test);
        }

        tiles.push_back(row);
    }

    while(!key_typed(ESCAPE_KEY))
    {
        clear_screen(background);
        
        for(int i = 0; i < tiles.size(); i++)
        {
            for(int j = 0; j < tiles[i].size(); j++)
            {
                tiles[i][j].draw_tile();
                tiles[i][j].check_input(current_selection);
            }
        }

        if(key_typed(A_KEY))
        {
            write_out_level_to_file("file.txt", tiles);
        }

        if(key_typed(UP_KEY))
        {
            tile_selection += 1;

            if(tile_selection > 6)
                tile_selection = 6;
        }

        if(key_typed(DOWN_KEY))
        {
            tile_selection -= 1;

            if(tile_selection < 0)
                tile_selection = 0;
        }

        switch (tile_selection)
        {
            case 0:
                current_selection = NONE;
                break;

            case 1:
                current_selection = DARK_BLOCK;
                break;

            case 2:
                current_selection = LIGHT_BLOCK;
                break;

            case 3:
                current_selection = LADDER;
                break;
            
            case 4:
                current_selection = WATER1;
                break;

            case 5:
                current_selection = WATER2;
                break;

            case 6:
                current_selection = TOXIC;
                break;

            default:
                current_selection = NONE;
                break;
        }
        
        process_events();
        refresh_screen(60);
    }

    free_resource_bundle("game_resources");

    return 0;
}
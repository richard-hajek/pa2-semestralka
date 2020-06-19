#include "Game.h"
#include "utils/Log.h"
#include <cassert>
#include <cstring>

bool parse_command_line_arguments(int argc, char *argv[], std::string & setup, std::string & save, std::string & newMap){

    bool newGame = false;

    Log::Debug("ARGPARSE", "All args:", "(", argc, ")");
    for (int j = 0; j < argc; ++j) {
        Log::Debug("ARGENUM", j, argv[j]);
    }

    for(int i = 1; i < argc; i++){

        if ( i == 1 ){
            setup = argv[i];
        }
        else if ( i == 2) {
            newGame = strcmp(argv[i], "map") == 0;
        }
        else if ( i == 3 ){
            if (newGame)
                newMap = argv[i];
            else
                save = argv[i];
        }
    }

    Log::Debug("ARGPARSE", "Found setup file: " + setup);
    Log::Debug("ARGPARSE", "Found save file: " + save);
    Log::Debug("ARGPARSE", "Found map file: " + newMap);

    return ! setup.empty() && ( ( ! save.empty() ) || ( ! newMap.empty() ) );
}

void printHelp(){
    std::cout <<
        "Usage:\n" <<
        "\thajekric <setupfile> map <mapname>\n" <<
        "\t .... to start a new game\n" <<
        "\thajekric <setupfile> save <savefile>\n" <<
        "\t .... to load a savefile\n";
}

int start(const std::string& setup, const std::string& save, const std::string& newMap){
    Game game;

    if (! game.Setup(setup)){
        Log::Err("STARTER", "Failed to load setup file! (" + setup + ")");
        return 1;
    }

    if (!save.empty()){
        if ( ! game.LoadGame(save)){
            Log::Err("STARTER", "Failed to load save file! (" + save + ")");
            return 1;
        }
    }
    else if (!newMap.empty()){
        if (! game.NewGame(newMap)){
            Log::Err("STARTER", "Failed to start a new game! ( mapname: " + newMap + ")");
            return 1;
        }
    }

    game.Start();

    return 0;
}

int main(int argc, char *argv[]){

    std::string setup;
    std::string save;
    std::string newMap;

    int ret = 0;

    Log::Begin();

    if (parse_command_line_arguments(argc, argv, setup, save, newMap)){
        ret = start(setup, save, newMap);
    }
    else {
        printHelp();
    }

    Log::End();

    return ret;
}
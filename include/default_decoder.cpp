#include "linked_list.h"
#include "player.h"
#include "default_decoder.h"
#include "directed_graph.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime>
#include <bits/stdc++.h>
#include <cstddef>

using namespace std;

DefaultDecoder::DefaultDecoder( string _folderPath ) : BaseDecoder(_folderPath) {
    
    for( const auto& entry : filesystem::directory_iterator(_folderPath) ){
        
        file *newFile = new file;
        filesystem::path fPath = entry.path();

        if( fPath.has_filename() ){
            newFile->path = fPath.filename().generic_string();

            regex re("^\\[(\\d{2}-\\d{2}-\\d{4})\\]\\.FullLog\\.txt$");
            smatch match;

            bool matches = regex_search(folderPath, match, re);
            matches = matches && match.size() == 2;

            if( matches ){

                string date = match.str(1);
                
                tm *timeinfo;

                strptime( date.c_str(), "%d-%m-%Y", timeinfo);

                CustomTime ct;
                ct.time = mktime( timeinfo );

                newFile->date = ct;

                files.add( ct, newFile );
            }
        }
        
    }
}

struct PlayerInfo{
    Player *player;
    time_t playing_start_time;
};

void perfomPlayerOperation( 
    DirectedGraph<string,char,IP,Player> *& graphByName,
    DirectedGraph<IP,int,string,Player> *& graphByIp,
    string line,
    time_t file_time,
    LinkedList<string,PlayerInfo>*& current_players
){

    regex re("^\\[(.+)\\]\\s\\[(.+)\\](.+)$");
    smatch match;

    bool matches = regex_search(line, match, re);
    matches = matches && match.size() == 4;

    if( matches ){
        
        tm *timeinfo;
        string date = match.str(1);
        strptime( date.c_str(), "%d/%m/%Y - %H:%M:%S", timeinfo);

        time_t msg_time = mktime( timeinfo );

        CustomTime ct;
        ct.time = msg_time;

        char* type = match.str(2).c_str();

        switch( type ){
            case "GLOBAL":
            case "TEAM":
            case "VEHICLE":

            // new chat message
            regex msg_re("^\\s(.+)\\sID:\\s\\[\\d{1,2}\\]\\s:\\s(.+)$");
            smatch msg_match;

            bool msg_matches = regex_search(msg_match.str(3), msg_match, msg_re);
            msg_matches = matches && msg_match.size() == 3;

            if( msg_matches ){
                string name = msg_match.str(1);
                string msg = msg_match.str(2);

                Message newMessage;
                newMessage.time = ct;
                newMessage.value = msg;

                PlayerInfo* playerInfo = current_players->find( name );

                if( playerInfo != NULL ){
                    playerInfo->player->messages->add( ct, &newMessage );
                }else{
                    DirectedGraphNode<string,IP,Player>* node = graphByName->getNodeByKey( name );
                    IP lastKnownIp = node->lastKnownKey;

                    Player* player = node->values->find( lastKnownIp );

                    if( player == NULL ){

                        player = new Player;
                        player->ip = lastKnownIp;
                        player->name = name;
                        player->messages = new LinkedList<CustomTime, Message>;
                        player->commands = new LinkedList<CustomTime, Message>;

                        node->values->add( lastKnownIp, player );
                        graphByIp->add( lastKnownIp, name, player);
                    }

                    player->messages->add( ct, &newMessage );

                    playerInfo = new PlayerInfo;
                    playerInfo->player = player;
                    playerInfo->playing_start_time = ct.time;

                    current_players->add( name, playerInfo );
                }
                
            }
            break;

            case "CHAT COMMAND":
                // new join message
                // Hash key doesnt look relevant for now
                regex msg_re(
                    "^\\s\\[.+\\]\\s(.+)\\s\\ID:\\s\\[\\d{1,2}\\]\\sIP:\\s\\[(.+)\\]:\\s(.+)$"
                );
                smatch msg_match;

                bool msg_matches = regex_search(msg_match.str(3), msg_match, msg_re);
                msg_matches = matches && msg_match.size() == 4;

                if( msg_matches ){
                    string name = msg_match.str(1);
                    string str_ip_port = msg_match.str(2);
                    string msg = msg_match.str(3);

                    IP ip_port( str_ip_port );

                    Message newMessage;
                    newMessage.time = ct;
                    newMessage.value = msg;

                    PlayerInfo* playerInfo = current_players->find( name );

                    if( playerInfo != NULL ){
                        playerInfo->player->commands->add( ct, &newMessage );
                    }else{
                        Player* player = graphByIp->find( ip_port, name );

                        if( player == NULL ){
                            player = new Player;

                            player->ip = ip_port;
                            player->name = name;
                            player->messages = new LinkedList<CustomTime, Message>;
                            player->commands = new LinkedList<CustomTime, Message>;

                            graphByIp->add( ip_port, name, player);
                            graphByName->add( name, ip_port, player);
                        }

                        player->commands->add( ct, &newMessage );

                        playerInfo = new PlayerInfo;

                        playerInfo->player = player;
                        playerInfo->playing_start_time = ct.time;

                        current_players->add( name, playerInfo );

                        PlayerInfo *playerInfo = current_players->find( name );
                    }
                    
                }
            break;

            case "JOIN":
                // new join message
                // Hash key doesnt look relevant for now
                regex msg_re("^\\tName:\\s(.+)\\tID:\\s\\[\\d{1,2}\\]\\tIP:\\s\\[(.+)\\].+$");
                smatch msg_match;

                bool msg_matches = regex_search(msg_match.str(3), msg_match, msg_re);
                msg_matches = matches && msg_match.size() == 3;

                if( msg_matches ){
                    string name = msg_match.str(1);
                    string str_ip_port = msg_match.str(2);

                    IP ip_port( str_ip_port );

                    PlayerInfo *playerInfo = current_players->find( name );
                    if( playerInfo != NULL ){

                        double played_time = difftime( ct.time, playerInfo->playing_start_time);
                        playerInfo->player->time_played += played_time;
                        playerInfo->playing_start_time = ct.time;

                    }else{
                        Player* player = graphByIp->find( ip_port, name );

                        if( player == NULL ){
                            player = new Player;

                            player->ip = ip_port;
                            player->name = name;
                            player->messages = new LinkedList<CustomTime, Message>;
                            player->commands = new LinkedList<CustomTime, Message>;

                            graphByIp->add( ip_port, name, player);
                            graphByName->add( name, ip_port, player);
                        }

                        playerInfo = new PlayerInfo;

                        playerInfo->player = player;
                        playerInfo->playing_start_time = ct.time;

                        current_players->add( name, playerInfo );
                    }
                }
            break;

            case "QUIT":

                // new quit message
                regex msg_re("^\\tName:\\s(.+)\\tID:\\s\\[\\d{1,2}\\]\\tIP:\\s\\[(.+)\\].+$");
                smatch msg_match;

                bool msg_matches = regex_search(msg_match.str(3), msg_match, msg_re);
                msg_matches = matches && msg_match.size() == 3;

                if( msg_matches ){
                    string name = msg_match.str(1);
                    string str_ip_port = msg_match.str(2);

                    IP ip_port( str_ip_port );

                    PlayerInfo *playerInfo = current_players->find( name );
                    if( playerInfo != NULL ){

                        double played_time = difftime( ct.time, playerInfo->playing_start_time);
                        playerInfo->player->time_played += played_time;
                        playerInfo->playing_start_time = ct.time;

                        current_players->delete( name );
                    }else{
                        Player* player = graphByIp->find( ip_port, name );

                        if( player == NULL ){
                            player = new Player;

                            player->ip = ip_port;
                            player->name = name;
                            player->messages = new LinkedList<CustomTime, Message>;
                            player->commands = new LinkedList<CustomTime, Message>;

                            graphByIp->add( ip_port, name, player);
                            graphByName->add( name, ip_port, player);
                        }

                        double played_time = difftime( ct.time, file_time );
                        player->time_played += played_time;
                    }

                    
                }
            break;

            case "GAME START":
                LinkedListNode<string, PlayerInfo> *temp = current_players->first;

                while( temp != NULL ){
                    PlayerInfo* playerInfo = temp->value;

                    double played_time = difftime( ct.time, playerInfo->playing_start_time );
                    playerInfo->player->time_played += played_time;
                    playerInfo->playing_start_time = ct.time;
                }

                delete current_players;
                current_players = new LinkedList<string, PlayerInfo>();
            break;

            case "GAME END":

            break;

        }
    }

}
void DefaultDecoder::readAndInsert(
    DirectedGraph<string,char,IP,Player> *& graphByName,
    DirectedGraph<IP,int,string,Player> *& graphByIp)
{

    LinkedListNode<CustomTime,file> *temp = files.first;
    LinkedList<string,PlayerInfo> *current_players = new LinkedList<string,PlayerInfo>();
    time_t last_file_time = 0;

    while( temp != NULL ){

        file *current = temp->value;
        string path = folderPath + "\\" + current->path;

        fstream rFile ( path.c_str(), fstream::in );
        string line;

        time_t file_time = current->date.time_t;

        while( getline(rFile, line) ){
            perfomPlayerOperation( 
            graphByName, 
            graphByIp, 
            line, 
            file_time,
            current_players
            );
        }

        double files_difference_time = difftime( file_time, last_file_time );

        if( files_difference_time > 86400 ){ // more than one day 
            LinkedListNode<string, PlayerInfo> *temp = current_players->first;

            while( temp != NULL ){
                PlayerInfo* playerInfo = temp->value;

                double played_time = difftime( ct.time, playerInfo->playing_start_time );
                playerInfo->player->time_played += played_time;
                playerInfo->playing_start_time = ct.time;
            }

            delete current_players;
            current_players = new LinkedList<string, PlayerInfo>();
        }

        last_file_time = file_time;
    }

}

DefaultDecoder::~DefaultDecoder(){}

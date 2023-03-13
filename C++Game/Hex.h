//
// Created by bhaa on 03/12/2021.
//

#ifndef HEX_H
#define HEX_H

typedef struct Hex
{
    int val; /* 0 =empty, 1=red player, 2=blue player.  */
    bool getIn; /* wen we use the recursion ~ to make sure that not get in hex more than once */ 
}Hex;

 

#endif //HEX_H
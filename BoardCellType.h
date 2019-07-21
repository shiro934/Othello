#pragma once
#ifndef INCLUDED_BOARD_CELL_TYPE_H_
#define INCLUDED_BOARD_CELL_TYPE_H_

enum BoardCellType {
	LOCATED_BLACK_STONE, 
	LOCATED_WHITE_STONE, 
	STONE_MAX, 
	EMPTY
};

static const unsigned int stoneColor[BoardCellType::STONE_MAX] = {
	0x333333,
	0xeeeeee
};
#endif // !INCLUDED_BOARD_CELL_TYPE_H_

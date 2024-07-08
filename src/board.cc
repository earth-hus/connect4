#include "board.hpp"

// you might need additional includes
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "board.hpp"
#include "cassert"
#include "cctype"
#include "iomanip"
#include "iostream"
#include "sstream"
#include "stdexcept"
#include "string"
using namespace std;
/**************************************************************************/
/* your function definitions                                              */
/**************************************************************************/

void InitBoard(Board& b) {
  // below was minimal to get tests to actually compile and given test case to
  // fail
  for (int row = 0; row < Board::kBoardHeight; row++) {
    for (int col = 0; col < Board::kBoardWidth; col++) {
      b.board[row][col] = DiskType::kEmpty;
    }
  }
}

void DropDiskToBoard(Board& b, DiskType disk, int col) {
  int counter = 0;
  if (!BoardLocationInBounds(0, col)) {
    throw runtime_error("Column Out Of Bounds");
  }
  for (int row = 0; row < Board::kBoardHeight; row++) {
    if (b.board[row][col] == DiskType::kEmpty) {
      b.board[row][col] = disk;
      counter++;
      break;
    }
  }
  if (counter == 0) {
    throw runtime_error("No Free Space in Column");
  }
}

// calls search for winner and jus states if its a winner
bool CheckForWinner(Board& b, DiskType disk) {
  // call search for winner 4 different
  if (SearchForWinner(b, disk, WinningDirection::kHorizontal)) {
    return true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kVertical)) {
    return true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kLeftDiag)) {
    return true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kRightDiag)) {
    return true;
  }
  return false;
}

bool LeftDiag(Board& b, DiskType disk) {
  for (int row = 0; row < Board::kBoardHeight; ++row) {
    for (int col = Board::kBoardWidth - 1; col >= 0; --col) {
      if (BoardLocationInBounds(row + 3, col - 3)) {
        // check for winner
        if (b.board[row][col] == disk && b.board[row + 1][col - 1] == disk &&
            b.board[row + 2][col - 2] == disk &&
            b.board[row + 3][col - 3] == disk) {
          return true;
        }
      }
    }
  }
  return false;
}

bool RightDiag(Board& b, DiskType disk) {  // disk can be any color
  for (int row = 0; row < Board::kBoardHeight; row++) {
    for (int col = 0; col < Board::kBoardWidth; col++) {
      if (BoardLocationInBounds(row + 3, col + 3)) {
        // check for winner
        if (b.board[row][col] == disk && b.board[row + 1][col + 1] == disk &&
            b.board[row + 2][col + 2] == disk &&
            b.board[row + 3][col + 3] == disk) {
          return true;
        }
      }
    }
  }
  return false;
}

bool Horizontal(Board& b, DiskType disk) {
  for (int row = 0; row < Board::kBoardHeight; row++) {
    for (int col = 0; col < Board::kBoardWidth; col++) {
      if (BoardLocationInBounds(row, col + 3)) {
        // check for winner
        if (b.board[row][col] == disk && b.board[row][col + 1] == disk &&
            b.board[row][col + 2] == disk && b.board[row][col + 3] == disk) {
          return true;
        }
      }
    }
  }
  return false;
}

bool Vertical(Board& b, DiskType disk) {
  for (int row = 0; row < Board::kBoardHeight; row++) {
    for (int col = 0; col < Board::kBoardWidth; col++) {
      if (BoardLocationInBounds(row + 3, col)) {
        // check for winner
        if (b.board[row][col] == disk && b.board[row + 1][col] == disk &&
            b.board[row + 2][col] == disk && b.board[row + 3][col] == disk) {
          return true;
        }
      }
    }
  }
  return false;
}

bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check) {
  // start from row 0, col 6. check to see if gogin up to the left is wihtin
  // bounds 10 lines of code
  // call helpr fucntions
  if (to_check == WinningDirection::kRightDiag) {
    if (RightDiag(b, disk)) {
      return true;
    }
  } else if (to_check == WinningDirection::kLeftDiag) {
    if (LeftDiag(b, disk)) {
      return true;
    }
  } else if (to_check == WinningDirection::kHorizontal) {
    if (Horizontal(b, disk)) {
      return true;
    }
  } else if (to_check == WinningDirection::kVertical) {
    if (Vertical(b, disk)) {
      return true;
    }
  }
  return false;
}

bool BoardLocationInBounds(int row, int col) {
  if (row < 0 || row >= Board::kBoardHeight) {  // row --> tall (height)
    return false;
  }
  if (col < 0 || col >= Board::kBoardWidth) {  // col --> wide
    return false;
  }
  return true;
}

/**************************************************************************/
/* provided to you                                                        */
/**************************************************************************/
std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  return ss.str();
}

std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}
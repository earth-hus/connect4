// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest               //
//  Date ......: 2022/02/07                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "board.hpp"
using namespace std;
#include <string>
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));

  // string visual = BoardToStr(student);
  // cout << visual << endl;

}

/////////////////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Throwing Errors", "[11111111]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board b;  // NOLINT
  InitBoard(b);
  REQUIRE(AreEqual(solution, b.board)); // true

  // Row and Column out of Range
  SECTION("row and column out of range") {
    REQUIRE_FALSE( BoardLocationInBounds(6, 7));
  }

  // are in range
  SECTION("row and column ARE in range") {
    REQUIRE( BoardLocationInBounds(0, 0));
  }

  //just column in range
  SECTION("just column in range, row out of range") {
    REQUIRE_FALSE( BoardLocationInBounds(8, 0));
  }

  //just row in range
  SECTION("just row in range, column out of range") {
    REQUIRE_FALSE( BoardLocationInBounds(0, 8));
  }

  // column out of bounds
  SECTION("column is out of bounds") {
    REQUIRE_THROWS(DropDiskToBoard(b, DiskType::kPlayer1, 8));
    REQUIRE_THROWS(DropDiskToBoard(b, DiskType::kPlayer1, -1));
    REQUIRE_THROWS(DropDiskToBoard(b, DiskType::kPlayer1, 7));
  }

  // throw if board is out column overflows & no free space
  SECTION("overflow column") {
    for(int i =0; i < Board::kBoardHeight; i++){
      DropDiskToBoard(b, DiskType::kPlayer1, 0);
    }
    REQUIRE_THROWS(DropDiskToBoard(b, DiskType::kPlayer1, 0));
  }
}
//---------------------------------------------------------------------------------
TEST_CASE("One in the middle - horzontal/vertical", "[22222]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board b;  // NOLINT
  InitBoard(b);
  REQUIRE(AreEqual(solution, b.board)); // true

  SECTION("horizontal one in middle") {
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer2, 2); // there is no winner
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 4);

    REQUIRE_FALSE(SearchForWinner(b,  DiskType::kPlayer1, WinningDirection::kHorizontal));
  }

  SECTION("vertical one in middle") {
    DropDiskToBoard(b, DiskType::kPlayer1, 5);
    DropDiskToBoard(b, DiskType::kPlayer1, 5);
    DropDiskToBoard(b, DiskType::kPlayer2, 5); // no winner
    DropDiskToBoard(b, DiskType::kPlayer1, 5);
    DropDiskToBoard(b, DiskType::kPlayer1, 5);

    REQUIRE_FALSE(SearchForWinner(b,  DiskType::kPlayer1, WinningDirection::kVertical));

  }
}


//----------------------------------------------------------------------------------------------------
TEST_CASE("Horzontal & Vertical directions", "[333333]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board b;  // NOLINT
  InitBoard(b);
  REQUIRE(AreEqual(solution, b.board)); // true
  

    DropDiskToBoard(b, DiskType::kPlayer1, 6);
    DropDiskToBoard(b, DiskType::kPlayer1, 5);
    DropDiskToBoard(b, DiskType::kPlayer1, 4);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
  

    DropDiskToBoard(b, DiskType::kPlayer2, 6);
    DropDiskToBoard(b, DiskType::kPlayer2, 5);
    DropDiskToBoard(b, DiskType::kPlayer2, 4);
    DropDiskToBoard(b, DiskType::kPlayer2, 3);


    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
  


    DropDiskToBoard(b, DiskType::kPlayer2, 2);
    DropDiskToBoard(b, DiskType::kPlayer2, 2);
    DropDiskToBoard(b, DiskType::kPlayer2, 2);
    DropDiskToBoard(b, DiskType::kPlayer2, 2);

    // string visual = BoardToStr(b);
    // cout << visual << endl;

    SECTION("Horizontal Player 1 winning direction") {
      REQUIRE( SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
    }
    SECTION("Horizontal Player 2 winning direction") {
      REQUIRE( SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
    }
    SECTION("Vertical Player 1 winning direction") {
      REQUIRE( SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
    }
    SECTION("Vertical Player 2 winning direction") {
      REQUIRE( SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical));
    }

    // string visual = BoardToStr(b);
    // cout << visual << endl;

}

//----------------------------------------------------------------------------------------------------
TEST_CASE("Right Diagnol Directions", "[4444]") {
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board b;  // NOLINT
  InitBoard(b);
  REQUIRE(AreEqual(solution, b.board)); // true

    // right diagnol
    DropDiskToBoard(b, DiskType::kPlayer1, 0);

    DropDiskToBoard(b, DiskType::kPlayer2, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);

    DropDiskToBoard(b, DiskType::kPlayer2, 2);
    DropDiskToBoard(b, DiskType::kPlayer2, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 2);

    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer2, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);

    DropDiskToBoard(b, DiskType::kPlayer1, 4);
    DropDiskToBoard(b, DiskType::kPlayer2, 4);
    DropDiskToBoard(b, DiskType::kPlayer1, 4);
    DropDiskToBoard(b, DiskType::kPlayer2, 4);

  SECTION("board was equal, now not equal") {
    REQUIRE_FALSE(AreEqual(solution, b.board)); // true
  }
  SECTION("right diagnol p1 winner") {
    REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
  }
  SECTION("right diagnol p2 winner") {
    REQUIRE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
  }
}

//----------------------------------------------------------------------------------------------------
TEST_CASE("No Right Diagnol Directions", "[5555]") {
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board b;  // NOLINT
  InitBoard(b);
  REQUIRE(AreEqual(solution, b.board)); // true

    // no right diagnol
    DropDiskToBoard(b, DiskType::kPlayer1, 0);

    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer2, 1);

    DropDiskToBoard(b, DiskType::kPlayer2, 2);
    DropDiskToBoard(b, DiskType::kPlayer2, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 2);

    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer2, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);

    DropDiskToBoard(b, DiskType::kPlayer1, 4);
    DropDiskToBoard(b, DiskType::kPlayer2, 4);
    DropDiskToBoard(b, DiskType::kPlayer1, 4);
    DropDiskToBoard(b, DiskType::kPlayer2, 4);


  SECTION("right diagnol p1 winner") {
    REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
  }
  SECTION("right diagnol p2 winner") {
    REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
  }
}

//----------------------------------------------------------------------------------------------------
TEST_CASE("Left Diagnol Directions", "[6666]") {
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board b;  // NOLINT
  InitBoard(b);
  REQUIRE(AreEqual(solution, b.board)); // true

  DropDiskToBoard(b, DiskType::kPlayer2, 5);

  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);

  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);

  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);

  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);

  SECTION("left diagnol p1 winner") {
    REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  }
  SECTION("left diagnol p2 winner") {
    REQUIRE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  }

}

//----------------------------------------------------------------------------------------------------
TEST_CASE("No Left Diagnol Directions", "[7777]") {
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board b;  // NOLINT
  InitBoard(b);
  REQUIRE(AreEqual(solution, b.board)); // true

  DropDiskToBoard(b, DiskType::kPlayer2, 5);

  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);

  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);

  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);

  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);

  SECTION("left diagnol p1 winner") {
    REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  }
  SECTION("left diagnol p2 winner") {
    REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  }

}



//----------------------------------------------------------------------------------------------------
TEST_CASE("All Directions Together", "[8888]") {
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board b;  // NOLINT
  InitBoard(b);
  REQUIRE(AreEqual(solution, b.board)); // true

  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);

  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);


  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);

  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);

  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);

  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);

  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  
  // left diagnol
  SECTION("left diagnol p1 winner") {
    REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  }
  SECTION("left diagnol p2 winner") {
    REQUIRE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  }

  // right diagnol
  SECTION("right diagnol p1 winner") {
    REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
  }
  SECTION("right diagnol p2 winner") {
    REQUIRE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
  }
  
  // horzontal & vertical
  SECTION("Horizontal Player 1 winning direction") {
    REQUIRE( SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
  }
  SECTION("Horizontal Player 2 winning direction") {
    REQUIRE( SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
  }


  SECTION("Vertical Player 1 winning direction") {
    REQUIRE( SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
  }
  SECTION("Vertical Player 2 winning direction") {
    REQUIRE( SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical));
  }

}


//----------------------------------------------------------------------------------------------------
TEST_CASE("All Directions for p1", "[99999]") {
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board b;  // NOLINT
  InitBoard(b);
  REQUIRE(AreEqual(solution, b.board)); // true
  
  for (int row = 0; row < kBoardHeight; row++) {
    for (int col = 0; col < kBoardWidth; col++) {
      DropDiskToBoard(b, DiskType::kPlayer1, col);
    }
  }

  SECTION("left diagnol p1 winner") {
    REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  }
  SECTION("left diagnol p2 winner") {
    REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  }

  // right diagnol
  SECTION("right diagnol p1 winner") {
    REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
  }
  SECTION("right diagnol p2 winner") {
    REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
  }
  
  // horzontal & vertical
  SECTION("Horizontal Player 1 winning direction") {
    REQUIRE( SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
  }
  SECTION("Horizontal Player 2 winning direction") {
    REQUIRE_FALSE( SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
  }
  SECTION("Vertical Player 1 winning direction") {
    REQUIRE( SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
  }
  SECTION("Vertical Player 2 winning direction") {
    REQUIRE_FALSE( SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical));
  }
}

//----------------------------------------------------------------------------------------------------
TEST_CASE("All Directions for p2", "[10101010]") {
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board b;  // NOLINT
  InitBoard(b);
  REQUIRE(AreEqual(solution, b.board)); // true
  
  for (int row = 0; row < kBoardHeight; row++) {
    for (int col = 0; col < kBoardWidth; col++) {
      DropDiskToBoard(b, DiskType::kPlayer2, col);
    }
  }

  SECTION("left diagnol p1 winner") {
    REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  }
  SECTION("left diagnol p2 winner") {
    REQUIRE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  }

  // right diagnol
  SECTION("right diagnol p1 winner") {
    REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
  }
  SECTION("right diagnol p2 winner") {
    REQUIRE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
  }
  
  // horzontal & vertical
  SECTION("Horizontal Player 1 winning direction") {
    REQUIRE_FALSE( SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
  }
  SECTION("Horizontal Player 2 winning direction") {
    REQUIRE( SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
  }
  SECTION("Vertical Player 1 winning direction") {
    REQUIRE_FALSE( SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
  }
  SECTION("Vertical Player 2 winning direction") {
    REQUIRE( SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical));
  }
}




//----------------------------------------------------------------------------------------------------
TEST_CASE("filled, but No one wins", "[131313]") {
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };

  Board b;  // NOLINT
  InitBoard(b);
  REQUIRE(AreEqual(solution, b.board)); // true

  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);

  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);

  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);

  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);

  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);

  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);

  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);



  SECTION("no left diagnol p1 winner") {
    REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  }
  SECTION("no left diagnol p2 winner") {
    REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  }

  // right diagnol
  SECTION("no right diagnol p1 winner") {
    REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
  }
  SECTION("no right diagnol p2 winner") {
    REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
  }
  
  // horzontal & vertical
  SECTION("no Horizontal Player 1 winning direction") {
    REQUIRE_FALSE( SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
  }
  SECTION("no Horizontal Player 2 winning direction") {
    REQUIRE_FALSE( SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
  }
  SECTION("no Vertical Player 1 winning direction") {
    REQUIRE_FALSE( SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
  }
  SECTION("no Vertical Player 2 winning direction") {
    REQUIRE_FALSE( SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical));
  }

}




//----------------------------------------------------------------------------------------------------
TEST_CASE("2's won, 1 horzontal", "[12121212]") {
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };

  Board b;  // NOLINT
  InitBoard(b);
  REQUIRE(AreEqual(solution, b.board)); // true


  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);

  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);

  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);

  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);

  SECTION("no left diagnol p1 winner") {
    REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  }
  SECTION("no left diagnol p2 winner") {
    REQUIRE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  }

  // right diagnol
  SECTION("no right diagnol p1 winner") {
    REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
  }
  SECTION("no right diagnol p2 winner") {
    REQUIRE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
  }
  
  // horzontal & vertical
  SECTION("no Horizontal Player 1 winning direction") {
    REQUIRE( SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
  }
  SECTION("no Horizontal Player 2 winning direction") {
    REQUIRE( SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
  }

  SECTION("no Vertical Player 1 winning direction") {
    REQUIRE_FALSE( SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
  }
  SECTION("no Vertical Player 2 winning direction") {
    REQUIRE( SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical));
  }

}


//----------------------------------------------------------------------------------------------------
TEST_CASE("cross", "[12121212]") {
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };

  Board b;  // NOLINT
  InitBoard(b);
  REQUIRE(AreEqual(solution, b.board)); // true


  
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);


  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);


  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);


  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);

  SECTION("no left diagnol p2 winner") {
    REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  }

  // right diagnol
  SECTION("no right diagnol p1 winner") {
    REQUIRE_FALSE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
  }


}
// REQUIRE_THROWS shoudl throws and exception - means throws an error
// or REQUIRE_THROWS_AS



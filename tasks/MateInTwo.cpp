#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/misc.h"

class MateInTwo {
public:
    void solve() {
        struct MoveLine {
            bool canMove;
            bool canCapture;
            vector<pii> moves;
            set<pii>& sources;

            MoveLine(bool canMove, bool canCapture, const vector<pii>& moves, set<pii>& sources) : canMove(
                    canMove), canCapture(canCapture), moves(moves), sources(sources) {}
        };
        set<pii> wholeBoard;
        for (int i : range(8)) {
            for (int j : range(8)) {
                wholeBoard.emplace(i, j);
            }
        }
        set<pii> secondRow;
        for (int i : range(8)) {
            secondRow.emplace(1, i);
        }
        auto buildLine = [](int dx, int dy) -> vector<pii> {
            int x = dx;
            int y = dy;
            vector<pii> res;
            for (int i : range(7)) {
                res.emplace_back(x, y);
                x += dx;
                y += dy;
            }
            return res;
        };
        MoveLine upLine(true, true, buildLine(1, 0), wholeBoard);
        MoveLine downLine(true, true, buildLine(-1, 0), wholeBoard);
        MoveLine rightLine(true, true, buildLine(0, 1), wholeBoard);
        MoveLine leftLine(true, true, buildLine(0, -1), wholeBoard);
        MoveLine upRightLine(true, true, buildLine(1, 1), wholeBoard);
        MoveLine upLeftLine(true, true, buildLine(1, -1), wholeBoard);
        MoveLine downRightLine(true, true, buildLine(-1, 1), wholeBoard);
        MoveLine downLeftLine(true, true, buildLine(-1, -1), wholeBoard);
        struct PieceType {
            vector<MoveLine> lines;
            bool isKing;

            PieceType(const vector<MoveLine>& lines, bool isKing) : lines(lines), isKing(isKing) {}
        };
        PieceType* king = new PieceType({
                                                MoveLine(true, true, {{1, 1}}, wholeBoard),
                                                MoveLine(true, true, {{1, 0}}, wholeBoard),
                                                MoveLine(true, true, {{1, -1}}, wholeBoard),
                                                MoveLine(true, true, {{0, 1}}, wholeBoard),
                                                MoveLine(true, true, {{-1, 1}}, wholeBoard),
                                                MoveLine(true, true, {{0, -1}}, wholeBoard),
                                                MoveLine(true, true, {{-1, -1}}, wholeBoard),
                                                MoveLine(true, true, {{-1, 0}}, wholeBoard)
                                        }, true);
        PieceType* queen = new PieceType({
                                                 upLine, downLine, leftLine, rightLine, upLeftLine, upRightLine,
                                                 downLeftLine, downRightLine
                                         }, false);
        PieceType* rook = new PieceType({
                                                upLine, downLine, leftLine, rightLine
                                        }, false);
        PieceType* bishop = new PieceType({
                                                  upLeftLine, upRightLine, downLeftLine, downRightLine
                                          }, false);
        PieceType* knight = new PieceType({
                                                  MoveLine(true, true, {{2, 1}}, wholeBoard),
                                                  MoveLine(true, true, {{2, -1}}, wholeBoard),
                                                  MoveLine(true, true, {{-2, 1}}, wholeBoard),
                                                  MoveLine(true, true, {{-2, -1}}, wholeBoard),
                                                  MoveLine(true, true, {{1, 2}}, wholeBoard),
                                                  MoveLine(true, true, {{1, -2}}, wholeBoard),
                                                  MoveLine(true, true, {{-1, 2}}, wholeBoard),
                                                  MoveLine(true, true, {{-1, -2}}, wholeBoard)
                                          }, false);
        PieceType* pawn = new PieceType({
                                                MoveLine(true, false, {{1, 0}}, wholeBoard),
                                                MoveLine(true, false, {{1, 0},
                                                                       {2, 0}}, secondRow),
                                                MoveLine(false, true, {{1, 1}}, wholeBoard),
                                                MoveLine(false, true, {{1, -1}}, wholeBoard)
                                        }, false);
        struct Cell {
            PieceType* piece;
            bool color;

            Cell(PieceType* piece, bool color) : piece(piece), color(color) {}
        };
        struct Board {
            arr2d<Cell> cells = arr2d<Cell>(8, 8, Cell(nullptr, false));

            Board flip() {
                Board result;
                for (int i : range(8)) {
                    for (int j : range(8)) {
                        if (cells(i, j).piece != nullptr) {
                            result.cells(7 - i, j) = Cell(cells(i, j).piece, !cells(i, j).color);
                        }
                    }
                }
                return result;
            }

            bool isBlackChecked() {
                for (int i : range(8)) {
                    for (int j : range(8)) {
                        if (cells(i, j).piece == nullptr || !cells(i, j).color) {
                            continue;
                        }
                        for (const MoveLine& line : cells(i, j).piece->lines) {
                            if (!line.canCapture) {
                                continue;
                            }
                            if (line.sources.count({i, j}) == 0) {
                                continue;
                            }
                            for (const pii& shift : line.moves) {
                                int ni = i + shift.first;
                                int nj = j + shift.second;
                                if (!isValidCell(ni, nj, 8, 8)) {
                                    break;
                                }
                                if (cells(ni, nj).piece != nullptr) {
                                    if (cells(ni, nj).piece->isKing && !cells(ni, nj).color) {
                                        return true;
                                    }
                                    break;
                                }
                            }
                        }
                    }
                }
                return false;
            }

            vector<Board> allMoves() {
                vector<Board> result;
                for (int i : range(8)) {
                    for (int j : range(8)) {
                        if (cells(i, j).piece == nullptr || !cells(i, j).color) {
                            continue;
                        }
                        for (const MoveLine& line : cells(i, j).piece->lines) {
                            if (line.sources.count({i, j}) == 0) {
                                continue;
                            }
                            for (const pii& shift : line.moves) {
                                int ni = i + shift.first;
                                int nj = j + shift.second;
                                if (!isValidCell(ni, nj, 8, 8)) {
                                    break;
                                }
                                bool isCapture = false;
                                if (cells(ni, nj).piece != nullptr) {
                                    if (!line.canCapture || cells(ni, nj).color) {
                                        break;
                                    }
                                    isCapture = true;
                                } else if (!line.canMove) {
                                    break;
                                }
                                Board after = flip();
                                after.cells(7 - i, j).piece = nullptr;
                                after.cells(7 - ni, nj).piece = cells(i, j).piece;
                                after.cells(7 - ni, nj).color = false;
                                if (!after.isBlackChecked()) {
                                    result.push_back(after);
                                }
                                if (isCapture) {
                                    break;
                                }
                            }
                        }
                    }
                }
                return result;
            }

            bool isWhiteCheckmated() {
                return flip().isBlackChecked() && allMoves().empty();
            }
        };

        Board start;
        for (int i : range(8)) {
            for (int j : range(8)) {
                char p = in.readChar();
                char c = in.readChar();
                if (p == '-') {
                    continue;
                }
                start.cells(7 - i, j).color = c == 'w';
                if (p == 'K') {
                    start.cells(7 - i, j).piece = king;
                } else if (p == 'Q') {
                    start.cells(7 - i, j).piece = queen;
                } else if (p == 'R') {
                    start.cells(7 - i, j).piece = rook;
                } else if (p == 'B') {
                    start.cells(7 - i, j).piece = bishop;
                } else if (p == 'N') {
                    start.cells(7 - i, j).piece = knight;
                } else if (p == 'P') {
                    start.cells(7 - i, j).piece = pawn;
                }
            }
        }
        auto canMateInOne = [](Board board) -> bool {
            auto moves = board.allMoves();
            for (Board& b : moves) {
                if (b.isWhiteCheckmated()) {
                    return true;
                }
            }
            return false;
        };
        auto canAvoidMateInOne = [&](Board board) -> bool {
            auto moves = board.allMoves();
            if (moves.empty()) {
                return true;
            }
            for (Board& b : moves) {
                if (!canMateInOne(b)) {
                    return true;
                }
            }
            return false;
        };
        auto canMateInTwo = [&](Board board) -> bool {
            auto moves = board.allMoves();
            for (Board& b : moves) {
                if (b.isWhiteCheckmated() || !canAvoidMateInOne(b)) {
                    return true;
                }
            }
            return false;
        };
        out.printLine(canMateInTwo(start) ? "YES" : "NO");
    }
};

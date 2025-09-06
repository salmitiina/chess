#include "rook.hh"

#include <vector>

Rook::Rook(ChessColor color)
    : ChessPiece(color, PieceType::ROOK, "rook")
{

}

set<Coord> Rook::get_allowed_moves(const ChessBoard &board) const
{
    set<Coord> moves;

    Coord from = get_position();
    ChessColor ownColor = get_color();

    // Neljä suuntaa: ylös, alas, vasen, oikea
    const std::vector<Coord> directions = {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1}
    };

    for (const Coord& dir : directions) {
        Coord current = from;
        while (true) {
            current.row += dir.row;
            current.col += dir.col;

            if (!board.coord_in_bounds(current)) {
                break;
            }

            auto piece = board.get_piece_at(current);
            if (piece == nullptr) {
                moves.insert(current);
            }
            else if (piece->get_color() != ownColor) {
                // vihollinen -> voi syödä, mutta ei jatketa
                moves.insert(current);
                break;
            }
            else {
                break;
            }
        }
    }

    return moves;
}

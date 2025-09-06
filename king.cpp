#include "king.hh"

#include <vector>

King::King(ChessColor color)
    : ChessPiece(color, PieceType::KING, "king")
{

}


set<Coord> King::get_allowed_moves(const ChessBoard &board) const
{
    set<Coord> moves;

    Coord from = get_position();
    ChessColor ownColor = get_color();

    // Kaikki 8 suuntaa
    const std::vector<Coord> directions = {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1},
        {-1, -1},
        {-1, 1},
        {1, -1},
        {1, 1}
    };

    for (const Coord& dir : directions) {
        Coord dest = {from.row + dir.row, from.col + dir.col};

        if (!board.coord_in_bounds(dest)) {
            continue;
        }

        auto piece = board.get_piece_at(dest);
        if (piece == nullptr || piece->get_color() != ownColor) {
            moves.insert(dest);
        }
    }

    return moves;
}

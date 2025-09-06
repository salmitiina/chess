#include "bishop.hh"

#include <vector>

Bishop::Bishop(ChessColor color)
    :ChessPiece(color, PieceType::BISHOP, "bishop")
{

}

set<Coord> Bishop::get_allowed_moves(const ChessBoard &board) const
{
    set<Coord> moves;

    Coord from = get_position();
    ChessColor ownColor = get_color();

    // Vinottaiset suunnat: ylös-oikea, alas-oikea, alas-vasen, ylös-vasen
    const std::vector<Coord> directions = {
        {-1, 1},
        {1, 1},
        {1, -1},
        {-1, -1}
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

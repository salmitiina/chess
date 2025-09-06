/*
 * Tiedosto: mainwindow.cpp
 * Kuvaus: Toteuttaa MainWindow-luokan, joka hallitsee graafista shakkipeliä
 * Tekijä: Tiina Salmi
 * Opiskelijatunnus: K392596
 * Sähköposti: tiina.k.salmi@tuni.fi
 * Projekti: student/07/chess
 */

#include "mainwindow.hh"
#include "chesspiece.hh"
#include "bishop.hh"
#include "king.hh"
#include "pawn.hh"
#include "queen.hh"
#include "rook.hh"
#include "knight.hh"

#include <QMessageBox>

/**
 * @brief MainWindow::MainWindow
 * Luo peliruudukon ja alustaa pelin aloitustilaan.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    centralWidget_ = new QWidget(this);
    setCentralWidget(centralWidget_);

    gridLayout_ = new QGridLayout(centralWidget_);
    buttons_.resize(8);

    createBoard();
    setupInitialPosition();
    initializeBoard();
}

/**
 * @brief MainWindow::~MainWindow
 * Tyhjä purkaja.
 */
MainWindow::~MainWindow()
{
}

/**
 * @brief MainWindow::createBoard
 * Luo käyttöliittymään 8x8 ruudukon, asettaa pohjavärit ja yhdistää napit tapahtumankäsittelyyn.
 */
void MainWindow::createBoard()
{
    for ( int row = 0; row < 8; ++row )
    {
        buttons_[row].resize(8);

        for ( int col = 0; col < 8; ++col )
        {
            QPushButton* button = new QPushButton(this);

            button->setFixedSize(64, 64);
            button->setStyleSheet(( row + col ) % 2 == 0
                                  ? "background-color: white;"
                                  : "background-color: gray;");

            gridLayout_->addWidget(button, row, col);
            buttons_[row][col] = button;

            connect(button, &QPushButton::clicked, this, [=]() {
                handleSquareClick(row, col);
            });
        }
    }

}

/**
 * @brief MainWindow::initializeBoard
 * Päivittää käyttöliittymässä nappuloiden kuvat shakkilaudan tilan mukaan.
 */
void MainWindow::initializeBoard()
{
    const QString squares[2] = {"wt", "bl"};

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            QPushButton* button = buttons_[row][col];
            button->setIcon(QIcon()); // tyhjennä ensin

            std::shared_ptr<ChessPiece> piece = board_.get_piece_at(row, col);
            if (piece)
            {
                QString color = (piece->get_color() == WHITE) ? "wt" : "bl";
                QString type = QString::fromStdString(piece->get_name());  // esim. "pawn"
                QString squareColor = squares[(row + col) % 2];

                QString iconPath = QString(":/pieces/%1-%2-on-%3.png").arg(color, type, squareColor);

                button->setIcon(QIcon(iconPath));
                button->setIconSize(QSize(64, 64));
            }
        }
    }
}


/**
 * @brief MainWindow::setupInitialPosition
 * Asettaa kaikki nappulat aloituspaikoille logiikkalaudalle.
 */
void MainWindow::setupInitialPosition()
{
    // Aseta sotilaat
    for (int col = 0; col < 8; ++col) {
        auto whitePawn = std::make_shared<Pawn>(WHITE);
        whitePawn->set_position({6, col});
        board_.set_piece(6, col, whitePawn);

        auto blackPawn = std::make_shared<Pawn>(BLACK);
        blackPawn->set_position({1, col});
        board_.set_piece(1, col, blackPawn);
    }

    // Aseta upseerit (rivit 7 ja 0)
    const std::array<std::shared_ptr<ChessPiece>, 8> whiteRow = {
        std::make_shared<Rook>(WHITE),
        std::make_shared<Knight>(WHITE),
        std::make_shared<Bishop>(WHITE),
        std::make_shared<Queen>(WHITE),
        std::make_shared<King>(WHITE),
        std::make_shared<Bishop>(WHITE),
        std::make_shared<Knight>(WHITE),
        std::make_shared<Rook>(WHITE),
    };

    const std::array<std::shared_ptr<ChessPiece>, 8> blackRow = {
        std::make_shared<Rook>(BLACK),
        std::make_shared<Knight>(BLACK),
        std::make_shared<Bishop>(BLACK),
        std::make_shared<Queen>(BLACK),
        std::make_shared<King>(BLACK),
        std::make_shared<Bishop>(BLACK),
        std::make_shared<Knight>(BLACK),
        std::make_shared<Rook>(BLACK),
    };

    for (int col = 0; col < 8; ++col) {
        whiteRow[col]->set_position({7, col});
        board_.set_piece(7, col, whiteRow[col]);

        blackRow[col]->set_position({0, col});
        board_.set_piece(0, col, blackRow[col]);
    }
}

/**
 * @brief MainWindow::resetSquareHighlight
 * Palauttaa annetun ruudun taustavärin alkuperäiseksi (valkoinen tai harmaa).
 * @param row Rivi
 * @param col Sarake
 */
void MainWindow::handleSquareClick(int row, int col)
{
    if (gameOver_)
    {
        return;
    }

    if (!pieceSelected_)
    {
        std::shared_ptr<ChessPiece> piece = board_.get_piece_at(row, col);
        if ( !piece || piece->get_color() != currentTurn_ )
        {
            return;
        }

        // Palautetaan perusvärit laudalle
        resetSquareHighlight();

        //Korosta valitun nappulan lailliset siirrot
        std::set<Coord> allowedMoves = piece->get_allowed_moves(board_);
        highlightSquares(allowedMoves);

        // Ensimmäinen klikkaus: valitaan ruutu
        selectedSquare_ = qMakePair(row, col);
        pieceSelected_ = true;

    }
    else
    {
        // Toinen klikkaus: yritetään siirtää nappula
        int fromRow = selectedSquare_.first;
        int fromCol = selectedSquare_.second;

        // Hae nappula logiikasta
        std::shared_ptr<ChessPiece> piece = board_.get_piece_at(fromRow, fromCol);

        // Estä siirto, jos kohderuudussa on oma nappula
        std::shared_ptr<ChessPiece> targetPiece = board_.get_piece_at(row, col);

        if (targetPiece && targetPiece->get_type() == KING) {
            gameOver_ = true;

            QString winner = (currentTurn_ == WHITE) ? "Valkoinen" : "Musta";
            QMessageBox::information(this, "Peli päättyi", winner + " voitti pelin!");

            return;
        }

        Coord toCoord = {row, col};

        if (targetPiece && targetPiece->get_color() == piece->get_color())
        {
            resetSquareHighlight();
            pieceSelected_ = false;
            return;
        }

        auto allowed = piece->get_allowed_moves(board_);

        if (allowed.find(toCoord) == allowed.end()) {
            // Laiton siirto
            resetSquareHighlight();
            pieceSelected_ = false;
            return;
        }

        // Aseta nappula uuteen ruutuun
        board_.set_piece(row, col, piece);

        // Tyhjennä lähtöruutu
        board_.set_piece(fromRow, fromCol, nullptr);

        piece->set_position(toCoord);

        // Päivitä grafiikka
        initializeBoard();

        // Palauta lähtöruudun väri
        resetSquareHighlight();
        pieceSelected_ = false;
        currentTurn_ = (currentTurn_ == WHITE ? BLACK : WHITE);
    }
}

void MainWindow::highlightSquares(const std::set<Coord>& coords)
{
    for (const Coord& c : coords) {
        int row = c.row;
        int col = c.col;

        if (row >= 0 && row < 8 && col >= 0 && col < 8 && buttons_[row][col]) {
            buttons_[row][col]->setStyleSheet("background-color: lightblue;");
        }
    }
}

void MainWindow::resetSquareHighlight()
{
    // 8x8-lauta
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            // varmistus: nappi on olemassa
            if (!buttons_.isEmpty() &&
                row < buttons_.size() &&
                col < buttons_[row].size() &&
                buttons_[row][col] != nullptr) {

                // palauta ruudukon perusvärit (vaihda omiin väreihisi)
                const QString baseColor = ((row + col) % 2 == 0)
                                              ? "white"   // vaalea
                                              : "gray";  // tumma
                buttons_[row][col]->setStyleSheet("background-color: " + baseColor + ";");
            }
        }
    }
}

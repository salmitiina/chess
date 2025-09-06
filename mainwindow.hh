#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

/**
 * Tiedosto: mainwindow.hh
 * Kuvaus: Määrittelee MainWindow-luokan, joka hallitsee shakkipelin graafista käyttöliittymää
 * Tekijä: Tiina Salmi
 * Projekti: student/07/chess
 */

#include "chessboard.hh"
#include "chesspiece.hh"

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QVector>
#include <QPair>

/**
 * @brief MainWindow-luokka
 * Luo graafisen shakkilaudan ja hallitsee käyttäjän vuorovaikutusta pelin kanssa.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /**
     * @brief MainWindow
     * Luo uuden käyttöliittymäikkunan ja alustaa pelilaudan.
     * @param parent QMainWindown yläolio (yleensä nullptr)
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief ~MainWindow
     * Tuhoaa ikkunan.
     */
    ~MainWindow();


private:

    QWidget* centralWidget_;
    QGridLayout *gridLayout_;
    QVector<QVector<QPushButton*>> buttons_;
    QPair<int, int> selectedSquare_;
    ChessBoard board_;
    ChessColor currentTurn_ = WHITE;
    bool pieceSelected_ = false;
    bool gameOver_ = false;

    /**
     * @brief createBoard
     * Luo 8x8 ruudukon käyttöliittymään ja alustaa napit oikeilla väreillä.
     */
    void createBoard();

    /**
     * @brief initializeBoard
     * Päivittää käyttöliittymään pelilaudan tilanteen (nappulat ja ikonit).
     */
    void initializeBoard();

    /**
     * @brief setupInitialPosition
     * Asettaa nappulat aloituspaikoilleen logiikkalaudalle.
     */
    void setupInitialPosition();

    /**
     * @brief handleSquareClick
     * Käsittelee käyttäjän klikkauksen tiettyyn ruutuun.
     * @param row Klikatun ruudun rivi
     * @param col Klikatun ruudun sarake
     */
    void handleSquareClick(int row, int col);

    /**
     * @brief highLightSquares
     * Korostaa valitut ruudut
     * @param lista korostetuista ruuduista
     */
    void highlightSquares(const std::set<Coord>& coords);

    /**
     * @brief resetSquareHighlight
     * Palauttaa annetun ruudun taustavärin alkuperäiseksi.
     */
    void resetSquareHighlight();
};

#endif // MAINWINDOW_HH

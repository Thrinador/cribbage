/**class Board {
public:

    Board(Player* p1, Player* p2) : player1(p1), player2(p2), deck(new Deck()), turn(true) {}
    Board(Player* p1, Player* p2, bool turn) : player1(p1), player2(p2), deck(new Deck()), turn(turn) {}
    

    GameStats play();

    Player* getPlayer1() { return player1; }
    Player* getPlayer2() { return player2; }

    void resetGame(bool turn);


    int checkForPeggingPoints(vector<Card> pastCards, int sum);
    void deal();
    bool hasWon() { return (player1->getScore() > 120 || player2->getScore() > 120); }
    bool inARow(vector<int> v);
    void pegging(Score &p1, Score &p2);
    void calculateScores(Score &p1Score, Score &p2Score, Score &cribScore);
    void printTable(Score p1Scores, Score p2Scores, Score cribScore);
    void printWinner();
    void getCribCards();
    void cut();

    Deck *deck;
    Player *player1;
    Player *player2;
    GameStats stats;
    bool turn;
    Card cutCard;
    vector<Card> crib;
};**/

fn checkForPeggingPoints(past_cards: Vec<Card>, sum: usize) -> usize {

}

fn deal();
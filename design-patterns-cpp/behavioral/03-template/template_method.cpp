#include <iostream>
#include <string>
using namespace std;

class Game
{
public:
	explicit Game(int number_of_players) : m_number_of_players(number_of_players)
	{
	}

	void run()
	{
		start();
		while (!haveWinner()) {
			takeTurn();
		}
		std::cout << "Player " << getWinner() << " wins.\n";
	}

protected:
	virtual void start() = 0;
	virtual bool haveWinner() = 0;
	virtual void takeTurn() = 0;
	virtual int getWinner() = 0;

	int m_current_player{ 0 };
	int m_number_of_players;
};

class Chess : public Game
{
public:
	explicit Chess() : Game{ 2 } {}

protected:
	void start() override
	{
		std::cout << "Starting a game of chess with " << m_number_of_players << " players\n";
	}

	bool haveWinner() override
	{
		return m_turns == m_max_turns;
	}

	void takeTurn() override
	{
		std::cout << "Turn " << m_turns << " taken by player " << m_current_player << "\n";
		m_turns++;
		m_current_player = (m_current_player + 1) % m_number_of_players;
	}

	int getWinner() override
	{
		return m_current_player;
	}

private:
	int m_turns{ 0 }, m_max_turns{ 10 };
};

int main(int argc, char **argv)
{
	Chess chess;
	chess.run();

	return 0;
}

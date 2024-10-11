#include <iostream>
#include <cstdlib>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>

using namespace std;

int AssignUserID()
{
	int userid;
	int readid, readdifficulty;
	bool found = true;
	srand(time(NULL));
	ifstream ReadFile;
	ReadFile.open("ID.txt");
	do
	{
		found = false;
		userid = (rand() % 999999) + 1;
		while (!ReadFile.eof())
		{
			ReadFile >> readid;
			ReadFile >> readdifficulty;
			if (readid == userid)
			{
				found = true;
				break;
			}
		}
	} while (found == true);
	return userid;
}

int CheckUserID(int &userID)
{
	int difficulty;
	int temp;
	bool isFound = false;
	ifstream ReadID;
	ofstream WriteID;
	ReadID.open("ID.txt");
	WriteID.open("ID.txt", ios::app);
	while (!ReadID.eof())
	{
		ReadID >> temp;
		ReadID >> difficulty;
		if (temp == userID)
		{
			isFound = true;
			break;
		}
	}
	ReadID.close();
	if (isFound == true)
	{
		cout << "You are a Returning User" << endl;
		if (difficulty == 1)
		{
			cout << "You can play difficulty 1" << endl;
		}
		else if (difficulty == 2)
		{
			cout << "You can play both difficulties" << endl;
		}
	}
	else if (isFound == false)
	{
		cout << "Not a Returning User" << endl;
		cout << "You can only play difficulty 1" << endl;
		userID = AssignUserID();
		WriteID << userID << " " << 1 << endl;
		difficulty = 1;
		cout << "Your User ID is " << userID << endl;
	}
	WriteID.close();
	return difficulty;
}

void UpdateID(bool won, int userID)
{
	if (won == true)
	{
		int readID, readDifficulty;
		ifstream ReadFile;
		ofstream WriteFile;
		ReadFile.open("ID.txt");
		WriteFile.open("DuplicateID.txt");
		while (!ReadFile.eof())
		{
			ReadFile >> readID;
			ReadFile >> readDifficulty;
			if (readID != userID)
			{
				WriteFile << readID << " ";
				WriteFile << readDifficulty << endl;
			}
		}
		WriteFile << userID << " " << 2 << endl;
		WriteFile.close();
		ReadFile.close();
		WriteFile.open("ID.txt", ios::trunc);
		WriteFile.close();
		ReadFile.open("DuplicateID.txt");
		WriteFile.open("ID.txt");
		while (!ReadFile.eof())
		{
			ReadFile >> readID;
			ReadFile >> readDifficulty;
			WriteFile << readID << " " << readDifficulty << endl;
		}
		ReadFile.close();
		WriteFile.close();
		WriteFile.open("DuplicateID.txt", ios::trunc);
		WriteFile.close();
	}
}

void GenerateBoard(int Board[][15])
{
	for (int index = 0; index <= 19; index++)
	{
		for (int count = 0; count <= 14; count++)
		{
			Board[index][count] = 0;
		}
	}
}

void GenerateBoard2(int Board[][12])
{
	for (int index = 0; index <= 11; index++)
	{
		for (int count = 0; count <= 11; count++)
		{
			Board[index][count] = 0;
		}
	}
}

void InitialiseTable(bool Table[][15])
{
	for (int index = 0; index <= 19; index++)
	{
		for (int count = 0; count <= 14; count++)
		{
			Table[index][count] = false;
		}
	}
}

void InitialiseTable2(bool Table[][12])
{
	for (int index = 0; index <= 11; index++)
	{
		for (int count = 0; count <= 11; count++)
		{
			Table[index][count] = false;
		}
	}
}
	
void AddBombs(int Board[][15], bool Table[][15])
{
	srand(time(0));
	int number, row , column;
	int count = 0;
	while (count < 45)
	{
		row = rand() % 20;
		column = rand() % 15;
		number = rand() % 4;
		if (number == 1 && Board[row][column] == 0 && Table[row][column] == 0)
		{
			Board[row][column] = 9;
			count = count + 1;
		}
	}
}

void AddBombs2(int Board[][12], bool Table[][12])
{
	srand(time(0));
	int number, row, column;
	int count = 0;
	while (count < 25)
	{
		row = rand() % 12;
		column = rand() % 12;
		number = rand() % 4;
		if (number == 1 && Board[row][column] == 0 && Table[row][column] == 0)
		{
			Board[row][column] = 9;
			count = count + 1;
		}
	}
}

void AddNumbers(int Board[][15], bool Table[][15])
{
	int row, column;
	for (row = 0; row < 20; row++)
	{
		for (column = 0; column < 15; column++)
		{
			if (Board[row][column] == 9)
			{
				continue;
			}
			if (Board[row + 1][column] == 9 && row != 19)
			{
				Board[row][column]++;
			}
			if (Board[row - 1][column] == 9 && row != 0)
			{
				Board[row][column]++;
			}
			if (Board[row][column + 1] == 9 && column != 14)
			{
				Board[row][column]++;
			}
			if (Board[row][column - 1] == 9)
			{
				if (column != 0)
				{
					Board[row][column]++;
				}
			}
			if (Board[row - 1][column - 1] == 9)
			{
				if (row != 0 && column != 0)
				{
					Board[row][column]++;
				}
			}
			if (Board[row - 1][column + 1] == 9)
			{
				if (row != 0 && column != 14)
				{
					Board[row][column]++;
				}
			}
			if(Board[row + 1][column - 1] == 9)
			{
				if (row != 19 && column != 0)
				{
					Board[row][column]++;
				}
			}
			if (Board[row + 1][column + 1] == 9)
			{
				if(row != 19 && column != 14)
				Board[row][column]++;
			}
		}
	}
}

void AddNumbers2(int Board[][12], bool Table[][12])
{
	int row, column;
	for (row = 0; row < 12; row++)
	{
		for (column = 0; column < 12; column++)
		{
			if (Board[row][column] == 9)
			{
				continue;
			}
			if (Board[row + 1][column] == 9 && row != 11)
			{
				Board[row][column]++;
			}
			if (Board[row - 1][column] == 9 && row != 0)
			{
				Board[row][column]++;
			}
			if (Board[row][column + 1] == 9 && column != 11)
			{
				Board[row][column]++;
			}
			if (Board[row][column - 1] == 9)
			{
				if (column != 0)
				{
					Board[row][column]++;
				}
			}
			if (Board[row - 1][column - 1] == 9)
			{
				if (row != 0 && column != 0)
				{
					Board[row][column]++;
				}
			}
			if (Board[row - 1][column + 1] == 9)
			{
				if (row != 0 && column != 11)
				{
					Board[row][column]++;
				}
			}
			if (Board[row + 1][column - 1] == 9)
			{
				if (row != 11 && column != 0)
				{
					Board[row][column]++;
				}
			}
			if (Board[row + 1][column + 1] == 9)
			{
				if (row != 11 && column != 11)
					Board[row][column]++;
			}
		}
	}
}

void Open(int Board[][15], bool Table[][15], int row, int column)
{
		for (int i = row + 1; Board[i][column] >= 0 && Board[i][column] <= 8 && i < 20; i++)
		{
			for (int j = column + 1; Board[i][j] >= 0 && Board[i][j] <= 8 && j < 15; j++)
			{
				Table[i][j] = true;
				if (Board[i][j] > 0 && Board[i][j] <= 8)
				{
					break;
				}
			}
			if (Board[i][column] > 0 && Board[i][column] <= 8)
			{
				Table[i][column] = true;
				break;
			}
		}

		for (int i = row - 1; Board[i][column] >= 0 && Board[i][column] <= 8 && i > -1; i--)
		{
			for (int j = column + 1; Board[i][j] == 0 && Board[i][j] <= 8 && j < 15; j++)
			{
				Table[i][j] = true;
				if (Board[i][j] > 0 && Board[i][j] <= 8)
				{
					break;
				}
			}
			if (Board[i][column] > 0 && Board[i][column] <= 8)
			{
				Table[i][column] = true;
				break;
			}
		}

		for (int i = row + 1; Board[i][column] >= 0 && Board[i][column] <= 8 && i < 20; i++)
		{
			for (int j = column - 1; Board[i][j] >= 0 && Board[i][j] <= 8 && j > -1; j--)
			{
				Table[i][j] = true;
				if (Board[i][j] > 0 && Board[i][j] <= 8)
				{
					break;
				}
			}
			if (Board[i][column] > 0 && Board[i][column] <= 8)
			{
				Table[i][column] = true;
				break;
			}
		}

		for (int i = row - 1; Board[i][column] >= 0 && Board[i][column] <= 8 && i > -1; i--)
		{
			for (int j = column - 1; Board[i][j] >= 0 && Board[i][j] <= 8 && j > -1; j--)
			{
				Table[i][j] = true;
				if (Board[i][j] > 0 && Board[i][j] <= 8)
				{
					break;
				}
			}
			if (Board[i][column] > 0 && Board[i][column] <= 8)
			{
				Table[i][column] = true;
				break;
			}
		}

		for (int i = row + 1; Board[i][column] >= 0 && Board[i][column] <= 8 && i < 20; i++)
		{
			Table[i][column] = true;
			if (Board[i][column] > 0 && Board[i][column] <= 8)
			{
				break;
			}
		}

		for (int i = row - 1; Board[i][column] >= 0 && Board[i][column] <= 8 && i > -1; i--)
		{
			Table[i][column] = true;
			if (Board[i][column] > 0 && Board[i][column] <= 8)
			{
				break;
			}
			
		}

		for (int j = column + 1; Board[row][j] >= 0 && Board[row][j] <= 8 && j < 15; j++)
		{
			Table[row][j] = true;
			if (Board[row][j] > 0 && Board[row][j] <= 8)
			{
				break;
			}
		}

		for (int j = column - 1; Board[row][j] >= 0 && Board[row][j] <= 8 && j > -1; j--)
		{
			Table[row][j] = true;
			if (Board[row][j] > 0 && Board[row][j] <= 8)
			{
				break;
			}
		}
	}

void Open2(int Board[][12], bool Table[][12], int row, int column)
{
	for (int i = row + 1; Board[i][column] >= 0 && Board[i][column] <= 8 && i < 11; i++)
	{
		for (int j = column + 1; Board[i][j] >= 0 && Board[i][j] <= 8 && j < 11; j++)
		{
			Table[i][j] = true;
			if (Board[i][j] > 0 && Board[i][j] <= 8)
			{
				break;
			}
		}
		if (Board[i][column] > 0 && Board[i][column] <= 8)
		{
			Table[i][column] = true;
			break;
		}
	}

	for (int i = row - 1; Board[i][column] >= 0 && Board[i][column] <= 8 && i > -1; i--)
	{
		for (int j = column + 1; Board[i][j] == 0 && Board[i][j] <= 8 && j < 11; j++)
		{
			Table[i][j] = true;
			if (Board[i][j] > 0 && Board[i][j] <= 8)
			{
				break;
			}
		}
		if (Board[i][column] > 0 && Board[i][column] <= 8)
		{
			Table[i][column] = true;
			break;
		}
	}

	for (int i = row + 1; Board[i][column] >= 0 && Board[i][column] <= 8 && i < 11; i++)
	{
		for (int j = column - 1; Board[i][j] >= 0 && Board[i][j] <= 8 && j > -1; j--)
		{
			Table[i][j] = true;
			if (Board[i][j] > 0 && Board[i][j] <= 8)
			{
				break;
			}
		}
		if (Board[i][column] > 0 && Board[i][column] <= 8)
		{
			Table[i][column] = true;
			break;
		}
	}

	for (int i = row - 1; Board[i][column] >= 0 && Board[i][column] <= 8 && i > -1; i--)
	{
		for (int j = column - 1; Board[i][j] >= 0 && Board[i][j] <= 8 && j > -1; j--)
		{
			Table[i][j] = true;
			if (Board[i][j] > 0 && Board[i][j] <= 8)
			{
				break;
			}
		}
		if (Board[i][column] > 0 && Board[i][column] <= 8)
		{
			Table[i][column] = true;
			break;
		}
	}

	for (int i = row + 1; Board[i][column] >= 0 && Board[i][column] <= 8 && i < 11; i++)
	{
		Table[i][column] = true;
		if (Board[i][column] > 0 && Board[i][column] <= 8)
		{
			break;
		}
	}

	for (int i = row - 1; Board[i][column] >= 0 && Board[i][column] <= 8 && i > -1; i--)
	{
		Table[i][column] = true;
		if (Board[i][column] > 0 && Board[i][column] <= 8)
		{
			break;
		}

	}

	for (int j = column + 1; Board[row][j] >= 0 && Board[row][j] <= 8 && j < 11; j++)
	{
		Table[row][j] = true;
		if (Board[row][j] > 0 && Board[row][j] <= 8)
		{
			break;
		}
	}

	for (int j = column - 1; Board[row][j] >= 0 && Board[row][j] <= 8 && j > -1; j--)
	{
		Table[row][j] = true;
		if (Board[row][j] > 0 && Board[row][j] <= 8)
		{
			break;
		}
	}
}

bool CheckWinner(int Board[][15], bool Table[][15])
{
	bool won = false;
	int count = 0;
	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 15; column++)
		{
			if (Table[row][column] == false)
			{
				count++;
			}
		}
	}
	if (count <= 45)
	{
		won = true;
	}
	return won;
}

bool CheckWinner2(int Board[][12], bool Table[][12])
{
	bool won = false;
	int count = 0;
	for (int row = 0; row < 12; row++)
	{
		for (int column = 0; column < 12; column++)
		{
			if (Table[row][column] == false)
			{
				count++;
			}
		}
	}
	if (count <= 25)
	{
		won = true;
	}
	return won;
}

bool Play(int Board[][15], bool Table[][15] , int &lives , int row , int column , long long int & score , int & turn )
{
	bool bomb = false;
	Table[row - 1][column - 1] = true;
	if (Board[row - 1][column - 1] == 9)
	{
		lives = lives - 1;
		if (lives == 0)
		{
			for (int index = 0; index < 20; index++)
			{
				for (int count = 0;count < 15; count++)
				{
					Table[index][count] = true;
				}
			}
			bomb = true;
		}
		else
		{
			score = score / 2;
			turn--;
		}
	}
	else
	{
		row--;
		column--;
		Open(Board, Table, row, column);
		if (Board[row][column] == -1)
		{
			lives = lives + 1;
		}
		score = (score + turn) * 2;
	}
	return bomb;
}

bool Play2(int Board[][12], bool Table[][12], int& lives, int row, int column , long long int &score , int & turn)
{
	bool bomb = false;
	Table[row - 1][column - 1] = true;
	if (Board[row - 1][column - 1] == 9)
	{
		lives = lives - 1;
		if (lives == 0)
		{
			for (int index = 0; index < 12; index++)
			{
				for (int count = 0;count < 12; count++)
				{
					Table[index][count] = true;
				}
			}
			bomb = true;
		}
		else
		{
			score = score / 2;
			turn--;
		}
	}
	else
	{
		row--;
		column--;
		Open2(Board, Table, row, column);
		if (Board[row][column] == -1)
		{
			lives = lives + 1;
		}
		score = (score + turn) * 2;
	}
	return bomb;
}

void AddLife(int Board[][15] , bool Table[][15])
{
	srand(time(0));
	int number, row, column;
	int count = 0;
	while (count < 1)
	{
		row = rand() % 20;
		column = rand() % 15;
		number = rand() % 4;
		if (number == 1 && Board[row][column] == 0 && Table[row][column] == false)
		{
			Board[row][column] = -1;
			count = count + 1;
		}
	}
}

void AddLife2(int Board[][12], bool Table[][12])
{
	srand(time(0));
	int number, row, column;
	int count = 0;
	while (count < 1)
	{
		row = rand() % 12;
		column = rand() % 12;
		number = rand() % 4;
		if (number == 1 && Board[row][column] == 0 && Table[row][column] == false)
		{
			Board[row][column] = -1;
			count = count + 1;
		}
	}
}

void main()
{
	sf::SoundBuffer buffer3;
	buffer3.loadFromFile("IntroMusic.flac");
	sf::Sound intromusic;
	intromusic.setBuffer(buffer3);
	sf::RenderWindow startwindow(sf::VideoMode(400, 600), "Minesweeper" , sf::Style::Close | sf::Style::Titlebar);
	sf::Texture start;
	start.loadFromFile("StartScreen.jpg");
	start.setSmooth(true);
	sf::Sprite StartScreen;
	StartScreen.setTexture(start);
	sf::Font font;
	font.loadFromFile("arial.ttf");
	sf::Text startgame("Press S to continue", font, 30);
	startgame.setFillColor(sf::Color::Black);
	startgame.setPosition(sf::Vector2f(40.0f, 475.0f));
	intromusic.play();
	intromusic.setLoop(100);
	while (startwindow.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event1;
		while (startwindow.pollEvent(event1))
		{
			// "close requested" event: we close the window
			if (event1.type == sf::Event::Closed)
				startwindow.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			startwindow.close();
		}
		// clear the window with black color
		startwindow.clear();
		// draw everything here...
		// window.draw(...);
		startwindow.draw(StartScreen);
		startwindow.draw(startgame);
		startwindow.display();
	}
	int difficulty = 1;
	sf::RenderWindow middlewindow(sf::VideoMode(400, 600), "Minesweeper", sf::Style::Close | sf::Style::Titlebar);
	sf:: Text GameIntroduction2 ("To win, open all boxes which do not \ncontain a bomb." , font , 20) ;
	sf:: Text GameIntroduction3("To make things easy, we are giving you \nan additional life, if you open a \nspecific box during the game.", font, 20);
	sf:: Text GameIntroduction4 ("To make things difficult, we are not \ngiving you the option to flag boxes.", font , 20);
	sf:: Text GameIntroduction5 ("You can save progress of 1 difficulty at \na time and upon completing the game, \nit does not matter whether you win or\nlose, the save data is deleted.", font , 20);
	sf:: Text GameIntroduction6("There are 2 difficulties.", font, 20);
	sf:: Text GameIntroduction7("In Difficulty 1 , there is a 12*12 matrix \nconsisting 25 bombs", font, 20);
	sf:: Text GameIntroduction8("In Difficulty 2 , there is a 20*15\nmatrix consisting 45 bombs", font, 20);
	sf:: Text AskDifficulty1("Press 1 to play difficulty 1", font, 20);
	sf:: Text AskDifficulty2("Press 2 to play difficulty 2", font, 20);
	sf::Color Color(0, 0, 110 , 255);
	GameIntroduction2.setFillColor(Color);
	GameIntroduction3.setFillColor(Color);
	GameIntroduction4.setFillColor(Color);
	GameIntroduction5.setFillColor(Color);
	GameIntroduction6.setFillColor(Color);
	GameIntroduction7.setFillColor(Color);
	GameIntroduction8.setFillColor(Color);
	AskDifficulty1.setFillColor(Color);
	AskDifficulty2.setFillColor(Color);
	GameIntroduction2.setStyle(sf::Text::Bold);
	GameIntroduction3.setStyle(sf::Text::Bold);
	GameIntroduction4.setStyle(sf::Text::Bold);
	GameIntroduction5.setStyle(sf::Text::Bold);
	GameIntroduction6.setStyle(sf::Text::Bold);
	GameIntroduction7.setStyle(sf::Text::Bold);
	GameIntroduction8.setStyle(sf::Text::Bold);
	AskDifficulty1.setStyle(sf::Text::Bold);
	AskDifficulty2.setStyle(sf::Text::Bold);
	GameIntroduction2.setPosition(sf::Vector2f(0.0f, 125.0f));
	GameIntroduction3.setPosition(sf::Vector2f(0.0f, 175.0f));
	GameIntroduction4.setPosition(sf::Vector2f(0.0f, 250.0f));
	GameIntroduction5.setPosition(sf::Vector2f(0.0f, 300.0f));
	GameIntroduction6.setPosition(sf::Vector2f(0.0f, 400.0f));
	GameIntroduction7.setPosition(sf::Vector2f(0.0f, 425.0f));
	GameIntroduction8.setPosition(sf::Vector2f(0.0f, 475.0f));
	AskDifficulty1.setPosition(sf::Vector2f(0.0f, 525.0f));
	AskDifficulty2.setPosition(sf::Vector2f(0.0f, 550.0f));
	sf::Texture secondwallpaper;
	secondwallpaper.loadFromFile("Secondwindow.png");
	secondwallpaper.setSmooth(true);
	sf::Sprite Wallpaper2;
	Wallpaper2.setTexture(secondwallpaper);
	int userid;
	int diff;
	cout << "If you are a returning user , Enter your UserID" << endl;
	cin >> userid;
	diff = CheckUserID(userid);
	while (middlewindow.isOpen())
	{
	
		if (diff == 2)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				difficulty = 1;
				middlewindow.close();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			{
				difficulty = 2;
				middlewindow.close();
			}
		}
		else if (diff == 1)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				difficulty = 1;
				middlewindow.close();
			}
		}
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event2;
		while (middlewindow.pollEvent(event2))
		{
			// "close requested" event: we close the window
			if (event2.type == sf::Event::Closed)
				middlewindow.close();
		}
		// clear the window with black color
		middlewindow.clear();
		// draw everything here...
		// window.draw(...);
		middlewindow.draw(Wallpaper2);
		middlewindow.draw(GameIntroduction2);
		middlewindow.draw(GameIntroduction3);
		middlewindow.draw(GameIntroduction4);
		middlewindow.draw(GameIntroduction5);
		middlewindow.draw(GameIntroduction6);
		middlewindow.draw(GameIntroduction7);
		middlewindow.draw(GameIntroduction8);
		if (diff == 2)
		{
			middlewindow.draw(AskDifficulty1);
			middlewindow.draw(AskDifficulty2);
		}
		else if (diff == 1)
		{
			middlewindow.draw(AskDifficulty1);
		}
		middlewindow.display();
	}
	int Board[20][15];
	bool Table[20][15];
	int Board2[12][12];
	bool Table2[12][12];
	int lives = 1;
	long long int score = 0;
	int turn = -1;
	bool isBomb = false, won = false;
	string showscore = to_string(score);
	sf::Text scorestring("Score = ", font, 15);
	sf::Text score1(showscore, font, 15);
	scorestring.setPosition(sf::Vector2f(0.0f, 450.0f));
	score1.setPosition(sf::Vector2f(60.0f, 450.0f));
	sf::Text save("Press S to save your current progress", font, 15);
	save.setPosition(sf::Vector2f(0.0f, 525.0f));
	sf::Texture tile;
	tile.loadFromFile("Tile.png");
	tile.setSmooth(true);
	sf::Texture bomb;
	bomb.loadFromFile("Bomb.png");
	bomb.setSmooth(true);
	sf::Texture opentile;
	opentile.loadFromFile("OpenTile.png");
	sf::Texture digit1;
	digit1.loadFromFile("Digit1.png");
	digit1.setSmooth(true);
	sf::Texture digit2;
	digit2.loadFromFile("Digit2.jpg");
	digit2.setSmooth(true);
	sf::Texture digit3;
	digit3.loadFromFile("Digit3.jpg");
	digit3.setSmooth(true);
	sf::Texture digit4;
	digit4.loadFromFile("Digit4.jpg");
	digit4.setSmooth(true);
	sf::Texture digit5;
	digit5.loadFromFile("Digit5.jpg");
	digit5.setSmooth(true);
	sf::Texture digit6;
	digit6.loadFromFile("Digit6.jpg");
	digit6.setSmooth(true);
	sf::Texture digit7;
	digit7.loadFromFile("Digit7.jpg");
	digit7.setSmooth(true);
	sf::Texture digit8;
	digit8.loadFromFile("Digit8.jpg");
	digit8.setSmooth(true);
	sf::Texture heart;
	heart.loadFromFile("Heart.png");
	heart.setSmooth(true);
	sf::Texture background;
	background.loadFromFile("Background.jpg");
	background.setSmooth(true);
	sf::SoundBuffer buffer;
	buffer.loadFromFile("mixkit-8-bit-bomb-explosion-2811.wav");
	sf::Sound explosionsound;
	explosionsound.setBuffer(buffer);
	sf::SoundBuffer buffer2;
	buffer2.loadFromFile("click.wav");
	sf::Sound clicksound;
	clicksound.setBuffer(buffer2);
	sf::Sprite TileBoard[20][15];
	sf::Sprite TileBoard2[12][12];
	sf::Sprite Background;
	Background.setTexture(background);
	int TileXCoordinate = 20;
	int TileYCoordinate = 20;
	srand(time(0));
	int MouseXCoordinate;
	int MouseYCoordinate;
	bool Gameover = false;
	bool usesavefile = false;
	int readdifficulty , readuserid;
	ofstream SaveFile;
	ifstream ReadFile;
	ReadFile.open("Save.txt");
	ReadFile >> readdifficulty;
	ReadFile >> readuserid;
	if (readdifficulty == difficulty && readuserid == userid)
	{
		ReadFile >> turn >> score >> lives;
		usesavefile = true;
		if (difficulty == 2)
		{
			for (int index = 0; index < 20; index++)
			{
				for (int count = 0; count < 15; count++)
				{
					ReadFile >> Board[index][count];
				}
			}
			for (int index = 0; index < 20; index++)
			{
				for (int count = 0; count < 15; count++)
				{
					ReadFile >> Table[index][count];
				}
			}
			for (int index = 0; index < 20; index++)
			{
				TileXCoordinate = 0;
				for (int count = 0; count < 15; count++)
				{
					TileXCoordinate = TileXCoordinate + 20;
					if (Table[index][count] == false)
					{
						TileBoard[index][count].setTexture(tile);
					}
					else if (Table[index][count] == true)
					{
						if (Board[index][count] == 0)
						{
							TileBoard[index][count].setTexture(opentile);
						}
						else if (Board[index][count] == 1)
						{
							TileBoard[index][count].setTexture(digit1);
						}
						else if (Board[index][count] == 2)
						{
							TileBoard[index][count].setTexture(digit2);
						}
						else if (Board[index][count] == 3)
						{
							TileBoard[index][count].setTexture(digit3);
						}
						else if (Board[index][count] == 4)
						{
							TileBoard[index][count].setTexture(digit4);
						}
						else if (Board[index][count] == 5)
						{
							TileBoard[index][count].setTexture(digit5);
						}
						else if (Board[index][count] == 6)
						{
							TileBoard[index][count].setTexture(digit6);
						}
						else if (Board[index][count] == 7)
						{
							TileBoard[index][count].setTexture(digit7);
						}
						else if (Board[index][count] == 8)
						{
							TileBoard[index][count].setTexture(digit8);
						}
						else if (Board[index][count] == 9)
						{
							TileBoard[index][count].setTexture(bomb);
						}
						else if (Board[index][count] == -1)
						{
							TileBoard[index][count].setTexture(heart);
						}
					}
					TileBoard[index][count].setPosition(TileXCoordinate, TileYCoordinate);
				}
				TileYCoordinate = TileYCoordinate + 20;
			}
		}
		if (difficulty == 1)
		{
			for (int index = 0; index < 12; index++)
			{
				for (int count = 0; count < 12; count++)
				{
					ReadFile >> Board2[index][count];
				}
			}
			for (int index = 0; index < 12; index++)
			{
				for (int count = 0; count < 12; count++)
				{
					ReadFile >> Table2[index][count];
				}
			}
			for (int index = 0; index < 12; index++)
			{
				TileXCoordinate = 0;
				for (int count = 0; count < 12; count++)
				{
					TileXCoordinate = TileXCoordinate + 20;
					if (Table2[index][count] == false)
					{
						TileBoard2[index][count].setTexture(tile);
					}
					else if (Table2[index][count] == true)
					{
						if (Board2[index][count] == 0)
						{
							TileBoard2[index][count].setTexture(opentile);
						}
						else if (Board2[index][count] == 1)
						{
							TileBoard2[index][count].setTexture(digit1);
						}
						else if (Board2[index][count] == 2)
						{
							TileBoard2[index][count].setTexture(digit2);
						}
						else if (Board2[index][count] == 3)
						{
							TileBoard2[index][count].setTexture(digit3);
						}
						else if (Board2[index][count] == 4)
						{
							TileBoard2[index][count].setTexture(digit4);
						}
						else if (Board2[index][count] == 5)
						{
							TileBoard2[index][count].setTexture(digit5);
						}
						else if (Board2[index][count] == 6)
						{
							TileBoard2[index][count].setTexture(digit6);
						}
						else if (Board2[index][count] == 7)
						{
							TileBoard2[index][count].setTexture(digit7);
						}
						else if (Board2[index][count] == 8)
						{
							TileBoard2[index][count].setTexture(digit8);
						}
						else if (Board2[index][count] == 9)
						{
							TileBoard2[index][count].setTexture(bomb);
						}
						else if (Board2[index][count] == -1)
						{
							TileBoard2[index][count].setTexture(heart);
						}
					}
					TileBoard2[index][count].setPosition(TileXCoordinate, TileYCoordinate);
				}
				TileYCoordinate = TileYCoordinate + 20;
			}
		}
		showscore = to_string(score);
		score1.setString(showscore);
	}
	ReadFile.close();
	sf::RenderWindow window(sf::VideoMode(400, 600), "Minesweeper", sf::Style::Close | sf::Style::Titlebar);
	while (window.isOpen())
	{
		intromusic.stop();
		if (difficulty == 2)
		{
			sf::Text BombMessage("Bombs = 45", font, 15);
			BombMessage.setPosition(sf::Vector2f(300.0f, 450.0f));
			if (Gameover == false)
			{
				if (turn == -1)
				{
					GenerateBoard(Board);
					InitialiseTable(Table);
					for (int index = 0; index < 20; index++)
					{
						TileXCoordinate = 0;
						for (int count = 0; count < 15; count++)
						{
							TileXCoordinate = TileXCoordinate + 20;
							TileBoard[index][count].setTexture(tile);
							TileBoard[index][count].setPosition(TileXCoordinate, TileYCoordinate);
						}
						TileYCoordinate = TileYCoordinate + 20;
					}
					turn++;
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && turn == 0)
				{
					do
					{
						sf::Vector2i mouseposition = sf::Mouse::getPosition(window);
						MouseXCoordinate = mouseposition.x / 20;
						MouseYCoordinate = mouseposition.y / 20;
					} while ((MouseYCoordinate < 1 || MouseYCoordinate > 20) || (MouseXCoordinate < 1 || MouseXCoordinate > 15));
					Table[MouseYCoordinate - 1][MouseXCoordinate - 1] = true;
					AddBombs(Board, Table);
					AddNumbers(Board, Table);
					AddLife(Board, Table);
					Open(Board, Table, MouseYCoordinate - 1, MouseXCoordinate - 1);
					TileXCoordinate = 20;
					TileYCoordinate = 20;
					for (int index = 0; index < 20; index++)
					{
						TileXCoordinate = 0;
						for (int count = 0; count < 15; count++)
						{
							TileXCoordinate = TileXCoordinate + 20;
							if (Table[index][count] == false)
							{
								TileBoard[index][count].setTexture(tile);
							}
							else if (Table[index][count] == true)
							{
								if (Board[index][count] == 0)
								{
									TileBoard[index][count].setTexture(opentile);
								}
								else if (Board[index][count] == 1)
								{
									TileBoard[index][count].setTexture(digit1);
								}
								else if (Board[index][count] == 2)
								{
									TileBoard[index][count].setTexture(digit2);
								}
								else if (Board[index][count] == 3)
								{
									TileBoard[index][count].setTexture(digit3);
								}
								else if (Board[index][count] == 4)
								{
									TileBoard[index][count].setTexture(digit4);
								}
								else if (Board[index][count] == 5)
								{
									TileBoard[index][count].setTexture(digit5);
								}
								else if (Board[index][count] == 6)
								{
									TileBoard[index][count].setTexture(digit6);
								}
								else if (Board[index][count] == 7)
								{
									TileBoard[index][count].setTexture(digit7);
								}
								else if (Board[index][count] == 8)
								{
									TileBoard[index][count].setTexture(digit8);
								}
								else if (Board[index][count] == 9)
								{
									TileBoard[index][count].setTexture(bomb);
								}
								else if (Board[index][count] == -1)
								{
									TileBoard[index][count].setTexture(heart);
								}
							}
							TileBoard[index][count].setPosition(TileXCoordinate, TileYCoordinate);
						}
						TileYCoordinate = TileYCoordinate + 20;
					}
					turn++;
					clicksound.play();
					score = 1;
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && turn > 0)
				{
					showscore = to_string(score);
					score1.setString(showscore);
					do
					{
						sf::Vector2i mouseposition = sf::Mouse::getPosition(window);
						MouseXCoordinate = mouseposition.x / 20;
						MouseYCoordinate = mouseposition.y / 20;
					} while ((MouseYCoordinate < 1 || MouseYCoordinate > 20) || (MouseXCoordinate < 1 || MouseXCoordinate > 15));
					if (Table[MouseYCoordinate - 1][MouseXCoordinate - 1] == false)
					{
						turn++;
						isBomb = Play(Board, Table, lives, MouseYCoordinate, MouseXCoordinate , score , turn);
						TileXCoordinate = 20;
						TileYCoordinate = 20;
						for (int index = 0; index < 20; index++)
						{
							TileXCoordinate = 0;
							for (int count = 0; count < 15; count++)
							{
								TileXCoordinate = TileXCoordinate + 20;
								if (Table[index][count] == false)
								{
									TileBoard[index][count].setTexture(tile);
								}
								else if (Table[index][count] == true)
								{
									if (Board[index][count] == 0)
									{
										TileBoard[index][count].setTexture(opentile);
									}
									else if (Board[index][count] == 1)
									{
										TileBoard[index][count].setTexture(digit1);
									}
									else if (Board[index][count] == 2)
									{
										TileBoard[index][count].setTexture(digit2);
									}
									else if (Board[index][count] == 3)
									{
										TileBoard[index][count].setTexture(digit3);
									}
									else if (Board[index][count] == 4)
									{
										TileBoard[index][count].setTexture(digit4);
									}
									else if (Board[index][count] == 5)
									{
										TileBoard[index][count].setTexture(digit5);
									}
									else if (Board[index][count] == 6)
									{
										TileBoard[index][count].setTexture(digit6);
									}
									else if (Board[index][count] == 7)
									{
										TileBoard[index][count].setTexture(digit7);
									}
									else if (Board[index][count] == 8)
									{
										TileBoard[index][count].setTexture(digit8);
									}
									else if (Board[index][count] == 9)
									{
										TileBoard[index][count].setTexture(bomb);
									}
									else if (Board[index][count] == -1)
									{
										TileBoard[index][count].setTexture(heart);
									}
								}
								TileBoard[index][count].setPosition(TileXCoordinate, TileYCoordinate);
							}
							TileYCoordinate = TileYCoordinate + 20;
						}
						if (isBomb == true)
						{
							explosionsound.play();
						}
						else
						{
							clicksound.play();
						}
					}
					if (lives == 0)
					{
						Gameover = true;
					}
				}
			}
				// check all the window's events that were triggered since the last iteration of the loop
				sf::Event event;
				while (window.pollEvent(event))
				{
					// "close requested" event: we close the window
					if (event.type == sf::Event::Closed)
						window.close();
				}
			// clear the window with black color
			window.clear();
			// draw everything here...
			// window.draw(...);
			window.draw(Background);
			window.draw(scorestring);
			window.draw(score1);
			window.draw(BombMessage);
			if (turn > 0 && Gameover == false)
			{
				window.draw(save);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					SaveFile.open("Save.txt");
					SaveFile << difficulty << endl << userid << endl << turn << endl << score << endl << lives << endl;
					for (int index = 0; index < 20; index++)
					{
						for (int count = 0; count < 15; count++)
						{
							SaveFile << Board[index][count] << " ";
						}
						SaveFile << endl;
					}
					SaveFile << endl;
					for (int index = 0; index < 20; index++)
					{
						for (int count = 0; count < 15; count++)
						{
							SaveFile << Table[index][count] << " ";
						}
						SaveFile << endl;
					}
					SaveFile.close();
				}
			}
			for (int index = 0; index < 20; index++)
			{
				for (int count = 0; count < 15; count++)
				{
					window.draw(TileBoard[index][count]);
				}
			}
			if (isBomb == true && lives == 0)
			{
				Gameover = true;
				string LoseMessage = "You Lost";
				sf::Text Message(LoseMessage, font, 80);
				Message.setPosition(sf::Vector2f(0.0f, 150.0f));
				Message.setFillColor(sf::Color::Magenta);
				window.draw(Message);
			}
			else if (CheckWinner(Board, Table) == true)
			{
				Gameover = true;
				string WinMessage = "You Won";
				sf::Text Won(WinMessage, font, 80);
				Won.setPosition(sf::Vector2f(0.0f, 150.0f));
				Won.setFillColor(sf::Color::Magenta);
				window.draw(Won);
			}
			if (Gameover == true)
			{
				string NewGameMessage = "Press N to start a new game";
				sf::Text NewGame(NewGameMessage, font, 15);
				NewGame.setPosition(sf::Vector2f(0.0f, 475.0f));
				NewGame.setFillColor(sf::Color::White);
				window.draw(NewGame);
				string Close = "Press X to close the game";
				sf::Text CloseMessage(Close, font, 15);
				CloseMessage.setPosition(sf::Vector2f(0.0f, 500.0f));
				CloseMessage.setFillColor(sf::Color::White);
				window.draw(CloseMessage);
				string Previous = "Press P to play difficulty 1";
				sf::Text ChangeDifficulty(Previous, font, 15);
				ChangeDifficulty.setPosition(sf::Vector2f(0.0f, 525.0f));
				ChangeDifficulty.setFillColor(sf::Color::White);
				window.draw(ChangeDifficulty);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
				{
					window.close();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
				{
					Gameover = false;
					turn = -1;
					lives = 1;
					score = 0;
					isBomb = false;
					TileXCoordinate = 20;
					TileYCoordinate = 20;
					showscore = to_string(score);
					score1.setString(showscore);
					window.draw(scorestring);
					window.draw(score1);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
				{
					Gameover = false;
					turn = -1;
					lives = 1;
					score = 0;
					isBomb = false;
					TileXCoordinate = 20;
					TileYCoordinate = 20;
					showscore = to_string(score);
					score1.setString(showscore);
					window.draw(scorestring);
					window.draw(score1);
					difficulty = 1;
				}
			}
		}
		else if (difficulty == 1)
		{
			sf::Text BombMessage2("Bombs = 25", font, 15);
			BombMessage2.setPosition(sf::Vector2f(300.0f, 450.0f));
			if (Gameover == false)
			{
				if (turn == -1)
				{
					GenerateBoard2(Board2);
					InitialiseTable2(Table2);
					for (int index = 0; index < 12; index++)
				{
					TileXCoordinate = 0;
					for (int count = 0; count < 12; count++)
					{
						TileXCoordinate = TileXCoordinate + 20;
						TileBoard2[index][count].setTexture(tile);
						TileBoard2[index][count].setPosition(TileXCoordinate, TileYCoordinate);
					}
					TileYCoordinate = TileYCoordinate + 20;
				}
					turn++;
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && turn == 0)
			{
				do
				{
					sf::Vector2i mouseposition = sf::Mouse::getPosition(window);
					MouseXCoordinate = mouseposition.x / 20;
					MouseYCoordinate = mouseposition.y / 20;
				} while ((MouseYCoordinate < 1 || MouseYCoordinate > 12) || (MouseXCoordinate < 1 || MouseXCoordinate > 12));
				Table2[MouseYCoordinate - 1][MouseXCoordinate - 1] = true;
				AddBombs2(Board2, Table2);
				AddNumbers2(Board2, Table2);
				AddLife2(Board2, Table2);
				Open2(Board2, Table2, MouseYCoordinate - 1, MouseXCoordinate - 1);
				TileXCoordinate = 20;
				TileYCoordinate = 20;
				for (int index = 0; index < 12; index++)
				{
					TileXCoordinate = 0;
					for (int count = 0; count < 12; count++)
					{
						TileXCoordinate = TileXCoordinate + 20;
						if (Table2[index][count] == false)
						{
							TileBoard2[index][count].setTexture(tile);
						}
						else if (Table2[index][count] == true)
						{
							if (Board2[index][count] == 0)
							{
								TileBoard2[index][count].setTexture(opentile);
							}
							else if (Board2[index][count] == 1)
							{
								TileBoard2[index][count].setTexture(digit1);
							}
							else if (Board2[index][count] == 2)
							{
								TileBoard2[index][count].setTexture(digit2);
							}
							else if (Board2[index][count] == 3)
							{
								TileBoard2[index][count].setTexture(digit3);
							}
							else if (Board2[index][count] == 4)
							{
								TileBoard2[index][count].setTexture(digit4);
							}
							else if (Board2[index][count] == 5)
							{
								TileBoard2[index][count].setTexture(digit5);
							}
							else if (Board2[index][count] == 6)
							{
								TileBoard2[index][count].setTexture(digit6);
							}
							else if (Board2[index][count] == 7)
							{
								TileBoard2[index][count].setTexture(digit7);
							}
							else if (Board2[index][count] == 8)
							{
								TileBoard2[index][count].setTexture(digit8);
							}
							else if (Board2[index][count] == 9)
							{
								TileBoard2[index][count].setTexture(bomb);
							}
							else if (Board2[index][count] == -1)
							{
								TileBoard2[index][count].setTexture(heart);
							}
						}
						TileBoard2[index][count].setPosition(TileXCoordinate, TileYCoordinate);
					}
					TileYCoordinate = TileYCoordinate + 20;
				}
				turn++;
				clicksound.play();
				score = 1;
			}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && turn > 0)
				{
					showscore = to_string(score);
					score1.setString(showscore);
					do
					{
						sf::Vector2i mouseposition = sf::Mouse::getPosition(window);
						MouseXCoordinate = mouseposition.x / 20;
						MouseYCoordinate = mouseposition.y / 20;
					} while ((MouseYCoordinate < 1 || MouseYCoordinate > 12) || (MouseXCoordinate < 1 || MouseXCoordinate > 12));
					if (Table2[MouseYCoordinate - 1][MouseXCoordinate - 1] == false)
					{
						turn++;
						isBomb = Play2(Board2, Table2, lives, MouseYCoordinate, MouseXCoordinate , score , turn);
						TileXCoordinate = 20;
						TileYCoordinate = 20;
						for (int index = 0; index < 12; index++)
					{
						TileXCoordinate = 0;
						for (int count = 0; count < 12; count++)
						{
							TileXCoordinate = TileXCoordinate + 20;
							if (Table2[index][count] == false)
							{
								TileBoard2[index][count].setTexture(tile);
							}
							else if (Table2[index][count] == true)
							{
								if (Board2[index][count] == 0)
								{
									TileBoard2[index][count].setTexture(opentile);
								}
								else if (Board2[index][count] == 1)
								{
									TileBoard2[index][count].setTexture(digit1);
								}
								else if (Board2[index][count] == 2)
								{
									TileBoard2[index][count].setTexture(digit2);
								}
								else if (Board2[index][count] == 3)
								{
									TileBoard2[index][count].setTexture(digit3);
								}
								else if (Board2[index][count] == 4)
								{
									TileBoard2[index][count].setTexture(digit4);
								}
								else if (Board2[index][count] == 5)
								{
									TileBoard2[index][count].setTexture(digit5);
								}
								else if (Board2[index][count] == 6)
								{
									TileBoard2[index][count].setTexture(digit6);
								}
								else if (Board2[index][count] == 7)
								{
									TileBoard2[index][count].setTexture(digit7);
								}
								else if (Board2[index][count] == 8)
								{
									TileBoard2[index][count].setTexture(digit8);
								}
								else if (Board2[index][count] == 9)
								{
									TileBoard2[index][count].setTexture(bomb);
								}
								else if (Board2[index][count] == -1)
								{
									TileBoard2[index][count].setTexture(heart);
								}
							}
							TileBoard2[index][count].setPosition(TileXCoordinate, TileYCoordinate);
						}
						TileYCoordinate = TileYCoordinate + 20;
					}
						if (isBomb == true)
						{
							explosionsound.play();
						}
						else
						{
							clicksound.play();
						}
					}
				}
			}
			// check all the window's events that were triggered since the last iteration of the loop
			sf::Event event;
			while (window.pollEvent(event))
			{
				// "close requested" event: we close the window
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}	
			}

			// clear the window with black color
			window.clear();
			// draw everything here...
			// window.draw(...);
			window.draw(Background);
			window.draw(scorestring);
			window.draw(score1);
			window.draw(BombMessage2);
			if (turn > 0 && Gameover == false)
			{
				window.draw(save);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					SaveFile.open("Save.txt");
					SaveFile << difficulty << endl << userid << endl << turn << endl << score << endl << lives << endl;
					for (int index = 0; index < 12; index++)
					{
						for (int count = 0; count < 12; count++)
						{
							SaveFile << Board2[index][count] << " ";
						}
						SaveFile << endl;
					}
					SaveFile << endl;
					for (int index = 0; index < 12; index++)
					{
						for (int count = 0; count < 12; count++)
						{
							SaveFile << Table2[index][count] << " ";
						}
						SaveFile << endl;
					}
					SaveFile.close();
				}
			}
			for (int index = 0; index < 12; index++)
			{
				for (int count = 0; count < 12; count++)
				{
					window.draw(TileBoard2[index][count]);
				}
			}
			if (isBomb == true && lives == 0)
			{
				Gameover = true;
				string LoseMessage = "You Lost";
				sf::Text Message(LoseMessage, font, 80);
				Message.setPosition(sf::Vector2f(0.0f, 250.0f));
				Message.setFillColor(sf::Color::Magenta);
				window.draw(Message);
			}
			else if (CheckWinner2(Board2, Table2))
			{
				UpdateID(true, userid);
				Gameover = true;
				string WinMessage = "You Won";
				sf::Text Won(WinMessage, font, 80);
				Won.setPosition(sf::Vector2f(0.0f, 250.0f));
				Won.setFillColor(sf::Color::Magenta);
				window.draw(Won);
				difficulty = 2;
			}
			if (Gameover == true)
			{
				if (readuserid == userid)
				{
					SaveFile.open("Save.txt");
					SaveFile.clear();
					SaveFile.close();
				}
				string NewGameMessage = "Press N to start a new game";
				sf::Text NewGame(NewGameMessage, font, 15);
				NewGame.setPosition(sf::Vector2f(0.0f, 475.0f));
				NewGame.setFillColor(sf::Color::White);
				window.draw(NewGame);
				string Close = "Press X to close the game";
				sf::Text CloseMessage(Close, font, 15);
				CloseMessage.setPosition(sf::Vector2f(0.0f, 500.0f));
				CloseMessage.setFillColor(sf::Color::White);
				window.draw(CloseMessage);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
				{
					window.close();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
				{
					Gameover = false;
					turn = -1;
					lives = 1;
					score = 0;
					isBomb = false;
					TileXCoordinate = 20;
					TileYCoordinate = 20;
					showscore = to_string(score);
					score1.setString(showscore);
					window.draw(scorestring);
					window.draw(score1);
				}
			}
		}
			window.display();
	}
}

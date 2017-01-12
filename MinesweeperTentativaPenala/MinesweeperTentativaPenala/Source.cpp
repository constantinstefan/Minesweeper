#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <iostream>
#include <sstream>
#define vecin coada_x[prim] + deplasare_x[i]][coada_y[prim] + deplasare_y[i]
using namespace sf;
using namespace std;

int pixel = 32;
int matrice[40][40];
int afisare[40][40];
int vizitat[40][40];

int contor;
int nrSteaguri = 0;
int coada_x[1000];
int coada_y[1000];
int nrMaximBombe = 10;
int contorAfisate;

int size_x = 9;
int size_y = 9;
int start_x = (36 - size_x) / 2;
int final_x = start_x + size_x - 1;
int start_y = (36 - size_y) / 2;
int final_y = start_y + size_y - 1;
bool won = 0;
bool ok = 1;
int bomba_x;
int bomba_y;

void setBoard()
{
	for (int i = start_x; i <= final_x; i++)
		for (int j = start_y; j <= final_y; j++)
		{
			afisare[i][j] = 10;
			matrice[i][j] = 0;
		}
	
	for (int i = 1; i <= nrMaximBombe; i++)
	{
		do
		{
			bomba_x = std::rand() % size_x;
			bomba_y = std::rand() % size_y;
		} while (matrice[start_x+bomba_x][start_y+bomba_y]==9);
		
		++nrSteaguri;
		matrice[start_x+bomba_x][start_y+bomba_y]=9;
		cout << "B:" <<bomba_x+1 << " " << bomba_y +1<< endl;
	}
	
	for (int i = start_x; i <= final_x; i++)
		for (int j = start_y; j <= final_y; j++)
		{
			contor = 0;
			if (matrice[i - 1][j - 1] == 9) contor++;
			if (matrice[i - 1][j] == 9) contor++;
			if (matrice[i - 1][j + 1] == 9) contor++;
			if (matrice[i][j - 1] == 9) contor++;
			if (matrice[i][j] == 9) continue;
			if (matrice[i][j + 1] == 9) contor++;
			if (matrice[i + 1][j - 1] == 9) contor++;
			if (matrice[i + 1][j] == 9) contor++;
			if (matrice[i + 1][j + 1] == 9) contor++;
			matrice[i][j] = contor;


		}

}


bool pozitieValida(int a, int b)
{
	if (a<start_x || b<start_y || a>final_x || b>final_y)
		return 0;

	return 1;
}

void BFS(int a, int b)
{
	int deplasare_x[] = { -1,-1,-1,0,1,1,1,0 };
	int deplasare_y[] = { -1,0,1,1,1,0,-1,-1 };
	int prim = 1;
	int ultim = 1;
	coada_x[prim] = a;
	coada_y[prim] = b;
	vizitat[a][b] = 1;
	std::cout << "prim: " << coada_x[prim] - start_x+1 << " " << coada_y[prim] - start_y+1<< " " << vizitat[coada_x[prim]][coada_y[prim]] << endl;
	while (prim <= ultim)
	{

		vizitat[coada_x[prim]][coada_y[prim]] = 1;
		for (int i = 0; i < 8; i++)
		{
			if (pozitieValida(coada_x[prim] + deplasare_x[i], coada_y[prim] + deplasare_y[i]))
			{

				afisare[vecin] = matrice[vecin];

				if (matrice[vecin] != 0)
					vizitat[vecin] = 1;

				if (matrice[vecin] == 0 && vizitat[vecin] == 0)
				{
					++ultim;
					coada_x[ultim] = coada_x[prim] + deplasare_x[i];
					coada_y[ultim] = coada_y[prim] + deplasare_y[i];
					//std::cout << "ultim:" << coada_x[ultim] - 2 << " " << coada_y[ultim] - 2 << " " << vizitat[coada_x[ultim]][coada_y[ultim]] << endl;
				}

			}

		}
		++prim;
	}
}

bool ispressed = false;
int main()
{
	std::srand(time(0));

	cout << start_x << " " << final_x << " " << start_y << " " << final_y;
	enum FazaJoc
	{
		Menu,
		Options,
		Game,
		GameOver,
		BestTime
	};

	FazaJoc faza = Menu;
	//stii care e faza?:)


	Image icon;
	icon.loadFromFile("icon.png");
	icon.createMaskFromColor(Color::White);

	

	sf::RenderWindow joc(sf::VideoMode(1156, 1156), "Minesweeper");
	joc.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	Music muzica;
	muzica.openFromFile("TurnDownForWhat2.ogg");
	muzica.play();
	muzica.setLoop(true);

	Music explozie;
	explozie.openFromFile("exploding.ogg");
	
	Music win;
	win.openFromFile("salam.ogg");




	
	Text nrSteaguriText;
	Font font;
	font.loadFromFile("font.ttf");
	nrSteaguriText.setFont(font);
	nrSteaguriText.setFillColor(Color::White);
	nrSteaguriText.setPosition(200, 1060);
	nrSteaguriText.setCharacterSize(60);
	
	
	
	Texture t;
	t.loadFromFile("images/tiles.jpg");
	Sprite s(t);

	Texture titlu;
	titlu.loadFromFile("images/title.png");
	Sprite stitlu;
	stitlu.setTexture(titlu);
	stitlu.setPosition(195, 100);

	Texture tplay, tplay1;
	tplay.loadFromFile("play.png");
	tplay1.loadFromFile("play1.png");
	
	Sprite splay;
	splay.setTexture(tplay);
	splay.setPosition(415, 460);

	Texture background;
	background.loadFromFile("images/background.jpg");
	Sprite sbackground;
	sbackground.setTexture(background);
	sbackground.setPosition(0, 0);

	Texture mina;
	mina.loadFromFile("icon.png");
	Sprite smina;
	smina.setTexture(mina);
	smina.setPosition(340, 460);
	smina.setScale(0.25, 0.25);

	Texture gameOver;
	gameOver.loadFromFile("GameOver.png");
	Sprite sgameOver;
	sgameOver.setTexture(gameOver);
	sgameOver.setPosition(400, 200);
	sgameOver.setScale(0.4, 0.4);

	
	std::cout << "Nr. steaguri:" << nrSteaguri << endl;
	while (joc.isOpen())
	{
		faza = Menu;
		while (faza == Menu)
		{
			joc.clear();
			joc.draw(sbackground);
			joc.draw(stitlu);
			joc.draw(splay);
			Vector2i pozitie = Mouse::getPosition(joc);

			if (splay.getGlobalBounds().contains(pozitie.x, pozitie.y))
			{

				joc.draw(smina);
			}
			joc.display();
			sf::Event e;
			while (joc.pollEvent(e))
			{


				if (e.type == sf::Event::Closed)
				{
					joc.close();
					muzica.stop();
				}


				if (e.type == sf::Event::MouseButtonPressed)
					if (e.key.code == Mouse::Left)
						if (splay.getGlobalBounds().contains(pozitie.x, pozitie.y)) {
							ispressed = true;
							splay.setTexture(tplay1);
						}
				if (e.type == sf::Event::MouseButtonReleased)
					if (e.key.code == Mouse::Left)
						if (ispressed)
						{
							ispressed = false;
							splay.setTexture(tplay);
							setBoard();
							faza = Game;
						}
			}

		}



		while (faza == Game)

		{
			



			stringstream nrSteaguriString;
			nrSteaguriString << to_string(nrSteaguri);
			nrSteaguriText.setString(nrSteaguriString.str());
			
			
			muzica.setVolume(50);

			Vector2i pozitie = Mouse::getPosition(joc);
			int x = pozitie.x / pixel;
			int y = pozitie.y / pixel;



			sf::Event e;
			while (joc.pollEvent(e))
			{

				if (e.type == sf::Event::Closed)
				{
					joc.close();
					muzica.stop();
				}

				if (e.type == Event::MouseButtonPressed)
				{

					if (e.key.code == Mouse::Left && afisare[x][y] != 11 && pozitieValida(x, y) != 0 && ok==1 && won==0)
					{
						afisare[x][y] = matrice[x][y];

						if (matrice[x][y] == 9)
						{
							muzica.stop();
							explozie.play();
							std::cout << "BUM!" << endl;
							ok = 0;
							
							


							for (int i = start_x; i <= final_x; i++)
								for (int j = start_y; j <= final_y; j++)
									if (matrice[i][j] != 9 || afisare[i][j] != 11)
										afisare[i][j] = matrice[i][j];

							//joc.close(); 
							//faza = GameOver;
						}
						std::cout <<x<<" "<<y<<" "<< x - start_x+1 << " " << y - start_y+1 << " " << pozitieValida(x, y) << endl;
						if (matrice[x][y] == 0 && pozitieValida(x, y))  BFS(x, y);

					}

					if (nrSteaguri > 0)
					{
						if (e.key.code == Mouse::Right && ok == 1 && won==0)
						{
							if (afisare[x][y] == 10)
							{
								afisare[x][y] = 11;
								--nrSteaguri;
								std::cout << "Nr. steaguri:" << nrSteaguri << endl;
							}
							else if (afisare[x][y] == 11)
							{
								afisare[x][y] = 10;
								++nrSteaguri;
								std::cout << "Nr. steaguri:" << nrSteaguri << endl;
							}
						}
					}
					else { std::cout << "Ai ramas fara steaguri!:(";/* joc.close();*/ }


				}


			}

			joc.clear(Color(100, 0, 0, 255));

			for (int i = start_x; i <= final_x; i++)
				for (int j = start_y; j <= final_y; j++)
				{

					s.setTextureRect(IntRect(pixel*afisare[i][j], 0, pixel, pixel));
					s.setPosition(i*pixel, j*pixel);
					joc.draw(s);
					
					if (ok == 0)
						joc.draw(sgameOver);


				}

			won = 1;
			for (int i = start_x; i <= final_x; i++)
				for (int j = start_y; j <= final_y; j++)
					if (afisare[i][j] == 10)
						won = 0;
			if (won == 1 && ok == 1)
			{
				nrSteaguri = 1998;
			}
			joc.draw(nrSteaguriText);
			joc.display();
		}
	}
	return 0;
}
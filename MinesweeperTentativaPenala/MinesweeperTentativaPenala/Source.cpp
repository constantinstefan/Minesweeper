#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
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
int nrMaximBombe = 160;

bool pozitieValida(int a,int b)
{
	if(a<3||b<3||a>32||b>32)
	return 0;

	return 1;
}

void BFS(int a, int b)
{
	int deplasareLinie[] = { -1,-1,-1,0,1,1,1,0 };
	int deplasareColoana[] = {-1,0,1,1,1,0,-1,-1 };
	int prim = 1;
	int ultim = 1;
	coada_x[prim] = a;
	coada_y[prim] = b;
	vizitat[a][b] = 1;
	cout <<"prim: "<<coada_x[prim]-2 << " " << coada_y[prim]-2<<" "<<vizitat[coada_x[prim]][coada_y[prim]]<<endl;
	while (prim <= ultim)
	{
		vizitat[coada_x[prim]][coada_y[prim]] = 1;
		for (int i = 0; i < 8; i++)
			if (pozitieValida(coada_x[prim] + deplasareLinie[i], coada_y[prim] + deplasareColoana[i]))
			{
				afisare[coada_x[prim] + deplasareLinie[i]][coada_y[prim] + deplasareColoana[i]] = matrice[coada_x[prim] + deplasareLinie[i]][coada_y[prim] + deplasareColoana[i]];
				if ( (matrice[coada_x[prim] + deplasareLinie[i]][coada_y[prim] + deplasareColoana[i]] == 0) && (vizitat[coada_x[prim] + deplasareLinie[i]][coada_y[prim] + deplasareColoana[i]]==0));
				{
					vizitat[coada_x[prim] + deplasareLinie[i]][coada_y[prim] + deplasareColoana[i]] = 1;
					ultim++;
					coada_x[ultim] = coada_x[prim] + deplasareLinie[i];
					coada_y[ultim] = coada_y[prim] + deplasareColoana[i];
					cout << "ultim:" << coada_x[ultim]-2 << " " << coada_y[ultim]-2 <<" "<<vizitat[coada_x[ultim]][coada_y[ultim]]<<endl;
                    				
				}
			}

		++prim;
	}
}
	
	int main()
{   
    Image icon;
	icon.loadFromFile("icon.png");
	icon.createMaskFromColor(Color::White);

	srand(time(0));

	sf::RenderWindow joc(sf::VideoMode(1200, 1200), "Cosmin");
	joc.setIcon(icon.getSize().x,icon.getSize().y,icon.getPixelsPtr());

	

	for (int i = 3; i <= 32; i++)
		for (int j = 3; j <= 32; j++)
		{    
			afisare[i][j] = 10;
			
			if (rand() % 5 == 0 && nrMaximBombe>0)
			{
				matrice[i][j] = 9;
				++nrSteaguri;
				--nrMaximBombe;
			}
			else matrice[i][j] = 0;
        }

	for(int i=3;i<=32;i++)
		for (int j = 3; j <= 32; j++)
		{   
			contor = 0;
			if (matrice[i-1][j-1] == 9) contor++;
			if (matrice[i-1][j] == 9) contor++;
			if (matrice[i-1][j+1] == 9) contor++;
			if (matrice[i][j-1] == 9) contor++;
			if (matrice[i][j] == 9) continue;
			if (matrice[i][j+1] == 9) contor++;
			if (matrice[i + 1][j-1] == 9) contor++;
			if (matrice[i + 1][j] == 9) contor++;
			if (matrice[i + 1][j+1] == 9) contor++;
			matrice[i][j] = contor;
			

		}

	Texture t;
	t.loadFromFile("images/tiles.jpg");
	Sprite s(t);


	cout <<"Nr. steaguri:"<< nrSteaguri << endl;
	while (joc.isOpen())
	{
		Vector2i pozitie = Mouse::getPosition(joc);
		int x = pozitie.x / pixel;
		int y = pozitie.y / pixel;
		
		
		
		sf::Event e;
		while (joc.pollEvent(e))
		{
			
			if (e.type == sf::Event::Closed)
				joc.close();
			
			if (e.type == Event::MouseButtonPressed)
			{
				
				if (e.key.code == Mouse::Left && afisare[x][y]!=11) 
				{ 
                   	afisare[x][y] = matrice[x][y];
					
					if (matrice[x][y] == 9) 
					{ 
						cout << "BUM!"<< endl;
						for (int i = 3; i <= 32; i++)
							for (int j = 3; j <= 32; j++)
								if(matrice[i][j]!=9||afisare[i][j]!=11)
								afisare[i][j] = matrice[i][j];
						//joc.close(); 
					}
					cout << x-2 << " " << y-2 << endl;;
					//if (matrice[x][y] == 0)  BFS(x, y);
                 
				}				
				
				if (nrSteaguri > 0)
				{
					if (e.key.code == Mouse::Right)
					{
						if (afisare[x][y] == 10)
						{
							afisare[x][y] = 11;
							--nrSteaguri;
							cout << "Nr. steaguri:" << nrSteaguri << endl;
						}
						else if (afisare[x][y] == 11)
						{
							afisare[x][y] = 10;
							++nrSteaguri;
							cout << "Nr. steaguri:" << nrSteaguri << endl;
						 }
					}
				}
				else { cout << "Ai ramas fara steaguri!:("; joc.close(); }
			
			
			}
		
		
        }

		joc.clear(Color(100,0,0,255)); 
		
		for (int i = 3; i < 32; i++)
			for (int j = 3; j <= 32; j++)
			{   
				
				s.setTextureRect(IntRect(pixel*afisare[i][j], 0, pixel, pixel));
				s.setPosition(i*pixel, j*pixel);
				joc.draw(s);
			}
		joc.display();
	}

	return 0;
}
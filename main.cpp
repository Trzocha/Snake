#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <sstream>
#include <functional>
#include <memory>

using namespace sf;


int N=30,M=20;
int size=16;       //wielkosc obrazka wczytywanego
int w = size*N;
int h = size*M;
int sscore;
int dir,num;
float delay=0.1;
bool q;


class Snake
{
public:
	int x,y;
};

Snake s[100];

class Fruit
{
public:
	int x,y;
};

Fruit f;

void Trick()
{

	for(int i=num;i>0;--i)           //ruch weza
	{
		s[i].x=s[i-1].x;
		s[i].y=s[i-1].y;
	}
                                 //nadanie kierunku poprzez zmiejszanie lub zwieszanie po x/y pozycji
	if(dir==0) s[0].y+=1;
	if(dir==1) s[0].x-=1;
	if(dir==2) s[0].x+=1;
	if(dir==3) s[0].y-=1;

	if((s[0].x==f.x) && (s[0].y==f.y))   //Jezeli pozycja glowy jest rowna pozycji owocu
	{
		num++;  						//waz powieksza sie
		sscore++;
		f.x=rand()%N;                   //generowanie pozycji x i y nowego owoca
		f.y=rand()%M;
	}
                                        //przechodzenie przez sciany
	if(s[0].x>N) s[0].x=0;
	if(s[0].x<0) s[0].x=N;
	if(s[0].y>M) s[0].y=0;
	if(s[0].y<0) s[0].y=M;

}

bool SnakeColision()
{
   for(int i=1;i<num;i++)
   {
	   if(s[0].x == s[i].x && s[0].y == s[i].y) return 1;
   }
   return 0;
}

void resetGame()
{
	num=4;
	sscore =0;
	dir=0;
	delay=0.1;
}

void Snakelvl()
{
	delay-=0.01;
}

bool okno()
{
	RenderWindow window2(VideoMode(400,300),"SnakeVer2.1");
	Texture t3;
	t3.loadFromFile("images/GameOver.jpg");
	Sprite sprite3(t3);

	std::stringstream Score;
	std::stringstream Question;
	Score<<"Your Score: "<<sscore;
	Question<<"Continue [T/N]?";

	Font arial;
	arial.loadFromFile("images/arial.ttf");
	Text text;
	Text text2;

	text.setCharacterSize(15);
	text.setPosition(160,200);
	text.setFillColor(Color::White);
	text.setFont(arial);
	text.setString(Score.str());

	text2.setCharacterSize(15);
	text2.setPosition(160,250);
	text2.setFillColor(Color::White);
	text2.setFont(arial);
	text2.setString(Question.str());


		while(window2.isOpen())
		{

			Event ee;
			while(window2.pollEvent(ee))
				{
				   if(ee.type ==Event::Closed)
					 {window2.close(); return false;}
				   if(Keyboard::isKeyPressed(Keyboard::Key::T))
					   {window2.close(); return true;}
				   if(Keyboard::isKeyPressed(Keyboard::Key::N))
				   	   {window2.close(); return false;}
				}
			window2.draw(sprite3);
			window2.draw(text);
			window2.draw(text2);
			window2.display();
		}
	return false;
}

void window_game()
{
	int j=1;

	srand(time(0));

		RenderWindow window(VideoMode(w,h),"SnakeVer2");

		Texture t1,t2;
		t1.loadFromFile("images/white.png");
		t2.loadFromFile("images/red.png");

		Sprite sprite1(t1);
		Sprite sprite2(t2);

		std::stringstream Score;
		Score<<"Your Score: "<<sscore;

		Font arial;
		arial.loadFromFile("images/arial.ttf");
		Text text;

		text.setCharacterSize(15);
		text.setPosition(375,5);
		text.setFillColor(Color::Blue);
		text.setFont(arial);
		text.setString(Score.str());

		Clock clock;
		float timer=0;

		f.x=10;
		f.y=10;

		while(window.isOpen())
		{

				float time = clock.getElapsedTime().asSeconds();
				clock.restart();
				timer+=time;

				Event e;
				while(window.pollEvent(e))
				{
					if(e.type ==Event::Closed)
						window.close();

				}


				if(num>=5)
				{
					if(SnakeColision()==1)
					{
						window.close();
					}
				}

				if(Keyboard::isKeyPressed(Keyboard::Left)) dir=1;
				if(Keyboard::isKeyPressed(Keyboard::Right)) dir=2;
				if(Keyboard::isKeyPressed(Keyboard::Up)) dir=3;
				if(Keyboard::isKeyPressed(Keyboard::Down)) dir=0;

				window.clear();

				if(timer>delay)  // co 0.1s wywolywana jest funkcja Trick czyli wprawiany waz w ruch
				{
					timer=0;
					Trick();
					if(sscore%(5*j)==0 && num>4){j++;q=1;}
					if(q){Snakelvl();q=0;}
					std::cout<<"\ndelay: "<<delay<<" q: "<<q;
					Score.str("");
					Score<<"Your Score: "<<sscore;
					text.setString(Score.str());

				}

				for(int i=0;i<N;i++)
					for(int j=0;j<M;j++)
					{
						sprite1.setPosition(i*size,j*size);
						window.draw(sprite1);
						window.draw(text);

					}

				for(int i=0;i<num;i++)
				{
					sprite2.setPosition(s[i].x*size,s[i].y*size);
					window.draw(sprite2);
				}

				sprite2.setPosition(f.x*size,f.y*size); window.draw(sprite2);

				window.display();

		}
}

int main()
{
	auto x = std::make_unique<int>(10);

	bool q=0;
	do{
		resetGame();
		window_game();
		q=okno();
	}while(q);

	return 0;
}


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <windows.h>

using namespace std;

const int WINDOW_HEIGHT = 1200;
const int WINDOW_WIDTH = 1000;
const int wh = 1500;
const int ww = 1500;
int ARRAY_SIZE = 20;
int speed = 50;
int BAR_WIDTH = (WINDOW_WIDTH / 3) / (ARRAY_SIZE / 3);
int elapsedTime = 0; // milliseconds mein hai
int minutes = 0;
int seconds = 0;
int milliseconds = 0;
bool timerRunning = false;

sf::Texture bgt;
sf::Sprite bgs;

sf::Texture bot;
sf::Sprite bos;

sf::Texture solgt;
sf::Sprite solgs;

sf::Texture b1t;
sf::Sprite b1s;

sf::Texture b2t;
sf::Sprite b2s;

sf::Texture b3t;
sf::Sprite b3s;

sf::Texture b4t;
sf::Sprite b4s;

sf::Texture b5t;
sf::Sprite b5s;

sf::Texture b6t;
sf::Sprite b6s;

sf::Texture splt;
sf::Sprite spls;

sf::Texture sprt;
sf::Sprite sprs;

sf::Texture nlt;
sf::Sprite nls;

sf::Texture nrt;
sf::Sprite nrs;

sf::Texture ret;
sf::Sprite res;

sf::Texture timet;
sf::Sprite times;

sf::SoundBuffer beepBuffer;
sf::Sound beepSound;

sf::SoundBuffer tBuffer;
sf::Sound tSound;

sf::SoundBuffer clickBuffer;
sf::Sound clickSound;

sf::Text sped;

sf::Text nnp;

sf::Text sp;

sf::Text timerText;

sf::Clock timerClock; 

std::string intToString(int value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

void updateTimer()
{
    if(timerRunning)
    {
        sf::Time deltaTime = timerClock.restart();
        elapsedTime += deltaTime.asMilliseconds();

        int minutes = elapsedTime / 60000;
        int seconds = (elapsedTime % 60000) / 1000;
        int milliseconds = (elapsedTime % 1000) / 10; // Deciseconds

        timerText.setString(intToString(minutes) + "m " + intToString(seconds) + "s " + intToString(milliseconds) + "ms");
    }
}

void render(sf::RenderWindow &window)
{
	window.draw(bgs);
    window.draw(bos);
    window.draw(solgs);
    window.draw(b1s);
    window.draw(b2s);
    window.draw(b3s);
    window.draw(b4s);
    window.draw(b5s);
    window.draw(b6s);
    window.draw(spls);
    window.draw(sprs);
    window.draw(nls);
    window.draw(nrs);
    window.draw(sp);
    window.draw(nnp);
    window.draw(res);
    window.draw(times);
    window.draw(sped);
    window.draw(timerText);
}

void drawArray(sf::RenderWindow &window, const std::vector<int> &array, int id1 , int id2, bool q, bool f)
{
    window.clear();
    render(window);
    if(f == false)
    {
    	updateTimer();
	}
    for(int i = 0; i < array.size(); i++)
    {
        sf::RectangleShape bar(sf::Vector2f(BAR_WIDTH - 2, array[i]));
        if(i == id2)
		{
            bar.setFillColor(sf::Color::Green);
        }
		else if(i == id1)
		{
            bar.setFillColor(sf::Color::Red);
            tSound.play();
        }
        else
        {
            bar.setFillColor(sf::Color::White);
        }
        bar.setPosition(i * BAR_WIDTH + 50, WINDOW_HEIGHT - array[i] + 50);
        window.draw(bar);
    }
    if(q == true)
    {
    	for(int i = 0 ; i < array.size() ; i++)
    	{
    		sf::RectangleShape bar(sf::Vector2f(BAR_WIDTH - 2, array[i]));
            bar.setFillColor(sf::Color::Green);
            bar.setPosition(i * BAR_WIDTH + 50, WINDOW_HEIGHT - array[i] + 50);
            window.draw(bar);
		}
	}
    window.display();
}

void bubbleSort(sf::RenderWindow &window, vector<int> &array)
{
    for(int i = 0 ; i < array.size() - 1 ; i++)
    {
        for(int j = 0 ; j < array.size() - i - 1 ; j++)
        {
        	if(!window.isOpen())
            {
                beepSound.stop(); 
                return;   
            }
            if(array[j] > array[j + 1])
            {
                int temp = array[j + 1];
                array[j + 1] = array[j];
                array[j] = temp;
            }
            drawArray(window, array , j , j + 1 , false , false);
            beepSound.play();
            sf::Event event;
            while(window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                {   
                    beepSound.stop();
                    window.close();
                }
            }
            sleep(sf::milliseconds(speed));
        }
    }
}

void mergeSort(sf::RenderWindow &window, vector<int>& array)
{
    int n = array.size();
    vector<int> temp(n);

    for(int size = 1 ; size < n ; size *= 2)
	{
        for(int leftStart = 0 ; leftStart < n ; leftStart += 2 * size)
		{
            int mid = min(leftStart + size - 1 , n - 1);
            int rightEnd = min(leftStart + 2 * size - 1 , n - 1);
            int i = leftStart;
            int j = mid + 1;
            int k = leftStart;

            while(i <= mid && j <= rightEnd)
			{
                if(array[i] <= array[j])
				{
                    temp[k++] = array[i++];
                }
				else
				{
                    temp[k++] = array[j++];
                }
            }

            while(i <= mid)
			{
                temp[k++] = array[i++];
            }

            while(j <= rightEnd)
			{
                temp[k++] = array[j++];
            }

            for(int m = leftStart; m <= rightEnd; m++)
			{
                array[m] = temp[m];
            }

            drawArray(window, array, leftStart, rightEnd, false , false);
            beepSound.play();
            sf::Event event;
            while(window.pollEvent(event))
			{
                if(event.type == sf::Event::Closed)
				{
					beepSound.stop();
                    window.close();
                    return; 
                }
            }
            sleep(sf::milliseconds(speed));
        }
    }
}

void insertionSort(sf::RenderWindow &window, vector<int>& array)
{
    int n = array.size();
    
    for(int i = 1 ; i < n ; i++)
    {
    	int j = i - 1;
    	int k = array[i];
    	while(j >= 0 && array[j] > k)
    	{
    		array[j + 1] = array[j];
    		j--;
    		drawArray(window, array, i, j + 1, false , false);
    		beepSound.play();
    		sf::Event event;
            while(window.pollEvent(event))
			{
                if(event.type == sf::Event::Closed)
				{
					beepSound.stop();
                    window.close();
                    return; 
                }
            }
            sleep(sf::milliseconds(speed));
		}
		array[j + 1] = k;
	}
}

void selectionSort(sf::RenderWindow &window, vector<int>& array)
{
    int n = array.size();
    vector<int> temp(n);
    
	for(int i = 0 ; i < n - 1 ; i++)
	{
		int k = i;
		for(int j = i + 1 ; j < n ; j++)
		{
			if(array[j] < array[k])
			{
				k = j;
			}
			drawArray(window, array, i , j , false , false);
			beepSound.play();
    		sf::Event event;
            while(window.pollEvent(event))
			{
                if(event.type == sf::Event::Closed)
				{
					beepSound.stop();
                    window.close();
                    return; 
                }
            }
            sleep(sf::milliseconds(speed));
		}
		int temp = array[i];
		array[i] = array[k];
		array[k] = temp;
	}
}

void quickSort(sf::RenderWindow &window, vector<int>& array)
{
    vector<int> indices;
    indices.push_back(0);
    indices.push_back(array.size() - 1);

    while(!indices.empty())
	{
        int high = indices.back(); indices.pop_back();
        int low = indices.back(); indices.pop_back();

        if(low < high)
		{
            int pivot = array[high];
            int i = low - 1;

            for(int j = low; j < high; j++)
			{
                if(array[j] < pivot)
				{
                    i++;
                    std::swap(array[i], array[j]);
                    drawArray(window, array, i, j, false , false);

                    sf::Event event;
                    while (window.pollEvent(event))
					{
                        if(event.type == sf::Event::Closed)
						{
							beepSound.stop();
                            window.close();
                            return;
                        }
                    }
                    sleep(sf::milliseconds(speed));
                }
            }
            int temp = array[i + 1];
            array[i + 1] = array[high];
            array[high] = temp;
            drawArray(window, array, i + 1, high, false , false);
            beepSound.play();
            sf::Event event;
            while(window.pollEvent(event))
			{
                if(event.type == sf::Event::Closed)
				{
					beepSound.stop();
                    window.close();
                    return;
                }
            }
            sleep(sf::milliseconds(speed));

            int pivotIndex = i + 1;

            indices.push_back(low);
            indices.push_back(pivotIndex - 1); 
            indices.push_back(pivotIndex + 1);
            indices.push_back(high); 
        }
    }
}

void shellSort(sf::RenderWindow &window, vector<int>& array)
{
    int n = array.size();
    int gap = n / 2; 
    while(gap > 0)
	{
        for(int i = gap; i < n; i++)
		{
            int temp = array[i];
            int j = i;
            while(j >= gap && array[j - gap] > temp)
			{
                array[j] = array[j - gap];
                drawArray(window , array , j , j - gap , false , false);
                beepSound.play();
                sf::Event event;
                while(window.pollEvent(event))
				{
                    if(event.type == sf::Event::Closed)
					{
						beepSound.stop();
                        window.close();
                        return;
                    }
                }
                sleep(sf::milliseconds(speed));
                j -= gap;
            }
            array[j] = temp;
            drawArray(window , array , j , i , false , false);
            beepSound.play();
            sf::Event event;
            while(window.pollEvent(event))
			{
                if(event.type == sf::Event::Closed)
                {
                	beepSound.stop();
                    window.close();
                    return;
                }
            }
            sleep(sf::milliseconds(speed));
        }
        gap /= 2; 
    }
}

void software(sf::RenderWindow &window)
{
	window.draw(timerText);
    BAR_WIDTH = WINDOW_WIDTH / ARRAY_SIZE;
    vector<int> array(ARRAY_SIZE);
    bool done = false;
    for(int i = 0; i < ARRAY_SIZE; i++)
	{
        array[i] = std::rand() % (WINDOW_HEIGHT - 200) + 20;
    }

    timerText.setString(intToString(minutes) + "m " + intToString(seconds) + "s " + intToString(milliseconds) + "ms");
    
    while(window.isOpen())
	{
        drawArray(window, array, -1 , -1, false , true);

        sf::Event event;
        while(window.pollEvent(event))
		{
            if(event.type == sf::Event::Closed)
			{
				beepSound.stop();
                window.close();
            }
			else if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
                if(b1s.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
				{
					clickSound.play();
					sped.setString("Bubble");
                    if(done == true)
                    {
                    	for(int i = 0 ; i < ARRAY_SIZE ; i++)
	                    {
                            array[i] = std::rand() % (WINDOW_HEIGHT - 200) + 20;
                        }
                        drawArray(window , array , 0 , 0 , false , true);
                        sleep(sf::milliseconds(500));
					}
					elapsedTime = 0;
                    timerClock.restart(); 
                    timerRunning = true;
                    bubbleSort(window, array);
                    timerRunning = false;
                    sleep(sf::milliseconds(500));
                    for(int i = 0; i < ARRAY_SIZE; i++)
					{
                        drawArray(window, array, -1, i, false , true);
                        sleep(sf::milliseconds(50));
                        if(window.isOpen())
						{
                            beepSound.play();
                        }
						sf::Event event;
                        while(window.pollEvent(event))
						{
                            if(event.type == sf::Event::Closed)
						    {
                                beepSound.stop();  
                                window.close();
                                return;  
                            }
                        }
                    }
		 			sleep(sf::milliseconds(500));
                    done = true;
                }
				else if(b2s.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
				{
					clickSound.play();
					sped.setString("Selection");
                    if(done == true)
                    {
                    	for(int i = 0 ; i < ARRAY_SIZE ; i++)
	                    {
                            array[i] = std::rand() % (WINDOW_HEIGHT - 200) + 20;
                        }
                        drawArray(window , array , 0 , 0 , false , true);
                        sleep(sf::milliseconds(500));
					}
					elapsedTime = 0;
                    timerClock.restart(); 
                    timerRunning = true;
                    selectionSort(window, array);
                    timerRunning = false;
                    sleep(sf::milliseconds(500));
                    for(int i = 0; i < ARRAY_SIZE; i++)
					{
                        drawArray(window, array, -1, i, false , true);
                        sleep(sf::milliseconds(50));
                        if(window.isOpen())
						{
                            beepSound.play();
                        }
						sf::Event event;
                        while(window.pollEvent(event))
						{
                            if(event.type == sf::Event::Closed)
						    {
                                beepSound.stop();  
                                window.close();
                                return;  
                            }
                        }
                    }
					sleep(sf::milliseconds(500));
                    done = true;
                }
                else if(b3s.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
				{
					clickSound.play();
					sped.setString("Insertion");
                    if(done == true)
                    {
                    	for(int i = 0 ; i < ARRAY_SIZE ; i++)
	                    {
                            array[i] = std::rand() % (WINDOW_HEIGHT - 200) + 20;
                        }
                        drawArray(window , array , 0 , 0 , false , true);
                        sleep(sf::milliseconds(500));
					}
					elapsedTime = 0;
                    timerClock.restart(); 
                    timerRunning = true;
                    insertionSort(window, array);
                    timerRunning = false;
                    sleep(sf::milliseconds(500));
                    for(int i = 0; i < ARRAY_SIZE; i++)
					{
                        drawArray(window, array, -1, i, false , true);
                        sleep(sf::milliseconds(50));
                        if(window.isOpen())
						{
                            beepSound.play();
                        }
						sf::Event event;
                        while(window.pollEvent(event))
						{
                            if(event.type == sf::Event::Closed)
						    {
                                beepSound.stop();  
                                window.close();
                                return;  
                            }
                        }
                    }
					sleep(sf::milliseconds(500));
                    done = true;
                }
                else if(b4s.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
				{
					clickSound.play();
					sped.setString("Merge");
                    if(done == true)
                    {
                    	for(int i = 0 ; i < ARRAY_SIZE ; i++)
	                    {
                            array[i] = std::rand() % (WINDOW_HEIGHT - 200) + 20;
                        }
                        drawArray(window , array , 0 , 0 , false , true);
                        sleep(sf::milliseconds(500));
					}
					elapsedTime = 0;
                    timerClock.restart(); 
                    timerRunning = true;
                    mergeSort(window, array);
                    timerRunning = false;
                    sleep(sf::milliseconds(500));
                    for(int i = 0; i < ARRAY_SIZE; i++)
					{
                        drawArray(window, array, -1, i, false , true);
                        sleep(sf::milliseconds(50));
                        if(window.isOpen())
						{
                            beepSound.play();
                        }
						sf::Event event;
                        while(window.pollEvent(event))
						{
                            if(event.type == sf::Event::Closed)
						    {
                                beepSound.stop();  
                                window.close();
                                return;  
                            }
                        }
                    }
					sleep(sf::milliseconds(500));
                    done = true;
                }
                else if(b5s.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
				{
					clickSound.play();
					sped.setString("Shell");
                    if(done == true)
                    {
                    	for(int i = 0 ; i < ARRAY_SIZE ; i++)
	                    {
                            array[i] = std::rand() % (WINDOW_HEIGHT - 200) + 20;
                        }
                        drawArray(window , array , 0 , 0 , false , true);
                        sleep(sf::milliseconds(500));
					}
					elapsedTime = 0;
                    timerClock.restart(); 
                    timerRunning = true;
                    shellSort(window, array);
                    timerRunning = false;
                    sleep(sf::milliseconds(500));
                    for(int i = 0; i < ARRAY_SIZE; i++)
					{
                        drawArray(window, array, -1, i, false , true);
                        sleep(sf::milliseconds(50));
                        if(window.isOpen())
						{
                            beepSound.play();
                        }
						sf::Event event;
                        while(window.pollEvent(event))
						{
                            if(event.type == sf::Event::Closed)
						    {
                                beepSound.stop();  
                                window.close();
                                return;  
                            }
                        }
                    }
					sleep(sf::milliseconds(500));
                    done = true;
                }
                else if(b6s.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
				{
					clickSound.play();
					sped.setString("Quick");
                    if(done == true)
                    {
                    	for(int i = 0 ; i < ARRAY_SIZE ; i++)
	                    {
                            array[i] = std::rand() % (WINDOW_HEIGHT - 200) + 20;
                        }
                        drawArray(window , array , 0 , 0 , false , true);
                        sleep(sf::milliseconds(500));
					}
				    elapsedTime = 0;
                    timerClock.restart(); 
                    timerRunning = true;
                    quickSort(window, array);
                    timerRunning = false;
                    sleep(sf::milliseconds(500));
                    for(int i = 0; i < ARRAY_SIZE; i++)
					{
                        drawArray(window, array, -1, i, false , true);
                        sleep(sf::milliseconds(50));
                        if(window.isOpen())
						{
                            beepSound.play();
                        }
						sf::Event event;
                        while(window.pollEvent(event))
						{
                            if(event.type == sf::Event::Closed)
						    {
                                beepSound.stop();  
                                window.close();
                                return;  
                            }
                        }
                    }
					sleep(sf::milliseconds(500));
                    done = true;
                }
                else if(spls.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
				{
				    clickSound.play();	
				    speed -= 10;			
					if(speed == 0)
					{
						speed = 10;
					}
                }
                else if(sprs.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
				{	
				    clickSound.play();
				    speed += 10;			
					if(speed == 510)
					{
						speed = 500;
					}
                }
                else if(nls.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
				{	
				    clickSound.play();
				    ARRAY_SIZE -= 1;			
					if(ARRAY_SIZE == 2)
					{
						ARRAY_SIZE = 3;
					}
					nnp.setString(intToString(ARRAY_SIZE));
					software(window);
                }
                else if(nrs.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
				{	
				    clickSound.play();
				    ARRAY_SIZE += 1;			
					if(ARRAY_SIZE == 101)
					{
						ARRAY_SIZE = 100;
					}
					nnp.setString(intToString(ARRAY_SIZE));
					software(window);
                }
                else if(res.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
				{	
				    clickSound.play();
					software(window);
                }
                sp.setString(intToString(speed));
            }
        }
        if(done == true)
        {
        	drawArray(window, array, 0, 0, true , true);
            sleep(sf::milliseconds(500));
		}
    }
}


int main()
{   
    sf::RenderWindow window(sf::VideoMode(ww, wh), "Sorting Visualizer");
    srand(static_cast<unsigned>(time(NULL)));
    
    beepBuffer.loadFromFile("write.wav");
    beepSound.setBuffer(beepBuffer);
    beepSound.setVolume(20);
    
    tBuffer.loadFromFile("read.wav");
    tSound.setBuffer(tBuffer);
    tSound.setVolume(20);
    
    clickBuffer.loadFromFile("bt.wav");
    clickSound.setBuffer(clickBuffer);
    clickSound.setVolume(20);

    bgt.loadFromFile("bg1.png");
    bgs.setTexture(bgt);
    bgs.setScale(1.5, 1.5);

    bot.loadFromFile("board.png");
    bos.setTexture(bot);
    bos.setScale(1.52, 1.15);
    bos.setPosition(5, 150);

    solgt.loadFromFile("lgo.png");
    solgs.setTexture(solgt);
    solgs.setScale(1, 0.6);
    solgs.setPosition(-650, -200);

    b1t.loadFromFile("b11.png");
    b1s.setTexture(b1t);
    b1s.setScale(1.1, 1.2);
    b1s.setPosition(1095, 250);
    
    b2t.loadFromFile("b22.png");
    b2s.setTexture(b2t);
    b2s.setScale(1.1, 1.2);
    b2s.setPosition(1095, 400);

    b3t.loadFromFile("b33.png");
    b3s.setTexture(b3t);
    b3s.setScale(1.1, 1.2);
    b3s.setPosition(1095, 550);

    b4t.loadFromFile("b44.png");
    b4s.setTexture(b4t);
    b4s.setScale(1.1, 1.2);
    b4s.setPosition(1095, 700);

    b5t.loadFromFile("b55.png");
    b5s.setTexture(b5t);
    b5s.setScale(1.1, 1.2);
    b5s.setPosition(1095, 850);

    b6t.loadFromFile("b66.png");
    b6s.setTexture(b6t);
    b6s.setScale(1.1, 1.2);
    b6s.setPosition(1095, 1000);
    
    splt.loadFromFile("ls.png");
    spls.setTexture(splt);
    spls.setScale(1.1, 1.2);
    spls.setPosition(920, 1315);
    
    sprt.loadFromFile("rs.png");
    sprs.setTexture(sprt);
    sprs.setScale(1.1, 1.2);
    sprs.setPosition(1020, 1315);
    
    nlt.loadFromFile("ls.png");
    nls.setTexture(nlt);
    nls.setScale(1.1, 1.2);
    nls.setPosition(920, 1410);
    
    nrt.loadFromFile("rs.png");
    nrs.setTexture(nrt);
    nrs.setScale(1.1, 1.2);
    nrs.setPosition(1020, 1410);
    
    ret.loadFromFile("re.png");
    res.setTexture(ret);
    res.setScale(1.1, 1.2);
    res.setPosition(1200, 1150);
    
    timet.loadFromFile("yellow.png");
    times.setTexture(timet);
    times.setScale(1.7, 0.9);
    times.setPosition(300, 1315);
    
    sf::Font font;
    font.loadFromFile("art.ttf");
    sped.setFont(font);
    sped.setString("");
    sped.setCharacterSize(80); 
    sped.setFillColor(sf::Color::Yellow);
    sped.setStyle(sf::Text::Bold);
    sped.move(1170,130);
    
    sp.setFont(font);
    sp.setString(intToString(speed));
    sp.setCharacterSize(80); 
    sp.setFillColor(sf::Color::Yellow);
    sp.setStyle(sf::Text::Bold);
    sp.move(1250,1295);
    
    nnp.setFont(font);
    nnp.setString(intToString(ARRAY_SIZE));
    nnp.setCharacterSize(80); 
    nnp.setFillColor(sf::Color::Yellow);
    nnp.setStyle(sf::Text::Bold);
    nnp.move(1250,1390);
    
    timerText.setFont(font);
    timerText.setString(intToString(minutes) + "m " + intToString(seconds) + "s " + intToString(milliseconds) + "ms");
    timerText.setCharacterSize(40); 
    timerText.setFillColor(sf::Color::Black);
    timerText.setStyle(sf::Text::Bold);
    timerText.move(360,1340);
    
    software(window);
    return 0;
}


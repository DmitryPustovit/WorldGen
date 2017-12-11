#include <SFML/Graphics.hpp>
#include "WorldGenerator.h"
#include "Textbox.h"
#include <math.h>
#include <iomanip>
#include <sstream>

WorldGenerator _worldGenerator;

/**
* Zooms into image with view based on current location
*
* @param pixel
* @param window
* @param zoom
*
* @return none
*/
void zoomViewAt(sf::Vector2i pixel, sf::RenderWindow &window, float zoom) {
    sf::View view{window.getView()};
    view.zoom(zoom);
    window.setView(view);
    window.setView(view);
}

/**
* Rending function loop for the rendering thread
*
* @param window
*
* @return none
*/
void renderingThread(sf::RenderWindow *window) {
    // the rendering loop
    window->setActive(true);
    while (window->isOpen()) {
        // draw...
        window->clear();
        _worldGenerator.Render(window);
        window->display();
    }
}

/**
* Output formated string from double
* Limits precision to 2 decimal points
*
* @param double
*
* @return string
*/
std::string stringy(double n)
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << n;
	std::string str = stream.str();

	return str;
}

/**
* Opens the settings menu
* Waits for user to submit changes or exit program
*
* @param worldGenerator
*
* @return changes made
*/
bool opensettings(WorldGenerator& wg)
{
	//Creates window
	sf::RenderWindow settingsWindow(sf::VideoMode(840, 640), "Settings", sf::Style::Titlebar | sf::Style::Close);
	//Font loading
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
		std::cout << "FONT LOAD ERROR" << std::endl;

	//Creates header text
	sf::Text elevHeader;
	sf::Text moistHeader;
	sf::Text tempHeader;

	//Elevation header and textboxes
	elevHeader.setFont(font);
	elevHeader.setFillColor(sf::Color::Black);
	elevHeader.setCharacterSize(28);
	elevHeader.setString("Elevation");
	elevHeader.setPosition(18, 10);

	Textbox elevationFreq(settingsWindow, font);
	elevationFreq.setDimensons(20, 100, 200, 50);
	elevationFreq.setString(stringy(wg.elev.freq));
	elevationFreq.setSubtext("Fequency");
	elevationFreq.setFocus(true);

	Textbox elevationFractalOct(settingsWindow, font);
	elevationFractalOct.setDimensons(20, 220, 200, 50);
	elevationFractalOct.setString(stringy(wg.elev.oct));
	elevationFractalOct.setSubtext("Fractal Octaves");
	elevationFractalOct.setFocus(false);

	Textbox elevationFractalLac(settingsWindow, font);
	elevationFractalLac.setDimensons(20, 340, 200, 50);
	elevationFractalLac.setString(stringy(wg.elev.lac));
	elevationFractalLac.setSubtext("Fractal Lacunarity");
	elevationFractalLac.setFocus(false);

	Textbox elevationFractalGain(settingsWindow, font);
	elevationFractalGain.setDimensons(20, 460, 200, 50);
	elevationFractalGain.setString(stringy(wg.elev.gain));
	elevationFractalGain.setSubtext("Fractal Gain");
	elevationFractalGain.setFocus(false);

	//Moisture Header and Textboxes
	moistHeader.setFont(font);
	moistHeader.setFillColor(sf::Color::Black);
	moistHeader.setCharacterSize(28);
	moistHeader.setString("Moisture");
	moistHeader.setPosition(318, 10);

	Textbox moistFreq(settingsWindow, font);
	moistFreq.setDimensons(320, 100, 200, 50);
	moistFreq.setString(stringy(wg.moist.freq));
	moistFreq.setSubtext("Fequency");
	moistFreq.setFocus(false);

	Textbox moistFractalOct(settingsWindow, font);
	moistFractalOct.setDimensons(320, 220, 200, 50);
	moistFractalOct.setString(stringy(wg.moist.oct));
	moistFractalOct.setSubtext("Fractal Octaves");
	moistFractalOct.setFocus(false);

	Textbox moistFractalLac(settingsWindow, font);
	moistFractalLac.setDimensons(320, 340, 200, 50);
	moistFractalLac.setString(stringy(wg.moist.lac));
	moistFractalLac.setSubtext("Fractal Lacunarity");
	moistFractalLac.setFocus(false);

	Textbox moistFractalGain(settingsWindow, font);
	moistFractalGain.setDimensons(320, 460, 200, 50);
	moistFractalGain.setString(stringy(wg.moist.gain));
	moistFractalGain.setSubtext("Fractal Gain");
	moistFractalGain.setFocus(false);

	//Tempeture heading and textboxes
	tempHeader.setString("Tempeture");
	tempHeader.setFont(font);
	tempHeader.setFillColor(sf::Color::Black);
	tempHeader.setCharacterSize(28);
	tempHeader.setString("Tempeture");
	tempHeader.setPosition(618, 10);

	Textbox tempFreq(settingsWindow, font);
	tempFreq.setDimensons(620, 100, 200, 50);
	tempFreq.setString(stringy(wg.temp.freq));
	tempFreq.setSubtext("Fequency");
	tempFreq.setFocus(false);

	Textbox tempFractalOct(settingsWindow, font);
	tempFractalOct.setDimensons(620, 220, 200, 50);
	tempFractalOct.setString(stringy(wg.temp.oct));
	tempFractalOct.setSubtext("Fractal Octaves");
	tempFractalOct.setFocus(false);

	Textbox tempFractalLac(settingsWindow, font);
	tempFractalLac.setDimensons(620, 340, 200, 50);
	tempFractalLac.setString(stringy(wg.temp.lac));
	tempFractalLac.setSubtext("Fractal Lacunarity");
	tempFractalLac.setFocus(false);

	Textbox tempFractalGain(settingsWindow, font);
	tempFractalGain.setDimensons(620, 460, 200, 50);
	tempFractalGain.setString(stringy(wg.temp.gain));
	tempFractalGain.setSubtext("Fractal Gain");
	tempFractalGain.setFocus(false);

	Textbox fractalNoise(settingsWindow, font);
	fractalNoise.setDimensons(20, 580, 50, 50);
	fractalNoise.setString(wg.temp.type);
	fractalNoise.setSubtext("Noise Type");
	fractalNoise.setFocus(false);

	//Button Creation
	sf::Text buttonText;
	buttonText.setString("Re Generate");
	buttonText.setFont(font);
	buttonText.setFillColor(sf::Color::Black);
	buttonText.setCharacterSize(28);
	sf::FloatRect textRect = buttonText.getLocalBounds();
	buttonText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);

	buttonText.setPosition(sf::Vector2f(settingsWindow.getSize().x / 2.0f, 580));
	sf::RectangleShape rectangle(sf::Vector2f(200, 60));
	rectangle.setOutlineColor(sf::Color::Black);
	rectangle.setPosition((settingsWindow.getSize().x / 2.0f) - 100, 550);

	while (settingsWindow.isOpen()) {
		// Process events
		sf::Event event;
		while (settingsWindow.pollEvent(event)) {
			// Close window
			if (event.type == sf::Event::Closed) {
				settingsWindow.close();
				return false;
			}

			sf::Vector2i pos = sf::Mouse::getPosition(settingsWindow);

			//Checks for button press
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)
				&& pos.x >= (settingsWindow.getSize().x / 2.0f) - 100
				&& pos.x <= (settingsWindow.getSize().x / 2.0f) + 100
				&& pos.y >= 550
				&& pos.y <= 610)
			{
				//Update for all textboxes
				wg.elev.freq = std::stod(elevationFreq.getString());
				wg.elev.oct = std::stod(elevationFractalOct.getString());
				wg.elev.lac = std::stod(elevationFractalLac.getString());
				wg.elev.gain = std::stod(elevationFractalGain.getString());

				wg.temp.freq = std::stod(tempFreq.getString());
				wg.temp.oct = std::stod(tempFractalOct.getString());
				wg.temp.lac = std::stod(tempFractalLac.getString());
				wg.temp.gain = std::stod(tempFractalGain.getString());

				wg.moist.freq = std::stod(moistFreq.getString());
				wg.moist.oct = std::stod(moistFractalOct.getString());
				wg.moist.lac = std::stod(moistFractalLac.getString());
				wg.moist.gain = std::stod(moistFractalGain.getString());

				wg.moist.type = fractalNoise.getString();
				wg.temp.type = fractalNoise.getString();
				wg.elev.type = fractalNoise.getString();

				settingsWindow.close();
				return true;
			}
			
	
			elevationFreq.pollEvent(event, pos);
			elevationFractalOct.pollEvent(event, pos);
			elevationFractalLac.pollEvent(event, pos);
			elevationFractalGain.pollEvent(event, pos);

			moistFreq.pollEvent(event, pos);
			moistFractalOct.pollEvent(event, pos);
			moistFractalLac.pollEvent(event, pos);
			moistFractalGain.pollEvent(event, pos);

			tempFreq.pollEvent(event, pos);
			tempFractalOct.pollEvent(event, pos);
			tempFractalLac.pollEvent(event, pos);
			tempFractalGain.pollEvent(event, pos);

			fractalNoise.pollEvent(event, pos);
		}

		// Clear screen to gray color
		settingsWindow.clear(sf::Color(236, 236, 236));

		//Draws all textboxes
		elevationFreq.draw();
		elevationFractalOct.draw();
		elevationFractalLac.draw();
		elevationFractalGain.draw();

		moistFreq.draw();
		moistFractalOct.draw();
		moistFractalLac.draw();
		moistFractalGain.draw();

		tempFreq.draw();
		tempFractalOct.draw();
		tempFractalLac.draw();
		tempFractalGain.draw();

		fractalNoise.draw();

		//Draws all headers and button
		settingsWindow.draw(elevHeader);
		settingsWindow.draw(moistHeader);
		settingsWindow.draw(tempHeader);
		settingsWindow.draw(rectangle);
		settingsWindow.draw(buttonText);

		// Update the window
		settingsWindow.display();
	}
}


int main()
{
	//Creates window
    sf::RenderWindow window(sf::VideoMode(800, 800), "World");
    int size = 1000; //World Size
	//Generates world
    _worldGenerator = WorldGenerator(size);
    _worldGenerator.createGraphics();
	//Creates view and sets move speed for view
    sf::View view;
    float moveSpeed = size * .00001;
    view.setSize(900, 900);
	//Windows settings
    window.setView(view);
    window.setActive(false);

    // launch the rendering thread
    sf::Thread thread(&renderingThread, &window);
    thread.launch();

	//Update
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)) {
			//Close window
            if (event.type == sf::Event::Closed) {
				thread.terminate();
				window.close();
                return 0;
            }
			//Scroll Zoom
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0)
                    zoomViewAt({event.mouseWheelScroll.x, event.mouseWheelScroll.y}, window, (1.f / .9));
                else if (event.mouseWheelScroll.delta < 0)
                    zoomViewAt({event.mouseWheelScroll.x, event.mouseWheelScroll.y}, window, .9);
            }
        }
		//Gets view
        view = window.getView();
		//Movement controls
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            _worldGenerator.MoveGraphics(-moveSpeed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            _worldGenerator.MoveGraphics(moveSpeed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            _worldGenerator.MoveGraphics(0, -moveSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            _worldGenerator.MoveGraphics(0, moveSpeed);
        }

		//Alt zoom controls
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp)) {
            view.setSize(view.getSize().x * 0.999999f, view.getSize().y * 0.999999f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)) {
            view.setSize(view.getSize().x * 1.00001f, view.getSize().y * 1.00001f);
        }
		//Laptop control support
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
			view.setSize(view.getSize().x * 0.999999f, view.getSize().y * 0.999999f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			view.setSize(view.getSize().x * 1.00001f, view.getSize().y * 1.00001f);
		}

		//Opens settings
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
			//If settings changes are made, creates a new world
			if (opensettings(_worldGenerator))
			{
				WorldGenerator newG = WorldGenerator(size, false);
				newG.elev = _worldGenerator.elev;
				newG.moist = _worldGenerator.moist;
				newG.temp = _worldGenerator.temp;
				newG.setUpNoises();
				newG.createGraphics();
				_worldGenerator = newG;
			}

		}

        //_worldGenerator.Render(&window);
        window.setView(view);
        //window.display();
    }
    system("pause");
    return 0;
}

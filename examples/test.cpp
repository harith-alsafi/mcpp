#include <SFML/Graphics.hpp>

void test(){
    // Code adapted from the SFML 2 "Window" example.
    sf::Window App(sf::VideoMode(800, 600), "myproject");

    while (App.isOpen()) {
        sf::Event Event;
        while (App.pollEvent(Event)) {
        if (Event.type == sf::Event::Closed)
        App.close();
        }
        App.display();
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
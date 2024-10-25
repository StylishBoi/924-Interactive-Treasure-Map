#include <SFML/Graphics.hpp>

#include "Functions.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Treasure Hunt");

    srand(time(0));

    sf::CircleShape option_buttons(60);
    option_buttons.setFillColor(sf::Color::Black);

    sf::Texture basic;
    basic.loadFromFile("924-Inte.77a09680\\x64\\Assets\\Tiles\\basics.png");
    sf::Texture wrong;
    wrong.loadFromFile("924-Inte.77a09680\\x64\\Assets\\Tiles\\failure.png");
    sf::Texture correct;
    correct.loadFromFile("924-Inte.77a09680\\x64\\Assets\\Tiles\\success.png");
    sf::Texture potential;
    potential.loadFromFile("924-Inte.77a09680\\x64\\Assets\\Tiles\\potential.png");

    sf::Sprite s_basic;
    s_basic.setTexture(basic);
    sf::Sprite s_wrong;
    s_wrong.setTexture(wrong);
    sf::Sprite s_success;
    s_success.setTexture(correct);
    sf::Sprite s_potential;
    s_potential.setTexture(potential);

    std::array<int, 2>solution = {rand() % 5, rand() % 5};
    std::array<int, 2>player_answer;
    std::array<int, 5> memory = {-1,-1,-1,-1,-1};
    int attempts=0;
    bool answer = false;

    sf::Font font;
    font.loadFromFile("924-Inte.77a09680\\x64\\Assets\\OpenSans.ttf");
    sf::Text try_again;
    try_again.setFont(font);
    try_again.setString("Would you like to play again ?");
    try_again.setCharacterSize(50);
    try_again.setFillColor(sf::Color::Black);
    try_again.setPosition(155, 50);

    sf::Text yes;
    yes.setFont(font);
    yes.setString("Yes");
    yes.setCharacterSize(50);
    yes.setFillColor(sf::Color::White);
    yes.setPosition(260, 665);

    sf::Text no;
    no.setFont(font);
    no.setString("No");
    no.setCharacterSize(50);
    no.setFillColor(sf::Color::White);
    no.setPosition(665, 665);

    while (window.isOpen())
    {
        sf::Event event;
        while ((window.pollEvent(event) and attempts != 5) or (window.pollEvent(event) and answer==false))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            for (int x = 0; x < 5; ++x)
            {
                for (int y = 0; y < 5; ++y)
                {
                    s_basic.setPosition((200 * x), (200 * y));
                    window.draw(s_basic);
                }

            }

            for (int idx = 0; idx <= attempts; ++idx)
            {
                s_wrong.setPosition(((memory[idx] / 10) * 200), ((memory[idx] % 10) * 200));
                window.draw(s_wrong);
            }

            if (answer==true)
            {
                window.draw(s_success);
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    player_answer=coordinates_translator(event.mouseButton.x, event.mouseButton.y);

                    if (Double_Verification(memory, player_answer) == true) {
                    }
                    else if(verification(solution, player_answer)==true)
                    {
                        s_success.setPosition((player_answer[0]*200), (player_answer[1]*200));
                        window.draw(s_success);
                        std::cout << "It's a match.\n";
                        answer = true;
                    }
                    else if(verification(solution, player_answer)==false)
                    {
                        std::cout << "It's not a match.\n";
                        memory = Memory(memory, attempts, player_answer);
                    	attempts = attempts+1;
                    }
                }
            }
        }

        while(attempts == 5 or answer == true){
            if (answer == true) {
                s_success.setPosition((solution[0] * 200), (solution[1] * 200));
                window.draw(s_success);
            }
            if (attempts == 5)
                {
                    s_wrong.setPosition(((memory[4] / 10) * 200), ((memory[4] % 10) * 200));
                    window.draw(s_wrong);

                    s_potential.setPosition((solution[0] * 200), (solution[1] * 200));
                    window.draw(s_potential);
                }

                window.draw(try_again);

                option_buttons.setPosition(235, 635);
                window.draw(option_buttons);
                option_buttons.setPosition(635, 635);
                window.draw(option_buttons);

                window.draw(yes);
                window.draw(no);
                window.display();

                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::MouseButtonReleased and event.mouseButton.button == sf::Mouse::Left)
                    {
                        if ((event.mouseButton.x > 200 and event.mouseButton.y > 600) and (event.mouseButton.x < 400 and event.mouseButton.y < 800))
                        {
                            solution = { rand() % 5, rand() % 5 };
                            memory = { -1,-1,-1,-1,-1 };
                            attempts = 0;
                            answer = false;
                        }
                        else if ((event.mouseButton.x > 600 and event.mouseButton.y > 600) and (event.mouseButton.x < 800 and event.mouseButton.y < 800))
                        {
                            return 0;
                        }
                    }

                }
                
        }

        window.display();
    }
}

//1 - Make it so you can't click on the same spot again
//2 - Stop the glitching when victory
//3 - Add menu
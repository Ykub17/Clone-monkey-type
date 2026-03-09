#include "Game.hpp"
#include "Config.hpp"
#include <random>
#include <ctime>
#include <iostream>


Game::Game() 
{
    // Сглаживание до создания окна
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8; 
    //Создаем окно 
    window.create(sf::VideoMode(Config::WIDTH, Config::HEIGHT), "Monkeytype Clone", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    
    if (!font.loadFromFile(Config::FONT_PATH))
    {
        std::cerr << "Failed to load font\n";
    }
    const_cast<sf::Texture&>(font.getTexture(Config::FONT_SIZE)).setSmooth(true);// Сглаживание шрифта 
    const_cast<sf::Texture&>(font.getTexture(32)).setSmooth(true); // Сглаживание текста кнопки
    
    // Инициализация генератора случайных чисел
    srand(static_cast<unsigned>(time(nullptr)));

    // Выбираем случайный текст из списка
    int randomIndex = std::rand() % Config::SENTENCES.size();
    std::string randomText = Config::SENTENCES[randomIndex];

    handler = new TypingHandler(randomText); 
    renderer = new Renderer(font);

    // Настройка кнопки перезапуска
    restartButton.setFillColor(sf::Color(234, 196, 53));
    restartButton.setOutlineThickness(3);
    restartButton.setOutlineColor(sf::Color(200, 160, 0));
    restartButton.setSize(sf::Vector2f(200, 60));

    restartButton.setOrigin(100, 30); // Центрируем кнопку по её размеру (половина ширины и половина высоты)
    restartButton.setPosition(Config::WIDTH / 2.0f, 700.0f);//

    // Настройка текста на кнопке
    restartText.setFont(font);
    restartText.setString("RESTART");
    restartText.setCharacterSize(32); 
    restartText.setScale(1.0f, 1.0f); 
    restartText.setFillColor(sf::Color::Black);

    // Центрируем сам текст 
    sf::FloatRect textRect = restartText.getLocalBounds();
    restartText.setOrigin(textRect.left + textRect.width / 2.0f, 
                          textRect.top + textRect.height / 2.0f);

    // Устанавливаем тексту ту же позицию, что и у кнопки
    restartText.setPosition(restartButton.getPosition());

    smoothedCursorPos = sf::Vector2f(100.f, 200.f);
}

// Деструктор
Game::~Game() 
{
    delete handler;
    delete renderer;
}

// Главный цикл игры
void Game::run() 
{
    while (window.isOpen()) 
    {
        processEvents(); 
        render();        
    }
}

// Обработка событий
void Game::processEvents() 
{
    sf::Event event;
    while (window.pollEvent(event)) 
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) 
        {
            delete handler; 
            int nextIndex = std::rand() % Config::SENTENCES.size();
            handler = new TypingHandler(Config::SENTENCES[nextIndex]);
            smoothedCursorPos = renderer->getCursorTargetPos(*handler);
        }
        // Обработка клика по кнопке перезапуска
        if (event.type == sf::Event::MouseButtonPressed) 
        {
            if (event.mouseButton.button == sf::Mouse::Left) 
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (restartButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    delete handler;
                    int nextIndex = std::rand() % Config::SENTENCES.size();
                    handler = new TypingHandler(Config::SENTENCES[nextIndex]);
                    smoothedCursorPos = renderer->getCursorTargetPos(*handler);
                }
            }
        }
        // Получаем позицию мыши относительно окна
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mouseCoords = window.mapPixelToCoords(mousePos);

        // Проверяем, находится ли курсор над кнопкой
        if (restartButton.getGlobalBounds().contains(mouseCoords)) 
        {
            restartButton.setFillColor(sf::Color(212, 175, 55)); // Светлеет при наведении
            restartButton.setScale(1.05f, 1.05f);               // Увеличение

        } else {
            restartButton.setFillColor(sf::Color(234, 196, 53));  
            restartButton.setScale(1.0f, 1.0f);                 
        }
        // Обработка ввода текста, только если игра не закончилась
        if (!handler->isFinished() && event.type == sf::Event::TextEntered) 
        {
            handler->handleInput(event.text.unicode);
        }
    }
}

// Отрисовка игры
void Game::render() 
{
    window.clear(Config::COLOR_BG);
    
    if (handler->isFinished()) 
    {
        renderer->drawResults(window, handler->getMistakes(), handler->getTime(), static_cast<int>(handler->getTyped().size()));
    } else {
        sf::Vector2f targetPos = renderer->getCursorTargetPos(*handler);
        float speed = 0.15f; 
        smoothedCursorPos.x += (targetPos.x - smoothedCursorPos.x) * speed;
        smoothedCursorPos.y += (targetPos.y - smoothedCursorPos.y) * speed;

        renderer->drawGame(window, *handler, smoothedCursorPos);
    }
    
    renderer->drawRestartButton(window, restartButton, restartText);
    window.display();
}
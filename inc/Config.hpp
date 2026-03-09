#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <SFML/Graphics.hpp>

namespace Config 
{
    const int WIDTH = 1920;
    const int HEIGHT = 1080;
    const int FONT_SIZE = 50;
    const std::string FONT_PATH = "/System/Library/Fonts/Monaco.ttf"; 

    
    const sf::Color COLOR_BG(32, 34, 37);
    const sf::Color COLOR_BASE(80, 80, 80);
    const sf::Color COLOR_CORRECT(210, 210, 210);
    const sf::Color COLOR_WRONG(219, 30, 58);
    const sf::Color COLOR_CURSOR(255, 213, 0);
    const std::vector<std::string> SENTENCES = 
{
    // --- Цитаты о программировании (Средний объем) ---
    "Programming isn't about what you know; it's about what you can figure out. "
    "The best programs are written so that computing machines can execute them quickly "
    "and humans can understand them clearly.",

    "The function of a good software framework is to provide a structured environment "
    "where developers can build complex applications without reinventing the wheel "
    "every single time they start a new project.",

    // --- Технические тексты (Большой объем) ---
    "Object-oriented programming is a paradigm based on the concept of objects, "
    "which can contain data in the form of fields and code in the form of procedures. "
    "A feature of objects is that an object's own procedures can access and often "
    "modify the data fields of itself.",

    "The Standard Template Library is a powerful set of C++ template classes to provide "
    "common programming data structures and functions such as vectors, lists, queues, "
    "and stacks. It is a library of container classes, algorithms, and iterators.",

    // --- Тексты про IT-культуру (Большой объем) ---
    "Open source software is code that is designed to be publicly accessible. "
    "Anyone can see, modify, and distribute the code as they see fit. It is developed "
    "in a decentralized and collaborative way, relying on peer review and community production.",

    "Cybersecurity is the practice of protecting systems, networks, and programs from "
    "digital attacks. These attacks are usually aimed at accessing, changing, or "
    "destroying sensitive information or interrupting normal business processes.",

    // --- Философский/Общий текст (Максимальный объем) ---
    "In the world of software development, the only constant is change. Technologies "
    "emerge and vanish, but the fundamental principles of logic and problem solving "
    "remain the same. Success as a developer requires continuous learning, patience, "
    "and the ability to adapt to new tools and environments quickly."
};
}
#endif
#include "boost/signals2/signal.hpp"
#include <iostream>

//SIGNALS SYSTEM

class Text {
public:
    void setText(const std::string& text) { /*...*/ TextChanged(5); }
    boost::signals2::signal<void(int)> TextChanged; //Сигнал
};

class Button {
public:
    Button() {
        text.TextChanged.connect(std::bind(&Button::reDraw, this, std::placeholders::_1));
    }
    Text text;
    void reDraw(int priority) { std::cout << "redraw with priority: " << priority <<std::endl; }
};

//BASIC REALIZATION

class Button2;

class Text2 {
public:
    Text2(Button2 *parent) : ptr(parent) {}
    void TextChanged(int n);
    void setText(const std::string& text) { /*...*/ TextChanged(5); }
    Button2* ptr;
};

class Button2 {
public:
    void reDraw(int priority) { std::cout << "redraw with priority: " << priority; }
    Button2() : text(this) {}
    Text2 text;
};

void Text2::TextChanged(int n) { ptr->reDraw(n); }

int main() {
    Button mainButton;
    mainButton.text.setText("test");
    Button2 mainButton2;
    mainButton2.text.setText("test");
}
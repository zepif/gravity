#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <unistd.h>
#include <vector>
#define double long double
using namespace sf;
using namespace std;

//Функция определения знака
double sign(double a) {
    if (a < 0) return -1;
    if (a == 0) return 0;
    return 1;
}

//Создание структуры вектора и операции с ним
struct vec {
    double x;
    double y;
    // double z;
};

//Создание класса обьекта
class object {
public:
    // Задание массы обьекта
    double mass;
    // Задание координат обьекта
    double x;
    double y;
    // Задание скорости обьекта, ускорения и сил соответственно
    vec v;
    vec a;
    vec F;
};

int main() {
    // cout << setpresition(3);
    // rect.SetOrigin(400, 300);
    // Задание констант
    double G = 1;
    double dt = 0.05;
    // Создать окно программы
    RenderWindow window(VideoMode(400, 700), "It works!");
    // Создаем часы
    Clock clock;
    // Создаем обьекты
    object A, B;
    A.x = 210;
    A.y = 200;
    B.x = 600;
    B.y = 548;

    A.v.x = 5;
    A.v.y = 5;
    B.v.x = -5;
    B.v.y = -5;
    A.mass = 10;
    B.mass = 5000;
    // Главный цикл программы
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            // Закрытие окна
            if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
                window.close();
        }

        // Очистка экрана
        window.clear(Color::Black);
        //Часики
        usleep(1);
        clock.restart();
        // Отрисовка
        CircleShape shape(10);
        shape.setPosition(A.x, A.y);
        shape.setFillColor(Color::Green);
        window.draw(shape);
        shape.setPosition(B.x, B.y);
        shape.setFillColor(Color::Red);
        window.draw(shape);
        // Если обьекты сблизились слишком сильно
        if (sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y)) < 20) {
            swap(A.v.x, B.v.x);
            swap(A.v.y, B.v.y);
        }
        // Расчет сил на обьекты
        double alf = atan((A.x - B.x) / (A.y - B.y));
        double bet = atan((B.x - A.x) / (B.y - A.y));
        double F_A = G * (A.mass * B.mass) / ((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
        double F_B = G * (A.mass * B.mass) / ((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));

        A.F.x = -abs(sin(alf) * F_A) * sign(A.x - B.x);
        A.F.y = -abs(cos(alf) * F_A) * sign(A.y - B.y);
        B.F.x = -abs(sin(bet) * F_B) * sign(B.x - A.x);
        B.F.y = -abs(cos(bet) * F_B) * sign(B.y - A.y);
        // Расчет ускорений обьектов
        A.a.x = A.F.x / A.mass;
        A.a.y = A.F.y / A.mass;
        B.a.x = B.F.x / B.mass;
        B.a.y = B.F.y / B.mass;

        // Расчет скоростей обьектов
        A.v.x += A.a.x * dt;
        A.v.y += A.a.y * dt;
        B.v.x += B.a.x * dt;
        B.v.y += B.a.y * dt;

        // Расчет новых координвт обьектов
        cout << A.x << " " << A.y << "\t\t\t" << B.x << " " << B.y << "\n";
        A.x += A.v.x * dt;
        A.y += A.v.y * dt;
        B.x += B.v.x * dt;
        B.y += B.v.y * dt;
        if (A.x <= 0 || A.x >= 800) A.v.x = -A.v.x;
        if (A.y <= 0 || A.y >= 600) A.v.y = -A.v.y;
        if (B.x <= 0 || B.x >= 800) B.v.x = -B.v.x;
        if (B.y <= 0 || B.y >= 600) B.v.y = -B.v.y;
        // Отрисовка
        window.display();
    }
    return 0;
}

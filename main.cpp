#include <iostream>

using namespace std;

class Window {
private:
    int x = 0;
    int y = 0;

    int width = 10;
    int height = 10;
public:

    void setX(int valueX) {
        x = valueX;
    }

    void setY(int valueY) {
        y = valueY;
    }

    void setHeight(int valueHeight) {
        height = valueHeight;
    }

    void setWidth(int valueWidth) {
        width = valueWidth;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    int getWigth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }
};

class Monitor {
private:
    int width = 80;
    int height = 50;

    Window *window = new Window;
public:

    void showMonitor() {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if ((i >= window->getY() and i <= window->getY() + window->getHeight() - 1) and
                    (j >= window->getX() and j <= window->getX() + window->getWigth() - 1)) {
                    cout << 1 << ' ';
                } else {
                    cout << 0 << ' ';
                }
            }
            cout << endl;
        }
    }

    bool setPos(int x, int y) {
        if (window->getX() + x < 0 or window->getX() + window->getWigth() + x > width) {
            cerr << "The window goes off the screen horizontally. Try again" << endl;
            return false;
        } else if (window->getY() + y < 0 or window->getY() + window->getHeight() + y > height) {
            cerr << "The window goes off the screen vertically. Try again" << endl;
            return false;
        } else {
            window->setX(window->getX() + x);
            window->setY(window->getY() + y);
            return true;
        }
    }

    bool setScale(int win_height, int win_width) {
        if (win_height < 1 or window->getY() + win_height > height) {
            cerr << "The height of the window is greater than the height of the monitor. Try again" << endl;
            return false;
        } else if (win_width < 1 or window->getX() + win_width > width) {
            cerr << "The width of the window is greater than the width of the monitor. Try again" << endl;
            return false;
        } else {
            window->setHeight(win_height);
            window->setWidth(win_width);
            return true;
        }
    }

    pair<int, int> getScale() {
        return make_pair(window->getWigth(), window->getHeight());
    }

    pair<int, int> getPos(){
        return make_pair(window->getX(), window->getY());
    }

    void close() {
        delete window;
        window = nullptr;
    }
};

int main() {
    auto *monitor = new Monitor;
    std::string command;

    while (true) {
        cout << "Enter the command (move, scale, display, close): ";
        cin >> command;

        if (command == "move") {
            int x, y;
            pair<int, int> pos = monitor->getPos();

            while (true) {
                cout << "Window position: x - " << pos.first << ", y - " << pos.second << endl << endl;
                cout << R"(Enter the horizontal offset of the window ("digit" - right, "-digit" - left): )";
                cin >> x;
                cout << R"(Enter the vertical offset of the window ("digit" - down, "-digit" - up): )";
                cin >> y;
                if (monitor->setPos(x, y)) break;
            }

        } else if (command == "scale") {
            int height, width;
            pair<int, int> size = monitor->getScale();

            while (true) {
                cout << "Window size: width - " << size.first << ", height - " << size.second << endl << endl;
                cout << "Enter window width in pixels: ";
                cin >> width;
                cout << "Enter window height in pixels: ";
                cin >> height;
                if (monitor->setScale(height, width)) break;
            }
        } else if (command == "display") {
            monitor->showMonitor();
        } else if (command == "close") {
            monitor->close();
            delete monitor;
            monitor = nullptr;
            break;
        } else {
            cerr << "Wrong input! Try again." << endl;
        }
    }
    return 0;
}

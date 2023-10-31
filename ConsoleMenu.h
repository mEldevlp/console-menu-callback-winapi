#pragma once

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <functional>
#include <vector>

enum KEY {
    ENTER = 13,
    ESC = 27,
    SPACE = 32,
    UP = 72,
    DOWN = 80,
};

enum Color {
    RED = FOREGROUND_RED,
    GREEN = FOREGROUND_GREEN,
    BLUE = FOREGROUND_BLUE,
    INTENSITY = FOREGROUND_INTENSITY
};

typedef struct menu_item_s
{
    int Info;
    std::string Text;
    bool Disabled;
    int Extra;
} menu_item_t;

class Console
{
public:
    virtual void SetCursorVisible(bool bVisible, int16_t size);
    virtual void MoveToXY(int16_t x, int16_t y);

    Console(int16_t width, int16_t height);
    virtual ~Console();

    Console() = delete;
    Console(const Console& c) = delete;

protected:
    HANDLE m_hConsole;
    CONSOLE_CURSOR_INFO m_cursor_info;
    CONSOLE_SCREEN_BUFFER_INFO m_screen_buffer_info;
    const wchar_t* m_szTitle;
    int16_t m_width;
    int16_t m_height;
};

class ConsoleMenu : public Console
{
public:
    ConsoleMenu(int16_t width, int16_t height) : Console(width, height) {}

    void Clear();
    bool InitMenu(const wchar_t* Title, std::function<void(menu_item_t Info)> CallbackFunction);
    void AddItem(int Info, std::string Text);
    void AddItem(int Info, std::string Text, bool Disabled);
    void AddItem(int Info, std::string Text, bool Disabled, int Extra);
    bool DrawMenu();
    bool HandleCallback(int key);
    size_t GetMenuSize();
    void SetColor(Color clr);

private:
    uint16_t m_active_item;
    int16_t m_active_height;
    int32_t m_menu_color;

    std::vector<menu_item_t> m_vecData;
    std::function<void(menu_item_t Info)> m_fnCallback = nullptr;
};
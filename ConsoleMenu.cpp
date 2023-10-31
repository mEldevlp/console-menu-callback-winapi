#include "ConsoleMenu.h"

void Console::MoveToXY(int16_t x, int16_t y)
{
    SetConsoleCursorPosition(this->m_hConsole, { x, y });
}

Console::Console(int16_t width, int16_t height)
{
    this->m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(this->m_hConsole, &this->m_cursor_info);
    GetConsoleScreenBufferInfo(this->m_hConsole, &this->m_screen_buffer_info);

    this->m_width = width;
    this->m_height = height;
    this->m_szTitle = L"";

    COORD size = { width, height };
    SetConsoleScreenBufferSize(this->m_hConsole, size);
    SMALL_RECT DisplayArea = { 0, 0, width - 1, height - 1 };
    SetConsoleWindowInfo(this->m_hConsole, TRUE, &DisplayArea);
}

Console::~Console()
{
    delete this;
}

void ConsoleMenu::Clear()
{
    this->m_szTitle = NULL;
    this->m_vecData.clear();
    this->m_fnCallback = nullptr;
}

bool ConsoleMenu::InitMenu(const wchar_t* Title, std::function<void(menu_item_t Info)> CallbackFunction)
{
    system("cls");

    this->Clear();

    this->m_szTitle = Title;
    this->m_fnCallback = std::move(CallbackFunction);
    this->m_active_item = 0;

    SetCursorVisible(false, 100);
    SetConsoleTitle(this->m_szTitle);

    return true;
}

void ConsoleMenu::AddItem(int Info, std::string Text)
{
    this->AddItem(Info, Text, false, 0);
}

void ConsoleMenu::AddItem(int Info, std::string Text, bool Disabled)
{
    this->AddItem(Info, Text, Disabled, 0);
}

void ConsoleMenu::AddItem(int Info, std::string Text, bool Disabled, int Extra)
{
    menu_item_t menu_item = { Info, Text, Disabled, Extra };

    this->m_vecData.push_back(menu_item);
}

bool ConsoleMenu::DrawMenu()
{
    system("cls");
    char ch;

    this->m_active_height = this->m_height / 2;

    MoveToXY(this->m_width / 2 - 3, this->m_active_height);

    for (size_t i = 0; i < this->GetMenuSize(); ++i)
    {
        if (i == this->m_active_item)
        {
            SetConsoleTextAttribute(this->m_hConsole, this->m_menu_color | Color::INTENSITY);
        }
        else
        {
            SetConsoleTextAttribute(this->m_hConsole, this->m_menu_color);
        }

        MoveToXY(this->m_width / 2 - 3, this->m_active_height++);
        std::cout << this->m_vecData[i].Text << std::endl;
    }

    ch = _getch();

    if (ch == -32) ch = _getch(); // magic
    else if (ch == '\n') ch = _getch();

    switch (static_cast<KEY>(ch))
    {
        case KEY::ESC:      exit(0);
        case KEY::UP:
        {
            if (this->m_active_item == 0) break;
            this->m_active_item--;
            break;
        }
        case KEY::DOWN:
        {
            if (this->m_active_item == this->GetMenuSize() - 1) break;
            this->m_active_item++;
            break;
        }
        case KEY::ENTER:
        case KEY::SPACE:
        {
            this->HandleCallback(this->m_active_item);
            break;
        }
        default: break;
    }

    return true;
}

bool ConsoleMenu::HandleCallback(int key)
{
    if (this->m_fnCallback)
    {
        this->m_fnCallback(this->m_vecData[key]);
        return true;
    }

    return false;
}

size_t ConsoleMenu::GetMenuSize()
{
    return this->m_vecData.size();
}

void ConsoleMenu::SetColor(Color clr)
{
    this->m_menu_color = static_cast<int32_t>(clr);
}

void Console::SetCursorVisible(bool bVisible, int16_t size)
{
    this->m_cursor_info.bVisible = bVisible;
    this->m_cursor_info.dwSize = static_cast<DWORD>(size);

    SetConsoleCursorInfo(this->m_hConsole, &this->m_cursor_info);
}
#include "ConsoleMenu.h"

void Handle_Menu(menu_item_t Info)
{
    system("cls");

    std::cout << Info.Text.c_str() << std::endl;

    _getch();
}

int main(int argc, char* argv[])
{
    ConsoleMenu* console_menu = new ConsoleMenu(100, 40);

    console_menu->InitMenu(L"Custom menu in console", Handle_Menu);
    console_menu->AddItem(1, "New Game");
    console_menu->AddItem(2, "Load");
    console_menu->AddItem(3, "Settings");
    console_menu->AddItem(4, "Exit");
    console_menu->SetColor(Color::RED);
    //console_menu->SetColor(Color::BLUE);
    //console_menu->SetColor(Color::GREEN);

    while (true)
    {
        console_menu->DrawMenu();
    }

    return 0;
}
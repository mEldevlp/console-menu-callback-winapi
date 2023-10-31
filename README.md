<div align="center">
  <h3>Console Menu with callback functions</h3>
</div> 

#### Navigation
- Up Arrow to up
- Down Arrow to down
- Enter or Space to choose item

#### Usage

Init Console window
```cpp
ConsoleMenu* console_menu = new ConsoleMenu(100, 40); // 100 - width; 40 - height
```

Init Menu and add items
```cpp
console_menu->InitMenu(L"Custom menu in console", Handle_Menu); // Handle_Menu - callback function. Proto: `void Handle_Menu(menu_item_t Info)`
console_menu->AddItem(1, "New Game");
console_menu->AddItem(2, "Load");
console_menu->AddItem(3, "Settings");
console_menu->AddItem(4, "Exit");
```

Set color for the menu items
```cpp
console_menu->SetColor(Color::RED);
```

In infinity loop draw the menu
```cpp
while (true)
{
    console_menu->DrawMenu();
}
```

#### Preview


![src1](https://i.ibb.co/5xxPMBV/Screenshot-1.png)

Enter on item

![src2](https://i.ibb.co/85JtqSD/Screenshot-2.png)

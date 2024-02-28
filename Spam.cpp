#include <iostream>
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>

using namespace std;

bool thread_finish = false;
bool finish = false;

void Spam()
{
    // Открытие файла для чтения
    ifstream fin("Input.txt", std::ios::binary);
    if (!fin.is_open()) {
        cout << "Error Open File" << endl;
    }

    // Инициализация генератора случайных чисел
    srand(static_cast<unsigned int>(time(nullptr)));

    string str;
    while (getline(fin, str)) {
        wstring message = wstring(str.begin(), str.end()); // Преобразование из std::string в std::wstring

        // Отправка сообщения
     
        // Включение левого шифта
        keybd_event(VK_SHIFT, 0, 0, 0);  // Key Down

        for (wchar_t ch : message) {
            while (finish)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            keybd_event(VkKeyScanW(ch), 0, 0, 0);  // Key Down
            keybd_event(VkKeyScanW(ch), 0, KEYEVENTF_KEYUP, 0);  // Key Up
            keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);  // Key Up
            Sleep(rand() % 150 + 50);
        }

        // Нажатие и отпускание Enter 
        keybd_event(VK_RETURN, 0, 0, 0);  // Key Down
        keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);  // Key Up

        // Задержка между сообщениями
        //Sleep(rand() % 5000 + 1000);
    }
    

    // Закрытие файла
    fin.close();
    thread_finish = true;
}



int main() {

    // Задержка перед отправкой первого сообщения
        Sleep(10000);
    thread write(Spam);
    write.detach();

    while (true)
    {
        if (GetKeyState('X') & 0x8000 & GetKeyState(VK_LCONTROL) & 0x8000)
        {
            finish = !finish;
        }
        else if (GetKeyState('C') & 0x8000 & GetKeyState(VK_LCONTROL) & 0x8000 || thread_finish)
        {
            write.~thread();
            break;
        }
        
    }

 
    
    return 0;
}

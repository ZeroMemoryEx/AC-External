#include"Offsets.h"

using namespace std;


/*
 By anas
github :https://github.com/walczy
*/

void Title(HANDLE  hProcess, DWORD procID);
uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName)
{
    uintptr_t modBaseAddr = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
    if (hSnap != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry))
        {
            do
            {
                if (!_wcsicmp(modEntry.szModule, modName))
                {
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return modBaseAddr;
}

void Menu();
uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, vector<unsigned int> offsets)
{
    uintptr_t addr = ptr;
    for (unsigned int i = 0; i < offsets.size(); ++i)
    {
        ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), NULL);
        addr += offsets[i];
    }
    return addr;
}


void ReadWriteProces(DWORD procID ,HANDLE  hProcess, uintptr_t playb, vector<unsigned int> offsets,int row)
{
    uintptr_t modulebase = GetModuleBaseAddress(procID, L"ac_client.exe");
    uintptr_t  addx = FindDMAAddy(hProcess, playb, offsets);
    int res = 1337;
    if (row == 1)
    {
        WriteProcessMemory(hProcess, (LPVOID)addx, &res, sizeof(res), NULL);
    }

    else
    {
        ReadProcessMemory(hProcess, (LPCVOID)addx, &res, sizeof(res), NULL);
        cout << res << endl;
    }

}

void IsConsoleVisible()
{
    bool re = (IsWindowVisible(GetConsoleWindow()));
    if (re == 0x0)
    {
        ShowWindow(GetConsoleWindow(), SW_SHOW);
    }
    else
    {
        ShowWindow(::GetConsoleWindow(), SW_HIDE);
    }

}
int main()
{
    Menu();
    HWND hwnd = FindWindowA(NULL, "AssaultCube");
    if (hwnd == NULL)
    {
        MessageBox(hwnd, _T("Please Make  Sure The  Game is  running and try again !"), _T("Error  Could not  find the game window"), MB_ICONERROR);
        ExitProcess(0);
    }
    DWORD procID;
    GetWindowThreadProcessId(hwnd, &procID);
    HANDLE  hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
    thread title(Title, hProcess, procID);
    while (true)
    {

        if (GetAsyncKeyState(VK_F1))
        {
            ReadWriteProces(procID,hProcess, 0x00509B74, ammo,1); // ammo
            //ReadWriteProces(procID, hProcess, 0x00509B74, ammo, 0);
            Sleep(200);
        }
        if (GetAsyncKeyState(VK_F2))
        {
            ReadWriteProces(procID,hProcess, pb, hpof,1); // health
            Sleep(200);
        }
        if (GetAsyncKeyState(VK_F3))
        {
            WriteProcessMemory(hProcess, (LPVOID)0x463786, "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90", 10, NULL);//no recoil
            Sleep(200);
        }

        if (GetAsyncKeyState(VK_INSERT))//Hide console
        {
            
            IsConsoleVisible();
            Sleep(200);

        }
        /*if (GetAsyncKeyState(VK_F5))
        {
            
        }*/
        
    }
    title.join();
}

void Title(HANDLE  hProcess, DWORD procID)
{

    char name[30];
    int base;
    ReadProcessMemory(hProcess, (LPCVOID)(player_base), &base, sizeof(base), nullptr);
    ReadProcessMemory(hProcess, (PBYTE)(base + 0x225), &name, sizeof(name), nullptr);

    string sname = "Welcome Back '";
    sname += name;
    sname += " 'To AC External";
    HWND console = GetConsoleWindow();
    RECT ConsoleRect;
    GetWindowRect(console, &ConsoleRect);
    MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 800, 300, TRUE);
    /*while (true)
    {
        SetConsoleTitleA(sname.c_str());
    }
    */

    char sp[] = "External Hack Created By anas";

    while (0x1)
    {
        SetConsoleTitleA("C");
        Sleep(100);
        SetConsoleTitleA("Cr");
        Sleep(100);
        SetConsoleTitleA("Crea");
        Sleep(200);
        SetConsoleTitleA("Creat");
        Sleep(100);
        SetConsoleTitleA("Created");
        Sleep(150);
        SetConsoleTitleA("Created B");
        Sleep(150);
        SetConsoleTitleA("Created By");
        Sleep(150);
        SetConsoleTitleA("Created By A");
        Sleep(150);
        SetConsoleTitleA("Created By An");
        Sleep(150);
        SetConsoleTitleA("Created By Ana");
        Sleep(150);
        SetConsoleTitleA("Created By Anas");
        Sleep(3000);
        SetConsoleTitleA(sname.c_str());
        Sleep(4000);
    }
}
void Menu()
{
    cout << "F1" << setfill(' ') << setw(25);
    cout << "Unlimited Ammo" << endl;
    cout << "F2" << setfill(' ') << setw(25);
    cout << "Unlimited Health" << endl;
    cout << "F3" << setfill(' ') << setw(25);
    cout << "No Recoil" << endl;
    cout << "INSERT" << setfill(' ') << setw(21);
    cout << "Hide Hack" << endl;
}

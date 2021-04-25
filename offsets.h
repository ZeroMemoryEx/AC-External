#include<vector>
#include<iostream>
#include<Windows.h>
#include <string>
#include<tlhelp32.h>
#include<TlHelp32.h>
#include<thread>
#include <tchar.h>
#include<iomanip>



uintptr_t pb = 0x00509B74; 


static int of_name = { 0x225 };
static int baseadd = 0x00400000;
static int oba = 0x0010F4F4;
static int player_base = baseadd + oba;

std::vector<unsigned int>ammo = { 0x0150 };

std::vector<unsigned int>hpof = { 0xF8 };
//std::vector<unsigned int>grenad = { 0x158,0x38,0x200,0x48,0x1F4,0x58 };

std::vector<unsigned int>name = { 0x225 };




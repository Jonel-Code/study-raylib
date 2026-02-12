#pragma once

#include "iostream"
#include "string"
#include "raylib.h"

class Printer
{
public:
    std::string Data;

    Printer(std::string Input)
    {
        Data = Input;
    }
    Printer()
    {
        Data = "";
    }

    void HookInput()
    {
        const int CharInput = GetKeyPressed();
        if (CharInput == 0)
        {
            return;
        }

        std::cout << "Input UniCode " << CharInput << '\n';

        /// backspace
        if (CharInput == 259)
        {
            Data.pop_back();
            return;
        }

        std::string strBuff;
        /// new line
        if (CharInput == 257)
        {
            strBuff = '\n';
        }
        else
        {
            strBuff = (char)CharInput;
        }

        Data.append(strBuff);
    }

    void RenderText()
    {
        DrawText(Data.c_str(), 0, 0, 20, BLACK);
    }

    void Update(){
        HookInput();
        RenderText();
    }
};
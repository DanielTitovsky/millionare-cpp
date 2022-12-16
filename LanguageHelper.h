#pragma once
#include <iostream>

class LanguageHelper
{
private:
    static const int N = 67;

public:
    static std::string Translit(std::string input)
    {
        const char DosABC[N] = "abvgdeejzijklmnoprstyfhchhh'i'eyaABVGDEEJZIIKLMNOPRSTYFHCHHH'I'EYA";
        const char WinABC[N] = "àáâãäå¸æçèéêëìíîïğñòóôõö÷øùúûüışÿÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞß";

        std::string output = "";
        bool Ok;
        for (unsigned i = 0; i < input.length(); i++)
        {
            Ok = false;
            for (int j = 0; j < N; j++)
                if (input[i] == WinABC[j])
                {
                    output += DosABC[j];
                    Ok = true;
                }
            if (!Ok)
                output += input[i];
        }
        return output;
    }

};
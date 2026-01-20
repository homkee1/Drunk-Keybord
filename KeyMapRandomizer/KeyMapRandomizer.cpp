#include <iostream>
#include <windows.h>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <random>
#include <algorithm>

static bool useAllLetters = true; // vse bukvi
static bool includeDigits = true; // eshe i cifri
static bool persistentMapping = true; // ne menyat kajdii klik
static bool isConsole = false; // consol
static bool altf5close = true; // altf5close

static const std::vector<int> customKeys = {
    'T', 'Y', 'U', 'R', 'Q', 'Z', 'X', 'C', 'V', 'B', 'N', 'G', 'H', 'J', 'M', 'L'
};

static std::unordered_map<int, int> keyMapping;
static std::unordered_map<int, int> permanentKeyMapping;
static std::random_device rd;
static std::mt19937 gen(rd());
static std::vector<int> targetKeys;
static std::unordered_set<int> keysToRemap;
static bool altPressed = false;
static bool f5Pressed = false;

void InitializeKeys() {
    targetKeys.clear();
    keysToRemap.clear();
    permanentKeyMapping.clear();

    if (useAllLetters) {
        for (int i = 'A'; i <= 'Z'; ++i) {
            targetKeys.push_back(i);
            keysToRemap.insert(i);
        }
    }
    else {
        targetKeys = customKeys;
        keysToRemap = std::unordered_set<int>(customKeys.begin(), customKeys.end());
    }

    if (includeDigits) {
        for (int i = '0'; i <= '9'; ++i) {
            targetKeys.push_back(i);
            keysToRemap.insert(i);
        }
    }

    if (persistentMapping) {
        std::vector<int> shuffledKeys = targetKeys;
        std::shuffle(shuffledKeys.begin(), shuffledKeys.end(), gen);
        for (size_t i = 0; i < targetKeys.size(); ++i) {
            permanentKeyMapping[targetKeys[i]] = shuffledKeys[i];
        }
    }
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pKeyboard = (KBDLLHOOKSTRUCT*)lParam;

        if (altf5close && (pKeyboard->vkCode == VK_MENU || pKeyboard->vkCode == VK_LMENU || pKeyboard->vkCode == VK_RMENU)) {
            if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
                altPressed = true;
            }
            else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
                altPressed = false;
            }
        }

        if (altf5close && pKeyboard->vkCode == VK_F5) {
            if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
                if (altPressed) {
                    PostQuitMessage(0);
                    return 1;
                }
            }
        }

        if (pKeyboard->flags & LLKHF_INJECTED) {
            return CallNextHookEx(NULL, nCode, wParam, lParam);
        }

        if (keysToRemap.find(pKeyboard->vkCode) != keysToRemap.end()) {
            if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
                if (keyMapping.find(pKeyboard->vkCode) != keyMapping.end()) {
                    return 1;
                }

                int randomKey;

                if (persistentMapping) {
                    randomKey = permanentKeyMapping[pKeyboard->vkCode];
                }
                else {
                    std::uniform_int_distribution<> dist(0, targetKeys.size() - 1);
                    randomKey = targetKeys[dist(gen)];
                }

                keyMapping[pKeyboard->vkCode] = randomKey;

                INPUT input = { 0 };
                input.type = INPUT_KEYBOARD;
                input.ki.wVk = randomKey;
                SendInput(1, &input, sizeof(INPUT));
                return 1;
            }
            else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
                auto it = keyMapping.find(pKeyboard->vkCode);
                if (it != keyMapping.end()) {
                    INPUT input = { 0 };
                    input.type = INPUT_KEYBOARD;
                    input.ki.wVk = it->second;
                    input.ki.dwFlags = KEYEVENTF_KEYUP;
                    SendInput(1, &input, sizeof(INPUT));
                    keyMapping.erase(it);
                }
                return 1;
            }
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    if (!isConsole) ShowWindow(GetConsoleWindow(), SW_HIDE);
    InitializeKeys();
    HHOOK hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    if (hHook == NULL) return 1;
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(hHook);
    return 0;
}

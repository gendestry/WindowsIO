#include "WindowsIO.h"
#include <Windows.h>
#include <iostream>


// SCREEN metrics
JNIEXPORT jint JNICALL Java_WindowsIO_getScreenSizeX(JNIEnv*, jobject) {
    return GetSystemMetrics(SM_CXSCREEN);
}

JNIEXPORT jint JNICALL Java_WindowsIO_getScreenSizeY(JNIEnv*, jobject) {
    return GetSystemMetrics(SM_CYSCREEN);
}

JNIEXPORT jint JNICALL Java_WindowsIO_getVirtualScreenSizeX(JNIEnv*, jobject) {
    return GetSystemMetrics(SM_CXVIRTUALSCREEN);
}

JNIEXPORT jint JNICALL Java_WindowsIO_getVirtualScreenSizeY(JNIEnv*, jobject) {
    return GetSystemMetrics(SM_CYVIRTUALSCREEN);
}


// WINDOW metrics
JNIEXPORT jobject JNICALL Java_WindowsIO_getForegroundWindowMetrics(JNIEnv* env, jobject) {
    RECT rect = { NULL };
    
    GetWindowRect(GetForegroundWindow(), &rect);

    jclass colorClass = env->FindClass("java/awt/Rectangle");
    jmethodID constr = env->GetMethodID(colorClass, "<init>", "(IIII)V");
    jobject ret = env->NewObject(colorClass, constr, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);

    return ret;
}


// KEY press, release
JNIEXPORT void JNICALL Java_WindowsIO_keyPress(JNIEnv*, jobject, jchar c) {
    INPUT ip;

    ip.type = INPUT_KEYBOARD;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.wVk = c;

    ip.ki.dwFlags = 0;
    ip.ki.wScan = 0;

    SendInput(1, &ip, sizeof(INPUT));
}

JNIEXPORT void JNICALL Java_WindowsIO_keyRelease(JNIEnv*, jobject, jchar c) {
    INPUT ip;

    ip.type = INPUT_KEYBOARD;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.wVk = c;

    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    ip.ki.wScan = 0;

    SendInput(1, &ip, sizeof(INPUT));
}


// KEY type (unicode)
JNIEXPORT void JNICALL Java_WindowsIO_typeChar (JNIEnv*, jobject, jchar c) {    
    INPUT ip;

    ip.type = INPUT_KEYBOARD;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.wVk = 0;

    ip.ki.dwFlags = KEYEVENTF_UNICODE;
    ip.ki.wScan = c;

    SendInput(1, &ip, sizeof(INPUT));

    ip.ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;            // KEYEVENTF_KEYUP for key release
    SendInput(1, &ip, sizeof(INPUT));
}

JNIEXPORT void JNICALL Java_WindowsIO_typeString(JNIEnv* env, jobject obj, jstring str) {
    std::string s = env->GetStringUTFChars(str, NULL);
    for (int i = 0; i < s.length(); i++)
        Java_WindowsIO_typeChar(env, obj, s.at(i));
}


// MOUSE keys
JNIEXPORT void JNICALL Java_WindowsIO_mousePress(JNIEnv*, jobject, jchar code) {
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.mouseData = 0;
    input.mi.time = 0;
    input.mi.dx = 0;
    input.mi.dy = 0;
    input.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | code);
    SendInput(1, &input, sizeof(INPUT));
}

JNIEXPORT void JNICALL Java_WindowsIO_mouseRelease(JNIEnv*, jobject, jchar code) {
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.mouseData = 0;
    input.mi.time = 0;
    input.mi.dx = 0;
    input.mi.dy = 0;
    input.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | (code << 1));
    SendInput(1, &input, sizeof(INPUT));
}


// MOUSE cursor pos
JNIEXPORT jint JNICALL Java_WindowsIO_getMouseX (JNIEnv*, jobject) {
    POINT p;
    GetCursorPos(&p);
    return p.x;
}

JNIEXPORT jint JNICALL Java_WindowsIO_getMouseY(JNIEnv*, jobject) {
    POINT p;
    GetCursorPos(&p);
    return p.y;
}


// MOUSE movement
JNIEXPORT void JNICALL Java_WindowsIO_mouseMove(JNIEnv*, jobject, jint x, jint y) {
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.mouseData = 0;
    input.mi.time = 0;
    input.mi.dx = x * (0xFFFF / GetSystemMetrics(SM_CXSCREEN));//x being coord in pixels
    input.mi.dy = y * (0xFFFF / GetSystemMetrics(SM_CYSCREEN));//y being coord in pixels
    input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    SendInput(1, &input, sizeof(input));
}

JNIEXPORT void JNICALL Java_WindowsIO_mouseMoveVirtual(JNIEnv*, jobject, jint x, jint y) {
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.mouseData = 0;
    input.mi.time = 0;
    input.mi.dx = x * (0xFFFF / GetSystemMetrics(SM_CXVIRTUALSCREEN));//x being coord in pixels
    input.mi.dy = y * (0xFFFF / GetSystemMetrics(SM_CYVIRTUALSCREEN));//y being coord in pixels
    input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_ABSOLUTE;
    SendInput(1, &input, sizeof(input));
}

JNIEXPORT void JNICALL Java_WindowsIO_mouseMoveRelative(JNIEnv*, jobject, jint x, jint y) {
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.mouseData = 0;
    input.mi.time = 0;
    input.mi.dx = x;
    input.mi.dy = y;
    input.mi.dwFlags = MOUSEEVENTF_MOVE;
    SendInput(1, &input, sizeof(input));
}

JNIEXPORT void JNICALL Java_WindowsIO_mouseScroll(JNIEnv*, jobject, jint ydiff) {
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.time = 0;
    input.mi.dx = 0;
    input.mi.dy = 0;
    input.mi.mouseData = -ydiff * WHEEL_DELTA;
    input.mi.dwFlags = MOUSEEVENTF_WHEEL;
    SendInput(1, &input, sizeof(input));
}


// SCREEN gfx DATA
JNIEXPORT jobject JNICALL Java_WindowsIO_getPixel(JNIEnv* env, jobject, jint x, jint y) {
    HDC hdc = GetDC(NULL);
    DWORD color = GetPixel(hdc, x, y);
    unsigned int r = GetRValue(color);
    unsigned int g = GetGValue(color);
    unsigned int b = GetBValue(color);
    ReleaseDC(NULL, hdc);

    jclass colorClass = env->FindClass("java/awt/Color");
    jmethodID constr = env->GetMethodID(colorClass, "<init>", "(III)V");
    jobject ret = env->NewObject(colorClass, constr, r, g, b);

    return ret;
}

JNIEXPORT jbyteArray JNICALL Java_WindowsIO_getScreenshot(JNIEnv* env, jobject, jint x, jint y, jint width, jint height) {
    BITMAPINFO MyBMInfo = { 0 };
    MyBMInfo.bmiHeader.biSize = sizeof(MyBMInfo.bmiHeader);
    MyBMInfo.bmiHeader.biWidth = width;
    MyBMInfo.bmiHeader.biHeight = -height;
    MyBMInfo.bmiHeader.biPlanes = 1;
    MyBMInfo.bmiHeader.biBitCount = 24;
    MyBMInfo.bmiHeader.biCompression = BI_RGB;
    MyBMInfo.bmiHeader.biSizeImage = 0;
    MyBMInfo.bmiHeader.biXPelsPerMeter = 0;
    MyBMInfo.bmiHeader.biYPelsPerMeter = 0;
    MyBMInfo.bmiHeader.biClrUsed = 0;
    MyBMInfo.bmiHeader.biClrImportant = 0;

    // Create compatible DC, create a compatible bitmap and copy the screen using BitBlt()
    HDC hdcScreen = GetDC(0);
    HDC hdcCompatible = CreateCompatibleDC(hdcScreen);
    HBITMAP hBmp = CreateCompatibleBitmap(hdcScreen, width, height);
    HGDIOBJ hOldBmp = (HGDIOBJ)SelectObject(hdcCompatible, hBmp);

    BOOL bOK = BitBlt(hdcCompatible, 0, 0, width, height, hdcScreen, 0, 0, SRCCOPY | CAPTUREBLT);

    SelectObject(hdcCompatible, hOldBmp); // always select the previously selected object once done
    // Get the BITMAPINFO structure from the bitmap
    GetDIBits(hdcScreen, hBmp, 0, 0, NULL, &MyBMInfo, DIB_RGB_COLORS);

    // create the bitmap buffer
    char* lpPixels = new char[MyBMInfo.bmiHeader.biSizeImage];

    MyBMInfo.bmiHeader.biCompression = BI_RGB;
    MyBMInfo.bmiHeader.biBitCount = 24;

    // get the actual bitmap buffer
    GetDIBits(hdcScreen, hBmp, 0, -MyBMInfo.bmiHeader.biHeight, (LPVOID)lpPixels, &MyBMInfo, DIB_RGB_COLORS);

    //Clean Up
    ReleaseDC(0, hdcScreen);
    ReleaseDC(0, hdcCompatible);
    DeleteDC(hdcCompatible);
    DeleteDC(hdcScreen);
    DeleteObject(hBmp);
    DeleteObject(hOldBmp);

    jbyteArray array = env->NewByteArray(MyBMInfo.bmiHeader.biSizeImage);
    env->SetByteArrayRegion(array, 0, MyBMInfo.bmiHeader.biSizeImage, (jbyte*)lpPixels);

    delete[] lpPixels;
    return array;
}


// CLIPBOARD manipulation
JNIEXPORT jstring JNICALL Java_WindowsIO_getClipboardText(JNIEnv* env, jobject) {
    if (!OpenClipboard(nullptr))
        std::cout << "getClipboardText(): Cannot open clipboard!" << std::endl;

    HANDLE hData = GetClipboardData(CF_TEXT);
    if (hData == nullptr)
        std::cout << "getClipboardText(): Cannot get clipboard data!" << std::endl;

    char* pszText = static_cast<char*>(GlobalLock(hData));
    if (pszText == nullptr)
        std::cout << "getClipboardText(): Clipboard data empty!" << std::endl;

    std::string text(pszText);

    GlobalUnlock(hData);
    CloseClipboard();

    return env->NewStringUTF(text.c_str());
}

JNIEXPORT void JNICALL Java_WindowsIO_setClipboardText(JNIEnv* env, jobject, jstring str) {
    const char* output = env->GetStringUTFChars(str, NULL);
    const size_t len = strlen(output) + 1;

    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), output, len);

    GlobalUnlock(hMem);

    if (!OpenClipboard(nullptr))
        std::cout << "setClipboardText(): Cannot open clipboard!" << std::endl;

    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);

    CloseClipboard();
}
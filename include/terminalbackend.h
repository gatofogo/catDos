#ifndef terminalbackend_h
#define terminalbackend_h

#ifdef _WIN32
#include <windows.h>
#include <consoleapi2.h>
#include <wincontypes.h>
#endif

#include <iostream>

class terminalbackend{
public:
    virtual bool start(const std::wstring& exe)=0;
    //virtual void write(const std::string& data){};
    //virtual std::string read()=0;
    //virtual void stop(){};
    virtual ~terminalbackend()=default;
};

class win_terminalbackend : public terminalbackend{
private:
    HPCON hPty = nullptr;
    HANDLE hInRead = nullptr;
    HANDLE hInWrite = nullptr;
    HANDLE hOutRead = nullptr;
    HANDLE hOutWrite = nullptr;
    PROCESS_INFORMATION pi = {};
public:
    bool start(const std::wstring& exe) override;
    //void write(const std::string& data) override;
    //std::string read() override;
    //void stop() override;
};

#endif
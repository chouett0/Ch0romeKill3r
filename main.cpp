#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tlhelp32.h>

DWORD GetProcessId(LPSTR Target) {
    HANDLE hSnapShot;
    DWORD TargetProcessId = -1;
    if ((hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)) == INVALID_HANDLE_VALUE) {
    //    MessageBoxA(NULL, "Create Snapshot Failed", "GetProcessID Error", MB_OK);
        printf("[!] Error: Create Snapshot Failed");
        return -1;

    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(pe32);
    BOOL result = Process32First(hSnapShot, &pe32);
    while (result) {
        if (lstrcmp(Target, pe32.szExeFile) == 0) {
            TargetProcessId = pe32.th32ProcessID;
            break;

        }

        result = Process32Next(hSnapShot, &pe32);

    }
    return TargetProcessId;

}

int KillProcess(LPSTR TargetName) {
    DWORD TargetProcessId = GetProcessId(TargetName);
    HANDLE hTargetProc;
    int rslt;
    
    if ((TargetProcessId = GetProcessId(TargetName)) == -1) {
        printf("[!] Error: Get Process ID Failed");

    }

    printf("%d\n", (DWORD)TargetProcessId);
    if ((hTargetProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)TargetProcessId)) == 0) {
       // MessageBoxA(NULL, "Open Target Process Failed", "KillProcess Error", MB_OK);
        printf("[!] Error: Open Target Process Failed");
        return -1;

    }

    if (TerminateProcess((HANDLE)hTargetProc, 0) == 0)
    //    MessageBox(NULL, "Kill Target Process Failed", "KillProcess Error", MB_OK);
    printf("[!] Error: Kill Target Process Failed");

    return 0;

}

int main() {
    LPSTR TargetProcessName = "chrome.exe";
    KillProcess(TargetProcessName);

}
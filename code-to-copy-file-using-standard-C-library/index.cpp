// cpC.  Basic File Copy Program:  Windows Implementation

// Copy File1 to File2

#include <stdio.h>

#include <windows.h>

#include <stringapiset.h>

#define BUF_SIZE 16384

int main(int argc, char *argv[])
{

    HANDLE hIn, hOut;

    DWORD nIn, nOut;

    CHAR buffer[BUF_SIZE];

    LPWSTR lpwszFile1, lpwszFile2;

    INT iLen1, iLen2;

    if (argc != 3)
    {

        fprintf(stderr, "Usage: cp file1 file2\n");

        return 1;
    }

    lpwszFile1 = (LPTSTR)malloc(510);

    lpwszFile2 = (LPTSTR)malloc(510);

    iLen1 = MultiByteToWideChar(CP_ACP, 0, argv[1], -1, lpwszFile1, 510);

    iLen2 = MultiByteToWideChar(CP_ACP, 0, argv[2], -1, lpwszFile2, 510);

    hIn = CreateFile(lpwszFile1, GENERIC_READ, FILE_SHARE_READ, NULL,

                     OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hIn == INVALID_HANDLE_VALUE)
    {

        fprintf(stderr, "Cannot open input file. Error: %x\n", GetLastError());

        return 2;
    }

    hOut = CreateFile(lpwszFile2, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,

                      FILE_ATTRIBUTE_NORMAL, NULL);

    if (hOut == INVALID_HANDLE_VALUE)
    {

        fprintf(stderr, "cannot open output file. Error: %x\n", GetLastError());

        CloseHandle(hIn);

        return 3;
    }

    while ((ReadFile(hIn, buffer, BUF_SIZE, &nIn, NULL) &&nIn > 0)) {
        WriteFile(hOut, buffer, nIn, &nOut, NULL);

        if (nIn != nOut)
        {

            fprintf(stderr, "Fatal write error: %x\n", GetLastError());

            CloseHandle(hIn);

            CloseHandle(hOut);

            return 4;
        }
    };
        

    CloseHandle(hIn);

    CloseHandle(hOut);

    return 0;
}
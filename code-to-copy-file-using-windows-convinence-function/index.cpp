

#include <stdio.h>

#include <windows.h>

#define BUF_SIZE 256

LPWSTR lpwszFile1,
    lpwszFile2;

INT iLen1, iLen2;

int main(int argc, char *argv[])
{

    if (argc != 3)
    {

        fprintf(stderr, "Usage : cp file1 file2\n");

        return 1;
    }

    lpwszFile1 = (LPTSTR)malloc(510);

    lpwszFile2 = (LPTSTR)malloc(510);

    iLen1 = MultiByteToWideChar(CP_ACP, 0, argv[1], -1, lpwszFile1, 510);

    iLen2 = MultiByteToWideChar(CP_ACP, 0, argv[2], -1, lpwszFile2, 510);

    if (!CopyFile(lpwszFile1, lpwszFile2, FALSE))

    {
        fprintf(stderr, "CopyFile Error : % x\n", GetLastError());

        return 2;
    }

    return 0;
}

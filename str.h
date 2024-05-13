int ToUpper(char *str);
int StrAdd(char str1[], char str2[], char concatArray[]);
int StrEqual(char str1[], char str2[]);
int StrSize(char str[], int *strSize);
#define NULL 0LL

int ToUpper(char *str)
{
    if (!str)
    {
        return 1;
    }
    int strSize;
    if (StrSize(str, &strSize))
    {
        return 1;
    }
    for (int i = 0; i < strSize; i++)
    {
        if ((int)str[i] > 96 && (int)str[i] < 123)
        {
            str[i] = (int)str[i]- 32;
        }
    }
    return 0;
}

int StrSize(char str[], int *strSize)
{
    if (!str)
    {
        return 1; // Return 1 if no string is receivide
    }
    *strSize = 0;

    for (int i = 0; str[i] != NULL; i++)
    {
        ++*strSize;
        if (i >= 100)
        {
            return 1;
        }
    }

    return 0;
}

int StrEqual(char str1[], char str2[])
{
    if (!str1 || !str2)
    {
        return 1; // Return 1 if no string is receivide
    }

    // If sizes don't match return 1
    int str1Size, str2Size;
    StrSize(str1, &str1Size);
    StrSize(str2, &str2Size);
    if (str1Size != str2Size)
    {
        return 1;
    }

    // Return 1 if not equals
    for (int i = 0; i < str1Size; i++)
    {
        if (str1[i] != str2[i])
        {
            return 1;
        }
    }

    // Return 0 if equals
    return 0;
}

int StrAdd(char str1[], char str2[], char concatArray[])
{

    if (!str1 || !str2)
    {

        return 1;
    }
    int str1Size = 0;
    int str2Size = 0;

    // Loop from strings copying char to char
    for (int i = 0; str1[i] != NULL; i++)
    {
        concatArray[i] = str1[i];
        ++str1Size;
        if (i >= 9)
            return 1;
    }
    for (int i = 0; str2[i] != NULL; i++)
    {
        concatArray[str1Size + i] = str2[i];
        ++str2Size;
    }
    concatArray[str2Size + str1Size] = '\0';

    // return if ok
    return 0;
}
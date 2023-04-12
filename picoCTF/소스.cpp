#include<iostream>
#include<cstring>

using namespace std;

int main(int argc, char* argv[])
{
    char str[] = "cvpbPGS{arkg_gvzr_V'yy_gel_2_ebhaqf_bs_ebg13_hyLicInt}";

    for (int i = 0; i < strlen(str); i++)
    {
        if (!isalpha(str[i]))
        {
            continue;
        }

        int tmp = str[i];

        if (isupper(str[i]))
        {
            tmp += 13;

            if (tmp > 'Z')
                tmp -= 26;
        }
        else if (islower(str[i]))
        {
            tmp += 13;

            if (tmp > 'z')
                tmp -= 26;
        }

        str[i] = tmp;
    }

    cout << str;

    return 0;
}
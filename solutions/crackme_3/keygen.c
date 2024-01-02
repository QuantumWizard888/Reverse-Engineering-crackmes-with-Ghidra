#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    
    char input_name_str[100] = "";
    char real_pass_str[100] = "";
    int input_name_str_len;
    int key_str_len = 26;
    int index;

    printf("Enter name: \n");
    scanf("%s", input_name_str);

    input_name_str_len = strlen(input_name_str);
    printf("%d\n", input_name_str_len);

    for (int i=0; i < input_name_str_len; i++)
    {
        int char_int = input_name_str[i];
        index = (char_int ^ key_str_len) % input_name_str_len;
        real_pass_str[i] = input_name_str[index];

    }
    
    printf("Your password is: \n");
    printf("%s", real_pass_str);

    return 0;
}


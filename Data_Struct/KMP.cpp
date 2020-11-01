#define MaxLen 255
typedef struct SString{
    char data[MaxLen];
    int length;
};

typedef struct HString {
    char *data;
    int length;
};

//简单模式匹配
int SimplePattern(SString text, SString target)
{
    int i = 1, j = 1;
    while (i <= text.length and j <= target.length)
    {
        if (text.data[i] == target.data[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 2;
            j = 1;
        }
    }
    if (j > target.length)
        return i - j + 1;
    else
        return false;
}

//KMP算法
void get_next(SString T, int next[])
{
    int i = 1;
    int j = 0;
    next[1] = 0;
    while (i < T.length)
    {
        if (j == 0 or T.data[i] == T.data[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }
}

int KMP(SString S, SString T, int next[])
{
    int i = 1;
    int j = 1;
    while(i <= S.length and j <= T.length)
    {
        if (j == 0 or S.data[i] == T.data[j])
        {
            i++;
            j++;
        }
        else
            j = next[j];
    }
    if (j > T.length)
        return i - j + 1;
    else
        return false;
}
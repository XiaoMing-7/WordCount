#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include<windows.h>

int main(int argc, char* argv[]) {       //参数argv[1]表示输入控制参数，argv[2]表示文件名

    int totalChar = 0;      //总字符数
    int totalWord = 0;      //总单词数
    char buffer[1024];      //缓冲区，存储从文件中读到的内容，这里是以1024（一行）为单位
    int charNum = 0;        //缓冲区中所读内容中的字符数
    int wordNum = 0;        //缓冲区中所读内容中的单词数
    int bufferLen = 0;      //缓存区中存储内容的长度
    int i;                  //当前缓存区中第i个字符
    char c;                 //读取到的字符
    bool isBlank = false;
    bool isEndOfLine = false;           //用于判断上一个字符是否为空格或逗号
    FILE* fp;                           //指向文件的指针

    //判断输入的参数是否正确
    if ((strcmp(argv[1], "-c")!=0) && (strcmp(argv[1], "-w")!=0)) {
        perror("parameters is not correct!");
        return -1;
    }

    //判断是否能打开输入的文件
    if ((fp = fopen(argv[2], "rb")) == NULL) {
        perror("can't open");
        return -1;
    }

    //以行为单位读取数据并保存到buffer，以供判断
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        bufferLen = strlen(buffer);   //得到读取内容的长度
        for (i = 0; i < bufferLen; i++) {   //遍历缓冲区内容来判断
            c = buffer[i];

            if (c == '\r') {                //判断换行，换行则退出循环
                isEndOfLine = true;
                charNum++;
                break;
            }
            //计算单词数
            if (c == ' ' || c == ',') {
                if (!isBlank) {
                    wordNum++;             //如果上一个字符不是空格或逗号，单词数加1
                }
                isBlank = !isBlank;        //将判断是否空格变成true，下一个字符如果为逗号或空格则单词数不加1
            }

            //计算字符数
            charNum++;
            isBlank = false;              //字符数加1(因为字符条件包括了所有的字符，此处直接加1，不加判断)
        }

        totalChar += charNum;             //计算一行中字符和单词数
        totalWord += wordNum;

        charNum = 0;
        wordNum = 0;                      //一行结束清零
    }

    if (c != ' ' && c != ',') {
        totalWord += 1;                   //此处加1，因为最后一个单词如果后面没有空格或逗号会导致单词数少一
    }

    fclose(fp);

    if ((strcmp(argv[1], "-w"))!=0) {
        printf("字符数:%d", totalChar);
    }
    else {
        printf("单词数:%d", totalWord);
    }

    return 0;
}
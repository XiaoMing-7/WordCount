#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int wordCount(char* parameters, char* fileName);

int main() {
    char parameters[5];
    char filename[30];
    scanf("%s %s", parameters, filename);
    wordCount(parameters, filename);
    return 0;
}

int wordCount(char* parameters, char* fileName) {  //parametersΪ���Ʋ��� fileNameΪ��ȡ�ļ���
    int totalChar = 0;      //���ַ���
    int totalWord = 0;      //�ܵ�����
    char buffer[1024];      //���������洢���ļ��ж��������ݣ���������1024��һ�У�Ϊ��λ
    int charNum = 0;        //�����������������е��ַ���
    int wordNum = 0;        //�����������������еĵ�����
    int bufferLen = 0;      //�������д洢���ݵĳ���
    int i;                  //��ǰ�������е�i���ַ�
    char c;                 //��ȡ�����ַ�
    bool isBlank = false;
    bool isEndOfLine = false;           //�����ж���һ���ַ��Ƿ�Ϊ�ո�򶺺�
    FILE* fp;                           //ָ���ļ���ָ��

    //�ж�����Ĳ����Ƿ���ȷ
    if (parameters[1] != 'c' && parameters[1] != 'w') {
        perror("parameters is not correct");
        return -1;
    }

    //�ж��Ƿ��ܴ�������ļ�
    if ((fp = fopen(fileName, "rb")) == NULL) {
        perror("can't open");
        return -1;
    }

    //����Ϊ��λ��ȡ���ݲ����浽buffer���Թ��ж�
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        bufferLen = strlen(buffer);   //�õ���ȡ���ݵĳ���
        for (i = 0; i < bufferLen; i++) {   //�����������������ж�
            c = buffer[i];

            if (c == '\r') {                //�жϻ��У��������˳�ѭ��
                isEndOfLine = true;
                break;
            }
            //���㵥����
            if (c == ' ' || c == ',') {
                if (!isBlank) {
                    wordNum++;             //�����һ���ַ����ǿո�򶺺ţ���������1
                }
                isBlank = !isBlank;        //���ж��Ƿ�ո���true����һ���ַ����Ϊ���Ż�ո��򵥴�������1
            }

            //�����ַ���
            charNum++;
            isBlank = false;              //�ַ�����1(��Ϊ�ַ��������������е��ַ����˴�ֱ�Ӽ�1�������ж�)
        }

        totalChar += charNum;             //����һ�����ַ��͵�����
        totalWord += wordNum;

        charNum = 0;
        wordNum = 0;                      //һ�н�������
    }

    if (c != ' ' && c != ',') {
        totalWord += 1;                     //�˴���1����Ϊ���һ�������������û�пո�򶺺Żᵼ�µ�������һ
    }

    fclose(fp);
    if (parameters[1] == 'c') {
        printf("�ַ���:%d", totalChar);
    }
    else {
        printf("������:%d", totalWord);
    }

    return 0;
}
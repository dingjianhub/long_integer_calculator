#include "big_num_op.h"
#include "op_function.h"
#include "view.h"
int main(){
    prtWelcomeUI();
    DblList first,second,result;
    char op;
    InitList(first);
    InitList(second);
    InitList(result);
    for (;;) {
        scanf("%c",&op);
        if(op=='0'){
            DestroyList(first);
            DestroyList(second);
            DestroyList(result);
            break;
        }
        if(op!='0'&&op>'3'){
            printf("\n\n����ı��������˶Ժ��ٴ����룡\n���������������");
            getch();
            system("cls");
            prtMainUI();
            continue;
        }
        switch (op){
            case '1':
                prtInputFormatUI(op);
                InputInteger(first,second);
                //TravelList(first); //testing ������������
                //TravelList(second);
                PrtList(first);
                PrtList(second);
                addition(first,second,result);
                printf("\n=============================������=============================");
                PrtList(result);
                break;
            case '2':
                prtInputFormatUI(op);
                InputInteger(first,second);
                PrtList(first);
                PrtList(second);
                subtraction(first,second,result);
                printf("\n=============================������==============================");
                PrtList(result);
                break;
            case '3':
                prtInputFormatUI(op);
                InputInteger(first,second);
                PrtList(first);
                PrtList(second);
                multiplication(first,second,result);
                printf("\n=============================������===============================");
                PrtList(result);
                break;
//            default:
//                return 0;
        }
        ClearList(first);
        ClearList(second);
        ClearList(result);
        prtMainUI();
    }
    return 0;
}

#include "big_num_op.h"

//��ʼ����ͷ����˫��ѭ������
void InitList(DblList &first){
    first=(DblNode *)malloc(sizeof(DblNode));  //����ͷ���
    if(!first){
        printf("\n�ڴ����ʧ�ܣ�\n");
        exit(1);
    }
    first->data=0;  //ͷ���洢�ó���������λ������ʼ��Ϊ0
    first->prior=first->next=first;
}

//����˫ѭ����������ͷ�ڵ㣩
void DestroyList(DblList &first){
    DblList q,p=first->next;
    while (p!=first){
        q=p;
        p=p->next;
        free(q);
    }
    free(first);
}

//��մ�ͷ����˫ѭ����������ͷ��㣩
void ClearList(DblList &first){
    DblList q,p=first->next;
    while (p!=first){
        q=p;
        p=p->next;
        free(q);
    }
    first->data=0;
    first->prior=first->next=first;
}

//�����ͷ����˫��ѭ������ĳ���
int ListLength(DblList first){
    DblList p=first->next;
    int count=0;
    while(p!=first){
        p=p->next;
        count++;
    }
    return count;
}

//�����ú���
//����ѭ������
void TravelList(DblList first){
    printf("\n===========================TravelList_Testing============================\n");
    DblList p=first->next;
    while (p!=first){
        //ע��˴��������ʽ����
        if(p->next==first)
            printf("%4d",p->data);
        else
            printf("%4d,",p->data);

        p=p->next;
    }
    printf(";\tthe number of node: %d\n",first->data);
    getchar();
    if(getch())return;
}

//����ʽ���ѭ������
void PrtList(DblList first){
    printf("\n==================================================================\n");
    DblList p=first->next;
    if (p->data==0) ;   //�������ֻ����������"0"
    else if(first->data<0) printf("-");
    else if (first->data>0) printf("+");
    int flag_is_first_node=0;
    while (p!=first){
        if(ListLength(first)==1 && flag_is_first_node==0){//����Ϊ1ʱ��ֱ���������
            printf("%d",p->data);
            flag_is_first_node++;
            p=p->next;
            continue;
        }
        else if (flag_is_first_node==0){
            printf("%d,",p->data);//�ڵ㳤�ȳ���1����Ҫ���һ����,��
            flag_is_first_node++;
            p=p->next;//�ڵ�ָ�����
            continue;//���������ѭ��
        }
        else if(p->data==0){//���У�Ϊ��0��ʱ��ֱ��������֡�0��
            printf("0");
            break;//ֱ������ѭ��
        }
        if(p->next==first && flag_is_first_node!=0){ //ע��˴��������ʽ����
            if(p->data>=1000)printf("%4d",p->data);
            if(p->data<1000 && p->data>=100)printf("0%d",p->data);
            if(p->data<100 && p->data>=10)printf("00%d",p->data);
            if(p->data<10)printf("000%d",p->data);
        }
        else{
            if(p->data>=1000)printf("%4d,",p->data);
            if(p->data<1000 && p->data>=100)printf("0%d,",p->data);
            if(p->data<100 && p->data>=10)printf("00%d,",p->data);
            if(p->data<10)printf("000%d,",p->data);
        }

        p=p->next;
    }
    printf(";\t�ó�������: %d���ڵ�\n",abs(first->data));
    if(getch())return;
}

// ���Ĵ���
//�洢����ĳ�����
void InputInteger(DblList &first,DblList &second){
    printf("��ע�����������ʽ��(���\";\"��������)\n");
    char str[3][8]={"1","2"};
    DblList assist; //��������
    for (int i = 0; i < 2; ++i) {
        if(i==0)assist=first;
        else assist=second;
        printf("������� %s ���������� ",str[i]);
        DblList newdnode,p;
        int temp,flag=1;
        char ch;
        scanf("%d",&temp);
        if(temp<0){  //��ȡ��һ��������ݣ��������������洢�ĳ�������������ͷ���data������һ��
            assist->data--;
            flag=0;
        }
        else assist->data++;
        //������һ����㲢������β
        newdnode=(DblNode *)malloc(sizeof(DblNode));
        newdnode->data=abs(temp);  //�����ֵΪ��������λ����ͷ��㣬��ͷ���data�������һ��
        newdnode->prior=assist;
        assist->next=newdnode;
        newdnode->next=assist;
        assist->prior=newdnode;

        p=newdnode;  //pΪ��β���

        scanf("%c",&ch);  //�ж������Ƿ����
        if(ch==';')continue;
        while (scanf("%d",&temp)){  //��ȡ�ڶ�����㵽���һ�����
            newdnode=(DblNode *)malloc(sizeof(DblNode));  //�����½�㲢������β
            newdnode->data=temp;
            newdnode->prior=p;
            p->next=newdnode;
            newdnode->next=assist;
            assist->prior=newdnode;

            if(flag)assist->data++;  //�������ĳ���
            else assist->data--;
            p=newdnode;  //ʹpָ����β
            scanf("%c",&ch);
            if(ch==';')break;
            else if(ch==',')continue;
            else {
                printf("\nInput Error!\n");
                getchar();
                if(getch())exit(0);
                return;
            }
        }
    }
    return;
}

//ͷ������һ��λ�ò����½��
//p3:ָ��result��ǰ������(��ʼ��Ϊ��β���)
void newdnodeInset(DblList &p3,DblList &newdnode,DblList &result){
    p3->prior=newdnode;
    result->next=newdnode;
    newdnode->next=p3;
    newdnode->prior=result;
    p3=newdnode;
}

//��ʼ��������ֵΪ 0
void InitSpecial(DblList &first){
    DblList newdnode=(DblNode *)malloc(sizeof(DblNode));
    newdnode->data=0;
    newdnode->next=newdnode->prior=first;
    first->next=first->prior=newdnode;
    first->data=1;
}

//�ӷ���λ����
void judgeAdd(int temp,int &k,DblList &newdnode){
    if(temp/10000==0){
        newdnode->data=temp;
        k=0;
    }
    else{
        newdnode->data=temp%10000;
        //k=temp/10000;
        k=1;
    }
}

//�ӷ�
void addition(DblList &first,DblList &second,DblList &result){
    int len1=abs(first->data),len2=abs(second->data);
    int len=max(len1,len2);
    int smb1=first->data/abs(first->data),smb2=second->data/abs(second->data);  //ȡ����λ���ж�������
    //p1:ָ��first��ǰ������(��ʼ��Ϊ��β���)��p2:ָ��second��ǰ������(��ʼ��Ϊ��β���)
    DblList newdnode,p1=first->prior,p2=second->prior,p3=result;  //p3:ָ��result��ǰ������(��ʼ��Ϊ��β���)

    if(smb1+smb2!=0){  //������Ϊ������� �� ������Ϊ��������������������ת��Ϊ����������㣩
        int k=0,temp,i;  //k:��¼��λ  temp:����������ʱ���
        for (i = 0; i < len; i++) {  //�����λ��ʼ���㣨������β��ʼ��ǰ��ӣ�
            newdnode=(DblNode *)malloc(sizeof(DblNode));
            if(p1!=first && p2!=second){  //�����������δ���㵽ͷ���
                temp=p1->data+p2->data+k;
                judgeAdd(temp,k,newdnode);
                p1=p1->prior;   //ʹָ��ָ����һ��Ҫ����Ľ�㣨ָ���λ��
                p2=p2->prior;   //ʹָ��ָ����һ��Ҫ����Ľ�㣨ָ���λ��
            }
            else if(p1!=first && p2==second){  //���second�����㵽ͷ��㣬��firstδ��
                temp=p1->data+k;
                judgeAdd(temp,k,newdnode);
                p1=p1->prior;  //ʹָ��ָ����һ��Ҫ����Ľ�㣨ָ���λ��
            }
            else if(p1==first && p2!=second){  //���first�����㵽ͷ��㣬��secondδ��
                temp=p2->data+k;
                judgeAdd(temp,k,newdnode);
                p2=p2->prior;   //ʹָ��ָ����һ��Ҫ����Ľ�㣨ָ���λ��
            }
            newdnodeInset(p3,newdnode,result);  //ͷ������һ��λ�ò����½��
        }
        while(k){  //�������λ������Ҫ��λ�����
            newdnode=(DblNode *)malloc(sizeof(DblNode));
            i++;
            temp=k;
            judgeAdd(temp,k,newdnode);  //�ж��Ƿ���Ҫ��λ
            newdnodeInset(p3,newdnode,result);  //ͷ������һ��λ�ò����½��
        }
        //����Ϊ�������
        if(smb1+smb2>0)result->data=i; //���������ȣ���λ������,������������ֵһ��
        //����Ϊ�������
        if(smb1+smb2<0)result->data=-i;  //���������ȣ���λ������,������������ֵһ��
        return;
    }

    if(smb1+smb2==0){  //һ��һ������������ɼ����������д���
        if(smb1>0){  //firstΪ��
            second->data=abs(second->data);
            subtraction(first,second,result);
            second->data=-second->data;  //�ָ�second�ķ���λ
        }
        else{
            first->data=abs(first->data);
            subtraction(second,first,result);
            first->data=-first->data;  //�ָ�first�ķ���λ
        }
        return;
    }
}

//������λ����
void judgeSub(int temp,int &k,DblList &newdnode){
    if(temp>=0){  //����Ҫ��λ
        newdnode->data=temp;
        k=0;
    }
    else{  //��Ҫ��λ
        newdnode->data=temp+10000;
        k=1;
    }
}

//�Ƚϳ�����ȵ����������ĸ��ϴ�
int cmpInteger(DblList first,DblList second){
    DblList p1=first->next,p2=second->next;
    while(p1!=first){
        if(p1->data==p2->data){
            p1=p1->next;
            p2=p2->next;
            continue;
        }
        else if(p1->data>p2->data)return 1;
        else if(p1->data<p2->data)return -1;
    }
    return 0;
}

//���������ֵ�������
void subDnode(int len,DblList &first,DblList &second,DblList &result,int &i){  //��������ʱ��fisrt����ֵ��second�����
    DblList newdnode,p1=first->prior,p2=second->prior,p3=result;  //first��second�ļ��������β��㿪ʼ���������λ��ʼ���㣩
    int temp,k=0;  //k:��ʼ��λΪ0
    for (i = 0; i < len; i++) {  //ѭ������Ϊ����������󳤶�
        newdnode=(DblNode *)malloc(sizeof(DblNode));
        if(p1!=first && p2!=second){  //�������ָ���δ��ͷ���
            temp=p1->data-p2->data-k;
            judgeSub(temp,k,newdnode);  //�ж��Ƿ���Ҫ��λ������Ϊ�½�㸳ֵ
            p1=p1->prior;  //ʹָ��ָ����һ��Ҫ����Ľ�㣨ָ���λ��
            p2=p2->prior;  //ʹָ��ָ����һ��Ҫ����Ľ�㣨ָ���λ��
        }
        else {  //���p2�ѵ�ͷ��㣬��p1δ��ͷ���
            temp=p1->data-k;
            judgeSub(temp,k,newdnode);
            p1=p1->prior;
        }
        //ͷ������һ��λ�ò����½��
        newdnodeInset(p3,newdnode,result);  //�ڽ������result�в������õ����½��
    }
}

//����
void subtraction(DblList &first,DblList &second,DblList &result){
    int len1=abs(first->data),len2=abs(second->data);
    int smb1=first->data/abs(first->data),smb2=second->data/abs(second->data);  //ȡ����λ���ж�������
    //p3:ָ��result��ǰ������(��ʼ��Ϊ��β���)
    DblList newdnode,p3=result;
    if(smb1+smb2>0){  //������Ϊ�������
        int i,flag;  //flag:��ǽ��������; i:��ǽ����������
        if(len1>len2){  //�����һ�����ĳ��ȴ��ڵڶ���
            flag=1;  //������Ϊ��
            subDnode(len1,first,second,result,i); //����������������result��
        }
        if(len1<len2){  //����ڶ��������ȴ��ڵ�һ��
            flag=-1;  //������Ϊ��
            subDnode(len2,second,first,result,i);  //����������������result��
        }
        if(len1==len2){  //����������ĳ�����ȣ���Ƚ��ĸ�������
            if(cmpInteger(first,second)>0){  //���first>second
                subDnode(len1,first,second,result,i); //����ʱ�����first����ϴ�ֵfirst
                flag=1;  //������Ϊ��
            }
            if(cmpInteger(first,second)<0){  //���first<second
                subDnode(len2,second,first,result,i);  //����ʱ�����first����ϴ�ֵsecond
                flag=-1;  //������Ϊ��
            }
            if(cmpInteger(first,second)==0){  //������������
                newdnode=(DblNode *)malloc(sizeof(DblNode));
                newdnode->data=0;  //������Ϊ0��
                newdnodeInset(p3,newdnode,result);
                flag=1;  //������Ϊ��
                i=1;
            }
        }
        //�����������������������
        if(flag==1)result->data=i;
        else result->data=-i;
        return;
    }
    if(smb1+smb2<0){  //������Ϊ�����������ת��Ϊ����Ϊ����������
        //ת��Ϊ�����������
        first->data=abs(first->data);
        second->data=abs(second->data);
        subtraction(second,first,result); //�ݹ����subtraction��������
        //�ָ�����������λ���������
        first->data=-first->data;
        second->data=-second->data;
        return;
    }
    if(smb1+smb2==0){  //һ��һ��
        if(first->data>0 && second->data<0){  //firstΪ��secondΪ�������
            second->data=abs(second->data);  //ת��Ϊ�����������
            addition(first,second,result);  //���ɼӷ��������д���
            second->data=-second->data;  //�ָ�ԭ�������ݵķ���λ���������
        }
        if(first->data<0 && second->data>0){  //secondΪ��firstΪ�������
            first->data=abs(first->data); //ת��Ϊ�����������
            addition(first,second,result);  //���ɼӷ��������д���
            first->data=-first->data;  //�ָ�ԭ�������ݵķ���λ���������
            result->data=-result->data;  //����������Ϊ��
        }
        return;
    }
}

//�˷���λ����
void judgeMultiply(int temp,int &k,DblList &newdnode){
    if(temp/10000==0){
        newdnode->data=temp;
        k=0;
    }
    else{
        newdnode->data=temp%10000;
        k=temp/10000;
    }
}

//�˷������Ӵ���
void mulDnode(DblList &result,DblList &assist,int t){
    DblList newdnode,p1=result,p2=assist->prior;
    int temp,k=0;
    while(t--)
        p1=p1->prior;  //������ʼ���λ��
    while (p2!=assist){
        if(p1->prior!=result){
            temp=p1->prior->data+p2->data+k;
            judgeMultiply(temp,k,p1->prior);
            p1=p1->prior;
        }
        else{
            newdnode=(DblNode *)malloc(sizeof(DblNode));
            temp=p2->data+k;
            judgeMultiply(temp,k,newdnode);
            newdnodeInset(p1,newdnode,result);
            result->data++;
        }
        p2=p2->prior;
    }
    while(k) {  //�������λ������Ҫ��λ�����
        newdnode = (DblNode *) malloc(sizeof(DblNode));
        temp = k;
        judgeMultiply(temp, k, newdnode); //�ж��Ƿ���Ҫ��λ
        //ͷ������һ��λ�ò����½��
        newdnodeInset(p1, newdnode, result);
        result->data++;
    }
}

//�˷�
void multiplication(DblList &first,DblList &second,DblList &result){
    int smb1=first->data/abs(first->data),smb2=second->data/abs(second->data);  //ȡ����λ���ж�������

    DblList assist;  //�������������洢��ʱ������
    InitList(assist);  //��ʼ����������
    InitSpecial(result); //��ʼ��result��ֵΪ0������Ϊ1��
    DblList newdnode,p1,p2=second->prior,p4;

    int temp,i=0,t; //temp:������ʱ���  t:������ʼ���λ��
    while(p2!=second){
        t=i++;
        int k=0;
        p1=first->prior;
        p4=assist;
        while (p1!=first){
            newdnode=(DblNode *)malloc(sizeof(DblNode));
            temp=p2->data*p1->data+k;
            judgeMultiply(temp,k,newdnode);
            newdnodeInset(p4,newdnode,assist);

            assist->data++;  //ÿ���һ���µĽ�㣬����������+1
            p1=p1->prior;
        }
        p2=p2->prior;
        while(k){  //�������λ������Ҫ��λ�����
            newdnode=(DblNode *)malloc(sizeof(DblNode));
            temp=k;
            judgeMultiply(temp,k,newdnode); //�ж��Ƿ���Ҫ��λ
            //ͷ������һ��λ�ò����½��
            newdnodeInset(p4,newdnode,assist);
            assist->data++;
        }
        mulDnode(result,assist,t);
        ClearList(assist);
    }
    if(smb1+smb2==0)result->data=-result->data;
    else result->data=abs(result->data);
    return;
}

/**
 * @file stack_homework.c
 * @author ������
 * @brief ��ҵ��ʹ��������������ַ�ʽʵ��ջADT
 * @note 
 * 1. ��������ʵ�ֵ�ջ�ڱ������г���lstack / LStack��linked list stack��
 * 2. ��������ʵ�ֵ�ջ�ڱ������г���tstack / TStack��table stack��
 * 3. Ϊ�˱��ⷴ���Ķ����鷳��������û�жԸ��ֹ��ܺ�����������������ֱ�Ӷ�����main����ǰ��
 * @version 0.1
 * @date 2025-05-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/************************ʹ������ʵ��ջ***********************/
/* ����ջADT�ṹ��(ʵ������һ�������³�ÿ���ڵ�ΪջԪ��) */
typedef struct linked_list_stack{
    int32_t data;                   //ջԪ�ش洢������
    struct linked_list_stack *next; //��һ��ջԪ�أ���ջ��ָ��ջ�ף�
}lstack;

/**
 * @brief ջ��ʼ��
 * 
 * @param target_stack ��Ҫ��ʼ����Ŀ��ջ��ַ
 * @note ջ��ʼ����nextָ��ָ��NULL����ʾ�ڲ���Ԫ��
 * Ŀ��ջ�ĵ�ַ�ڱ������в���ջ��Ԫ�ر���ĵ�ַ����������
 * �������ͷָ��ĵ�ַ��ָ��ջ��Ԫ��
 * @return ��
 */
void vLStackInit(lstack *target_stack){
    /* ��ʼ��ʱջ����Ԫ�أ����ָ��NULL */
    target_stack->next = NULL;
}

/**
 * @brief ������ջ
 * 
 * @param target_stack Ŀ��ջ��ַ
 * @param data ��Ҫ��ջ������
 * @return uint8_t �����ɹ�����1��ʧ�ܷ���0
 */
uint8_t ucLStackPush(lstack *target_stack, int32_t data){
    /* Ϊ��Ԫ������һ���ڴ�ռ� */
    lstack *new_element = (lstack *)malloc(sizeof(lstack));
    /* �������ʧ�ܣ�����0 */
    if(new_element == NULL) return 0;
    /* ����Ҫ��ջ��ֵ��ֵ����Ԫ�� */
    new_element->data = data;
    /* ����Ԫ�ص�nextָ��ָ��ԭ����ջ��Ԫ�ص�nextָ����ָ���Ԫ�� */
    new_element->next = target_stack->next;
    /* ��Ԫ�س�Ϊջ�� */
    target_stack->next = new_element;
    return 1;
}

/**
 * @brief �鿴ջ��Ԫ��ֵ
 * 
 * @param target_stack ��Ҫ�鿴��Ŀ��ջ��ַ
 * @note Ŀ��ջ�ĵ�ַ����ջ��Ԫ�صĵ�ַ
 * @return int ջ��Ԫ��ֵ
 */
int32_t iLStackTop(lstack *target_stack){
    /* �����ʱջΪ�գ�����ʾ�û�������0 */
    if(target_stack->next == NULL){
        printf("Stack is empty!");
        return 0;
    }
    /* ����ջ��Ԫ��ֵ */
    return target_stack->next->data;
}

/**
 * @brief ���ݳ�ջ
 * 
 * @param target_stack Ŀ��ջ��ַ
 * @return int ��ջ����
 */
int32_t iLStackPop(lstack *target_stack){
    /* �����ʱջΪ�գ�����ʾ�û�������0 */
    if(target_stack->next == NULL){
        printf("Stack is empty!");
        return 0;
    }
    /* ��¼��ǰ��ջ��Ԫ�أ���ջ��Ԫ�أ� */
    lstack *old_top_element = target_stack->next;
    /* ��¼��ǰջ��Ԫ�غ󵯳������ջ��Ԫ�� */
    lstack *new_top_element = old_top_element->next;
    /* �ݴ���Ҫ���صĵ�ǰջ��Ԫ�ص����� */
    int return_data = old_top_element->data;
    /* �ͷžɵ�ջ��Ԫ�أ������� */
    free(old_top_element);
    /* ��target_stackָ���µ�ջ��Ԫ�� */
    target_stack->next = new_top_element;
    /* ���ص��������� */
    return return_data;
}

/**
 * @brief ���ջ
 * 
 * @param target_stack Ŀ��ջ��ַ
 * @return ��
 */
void vMakeLStackEmpty(lstack *target_stack){
    /* ֻҪջ��û�գ��Ͳ��ϵ�����ֱ��ջ����� */
    while(target_stack->next != NULL){
        lstack *next_top_element = target_stack->next->next;
        free(target_stack->next);
        target_stack->next = next_top_element;
    }
}

/**
 * @brief ��ӡջ
 * 
 * @param target_stack Ŀ��ջ��ַ
 * @return ��
 */
void vPrintLStack(lstack *target_stack){
    printf("Stack: >> "); //ջ����ʾ
    /* ѭ����ӡ�������ݣ�ֱ�����һ������ */
    while(target_stack->next != NULL){
        /* ͨ��nextָ�벻����ջ�׵ķ���������� */
        target_stack = target_stack->next;
        printf("%d ", target_stack->data);
    }
    printf("\b]\n"); //ջ����ʾ
}

/************************ʹ������ʵ��ջ***********************/
/* ����ջADT�ṹ�� */
typedef struct table_stack{
    int32_t *tstack_container;  //������������ջ�Ĵ洢�ռ�
    int32_t capacity;           //����ָʾջ����
    int32_t top_index;           //ջ������
}tstack;

/**
 * @brief ��ʼ��ջ
 * 
 * @param target_stack ����ʼ����ջ
 * @param stack_size ��Ҫ������ջ�Ĵ�С
 * @return uint8_t ��ʼ���ɹ�����1��ʧ�ܷ���0
 */
uint8_t ucTStackInit(tstack *target_stack, int32_t stack_size){
    /* ��������ջ��С�������ƣ�����Ϊ�������򷵻�0 */
    if((stack_size > 0x7FFFFFF) || (stack_size < 0)) return 0;
    /* ����ջ��СΪջ�����ڴ�ռ� */
    target_stack->tstack_container = (int *)malloc(stack_size * sizeof(int));
    /* ������䲻���ڴ棬�򷵻�0 */
    if(target_stack->tstack_container == NULL) return 0;
    /* ����ջ���� */
    target_stack->capacity = stack_size;
    /* ��ʼ��ջ������Ϊ-1����ʾջΪ�� */
    target_stack->top_index = -1;
    return 1;
}

/**
 * @brief ������ջ
 * 
 * @param target_stack Ŀ��ջ��ַ
 * @param data ��ջ����
 * @return uint8_t ��ջ�ɹ�����1��ʧ�ܷ���0
 */
uint8_t ucTStackPush(tstack *target_stack, int32_t data){
    /* ���ջ����������ʾ�û���������0 */
    if(target_stack->top_index >= target_stack->capacity - 1){
        printf("Stack is full!\n");
        return 0;
    }
    /* ����ջ��ָ�� */
    target_stack->top_index += 1;
    /* ������ջ����λ��ջ�� */
    target_stack->tstack_container[target_stack->top_index] = data;
    return 1;
}

/**
 * @brief ��ȡջ������
 * 
 * @param target_stack Ŀ��ջ��ַ
 * @return int32_t ջ������
 */
int32_t iTStackTop(tstack *target_stack){
    /* ���ջΪ��,����ʾ�û�������0 */
    if(target_stack->top_index == -1){
        printf("Stack is empty!\n");
        return 0;
    }
    /* ����ջ������ */
    return target_stack->tstack_container[target_stack->top_index];
}

/**
 * @brief ���ݳ�ջ
 * 
 * @param target_stack Ŀ��ջ��ַ
 * @return * int32_t ��ջ����
 */
int32_t iTStackPop(tstack *target_stack){
    /* ���ջΪ��,����ʾ�û�������0 */
    if(target_stack->top_index == -1){
        printf("Stack is empty!\n");
        return 0;
    }
    /* �ݴ��ջ���ݵ�ֵ(��ջ�����ݵ�ֵ) */
    int32_t return_data = target_stack->tstack_container[target_stack->top_index];
    /* ���ݳ�ջ���Ӧ��ջ������Ҫ-1, ָ���µ�ջ�� */
    target_stack->top_index -= 1;
    return return_data;
}

/**
 * @brief ���ջ
 * 
 * @param target_stack Ŀ��ջ��ַ
 * @return ��
 */
void vMakeTStackEmpty(tstack *target_stack){
    /* ֱ�ӽ�ջ����������Ϊ-1���� */
    target_stack->top_index = -1;
}

/**
 * @brief ��ӡջ
 * 
 * @param target_stack Ŀ��ջ��ַ
 * @return ��
 */
void vPrintTStack(tstack *target_stack){
    printf("Stack: ["); //��ӡջ����ʾ
    /* ��������ջ�ռ䣬ֻҪ��ǰ����û�г���ջ��ָ�룬�ʹ�ӡ��Ӧ������ */
    for(int32_t i = 0; i <= target_stack->top_index; i++){
        printf("%d ", target_stack->tstack_container[i]);
    }
    printf("<<\n"); //��ӡջ����ʾ
}

/* ����������ҵ����ʵ�֣� */
int main(void){
    printf("========================����ʵ��==========================\n");
    /* 1. ����һ��ջ */
    lstack lstack_test;
    vLStackInit(&lstack_test);

    /* 2. push��������Ԫ��5��Ԫ��2�ֱ�ѹջ */
    ucLStackPush(&lstack_test, 5);
    ucLStackPush(&lstack_test, 2);
    printf("push��������Ԫ��5��Ԫ��2�ֱ�ѹջ��\n");
    vPrintLStack(&lstack_test);

    /* 3. top�������鿴ջ��Ԫ��ֵ */
    int32_t top_data = iLStackTop(&lstack_test);
    printf("\ntop�������鿴ջ��Ԫ��ֵ��\n");
    printf("ջ��Ԫ�أ�%d\n", top_data);

    /* 4. pop������ջ��Ԫ�ص�������ӡ */
    int32_t pop_data = iLStackPop(&lstack_test);
    printf("\npop������ջ��Ԫ�ص�������ӡ��\n");
    printf("����Ԫ�أ�%d\n", pop_data);
    vPrintLStack(&lstack_test);

    /* 5. push��������Ԫ��6��Ԫ��7�ֱ�ѹջ */
    ucLStackPush(&lstack_test, 6);
    ucLStackPush(&lstack_test, 7);
    printf("\npush��������Ԫ��6��Ԫ��7�ֱ�ѹջ��\n");
    vPrintLStack(&lstack_test);

    /* 6. makeEmpty���������ջ */
    vMakeLStackEmpty(&lstack_test);
    printf("\nmakeEmpty���������ջ��\n");
    vPrintLStack(&lstack_test);

    printf("========================����ʵ��==========================\n");
    /* 1. ����һ��ջ */
    tstack tstack_test;
    ucTStackInit(&tstack_test, 64);

    /* 2. push��������Ԫ��5��Ԫ��2�ֱ�ѹջ */
    ucTStackPush(&tstack_test, 5);
    ucTStackPush(&tstack_test, 2);
    printf("push��������Ԫ��5��Ԫ��2�ֱ�ѹջ��\n");
    vPrintTStack(&tstack_test);

    /* 3. top�������鿴ջ��Ԫ��ֵ */
    int32_t top_data1 = iTStackTop(&tstack_test);
    printf("\ntop�������鿴ջ��Ԫ��ֵ��\n");
    printf("ջ��Ԫ�أ�%d\n", top_data1);

    /* 4. pop������ջ��Ԫ�ص�������ӡ */
    int32_t pop_data1 = iTStackPop(&tstack_test);
    printf("\npop������ջ��Ԫ�ص�������ӡ��\n");
    printf("����Ԫ�أ�%d\n", pop_data1);
    vPrintTStack(&tstack_test);

    /* 5. push��������Ԫ��6��Ԫ��7�ֱ�ѹջ */
    ucTStackPush(&tstack_test, 6);
    ucTStackPush(&tstack_test, 7);
    printf("\npush��������Ԫ��6��Ԫ��7�ֱ�ѹջ��\n");
    vPrintTStack(&tstack_test);

    /* 6. makeEmpty���������ջ */
    vMakeTStackEmpty(&tstack_test);
    printf("\nmakeEmpty���������ջ��\n");
    vPrintTStack(&tstack_test);
    return 0;
}

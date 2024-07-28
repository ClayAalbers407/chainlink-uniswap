//
// Created by zl on 2021/3/16.
//

struct UBigNumber InputUBN() {
    struct UBigNumber result;
    InitUBN(&result);
    char ch;
    do {
        ch = getchar();
        if (ch == '-') {
            if (flag == 0) {
                flag1++;
            } else {
                flag2++;
            }
        }
        flag++;
    } while (ch < '0' || ch > '9');
    while (ch >= '0' && ch <= '9') {
        AppendDigit(&result, ch - '0');
        ch = getchar();
    }
    Normalize(&result);
    return result;
}

int CompareUBN(struct UBigNumber ubn1, struct UBigNumber ubn2) {
    assert(ubn1.digitCount > 0 && ubn1.pHead->next != NULL);
    assert(ubn2.digitCount > 0 && ubn2.pHead->next != NULL);
    struct Node *p1 = ubn1.pHead->next;
    struct Node *p2 = ubn2.pHead->next;
    if (ubn1.digitCount > ubn2.digitCount) {
        return 1;
    } else if (ubn1.digitCount < ubn2.digitCount) {
        return 0;
    } else {
        while (p1) {
            if (p1->digit > p2->digit) {
                return 1;
            } else if (p1->digit < p2->digit) {
                return 0;
            } else {
                p1 = p1->next;
                p2 = p2->next;
            }
        }
    }
    return 2;
}

void PrintUBN(struct UBigNumber ubn) {
    assert(ubn.digitCount > 0 && ubn.pHead->next != NULL);
    struct Node *p = ubn.pHead->next;
    while (p) {
        printf("%d", p->digit);
        p = p->next;
    }
}

struct UBigNumber AddUBN(struct UBigNumber *pA, struct UBigNumber *pB) {
    struct UBigNumber result, *pResult = &result;
    InitUBN(pResult);
    int iCarry = 0;
    struct Node *p1, *p2;
    p1 = pA->pTail;
    p2 = pB->pTail;
    while (p1 != pA->pHead && p2 != pB->pHead) {
        int digit = p1->digit + p2->digit + iCarry;
        iCarry = digit / 10;
        digit %= 10;
        AppendFrontDigit(pResult, digit);
        p1 = p1->prev;
        p2 = p2->prev;
    }
    while (p1 != pA->pHead) {
        int digit = p1->digit + iCarry;
        iCarry = digit / 10;
        digit %= 10;
        AppendFrontDigit(pResult, digit);
        p1 = p1->prev;
    }
    while (p2 != pB->pHead) {
        int digit = p2->digit + iCarry;
        iCarry = digit / 10;
        digit %= 10;
        AppendFrontDigit(pResult, digit);
        p2 = p2->prev;
    }
    if (iCarry != 0) {
        AppendFrontDigit(pResult, iCarry);
    }
    return result;
}

struct UBigNumber MinusUBN(struct UBigNumber *pA, struct UBigNumber *pB) {
    struct UBigNumber result, *pResult = &result;
    InitUBN(pResult);
    int iCarry = 0;
    struct Node *p1, *p2;
    p1 = pA->pTail;
    p2 = pB->pTail;
    while (p1 != pA->pHead && p2 != pB->pHead) {
        int digit = p1->digit - p2->digit - iCarry;
        if (digit < 0) {
            iCarry = (digit + 20) / 10;
            digit += 10;
        } else {
            iCarry = digit / 10;
            digit %= 10;
        }
        AppendFrontDigit(pResult, digit);
        p1 = p1->prev;
        p2 = p2->prev;
    }
    while (p1 != pA->pHead) {
        int digit = p1->digit - iCarry;
        if (digit < 0) {
            iCarry = (digit + 20) / 10;
            digit += 10;
        } else {
            iCarry = digit / 10;
            digit %= 10;
        }
        AppendFrontDigit(pResult, digit);
        p1 = p1->prev;
    }
    while (p2 != pB->pHead) {
        int digit = p2->digit - iCarry;
        if (digit < 0) {
            iCarry = (digit + 20) / 10;
            digit += 10;
        } else {
            iCarry = digit / 10;
            digit %= 10;
        }
        AppendFrontDigit(pResult, digit);
        p2 = p2->prev;
    }
    if (iCarry != 0) {
        AppendFrontDigit(pResult, iCarry);
    }
    return result;
}

void DestoryUBN(struct UBigNumber *pUBN) {
    while (pUBN->pHead != NULL) {
        struct Node *p = pUBN->pHead;
        pUBN->pHead = p->next;
        free(p);
    }

}

void InitUBN(struct UBigNumber *pUBN) {
    struct Node *p = NewNode();
    pUBN->pHead = pUBN->pTail = p;
    p->next = p->prev = NULL;
    pUBN->digitCount = 0;
}

void AppendDigit(struct UBigNumber *pUBN, int digit) {
    if (pUBN->digitCount == 1 && pUBN->pTail->digit == 0) {
        pUBN->pTail->digit = digit;
        return;
    }
    struct Node *p = NewNode();
    p->digit = digit;
    p->next = NULL;
    p->prev = pUBN->pTail;
    pUBN->pTail->next = p;
    pUBN->pTail = p;
    ++pUBN->digitCount;
}

void AppendFrontDigit(struct UBigNumber *pUBN, int digit) {
    struct Node *p = NewNode();
    p->digit = digit;
    p->next = pUBN->pHead->next;
    if (p->next != NULL) {
        p->next->prev = p;
    }
    p->prev = pUBN->pHead;
    pUBN->pHead->next = p;
    if (pUBN->pTail == pUBN->pHead) {
        pUBN->pTail = p;
    }
    ++pUBN->digitCount;
}

void Normalize(struct UBigNumber *pUBN) {
    if (pUBN->digitCount == 0) {
        AppendDigit(pUBN, 0);
    }
    while (pUBN->digitCount > 1 && pUBN->pHead->next->digit == 0) {
        struct Node *p;
        p = pUBN->pHead->next;
        pUBN->pHead->next = p->next;
        p->next->prev = pUBN->pHead;
        free(p);
        --pUBN->digitCount;
    }
}

struct Node *NewNode() {
    struct Node *p;
    p = (struct Node *) malloc(sizeof(struct Node));
    if (p == NULL) {
        printf("Error:out of memory\n");
        exit(-1);
    }
    return p;
}

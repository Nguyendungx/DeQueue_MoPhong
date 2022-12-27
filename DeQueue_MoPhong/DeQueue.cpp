﻿#include "graphics.h"
#include<iostream>
#include<windows.h>
#include<string.h>
#include<sstream>
#include<conio.h>

using namespace std;

struct NODE {
    string data;
    NODE* next;
    NODE* prev;
};

struct DEQUEUE {
    NODE* LeftMost;
    NODE* RightMost;

    void init() {
        LeftMost = nullptr;
        RightMost = nullptr;
    }

    bool isEmpty() {
        return RightMost == nullptr;
    }

    NODE* makeNode(string x) {
        NODE* newNode = new NODE();
        newNode->data = x;
        newNode->next = nullptr;
        newNode->prev = nullptr;
        return newNode;
    }

    void insert(string x, bool left) {
        NODE* newNode = makeNode(x);
        if (this->isEmpty()) {
            LeftMost = RightMost = newNode;
            return;
        }

        if (left) {
            newNode->next = LeftMost;
            if (LeftMost != nullptr)
                LeftMost->prev = newNode;
            LeftMost = newNode;
        }

        else {
            RightMost->next = newNode;
            newNode->prev = RightMost;
            RightMost = newNode;
        }
    }


    void deleteElement(bool left) {
        if (this->isEmpty())
            return;
        // TRUE
        if (left) {
            NODE* tmp = LeftMost;
            LeftMost = LeftMost->next;
            if (LeftMost == nullptr)
                RightMost = nullptr;
            else
                LeftMost->prev = nullptr;
            delete tmp;
        }
        // FALSE
        else {
            NODE* tmp = RightMost;
            RightMost = RightMost->prev;
            if (RightMost == nullptr)
                LeftMost = nullptr;
            else
                RightMost->next = nullptr;
            delete (tmp);
        }
    }

    int size()
    {
        NODE* tmp = LeftMost;
        int cnt = 0;
        while (tmp != nullptr) {
            cnt++;
            tmp = tmp->next;
        }
        return cnt;
    }
};
void showFinal(DEQUEUE* dq)
{
    NODE* tmp = dq->LeftMost;
    system("cls");
    setcolor(7);
    line(400, 280, 800, 280);
    line(400, 370, 800, 370);
    setcolor(4);
    for (int i = 0; i < dq->size(); i++)
    {
        rectangle(400+i*60, 300, 450+i*60, 350);
        drawText(415 + i*60, 315, tmp->data.c_str());
        tmp = tmp->next;
    }
}
void showElement(DEQUEUE* dq)
{
    NODE* tmp = dq->LeftMost;
    setcolor(4);
    for (int i = 0; i < dq->size(); i++)
    {
        rectangle(400 + i * 60, 300, 450 + i * 60, 350);
        drawText(415 + i * 60, 315, tmp->data.c_str());
        tmp = tmp->next;
    }
}
void showInsertLeft(string a, DEQUEUE* dq)
{
    char s1[] = "PUSH FRONT";
    setcolor(7);
    line(400, 280, 800, 280);
    line(400, 370, 800, 370);

    for (int i = 0; i < 220; i+=5)
    {
        drawText(200, 250, s1);
        showElement(dq);
        line(400, 280, 800, 280);
        line(400, 370, 800, 370);
        rectangle(200 + i, 300, 250 + i, 350);
        drawText(215 + i, 315, a.c_str());
        system("cls");
    }
}
void showInsertRight(string a, DEQUEUE* dq)
{
    char s1[] = "PUSH BACK";
    setcolor(7);
    line(400, 280, 800, 280);
    line(400, 370, 800, 370);


    for (int i = 0; i < 480-dq->size()*60; i += 5)
    {
        drawText(900, 250, s1);
        showElement(dq);
        line(400, 280, 800, 280);
        line(400, 370, 800, 370);
        rectangle(900 - i, 300, 950 - i, 350);
        drawText(915 - i, 315, a.c_str());
        system("cls");
    }
}
void insertLeft(DEQUEUE* dq)
{
    string a;
    cin >> a;
    showInsertLeft(a, dq);
    dq->insert(a, true);
    showFinal(dq);

}
void insertRight(DEQUEUE* dq)
{
    string a;
    cin >> a;
    showInsertRight(a, dq);
    dq->insert(a, false);
    showFinal(dq);

}
void deleteLeft(DEQUEUE* dq)
{
    char s1[] = "POP FRONT";
    string a = dq->LeftMost->data;
    dq->deleteElement(true);
    for (int i = 0; i < 160; i+=5)
    {
        system("cls");
        drawText(200, 250, s1);
        showElement(dq);
        line(400, 280, 800, 280);
        line(400, 370, 800, 370);
        rectangle(350 - i, 300, 400 - i, 350);
        drawText(365 - i, 315, a.c_str());
    }
}
void deleteRight(DEQUEUE* dq)
{
    char s1[] = "POP BACK";
    string a = dq->RightMost->data;
    dq->deleteElement(false);
    for (int i = 0; i < 900-420-dq->size()*60; i += 5)
    {
        system("cls");
        drawText(900, 250, s1);
        showElement(dq);
        line(400, 280, 800, 280);
        line(400, 370, 800, 370);
        rectangle(420 +dq->size()*60 + i, 300, 470 + dq->size() * 60 + i, 350);
        drawText(435 + dq->size() * 60 + i, 315, a.c_str());
    }
}
void kiemTra(DEQUEUE* dq)
{
    cout << "Chon 1 de Insert vao ben trai." << endl;
    cout << "Chon 2 de Insert vao ben phai." << endl;
    cout << "Chon 3 de Delete phia ben trai." << endl;
    cout << "Chon 4 de Delete phia ben phai." << endl;
    int t;
    cout << "Nhap lua chon: " << endl;
    cin >> t;
    if (t == 1)
    {
        insertLeft(dq);
        kiemTra(dq);
    }
    else if (t == 2)
    {
        insertRight(dq);
        kiemTra(dq);
    }
    else if (t == 3)
    {
        deleteLeft(dq);
        kiemTra(dq);
    }
    else if (t == 4)
    {
        deleteRight(dq);
        kiemTra(dq);
    }
}

int main()
{
    DEQUEUE* dq = new DEQUEUE();
    dq->init();
    initgraph();
    char s1[] = "Press any key to view the program.";
    drawText(400, 50, s1);
    _getch();
    system("cls");
    kiemTra(dq);
    //dq->insert("2", true);
    //showFinal(dq);
}
#include <iostream>
#include "ListS.cpp"
#include "Queue.cpp"
#include "String.cpp"
#include "piorityqueue.cpp"
#define BUFFOR 40


/*Dijkstra i Bfs pomoc z zrodeł
https://youtu.be/KiCBXu4P-2Y
https://youtu.be/pSqmAO-m7Lk*/
using namespace std;

struct NodeS;
struct NodeN;

void Directions(Poz* neigh) {
    neigh[0].x = 0; neigh[0].y = 1;
    neigh[1].x = 0; neigh[1].y = -1;
    neigh[2].x = -1; neigh[2].y = 0;
    neigh[3].x = 1; neigh[3].y = 0;
    neigh[4].x = 1; neigh[4].y = 1;
    neigh[5].x = 1; neigh[5].y = -1;
    neigh[6].x = -1; neigh[6].y = -1;
    neigh[7].x = -1; neigh[7].y = 1;
}

void Boki(Poz* neigh) {
    neigh[0].x = 1; neigh[0].y = 0;
    neigh[1].x = -1; neigh[1].y = 0;
    neigh[2].x = 0; neigh[2].y = 1;
    neigh[3].x = 0; neigh[3].y = -1;

}

String* CityReader(int x, int y, char** tab, int sx, int sy, Poz* look) {
    int a = 0;
    char nazwa[30] = { 0 };
    for (int i = 0; i < 8; i++) {
        if (x + look[i].x >= 0 && x + look[i].x <= sx - 1 && y + look[i].y >= 0 && y + look[i].y <= sy - 1 && tab[y + look[i].y][x + look[i].x] > 47) {
            while (tab[y+look[i].y][x + look[i].x-a] > 47) {
                a++;
            }
            int pocz = x + look[i].x - a;
            a = 0;
            while (tab[y + look[i].y][pocz+1+a] > 47) {
                nazwa[a] = tab[y + look[i].y][pocz+a+1];
                a++;
            }
            String* miasto = new String(nazwa, a);
            return miasto;
        }
    }
    return nullptr;
}

void dix(ListN* friendlist,int size,int start,int koniec,String* name,int tryb) {
    bool* visited = new bool[size];
    int* kolejnosc = new int[size];
    int* distance = new int[size];
    for (int k = 0; k < size; k++) {
        visited[k] = false;
        kolejnosc[k] = -1;
        distance[k] = INT_MAX;
    }
    distance[start] = 0;
    PQueue kolejka;
    kolejka.enqueue(start,0,name);
    while (kolejka.getSize() != 0){
        Dane nod = kolejka.dequeue();
        visited[nod.index] = true;
        if (distance[nod.index] < nod.distance) {
            continue;
        }
        ListN::NodeN* current = friendlist->head;
        while (current != nullptr) {
            if (nod.index==current->index) {
                break;
            }
            current = current->next;
        }
        ListS::NodeS* sasiedzi = current->bffs.head;
        while (sasiedzi != nullptr) {
            if (visited[sasiedzi->index]) {
                sasiedzi = sasiedzi->next;
                continue;
            }
            int odl = distance[nod.index] + sasiedzi->distance;
            if (odl < distance[sasiedzi->index]) {
                distance[sasiedzi->index] = odl;
                kolejnosc[sasiedzi->index] = nod.index;
                kolejka.enqueue(sasiedzi->index, odl, sasiedzi->name);
            }
            sasiedzi = sasiedzi->next;
        }
        if (nod.index == koniec) {
            if (tryb) {
                List where;
                for (int k = koniec; k != -1; k = kolejnosc[k]) {
                    ListN::NodeN* current = friendlist->head;
                    while (current != nullptr) {
                        if (k == current->index) {
                            where.dodajNaPoczatek(current->name);
                            break;
                        }
                        current = current->next;
                    }
                }
                printf("%d ", distance[nod.index]);
                where.usunOstatni();
                where.usunPierwszy();
                if (where.head == nullptr) {
                    break;
                }
                while (where.GetLength()!=0) {
                    where.head->value->print();
                    printf(" ");
                    where.usunPierwszy();
                }
                printf("\n");
            }
            else {
                printf("%d\n", distance[nod.index]);
            }
            break;
        }
    }
    delete[] visited;
    delete[] kolejnosc;
    delete[] distance;
}

void Bfs(char** tab, ListN::NodeN* node, ListN* friendlist, bool** back, int x, int y, Poz* boki, int sx, int sy) {
    int odleglosc = 0;
    int ilejeszcze = 0;
    int ilebedzie = 0;
    Queue Donaprawy;
    Queue bffs;
    Donaprawy.enqueue(y, x);
    //node->bffs.addToEnd(node->name, odleglosc);
    back[y][x] = true;
    for (int i = 0; i < 4; i++) {
        int xx = x + boki[i].x;
        int yy = y + boki[i].y;
        if ((xx<0 || yy<0 || xx>sx - 1 || yy>sy - 1)) {
            continue;
        }
        if ((back[yy][xx] == true)) {
            continue;
        }
        if (tab[yy][xx] == '*') {
            String* m = new String;
            int index;
            ListN::NodeN* current = friendlist->head;
            while (current != nullptr) {
                if (yy == current->y && xx == current->x) {
                    m = current->name;
                    index = current->index;
                    break;
                }
                current = current->next;
            }
            node->bffs.addToEnd(m, odleglosc + 1, index);
            back[yy][xx] = true;
            Donaprawy.enqueue(yy, xx);
        }
        else {
            bffs.enqueue(yy, xx);
            back[yy][xx] = true;
            Donaprawy.enqueue(yy, xx);
            ilejeszcze++;
        }
    }
    odleglosc++;
    while (bffs.getSize() > 0) {
        Poz a = bffs.dequeue();
            for (int i = 0; i < 4; i++) {
                int xx = a.x + boki[i].x;
                int yy = a.y + boki[i].y;
                if ((xx<0 || yy<0 || xx>sy - 1 || yy>sx - 1)) {
                    continue;
                }
                if ((back[xx][yy] == true)) {
                    continue;
                }
                if (tab[xx][yy] == '*') {
                    String* m = new String;
                    int index;
                    ListN::NodeN* current = friendlist->head;
                    while (current != nullptr) {
                        if (xx == current->y && yy == current->x) {
                            m = current->name;
                            index = current->index;
                            break;
                        }
                        current = current->next;
                    }
                    node->bffs.addToEnd(m, odleglosc+1, index);
                    back[xx][yy] = true;
                    Donaprawy.enqueue(xx, yy);
                }
                else {
                    bffs.enqueue(xx, yy);
                    back[xx][yy] = true;
                    Donaprawy.enqueue(xx, yy);
                    ilebedzie++;
                }
            }
        ilejeszcze--;
        if (ilejeszcze == 0) {
            ilejeszcze = ilebedzie;
            ilebedzie = 0;
            odleglosc++;
        }
    }
    while (Donaprawy.getSize() > 0) {
        Poz a = Donaprawy.dequeue();
        back[a.x][a.y] = false;
    }
}

void LotyRead(ListN* friendlist) {
    String* pocz=0;
    String* kon=0;
    int dlug;
    int red = 0;
    int p = 0;
    int a = 0;
    char buf[BUFFOR];
    fgets(buf, BUFFOR, stdin);
    while (red < 3) {
        if (buf[a] == ' ' || buf[a] == '\n') {
            if (red == 0) {
                pocz = new String(buf, a);
                p = a;
                red++;
            }
            else if (red == 1) {
                kon = new String(buf, p+1, a);
                p = a;
                red++;
            }
            else {
                String* temp = new String(buf, p, a);
                dlug = temp->czytoint();
                red++;
            }
        }
        a++;
    }
    ListN::NodeN* nextt = friendlist->head;
    while (nextt != nullptr) {
        if (nextt->name->Tosamo(*pocz)) {
            int in=0;
            ListN::NodeN* cur = friendlist->head;
            while (cur != nullptr) {
                if (cur->name->Tosamo(*kon)) {
                    in = cur->index;
                    break;
                }
                cur = cur->next;
            }
            nextt->bffs.addToEnd(kon, dlug, in);
        }
        nextt = nextt->next;
    }

}

void DrogiRead(ListN* friendlist) {
    String* pocz = 0;
    String* kon = 0;
    int dlug;
    int red = 0;
    int p = 0;
    int a = 0;
    char buf[BUFFOR];
    fgets(buf, BUFFOR, stdin);
    while (red < 3) {
        if (buf[a] == ' ' || buf[a] == '\n') {
            if (red == 0) {
                pocz = new String(buf, a);
                p = a;
                red++;
            }
            else if (red == 1) {
                kon = new String(buf, p+1, a);
                p = a;
                red++;
            }
            else {
                String* temp = new String(buf, p, a);
                dlug = temp->czytoint();
                red++;
            }
        }
        a++;
    }
    int poczatek=0;
    int koniec=0;
    ListN::NodeN* current = friendlist->head;
    while (current != nullptr) {
        if (current->name->Tosamo(*pocz)) {
            poczatek = current->index;
            break;
        }
        current = current->next;
    }
    ListN::NodeN* current2 = friendlist->head;
    while (current2 != nullptr) {
        if (current2->name->Tosamo(*kon)) {
            koniec = current2->index;
            break;
        }
        current2 = current2->next;
    }
    dix(friendlist, friendlist->GetLength() + 1, poczatek, koniec, pocz, dlug);
}

void CzytajPodroze(ListN* friendlist) {
    int ile;
    cin >> ile;
    char c = getchar();
    for (int i = 0; i < ile; i++) {
        DrogiRead(friendlist);
    }
}

void Loty(ListN* friendlist) {
    int ile;
    cin >> ile;
    char c = getchar();
    for (int i = 0; i < ile; i++) {
        LotyRead(friendlist);
    }
}

void PathConnecting(ListN* friendlist, bool** back, char** tab, int sx, int sy, Poz* look, Poz* boki) {
    int index = 0;
    ListN::NodeN* nextt = friendlist->head;
    int end = friendlist->GetLength() + 1;
    for (int i = 0; i < end; i++) {
        nextt->name = (CityReader(nextt->x, nextt->y, tab, sx, sy, look));
        nextt->index = index;
        index++;
        nextt = nextt->next;
    }
    ListN::NodeN* nextt2 = friendlist->head;
    for (int i = 0; i < end; i++) {
        Bfs(tab, nextt2, friendlist, back, nextt2->x, nextt2->y, boki, sx, sy);
        nextt2 = nextt2->next;
    }
}

void ReadMap(int x, int y, char** tab, ListN* friendlist, bool** back) {
    char c;
    for (int k = 0; k < y; k++) {
        for (int w = 0; w < x; w++) {
            c = getchar();
            if (c < 33) {
                c = getchar();
            }
            tab[k][w] = c;
            if (tab[k][w] == '*') {
                friendlist->addToEnd(w, k);
                back[k][w] = false;
            }
            else if (tab[k][w] == '#') {
                back[k][w] = false;
            }
            else {
                back[k][w] = true;
            }
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int x, y;
    cin >> x >> y;

    bool** back = new bool* [y];
    char** tab = new char* [y];
    for (int i = 0; i < y; i++) {
        tab[i] = new char[x];
        back[i] = new bool[x];
    }

    ListN friendlist;

    ReadMap(x, y, tab, &friendlist, back);

    Poz look[8];
    Directions(look);
    Poz boki[4];
    Boki(boki);
    PathConnecting(&friendlist, back, tab, x, y, look, boki);
    for (int i = 0; i < y; i++) {
        delete[] tab[i];
        delete[] back[i];
    }
    delete[] tab;
    delete[] back;

    Loty(&friendlist);

    CzytajPodroze(&friendlist);

    return 0;
}

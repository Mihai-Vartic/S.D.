#include <bits/stdc++.h>

using namespace std;

enum Culoare {Rosu, Negru, Dublu};

class Nod
{
    int n_info;
    Nod *stanga, *dreapta, *parinte;
    Culoare culoare;

public:

    Nod(int info = 0) 
    { 
       this -> n_info = info;
       stanga = dreapta = parinte = NULL; 
       this -> culoare = Rosu; 
    }

    Nod *getParinte()
    {
        return parinte;
    }

    Nod *getSt()
    {
        return stanga;
    }

    Nod *getDr()
    {
        return dreapta;
    }

    int getInfo()
    {
        return n_info;
    }

    void setParinte(Nod *p)
    {
        this -> parinte = p;
    }

    void setSt(Nod *st)
    {
        this -> stanga = st;
    }

    void setDr(Nod *dr)
    {
        this -> dreapta = dr;
    }

    void setInfo(int info)
    {
        this -> n_info = info;
    }

    friend Culoare getCuloare(Nod *x);
    friend void setCuloare(Nod *x, Culoare culoare1);
};

Culoare getCuloare(Nod *x)
{
    if(x == nullptr)
        return Negru;
    return x -> culoare;
}

void setCuloare(Nod *x, Culoare culoare1)
{
    if(x == nullptr)
        return;
    x -> culoare = culoare1;
}

Nod* minValueNode(Nod *&nod)
{
    Nod *ptr = nod;
    while (ptr -> getSt() != nullptr)
        ptr = ptr -> getSt();
    return ptr;
}

Nod *maxValueNode(Nod *&nod)
{
    Nod *ptr = nod;
    while (ptr -> getDr() != nullptr)
        ptr = ptr -> getDr();
    return ptr;
}

Nod *deleteBST(Nod *&root, int data)
{
    if(root == nullptr)
        return root;
    Nod *dr = root -> getDr();
    Nod *st = root -> getSt();
    if(data < root -> getInfo())
        return deleteBST(st, data);
    if(data > root -> getInfo())
        return deleteBST(dr, data);
    if(st == nullptr || dr == nullptr)
        return root;
    Nod *aux = minValueNode(dr);
    root -> setInfo(aux -> getInfo());
    return deleteBST(dr, aux -> getInfo());
}

void rotateLeft(Nod *&radacina, Nod *&x)
{
    Nod *right_child = x -> getDr();
    x -> setDr(right_child -> getSt());
    if(x -> getDr() != nullptr)
        x -> getDr() -> setParinte(x);
    right_child -> setParinte(x -> getParinte());
    if(x -> getParinte() == nullptr)
        radacina = right_child;
    else
        if(x == x -> getParinte() -> getSt())
            x -> getParinte() -> setSt(right_child);
    else
        x -> getParinte() -> setDr(right_child);
    right_child -> setSt(x);
    x -> setParinte(right_child);
}

void rotateRight(Nod *&radacina, Nod *&x)
{
    Nod *left_child = x -> getSt();
    x -> setSt(left_child -> getDr());
    if(x -> getSt() != nullptr)
        x -> getSt() -> setParinte(x);
    left_child -> setParinte(x -> getParinte());
    if(x -> getParinte() == nullptr)
        radacina = left_child;
    else
        if(x == x -> getParinte() -> getSt())
            x -> getParinte() -> setSt(left_child);
    else
        x -> getParinte() -> setDr(left_child);
    left_child -> setDr(x);
    x -> setParinte(left_child);
}

void swapColor(Nod *a, Nod *b)
{
    Culoare aux = getCuloare(a);
    setCuloare(a, getCuloare(b));
    setCuloare(b, aux);
}

void fix(Nod *&radacina, Nod *&x)
{
    Nod *parinte = nullptr;
    Nod *bunic = nullptr;
    while(x != radacina && getCuloare(x) == Rosu && getCuloare(x -> getParinte()) == Rosu)
    {
        parinte = x -> getParinte();
        bunic = parinte -> getParinte();
        if(parinte == bunic -> getSt()) {
            Nod *unchi = bunic -> getDr();
            if(unchi != nullptr && getCuloare(unchi) == Rosu)
            {
                setCuloare(unchi, Negru);
                setCuloare(parinte, Negru);
                setCuloare(bunic, Rosu);
                x = bunic;
            }
            else
            {
                if(x == parinte -> getDr())
                {
                    rotateLeft(radacina, parinte);
                    x = parinte;
                    parinte = x -> getParinte();
                }
                rotateRight(radacina, bunic);
                swapColor(parinte, bunic);
                x = parinte;
            }
        }
        else
        {
            Nod *unchi = bunic -> getSt();
            if(unchi != nullptr && getCuloare(unchi) == Rosu)
            {
                setCuloare(unchi, Negru);
                setCuloare(parinte, Negru);
                setCuloare(bunic, Rosu);
                x = bunic;
            }
            else
            {
                if (x == parinte -> getSt())
                {
                    rotateRight(radacina, parinte);
                    x = parinte;
                    parinte = x -> getParinte();
                }
                rotateLeft(radacina, bunic);
                swapColor(parinte, bunic);
                x = parinte;
            }
        }
    }
    setCuloare(radacina, Negru);
}

Nod *inserareABC(Nod *&rad, Nod *&x)
{
    if((rad == nullptr) || (rad -> getInfo() == 0))
        return x;
    Nod *st = rad -> getSt();
    Nod *dr = rad -> getDr();
    if(x -> getInfo() <= rad -> getInfo())
    {
        rad -> setSt(inserareABC(st, x));
        rad -> getSt() -> setParinte(rad);
    }
    else
        if(x -> getInfo() > rad -> getInfo())
        {
            rad -> setDr(inserareABC(dr, x));
            rad -> getDr() -> setParinte(rad);
        }
    return rad;
}

void insertRBT(Nod *&radacina, int info)
{
    Nod *x = new Nod(info);
    radacina = inserareABC(radacina, x);
    fix(radacina, x);
}

void fixDelete(Nod *&radacina, Nod *&nod)
{
    if(nod == nullptr)
        return;
    if(nod == radacina)
    {
        radacina = nullptr;
        return;
    }
    if(getCuloare(nod) == Rosu || getCuloare(nod -> getSt()) == Rosu || getCuloare(nod -> getDr()) == Rosu)
    {
        Nod *copil = nod -> getSt() != nullptr ? nod->getSt() : nod->getDr();
        if(nod == nod -> getParinte() -> getSt())
        {
            nod -> getParinte() -> setSt(copil);
            if(copil != nullptr)
                copil -> setParinte(nod -> getParinte());
            setCuloare(copil, Negru);
            delete (nod);
        }
        else
        {
            nod -> getParinte() -> setDr(copil);
            if(copil != nullptr)
                copil -> setParinte(nod -> getParinte());
            setCuloare(copil, Negru);
            delete (nod);
        }
    }
    else
    {
        Nod *frate = nullptr;
        Nod *parinte = nullptr;
        Nod *ptr = nod;
        setCuloare(ptr, Dublu);
        while(ptr != radacina && getCuloare(ptr) == Dublu)
        {
            parinte = ptr -> getParinte();
            if (ptr == parinte -> getSt())
            {
                frate = parinte -> getDr();
                if(getCuloare(frate) == Rosu)
                {
                    setCuloare(frate, Negru);
                    setCuloare(parinte, Rosu);
                    rotateLeft(radacina, parinte);
                }
                else
                {
                    if(getCuloare(frate -> getSt()) == Negru && getCuloare(frate -> getDr()) == Negru)
                    {
                        setCuloare(frate, Rosu);
                        if(getCuloare(parinte) == Rosu)
                            setCuloare(parinte, Negru);
                        else
                            setCuloare(parinte, Dublu);
                        ptr = parinte;
                    }
                    else
                    {
                        if(getCuloare(frate -> getDr()) == Negru)
                        {
                            setCuloare(frate -> getSt(), Negru);
                            setCuloare(frate, Rosu);
                            rotateRight(radacina, frate);
                            frate = parinte -> getDr();
                        }
                        setCuloare(frate, getCuloare(parinte));
                        setCuloare(parinte, Negru);
                        setCuloare(frate->getDr(), Negru);
                        rotateLeft(radacina, parinte);
                        break;
                    }
                }
            }
            else
            {
                frate = parinte->getSt();
                if(getCuloare(frate) == Rosu)
                {
                    setCuloare(frate, Negru);
                    setCuloare(parinte, Rosu);
                    rotateRight(radacina, parinte);
                }
                else
                {
                    if(getCuloare(frate -> getSt()) == Negru && getCuloare(frate -> getDr()) == Negru)
                    {
                        setCuloare(frate, Rosu);
                        if(getCuloare(parinte) == Rosu)
                            setCuloare(parinte, Negru);
                        else
                            setCuloare(parinte, Dublu);
                        ptr = parinte;
                    }
                    else
                    {
                        if(getCuloare(frate -> getSt()) == Negru)
                        {
                            setCuloare(frate -> getDr(), Negru);
                            setCuloare(frate, Rosu);
                            rotateLeft(radacina, frate);
                            frate = parinte -> getSt();
                        }
                        setCuloare(frate, getCuloare(parinte));
                        setCuloare(parinte, Negru);
                        setCuloare(frate -> getSt(), Negru);
                        rotateRight(radacina, parinte);
                        break;
                    }
                }
            }
        }
        if(nod == nod -> getParinte() -> getSt())
            nod -> getParinte() -> setSt(nullptr);
        else
            nod -> getParinte() -> setDr(nullptr);
        delete(nod);
        setCuloare(radacina, Negru);
    }
}

void nrAparitii(Nod *rad, int val, int &contor)
{
    if(rad == nullptr)
        return;
    else
    {
        nrAparitii(rad -> getSt(), val, contor);
        if(val == rad -> getInfo())
            contor++;
        nrAparitii(rad -> getDr(), val, contor);
    }
}

void deleteRBT(Nod *&radacina, int info)
{
    int cntr = 0;
    nrAparitii(radacina, info, cntr);
    cout << endl << cntr;
    while(cntr > 0)
    {
        Nod *x = deleteBST(radacina, info);
        fixDelete(radacina, x);
        cntr--;
    }
}

void cautare(Nod *rad, int x)
{
    int cntr = 0;
    nrAparitii(rad, x, cntr);
    if(cntr >= 1)
        cout << '1';
    else
        cout << '0';
}

Nod *gasesteNod(Nod* rad, int val)
{
    if(rad == nullptr || rad->getInfo() == val)
        return rad;
    if(rad -> getInfo() < val)
        return gasesteNod(rad -> getDr(), val);
    return gasesteNod(rad -> getSt(), val);
}

Nod *succesor(Nod* rad, int val)
{
    Nod *nod = gasesteNod(rad, val);
    if(nod -> getDr() != nullptr)
    {
        Nod *dr = nod -> getDr();
        return minValueNode(dr);
    }
    Nod *parinte = nod->getParinte();
    while(parinte != nullptr && nod == parinte -> getDr())
    {
        nod = parinte;
        parinte = parinte -> getParinte();
    }
    return parinte;
}

void afisaresuccesor(Nod *rad, int x)
{
    Nod *succ = succesor(rad, x);
    if(succ == nullptr)
        cout << -1;
    else
        cout << succ -> getInfo();
}

Nod *predecesor(Nod* rad, int val)
{
    Nod *nod = gasesteNod(rad, val);
    if(nod->getSt() != nullptr)
    {
        Nod *st = nod -> getSt();
        return maxValueNode(st);
    }
    Nod *parinte = nod->getParinte();
    while(parinte != nullptr && nod == parinte -> getSt())
    {
        nod = parinte;
        parinte = parinte -> getParinte();
    }
    return parinte;
}

void afisarepredecesor(Nod *rad, int x)
{
    Nod *pred = predecesor(rad, x);
    if(pred == nullptr)
        cout << -1;
    else
        cout << pred -> getInfo();
}

void afisareInterval(Nod *rad, int x, int y)
{
    if(rad == nullptr)
        return;
    if(x < rad -> getInfo())
        afisareInterval(rad->getSt(), x, y);
    if(x < rad -> getInfo() && rad -> getInfo() < y)
        cout << rad -> getInfo() << " ";
    if(y > rad -> getInfo())
        afisareInterval(rad -> getDr(), x, y);
}

void afisare(Nod *nod)
{
    if(nod == nullptr)
        return;
    else
    {
        afisare(nod -> getSt());
        cout << nod -> getInfo() << " " << getCuloare(nod) << endl;
        afisare(nod -> getDr());
    }
}

int main()
{

  int op, x, y, nrop;
  Nod *rad = NULL;
  cout << "Citim numarul de operatii: ";
  cin >> nrop;
  
  for (int i = 0; i <nrop; i++)
  {
        cout << "\nCitim operatia si numarul: ";
        cin >> op >> x;
        switch(op)
        { 
            case 1: //! 1 -> inserare, inseram valoarea
            {
                insertRBT(rad, x);
                break;
            }

            case 2: //! 2 -> delete
            {
                deleteRBT(rad, x);
                break;
            }

            case 3: //! 3 -> find val
            {
                cautare(rad, x);
                break;
            }

            case 4: //! 4 -> succesor(x)
            {
                afisaresuccesor(rad, x);
                break;
            }

            case 5: //! 5 -> predecesor(x)
            {
                afisarepredecesor(rad, x);
                break;
            }

            case 6: //! 6 -> afișare interval(x y)
            {
                cin >> y;
                afisareInterval(rad, x, y);
                break;
            }

            default:
                cout << "Operatie incorecta.";
        }
  }
  return 0;
}

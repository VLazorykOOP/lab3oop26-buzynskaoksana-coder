#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

// ================= TIME =================

class Time {
private:
    int h, m, s;

public:
    Time() { h = 0; m = 0; s = 0; }

    Time(int hh, int mm, int ss) {
        setTime(hh, mm, ss);
    }

    void setTime(int hh, int mm, int ss) {
        if (hh >= 0 && hh < 24) h = hh; else h = 0;
        if (mm >= 0 && mm < 60) m = mm; else m = 0;
        if (ss >= 0 && ss < 60) s = ss; else s = 0;
    }

    int getH() { return h; }
    int getM() { return m; }
    int getS() { return s; }

    void print24() {
        cout << h << " hours " << m << " minutes " << s << " seconds\n";
    }

    void print12() {
        int hh = h % 12;
        if (hh == 0) hh = 12;
        if (h < 12)
            cout << hh << " a.m. " << m << " minutes " << s << " seconds\n";
        else
            cout << hh << " p.m. " << m << " minutes " << s << " seconds\n";
    }
};

// ================= VECTOR =================

class Vector {
private:
    float* data;
    int    size;
    int    state;
    static int count;

public:
    Vector(int n = 1, float val = 0) {
        data = new(nothrow) float[n];
        if (!data) { size = 0; state = 1; }
        else {
            size = n; state = 0;
            for (int i = 0; i < size; i++) data[i] = val;
        }
        ++count;
    }

    Vector(const Vector& o) {
        data = new(nothrow) float[o.size];
        if (!data) { size = 0; state = 1; }
        else {
            size = o.size; state = o.state;
            for (int i = 0; i < size; i++) data[i] = o.data[i];
        }
        ++count;
    }

    Vector& operator=(const Vector& o) {
        if (this == &o) return *this;
        delete[] data;
        data = new(nothrow) float[o.size];
        if (!data) { size = 0; state = 1; }
        else {
            size = o.size; state = o.state;
            for (int i = 0; i < size; i++) data[i] = o.data[i];
        }
        return *this;
    }

    ~Vector() { delete[] data; --count; }

    void set(int i, float val = 0) {
        if (i < 0 || i >= size) { state = 2; cout << "Error: out of bounds\n"; return; }
        data[i] = val;
    }

    float get(int i) {
        if (i < 0 || i >= size) { state = 2; cout << "Error: out of bounds\n"; return 0; }
        return data[i];
    }

    void print() {
        if (state == 1) { cout << "[bad_alloc]\n"; return; }
        cout << "[ ";
        for (int i = 0; i < size; i++) cout << data[i] << " ";
        cout << "]\n";
    }

    Vector add(const Vector& v) {
        Vector r(size);
        for (int i = 0; i < size; i++) r.data[i] = data[i] + v.data[i];
        return r;
    }

    Vector sub(const Vector& v) {
        Vector r(size);
        for (int i = 0; i < size; i++) r.data[i] = data[i] - v.data[i];
        return r;
    }

    Vector mul(long scalar) {
        Vector r(size);
        for (int i = 0; i < size; i++) r.data[i] = data[i] * scalar;
        return r;
    }

    float sum() {
        float s = 0;
        for (int i = 0; i < size; i++) s += data[i];
        return s;
    }

    bool operator==(Vector& o) { return sum() == o.sum(); }
    bool operator!=(Vector& o) { return sum() != o.sum(); }
    bool operator> (Vector& o) { return sum() > o.sum(); }
    bool operator< (Vector& o) { return sum() < o.sum(); }

    int getState() { return state; }
    int getSize() { return size; }
    static int getCount() { return count; }
};

int Vector::count = 0;

// ================= MATRIX =================

class Matrix {
private:
    float* data;
    int    n, m;
    int    state;
    static int count;

public:
    Matrix(int r = 2, int c = 2, float val = 0) {
        data = new(nothrow) float[r * c];
        if (!data) { n = m = 0; state = 1; }
        else {
            n = r; m = c; state = 0;
            for (int i = 0; i < n * m; i++) data[i] = val;
        }
        ++count;
    }

    Matrix(const Matrix& o) {
        data = new(nothrow) float[o.n * o.m];
        if (!data) { n = m = 0; state = 1; }
        else {
            n = o.n; m = o.m; state = o.state;
            for (int i = 0; i < n * m; i++) data[i] = o.data[i];
        }
        ++count;
    }

    Matrix& operator=(const Matrix& o) {
        if (this == &o) return *this;
        delete[] data;
        data = new(nothrow) float[o.n * o.m];
        if (!data) { n = m = 0; state = 1; }
        else {
            n = o.n; m = o.m; state = o.state;
            for (int i = 0; i < n * m; i++) data[i] = o.data[i];
        }
        return *this;
    }

    ~Matrix() { delete[] data; --count; }

    void set(int i, int j, float val = 0) {
        if (i < 0 || i >= n || j < 0 || j >= m) { state = 2; cout << "Error: out of bounds\n"; return; }
        data[i * m + j] = val;
    }

    float get(int i, int j) {
        if (i < 0 || i >= n || j < 0 || j >= m) { state = 2; cout << "Error: out of bounds\n"; return 0; }
        return data[i * m + j];
    }

    void print() {
        if (state == 1) { cout << "[bad_alloc]\n"; return; }
        for (int i = 0; i < n; i++) {
            cout << "| ";
            for (int j = 0; j < m; j++) cout << data[i * m + j] << " ";
            cout << "|\n";
        }
    }

    Matrix add(const Matrix& x) {
        Matrix r(n, m);
        for (int i = 0; i < n * m; i++) r.data[i] = data[i] + x.data[i];
        return r;
    }

    Matrix sub(const Matrix& x) {
        Matrix r(n, m);
        for (int i = 0; i < n * m; i++) r.data[i] = data[i] - x.data[i];
        return r;
    }

    Matrix mul(const Matrix& x) {
        Matrix r(n, x.m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < x.m; j++)
                for (int k = 0; k < m; k++)
                    r.data[i * x.m + j] += data[i * m + k] * x.data[k * x.m + j];
        return r;
    }

    Matrix mulScalar(float scalar) {
        Matrix r(n, m);
        for (int i = 0; i < n * m; i++) r.data[i] = data[i] * scalar;
        return r;
    }

    float sum() {
        float s = 0;
        for (int i = 0; i < n * m; i++) s += data[i];
        return s;
    }

    bool operator==(Matrix& o) { return sum() == o.sum(); }
    bool operator!=(Matrix& o) { return sum() != o.sum(); }
    bool operator> (Matrix& o) { return sum() > o.sum(); }
    bool operator< (Matrix& o) { return sum() < o.sum(); }

    int getState() { return state; }
    static int getCount() { return count; }
};

int Matrix::count = 0;

// ================= MAIN =================

int main() {
    srand(time(0));
    int choice;

    do {
        cout << "\n=========================\n";
        cout << "1 - Time\n";
        cout << "2 - Vector\n";
        cout << "3 - Matrix\n";
        cout << "0 - Exit\n";
        cout << "=========================\n";
        cout << "Choice: ";
        cin >> choice;

        // ── TASK 1 ───────────────────────────────────────────────────────────
        if (choice == 1) {
            cout << "\n--- TIME ---\n";

            int h, m, s;
            cout << "Enter time (h m s): ";
            cin >> h >> m >> s;
            Time t1(h, m, s);
            cout << "24h: "; t1.print24();
            cout << "12h: "; t1.print12();

            ofstream fout("time.txt");
            fout << t1.getH() << " " << t1.getM() << " " << t1.getS() << "\n";
            fout.close();
            cout << "Saved to time.txt\n";

            Time t3(rand() % 24, rand() % 60, rand() % 60);
            cout << "Random: "; t3.print24();
        }

        // ── TASK 2 ───────────────────────────────────────────────────────────
        else if (choice == 2) {
            cout << "\n--- VECTOR ---\n";

            int n;
            cout << "Enter size: ";
            cin >> n;

            Vector v1(n);
            cout << "Enter elements:\n";
            for (int i = 0; i < n; i++) {
                float x; cin >> x;
                v1.set(i, x);
            }
            cout << "Vector:     "; v1.print();

            Vector v2(n);
            for (int i = 0; i < n; i++) v2.set(i, rand() % 10);
            cout << "Random:     "; v2.print();

            ofstream fout("vector.txt");
            for (int i = 0; i < n; i++) fout << v1.get(i) << " ";
            fout.close();
            cout << "Saved to vector.txt\n";

            cout << "Add:        "; v1.add(v2).print();
            cout << "Sub:        "; v1.sub(v2).print();
            cout << "Mul scalar: "; v1.mul(2).print();

            cout << "v1 == v2: " << (v1 == v2 ? "true" : "false") << "\n";
            cout << "v1 != v2: " << (v1 != v2 ? "true" : "false") << "\n";
            cout << "v1 >  v2: " << (v1 > v2 ? "true" : "false") << "\n";
            cout << "v1 <  v2: " << (v1 < v2 ? "true" : "false") << "\n";

            Vector v4(v1);
            cout << "Copy:       "; v4.print();
            Vector v5(1);
            v5 = v1;
            cout << "Assigned:   "; v5.print();

            cout << "Objects alive: " << Vector::getCount() << "\n";

            v1.get(0);
            cout << "State after bad access: " << v1.getState() << "\n";

            Vector huge(1000000000);
            cout << "Huge state: " << huge.getState() << "\n";
        }

        // ── TASK 3 ───────────────────────────────────────────────────────────
        else if (choice == 3) {
            cout << "\n--- MATRIX ---\n";

            int r, c;
            cout << "Enter rows and cols: ";
            cin >> r >> c;

            Matrix m1(r, c);
            cout << "Enter matrix:\n";
            for (int i = 0; i < r; i++)
                for (int j = 0; j < c; j++) {
                    float x; cin >> x;
                    m1.set(i, j, x);
                }
            cout << "Matrix:\n"; m1.print();

            Matrix m2(r, c);
            for (int i = 0; i < r; i++)
                for (int j = 0; j < c; j++) m2.set(i, j, rand() % 10);
            cout << "Random:\n"; m2.print();

            ofstream fout("matrix.txt");
            for (int i = 0; i < r; i++)
                for (int j = 0; j < c; j++) fout << m1.get(i, j) << " ";
            fout.close();
            cout << "Saved to matrix.txt\n";

            cout << "Add:\n";        m1.add(m2).print();
            cout << "Sub:\n";        m1.sub(m2).print();
            cout << "Mul scalar:\n"; m1.mulScalar(2).print();

            if (r == c) {
                cout << "Mul matrix:\n"; m1.mul(m2).print();
            }

            cout << "m1 == m2: " << (m1 == m2 ? "true" : "false") << "\n";
            cout << "m1 != m2: " << (m1 != m2 ? "true" : "false") << "\n";
            cout << "m1 >  m2: " << (m1 > m2 ? "true" : "false") << "\n";
            cout << "m1 <  m2: " << (m1 < m2 ? "true" : "false") << "\n";

            Matrix m4(m1);
            cout << "Copy:\n"; m4.print();
            Matrix m5;
            m5 = m1;
            cout << "Assigned:\n"; m5.print();

            cout << "Objects alive: " << Matrix::getCount() << "\n";

            m1.get(0, 0);
            cout << "State after bad access: " << m1.getState() << "\n";

            Matrix huge(30000, 30000);
            cout << "Huge state: " << huge.getState() << "\n";
        }

    } while (choice != 0);

    cout << "Goodbye!\n";
    return 0;
}